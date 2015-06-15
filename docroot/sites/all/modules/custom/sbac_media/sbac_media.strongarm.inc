<?php
/**
 * @file
 * sbac_media.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_media_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_background_callback';
  $strongarm->value = 1;
  $export['httprl_background_callback'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_connect_timeout';
  $strongarm->value = '5';
  $export['httprl_connect_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_dns_timeout';
  $strongarm->value = '5';
  $export['httprl_dns_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_global_timeout';
  $strongarm->value = '300';
  $export['httprl_global_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_server_addr';
  $strongarm->value = '-1';
  $export['httprl_server_addr'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_timeout';
  $strongarm->value = '300';
  $export['httprl_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'httprl_ttfb_timeout';
  $strongarm->value = '20';
  $export['httprl_ttfb_timeout'] = $strongarm;

  return $export;
}
