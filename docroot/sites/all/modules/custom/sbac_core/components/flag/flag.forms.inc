<?php

/**
 * Validation handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_validate($form, &$form_state) {
  $entity = $form_state['values']['entity'];
  
  $lang = LANGUAGE_NONE;
  if (isset($entity->language)) {
    $lang = $entity->language;
  }

  $fields = array(
    'field_issue_type' => 'Please select a reason to flag review.',
  );

  form_check_fields($fields, $form_state['values'], $lang);
}

/**
 * Submit handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_submit($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['action'] == 'submit') {
    eck__entity__form_submit($form, $form_state);

    $issue_options = field_allowed_values('field_issue_type');
    $issue_type = field_get_value($values, 'field_issue_type');
    $details = field_get_value($values, 'field_details');

    $messages = array();
    $messages[] = t('Thank you for submitting your report. Here is the 
      information we received from you.');
    $messages[] = '<strong>' . t('Issue Reported:') . '</strong> ' . $issue_options[$issue_type];
    $messages[] = '<strong>' . t('Additional Details:') . '</strong> ' . check_plain($details);

    foreach ($messages as $message) {
      drupal_set_message($message);
    }

    // remove ECK status message
    foreach ($_SESSION['messages']['status'] as $key => $msg) {
      if (preg_match('/Entity(.+)has been saved/', $msg)) {
        unset($_SESSION['messages']['status'][$key]);
      }

      // fix keys
      $_SESSION['messages']['status'] = array_merge($_SESSION['messages']['status']);
    }

    $form_state['completed'] = TRUE;
  }
}

/**
 * AJAX submit handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_ajax($form, &$form_state) {
  // once complete, the form will be re-rendered to display the status/error
  // messages, so we must remove the visible elements
  if (isset($form_state['completed'])) {
    unset($form['field_issue_type']);
    unset($form['field_details']);
    unset($form['actions']);
  }

  // check for form errors and set a JS flag which can be used to prevent
  // modal from opening
  $errors = form_get_errors();
  $form_error = (int) !empty($errors);

  $issue_type = field_get_value($form_state['values'], 'field_issue_type');
  $update_message = flag_flagged_message($issue_type);

  $form['run_js'] = array(
    '#markup' => '
                  <script>
                    Drupal.settings.flag.form_error = ' . $form_error . ';
                    Drupal.settings.flag.update_message = "' . $update_message . '";
                  </script>
                 ',
  );

  return $form;
}

/**
 * Returns the user-friendly "You've already flagged..." message.
 * @param  [type] $issue_type [description]
 * @return [type]             [description]
 */
function flag_flagged_message($issue_type) {
  $message = 'You flagged this review because it ';

  $issue_options = field_allowed_values('field_issue_type');

  switch ($issue_type) {
    case 'inaccurate':
    case 'unintelligible':
    case 'biased':
      $message .= ' is ';
      break;

    case 'pii':
    case 'spam':
    default:
      break;
  }

  $message .= ' ' . strtolower($issue_options[$issue_type]) . '.';
  $message = t($message);

  return $message;
}