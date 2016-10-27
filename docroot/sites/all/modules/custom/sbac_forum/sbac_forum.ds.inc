<?php
/**
 * @file
 * sbac_forum.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function sbac_forum_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'forum_page_card';
  $ds_view_mode->label = 'Forum Page Card';
  $ds_view_mode->entities = array(
    'taxonomy_term' => 'taxonomy_term',
  );
  $export['forum_page_card'] = $ds_view_mode;

  return $export;
}
