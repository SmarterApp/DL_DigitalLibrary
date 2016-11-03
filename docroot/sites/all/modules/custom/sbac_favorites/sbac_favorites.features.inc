<?php
/**
 * @file
 * sbac_favorites.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_favorites_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
