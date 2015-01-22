<?php

/**
 * Implements hook_drush_command()
 */
function sbac_forum_drush_command() {
  $items['sbac-forum-create-resource-forums'] = array(
    'description' => 'Create all resource forums',
    'arguments' => array(
      'count' => 'How many resources do you want to process?',
    ),
  );
  $items['sbac-forum-delete-all-resource-forums'] = array(
    'description' => 'Delete all the resource forums'
  );
  $items['sbac-forum-update-participant-count'] = array(
    'description' => 'Update participant count'
  );
  $items['sbac-forum-reset-participants'] = array(
    'description' => 'Restore the participants on all forums',
  );

  return $items;
}

/**
 * Generate all resource forums
 */
function drush_sbac_forum_create_resource_forums($count = NULL) {
  $resources = sbac_forum_get_posted_resources($count);
  $vocab = taxonomy_vocabulary_machine_name_load(SBAC_FORUM_VOCAB_NAME);
  foreach ($resources as $nid) {
    echo '.';
    sbac_forum_create_resource_forum($nid, $vocab->vid);
  }
}

function drush_sbac_forum_delete_all_resource_forums() {
  // Get all resource forums
  $forum_query = "
    SELECT
      entity_id
    FROM {field_data_field_forum_resource_ref}
    WHERE field_forum_resource_ref_target_id IS NOT null";
  $results = db_query($forum_query)->fetchCol();
  foreach ($results as $tid) {
    echo '.';
    sbac_forum_delete_resource_forum($tid);
  }
}

function drush_sbac_forum_update_participant_count() {
  $query = "
    SELECT
      t.tid
    FROM {taxonomy_vocabulary} v
      LEFT JOIN {taxonomy_term_data} t
        ON v.vid = t.vid
    WHERE v.machine_name = 'forum'";
  $forum_ids = db_query($query)->fetchCol();
  foreach ($forum_ids as $tid) {
    $term = taxonomy_term_load($tid);
    $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
    if ($term_wrapper->field_forum_member_count->value() > 1) {
      foreach ($term_wrapper->field_fc_forum_members as $member_wrapper) {
        $uid = $member_wrapper->field_fc_forum_member->uid->value();
        if (!sbac_forum_user_has_participated($tid, $uid)) {
          sbac_forum__api__leave_forum($term, 'leave', $uid);
        }
      }
    }
  }
}

/**
 * Reset the forum's participants according to who has contributed and the forum restrictions
 *
 * @param $forum_id
 */
