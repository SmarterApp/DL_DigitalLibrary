<?php
/**
 * @file
 * sbac_resource_taxonomy_technologies_for_classroom_use.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_resource_taxonomy_technologies_for_classroom_use_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
