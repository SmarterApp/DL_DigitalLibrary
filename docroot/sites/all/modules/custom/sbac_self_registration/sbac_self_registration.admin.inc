<?php

/**
 * @file
 * Forms for sbac_self_registration screens
 */

/**
 * Self regsitration form
 *
 * @param array $form All form elements that are contained in self registration form
 * @param array $form_state All form functions that are contained in self registration form
 * @return array self registration form
 */
function sbac_self_registration_form($form, &$form_state) {

  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#collapsible' => TRUE
  );

  $form['browser']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#required' => TRUE,
  );

  $form['browser']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#required' => TRUE,
    '#description' => t("Enter your first and last name as they appear in your institution's records."),
  );


  $form['browser']['e-mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail Address'),
    '#required' => TRUE,
    '#description' => t('Email address must be from an authorized educational institution (school, district, etc.)'),
  );

  $form['scan'] = array(
    '#type' => 'submit',
    '#value' => t('Register'),
  );

  return $form;
}

/**
 * Check whether the Email address is in correct form
 *
 * @param array $form All form elements that are contained in self registration form
 * @param array $form_state All form functions that are contained in self registration form
 */
function sbac_self_registration_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['e-mail'])) {
    form_set_error('e-mail', 'This is an invalid email address.');
  }
}

/**
 * Submit action in self registration form
 *
 * @param array $form All form elements that are contained in self registration form
 * @param array $form_state All form functions that are contained in self registration form
 */
function sbac_self_registration_form_submit($form, &$form_state) {
  // Grab the form fields
  $first_name = $form_state['values']['first_name'];
  $last_name = $form_state['values']['last_name'];
  $email = $form_state['values']['e-mail'];
  // Create new emailer
  $emailer = new sbacEmails($email);
  // Check to see if the user's domain is valid
  $domain_valid = _sbac_self_registration_check_domain($email);
  // Check to see if the user exists
  $sbac_user = sbac_art_api_get_user($email, FALSE);
  // If they do, check to see if they have the DL role
  if ($sbac_user) {
    // Check to see if the user has the DL_EndUser role
    $role_exists = FALSE;
    foreach ($sbac_user['roleAssociations'] as $key => $association) {
      if ($association['role'] =='DL_EndUser') {
        $role_exists = TRUE;
      }
    }
    // If they have the DL role, send them a password reset email
    if ($role_exists) {
      $token = _sbac_self_registration_token_encode($email);
      $emailer->send_sr_user_exists_mail($first_name, $last_name, url('/verify-email/', array('absolute' => TRUE, 'query' => array('token' => $token))));
    } else {
      // If they don't have the DL role, and their domain is valid, add the role
      if ($domain_valid) {
        $domain_info = _sbac_self_registration_get_domain_info($email);
        $new_user_json = sbac_art_api_user_update_json($sbac_user, $domain_info['state'], $domain_info['district']);
        sbac_art_api_set_user($new_user_json);
        $emailer->send_sr_missing_role_mail($first_name, $last_name);
      } else {
        // If their domain isn't valid,  send an email saying they need manual intervention and log the unauthorized domain
        $emailer->send_sr_unauthorized_mail($first_name, $last_name);

        $email_parts = explode('@', $email);
        $domain = $email_parts[1];
        sbac_self_registration_add_unauthorized_domain($domain);
      }
    }
  } else {
    // If they don't exist, and their domain is valid, add them
    if ($domain_valid) {
      $domain_info = _sbac_self_registration_get_domain_info($email);
      $user_json = sbac_art_api_user_create_json($first_name, $last_name, $email, $domain_info['state'], $domain_info['district']);
      sbac_art_api_set_user($user_json);
    } else {
      // If their domain isn't valid,  send an email saying they need manual intervention and log the unauthorized domain
      $emailer->send_sr_unauthorized_mail($first_name, $last_name);

      $email_parts = explode('@', $email);
      $domain = $email_parts[1];
      sbac_self_registration_add_unauthorized_domain($domain);
    }
  }
  drupal_goto('/self-registration-processing');
}

/**
 * Add one unauthorized domain item and increase the access count
 *
 * @param string $domain The unauthorized domain
 */
function sbac_self_registration_add_unauthorized_domain($domain) {
    $unauthorized_domain_result = db_select('unauthorized_domain_audit', 'c')
      ->fields('c')
      ->condition('domain', $domain, '=')
      ->execute()
      ->fetchAssoc();
    if (empty($unauthorized_domain_result)) {
        db_insert('unauthorized_domain_audit')
          ->fields(array(
            'domain' => $domain,
            'accesscount' => 1,
            'date' => time(),
            'timeupdated' => time())
          )
          ->execute();
    } else {
        db_update('unauthorized_domain_audit')
          ->condition('domain', $domain)
          ->fields(array(
            'accesscount' => intval($unauthorized_domain_result['accesscount']) + 1,
            'timeupdated' => time())
          )
          ->execute();
    }
}

/**
 * Create self-Registration Success message page
 *
 * @return array Self-Registration Success message page
 */
function sbac_self_registration_processing() {
  $output = array(
    'registration' => array(
      '#type' => 'markup',
      '#markup' => t('Your information has been sent to the Digital Library. You will be receiving a welcome email shortly.'),
    )
  );

  return $output;
}

/**
 * Create Email verification form
 *
 * @param array $form All form elements that are contained in Email verification form
 * @param array $form_state All form functions that are contained in Email verification form
 * @param string $email The Email will be verified
 * @return array Email verification form
 */
