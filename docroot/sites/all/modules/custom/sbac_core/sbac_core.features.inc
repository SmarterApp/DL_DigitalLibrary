<?php
/**
 * @file
 * sbac_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
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
  'feedback_qc' => array(
  'machine_name' => 'feedback_qc',
  'entity_type' => 'feedback',
  'name' => 'qc',
  'label' => 'Quality Criteria Review',
),
  'flag_review_end_use' => array(
  'machine_name' => 'flag_review_end_use',
  'entity_type' => 'flag',
  'name' => 'review_end_use',
  'label' => 'Review End Use',
),
  'review_end_use' => array(
  'machine_name' => 'review_end_use',
  'entity_type' => 'review',
  'name' => 'end_use',
  'label' => 'End Use',
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
  'label' => 'Feedback',
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
       'flag' => array(
  'name' => 'flag',
  'label' => 'Flag',
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
    'target_type' => array(
      'label' => 'Target Type',
      'type' => 'text',
      'behavior' => 'textfield',
    ),
    'target_id' => array(
      'label' => 'Target ID',
      'type' => 'integer',
      'behavior' => 'textfield',
    ),
  ),
),
       'review' => array(
  'name' => 'review',
  'label' => 'Review',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
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
    'status' => array(
      'label' => 'Status',
      'type' => 'integer',
      'behavior' => 'checkbox',
    ),
    'node_id' => array(
      'label' => 'Node id',
      'type' => 'integer',
      'behavior' => 'textfield',
    ),
  ),
),
  );
  return $items;
}
