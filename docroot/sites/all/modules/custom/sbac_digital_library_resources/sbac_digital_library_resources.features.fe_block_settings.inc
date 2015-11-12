<?php
/**
 * @file
 * sbac_digital_library_resources.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_digital_library_resources_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['sbac_digital_library_resources-posted_w_distinction'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'posted_w_distinction',
    'module' => 'sbac_digital_library_resources',
    'node_types' => array(),
    'pages' => 'digital-library-resources
digital-library-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views-cd1ce356b15a5ee4d63abaa1aa697e16'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'cd1ce356b15a5ee4d63abaa1aa697e16',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'digital-library-resources
digital-library-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -37,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
