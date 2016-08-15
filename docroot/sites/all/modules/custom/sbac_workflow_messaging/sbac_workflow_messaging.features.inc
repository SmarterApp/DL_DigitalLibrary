<?php
/**
 * @file
 * sbac_workflow_messaging.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_workflow_messaging_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
