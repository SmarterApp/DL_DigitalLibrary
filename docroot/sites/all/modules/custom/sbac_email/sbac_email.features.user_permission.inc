<?php
/**
 * @file
 * sbac_email.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_email_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer smtp module'.
  $permissions['administer smtp module'] = array(
    'name' => 'administer smtp module',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'smtp',
  );

  // Exported permission: 'flag email'.
  $permissions['flag email'] = array(
    'name' => 'flag email',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag subscribe_term'.
  $permissions['flag subscribe_term'] = array(
    'name' => 'flag subscribe_term',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag email'.
  $permissions['unflag email'] = array(
    'name' => 'unflag email',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_term'.
  $permissions['unflag subscribe_term'] = array(
    'name' => 'unflag subscribe_term',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
