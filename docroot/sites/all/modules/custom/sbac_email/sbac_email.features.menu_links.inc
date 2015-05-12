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

  // Exported menu link: management_mail-system:admin/config/system/mailsystem
  $menu_links['management_mail-system:admin/config/system/mailsystem'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/mailsystem',
    'router_path' => 'admin/config/system/mailsystem',
    'link_title' => 'Mail System',
    'options' => array(
      'attributes' => array(
        'title' => 'Configure per-module Mail System settings.',
      ),
      'identifier' => 'management_mail-system:admin/config/system/mailsystem',
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
  // Exported menu link: management_mime-mail:admin/config/system/mimemail
  $menu_links['management_mime-mail:admin/config/system/mimemail'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/mimemail',
    'router_path' => 'admin/config/system/mimemail',
    'link_title' => 'Mime Mail',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage mime mail system settings.',
      ),
      'identifier' => 'management_mime-mail:admin/config/system/mimemail',
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
  t('Mail System');
  t('Mime Mail');


  return $menu_links;
}
