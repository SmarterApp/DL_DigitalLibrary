<?php

/**
 * Implements hook_drush_command()
 */
function sbac_forum_drush_command() {
  $items['sbac-forum-create-resource-forums'] = array(
    'description' => 'Create all resource forums',
  );
  $items['sbac-forum-update-topic-author'] = array(
    'description'=>'Set the default Resource Forum topic author to the Resource author'
  );

  return $items;
}

/**
 * Generate all resource forums
 */
function drush_sbac_forum_create_resource_forums(){
  sbac_forum_create_all_resource_forums();
}

function drush_sbac_forum_update_topic_author() {
  sbac_forum_update_resource_forum_topic_authors();
}