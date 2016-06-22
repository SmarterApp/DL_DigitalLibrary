<?php
/**
 * @file
 * sbac_alignment_taxonomy_alignment_type.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_alignment_taxonomy_alignment_type_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Teaches',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => '5f2535c4-4c49-442e-b760-60a7f7f748a8',
    'vocabulary_machine_name' => 'alignment_type',
  );
  $terms[] = array(
    'name' => 'Requires',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'bb62677c-9bc6-4a4f-95f3-7aa4e4099d49',
    'vocabulary_machine_name' => 'alignment_type',
  );
  $terms[] = array(
    'name' => 'Assesses',
    'description' => 'lorem ipsum',
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'bddc7072-5947-47e1-9719-a6ceafbf2f65',
    'vocabulary_machine_name' => 'alignment_type',
  );
  return $terms;
}
