<?php
/**
 * @file
 * sbac_alignment.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function sbac_alignment_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|education_alignment|default';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'education_alignment';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|education_alignment|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|education_alignment|tooltip';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'education_alignment';
  $ds_fieldsetting->view_mode = 'tooltip';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => '',
        'class' => '',
      ),
    ),
  );
  $export['taxonomy_term|education_alignment|tooltip'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function sbac_alignment_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|education_alignment|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'education_alignment';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['taxonomy_term|education_alignment|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|education_alignment|tooltip';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'education_alignment';
  $ds_layout->view_mode = 'tooltip';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'description',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'description' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'span',
    ),
    'layout_wrapper' => 'span',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['taxonomy_term|education_alignment|tooltip'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function sbac_alignment_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'tooltip';
  $ds_view_mode->label = 'Tooltip';
  $ds_view_mode->entities = array(
    'taxonomy_term' => 'taxonomy_term',
    'user' => 'user',
  );
  $export['tooltip'] = $ds_view_mode;

  return $export;
}
