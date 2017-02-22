<?php
/**
 * @file
 * sbac_resource_taxonomy_educational_use.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_educational_use_uuid_features_default_terms() {
  $terms = array();
  $terms[] = array(
    'name' => 'Unit',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '041f1dcf-6722-48de-a15a-886ef9612535',
    'vocabulary_machine_name' => 'educational_use',
  );
  $terms[] = array(
    'name' => 'Lesson',
    'description' => '',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => '9903c669-3729-461b-8b02-ae001b5b7837',
    'vocabulary_machine_name' => 'educational_use',
  );
  $terms[] = array(
    'name' => 'Classroom Activity/Assignment',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => '4182a7de-03a3-40a5-b256-00857c606768',
    'vocabulary_machine_name' => 'educational_use',
  );
  $terms[] = array(
    'name' => 'Tool (i.e., rubric, observation protocol, organizational tool, etc.)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => 'a5d86157-a3de-4cb1-8597-2d79f22cc926',
    'vocabulary_machine_name' => 'educational_use',
  );
  $terms[] = array(
    'name' => 'Assessment (i.e., quiz, test, exit ticket, etc.)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '1850a66a-d52e-463e-b15c-2eb156318d23',
    'vocabulary_machine_name' => 'educational_use',
  );
  $terms[] = array(
    'name' => 'Other',
    'description' => '',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => 'f4ffc135-a1a0-4799-b3bd-d85aa042febc',
    'vocabulary_machine_name' => 'educational_use',
  );
  return $terms;
}
