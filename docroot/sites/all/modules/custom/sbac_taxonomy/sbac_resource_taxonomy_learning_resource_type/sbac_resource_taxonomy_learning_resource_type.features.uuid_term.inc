<?php
/**
 * @file
 * sbac_resource_taxonomy_learning_resource_type.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_learning_resource_type_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Learning Task',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '5aa4a247-084d-432f-8579-181657829d92',
    'vocabulary_machine_name' => 'learning_resource_type',
  );
  $terms[] = array(
    'name' => 'Lesson',
    'description' => '',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => '78448e0f-ac6e-4e12-a9af-069e3932720e',
    'vocabulary_machine_name' => 'learning_resource_type',
  );
  $terms[] = array(
    'name' => 'Interm/Summative Assessment',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => 'de66a56c-6e11-4310-bc47-120e7fa88575',
    'vocabulary_machine_name' => 'learning_resource_type',
  );
  return $terms;
}
