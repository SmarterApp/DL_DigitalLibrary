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
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '368cd0b3-aade-434f-b715-9d36aa01e91e',
    'vocabulary_machine_name' => 'alignment_type',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 207,
  );
  $terms[] = array(
    'name' => 'Requires',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '52a7de03-e7bf-4fc3-857e-c2c3d01ca1bc',
    'vocabulary_machine_name' => 'alignment_type',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 208,
  );
  $terms[] = array(
    'name' => 'Assesses',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '9f97e308-128c-4b2d-8ca0-410b764d79dc',
    'vocabulary_machine_name' => 'alignment_type',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 206,
  );
  $terms[] = array(
    'name' => 'Teaches',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'af5698f4-8d23-4151-a267-c7482e37de83',
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
    'name' => 'Requires',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'bc980753-458d-4726-83ea-eb01b09cb459',
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
  $terms[] = array(
    'name' => 'Assesses',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'c0ab6612-ace2-42b9-83ae-293fc94bbcd1',
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
  return $terms;
}
