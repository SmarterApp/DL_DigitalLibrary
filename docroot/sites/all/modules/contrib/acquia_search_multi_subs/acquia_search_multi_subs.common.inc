<?php

/**
 * Get our expected search core name based on environment information
 *
 * @return string $expected_core_name
 */
function acquia_search_multi_subs_get_expected_search_core() {
  // Check if we have the correct environment variables
  if (isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $ah_site_environment = check_plain($_ENV['AH_SITE_ENVIRONMENT']);
  }
  else {
    // default to dev
    $ah_site_environment = 'dev';
  }
  // load our possible search cores
  $search_cores = acquia_search_multi_subs_get_search_cores();

  // Set the default core to production if all else fails
  $subscription_id = acquia_agent_settings('acquia_identifier');
  $expected_core_name = $subscription_id;

  // without a sitegroup value we can't do much
  if (!isset($_ENV['AH_SITE_NAME'])) {
    // We did not find a sitename, so let's default to a dev search core if it's present
    foreach ($search_cores as $search_core) {
      if (strstr($search_core['core_id'], 'dev')) {
        $expected_core_name = $search_core['core_id'];
        break;
      }
    }
  }
  else {
    // In all other cases, lets see if we can find a core to default to
    $ah_site_name = check_plain($_ENV['AH_SITE_NAME']);
    // Replace all weird characters that might appear in the sitegroup name or identifier
    $ah_site_name = preg_replace('@[^a-zA-Z0-9_-]+@','_',$ah_site_name);

    // Generate our expected core name according to Acquia Search
    // conventions
    if ($ah_site_environment != 'prod') {
      $expected_core_name = $subscription_id . '_' . $ah_site_name;
    }
  }
  return $expected_core_name;
}

/**
 * Get all the available search cores if its been set in the subscription.
 *
 * @return array $search_cores
 *   The search cores that are available according to the information in the
 *   rpc backend.
 */
function acquia_search_multi_subs_get_search_cores() {
  $search_cores = drupal_static(__FUNCTION__, array());

  // See if we can return it from static cache
  if (!empty($search_cores)) {
    return $search_cores;
  }

  $subscription = acquia_agent_settings('acquia_subscription_data');
  // Get our search cores if they exist
  if (isset($subscription['heartbeat_data']['search_cores'])) {
    $search_cores = $subscription['heartbeat_data']['search_cores'];
  }
  return $search_cores;
}

