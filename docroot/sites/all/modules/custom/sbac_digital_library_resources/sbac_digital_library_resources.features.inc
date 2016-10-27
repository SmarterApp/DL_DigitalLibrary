<?php
/**
 * @file
 * sbac_digital_library_resources.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_digital_library_resources_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "current_search" && $api == "current_search") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_digital_library_resources_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
