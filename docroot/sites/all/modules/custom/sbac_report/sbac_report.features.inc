<?php
/**
 * @file
 * sbac_report.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_report_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_report_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements export of a csv file().
 */
function _cex_download( $output, $filename)
{
  header("Pragma: public");
  header("Expires: 0");
  header("Cache-Control: private");
  header("Content-type: application/octet-stream");
  header("Content-Disposition: attachment; filename=$filename");
  header("Accept-Ranges: bytes");
  echo $output;
  exit;
}