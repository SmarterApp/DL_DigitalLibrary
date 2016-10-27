<?php
/**
 * @file
 * sbac_resource_taxonomy_geographic_settings.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_geographic_settings_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Urban',
    'description' => NULL,
    'format' => NULL,
    'weight' => -10,
    'uuid' => '1d58e782-932e-44bf-bc78-69225bd1d3f0',
    'vocabulary_machine_name' => 'geographical_settings',
  );
  $terms[] = array(
    'name' => 'Suburban',
    'description' => NULL,
    'format' => NULL,
    'weight' => -9,
    'uuid' => '6872b88b-68b8-4628-ac7b-e4db2f299042',
    'vocabulary_machine_name' => 'geographical_settings',
  );
  $terms[] = array(
    'name' => 'Rural',
    'description' => NULL,
    'format' => NULL,
    'weight' => -8,
    'uuid' => 'c1c5b63d-c153-46a5-bec8-23a9279806ea',
    'vocabulary_machine_name' => 'geographical_settings',
  );
  return $terms;
}
