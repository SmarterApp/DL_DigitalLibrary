<?php
/**
 * @file
 * sbac_resource_taxonomy_media_types.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_media_types_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Document',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => '0046cf2c-db38-4268-a6ef-1ce52e1617f4',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  $terms[] = array(
    'name' => 'Presentation',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '1028094a-3661-4b29-9c53-e6ce3e9f53da',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  $terms[] = array(
    'name' => 'Spreadsheet',
    'description' => '',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => '226730a5-beaf-4ec9-809f-039a52311bdb',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  $terms[] = array(
    'name' => 'Video',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '60932ff2-34a3-4314-9298-47621ba48326',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  $terms[] = array(
    'name' => 'Image',
    'description' => '',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => '8308f183-f16e-4100-8521-fc0a943ec349',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  $terms[] = array(
    'name' => 'Interactive',
    'description' => '',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => 'a6238bfc-2ae8-4517-a3ac-347740da0238',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  $terms[] = array(
    'name' => 'Audio',
    'description' => 'Description of audio.',
    'format' => 'plain_text',
    'weight' => 6,
    'uuid' => 'debcd71f-acc3-4fd4-9968-d40805429502',
    'vocabulary_machine_name' => 'digital_media_type',
  );
  return $terms;
}
