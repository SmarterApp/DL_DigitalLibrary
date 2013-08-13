<?php
/**
 * @file
 * sbac_search.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sbac_search_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management:admin/people/search
  $menu_links['management:admin/people/search'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/people/search',
    'router_path' => 'admin/people/search',
    'link_title' => 'User Search',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'parent_path' => 'admin/people',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('User Search');


  return $menu_links;
}
