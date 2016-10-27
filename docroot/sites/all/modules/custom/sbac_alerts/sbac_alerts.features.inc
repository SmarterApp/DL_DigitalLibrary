<?php
/**
 * @file
 * sbac_alerts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_alerts_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_alerts_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function sbac_alerts_node_info() {
  $items = array(
    'sbac_alerts' => array(
      'name' => t('Alerts'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Alert Title'),
      'help' => '',
    ),
  );
  return $items;
}
