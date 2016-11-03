<?php
/**
 * @file
 * sbac_resource_taxonomy_formative_assesment.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_formative_assesment_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Elicit Evidence',
    'description' => NULL,
    'format' => NULL,
    'weight' => -9,
    'uuid' => '54d50ecc-471b-4a42-b52c-a60587b5a546',
    'vocabulary_machine_name' => 'attributes',
  );
  $terms[] = array(
    'name' => 'Interpret Evidence',
    'description' => NULL,
    'format' => NULL,
    'weight' => -8,
    'uuid' => 'c366ce1d-c364-42f5-bfaa-c4864cdbc79c',
    'vocabulary_machine_name' => 'attributes',
  );
  $terms[] = array(
    'name' => 'Act on Evidence',
    'description' => NULL,
    'format' => NULL,
    'weight' => -7,
    'uuid' => 'ccd587a4-1e1c-4446-9702-8c1c5beccb50',
    'vocabulary_machine_name' => 'attributes',
  );
  $terms[] = array(
    'name' => 'Clarify Intended Learning',
    'description' => NULL,
    'format' => NULL,
    'weight' => -10,
    'uuid' => 'cf1e2447-6bc2-4f05-90c8-8d54442ea861',
    'vocabulary_machine_name' => 'attributes',
  );
  return $terms;
}
