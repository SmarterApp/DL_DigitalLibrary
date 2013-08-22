<?php
/**
 * @file
 * sbac_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function sbac_core_eck_bundle_info() {
  $items = array(
  'feedback_gate_keeper' => array(
  'machine_name' => 'feedback_gate_keeper',
  'entity_type' => 'feedback',
  'name' => 'gate_keeper',
  'label' => 'Gate Keeper',
),
  'feedback_post' => array(
  'machine_name' => 'feedback_post',
  'entity_type' => 'feedback',
  'name' => 'post',
  'label' => 'Post',
),
  'feedback_review' => array(
  'machine_name' => 'feedback_review',
  'entity_type' => 'feedback',
  'name' => 'review',
  'label' => 'Review',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function sbac_core_eck_entity_type_info() {
$items = array(
       'feedback' => array(
  'name' => 'feedback',
  'label' => 'feedback',
  'properties' => array(
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'changed' => array(
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
    'language' => array(
      'label' => 'Entity language',
      'type' => 'language',
      'behavior' => 'language',
    ),
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'status' => array(
      'label' => 'Published',
      'type' => 'integer',
      'behavior' => 'checkbox',
    ),
    'completed' => array(
      'label' => 'Completed',
      'type' => 'integer',
      'behavior' => 'checkbox',
    ),
    'node_id' => array(
      'label' => 'Node ID',
      'type' => 'integer',
      'behavior' => 'textfield',
    ),
    'met_criteria' => array(
      'label' => 'Meets Criteria',
      'type' => 'integer',
      'behavior' => 'checkbox',
    ),
    'current' => array(
      'label' => 'Current',
      'type' => 'integer',
      'behavior' => 'checkbox',
    ),
    'reminder' => array(
      'label' => 'reminder',
      'type' => 'integer',
      'behavior' => 'textfield',
    ),
  ),
),
  );
  return $items;
}
