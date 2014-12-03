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
    'description' => 'Check to see who has participated in the forum and add them to the participant list',
    'arguments' => array(
      'forum_id' => 'The forum id',
    )
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
function drush_sbac_forum_reset_participants($forum_id) {
  $forum_obj = taxonomy_term_load($forum_id);
  if (!empty($forum_obj)) {

    // Get the forum restrictions.  We won't add users who don't meet these restrictions
    $state_restrictions = array();
    if (isset($forum_obj->field_forum_access_states) && !empty($forum_obj->field_forum_access_states[LANGUAGE_NONE])) {
      $all_states = $forum_obj->field_forum_access_states[LANGUAGE_NONE][0]['value'];
      if (!$all_states && !empty($forum_obj->field_state[LANGUAGE_NONE])) {
        foreach ($forum_obj->field_state[LANGUAGE_NONE] as $key => $value) {
          $state_restrictions[$value['tid']] = $value['tid'];
        }
      }
    }

    $role_restrictions = array();
    if (isset($forum_obj->field_forum_access_user_roles) && !empty($forum_obj->field_forum_access_user_roles[LANGUAGE_NONE])) {
      $all_roles = $forum_obj->field_forum_access_user_roles[LANGUAGE_NONE][0]['value'];
      if (!$all_roles && !empty($forum_obj->field_forum_access_role_list[LANGUAGE_NONE])) {
        foreach ($forum_obj->field_forum_access_role_list[LANGUAGE_NONE] as $key => $value) {
          $role_restrictions[$value['value']] = $value['value'];
        }
      }
    }

    $forum_wrapper = entity_metadata_wrapper('taxonomy_term', $forum_obj);

    // delete all the current members
    if (!empty($forum_obj->field_fc_forum_members[LANGUAGE_NONE])) {
      $members_to_delete = array();
      foreach ($forum_obj->field_fc_forum_members[LANGUAGE_NONE] as $key => $value) {
        $members_to_delete[] = $value['value'];
        unset($forum_obj->field_fc_forum_members[LANGUAGE_NONE][$key]);
      }
      entity_delete_multiple('field_collection_item', $members_to_delete);
    }

    $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME . $forum_obj->tid;
    if (cache_get($cid)) {
      cache_clear_all($cid, 'cache');
    }

    $current_member_count = 0;

    // Add topic creators
    $query = db_select('field_data_field_topic_forum_parent', 'p');
    $query->leftJoin('node', 'n', 'n.nid = p.entity_id');
    $query->leftJoin('users_roles', 'ur', 'ur.uid = n.uid');
    $query->leftJoin('field_data_field_state', 's', 's.entity_id = n.uid AND s.entity_type = \'user\'');
    $query->condition('p.bundle', 'topic')
      ->condition('p.field_topic_forum_parent_tid', $forum_id);
    $query->fields('n', array('uid'));
    $query->addExpression("max(n.created)", 'created');
    $query->addExpression("count(DISTINCT n.nid)", 'count');
    $query->addExpression("GROUP_CONCAT(DISTINCT ur.rid)", 'roles');
    $query->addExpression("GROUP_CONCAT(DISTINCT s.field_state_tid)", 'states');
    $query->groupBy('n.uid');
    $topics = $query->execute()->fetchAll();
    foreach ($topics as $topic) {
      // check forum role restrictions
      if (empty($role_restrictions) || (!empty($role_restrictions) && array_intersect($role_restrictions, explode(',', $topic->roles)))) {
        if (empty($state_restrictions) || (!empty($state_restrictions) && array_intersect($state_restrictions, explode(',', $topic->states)))) {
          // add the user to the participant list
          $params = array(
            'field_name' => 'field_fc_forum_members'
          );
          $new_member_item = entity_create('field_collection_item', $params);
          $new_member_item->setHostEntity('taxonomy_term', $forum_obj);
          $new_member_wrapper = entity_metadata_wrapper('field_collection_item', $new_member_item);
          $new_member_wrapper->field_fc_forum_member->set($topic->uid);
          $new_member_wrapper->field_fc_forum_member_joined->set($topic->created);
          $new_member_wrapper->field_fc_forum_member_rcnt_actvt->set($topic->created);
          $new_member_wrapper->field_fc_forum_member_tpic_count->set($topic->count);
          $new_member_wrapper->field_fc_forum_member_post_count->set(0);
          $new_member_wrapper->field_fc_forum_member_reco_count->set(0);
          $new_member_wrapper->field_fc_forum_member_partip_scr->set(sbac_forum_calculate_participation_score(0, $topic->count, 0));
          $new_member_wrapper->save();

          $current_member_count++;

          // invalidate member list cache when a new user joins.
          if (cache_get($cid)) {
            cache_clear_all($cid, 'cache');
          }
        }
      }
    }

    // Add commenters
    $query = db_select('field_data_field_topic_forum_parent', 'p');
    $query->leftJoin('node', 'n', 'n.nid = p.entity_id');
    $query->leftJoin('comment', 'c', 'c.nid = n.nid');
    $query->leftJoin('users_roles', 'ur', 'ur.uid = c.uid');
    $query->leftJoin('field_data_field_state', 's', 's.entity_id = c.uid AND s.entity_type = \'user\'');
    $query->condition('p.bundle', 'topic')
      ->condition('p.field_topic_forum_parent_tid', $forum_id);
    $query->isNotNull('c.cid');
    $query->groupBy('c.uid');
    $query->fields('c', array('uid', 'created'));
    $query->addExpression("count(DISTINCT c.cid)", 'count');
    $query->addExpression("GROUP_CONCAT(DISTINCT ur.rid)", 'roles');
    $query->addExpression("GROUP_CONCAT(DISTINCT s.field_state_tid)", 'states');
    $comments = $query->execute()->fetchAll();
    foreach ($comments as $comment) {
      if (empty($role_restrictions) || (!empty($role_restrictions) && array_intersect($role_restrictions, explode(',', $comment->roles)))) {
        if (empty($state_restrictions) || (!empty($state_restrictions) && array_intersect($state_restrictions, explode(',', $comment->states)))) {
          if (!sbac_forum__api__check_user_is_forum_member($forum_obj->tid, $comment->uid)) {
            $query = db_select('comment', 'c');
            $query->innerJoin('field_data_field_topic_comment_recommended', 'r', 'r.entity_id = c.cid AND r.entity_type = \'comment\'');
            $query->innerJoin('field_data_field_topic_forum_parent', 'p', 'p.entity_id = c.nid');
            $query->condition('p.field_topic_forum_parent_tid', $forum_id)
              ->condition('c.uid', $comment->uid);
            $recommend_count = $query->fields('c', array('cid'))->countQuery()->execute()->fetchField();

            // add the user to the participant list
            $params = array(
              'field_name' => 'field_fc_forum_members'
            );
            $new_member_item = entity_create('field_collection_item', $params);
            $new_member_item->setHostEntity('taxonomy_term', $forum_obj);
            $new_member_wrapper = entity_metadata_wrapper('field_collection_item', $new_member_item);
            $new_member_wrapper->field_fc_forum_member->set($comment->uid);
            $new_member_wrapper->field_fc_forum_member_joined->set($comment->created);
            $new_member_wrapper->field_fc_forum_member_rcnt_actvt->set($comment->created);
            $new_member_wrapper->field_fc_forum_member_post_count->set($comment->count);
            $new_member_wrapper->field_fc_forum_member_reco_count->set($recommend_count);
            $new_member_wrapper->field_fc_forum_member_tpic_count->set(0);
            $new_member_wrapper->field_fc_forum_member_partip_scr->set(sbac_forum_calculate_participation_score($recommend_count, 0, $comment->count));
            $new_member_wrapper->save();

            if (cache_get($cid)) {
              cache_clear_all($cid, 'cache');
            }

            $current_member_count++;
          }
          else {
            foreach ($forum_wrapper->field_fc_forum_members as $member_wrapper) {
              if ($comment->uid == $member_wrapper->field_fc_forum_member->uid->value()) {
                if ($comment->created < $member_wrapper->field_fc_forum_member_joined->value()) {
                  $member_wrapper->field_fc_forum_member_joined->set($comment->created);
                }
                if ($comment->created > $member_wrapper->field_fc_forum_member_rcnt_actvt->value()) {
                  $member_wrapper->field_fc_forum_member_rcnt_actvt->set($comment->created);
                }
                $member_wrapper->field_fc_forum_member_post_count->set($comment->count);
                $member_wrapper->field_fc_forum_member_reco_count->set($recommend_count);
                $member_wrapper->field_fc_forum_member_partip_scr->set(sbac_forum_calculate_participation_score($recommend_count, $member_wrapper->field_fc_forum_member_tpic_count->value(), $comment->count));
                $member_wrapper->save();
              }
            }
          }
        }
      }
    }

    $forum_wrapper->field_forum_member_count->set($current_member_count);
    $forum_wrapper->save();
  }
}