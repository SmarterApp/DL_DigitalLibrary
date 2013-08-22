<?php
/**
 * @file
 * sbac_report.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_report_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'contextual_range_filter_date_field_names';
  $strongarm->value = array(
    'node:created_fulldate' => 'node:created_fulldate',
    'eck_feedback:created' => 'eck_feedback:created',
  );
  $export['contextual_range_filter_date_field_names'] = $strongarm;

  return $export;
}
