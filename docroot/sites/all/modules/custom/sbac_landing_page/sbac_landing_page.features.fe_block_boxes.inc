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
  $fe_block_boxes->body = '<p><img src="/sites/all/themes/custom/SBAC/images/search-images/instructional.jpg" alt="Classroom Photo" width="225" height="150" />Instructional Resources include ideas, activities, tools, and lessons designed to enhance instruction and supplement curriculum within K-12 classrooms.</p>';

  $export['instructional_resource'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Playlist Resource';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'playlist_resource';
  $fe_block_boxes->body = '<p><img src="/sites/all/themes/custom/SBAC/images/search-images/playlist.jpg" alt="Book Photo" width="225" height="150" />Playlists are collections of Digital Library resources that all focus on the same or similar content, and are organized into progressions of skills or understanding.</p>';

  $export['playlist_resource'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Professional Learning Resources';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'professionial_resource';
  $fe_block_boxes->body = '<p><img src="/sites/all/themes/custom/SBAC/images/search-images/professional-learning.jpg" alt="Teachers Photo" width="225" height="150" />Professional Learning Resources focus on educator professional development, mentoring, and coaching, and have utility in professional learning communities.</p>';

  $export['professionial_resource'] = $fe_block_boxes;

  return $export;
}
