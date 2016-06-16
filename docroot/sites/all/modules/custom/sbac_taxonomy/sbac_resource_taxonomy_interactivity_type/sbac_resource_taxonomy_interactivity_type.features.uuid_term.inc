<?php
/**
 * @file
 * sbac_resource_taxonomy_interactivity_type.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_interactivity_type_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Mixed',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '1872fd96-e1d7-4bd4-a09d-9ccd5fb99796',
    'vocabulary_machine_name' => 'interactivity_type',
  );
  $terms[] = array(
    'name' => 'Active',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '3c7fcdb6-3b8e-4a69-adc1-a243b4839067',
    'vocabulary_machine_name' => 'interactivity_type',
  );
  $terms[] = array(
    'name' => 'Expositive',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '758e4b4f-2739-4009-84a1-b13dfbb44647',
    'vocabulary_machine_name' => 'interactivity_type',
  );
  return $terms;
}
