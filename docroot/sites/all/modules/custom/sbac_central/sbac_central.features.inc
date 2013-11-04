<?php
/**
 * @file
 * sbac_central.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_central_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
