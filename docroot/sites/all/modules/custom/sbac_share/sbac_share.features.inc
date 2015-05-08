<?php
/**
 * @file
 * sbac_share.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_share_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