function drush_sbac_forum_reset_participants() {
  $query = db_select('taxonomy_term_data', 't');
  $query->innerJoin('taxonomy_vocabulary', 'v', 't.vid = v.vid');
  $query->condition('v.machine_name', 'forum');
  $query->fields('t', array('tid'));
  $forums = $query->execute()->fetchCol();
  $forum_count = count($forums);
  $i = 1;
  $start_time = time();
  foreach ($forums as $forum_id) {
    print "Processing $i/$forum_count (forum id $forum_id)\n";
    $term = taxonomy_term_load($forum_id);
    if ($term) {
      // Get the forum restrictions.  We won't add users who don't meet these restrictions
      $state_restrictions = array();
      if (isset($term->field_forum_access_states) && !empty($term->field_forum_access_states[LANGUAGE_NONE])) {
        $all_states = $term->field_forum_access_states[LANGUAGE_NONE][0]['value'];
        if (!$all_states && !empty($term->field_state[LANGUAGE_NONE])) {
          foreach ($term->field_state[LANGUAGE_NONE] as $key => $value) {
            $state_restrictions[$value['tid']] = $value['tid'];
          }
        }
      }

      $role_restrictions = array();
      if (isset($term->field_forum_access_user_roles) && !empty($term->field_forum_access_user_roles[LANGUAGE_NONE])) {
        $all_roles = $term->field_forum_access_user_roles[LANGUAGE_NONE][0]['value'];
        if (!$all_roles && !empty($term->field_forum_access_role_list[LANGUAGE_NONE])) {
          foreach ($term->field_forum_access_role_list[LANGUAGE_NONE] as $key => $value) {
            $role_restrictions[$value['value']] = $value['value'];
          }
        }
      }

      // delete all the current members
      $forum_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
      foreach ($forum_wrapper->field_fc_forum_members as $index => $member_wrapper) {
        $member_wrapper->delete();
        unset($term->field_fc_forum_members[LANGUAGE_NONE][$index]);
      }
      $current_member_count = 0;
      $current_members = array();

      // Add topic creators
      $topics = _sbac_forum_get_topic_creators($term->tid);
      foreach ($topics as $topic) {
        if (empty($role_restrictions) || (!empty($role_restrictions) && array_intersect($role_restrictions, explode(',', $topic->roles)))) {
          if (empty($state_restrictions) || (!empty($state_restrictions) && array_intersect($state_restrictions, explode(',', $topic->states)))) {
            // add the user to the participant list
            $params = array(
              'field_name' => 'field_fc_forum_members'
            );
            $new_member_item = entity_create('field_collection_item', $params);
            $new_member_item->setHostEntity('taxonomy_term', $term);
            $new_member_item->field_fc_forum_member[LANGUAGE_NONE][]['target_id'] = $topic->uid;
            $new_member_item->field_fc_forum_member_joined[LANGUAGE_NONE][]['value'] = date(DATE_FORMAT_DATETIME, $topic->created);
            $new_member_item->field_fc_forum_member_rcnt_actvt[LANGUAGE_NONE][]['value'] = $topic->created;
            $new_member_item->field_fc_forum_member_tpic_count[LANGUAGE_NONE][]['value'] = $topic->count;
            $new_member_item->field_fc_forum_member_post_count[LANGUAGE_NONE][]['value'] = 0;
            $new_member_item->field_fc_forum_member_reco_count[LANGUAGE_NONE][]['value'] = 0;
            $new_member_item->field_fc_forum_member_partip_scr[LANGUAGE_NONE][]['value'] = sbac_forum_calculate_participation_score(0, $topic->count, 0);
            $new_member_item->save();

            $current_members[$topic->uid] = $new_member_item->item_id;
            $current_member_count++;
          }
        }
      }

      // Add commenter
      $comments = _sbac_forum_get_commenters($term->tid);
      foreach ($comments as $comment) {
        if (empty($role_restrictions) || (!empty($role_restrictions) && array_intersect($role_restrictions, explode(',', $comment->roles)))) {
          if (empty($state_restrictions) || (!empty($state_restrictions) && array_intersect($state_restrictions, explode(',', $comment->states)))) {
            $query = db_select('comment', 'c');
            $query->innerJoin('field_data_field_topic_comment_recommended', 'r', 'r.entity_id = c.cid AND r.entity_type = \'comment\'');
            $query->innerJoin('field_data_field_topic_forum_parent', 'p', 'p.entity_id = c.nid');
            $query->condition('p.field_topic_forum_parent_tid', $term->tid)
              ->condition('c.uid', $comment->uid);
            $recommend_count = $query->fields('c', array('cid'))->countQuery()->execute()->fetchField();
            if (!in_array($comment->uid, array_keys($current_members))) {
              // add the user to the participant list
              $params = array(
                'field_name' => 'field_fc_forum_members'
              );
              $new_member_item = entity_create('field_collection_item', $params);
              $new_member_item->setHostEntity('taxonomy_term', $term);
              $new_member_item->field_fc_forum_member[LANGUAGE_NONE][]['target_id'] = $comment->uid;
              $new_member_item->field_fc_forum_member_joined[LANGUAGE_NONE][]['value'] = date(DATE_FORMAT_DATETIME, $comment->created);
              $new_member_item->field_fc_forum_member_rcnt_actvt[LANGUAGE_NONE][]['value'] = $comment->created;
              $new_member_item->field_fc_forum_member_post_count[LANGUAGE_NONE][]['value'] = $comment->count;
              $new_member_item->field_fc_forum_member_reco_count[LANGUAGE_NONE][]['value'] = $recommend_count;
              $new_member_item->field_fc_forum_member_tpic_count[LANGUAGE_NONE][]['value'] = 0;
              $new_member_item->field_fc_forum_member_partip_scr[LANGUAGE_NONE][]['value'] = sbac_forum_calculate_participation_score($recommend_count, 0, $comment->count);
              $new_member_item->save();

              $current_member_count++;
              $current_members[$comment->uid] = $new_member_item->item_id;
            }
            else {
              $member = field_collection_item_load($current_members[$comment->uid]);
              if ($comment->created < strtotime($member->field_fc_forum_member_joined['und'][0]['value'])) {
                $member->field_fc_forum_member_joined['und'][0]['value'] = date(DATE_FORMAT_DATETIME, $comment->created);
              }
              if ($comment->created > $member->field_fc_forum_member_rcnt_actvt['und'][0]['value']) {
                $member->field_fc_forum_member_rcnt_actvt['und'][0]['value'] = $comment->created;
              }
              $member->field_fc_forum_member_post_count['und'][0]['value'] = $comment->count;
              $member->field_fc_forum_member_reco_count['und'][0]['value'] = $recommend_count;
              $member->field_fc_forum_member_partip_scr['und'][0]['value'] = sbac_forum_calculate_participation_score($recommend_count, $member->field_fc_forum_member_tpic_count['und'][0]['value'], $comment->count);
              $member->save();
            }
          }
        }
      }

      $term->field_forum_member_count[LANGUAGE_NONE][0]['value'] = $current_member_count;
      taxonomy_term_save($term);

      // invalidate member list cache when a new user joins.
      $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME . $term->tid;
      if (cache_get($cid)) {
        cache_clear_all($cid, 'cache');
      }
    }
    $i++;
  }
  $end_time = time();
  $duration = $end_time - $start_time;
  $dtF = new DateTime("@0");
  $dtT = new DateTime("@$duration");
  print 'Duration: ' . $dtF->diff($dtT)->format('%a days, %h hours, %i minutes and %s seconds');
}