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
