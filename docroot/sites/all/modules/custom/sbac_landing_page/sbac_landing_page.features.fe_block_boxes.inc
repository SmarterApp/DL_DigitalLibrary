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
  $fe_block_boxes->body = '<p><img src="/sites/all/themes/custom/SBAC/images/search-images/instructional.jpg" alt="Classroom Photo" width="225" height="150" />The primary purpose of instructional resources is for use with students in K-12 classrooms. These resources help educators implement the intent of Common Core Standards using formative assessment practices. Examples are lesson or unit plans, student self-assessment and reflection guides, and performance tasks for writing.</p>';

  $export['instructional_resource'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Playlist Resource';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'playlist_resource';
  $fe_block_boxes->body = '<p><img src="/sites/all/themes/custom/SBAC/images/search-images/playlist.jpg" alt="Book Photo" width="225" height="150" />Playlist resources build educator understanding of the formative assessment process, the Common Core State Standards, or the components of a balanced assessment system. Examples include presentations with facilitator\'s notes, videos modeling mathmetical practices, and guides to help educators provide effective feedback.</p>';

  $export['playlist_resource'] = $fe_block_boxes;

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Professional Learning Resources';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'professionial_resource';
  $fe_block_boxes->body = '<p><img src="/sites/all/themes/custom/SBAC/images/search-images/professional-learning.jpg" alt="Teachers Photo" width="225" height="150" />Professional learning resources build educator understanding of the formative assessment process, the Common Core State Standards, or the components of a balanced assessment system. Examples include presentations with facilitator\'s notes, videos modeling mathmetical practices, and guides to help educators provide effective feedback.</p>';

  $export['professionial_resource'] = $fe_block_boxes;

  return $export;
}
