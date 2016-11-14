<?php

/**
 * Builds the ART API settings form.
 */
function sbac_art_api_settings_form($form, &$form_state) {
  $form['sbac_art_api_oauth_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base OAuth2 URL'),
    '#description' => t('Enter the base URL for the OAuth2 server. No trailing slash.'),
    '#default_value' => variable_get('sbac_art_api_oauth_url', ''),
    '#required' => TRUE,
  );
  $form['sbac_art_api_oauth_id'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth2 Client ID'),
    '#description' => t("The client ID used to access this server."),
    '#default_value' => variable_get('sbac_art_api_oauth_id', ''),
    '#required' => TRUE,
  );
  $form['sbac_art_api_oauth_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth2 Client Secret'),
    '#description' => t('The secret to access this server (Similar to a password).'),
    '#element_validate' => array('_sbac_art_api_encrypted_field_validate'),
    '#default_value' => sbac_art_api_decrypt(variable_get('sbac_art_api_oauth_secret', '')),
    '#required' => FALSE,
  );
  $form['sbac_art_api_oauth_username'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth2 Username'),
    '#description' => t('The username to authenticate with.'),
    '#default_value' => variable_get('sbac_art_api_oauth_username', ''),
    '#required' => TRUE,
  );
  $form['sbac_art_api_oauth_password'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth2 Password'),
    '#description' => t('The password to authenticate with.'),
    '#element_validate' => array('_sbac_art_api_encrypted_field_validate'),
    '#default_value' => sbac_art_api_decrypt(variable_get('sbac_art_api_oauth_password', '')),
    '#required' => TRUE,
  );
  $form['sbac_art_api_base_rest_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base REST URL'),
    '#description' => t('Enter the base path to the REST URL. No trailing slash.'),
    '#default_value' => variable_get('sbac_art_api_base_rest_url', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Form validate handler for the ART API settings form.
 */
function sbac_art_api_settings_form_validate($form, &$form_state) {
  // Check if the URLs are valid
  if (!valid_url($form_state['values']['sbac_art_api_oauth_url'])) {
    form_set_error('sbac_art_api_oauth_url', t('You have entered an invalid URL. Please try again.'));
  }
  if (!valid_url($form_state['values']['sbac_art_api_base_rest_url'])) {
    form_set_error('sbac_art_api_base_rest_url', t('You have entered an invalid URL. Please try again.'));
  }
}

/**
 * Encrypted element form handler.
 */
function _sbac_art_api_encrypted_field_validate($element, &$form_state, $form) {
  if (!empty($element['#value'])) {
    form_set_value($element, sbac_art_api_encrypt($element['#value']), $form_state);
  }
}
