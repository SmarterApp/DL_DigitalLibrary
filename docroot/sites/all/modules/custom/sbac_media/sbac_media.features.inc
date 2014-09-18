<?php
/**
 * @file
 * sbac_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function sbac_media_eck_bundle_info() {
  $items = array(
  'media_media' => array(
  'machine_name' => 'media_media',
  'entity_type' => 'media',
  'name' => 'media',
  'label' => 'media',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function sbac_media_eck_entity_type_info() {
$items = array(
       'media' => array(
  'name' => 'media',
  'label' => 'media',
  'properties' => array(
    'fid' => array(
      'label' => 'File ID',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'filename' => array(
      'label' => 'File Name',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'file_hash' => array(
      'label' => 'File Hash',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'file_size' => array(
      'label' => 'File Size',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'nid' => array(
      'label' => 'Node ID',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'weight' => array(
      'label' => 'Weight',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'document_id' => array(
      'label' => 'Document ID',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'embed_url' => array(
      'label' => 'Embed URL',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'transcript' => array(
      'label' => 'transcript',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'status' => array(
      'label' => 'Status',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
  ),
),
  );
  return $items;
}
