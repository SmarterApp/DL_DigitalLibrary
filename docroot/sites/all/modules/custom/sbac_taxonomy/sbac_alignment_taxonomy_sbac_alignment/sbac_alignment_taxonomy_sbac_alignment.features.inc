<?php
/**
 * @file
 * sbac_alignment_taxonomy_sbac_alignment.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_alignment_taxonomy_sbac_alignment_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
