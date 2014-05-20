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
  $items['sbac-forum-update-topic-author'] = array(
    'description' => 'Set the Resource Contributor as the Resource Forum Topic author'
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
    sbac_forum_create_resource_forum($nid, $vocab->vid);
  }
}

/**
 * Set the Resource Contributor as the Resource Forum Topic author
 */
function drush_sbac_forum_update_topic_author() {
  $query = "
    SELECT
      topic.nid,
      resource.uid
    FROM {node} topic
      LEFT JOIN {field_data_field_topic_forum_parent} forum
        ON topic.nid = forum.entity_id
      LEFT JOIN {field_data_field_forum_resource_ref} ref
        ON ref.entity_id = forum.field_topic_forum_parent_tid
      LEFT JOIN {node} resource
        ON ref.field_forum_resource_ref_target_id = resource.nid
    WHERE (topic.title = 'Use and Implementation'
           OR topic.title = 'Suggested Improvements')
          AND topic.uid = 1";
  $results = db_query($query);
  foreach ($results as $result) {
    $node = node_load($result->nid);
    if ($node) {
      $node->uid = $result->uid;
      node_save($node);
    }
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
    $topics_query = "
      SELECT
        n.nid
      FROM {node} n
        LEFT JOIN {field_data_field_topic_forum_parent} parent
          ON parent.entity_id = n.nid
        LEFT JOIN {field_data_field_topic_default} topic_default
          ON topic_default.entity_id = n.nid
      WHERE parent.field_topic_forum_parent_tid = :tid
            AND topic_default.field_topic_default_value = 1";
    $topics = db_query($topics_query, array(
      ':tid' => $tid,
    ))->fetchCol();
    node_delete_multiple($topics);
    taxonomy_term_delete($tid);
  }
}