<?php
/**
 * @file
 * sbac_forum.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_forum_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function sbac_forum_node_info() {
  $items = array(
    'topic' => array(
      'name' => t('Topic'),
      'base' => 'node_content',
      'description' => t('Forum Topic'),
      'has_title' => '1',
      'title_label' => t('Topic Title'),
      'help' => '',
    ),
  );
  return $items;
}
