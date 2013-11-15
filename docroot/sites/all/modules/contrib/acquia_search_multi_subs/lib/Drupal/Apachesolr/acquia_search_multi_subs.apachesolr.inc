<?php

/**
 * Change the Acquia Search environment on the fly based on the
 * AH_SITE_ENVIRONMENT and AH_SITE_NAME server variable
 * 
 */
function acquia_search_multi_subs_apachesolr_init() {
  $apachesolr_environments = array();
  // Load our default environment and see if we should change it
  $environments = apachesolr_load_all_environments();

  foreach ($environments as $environment) {
    $env_id = $environment['env_id'];
    $has_auto_switch = apachesolr_environment_variable_get($env_id, 'acquia_override_auto_switch');

    // If auto switch is not enabled, go to the next environment
    if (!$has_auto_switch) {
      continue;
    }

    // Get the expected search core
    $expected_core_name = acquia_search_multi_subs_get_expected_search_core();
    // load our possible search cores
    $search_cores = acquia_search_multi_subs_get_search_cores();
    // We know we have to switch automatically so we check if our core name
    // that is currently set is correct. If not, we change it and rebuild
    // our system.
    $environment_core_name = apachesolr_environment_variable_get($env_id, 'acquia_override_subscription_corename');
    $environment_core_url = $environment['url'];
    $expected_environment_core_host = acquia_search_multi_subs_get_hostname($environment_core_name);
    $expected_environment_core_url = 'http://' . $expected_environment_core_host . '/solr/' . $expected_core_name;

    // if the core is already the same, don't do anything
    if ($expected_core_name == $environment_core_name && $expected_environment_core_url == $environment_core_url) {
      continue;
    }

    // Loop over all the possible search cores
    foreach ($search_cores as $search_core) {
      if ($search_core['core_id'] == $expected_core_name) {
        acquia_search_multi_subs_apachesolr_set_default_core($env_id, $search_core);
      }
    }
  }
}

/**
 * Edit the environment form to connect to acquia search
 *
 * Implements hook_form_FORM_ID_alter().
 *
 * @param type $form
 * @param type $form_state
 */
function acquia_search_multi_subs_form_apachesolr_environment_edit_form_alter(&$form, $form_state) {
  if ($form['service_class']['#value'] == 'AcquiaSearchService') {

    // Gets environment from form, gets connection status to Acquia Search.
    $env_id = isset($form['env_id']['#default_value']) ? $form['env_id']['#default_value'] : '';
    $environment = ($env_id) ? apachesolr_environment_load($env_id) : FALSE;
    $configuration = $environment['conf'];

    // Set our ajax default for showing or hiding the custom input fields
    $defaults = array();

    $defaults['manual_input'] = (isset($form_state['values']['acquia_override_selector']) && $form_state['values']['acquia_override_selector'] == 'other');
    // Get our common settings form
    acquia_search_multi_subs_get_settings_form($form, $form_state, $configuration, $defaults);

    // add our new validation and submit handlers to the form.
    array_unshift($form['actions']['save']['#validate'], 'acquia_search_multi_subs_environment_edit_form_validate');
    array_unshift($form['actions']['save']['#submit'], 'acquia_search_multi_subs_environment_edit_form_submit');
    array_unshift($form['actions']['save_edit']['#validate'], 'acquia_search_multi_subs_environment_edit_form_validate');
    array_unshift($form['actions']['save_edit']['#submit'], 'acquia_search_multi_subs_environment_edit_form_submit');
  }
}


/**
 * Validate if the values given are correct
 * @param type $form
 * @param type $form_state
 */
function acquia_search_multi_subs_environment_edit_form_validate($form, &$form_state) {
  $form_values = $form_state['values'];
  // Only activate if the checkbox has been enabled and there is valid content
  if ($form_values['acquia_override_subscription_id'] == '') {
    form_set_error('acquia_override_subscription_id', t('You must at least fill in a valid Acquia Subscription Identifier.'));
  }
  if ($form_values['acquia_override_subscription_key'] == '') {
    form_set_error('acquia_override_subscription_key', t('You must at least fill in a valid Acquia Subscription key.'));
  }
  if ($form_values['acquia_override_subscription_corename'] == '') {
    $form_values['acquia_override_subscription_corename'] = $form_values['acquia_override_subscription_id'];
  }

  // Set the identifier and key
  $identifier = $form_values['acquia_override_subscription_id'];
  $key = $form_values['acquia_override_subscription_key'];

  $subscription = acquia_agent_get_subscription(array(), $identifier, $key);
  if (is_int($subscription)) {
    form_set_error('acquia_override_subscription_key', t('This combination of ID and key is not valid.'));
  }
}

/**
 * Adds the values to the environment variable array so Acquia Search will work
 *
 * @param type $form
 * @param type $form_state
 */
