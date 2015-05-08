<?php
/**
 * @file
 * sbac_email.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sbac_email_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_smtp-authentication-support:admin/config/system/smtp
  $menu_links['management_smtp-authentication-support:admin/config/system/smtp'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/smtp',
    'router_path' => 'admin/config/system/smtp',
    'link_title' => 'SMTP Authentication Support',
    'options' => array(
      'attributes' => array(
        'title' => 'Allow for site emails to be sent through an SMTP server of your choice.',
      ),
      'identifier' => 'management_smtp-authentication-support:admin/config/system/smtp',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_system:admin/config/system',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('SMTP Authentication Support');


  return $menu_links;
}
