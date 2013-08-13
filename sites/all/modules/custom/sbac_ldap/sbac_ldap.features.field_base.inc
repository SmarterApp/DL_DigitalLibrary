<?php
/**
 * @file
 * sbac_ldap.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function sbac_ldap_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'ldap_user_current_dn'
  $field_bases['ldap_user_current_dn'] = array(
    'active' => 1,
    'cadinality' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_current_dn',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'no_ui' => 1,
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'ldap_user_last_checked'
  $field_bases['ldap_user_last_checked'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_last_checked',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'number',
    'no_ui' => 1,
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'ldap_user_ldap_exclude'
  $field_bases['ldap_user_ldap_exclude'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_ldap_exclude',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'number',
    'no_ui' => 1,
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'ldap_user_prov_entries'
  $field_bases['ldap_user_prov_entries'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_prov_entries',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'no_ui' => 1,
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'ldap_user_puid'
  $field_bases['ldap_user_puid'] = array(
    'active' => 1,
    'cadinality' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_puid',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'no_ui' => 1,
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'ldap_user_puid_property'
  $field_bases['ldap_user_puid_property'] = array(
    'active' => 1,
    'cadinality' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_puid_property',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'no_ui' => 1,
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'ldap_user_puid_sid'
  $field_bases['ldap_user_puid_sid'] = array(
    'active' => 1,
    'cadinality' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'user',
    ),
    'field_name' => 'ldap_user_puid_sid',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'no_ui' => 1,
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
