<?php

/**
 * Individual Report filter form.
 */
function sbac_report_individual_form($form, &$form_state) {
  global $user;
  $account = user_load($user->uid);

  $form = array();

  // Make sure to load this after autocomplete.js
  // @see sbac_report.individual.js
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'sbac_report') .
    '/js/sbac_report.individual.js' => array('weight' => 99),
  );

  $form['state'] = array(
    '#type' => 'select',
    '#title' => t('Choose a state'),
    '#options' => sbac_report_state_options(),
    '#multiple' => FALSE,
    '#disabled' => !sbac_report_user_access_all($account) || sbac_central_user_has_role(array('reports administrator')),
    '#default_value' => sbac_report_get_default_state_tid(),
    '#ajax' => array(
      'callback' => 'sbac_report_state_ajax',
    ),
    '#required' => TRUE,
  );
  if (!isset($_SESSION['sbac_report']['first_time']) || !$_SESSION['sbac_report']['first_time']) {
    $_SESSION['sbac_report']['error_message'] = '';
  }
  else {
    $_SESSION['sbac_report']['first_time']=0;
  }

  $date_options = sbac_report_date_range_options();
  $session_date_range = sbac_report_get_session_value('date_range', 'range');

  // If there was no date range stored in SESSION.
  // Default to the "Cumulative to date".
  if (empty($session_date_range)) {
    $session_date_range = $date_options['Cumulative to date'];
    $date_display = t('Cumulative to date');
  }
  // If there is, we get the display text "Last 60 Days", "Last 90 Days", etc.
  elseif ($key = array_search($session_date_range, $date_options)) {
    $date_display = t($key);
  }
  // If it was a custom selection, format the string.
  else {
    $date_display = sbac_report_format_date_range($session_date_range);
  }

  $see_others = sbac_report_select_other_users($account);
  $name_value = sbac_user_format_username($user);
  $form['sne'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose a Contributor or Reviewer'),
    '#autocomplete_path' => 'sne/autocomplete',
    '#required' => TRUE,
    '#size' => 30,
    '#disabled' => !$see_others,
    '#default_value' => $see_others ? sbac_report_get_session_value('sne', 'name') : $name_value,
    '#attributes' => array('aria-required' => "true"),
  );

  sbac_report_build_date_range_dropdown($form, $session_date_range, $date_display, $date_options, '');

  // Hidden field to store the selected uid.
  // When the autocomplete suggetion is selected,
  // the uid value will be set here.
  // @see sbac_report.js
  $form['uid'] = array(
    '#type' => 'hidden',
    '#default_value' => $see_others ? sbac_report_get_session_value('sne', 'uid') : $user->uid,
    '#attributes' => array(
      'id' => 'sne-uid-field',
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('sbac_report_individual_form_submit'),
  );

  $form['#validate'][] = 'sbac_report_individual_form_validate';

  return $form;
}

/**
 * Individual Report: form validate.
 */
function sbac_report_individual_form_validate($form, &$form_state) {
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_INDIVIDUAL;

  global $user;
  if (empty($form_state['values']['uid']) || !is_numeric($form_state['values']['uid'])) {
    $account = user_load($user->uid);
    if (!sbac_report_select_other_users($account)) {
      $form_state['values']['uid'] = $user->uid;
    }
    else {
      form_set_error('sne', t('Please type and select an existing SNE'));
    }
  }

  if (empty($form_state['values']['date_range'])) {
    form_set_error('date_range', t('Choose a time period field is required.'));
  }

  if (sbac_central_user_has_role(array('reports administrator'))) {
    if ($form_state['values']['state'] != sbac_report_get_default_state_tid()) {
      form_set_error('state', t('You\'re only allowed to select your own state'));
    }
  }
}

/**
 * Individual Report: Form submit.
 * Store in SESSION:
 * $_SESSION['sbac_report'] = array(
 *   'state' => array('name' => 'California', 'tid' => 123),
 *   'date_range' => array('range' => '20130515--20140515'),
 *   'sne' => array('uid' => 1, 'name' => 'first last'),
 * );
 */
function sbac_report_individual_form_submit($form, &$form_state) {
  // State.
  if (isset($form_state)) {
    $state_tid = $form_state['values']['state'];
    // Numeric state term id
    $_SESSION['sbac_report']['state']['tid'] = $state_tid;
    
    // Friendly name of state term
    if (!is_numeric($state_tid) && $state_tid == 'all') {
      $_SESSION['sbac_report']['state']['name'] = 'all';
    }
    else {
      $state_options = $form['state']['#options'];
      $_SESSION['sbac_report']['state']['name'] = $state_options[$state_tid];
    }

    // Time range.
    $_SESSION['sbac_report']['date_range']['range'] = $form_state['values']['date_range'];

    // SNE.
    $_SESSION['sbac_report']['sne']['uid'] = $form_state['values']['uid'];
    $_SESSION['sbac_report']['sne']['name'] = $form_state['values']['sne'];
  }
}
