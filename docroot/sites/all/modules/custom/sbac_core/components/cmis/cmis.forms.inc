<?php

/**
 * Page callback for admin/sbac/cmis-server-conf
 *
 * @return Form cmis configuration
 */
function sbac_core_cmis_server_conf() {
  // Dont know why hook menu wouldnt register drupal_get_form right away.
  $output = drupal_get_form('sbac_core_cmis_server_form');
  return $output;
}

function _sbac_core_cmis__get_cred_keys() {
  $output = array(
    'user' => 1,
    'password'  => 1,
    'update_url' => 1,
    'zip_url' => 1,
    'login_url' => 1,
    'get_url' => 1,
    'label' => 1,
    'url' => 1,
    'transport' => 1,
    'headerswing_headers' => array(
      'HTTP_HOST',
      'HTTP_HOST',
      'HTTP_USER',
      'PHP_AUTH_USER',
      'PHP_AUTH_DIGEST',
    ),
  );
  return $output;
}

function _sbac_core_cmis__get_cred_defaults() {
  $defaults = variable_get('sbac_core_cmis_creds_default', array());
  $sub_array = array();
  foreach ($defaults as $key => $value) {
    if (is_array($value)) {
      $sub_array = $value;
      unset($defaults[$key]);
    }
  }
  if (!empty($sub_array)) {
    $defaults += $sub_array;
  }
  return $defaults;
}

function sbac_core_cmis_server_form($form, $form_state) {
  $form = array();

  $keys = _sbac_core_cmis__get_cred_keys();
  $defaults = _sbac_core_cmis__get_cred_defaults();
  $count = 0;
  // **
  //   In case encryption of the password is needed.
  //     See submit handler as well. sbac_core_cmis_server_form_submit
  //     Patch for cmis.module also needs to be applied to pull value and decrypt
  // **
  // global $drupal_hash_salt;
  // $pw_is_hashed = variable_get('sbac_core_cmis_pw_hashed', FALSE);
  // if ($pw_is_hashed && (!empty($defaults['password']))) {
  //   if (function_exists('mcrypt_decrypt')) {
  //     $salt = $drupal_hash_salt;
  //     $unhashed = rtrim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $salt, $defaults['password'], MCRYPT_MODE_ECB));
  //     $defaults['password'] = $unhashed;
  //   }
  // }

  // Show the value of the current variable.
  $form['current_cmis_repo_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Current CMIS Repository Info'),
    '#weight' => $count,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $def_val = variable_get('cmis_repositories', array());
  $current_repo_value = '<xmp>'. var_export($def_val, 1) .'</xmp>';
  $form['current_cmis_repo_info']['current_cmis_repo_value'] = array(
    '#markup' => $current_repo_value,
  );

  foreach ($keys as $key => $key_value) {
    $key_label = ucwords(str_replace('_', ' ', $key));
    $key_label .= ' (machine name: ' . $key . ')';
    if (is_array($key_value)) { // Put into a fieldset.
      $form[$key] = array(
        '#type' => 'fieldset',
        '#title' => t($key_label),
        '#weight' => $count,
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
      );
      foreach ($key_value as $key_child_id) {
        $key_child_label = ucwords(str_replace('_', ' ', $key_child_id));
        $key_child_label .= $key_child_label;
        $form[$key][$key_child_id] = array(
          '#type' => 'textfield',
          '#title' => t($key_child_label),
          '#default_value' => $defaults[$key_child_id],
          '#size' => 60,
          '#maxlength' => 256,
          '#required' => TRUE,
          '#weight' => $count,
        );
        $count++;
      }
    } else {
      $form[$key] = array(
        '#type' => 'textfield',
        '#title' => t($key_label),
        '#default_value' => $defaults[$key],
        '#size' => 60,
        '#maxlength' => 256,
        '#required' => TRUE,
        '#weight' => $count,
      );
    }
    $count++;
  }

  $form['password']['#type'] = 'password';

  $count++;
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Repository Info'),
    '#weight' => $count,
  );

  return $form;
}

function sbac_core_cmis_server_form_submit($form, &$form_state) {
  $keys = _sbac_core_cmis__get_cred_keys();
  $values = $form_state['values'];
  $final_variable = array();
  foreach ($keys as $key => $key_value) {
    if (is_array($key_value)) { // Put into a fieldset.
      $sub_field = array();
      foreach ($key_value as $key_child_id) {
        $sub_field[$key_child_id] = $values[$key_child_id];
      }
      $final_variable[$key] = $sub_field;
    } else { // Get raw value
      $final_variable[$key] = $values[$key];
    }
  }

  // if (function_exists('mcrypt_encrypt')) {
  //   global $drupal_hash_salt;
  //   $salt = $drupal_hash_salt;
  //   $raw_pw = $final_variable['password'];
  //   $encrypted = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $raw_pw, MCRYPT_MODE_ECB);
  //   $final_variable['password'] = $encrypted;
  //   variable_set('sbac_core_cmis_pw_hashed', TRUE);
  // }

  // Store one version of the variable thats easily consumed by form api to set field defaults.
  variable_set('sbac_core_cmis_creds_default', $final_variable);

  // Update the variable that cmis uses to track repo information.
  $defaults = $final_variable;
  $output = array(
    'default' => $defaults,
  );
  variable_set('cmis_repositories', $output);

  drupal_set_message('CMIS Repository Connection Information Updated.');
}
