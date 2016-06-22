<?php
/**
 * @file
 * sbac_help_taxonomy_help_page_topic.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_help_taxonomy_help_page_topic_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Resource Tutorial',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '2407c029-d611-4c3b-b747-df3b75f15cfe',
    'vocabulary_machine_name' => 'help_page_topic',
  );
  $terms[] = array(
    'name' => 'Help Desk Contacts',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'c8258e82-5be1-44da-a528-755759632a5e',
    'vocabulary_machine_name' => 'help_page_topic',
  );
  $terms[] = array(
    'name' => 'Welcome Tutorial',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'f7dda56b-db13-4e35-9144-e6523f5825d2',
    'vocabulary_machine_name' => 'help_page_topic',
  );
  return $terms;
}
