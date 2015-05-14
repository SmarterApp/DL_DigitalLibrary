<?php
/**
 * @file
 * sbac_central.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sbac_central_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_digital-library-resources:digital-library-resources
  $menu_links['main-menu_digital-library-resources:digital-library-resources'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'digital-library-resources',
    'router_path' => 'digital-library-resources',
    'link_title' => 'Digital Library Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'Digital Library Resources',
      ),
      'identifier' => 'main-menu_digital-library-resources:digital-library-resources',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: main-menu_forums:forums
  $menu_links['main-menu_forums:forums'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'forums',
    'router_path' => 'forums',
    'link_title' => 'Forums',
    'options' => array(
      'identifier' => 'main-menu_forums:forums',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
  );
  // Exported menu link: main-menu_home:<front>
  $menu_links['main-menu_home:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'identifier' => 'main-menu_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_my-resources:my-resources
  $menu_links['main-menu_my-resources:my-resources'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'my-resources',
    'router_path' => 'my-resources',
    'link_title' => 'My Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'My Resources',
      ),
      'identifier' => 'main-menu_my-resources:my-resources',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: main-menu_reports:reports
  $menu_links['main-menu_reports:reports'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'reports',
    'router_path' => 'reports',
    'link_title' => 'Reports',
    'options' => array(
      'identifier' => 'main-menu_reports:reports',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -38,
    'customized' => 1,
  );
  // Exported menu link: main-menu_resource-review:resource-review
  $menu_links['main-menu_resource-review:resource-review'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'resource-review',
    'router_path' => 'resource-review',
    'link_title' => 'Resource Review',
    'options' => array(
      'attributes' => array(
        'title' => 'Resource Review',
      ),
      'identifier' => 'main-menu_resource-review:resource-review',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Digital Library Resources');
  t('Forums');
  t('Home');
  t('My Resources');
  t('Reports');
  t('Resource Review');


  return $menu_links;
}
