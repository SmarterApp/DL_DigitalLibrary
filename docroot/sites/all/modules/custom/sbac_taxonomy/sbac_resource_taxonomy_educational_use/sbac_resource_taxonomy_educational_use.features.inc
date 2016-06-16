<?php
/**
 * @file
 * sbac_resource_taxonomy_educational_use.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_resource_taxonomy_educational_use_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
