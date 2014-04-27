<?php

/**
 * @file
 * Provides Admin interface to Google CDN.
 */

/**
 * Implements hook_admin().
 */
function google_cdn_admin() {
  $form = array();

  $form['google_cdn_connection_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connection Details'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['google_cdn_connection_details']['google_cdn_public_key_file'] = array(
    '#type' => 'managed_file',
    '#title' => t('Public Key'),
    '#default_value' => variable_get('google_cdn_public_key'),
    '#description' => t('The public p12 key that allows access to your Google Cloud Storage account.'),
    '#required' => TRUE,
    '#upload_validators' => array(
      'file_validate_extensions' => array('p12'),
    ),
    '#upload_location' => 'private://google_cdn/',
    '#process' => array('google_cdn_admin_public_key_file_element_process'),
  );

  $form['google_cdn_connection_details']['google_cdn_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Account Client ID'),
    '#default_value' => variable_get('google_cdn_client_id'),
    '#description' => t('The service account client ID credential. Should follow this pattern "xxxxxxxxxxxx-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.apps.googleusercontent.com"'),
    '#required' => TRUE,
  );

  $form['google_cdn_connection_details']['google_cdn_service_account_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Account Name'),
    '#default_value' => variable_get('google_cdn_service_account_name'),
    '#description' => t('The service account name credential. This is the email address that should look like xxxxxxxxxxxx-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx@developer.gserviceaccount.com'),
    '#required' => TRUE,
  );

  $form['google_cdn_connection_details']['google_cdn_bucket_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket Name'),
    '#default_value' => variable_get('google_cdn_bucket_name'),
    '#description' => t('The bucket name within Google Cloud Storage.'),
    '#required' => TRUE,
  );

  $form['google_cdn_connection_details']['google_cdn_folder'] = array(
    '#type' => 'textfield',
    '#title' => t('Folder Name'),
    '#default_value' => variable_get('google_cdn_folder'),
    '#description' => t('The folder name within Google Cloud Storage.'),
    '#required' => TRUE,
  );

  $form['google_cdn_library_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library Options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['google_cdn_library_options']['google_cdn_signed_url_expiry'] = array(
    '#type' => 'textfield',
    '#title' => t('Expiry'),
    '#default_value' => variable_get('google_cdn_signed_url_expiry'),
    '#description' => t('The amount of time in seconds that the signed url will expire. (Example: 300 = 5 minutes)'),
    '#required' => TRUE,
  );

  $versions = array(GOOGLE_CDN_LIBRARY_VERSION_067 => t('0.6.7'), GOOGLE_CDN_LIBRARY_VERSION_105BETA => t('1.0.5-beta'));
  $form['google_cdn_library_options']['google_cdn_library_version'] = array(
    '#type' => 'radios',
    '#title' => t('Library Version'),
    '#default_value' => variable_get('google_cdn_library_version'),
    '#description' => t('The Google PHP API library version in use.'),
    '#required' => TRUE,
    '#options' => $versions,
  );

  if (variable_get('google_cdn_public_key', NULL) != NULL) {
    $form['test_connection'] = array(
      '#type' => 'submit',
      '#value' => t('@test', array('@test' => GOOGLE_CDN_ADMIN_TEST_CONNECTION_BUTTON)),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('@save', array('@save' => GOOGLE_CDN_ADMIN_SUBMIT_BUTTON)),
    '#submit' => array('google_cdn_admin_submit'),
  );

  return $form;
}

/**
 * Hides the default upload button.
 *
 * @param array $element
 *   The remove element.
 * @param array $form_state
 *   The form state.
 * @param array $form
 *   The form array.
 *
 * @return mixed
 *   the form element.
 */
function google_cdn_admin_public_key_file_element_process($element, &$form_state, $form) {
  $element = file_managed_file_process($element, $form_state, $form);
  $element['upload_button']['#access'] = FALSE;

  if (isset($element['remove_button']['#submit'])) {
    $element['remove_button']['#submit'][] = 'google_cdn_delete_key_file';
  }

  return $element;
}

/**
 * Validates the admin form.
 *
 * Tests the credentials the user entered and responds with a message.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form_state array.
 */
function google_cdn_admin_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == GOOGLE_CDN_ADMIN_TEST_CONNECTION_BUTTON) {
    $info = libraries_load('google-api-php-client');
    $version = variable_get('google_cdn_library_version');
    if ($version && $info['loaded']) {
      $response = google_cdn_test_connection($version);
      if (empty($response)) {
        form_set_error('google_cdn_public_key_file', t('Error authenticating. Please check the Service Account Name, Key file and Bucket Name.'));
      }
      if ($response['access_token'] && $response['bucket']) {
        drupal_set_message('Success authenticating! We were able to connect to your Google Cloud Storage App.');
      }
    }
    else {
      form_set_error('', t("Google API Client Library for PHP was unable loaded."));
    }
  }
}

