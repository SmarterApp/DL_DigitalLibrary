<?php

/*----------------------------------------------------------------------------
      CALLBACKS
----------------------------------------------------------------------------*/

/**
 * Callback for admin/sbac/users/profile
 */
function user_profile_account_admin_form($form, &$form_state) {
  $help_content = variable_get('user_account_help', input_default_full_html());
  $form['user_account_help'] = array(
    '#title' => t('Helpful Information'),
    '#type' => 'text_format',
    '#default_value' => $help_content['value'],
    '#format' => $help_content['format'],
    '#description' => t('The Helpful Information text is displayed at the top of the Account
      tab on the user profile.'),
  );

  return system_settings_form($form);
}

/**
 * Callback for admin/sbac/users/profile/activity
 */
function user_profile_activity_admin_form($form, &$form_state) {
  $help_content = variable_get('user_activity_help', input_default_full_html());
  $form['user_activity_help'] = array(
    '#title' => t('Helpful Information'),
    '#type' => 'text_format',
    '#default_value' => $help_content['value'],
    '#format' => $help_content['format'],
    '#description' => t('The Helpful Information text is displayed at the top of the Activity
      tab on the user profile.'),
  );

  return system_settings_form($form);
}

/**
 * Callback for admin/sbac/users/profile/notifications
 */
function user_profile_notifications_admin_form($form, &$form_state) {
  $help_content = variable_get('user_notifications_help', input_default_full_html());
  $form['user_notifications_help'] = array(
    '#title' => t('Helpful Information'),
    '#type' => 'text_format',
    '#default_value' => $help_content['value'],
    '#format' => $help_content['format'],
    '#description' => t('The Helpful Information text is displayed at the top of the Notifications
      tab on the user profile.'),
  );

  return system_settings_form($form);
}