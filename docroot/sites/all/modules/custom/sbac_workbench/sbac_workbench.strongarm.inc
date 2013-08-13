<?php
/**
 * @file
 * sbac_workbench.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_workbench_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_moderation_default_state_alignment';
  $strongarm->value = 'creation';
  $export['workbench_moderation_default_state_alignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_moderation_default_state_resource';
  $strongarm->value = 'creation';
  $export['workbench_moderation_default_state_resource'] = $strongarm;

  return $export;
}