/**
 * Submit handler for admin form.
 *
 * Saves the variables and p12 key file. Also creates a PEM file for later use
 * in regards to signed urls.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form_state array.
 */
function google_cdn_admin_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == GOOGLE_CDN_ADMIN_SUBMIT_BUTTON) {
    variable_set('google_cdn_bucket_name', $form_state['values']['google_cdn_bucket_name']);
    variable_set('google_cdn_folder', $form_state['values']['google_cdn_folder']);
    variable_set('google_cdn_client_id', $form_state['values']['google_cdn_client_id']);
    variable_set('google_cdn_service_account_name', $form_state['values']['google_cdn_service_account_name']);
    variable_set('google_cdn_signed_url_expiry', $form_state['values']['google_cdn_signed_url_expiry']);
    variable_set('google_cdn_library_version', $form_state['values']['google_cdn_library_version']);
    google_cdn_admin_save_key_file($form, $form_state);
  }
}

/**
 * Saves the key file.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form_state array.
 */
function google_cdn_admin_save_key_file(&$form, &$form_state) {
  // Load the file.
  $file = file_load($form_state['values']['google_cdn_public_key_file']);
  // Change status to permanent.
  $file->status = FILE_STATUS_PERMANENT;
  $file->replace = FILE_EXISTS_REPLACE;
  $uploaded = file_save($file);
  global $user;
  $account = $user;
  // Record that the module is using the file.
  file_usage_add($file, 'google_cdn', 'admin', $account->uid);
  if ($uploaded) {
    $real_path = drupal_realpath($file->uri);
    variable_set('google_cdn_public_key', $file->fid);
    variable_set('google_cdn_public_key_file_path', $real_path);
    google_cdn_admin_save_pem_file($file, $real_path);
  }
}

/**
 * Creates and saves a PEM file.
 *
 * @param object $file
 *   The file object.
 * @param string $real_path
 *   The path to the file.
 */
function google_cdn_admin_save_pem_file($file, $real_path) {
  $path_to_pem = str_replace($file->filename, '', $real_path);
  $path_to_pem .= 'google_key.pem';
  $uri_to_pem = "private://google_cdn/google_key.pem";

  if (!file_exists($path_to_pem)) {
    $password = 'notasecret';
    $pkey_result = array();
    $pkcs12_read = openssl_pkcs12_read(file_get_contents($real_path), $pkey_result, $password);
    if ($pkcs12_read) {
      $new_password = 'notasecret';
      $pem_result = NULL;
      $pem_export = openssl_pkey_export($pkey_result['pkey'], $pem_result, $new_password);
      if ($pem_export) {
        // Save the file.
        file_put_contents($path_to_pem, $pem_result);

        global $user;
        // Create a record in managed files.
        $file = new stdClass();
        $file->fid = NULL;
        $file->uri = $uri_to_pem;
        $file->filename = drupal_basename($uri_to_pem);
        $file->filemime = file_get_mimetype($file->uri);
        $file->uid      = $user->uid;
        $file->status   = FILE_STATUS_PERMANENT;
        $file->replace = FILE_EXISTS_REPLACE;
        $file->size = filesize($path_to_pem);
        file_save($file);

        // Save information for later use.
        variable_set('google_cdn_pem_file_path', $path_to_pem);
        variable_set('google_cdn_pem_fid', $file->fid);
      }
    }
  }
}

/**
 * Remove the PEM file. Called when the user deletes the p12 key.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form_state array.
 */
function google_cdn_delete_key_file($form, &$form_state) {
  $pem_fid = variable_get('google_cdn_pem_fid');
  if ($pem_fid) {
    $file = file_load($pem_fid);
    if ($file) {
      file_delete($file);
      variable_del('google_cdn_pem_fid');
      variable_del('google_cdn_pem_file_path');
    }
    unset($file);
  }
  $p12_fid = variable_get('google_cdn_public_key');
  if ($p12_fid) {
    $file = file_load($p12_fid);
    if ($file) {
      file_usage_delete($file, 'google_cdn');
      file_delete($file);
      variable_del('google_cdn_public_key');
      variable_del('google_cdn_public_key_file_path');
    }
    unset($file);
  }
}
