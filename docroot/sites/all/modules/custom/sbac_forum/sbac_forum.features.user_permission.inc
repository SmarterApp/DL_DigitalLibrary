<?php
/**
 * @file
 * sbac_forum.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_forum_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete terms in forum'.
  $permissions['delete terms in forum'] = array(
    'name' => 'delete terms in forum',
    'roles' => array(
      'facilitator' => 'facilitator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in forum'.
  $permissions['edit terms in forum'] = array(
    'name' => 'edit terms in forum',
    'roles' => array(
      'facilitator' => 'facilitator',
    ),
    'module' => 'taxonomy',
  );

  return $permissions;
}
