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

  // Exported permission: 'administer flags'.
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
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

  // Exported permission: 'administer message subscribe'.
  $permissions['administer message subscribe'] = array(
    'name' => 'administer message subscribe',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'message_subscribe',
  );

  // Exported permission: 'administer message types'.
  $permissions['administer message types'] = array(
    'name' => 'administer message types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'message',
  );

  // Exported permission: 'create messages'.
  $permissions['create messages'] = array(
    'name' => 'create messages',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'message',
  );

  // Exported permission: 'delete terms in forum_flags'.
  $permissions['delete terms in forum_flags'] = array(
    'name' => 'delete terms in forum_flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in resource_flags'.
  $permissions['delete terms in resource_flags'] = array(
    'name' => 'delete terms in resource_flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in forum_flags'.
  $permissions['edit terms in forum_flags'] = array(
    'name' => 'edit terms in forum_flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in resource_flags'.
  $permissions['edit terms in resource_flags'] = array(
    'name' => 'edit terms in resource_flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'flag subscribe_comments'.
  $permissions['flag subscribe_comments'] = array(
    'name' => 'flag subscribe_comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag subscribe_node'.
  $permissions['flag subscribe_node'] = array(
    'name' => 'flag subscribe_node',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_comments'.
  $permissions['unflag subscribe_comments'] = array(
    'name' => 'unflag subscribe_comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_node'.
  $permissions['unflag subscribe_node'] = array(
    'name' => 'unflag subscribe_node',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use flag import'.
  $permissions['use flag import'] = array(
    'name' => 'use flag import',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
