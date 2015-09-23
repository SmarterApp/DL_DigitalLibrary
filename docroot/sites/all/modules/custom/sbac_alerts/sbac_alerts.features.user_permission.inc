<?php
/**
 * @file
 * sbac_alerts.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_alerts_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create sbac_alerts content'.
  $permissions['create sbac_alerts content'] = array(
    'name' => 'create sbac_alerts content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any sbac_alerts content'.
  $permissions['delete any sbac_alerts content'] = array(
    'name' => 'delete any sbac_alerts content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own sbac_alerts content'.
  $permissions['delete own sbac_alerts content'] = array(
    'name' => 'delete own sbac_alerts content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any sbac_alerts content'.
  $permissions['edit any sbac_alerts content'] = array(
    'name' => 'edit any sbac_alerts content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own sbac_alerts content'.
  $permissions['edit own sbac_alerts content'] = array(
    'name' => 'edit own sbac_alerts content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
