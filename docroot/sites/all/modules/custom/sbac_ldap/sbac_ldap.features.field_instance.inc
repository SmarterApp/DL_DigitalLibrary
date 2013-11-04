<?php
/**
 * @file
 * sbac_ldap.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sbac_ldap_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-ldap_user_current_dn'
  $field_instances['user-user-ldap_user_current_dn'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'default_value_function' => 'ldap_user_dn_default',
    'deleted' => 0,
    'description' => 'May change when user\'s DN changes. This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_current_dn',
    'label' => 'User LDAP DN',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'user-user-ldap_user_last_checked'
  $field_instances['user-user-ldap_user_last_checked'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_last_checked',
    'label' => 'Unix timestamp of when Drupal user was compard to ldap entry.  This could be for purposes of synching, deleteing drupal account, etc.',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 17,
    ),
  );

  // Exported field_instance: 'user-user-ldap_user_ldap_exclude'
  $field_instances['user-user-ldap_user_ldap_exclude'] = array(
    'bundle' => 'user',
    'default_value' => 0,
    'deleted' => 0,
    'description' => 'This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_ldap_exclude',
    'label' => 'Whether to exclude the user from LDAP functionality',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'user-user-ldap_user_prov_entries'
  $field_instances['user-user-ldap_user_prov_entries'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_prov_entries',
    'label' => 'LDAP Entries that have been provisioned from this Drupal user.',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'user-user-ldap_user_puid'
  $field_instances['user-user-ldap_user_puid'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'default_value_function' => 'ldap_user_puid_default',
    'deleted' => 0,
    'description' => 'This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_puid',
    'label' => 'Value of user\'s permanent unique id.  This should never change for a given ldap identified user.',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'user-user-ldap_user_puid_property'
  $field_instances['user-user-ldap_user_puid_property'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'default_value_function' => 'ldap_user_puid_property_default',
    'deleted' => 0,
    'description' => 'This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_puid_property',
    'label' => 'Property specified as user\'s puid.',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'user-user-ldap_user_puid_sid'
  $field_instances['user-user-ldap_user_puid_sid'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'default_value_function' => 'ldap_user_provisioned_sid_default',
    'deleted' => 0,
    'description' => 'This field should not be edited.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'tooltip' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'ldap_user_puid_sid',
    'label' => 'LDAP Server ID that puid was derived from.  NULL if puid is independent of server configuration instance.',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'ldap_user',
      'settings' => array(),
      'type' => 'ldap_user_hidden',
      'weight' => 12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('LDAP Entries that have been provisioned from this Drupal user.');
  t('LDAP Server ID that puid was derived from.  NULL if puid is independent of server configuration instance.');
  t('May change when user\'s DN changes. This field should not be edited.');
  t('Property specified as user\'s puid.');
  t('This field should not be edited.');
  t('Unix timestamp of when Drupal user was compard to ldap entry.  This could be for purposes of synching, deleteing drupal account, etc.');
  t('User LDAP DN');
  t('Value of user\'s permanent unique id.  This should never change for a given ldap identified user.');
  t('Whether to exclude the user from LDAP functionality');

  return $field_instances;
}
