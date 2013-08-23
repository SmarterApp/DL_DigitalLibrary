<?php
/**
 * @file
 * sbac_alignment.ds.inc
 */

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
  );
  $export['tooltip'] = $ds_view_mode;

  return $export;
}
