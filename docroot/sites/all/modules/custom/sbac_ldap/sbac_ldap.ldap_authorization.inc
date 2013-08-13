<?php
/**
 * @file
 * sbac_ldap.ldap_authorization.inc
 */

/**
 * Implements hook_default_ldap_authorization().
 */
function sbac_ldap_default_ldap_authorization() {
  $export = array();

  $consumer_type = new stdClass();
  $consumer_type->disabled = FALSE; /* Edit this to true to make a default consumer_type disabled initially */
  $consumer_type->api_version = 1;
  $consumer_type->sid = 'SBAC';
  $consumer_type->consumer_type = 'drupal_role';
  $consumer_type->consumer_module = 'ldap_authorization_drupal_role';
  $consumer_type->status = TRUE;
  $consumer_type->only_ldap_authenticated = TRUE;
  $consumer_type->use_first_attr_as_groupid = TRUE;
  $consumer_type->mappings = 'a:11:{i:0;a:6:{s:12:"user_entered";s:29:"digital library administrator";s:4:"from";s:4:"5001";s:10:"normalized";s:29:"digital library administrator";s:10:"simplified";s:29:"digital library administrator";s:5:"valid";b:0;s:13:"error_message";s:117:"Role <em class="placeholder">digital library administrator</em>_name does not exist and role creation is not enabled.";}i:1;a:6:{s:12:"user_entered";s:11:"DLRB member";s:4:"from";s:4:"5003";s:10:"normalized";s:11:"DLRB member";s:10:"simplified";s:11:"DLRB member";s:5:"valid";b:0;s:13:"error_message";s:99:"Role <em class="placeholder">DLRB member</em>_name does not exist and role creation is not enabled.";}i:2;a:6:{s:12:"user_entered";s:11:"facilitator";s:4:"from";s:4:"5006";s:10:"normalized";s:11:"facilitator";s:10:"simplified";s:11:"facilitator";s:5:"valid";b:0;s:13:"error_message";s:99:"Role <em class="placeholder">facilitator</em>_name does not exist and role creation is not enabled.";}i:3;a:6:{s:12:"user_entered";s:9:"help desk";s:4:"from";s:4:"5007";s:10:"normalized";s:9:"help desk";s:10:"simplified";s:9:"help desk";s:5:"valid";b:0;s:13:"error_message";s:97:"Role <em class="placeholder">help desk</em>_name does not exist and role creation is not enabled.";}i:4;a:6:{s:12:"user_entered";s:9:"moderator";s:4:"from";s:4:"5008";s:10:"normalized";s:9:"moderator";s:10:"simplified";s:9:"moderator";s:5:"valid";b:0;s:13:"error_message";s:97:"Role <em class="placeholder">moderator</em>_name does not exist and role creation is not enabled.";}i:5;a:6:{s:12:"user_entered";s:20:"resource contributor";s:4:"from";s:4:"5010";s:10:"normalized";s:20:"resource contributor";s:10:"simplified";s:20:"resource contributor";s:5:"valid";b:0;s:13:"error_message";s:108:"Role <em class="placeholder">resource contributor</em>_name does not exist and role creation is not enabled.";}i:6;a:6:{s:12:"user_entered";s:18:"resource publisher";s:4:"from";s:4:"5011";s:10:"normalized";s:18:"resource publisher";s:10:"simplified";s:18:"resource publisher";s:5:"valid";b:0;s:13:"error_message";s:106:"Role <em class="placeholder">resource publisher</em>_name does not exist and role creation is not enabled.";}i:7;a:6:{s:12:"user_entered";s:17:"resource reviewer";s:4:"from";s:4:"5012";s:10:"normalized";s:17:"resource reviewer";s:10:"simplified";s:17:"resource reviewer";s:5:"valid";b:0;s:13:"error_message";s:105:"Role <em class="placeholder">resource reviewer</em>_name does not exist and role creation is not enabled.";}i:8;a:6:{s:12:"user_entered";s:20:"system administrator";s:4:"from";s:4:"5016";s:10:"normalized";s:20:"system administrator";s:10:"simplified";s:20:"system administrator";s:5:"valid";b:0;s:13:"error_message";s:108:"Role <em class="placeholder">system administrator</em>_name does not exist and role creation is not enabled.";}i:9;a:6:{s:12:"user_entered";s:14:"basic end user";s:4:"from";s:4:"5020";s:10:"normalized";s:14:"basic end user";s:10:"simplified";s:14:"basic end user";s:5:"valid";b:0;s:13:"error_message";s:102:"Role <em class="placeholder">basic end user</em>_name does not exist and role creation is not enabled.";}i:10;a:6:{s:12:"user_entered";s:17:"advanced end user";s:4:"from";s:4:"5021";s:10:"normalized";s:17:"advanced end user";s:10:"simplified";s:17:"advanced end user";s:5:"valid";b:0;s:13:"error_message";s:105:"Role <em class="placeholder">advanced end user</em>_name does not exist and role creation is not enabled.";}}';
  $consumer_type->use_filter = TRUE;
  $consumer_type->synch_to_ldap = FALSE;
  $consumer_type->synch_on_logon = TRUE;
  $consumer_type->revoke_ldap_provisioned = TRUE;
  $consumer_type->create_consumers = TRUE;
  $consumer_type->regrant_ldap_provisioned = TRUE;
  $export['drupal_role'] = $consumer_type;

  return $export;
}