function acquia_search_multi_subs_get_settings_form(&$form, $form_state, $configuration, $defaults = array()) {
  $acquia_identifier = acquia_agent_settings('acquia_identifier');
  $acquia_key = acquia_agent_settings('acquia_key');
  $acquia_search_core = '';

  // Check if we have the auto switch set
  $defaults['acquia_search_auto_switch'] = isset($configuration['acquia_override_auto_switch']) ? $configuration['acquia_override_auto_switch'] : TRUE;
  $defaults['default_override_selector']  = isset($configuration['acquia_override_selector']) ? $configuration['acquia_override_selector'] : '';
  $defaults['default_acquia_id'] = !empty($configuration['acquia_override_subscription_id']) ? $configuration['acquia_override_subscription_id'] : $acquia_identifier;
  $defaults['default_acquia_key'] = !empty($configuration['acquia_override_subscription_key']) ? $configuration['acquia_override_subscription_key'] : $acquia_key;
  $defaults['not_other'] = (isset($configuration['acquia_override_selector']) && $configuration['acquia_override_selector'] !== 'other');
  $defaults['default_acquia_core_name'] = !empty($configuration['acquia_override_subscription_corename']) ? $configuration['acquia_override_subscription_corename'] : $acquia_search_core;

  // Define the override form
  $form['acquia_override_subscription'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure Acquia Search'),
    '#description' => t('This is usually not necessary unless you really want this
      search environment to connect to a different Acquia search subscription.
      by default it uses your subscription that was configured in the !acquiaagent.', array('!acquiaagent' => l('Acquia Agent','admin/config/system/acquia-agent'))),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
    '#weight' => 11,
    '#prefix' => '<div id="acquia-override-subscription-data-wrapper">',
    '#suffix' => '</div>',
  );

  // Add a form element to make it easier to choose from your multiple cores
  $options = array('other' => t('Other'));
  $search_cores = acquia_search_multi_subs_get_search_cores();
  if (is_array($search_cores)) {
    foreach ($search_cores as $search_core) {
      $options[$search_core['core_id']] = $search_core['core_id'];
    }
  }

  // Show a warning if there are not enough cores available to make the auto
  // switch possible
  if (count($options) <= 2) {
    drupal_set_message('It seems you only have 1 Acquia Search index. To find out if you are eligible for a search core per environment it is recommended you open a support ticket with Acquia.', 'warning');
  }

  // Add a checkbox to auto switch per environment
  $form['acquia_override_subscription']['acquia_override_auto_switch'] = array(
    '#type' => 'checkbox',
    '#title' => 'Automatically switch when an Acquia Environment is detected',
    '#description' => t('Based on the detection of the AH_SITE_NAME & AH_SITE_ENVIRONMENT header we can detect which environment you are currently using and switch the Acquia Search Core automatically if there is a corresponding core.'),
    '#default_value' => $defaults['acquia_search_auto_switch'],
  );


  // Add the ajax callback and wrapper
  $form['acquia_override_subscription']['acquia_override_selector'] = array(
    '#type' => 'select',
    '#title' => t('Acquia Search Core'),
    '#options' => $options,
    '#default_value' => $defaults['default_override_selector'],
    '#description' => t('Choose any of the available search cores or manually define one by choosing other.'),
    '#ajax' => array(
      'callback' => 'acquia_override_subscription_data',
      'wrapper' => 'acquia-override-subscription-data-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#states' => array(
      'visible' => array(   // action to take.
        ':input[name*="acquia_override_auto_switch"]' => array('checked' => FALSE),
      ),
    ),
  );


  $acquia_search_core = '';
  // Check if we choose a different search core
  if (isset($form_state['values']['acquia_override_selector'])) {
    if (is_array($search_cores)) {
      foreach ($search_cores as $search_core) {
        if ($search_core['core_id'] == $form_state['values']['acquia_override_selector']) {
          $acquia_search_core = $search_core['core_id'];
          break;
        }
      }
    }
  }

  // Generate our custom form

  $form['acquia_override_subscription']['acquia_override_subscription_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your Acquia Subscription Identifier'),
    '#description' => t('Prefilled with the identifier of the Acquia Connector. You can find your details in Acquia Insight.'),
    '#default_value' => $defaults['default_acquia_id'],
    '#states' => array(
      'visible' => array(   // action to take.
        ':input[name*="acquia_override_selector"]' => array('value' => 'other'),
        ':input[name*="acquia_override_auto_switch"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['acquia_override_subscription']['acquia_override_subscription_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your Acquia Subscription key'),
    '#description' => t('Prefilled with the key of the Acquia Connector. You can find your details in Acquia Insight.'),
    '#default_value' => $defaults['default_acquia_key'],
    '#states' => array(
      'visible' => array(   // action to take.
        ':input[name*="acquia_override_selector"]' => array('value' => 'other'),
        ':input[name*="acquia_override_auto_switch"]' => array('checked' => FALSE),
      ),
    ),
  );

  // @Todo : Figure out why the heck it does not reload with the new default values...
  $form['acquia_override_subscription']['acquia_override_subscription_corename'] = array(
    '#type' => 'textfield',
    '#description' => t('Please enter the name of the Acquia Search core you want to connect to that belongs to the above identifier and key. In most cases you would want to use the dropdown list to get the correct value.'),
    '#title' => t('Enter your Acquia Search Core Name'),
    '#default_value' => $defaults['default_acquia_core_name'],
    '#states' => array(
      'visible' => array(   // action to take.
        ':input[name*="acquia_override_selector"]' => array('value' => 'other'),
        ':input[name*="acquia_override_auto_switch"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Make sure if we select a value from our dropdown list of cores, that they are not alterable as we need to use
  // #value because the #ajax property is silly.
  if (isset($form_state['values']) && !$defaults['manual_input']) {
    $form['acquia_override_subscription']['acquia_override_subscription_id']['#value'] = $acquia_identifier;
    $form['acquia_override_subscription']['acquia_override_subscription_id']['#disabled'] = true;
    $form['acquia_override_subscription']['acquia_override_subscription_key']['#value'] = $acquia_key;
    $form['acquia_override_subscription']['acquia_override_subscription_key']['#disabled'] = true;
    $form['acquia_override_subscription']['acquia_override_subscription_corename']['#value'] = $acquia_search_core;
    $form['acquia_override_subscription']['acquia_override_subscription_corename']['#disabled'] = true;
  }

  return $form;
}

/**
 * Ajax callback to get a more selective farm list based on the colony
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function acquia_override_subscription_data($form, &$form_state) {
  $form = drupal_rebuild_form($form['#form_id'], $form_state, $form);
  if (isset($form['acquia_override_subscription'])) {
    return $form['acquia_override_subscription'];
  }
  if (isset($form['options']['form']['acquia_override_subscription'])) {
    return $form['options']['form']['acquia_override_subscription'];
  }
  return FALSE;
}


function acquia_search_multi_subs_get_hostname($corename) {
  // Override the URL
    $search_host = variable_get('acquia_search_host', 'search.acquia.com');
    $search_cores = acquia_search_multi_subs_get_search_cores();
    foreach ($search_cores as $search_core) {
      if ($corename == $search_core['core_id']) {
        $search_host = $search_core['balancer'];
      }
    }
    return $search_host;
}