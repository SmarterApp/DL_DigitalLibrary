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

  // Exported menu link: management_flag:admin/structure/entity-type/flag
  $menu_links['management_flag:admin/structure/entity-type/flag'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/entity-type/flag',
    'router_path' => 'admin/structure/entity-type/flag',
    'link_title' => 'Flag',
    'options' => array(
      'attributes' => array(
        'title' => 'View all the bundles for \'Flag\'',
      ),
      'identifier' => 'management_flag:admin/structure/entity-type/flag',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_entity-types:admin/structure/entity-type',
  );
  // Exported menu link: management_flags:admin/structure/flags
  $menu_links['management_flags:admin/structure/flags'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/flags',
    'router_path' => 'admin/structure/flags',
    'link_title' => 'Flags',
    'options' => array(
      'attributes' => array(
        'title' => 'Configure flags for marking content with arbitrary information (such as <em>offensive</em> or <em>bookmarked</em>).',
      ),
      'identifier' => 'management_flags:admin/structure/flags',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_structure:admin/structure',
  );
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
  // Exported menu link: navigation_flag-resource:sbac-flag/%/flag-resource
  $menu_links['navigation_flag-resource:sbac-flag/%/flag-resource'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'sbac-flag/%/flag-resource',
    'router_path' => 'sbac-flag/%/flag-resource',
    'link_title' => 'Flag Resource',
    'options' => array(
      'identifier' => 'navigation_flag-resource:sbac-flag/%/flag-resource',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_resolve-all-flags:sbac-flag/%/resolve-all-flags
  $menu_links['navigation_resolve-all-flags:sbac-flag/%/resolve-all-flags'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'sbac-flag/%/resolve-all-flags',
    'router_path' => 'sbac-flag/%/resolve-all-flags',
    'link_title' => 'Resolve All Flags',
    'options' => array(
      'identifier' => 'navigation_resolve-all-flags:sbac-flag/%/resolve-all-flags',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Flag');
  t('Flag Resource');
  t('Flags');
  t('Message subscribe settings');
  t('Message types');
  t('Resolve All Flags');


  return $menu_links;
}
