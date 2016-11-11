<?php
/**
 * @file
 * sbac_resource.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_resource_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_resource_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function sbac_resource_image_default_styles() {
  $styles = array();

  // Exported image style: resource_image_grid.
  $styles['resource_image_grid'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 268,
          'height' => 138,
        ),
        'weight' => -9,
      ),
    ),
    'label' => 'resource_image_grid',
  );

  // Exported image style: resource_profile.
  $styles['resource_profile'] = array(
    'label' => 'Resource Profile',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 880,
          'height' => 455,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function sbac_resource_node_info() {
  $items = array(
    'resource' => array(
      'name' => t('Resource'),
      'base' => 'node_content',
      'description' => t('Creates resource within the system.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
