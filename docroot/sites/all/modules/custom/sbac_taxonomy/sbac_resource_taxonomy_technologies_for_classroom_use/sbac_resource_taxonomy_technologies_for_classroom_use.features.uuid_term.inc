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
    'uuid' => '11162ed8-a2a2-451a-abb9-3f401435fc45',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Smartphone',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '4e5cdee9-27e5-4b68-93a1-801120cc30ca',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Tablets/Computers for Teacher',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '4faed31e-d9db-4abe-8754-6f9e19b80d05',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Tablets/Computers for Students',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '6a426c77-b65c-4881-be85-a58cd2fbcf4f',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Document Camera',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '854de586-080c-439e-ab30-7a4fd024226f',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Video Camera',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '9360d588-2deb-4ee0-874c-978038a9c6a0',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'LCD Projector',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '9cf07358-a10e-47ff-8f67-a0106a2b6cc7',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Clickers',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '9f4e4206-fa63-41e7-b843-21eb6329e608',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Internet',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'a63b5124-c605-4d87-8ed9-860d7e500a2d',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Interactive White Board',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => 'c798c07d-b637-4cb1-a493-a0342af7f641',
    'vocabulary_machine_name' => 'technologies_for_classroom_use',
  );
  $terms[] = array(
    'name' => 'Still Camera',
    'description' => NULL,
    'format' => NULL,
    'weight' => 2,
    'uuid' => 'fa0c22d8-3817-465e-afaa-ae65e5a68989',
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
