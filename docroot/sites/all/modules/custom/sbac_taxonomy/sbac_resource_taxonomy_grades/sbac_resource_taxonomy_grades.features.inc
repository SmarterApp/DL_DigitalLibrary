<?php
/**
 * @file
 * sbac_resource_taxonomy_grades.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_resource_taxonomy_grades_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
