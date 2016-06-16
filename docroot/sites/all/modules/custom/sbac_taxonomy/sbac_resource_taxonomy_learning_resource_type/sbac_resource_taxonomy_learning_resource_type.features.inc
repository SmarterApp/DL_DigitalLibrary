<?php
/**
 * @file
 * sbac_resource_taxonomy_learning_resource_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_resource_taxonomy_learning_resource_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
