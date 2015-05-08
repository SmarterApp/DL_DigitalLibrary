<?php
/**
 * @file
 * sbac_email.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_email_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-message-block_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'message-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
