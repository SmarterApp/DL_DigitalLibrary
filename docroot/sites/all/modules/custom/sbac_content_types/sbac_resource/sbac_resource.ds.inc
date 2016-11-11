<?php
/**
 * @file
 * sbac_resource.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function sbac_resource_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resource|search_index';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resource';
  $ds_layout->view_mode = 'search_index';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_file',
        1 => 'field_alignment_tags',
        2 => 'field_alt_body',
        3 => 'field_intended_end_user',
        4 => 'field_digital_media_type',
        5 => 'field_educational_use',
        6 => 'field_subject',
        7 => 'field_license_information',
        8 => 'field_author',
        9 => 'field_smarter_balanced_keyword',
        10 => 'field_publisher',
        11 => 'field_view_permissions',
        12 => 'field_view_permissions_per_state',
        13 => 'field_temp',
        14 => 'field_license',
        15 => 'field_attributes',
        16 => 'field_student_agency',
        17 => 'field_focus',
        18 => 'field_contexts',
        19 => 'field_connection_to_ccss',
        20 => 'field_connection_to_fap',
        21 => 'field_learning_goals',
        22 => 'field_success_criteria',
        23 => 'field_supporting_evidence',
        24 => 'field_principles',
        25 => 'field_grades',
        26 => 'field_intended_student',
        27 => 'field_classroom_technologies',
        28 => 'field_pii',
        29 => 'field_alignment_term',
      ),
    ),
    'fields' => array(
      'field_file' => 'ds_content',
      'field_alignment_tags' => 'ds_content',
      'field_alt_body' => 'ds_content',
      'field_intended_end_user' => 'ds_content',
      'field_digital_media_type' => 'ds_content',
      'field_educational_use' => 'ds_content',
      'field_subject' => 'ds_content',
      'field_license_information' => 'ds_content',
      'field_author' => 'ds_content',
      'field_smarter_balanced_keyword' => 'ds_content',
      'field_publisher' => 'ds_content',
      'field_view_permissions' => 'ds_content',
      'field_view_permissions_per_state' => 'ds_content',
      'field_temp' => 'ds_content',
      'field_license' => 'ds_content',
      'field_attributes' => 'ds_content',
      'field_student_agency' => 'ds_content',
      'field_focus' => 'ds_content',
      'field_contexts' => 'ds_content',
      'field_connection_to_ccss' => 'ds_content',
      'field_connection_to_fap' => 'ds_content',
      'field_learning_goals' => 'ds_content',
      'field_success_criteria' => 'ds_content',
      'field_supporting_evidence' => 'ds_content',
      'field_principles' => 'ds_content',
      'field_grades' => 'ds_content',
      'field_intended_student' => 'ds_content',
      'field_classroom_technologies' => 'ds_content',
      'field_pii' => 'ds_content',
      'field_alignment_term' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
  );
  $export['node|resource|search_index'] = $ds_layout;

  return $export;
}
