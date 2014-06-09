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