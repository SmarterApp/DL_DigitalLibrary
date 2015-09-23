<?php
/* 
 * @file.
 * Includes forms for all admin settings pages.
 */

/**
 * Page callback: Google CDN variables.
 *
 * @see sbac_central_menu()
 */

function sbac_central_google_cdn_admin() {
  $form = array();

  $form['google_cdn_bucket_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket Name'),
    '#default_value' => variable_get('google_cdn_bucket_name', ''),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['google_cdn_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Extentions'),
    '#default_value' => variable_get('google_cdn_extensions', 'all'),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['google_cdn_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => variable_get('google_cdn_client_id', ''),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['google_cdn_service_account_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Account Name'),
    '#default_value' => variable_get('google_cdn_service_account_name', ''),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['google_cdn_signed_url_expiry'] = array(
    '#type' => 'textfield',
    '#title' => t('URL Expiry'),
    '#default_value' => variable_get('google_cdn_signed_url_expiry', ''),
    '#maxlength' => 4,
    '#size'=> 30,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['google_cdn_library_version'] = array(
    '#type' => 'textfield',
    '#title' => t('CDN Library Version'),
    '#default_value' => variable_get('google_cdn_library_version', '2'),
    '#maxlength' => 4,
    '#size'=> 30,
    '#description' => t(""),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Page callback: osCaddie GCS variables.
 *
 * @see sbac_central_menu()
 */

function sbac_central_oscaddie_admin() {
  $form = array();

  $form['oscaddie_gcs_bucket_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket Name'),
    '#default_value' => variable_get('oscaddie_gcs_bucket_name', ''),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['oscaddie_gcs_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Extentions'),
    '#default_value' => variable_get('oscaddie_gcs_extensions', 'all'),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['oscaddie_gcs_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => variable_get('oscaddie_gcs_client_id', ''),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['oscaddie_gcs_service_account_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Account Name'),
    '#default_value' => variable_get('oscaddie_gcs_service_account_name', ''),
    '#maxlength' => 128,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['oscaddie_gcs_signed_url_expiry'] = array(
    '#type' => 'textfield',
    '#title' => t('URL Expiry'),
    '#default_value' => variable_get('oscaddie_gcs_signed_url_expiry', ''),
    '#maxlength' => 4,
    '#description' => t(""),
    '#required' => TRUE,
  );
  $form['oscaddie_gcs_library_version'] = array(
    '#type' => 'textfield',
    '#title' => t('Library Version'),
    '#default_value' => variable_get('oscaddie_gcs_library_version', '2'),
    '#maxlength' => 2,
    '#description' => t(""),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Page callback: osCaddie GCS variables.
 *
 * @see sbac_central_menu()
 */
function sbac_central_google_cdn_migrate_admin(){
$form['warning'] = array(
  '#markup' => '<h1>' . t('DO NOT USE UNLESS YOU KNOW <em>EXACTLY</em> WHAT THIS DOES!') . '</h1>',
);

  $form['submit'] = array('#type' => 'submit', '#value' => t('Upgrade Files - PROCEED WITH CAUTION!'));
  $form['#submit'][] = 'sbac_central_migrate_files';

  return $form;
}