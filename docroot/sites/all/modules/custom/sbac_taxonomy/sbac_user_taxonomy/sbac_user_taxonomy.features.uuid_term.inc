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
    'name' => 'Other',
    'description' => '',
    'format' => NULL,
    'weight' => 1,
    'uuid' => '00720fdb-b1e3-4c92-885a-541ac5563297',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 240,
  );
  $terms[] = array(
    'name' => 'School Counselor',
    'description' => '',
    'format' => NULL,
    'weight' => -5,
    'uuid' => '12e7e988-b177-4314-971c-edbc3b5677f1',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 234,
  );
  $terms[] = array(
    'name' => 'Regional Learning Consultant',
    'description' => '',
    'format' => NULL,
    'weight' => -9,
    'uuid' => '24134168-ec96-4bf3-bf96-b3df4066747b',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 230,
  );
  $terms[] = array(
    'name' => 'Instructional Coach',
    'description' => '',
    'format' => NULL,
    'weight' => -3,
    'uuid' => '377d0289-1616-4311-bc72-1b63a239e730',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 236,
  );
  $terms[] = array(
    'name' => 'Instructional Coordinator',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => -2,
    'uuid' => '44f9c2f2-c284-4f65-ac6e-0dca2b02b595',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 237,
  );
  $terms[] = array(
    'name' => 'Librarian / Media Specialist',
    'description' => '',
    'format' => NULL,
    'weight' => -4,
    'uuid' => '551f90d6-c783-4d4d-bcf9-2c8b8586c5e9',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 235,
  );
  $terms[] = array(
    'name' => 'Higher Education Personnel',
    'description' => '',
    'format' => NULL,
    'weight' => -1,
    'uuid' => '5d60db1f-dcf5-4e20-9978-3382d496de75',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 238,
  );
  $terms[] = array(
    'name' => 'District Administrator',
    'description' => '',
    'format' => NULL,
    'weight' => -8,
    'uuid' => '7158821e-558f-42ef-a6d8-8e8c3cce347b',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 231,
  );
  $terms[] = array(
    'name' => 'Student Teacher',
    'description' => '',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '7c1684cb-448a-47d0-990f-75f0b5bf28b6',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 239,
  );
  $terms[] = array(
    'name' => 'Teacher',
    'description' => '',
    'format' => NULL,
    'weight' => -6,
    'uuid' => '81af82f9-8f5a-46aa-a618-c223422cf844',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 233,
  );
  $terms[] = array(
    'name' => 'State Personnel',
    'description' => '',
    'format' => NULL,
    'weight' => -10,
    'uuid' => '83c483fe-17c2-4e89-a69c-a84e958114ce',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 229,
  );
  $terms[] = array(
    'name' => 'Building Administrator',
    'description' => '',
    'format' => NULL,
    'weight' => -7,
    'uuid' => 'f368fc1e-28b6-441e-aacd-88d47757ed81',
    'vocabulary_machine_name' => 'title',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 232,
  );
  return $terms;
}
