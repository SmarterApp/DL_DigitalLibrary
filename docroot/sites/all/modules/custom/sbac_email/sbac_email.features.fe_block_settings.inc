<?php
/**
 * @file
 * sbac_email.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_email_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  return $export;
}
