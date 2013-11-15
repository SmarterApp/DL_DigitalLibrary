<?php

/**
 * Change the Acquia Search environment on the fly based on the
 * AH_SITE_ENVIRONMENT and AH_SITE_NAME server variable
 *
 */
function acquia_search_multi_subs_searchapi_init() {
  $servers = search_api_server_load_multiple(FALSE);
  // We'll do it for all servers as we have no clue which servers we need to change
  foreach ($servers as $server) {
    // Check if the environment we've loaded has Acquia Search and verify if it
    // should be overridden
    if (!isset($server->options['acquia_override_subscription']['acquia_override_auto_switch'])) {
      // don't do anything
      break;
    }

    // If auto switch is enabled
    if ($server->options['acquia_override_subscription']['acquia_override_auto_switch'] == 1) {
       // Get the expected search core
      $expected_core_name = acquia_search_multi_subs_get_expected_search_core();

      // load our possible search cores
      $search_cores = acquia_search_multi_subs_get_search_cores();

      // We know we have to switch automatically so we check if our core name
      // that is currently set is correct. If not, we change it and rebuild
      // our system.
      $environment_core_name = $server->options['acquia_override_subscription']['acquia_override_subscription_corename'];

      // if the core is already the same, don't do anything
      if ($expected_core_name == $environment_core_name) {
        continue;
      }

      // Loop over all the possible search cores
      foreach ($search_cores as $search_core) {
        if ($search_core['core_id'] != $expected_core_name) {
          continue;
        }
        $server->options['acquia_override_subscription']['acquia_override_subscription_corename'] = $search_core['core_id'];
        // Get the derived key salt from the subscription
        $subscription = acquia_agent_settings('acquia_subscription_data');
        $derived_key_salt = $subscription['derived_key_salt'];
        // Get the derived key salt from the subscription
        $key = acquia_agent_settings('acquia_key');
        // Create our derived key
        $derived_key = _acquia_search_create_derived_key($derived_key_salt, $search_core['core_id'], $key);
        $server->options['derived_key'] = $derived_key;

        entity_save('search_api_server', $server);
      }
    }
  }
}

/**
 * Implements hook_search_api_service_info_alter().
 */
function acquia_search_multi_subs_search_api_service_info_alter(&$service_info) {
  foreach ($service_info as &$server) {
    if ($server['class'] == 'SearchApiAcquiaSearchService') {
      $server['class'] = 'SearchApiAcquiaSearchMultiService';
    }
  }
}