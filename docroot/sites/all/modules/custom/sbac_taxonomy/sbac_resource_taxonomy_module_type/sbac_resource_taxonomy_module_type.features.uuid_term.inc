<?php
/**
 * @file
 * sbac_resource_taxonomy_module_type.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_module_type_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Assessment Literacy',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '403c35f1-8cd8-4180-ba55-999d5a2d7a41',
    'vocabulary_machine_name' => 'smarter_balanced_keyword',
  );
  $terms[] = array(
    'name' => 'Mathematics Instructional',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => '8637bac3-933f-4113-a72c-5763510982a3',
    'vocabulary_machine_name' => 'smarter_balanced_keyword',
  );
  $terms[] = array(
    'name' => 'ELA  Instructional',
    'description' => '',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => 'd622dc04-86a6-4e35-84b6-c531a3ca3743',
    'vocabulary_machine_name' => 'smarter_balanced_keyword',
  );
  $terms[] = array(
    'name' => 'Score Report',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => 'e018a81c-96ab-4a35-bb88-4a9f58152fb6',
    'vocabulary_machine_name' => 'smarter_balanced_keyword',
  );
  return $terms;
}
