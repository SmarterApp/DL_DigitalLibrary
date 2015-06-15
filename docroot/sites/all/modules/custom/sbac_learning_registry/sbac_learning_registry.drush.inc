<?php

/**
 * Implements hook_drush_command()
 */
function sbac_learning_registry_drush_command() {
  $items['sbac-learning-registry-queue-all-resources'] = array(
    'description' => 'Queue all resources for sending to LR',
  );

  return $items;
}

function drush_sbac_learning_registry_queue_all_resources(){
  sbac_learning_registry_queue_all_resources();
}