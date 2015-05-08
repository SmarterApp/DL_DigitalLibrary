<?php
/**
 * @file
 * sbac_sso.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_sso_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_enforce_admin';
  $strongarm->value = 0;
  $export['autologout_enforce_admin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_inactivity_message';
  $strongarm->value = 'You have been logged out due to inactivity.';
  $export['autologout_inactivity_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_max_timeout';
  $strongarm->value = '1800';
  $export['autologout_max_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_message';
  $strongarm->value = 'Select OK to extend your session. Pressing Cancel or failing to respond in the next two minutes will require site reauthentication.';
  $export['autologout_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_no_dialog';
  $strongarm->value = 0;
  $export['autologout_no_dialog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_padding';
  $strongarm->value = '300';
  $export['autologout_padding'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_redirect_url';
  $strongarm->value = 'user/login';
  $export['autologout_redirect_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_timeout';
  $strongarm->value = '1800';
  $export['autologout_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_use_watchdog';
  $strongarm->value = 0;
  $export['autologout_use_watchdog'] = $strongarm;

  return $export;
}
