<?php
/**
 * @file
 * sbac_core_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_core_taxonomy_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'High School',
    'description' => NULL,
    'format' => NULL,
    'weight' => 6,
    'uuid' => '14b5056a-8e44-4b85-8dca-5188358a10e4',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34701,
  );
  $terms[] = array(
    'name' => 'High Quality Professional Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => 2,
    'uuid' => '1ea859b2-867e-4691-afa1-249e905afa44',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34681,
  );
  $terms[] = array(
    'name' => 'Students to Use During Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => 4,
    'uuid' => '1f79013a-6044-43ba-854c-e0f1e597b187',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34691,
  );
  $terms[] = array(
    'name' => 'Educators to Use During Instruction',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '229db359-fb4c-41ac-8bda-52340205f88a',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34676,
  );
  $terms[] = array(
    'name' => 'Middle School',
    'description' => NULL,
    'format' => NULL,
    'weight' => 3,
    'uuid' => '305400ba-8375-4ec2-a348-950095c47c07',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34686,
  );
  $terms[] = array(
    'name' => 'Collaborative Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => 5,
    'uuid' => 'b30bbc7f-8978-4416-9743-52116ba47a93',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34696,
  );
  $terms[] = array(
    'name' => 'Use with Families',
    'description' => NULL,
    'format' => NULL,
    'weight' => 7,
    'uuid' => 'd3f13d7a-75d7-49c3-9926-190a14e696f4',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34706,
  );
  $terms[] = array(
    'name' => 'Elementary School',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'f9e40e68-5599-4e64-920e-7d5ba8247d85',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34671,
  );
  return $terms;
}
