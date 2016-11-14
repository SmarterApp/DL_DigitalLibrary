<?php
/**
 * @file
 * sbac_authorized_domains.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_authorized_domains_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer authorized domains'.
  $permissions['administer authorized domains'] = array(
    'name' => 'administer authorized domains',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'sbac_authorized_domains',
  );

  return $permissions;
}
