<?php

/**
 * Individual Report filter form.
 */
function sbac_report_individual_form($form, &$form_state) {
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
    '#default_value' => sbac_report_get_default_state_tid(),
    '#ajax' => array(
      'callback' => 'sbac_report_state_ajax',
    ),
    '#required' => TRUE,
  );

  $date_options = sbac_report_date_range_options();
  $session_date_range = sbac_report_get_session_value('date_range', 'range');

  // If there was no date range stored in SESSION.
  // Default to the "Last 30 Days".
  if (empty($session_date_range)) {
    $session_date_range = $date_options['Last 30 Days'];
    $date_display = t('Last 30 Days');
  }
  // If there is, we get the display text "Last 60 Days", "Last 90 Days", etc.
  elseif ($key = array_search($session_date_range, $date_options)) {
    $date_display = t($key);
  }
  // If it was a custom selection, format the string.
  else {
    $date_display = sbac_report_format_date_range($session_date_range);
  }

  sbac_report_build_date_range_dropdown($form, $session_date_range, $date_display, $date_options, '');

  $form['sne'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose a SNE'),
    '#autocomplete_path' => 'sne/autocomplete',
    '#required' => TRUE,
    '#size' => 30,
    '#default_value' => sbac_report_get_session_value('sne', 'name'),
  );

  // Hidden field to store the selected uid.
  // When the autocomplete suggetion is selected,
  // the uid value will be set here.
  // @see sbac_report.js
  $form['uid'] = array(
    '#type' => 'hidden',
    '#default_value' => sbac_report_get_session_value('sne', 'uid'),
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
  if (empty($form_state['values']['uid']) || !is_numeric($form_state['values']['uid'])) {
    form_set_error('sne', t('Please type and select an existing SNE'));
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
function sbac_report_individual_form_submit($form=null, &$form_state=null) {
  // State.
  if (isset($form_state)) {
    $state_tid = $form_state['values']['state'];
    $_SESSION['sbac_report']['state']['tid'] = $state_tid;
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
  // Get SESSION values.
  $uid = sbac_report_get_session_value('sne', 'uid');
  $state_tid = sbac_report_get_session_value('state', 'tid');
  $date_range = sbac_report_get_session_value('date_range', 'range');
  $sne_details = '';
  $contributed_summary = '';
  $contributed_details = '';
  $gate_keeping = '';
  $all_reviews = '';
  $summation = '';
  if (!empty($uid) && !empty($date_range) && !empty($state_tid)) {
    $sne_details = sbac_report_embed_view('sne_details', 'sne_details', $uid, $state_tid);
    // If there are no SNE with the selected state and uid. Display none.
    // @todo: custom message if there's no result.
    if (!empty($sne_details)) {
      $contributed_summary = views_embed_view('contributed_resources', 'resources_summary', $uid, $date_range);
      $contributed_details = views_embed_view('contributed_resources', 'resources_details', $uid, $date_range);

      // Gate-Keeping Reviews.
      $name = sbac_report_get_session_value('sne', 'name');
      $gk_ind_accepted = sbac_report_get_ind_accepted_gate_keeper($uid, $date_range);
      $gk_ind_returned = sbac_report_get_ind_returned_gate_keeper($uid, $date_range);
      $gk_all_accepted = sbac_report_get_all_accepted_gate_keeper($date_range);
      $gk_all_returned = sbac_report_get_all_returned_gate_keeper($date_range);
      $gate_keeping = sbac_report_build_gk_table($name, $gk_ind_accepted, $gk_ind_returned, $gk_all_accepted, $gk_all_returned);

      // All Reviews.
      $reviews_in_progress = sbac_report_get_in_reviews($uid, $date_range);
      $completed_reviews = sbac_report_get_completed_reviews($uid, $date_range);
      // $reviews = array_merge($reviews_in_progress, $completed_reviews);
      $average_consistency_rate = sbac_report_get_average_consistency_rate_acr($uid, $completed_reviews);
      $all_reviews = sbac_report_build_ar_table($reviews_in_progress, $completed_reviews, $average_consistency_rate);

      // The big 'summation' table.
      $summation = sbac_report_build_summation_table($uid, $date_range);
      $_SESSION['sbac_report']['summation'] = $summation;
      $_SESSION['sbac_report']['sne_details'] = $sne_details;
      $_SESSION['sbac_report']['contributed_summary'] = $contributed_summary;
      $_SESSION['sbac_report']['contributed_details'] = $contributed_details;
      $_SESSION['sbac_report']['gate_keeping'] = $gate_keeping;
      $_SESSION['sbac_report']['all_reviews'] = $all_reviews;
      $_SESSION['sbac_report']['error_message'] = '';
      $_SESSION['sbac_report']['active_tab'] = 0;
      return;
    }

  }
  $_SESSION['sbac_report']['summation'] = $summation;
  $_SESSION['sbac_report']['sne_details'] = $sne_details;
  $_SESSION['sbac_report']['contributed_summary'] = $contributed_summary;
  $_SESSION['sbac_report']['contributed_details'] = $contributed_details;
  $_SESSION['sbac_report']['gate_keeping'] = $gate_keeping;
  $_SESSION['sbac_report']['all_reviews'] = $all_reviews;
  $_SESSION['sbac_report']['error_message'] = "<div> No data exists for the filters you have selected.  Please choose a new combination of filters and attempt your export again. </div>";
  $_SESSION['sbac_report']['active_tab'] = 0;
}