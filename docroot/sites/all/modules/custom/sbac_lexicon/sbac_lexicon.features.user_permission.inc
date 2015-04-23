<?php
/**
 * @file
 * sbac_lexicon.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_lexicon_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access lexicon'.
  $permissions['access lexicon'] = array(
    'name' => 'access lexicon',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'lexicon',
  );

  // Exported permission: 'administer lexicon'.
  $permissions['administer lexicon'] = array(
    'name' => 'administer lexicon',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'help desk' => 'help desk',
      'system administrator' => 'system administrator',
    ),
    'module' => 'lexicon',
  );

  return $permissions;
}
