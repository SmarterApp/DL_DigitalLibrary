<?php
/**
 * @file
 * sbac_resource_taxonomy_technologies_for_classroom_use.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_technologies_for_classroom_use_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Calculator',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'ec9715cf-76b1-4987-b42b-a1f37d390845',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Smartphone',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '3bafdefd-723f-426a-b830-7af013bb98db',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Tablets/Computers for Teacher',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'c6c3c676-4e31-4a3f-a791-5a8be10628e0',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Tablets/Computers for Students',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '76c498f4-2b28-4f69-9d7d-7056f5cff58b',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Document Camera',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '7db12b2c-7c9e-4cc4-bce7-9eca943a3ebd',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Video Camera',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => 'e6d3602c-2fec-44bc-b5cf-b309642d65b1',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'LCD Projector',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '3bfff820-e75c-4f25-85c7-7e80c79346b2',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Clickers',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'fbb67700-4a3a-4765-b8e1-071430323ca1',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Internet',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'ea38516a-26e5-4040-b247-64f7edb3bded',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Interactive White Board',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => '329720af-b232-4cb8-bd28-b22f889f550b',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Still Camera',
    'description' => NULL,
    'format' => NULL,
    'weight' => 2,
    'uuid' => 'aeef5908-1f2e-4f43-b82b-620ea0ad52ca',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'None',
    'description' => NULL,
    'format' => NULL,
    'weight' => 11,
    'uuid' => '9cbac353-c0b3-422d-b12a-df2b111fc97c',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  return $terms;
}
