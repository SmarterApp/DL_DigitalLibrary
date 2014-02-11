<?php
/**
 * @file
 * sbac_forum.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_forum_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == 'field_group' && $api == 'field_group') {
    return array('version' => 1);
  }
}
