<?php
/**
 * @file
 * sbac_help.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_help_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'publish any help_page content'.
  $permissions['publish any help_page content'] = array(
    'name' => 'publish any help_page content',
    'roles' => array(
      'help desk' => 'help desk',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish editable help_page content'.
  $permissions['publish editable help_page content'] = array(
    'name' => 'publish editable help_page content',
    'roles' => array(),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish own help_page content'.
  $permissions['publish own help_page content'] = array(
    'name' => 'publish own help_page content',
    'roles' => array(),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish any help_page content'.
  $permissions['unpublish any help_page content'] = array(
    'name' => 'unpublish any help_page content',
    'roles' => array(
      'help desk' => 'help desk',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish editable help_page content'.
  $permissions['unpublish editable help_page content'] = array(
    'name' => 'unpublish editable help_page content',
    'roles' => array(),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish own help_page content'.
  $permissions['unpublish own help_page content'] = array(
    'name' => 'unpublish own help_page content',
    'roles' => array(),
    'module' => 'publishcontent',
  );

  return $permissions;
}
