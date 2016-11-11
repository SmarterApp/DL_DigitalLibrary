<?php
/**
 * @file
 * sbac_learning_registry.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_learning_registry_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer sbac_learning_registry'.
  $permissions['administer sbac_learning_registry'] = array(
    'name' => 'administer sbac_learning_registry',
    'roles' => array(),
    'module' => 'sbac_learning_registry',
  );

  return $permissions;
}
