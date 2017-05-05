<?php
/**
 * @file
 * sbac_landing_page.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function sbac_landing_page_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Instructional Resources';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'instructional_resource';
  $fe_block_boxes->body = '<p>Blah Blah</p>';

  $export['instructional_resource'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Playlist Resource';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'playlist_resource';
  $fe_block_boxes->body = '<p>Blah Blah</p>';

  $export['playlist_resource'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Professional Learning Resources';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'professionial_resource';
  $fe_block_boxes->body = '<p>Blah Blah</p>';

  $export['professionial_resource'] = $fe_block_boxes;

  return $export;
}
