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

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'administrator' => 'administrator',
      'facilitator' => 'facilitator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer morecomments'.
  $permissions['administer morecomments'] = array(
    'name' => 'administer morecomments',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'morecomments',
  );

  // Exported permission: 'create topic content'.
  $permissions['create topic content'] = array(
    'name' => 'create topic content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any topic content'.
  $permissions['delete any topic content'] = array(
    'name' => 'delete any topic content',
    'roles' => array(
      'facilitator' => 'facilitator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own topic content'.
  $permissions['delete own topic content'] = array(
    'name' => 'delete own topic content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in forum'.
  $permissions['delete terms in forum'] = array(
    'name' => 'delete terms in forum',
    'roles' => array(
      'facilitator' => 'facilitator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any topic content'.
  $permissions['edit any topic content'] = array(
    'name' => 'edit any topic content',
    'roles' => array(
      'facilitator' => 'facilitator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own topic content'.
  $permissions['edit own topic content'] = array(
    'name' => 'edit own topic content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in forum'.
  $permissions['edit terms in forum'] = array(
    'name' => 'edit terms in forum',
    'roles' => array(
      'facilitator' => 'facilitator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  return $permissions;
}
