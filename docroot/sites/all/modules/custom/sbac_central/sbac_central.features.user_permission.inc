<?php
/**
 * @file
 * sbac_central.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_central_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer sbac_central'.
  $permissions['administer sbac_central'] = array(
    'name' => 'administer sbac_central',
    'roles' => array(),
    'module' => 'sbac_central',
  );

  return $permissions;
}
