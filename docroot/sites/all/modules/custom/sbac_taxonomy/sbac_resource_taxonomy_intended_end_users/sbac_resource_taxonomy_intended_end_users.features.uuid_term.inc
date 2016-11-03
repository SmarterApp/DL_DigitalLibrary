<?php
/**
 * @file
 * sbac_resource_taxonomy_intended_end_users.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_intended_end_users_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Professional Learning Community',
    'description' => '',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => '5ca0cc02-5809-49be-bcde-6cb084e3dd6a',
    'vocabulary_machine_name' => 'intended_end_user',
  );
  $terms[] = array(
    'name' => 'Student',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => '622d64b8-7260-4530-9cbd-51426704df10',
    'vocabulary_machine_name' => 'intended_end_user',
  );
  $terms[] = array(
    'name' => 'Coach/Coordinator',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '670868a1-1e20-4835-a4ee-4f0c66ee7001',
    'vocabulary_machine_name' => 'intended_end_user',
  );
  $terms[] = array(
    'name' => 'Parent',
    'description' => '',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => '856dfe3f-3964-441a-8c1d-73bb264b9330',
    'vocabulary_machine_name' => 'intended_end_user',
  );
  $terms[] = array(
    'name' => 'Administrator',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'bb7ed03c-34be-4807-81d8-d88840a09d3d',
    'vocabulary_machine_name' => 'intended_end_user',
  );
  $terms[] = array(
    'name' => 'Teacher',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => 'e31d398e-1c22-4dff-bbd1-e8e22a17d4ca',
    'vocabulary_machine_name' => 'intended_end_user',
  );
  return $terms;
}
