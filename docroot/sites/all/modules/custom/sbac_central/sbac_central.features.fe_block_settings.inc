<?php
/**
 * @file
 * sbac_central.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_central_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['user-login'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'login',
    'module' => 'user',
    'node_types' => array(),
    'pages' => 'legal_accept/*
legal_accept
terms-of-service',
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
