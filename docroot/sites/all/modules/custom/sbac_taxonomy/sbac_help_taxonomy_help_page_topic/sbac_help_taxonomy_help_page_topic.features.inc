<?php
/**
 * @file
 * sbac_help_taxonomy_help_page_topic.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_help_taxonomy_help_page_topic_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
