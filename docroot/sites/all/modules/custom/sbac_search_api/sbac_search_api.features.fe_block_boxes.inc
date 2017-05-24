<?php
/**
 * @file
 * sbac_search_api.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function sbac_search_api_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Placeholder for the CC Facet';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'cc_placeholder';
  $fe_block_boxes->body = '<p>Loading <img src="/misc/throbber-active.gif" alt="Loading animation" width="15" height="13" /></p>';

  $export['cc_placeholder'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Placeholder for the Target Facet';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'target_placeholder';
  $fe_block_boxes->body = '<p>Loading <img src="/misc/throbber-active.gif" alt="Loading animation" width="15" height="13" /></p>';

  $export['target_placeholder'] = $fe_block_boxes;

  return $export;
}
