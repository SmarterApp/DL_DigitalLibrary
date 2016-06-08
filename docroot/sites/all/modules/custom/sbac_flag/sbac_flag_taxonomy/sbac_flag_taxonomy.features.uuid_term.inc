<?php
/**
 * @file
 * sbac_flag_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_flag_taxonomy_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Unintelligible / not viewable / technology does not function properly',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => '0d51e1c1-0312-4d25-994d-99f78ee3473a',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60371,
  );
  $terms[] = array(
    'name' => 'Does not support the formative assessment process',
    'description' => NULL,
    'format' => NULL,
    'weight' => 10,
    'uuid' => '21d84add-76b0-41e0-91ae-2e6925df62c4',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 70416,
  );
  $terms[] = array(
    'name' => 'Does not support implementation of Common Core State Standards',
    'description' => '',
    'format' => 'full_html',
    'weight' => 9,
    'uuid' => '2f4ccf8b-8a29-4575-9f33-1c5de90fd660',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60401,
  );
  $terms[] = array(
    'name' => 'Summary information does not match the resource',
    'description' => '',
    'format' => 'full_html',
    'weight' => 7,
    'uuid' => '31e16336-9c26-4de4-973d-ddadc7f6d26b',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60391,
  );
  $terms[] = array(
    'name' => 'May be in violation of intellectual property rights (i.e., copyright infringement)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 8,
    'uuid' => '3e7a1ae5-211a-43e7-b12c-f622f2d29cd0',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60396,
  );
  $terms[] = array(
    'name' => 'Accessibility or accommodation issues',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '63f37720-86b7-4b55-89c6-231068be0e90',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60376,
  );
  $terms[] = array(
    'name' => 'Duplicate',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '6b0451bf-fa62-4e99-9e70-a80aca0d97b1',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 70421,
  );
  $terms[] = array(
    'name' => 'Resource is not available free of charge',
    'description' => '',
    'format' => 'full_html',
    'weight' => 11,
    'uuid' => '8588b9c2-3739-480c-ac18-3baf70b9f2da',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60406,
  );
  $terms[] = array(
    'name' => 'Contains personally identifiable information (PII)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 6,
    'uuid' => 'b48ebd62-a70e-4290-a1db-2bdbb5ebe5ed',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60386,
  );
  $terms[] = array(
    'name' => 'Outdated',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'c8d40bf2-b8af-41fe-b1c8-b21c09819adb',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60361,
  );
  $terms[] = array(
    'name' => 'Inaccurate / misleading',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => 'd8e94930-d7a2-4114-9f23-a18ced3dd478',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60366,
  );
  $terms[] = array(
    'name' => 'Biased, objectionable, or culturally insensitive material (e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => 'e8ba643d-4d2d-4e7d-87a4-6be5c66c961c',
    'vocabulary_machine_name' => 'resource_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60381,
  );
  return $terms;
}
