<?php
/**
 * @file
 * sbac_sne_webform.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_sne_webform_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_webform';
  $strongarm->value = '0';
  $export['comment_webform'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'uuid_features_entity_node';
  $strongarm->value = array(
    'webform' => 'webform',
    'sbac_alerts' => 0,
    'alignment' => 0,
    'collection' => 0,
    'help_page' => 0,
    'panel' => 0,
    'resource' => 0,
    'topic' => 0,
  );
  $export['uuid_features_entity_node'] = $strongarm;

  return $export;
}
