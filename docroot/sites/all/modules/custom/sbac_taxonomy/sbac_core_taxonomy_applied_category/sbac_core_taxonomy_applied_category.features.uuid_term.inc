<?php
/**
 * @file
 * sbac_core_taxonomy_applied_category.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_core_taxonomy_applied_category_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Collaborative Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => 5,
    'uuid' => '2acf6ccc-d214-4968-ba0e-f1c4f1fc769b',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34696,
  );
  $terms[] = array(
    'name' => 'Elementary School',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '2f949b5c-d357-4546-85fa-6b5f36f7c398',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34671,
  );
  $terms[] = array(
    'name' => 'Middle School',
    'description' => NULL,
    'format' => NULL,
    'weight' => 3,
    'uuid' => '421119b6-49a6-4b0c-b2d8-2d3e3a8b0d96',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34686,
  );
  $terms[] = array(
    'name' => 'Students to Use During Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => 4,
    'uuid' => '619d8fd7-8312-4487-afff-135eb686656c',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34691,
  );
  $terms[] = array(
    'name' => 'High Quality Professional Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => 2,
    'uuid' => 'bdeb3fa4-fd57-4da3-b692-6e23a7c58791',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34681,
  );
  $terms[] = array(
    'name' => 'High School',
    'description' => NULL,
    'format' => NULL,
    'weight' => 6,
    'uuid' => 'ed46a60d-47b3-4aa1-9c6f-61eb0f22877a',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34701,
  );
  $terms[] = array(
    'name' => 'Educators to Use During Instruction',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => 'eef7962f-42a7-4b78-b00f-8a558f177752',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34676,
  );
  $terms[] = array(
    'name' => 'Use with Families',
    'description' => NULL,
    'format' => NULL,
    'weight' => 7,
    'uuid' => 'f2d2891f-0969-48b8-92d1-340642ac483f',
    'vocabulary_machine_name' => 'applied_category',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 34706,
  );
  return $terms;
}
