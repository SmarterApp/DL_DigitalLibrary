<?php
/**
 * @file
 * sbac_featured_content.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_featured_content_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'flag featured_node'.
  $permissions['flag featured_node'] = array(
    'name' => 'flag featured_node',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag welcome_help_topic'.
  $permissions['flag welcome_help_topic'] = array(
    'name' => 'flag welcome_help_topic',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag featured_node'.
  $permissions['unflag featured_node'] = array(
    'name' => 'unflag featured_node',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag welcome_help_topic'.
  $permissions['unflag welcome_help_topic'] = array(
    'name' => 'unflag welcome_help_topic',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
