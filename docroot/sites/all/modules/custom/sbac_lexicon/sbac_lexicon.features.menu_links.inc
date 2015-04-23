<?php
/**
 * @file
 * sbac_lexicon.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sbac_lexicon_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_message-subscribe-settings:admin/config/system/message-subscribe
  $menu_links['management_message-subscribe-settings:admin/config/system/message-subscribe'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/message-subscribe',
    'router_path' => 'admin/config/system/message-subscribe',
    'link_title' => 'Message subscribe settings',
    'options' => array(
      'attributes' => array(
        'title' => 'Administer message subscribe',
      ),
      'identifier' => 'management_message-subscribe-settings:admin/config/system/message-subscribe',
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
  // Exported menu link: management_message-types:admin/structure/messages
  $menu_links['management_message-types:admin/structure/messages'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/messages',
    'router_path' => 'admin/structure/messages',
    'link_title' => 'Message types',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage Message types.',
      ),
      'identifier' => 'management_message-types:admin/structure/messages',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_structure:admin/structure',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Message subscribe settings');
  t('Message types');


  return $menu_links;
}
