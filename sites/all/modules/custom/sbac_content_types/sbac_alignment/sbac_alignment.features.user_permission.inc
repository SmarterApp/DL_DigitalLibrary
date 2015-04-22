<?php
/**
 * @file
 * sbac_alignment.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_alignment_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create alignment content'.
  $permissions['create alignment content'] = array(
    'name' => 'create alignment content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any alignment content'.
  $permissions['delete any alignment content'] = array(
    'name' => 'delete any alignment content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'moderator' => 'moderator',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own alignment content'.
  $permissions['delete own alignment content'] = array(
    'name' => 'delete own alignment content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any alignment content'.
  $permissions['edit any alignment content'] = array(
    'name' => 'edit any alignment content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'moderator' => 'moderator',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own alignment content'.
  $permissions['edit own alignment content'] = array(
    'name' => 'edit own alignment content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
