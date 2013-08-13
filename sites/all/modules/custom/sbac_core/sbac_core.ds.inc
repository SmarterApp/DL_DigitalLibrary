<?php
/**
 * @file
 * sbac_core.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function sbac_core_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|resource|secondary_teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'resource';
  $ds_fieldsetting->view_mode = 'secondary_teaser';
  $ds_fieldsetting->settings = array(
    'resource_slideshow' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'resource_slideshow',
    ),
  );
  $export['node|resource|secondary_teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function sbac_core_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resource|secondary_teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resource';
  $ds_layout->view_mode = 'secondary_teaser';
  $ds_layout->layout = 'ds_3col_stacked_equal_width';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'resource_slideshow',
      ),
      'right' => array(
        1 => 'field_alignment_tags',
        4 => 'field_educational_use',
        9 => 'field_geographical_settings',
      ),
      'left' => array(
        2 => 'field_intended_end_user',
        5 => 'field_subject',
        7 => 'field_grades',
      ),
      'middle' => array(
        3 => 'field_digital_media_type',
        6 => 'field_smarter_balanced_keyword',
        8 => 'field_intended_student',
      ),
    ),
    'fields' => array(
      'resource_slideshow' => 'header',
      'field_alignment_tags' => 'right',
      'field_intended_end_user' => 'left',
      'field_digital_media_type' => 'middle',
      'field_educational_use' => 'right',
      'field_subject' => 'left',
      'field_smarter_balanced_keyword' => 'middle',
      'field_grades' => 'left',
      'field_intended_student' => 'middle',
      'field_geographical_settings' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'middle' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['node|resource|secondary_teaser'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function sbac_core_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'secondary_teaser';
  $ds_view_mode->label = 'secondary_teaser';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['secondary_teaser'] = $ds_view_mode;

  return $export;
}