function sbac_self_registration_verify_email_form($form, &$form_state, $email) {
  if (!$email) {
    $email = '';
  }

  $form['info'] = array(
    '#markup' => t('Please verify your email address.')
  );

  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#collapsible' => TRUE
  );

  $form['browser']['e-mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail Address'),
    '#required' => TRUE,
    '#disabled' => TRUE,
    '#default_value' => $email,
  );

  $form['scan'] = array(
    '#type' => 'submit',
    '#value' => t('Verify'),
  );

  return $form;
}

/**
 * Check whether the Email address is in correct form
 *
 * @param array $form All form elements that are contained in Email verification form
 * @param array $form_state All form functions that are contained in Email verification form
 */
function sbac_self_registration_verify_email_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['e-mail'])) {
    form_set_error('e-mail', 'This is an invalid email address.');
  }
}

/**
 * Verify button
 *
 * @param array $form All form elements that are contained in Email verification form
 * @param array $form_state All form functions that are contained in Email verification form
 */
function sbac_self_registration_verify_email_form_submit($form, &$form_state) {
  $result = sbac_art_api_reset_password($form_state['values']['e-mail']);
  drupal_goto('/verify-email-processing');
}

/**
 * Check if the link expires after 72 hours
 *
 * @return array if reset password token is expired then return to password reset failure message page else return to Email verification form
 */
function sbac_self_registration_verify_email() {
  $params = drupal_get_query_parameters();
  $token = $params['token'];
  $token_info = _sbac_self_registration_token_decode($token);
  if (!$token_info || empty($token_info['email']) || !valid_email_address($token_info['email'])) {
    $reset_link = l(t('click here'), '/reset-password/');
    $output = array(
      'expired' => array(
        '#type' => 'markup',
        '#markup' => t('This token is invalid. If you need to reset your password, please !link.', array('!link' => $reset_link)),
      )
    );
    return $output;
  } elseif (($token_info && $token_info['expiration'] <= time())) {
    $reset_link = l(t('click here'), '/reset-password-token/' . urlencode($token_info['email']));
    $output = array(
      'expired' => array(
        '#type' => 'markup',
        '#markup' => t('This link has expired. Please !link to send a new email.', array('!link' => $reset_link)),
      )
    );
    return $output;
  }
  $form = drupal_get_form('sbac_self_registration_verify_email_form', $token_info['email']);
  return $form;
}

/**
 * Create Password Reset Success message page
 *
 * @return array Password Reset Success message page
 */
function sbac_self_registration_verify_email_processing() {
  $output = array(
    'reset' => array(
      '#type' => 'markup',
      '#markup' => 'Your password has been reset. You will receive an email with further instructions shortly.'
    )
  );
  return $output;
}

/**
 * Create password reset form
 *
 * @param array $form All form elements that are contained in password reset form
 * @param array $form_state All form functions that are contained in password reset form
 * @return array password reset form
 */
function sbac_self_registration_reset_password_form($form, &$form_state) {

  $form['info'] = array(
    '#markup' => t('Please enter your email address.')
  );

  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#collapsible' => TRUE
  );

  $form['browser']['e-mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail Address'),
    '#required' => TRUE,
    '#description' => t('Enter the email address you use to access Smarter Balanced and the Digital Library.'),
  );

  $form['scan'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );

  return $form;
}

/**
 * Check whether the Email address is in correct form
 *
 * @param array $form All form elements that are contained in password reset form
 * @param array $form_state All form functions that are contained in password reset form
 */
function sbac_self_registration_reset_password_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['e-mail'])) {
    form_set_error('e-mail', 'This is an invalid email address.');
  }
}

/**
 * Reset button in password reset form page
 *
 * @param array $form All form elements that are contained in password reset form
 * @param array $form_state All form functions that are contained in password reset form
 */
function sbac_self_registration_reset_password_form_submit($form, &$form_state) {
  $email = $form_state['values']['e-mail'];
  $sbac_user = sbac_art_api_get_user($email);
  $emailer = new sbacEmails($email);
  if ($sbac_user) {
    $token = _sbac_self_registration_token_encode($email);
    $emailer->send_pr_reset_mail(url('/verify-email/', array('absolute' => TRUE, 'query' => array('token' => $token))));
  } else {
    $domain_valid = _sbac_self_registration_check_domain($email);
    if ($domain_valid) {
      $emailer->send_pr_register_mail();
    } else {
      $emailer->send_pr_unauthorized_mail();
    }
  }
  drupal_goto('/reset-password-processing');
}

/**
 * Create password reset success message page
 *
 * @return array password reset success message page
 */
function sbac_self_registration_reset_password_processing() {

  $output = array(
    'reset' => array(
      '#type' => 'markup',
      '#markup' => t('Your email needs to be verified. You will receive an email with further instructions shortly.')
    )
  );

  return $output;
}

/**
 * Embed Email Verification Token and send password reset Email then redirect to Password Reset Success message page
 *
 * @param string $email Receive reset password email
 */
function sbac_self_registration_reset_password_token($email) {
  $emailer = new sbacEmails($email);
  $token = _sbac_self_registration_token_encode($email);
  $emailer->send_pr_reset_mail(url('/verify-email/', array('absolute' => TRUE, 'query' => array('token' => $token))));

  drupal_goto('/reset-password-processing');
}
