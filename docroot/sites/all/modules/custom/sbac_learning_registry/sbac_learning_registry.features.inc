<?php
/**
 * @file
 * sbac_learning_registry.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_learning_registry_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
