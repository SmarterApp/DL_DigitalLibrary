<?php
/**
 * @file
 * sbac_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: access print.
  $permissions['access print'] = array(
    'name' => 'access print',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'print',
  );

  // Exported permission: configure sbac.
  $permissions['configure sbac'] = array(
    'name' => 'configure sbac',
    'roles' => array(),
    'module' => 'sbac_core',
  );

  // Exported permission: eck add feedback bundles.
  $permissions['eck add feedback bundles'] = array(
    'name' => 'eck add feedback bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add feedback gate_keeper entities.
  $permissions['eck add feedback gate_keeper entities'] = array(
    'name' => 'eck add feedback gate_keeper entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck add feedback review entities.
  $permissions['eck add feedback review entities'] = array(
    'name' => 'eck add feedback review entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer feedback bundles.
  $permissions['eck administer feedback bundles'] = array(
    'name' => 'eck administer feedback bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer feedback gate_keeper entities.
  $permissions['eck administer feedback gate_keeper entities'] = array(
    'name' => 'eck administer feedback gate_keeper entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck administer feedback review entities.
  $permissions['eck administer feedback review entities'] = array(
    'name' => 'eck administer feedback review entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete feedback bundles.
  $permissions['eck delete feedback bundles'] = array(
    'name' => 'eck delete feedback bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete feedback gate_keeper entities.
  $permissions['eck delete feedback gate_keeper entities'] = array(
    'name' => 'eck delete feedback gate_keeper entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck delete feedback review entities.
  $permissions['eck delete feedback review entities'] = array(
    'name' => 'eck delete feedback review entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit feedback bundles.
  $permissions['eck edit feedback bundles'] = array(
    'name' => 'eck edit feedback bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit feedback gate_keeper entities.
  $permissions['eck edit feedback gate_keeper entities'] = array(
    'name' => 'eck edit feedback gate_keeper entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck edit feedback review entities.
  $permissions['eck edit feedback review entities'] = array(
    'name' => 'eck edit feedback review entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list feedback bundles.
  $permissions['eck list feedback bundles'] = array(
    'name' => 'eck list feedback bundles',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list feedback gate_keeper entities.
  $permissions['eck list feedback gate_keeper entities'] = array(
    'name' => 'eck list feedback gate_keeper entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck list feedback review entities.
  $permissions['eck list feedback review entities'] = array(
    'name' => 'eck list feedback review entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view feedback gate_keeper entities.
  $permissions['eck view feedback gate_keeper entities'] = array(
    'name' => 'eck view feedback gate_keeper entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: eck view feedback review entities.
  $permissions['eck view feedback review entities'] = array(
    'name' => 'eck view feedback review entities',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: manage feedback properties.
  $permissions['manage feedback properties'] = array(
    'name' => 'manage feedback properties',
    'roles' => array(),
    'module' => 'eck',
  );

  // Exported permission: view any taskit tasks.
  $permissions['view any taskit tasks'] = array(
    'name' => 'view any taskit tasks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taskit',
  );

  // Exported permission: view own taskit tasks.
  $permissions['view own taskit tasks'] = array(
    'name' => 'view own taskit tasks',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'taskit',
  );

  return $permissions;
}
