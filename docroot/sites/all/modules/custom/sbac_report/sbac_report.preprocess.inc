<?php
/**
 * @file
 * Preprocess for SBAC Report.
 */

/**
 * Preprocess for sbac_report_individual.
 */
function sbac_report_preprocess_sbac_report_individual(&$vars) {
  drupal_add_css(drupal_get_path('module', 'sbac_report') . '/css/sbac_report.css');
}
