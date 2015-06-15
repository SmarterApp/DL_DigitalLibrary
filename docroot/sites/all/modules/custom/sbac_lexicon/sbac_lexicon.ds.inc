<?php
/**
 * @file
 * sbac_lexicon.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function sbac_lexicon_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|glossary_terms|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'glossary_terms';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'description',
      ),
    ),
    'fields' => array(
      'description' => 'left',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
  );
  $export['taxonomy_term|glossary_terms|default'] = $ds_layout;

  return $export;
}
