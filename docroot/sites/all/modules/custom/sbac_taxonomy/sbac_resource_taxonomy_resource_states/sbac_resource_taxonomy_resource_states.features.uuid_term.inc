<?php
/**
 * @file
 * sbac_resource_taxonomy_resource_states.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_resource_states_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Draft',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '002aceec-d76c-4a62-b830-52ad6dc8b508',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Needs Review',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '01757b30-c6e0-41c3-954a-7744ef461a38',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Returned',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '880149f3-4147-44b4-95e1-2b48ea6ab68c',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Submitted',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '9a1f93ff-2ac6-4258-b361-a36abd748f85',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Being Reviewed',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'b8b2ce3e-fd22-47a7-bb2e-87e950466e8e',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Needs Arbitration',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd1a24694-7b02-451c-904c-612ae0e58ba4',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'In Review',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd51b017d-ee0e-42e8-ae12-d96b65c21a4a',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Removed',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'ee4c82ae-11fd-44ec-8175-608261535c58',
    'vocabulary_machine_name' => 'resource_states',
  );
  $terms[] = array(
    'name' => 'Posted',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'fb7728b1-6d3f-4ed9-831c-4621aabb8615',
    'vocabulary_machine_name' => 'resource_states',
  );
  return $terms;
}
