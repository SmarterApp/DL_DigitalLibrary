<?php
/**
 * @file
 * sbac_landing_page.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_landing_page_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-instructional_resource'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'instructional_resource',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'resource_feature',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => 'Instructional Resources',
    'visibility' => 0,
  );

  $export['block-playlist_resource'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'playlist_resource',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'resource_feature',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => 'Playlist Resource',
    'visibility' => 0,
  );

  $export['block-professionial_resource'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'professionial_resource',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'resource_feature',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => 'Professional Learning Resources',
    'visibility' => 0,
  );

  return $export;
}
