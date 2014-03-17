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

  $form['google_cdn_public_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Public Key'),
    '#default_value' => variable_get('google_cdn_public_key', ''),
    '#description' => t('The public key to Google Cloud Storage.'),
    '#required' => TRUE,
  );

  $form['google_cdn_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Cloud Storage URI'),
    '#description' => t('The URI that points to your google cloud store.'),
    '#default_value' => variable_get('google_cdn_uri', ''),
  );

  $form['google_cdn_bucket_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket Name'),
    '#default_value' => variable_get('google_cdn_bucket_name', ''),
    '#description' => t('The bucket name within Google Cloud Storage.'),
    '#required' => TRUE,
  );

  $form['google_cdn_extensions'] = array(
    '#type' => 'textarea',
    '#title' => t('File Extensions'),
    '#default_value' => variable_get('google_cdn_extensions', ''),
    '#description' => t('The file extensions to copy to the Google Cloud Storage bucket.'),
    '#required' => TRUE,
    '#rows' => 10,
    '#cols' => 90,
  );

  return system_settings_form($form);
}

/**
 * Validate the admin form.
 */
function google_cdn_admin_validate($form, &$form_state) {
  $bucket = $form_state['values']['google_cdn_bucket'];
  $cloudfront = $form_state['values']['google_cdn_cloudfront'];

  if ($cloudfront) {
    $keypair = variable_get('aws_cloudfront_keypair', '');
    $pem = variable_get('aws_cloudfront_pem', '');
    if (empty($keypair) || empty($pem)) {
      form_set_error('google_cdn_cloudfront', t('You must configure your CloudFront credentials in the awksdk module.'));
    }
  }

  if (!libraries_load('awssdk')) {
    form_set_error('google_cdn_bucket', t('Unable to load the AWS SDK. Please check you have installed the library correctly and configured your S3 credentials.'));
  }
  elseif (!class_exists('google_cdn')) {
    form_set_error('google_cdn_bucket', t('Cannot load google_cdn class. Please check the awssdk is installed correctly'));
  }
  else {
    try {
      $s3 = new google_cdn();
      $response = $s3->list_objects($bucket, array(
        'max-keys' => 1,
      ));
      if (!$s3->if_bucket_exists($bucket) || !$response->isOK()) {
        form_set_error('google_cdn_bucket', t('The S3 access credentials are invalid or the bucket does not exist'));
      }
    }
    catch (RequestCore_Exception $e) {
      if (strstr($e->getMessage(), 'SSL certificate problem')) {
        form_set_error('google_cdn_bucket', t('There was a problem with the SSL certificate. Try setting AWS_CERTIFICATE_AUTHORITY to true in "libraries/awssdk/config.inc.php". You may also have a curl library (e.g. the default shipped with MAMP) that does not contain trust certificates for the major authorities. The following exception was thrown: @exception'), array('@exception' => $e->getMessage()));
      }
      else {
        form_set_error('google_cdn_bucket', t('There was a problem connecting to S3. The following exception was thrown: @exception'), array('@exception' => $e->getMessage()));
      }

    }
    catch (Exception $e) {
      form_set_error('google_cdn_bucket', t('There was a problem using S3. The following exception was thrown: @exception'), array('@exception' => $e->getMessage()));
    }
  }
}