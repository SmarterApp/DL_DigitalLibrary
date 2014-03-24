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

  $form['google_cdn_public_key_file'] = array(
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

  $form['google_cdn_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Account Client ID'),
    '#default_value' => variable_get('google_cdn_client_id'),
    '#description' => t('The service account client ID credential. Should follow this pattern "xxxxxxxxxxxx-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.apps.googleusercontent.com"'),
    '#required' => TRUE,
  );

  $form['google_cdn_service_account_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Account Name'),
    '#default_value' => variable_get('google_cdn_service_account_name'),
    '#description' => t('The service account name credential. This is the email address that should look like xxxxxxxxxxxx-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx@developer.gserviceaccount.com'),
    '#required' => TRUE,
  );

  $form['google_cdn_bucket_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket Name'),
    '#default_value' => variable_get('google_cdn_bucket_name'),
    '#description' => t('The bucket name within Google Cloud Storage.'),
    '#required' => TRUE,
  );

  $form['google_cdn_folder'] = array(
    '#type' => 'textfield',
    '#title' => t('Folder Name'),
    '#default_value' => variable_get('google_cdn_folder'),
    '#description' => t('The folder name within Google Cloud Storage.'),
    '#required' => TRUE,
  );

  $form['google_cdn_extensions'] = array(
    '#type' => 'textarea',
    '#title' => t('File Extensions'),
    '#default_value' => variable_get('google_cdn_extensions'),
    '#description' => t('The file extensions to copy to the Google Cloud Storage bucket.'),
    '#required' => TRUE,
    '#rows' => 10,
    '#cols' => 90,
  );

  if (variable_get('google_cdn_public_key', NULL) != NULL) {
    $form['test_connection'] = array(
      '#type' => 'submit',
      '#value' => t(GOOGLE_CDN_ADMIN_TEST_CONNECTION_BUTTON),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t(GOOGLE_CDN_ADMIN_SUBMIT_BUTTON),
    '#submit' => array('google_cdn_admin_submit'),
  );

  return $form;
}

/**
 * Hides the default upload button.
 *
 * @param $element
 * @param $form_state
 * @param $form
 * @return mixed
 */
function google_cdn_admin_public_key_file_element_process($element, &$form_state, $form) {
  $element = file_managed_file_process($element, $form_state, $form);
  $element['upload_button']['#access'] = FALSE;
  return $element;
}

/**
 * Validates the admin form.
 *
 * Tests the credentials the user entered and responds with a message.
 *
 * @param $form
 * @param $form_state
 */
function google_cdn_admin_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == GOOGLE_CDN_ADMIN_TEST_CONNECTION_BUTTON) {
    $info = libraries_load('google-api-php-client');
    if ($info['loaded']) {
      $google_cdn_service_account_name = variable_get('google_cdn_service_account_name');
      $google_cdn_key_file_path = variable_get('google_cdn_public_key_file_path');
      $google_cdn_bucket_name = variable_get('google_cdn_bucket_name');

      try {
        $client = new Google_Client();
        // Replace this with your application name.
        $client->setApplicationName($google_cdn_service_account_name);
        // Replace this with the service you are using.
        $service = new Google_StorageService($client);
        // This file location should point to the private key file.
        $key = file_get_contents($google_cdn_key_file_path);
        $cred = new Google_AssertionCredentials(
        // Replace this with the email address from the client.
          $google_cdn_service_account_name,
          // Replace this with the scopes you are requesting.
          array('https://www.googleapis.com/auth/devstorage.read_write'),
          $key
        );

        $client->setAssertionCredentials($cred);
        if($client->getAuth()->isAccessTokenExpired()) {
          $client->getAuth()->refreshTokenWithAssertion($cred);
        }
        $access_token = $client->getAccessToken();
        $bucket_info = $service->buckets->get($google_cdn_bucket_name);

        if ($access_token && $bucket_info) {
          drupal_set_message('Success authenticating! We were able to connect to your Google Cloud Storage App.');
        }

      } catch (Exception $e) {
        watchdog_exception('google_cdn', $e);
        form_set_error('google_cdn_public_key_file', t('Error authenticating. Please check the Service Account Name, Key file and Bucket Name.'));
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
 * @param $form
 * @param $form_state
 */
function google_cdn_admin_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == GOOGLE_CDN_ADMIN_SUBMIT_BUTTON) {
    variable_set('google_cdn_bucket_name', $form_state['values']['google_cdn_bucket_name']);
    variable_set('google_cdn_folder', $form_state['values']['google_cdn_folder']);
    variable_set('google_cdn_extensions', $form_state['values']['google_cdn_extensions']);
    variable_set('google_cdn_client_id', $form_state['values']['google_cdn_client_id']);
    variable_set('google_cdn_service_account_name', $form_state['values']['google_cdn_service_account_name']);

    // Load the file.
    $file = file_load($form_state['values']['google_cdn_public_key_file']);
    // Change status to permanent.
    $file->status = FILE_STATUS_PERMANENT;
    $file->replace = FILE_EXISTS_REPLACE;
    // Save.
    $uploaded = file_save($file);
    // Record that the module is using the file.
    global $user;
    $account = $user;
    file_usage_add($file, 'google_cdn', 'admin', $account->uid);
    if ($uploaded) {
      variable_set('google_cdn_public_key', $file->fid);
      $real_path = drupal_realpath($file->uri);
      variable_set('google_cdn_public_key_file_path', $real_path);

      // Create the PEM file using PHP: openssl pkcs12 -in path/to/key.p12 -nodes -nocerts > path/to/key.pem
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
            // save the file.
            file_put_contents($path_to_pem, $pem_result);

            // create a record in Druapl managed files.
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

            // save information for later use.
            variable_set('google_cdn_pem_file_path', $path_to_pem);
            variable_set('google_cdn_pem_fid', $file->fid);
          }
        }
      }
    }
  }
}