function acquia_search_multi_subs_environment_edit_form_submit($form, &$form_state) {
  $fv = &$form_state['values'];

  // Only activate if the checkbox has been enabled and there is valid content
  // Add our overrides to the configuration
  if(!empty($fv['acquia_override_selector'])) {
    // Set the identifier and key
    $identifier = $fv['acquia_override_subscription_id'];
    $key = $fv['acquia_override_subscription_key'];
    $corename = $fv['acquia_override_subscription_corename'];

    // Add our acquia_connection check to this environment
    $fv['conf']['acquia_override_auto_switch'] = $fv['acquia_override_auto_switch'];
    $fv['conf']['acquia_override_selector'] = $fv['acquia_override_selector'];

    // Save that to our confs per environment, anything outside of conf is
    // ignored as extra value, so adding it to that array so it can be saved
    $fv['conf']['acquia_override_subscription_id'] = $identifier;
    $fv['conf']['acquia_override_subscription_key'] = $key;
    $fv['conf']['acquia_override_subscription_corename'] = $corename;

    // Set the derived key for this environment
    $subscription = acquia_agent_get_subscription(array(), $identifier, $key);
    $derived_key_salt = $subscription['derived_key_salt'];
    $derived_key = _acquia_search_create_derived_key($derived_key_salt, $corename, $key);
    $fv['conf']['acquia_search_key'] = $derived_key;

    $override_values = array();
    $override_values['env_id'] = $form['env_id']['#default_value'];
    $override_values['name'] = $fv['name'];
    $override_values['acquia_subscription_id'] = $identifier;
    $override_values['acquia_subscription_key'] = $key;
    $override_values['acquia_subscription_corename'] = $corename;

    // merge with our defaults
    $fv = array_merge($fv, acquia_search_get_environment($override_values));

    $search_host = acquia_search_multi_subs_get_hostname($corename);
    $fv['url'] = 'http://' . $search_host . variable_get('acquia_search_path', '/solr/'. $corename);

    if (empty($fv['conf']['acquia_override_auto_switch'])) {
      // unset our apachesolr_environments variable. This overrides
      // certain configurations and makes sure that we do not accidentially
      // override the server configs if auto switch is set to disabled.
      variable_del('apachesolr_environments');
    }
  }
  else {
    // Remove any manual configuration so we can auto-set the environment.
    unset($fv['conf']['acquia_search_key']);
    unset($fv['conf']['acquia_subscription_id']);
    unset($fv['conf']['acquia_subscription_key']);
    apachesolr_environment_variable_del($override_values['env_id'], 'acquia_search_key');
    apachesolr_environment_variable_del($override_values['env_id'], 'acquia_override_subscription_id');
    apachesolr_environment_variable_del($override_values['env_id'], 'acquia_override_subscription_key');
    apachesolr_environment_variable_del($override_values['env_id'], 'acquia_override_subscription_corename');
    $fv = array_merge($fv, acquia_search_get_environment($override_values));
  }
}

/**
 * Alter the environment before it gets saved
 *
 * Implements hook_acquia_search_enable_alter().
 *
 * @param array $environment
 *   The environment that is being enabled by the Acquia Search module.
 */
function acquia_search_multi_subs_acquia_search_enable_alter(&$environment) {
  $env_id = $environment['env_id'];
  $corename = apachesolr_environment_variable_get($env_id, 'acquia_override_subscription_corename');
  $id = apachesolr_environment_variable_get($env_id, 'acquia_override_subscription_id');
  $key = apachesolr_environment_variable_get($env_id, 'acquia_override_subscription_key');

  $subscription = acquia_agent_get_subscription($params = array(), $id, $key);
  // Override the URL
  $search_host = acquia_search_multi_subs_get_hostname($corename);
  $url = 'http://' . $search_host . variable_get('acquia_search_path', '/solr/'. $corename);
  $environment['url'] = $url;
}

/**
 * Set our default search core for the acquia index
 *
 * @param string $env_id
 *   Environment identifier
 *
 * @param array $search_core
 *   The search core data array from the connector subscription data
 */
function acquia_search_multi_subs_apachesolr_set_default_core($env_id, $search_core) {
  // Get the derived key salt from the subscription
  $key = acquia_agent_settings('acquia_key');
  $subscription = acquia_agent_settings('acquia_subscription_data');
  $derived_key_salt = $subscription['derived_key_salt'];
  // Create our derived key
  $derived_key = _acquia_search_create_derived_key($derived_key_salt, $search_core['core_id'], $key);

  // Set our variables in the subscription array
  apachesolr_environment_variable_set($env_id, 'acquia_override_subscription_corename', $search_core['core_id']);
  apachesolr_environment_variable_set($env_id, 'acquia_search_key', $derived_key);
  apachesolr_environment_variable_set($env_id, 'acquia_override_selector', $search_core['core_id']);

  // Generate the url where this core should connect to
  $url = 'http://' . $search_core['balancer'] . variable_get('acquia_search_path', '/solr/'. $search_core['core_id']);
  $apachesolr_environments[$env_id]['url'] = $url;
  // Set our variable, needs two page loads to make sure it is in the
  // system. Setting the global conf variable is not valid as some
  // calls to apachesolr_load_all_environments happen too early in
  // the process. If we set the variable, we are sure it is there in
  // the next page load. Also, setting this variable only happens when
  // the environment changes and another environment which fits is
  // found.
  variable_set('apachesolr_environments', $apachesolr_environments);
  drupal_static_reset('apachesolr_load_all_environments');
}


