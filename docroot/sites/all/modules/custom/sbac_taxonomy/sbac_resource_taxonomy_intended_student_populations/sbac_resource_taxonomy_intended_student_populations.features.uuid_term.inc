<?php
/**
 * @file
 * sbac_resource_taxonomy_intended_student_populations.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_intended_student_populations_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Gifted & Talented (G&T)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => '4919fabd-5f7f-4b95-ac86-d1eb10e968c9',
    'vocabulary_machine_name' => 'intended_student_populations',
  );
  $terms[] = array(
    'name' => 'English Language Learners (ELL)',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '529726b1-8002-4e96-a92d-391552f46a0f',
    'vocabulary_machine_name' => 'intended_student_populations',
  );
  $terms[] = array(
    'name' => 'Students with Disabilities (SWD)',
    'description' => NULL,
    'format' => NULL,
    'weight' => 2,
    'uuid' => '7e1bd734-c49e-4bf0-9567-e158a4f38485',
    'vocabulary_machine_name' => 'intended_student_populations',
  );
  $terms[] = array(
    'name' => 'All Students',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'da9306bd-7659-42a5-aa13-414bbac862cd',
    'vocabulary_machine_name' => 'intended_student_populations',
  );
  return $terms;
}
