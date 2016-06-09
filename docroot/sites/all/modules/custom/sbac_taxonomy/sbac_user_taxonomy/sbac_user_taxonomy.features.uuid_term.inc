<?php
/**
 * @file
 * sbac_user_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_user_taxonomy_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Regional Learning Consultant',
    'description' => '',
    'format' => NULL,
    'weight' => -9,
    'uuid' => '1fa956da-0d2e-4630-ba8d-20bfd922a63a',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 230,
  );
  $terms[] = array(
    'name' => 'Other',
    'description' => '',
    'format' => NULL,
    'weight' => 1,
    'uuid' => '3ff01c9b-0b09-41fd-9dd6-9178b0fd8951',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 240,
  );
  $terms[] = array(
    'name' => 'Student Teacher',
    'description' => '',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '4d59a19f-4047-4aea-859e-0c0483eb90b8',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 239,
  );
  $terms[] = array(
    'name' => 'School Counselor',
    'description' => '',
    'format' => NULL,
    'weight' => -5,
    'uuid' => '6dfa8a1f-3fd4-470d-bc41-1846d8c66a20',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 234,
  );
  $terms[] = array(
    'name' => 'Librarian / Media Specialist',
    'description' => '',
    'format' => NULL,
    'weight' => -4,
    'uuid' => '8937a6c5-6044-4e5b-8b20-e2ab1cf2b1c2',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 235,
  );
  $terms[] = array(
    'name' => 'Higher Education Personnel',
    'description' => '',
    'format' => NULL,
    'weight' => -1,
    'uuid' => '9b314880-07c5-48fa-8156-002048ee2913',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 238,
  );
  $terms[] = array(
    'name' => 'District Administrator',
    'description' => '',
    'format' => NULL,
    'weight' => -8,
    'uuid' => 'bc556639-9ee4-4173-8aab-fc15a709a696',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 231,
  );
  $terms[] = array(
    'name' => 'Instructional Coach',
    'description' => '',
    'format' => NULL,
    'weight' => -3,
    'uuid' => 'cb98277e-b926-4030-ba8e-8ed62d4b8aea',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 236,
  );
  $terms[] = array(
    'name' => 'Building Administrator',
    'description' => '',
    'format' => NULL,
    'weight' => -7,
    'uuid' => 'd3daec4f-4940-4033-bcd0-a51b79201107',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 232,
  );
  $terms[] = array(
    'name' => 'State Personnel',
    'description' => '',
    'format' => NULL,
    'weight' => -10,
    'uuid' => 'e4e55cde-6d69-47b0-af2c-86171170e770',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 229,
  );
  $terms[] = array(
    'name' => 'Instructional Coordinator',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => -2,
    'uuid' => 'eba9d5af-7578-4243-a90e-cdd8ad1e392d',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 237,
  );
  $terms[] = array(
    'name' => 'Teacher',
    'description' => '',
    'format' => NULL,
    'weight' => -6,
    'uuid' => 'fd8c66db-f6fb-4fb6-8ba1-7580f1af6eaf',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 233,
  );
  return $terms;
}
