<?php

/**
 * Implements hook_drush_command()
 */
function sbac_forum_drush_command() {
  $items['sbac-forum-create-resource-forums'] = array(
    'description' => 'Create all resource forums',
  );

  return $items;
}

/**
 * Generate all resource forums
 */
function drush_sbac_forum_create_resource_forums(){
  sbac_forum_create_all_resource_forums();
}