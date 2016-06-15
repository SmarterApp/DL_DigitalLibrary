<?php
/**
 * @file
 * sbac_alignment_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_alignment_taxonomy_uuid_features_default_terms() {
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
    'entity_type' => 'taxonomy_term',
    'entity_id' => 251,
  );
  $terms[] = array(
    'name' => 'Teaches',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '5f2535c4-4c49-442e-b760-60a7f7f748a8',
    'vocabulary_machine_name' => 'alignment_type',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 207,
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
    'entity_type' => 'taxonomy_term',
    'entity_id' => 249,
  );
  $terms[] = array(
    'name' => 'Requires',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'bb62677c-9bc6-4a4f-95f3-7aa4e4099d49',
    'vocabulary_machine_name' => 'alignment_type',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 208,
  );
  $terms[] = array(
    'name' => 'Assesses',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'bddc7072-5947-47e1-9719-a6ceafbf2f65',
    'vocabulary_machine_name' => 'alignment_type',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 206,
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
    'entity_type' => 'taxonomy_term',
    'entity_id' => 250,
  );
  return $terms;
}
