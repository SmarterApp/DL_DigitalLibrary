<?php
/**
 * @file
 * sbac_search.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_search_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'system administrator' => 'system administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'system administrator' => 'system administrator',
    ),
    'module' => 'search',
  );

  return $permissions;
}
