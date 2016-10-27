<?php
/**
 * @file
 * sbac_flag_taxonomy_resource_flags.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_flag_taxonomy_resource_flags_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
