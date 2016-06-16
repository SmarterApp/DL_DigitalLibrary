<?php
/**
 * @file
 * sbac_alignment_taxonomy_sbac_alignment.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_alignment_taxonomy_sbac_alignment_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Teaches',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '4fa402a1-f901-419d-963a-a352ee2e117d',
    'vocabulary_machine_name' => 'sbac_alignment',
    'field_sbacdrupaluid' => array(),
    'field_sbacgrade' => array(),
    'field_sbackey' => array(),
    'field_sbacparent' => array(),
    'field_sbacpublication' => array(),
    'field_sbacshortname' => array(),
    'field_sbactreelevel' => array(),
  );
  $terms[] = array(
    'name' => 'Assesses',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'ba7ad77f-573a-466e-bc26-334a01bb3343',
    'vocabulary_machine_name' => 'sbac_alignment',
    'field_sbacdrupaluid' => array(),
    'field_sbacgrade' => array(),
    'field_sbackey' => array(),
    'field_sbacparent' => array(),
    'field_sbacpublication' => array(),
    'field_sbacshortname' => array(),
    'field_sbactreelevel' => array(),
  );
  $terms[] = array(
    'name' => 'Requires',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'c3f91ed6-6a6c-4ae8-985c-b5883b4bd322',
    'vocabulary_machine_name' => 'sbac_alignment',
    'field_sbacdrupaluid' => array(),
    'field_sbacgrade' => array(),
    'field_sbackey' => array(),
    'field_sbacparent' => array(),
    'field_sbacpublication' => array(),
    'field_sbacshortname' => array(),
    'field_sbactreelevel' => array(),
  );
  return $terms;
}
