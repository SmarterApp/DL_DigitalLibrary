<?php

/**
 * AJAX submit handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_ajax($form, &$form_state) {
  // check for form errors and set a JS flag which can be used to prevent
  // modal from opening
  $errors = form_get_errors();
  $form_error = (int) !empty($errors);

  $form['run_js'] = array(
    '#markup' => '<script>Drupal.settings.flag.form_error = ' . $form_error . ';</script>',
  );

  return $form;
}

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
  
}