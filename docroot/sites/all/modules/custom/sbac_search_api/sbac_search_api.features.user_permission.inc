<?php
/**
 * @file
 * sbac_search_api.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_search_api_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use search_api_sorts'.
  $permissions['use search_api_sorts'] = array(
    'name' => 'use search_api_sorts',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'authenticated user' => 'authenticated user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'guest' => 'guest',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'on-boarding' => 'on-boarding',
      'reports administrator' => 'reports administrator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'search_api_sorts',
  );

  return $permissions;
}
