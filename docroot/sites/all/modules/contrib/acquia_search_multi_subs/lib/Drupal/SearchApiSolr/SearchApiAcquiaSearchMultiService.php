<?php

/**
 * @file
 * Contains SearchApiAcquiaSearchService.
 */


/**
 * Search API service class for Acquia Search.
 */
class SearchApiAcquiaSearchMultiService extends SearchApiAcquiaSearchService {

  /**
   * Set some special overrides for Acquia Search
   */
  public function setConnectionOptions() {
    if (isset($this->options['acquia_override_subscription'])) {
      $identifier = $this->options['acquia_override_subscription']['acquia_override_subscription_id'];
      $key = $this->options['acquia_override_subscription']['acquia_override_subscription_key'];
      $corename = $this->options['acquia_override_subscription']['acquia_override_subscription_corename'];

      $this->options['path'] = '/solr/' . $corename;
      // Set the derived key for this environment
      $subscription = acquia_agent_get_subscription(array(), $identifier, $key);
      $derived_key_salt = $subscription['derived_key_salt'];
      $derived_key = _acquia_search_create_derived_key($derived_key_salt, $corename, $key);
      $this->options['derived_key'] = $derived_key;

      // Get and set our search core hostname
      $search_host = acquia_search_multi_subs_get_hostname($corename);
      $this->options['host'] = $search_host;
    }

  }

  /**
   * Overrides SearchApiSolrService::configurationForm().
   *
   * Populates the Solr configs with Acquia Search Information.
   */
  public function configurationForm(array $form, array &$form_state) {
    $form = parent::configurationForm($form, $form_state);
    $configuration = isset($this->options['acquia_override_subscription']) ? $this->options['acquia_override_subscription'] : array();
    $defaults = array();
    $defaults['manual_input'] = (isset($form_state['values']['options']['form']['acquia_override_subscription']['acquia_override_selector']) && $form_state['values']['options']['form']['acquia_override_subscription']['acquia_override_selector'] == 'other');

    // do not allow for other modules such as Search API Acquia to modify connection properties
    unset($form['modify_acquia_connection']);

    // Get our common settings form
    acquia_search_multi_subs_get_settings_form($form, $form_state, $configuration, $defaults);
    return $form;
  }

  /**
   * View this server's settings.
   */
  public function viewSettings() {
    $output = parent::viewSettings();

    // Set our special overrides if applicable
    $this->setConnectionOptions();

    $options = $this->options;
    $auto_detection = (isset($options['acquia_override_subscription']['acquia_override_auto_switch']) && $options['acquia_override_subscription']['acquia_override_auto_switch']);
    $auto_detection_state = ($auto_detection) ? t('enabled') : t('disabled');
    $output .= "<dl>\n  <dt>";
    $output .= t('Acquia Search Auto Detection');
    $output .= "</dt>\n  <dd>";
    $output .= t('Auto detection of your environment is <strong>@state</strong>', array('@state' => $auto_detection_state));
    $output .= '</dd>';
    $output .= "\n</dl>";

    return $output;
  }

  /**
   * Overrides SearchApiSolrService::configurationFormValidate().
   *
   * Checks if the data that was inputted is correct and maps to an Acquia
   * Network subscription
   *
   */
  public function configurationFormValidate(array $form, array &$values, array &$form_state) {
    $form_values = &$form_state['values']['options']['form']['acquia_override_subscription'];
    // Only activate if the checkbox has been enabled and there is valid content
    if ($form_values['acquia_override_subscription_id'] == '') {
      form_set_error('options][form][acquia_override_subscription][acquia_override_subscription_id', t('You must at least fill in a valid Acquia Subscription Identifier.'));
    }
    if ($form_values['acquia_override_subscription_key'] == '') {
      form_set_error('options][form][acquia_override_subscription][acquia_override_subscription_key', t('You must at least fill in a valid Acquia Subscription key.'));
    }
    if ($form_values['acquia_override_selector'] != 'other') {
      $form_values['acquia_override_subscription_corename'] = $form_values['acquia_override_selector'];
    } elseif ($form_values['acquia_override_subscription_corename'] == '') {
      $form_values['acquia_override_subscription_corename'] = $form_values['acquia_override_subscription_id'];
    }

    // Set the identifier and key
    $identifier = $form_values['acquia_override_subscription_id'];
    $key = $form_values['acquia_override_subscription_key'];

    $subscription = acquia_agent_get_subscription(array(), $identifier, $key);
    if (is_int($subscription)) {
      form_set_error('options][form][acquia_override_subscription][acquia_override_subscription_key', t('This combination of ID and key is not valid.'));
    }
    parent::configurationFormValidate($form, $values, $form_state);
  }

  /**
   * Overrides SearchApiSolrService::configurationFormSubmit().
   *
   * If auto detection is not on, let's change our search core name to the one
   * that was inputted.
   */
  public function configurationFormSubmit(array $form, array &$values, array &$form_state) {
    parent::configurationFormSubmit($form, $values, $form_state);

    // we do not allow other modules to modify the connection.
    unset($this->options['modify_acquia_connection']);

    // Only activate if the checkbox has been enabled and there is valid content
    // Add our overrides to the configuration
    $form_values = $form_state['values']['options']['form']['acquia_override_subscription'];
    $identifier = $this->options['acquia_override_subscription']['acquia_override_subscription_id'];
    $key = $this->options['acquia_override_subscription']['acquia_override_subscription_key'];
    $corename = $this->options['acquia_override_subscription']['acquia_override_subscription_corename'];

    // if we do not have auto switch enabled, statically configure the right
    // core to options.
    if (!$form_values['acquia_override_auto_switch']) {
      $this->options['path'] = '/solr/' . $corename;
      // Set the derived key for this environment
      $subscription = acquia_agent_get_subscription(array(), $identifier, $key);
      $derived_key_salt = $subscription['derived_key_salt'];
      $derived_key = _acquia_search_create_derived_key($derived_key_salt, $corename, $key);
      $this->options['derived_key'] = $derived_key;

      $search_host = acquia_search_multi_subs_get_hostname($corename);
      $this->options['host'] = $search_host;
    }
  }
}
