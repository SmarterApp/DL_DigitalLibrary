<?php
/**
 * @file
 * sbac_resource_taxonomy_age_range.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_age_range_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => '0 - 3',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '03afa4e8-bb2d-4f57-b007-ffa7e55bcd25',
    'vocabulary_machine_name' => 'age_range',
  );
  $terms[] = array(
    'name' => '4 - 6',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '8683b65e-2a75-423b-9bf7-b871a95affa2',
    'vocabulary_machine_name' => 'age_range',
  );
  $terms[] = array(
    'name' => '7 - 10',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'e74c8fcd-89c5-47b1-9ff8-9684985fe861',
    'vocabulary_machine_name' => 'age_range',
  );
  return $terms;
}
