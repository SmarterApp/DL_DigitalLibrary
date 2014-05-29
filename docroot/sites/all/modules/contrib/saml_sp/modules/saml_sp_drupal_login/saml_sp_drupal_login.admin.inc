<?php

/**
 * @file
 * Admin pages for the SAML Drupal Login module
 */

/**
 * Configure which IDP to use when authenticating with Drupal.
 */
function saml_sp_drupal_login__admin_config_form($form, &$form_state) {
  // List all the IDPs in the system.
  foreach (saml_sp__load_all_idps() as $machine_name => $idp) {
    $idps[$machine_name] = $idp->name;
  }

  $form['saml_sp_drupal_login__idp'] = array(
    '#type' => 'select',
    '#options' => $idps,
    '#title' => t('IDP'),
    '#description' => t('Choose the IDP to use when authenticating Drupal logins'),
    '#default_value' => variable_get('saml_sp_drupal_login__idp', ''),
  );
  return system_settings_form($form);
}
