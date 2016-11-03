<?php
/**
 * @file
 * sbac_flag_taxonomy_resource_flags.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_flag_taxonomy_resource_flags_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Resource is not available free of charge',
    'description' => '',
    'format' => 'full_html',
    'weight' => 11,
    'uuid' => '0428213d-b192-4e44-95ac-b726d445c586',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Unintelligible / not viewable / technology does not function properly',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => '216cd3f7-2a9e-40e7-bb1e-5a92f5c51662',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Does not support the formative assessment process',
    'description' => NULL,
    'format' => NULL,
    'weight' => 10,
    'uuid' => '3aa9d41d-37c8-4faa-9d7f-fd81ec5517cd',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Contains personally identifiable information (PII)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 6,
    'uuid' => '524f59a7-477a-408b-b95c-410ee601eb75',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Summary information does not match the resource',
    'description' => '',
    'format' => 'full_html',
    'weight' => 7,
    'uuid' => '735ddaec-7253-4fdb-b0f3-bd1f55809e3c',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Duplicate',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '793a2de6-2325-4289-87ba-bd7eec2bd14d',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Biased, objectionable, or culturally insensitive material (e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => '799a79b3-caba-4f92-ae8d-ac662d77d4f7',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'May be in violation of intellectual property rights (i.e., copyright infringement)',
    'description' => '',
    'format' => 'full_html',
    'weight' => 8,
    'uuid' => 'b047e143-ab44-4854-8d40-8f9f56284c9e',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Inaccurate / misleading',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => 'b72d7537-11c7-4ecc-855d-5437e53cdfc6',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Outdated',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'bbd88910-0a0b-4683-b850-29b3b6ceed4b',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Accessibility or accommodation issues',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => 'd4fa0f0e-9841-432e-9953-72880af3fec7',
    'vocabulary_machine_name' => 'resource_flags',
  );
  $terms[] = array(
    'name' => 'Does not support implementation of Common Core State Standards',
    'description' => '',
    'format' => 'full_html',
    'weight' => 9,
    'uuid' => 'f1db8cfa-5dad-42db-8c98-25e9cfd056eb',
    'vocabulary_machine_name' => 'resource_flags',
  );
  return $terms;
}
