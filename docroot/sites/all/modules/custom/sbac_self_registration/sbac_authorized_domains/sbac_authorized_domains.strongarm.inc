<?php
/**
 * @file
 * sbac_authorized_domains.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_authorized_domains_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_districts_pattern';
  $strongarm->value = '';
  $export['pathauto_taxonomy_term_districts_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_states_pattern';
  $strongarm->value = '';
  $export['pathauto_taxonomy_term_states_pattern'] = $strongarm;

  return $export;
}
