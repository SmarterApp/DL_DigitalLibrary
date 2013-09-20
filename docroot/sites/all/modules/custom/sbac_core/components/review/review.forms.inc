<?php

/**
 * Validation handler for Review form
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_validate($form, &$form_state) {
  switch ($form_state['current_state']) { 
    case 'create':
      // perform profanity validation on title
      if (profanity_validate_text($form_state['values']['title'])) {
        form_set_error('title', profanity_error_message_text());
      }

      break;  
  
    case 'preview': 
    default:
      // no validation necessary
      break;
  }
}

/**
 * "Previous" state transition.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_previous($form, &$form_state) {
  $form_state['previous_state'] = $form_state['current_state'];

  switch ($form_state['current_state']) {
    case 'create':
      $form_state['rebuild'] = FALSE;

      break;

    case 'preview':
      $form_state['current_state'] = 'create';
      $form_state['rebuild'] = TRUE;

      break;
  }
}

/**
 * "Next" state transition.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_next($form, &$form_state) {
  $form_state['previous_state'] = $form_state['current_state'];

  switch ($form_state['current_state']) {
    case 'create':
      $form_state['current_state'] = 'preview';
      $form_state['rebuild'] = TRUE;

      break;

    case 'preview':
      $form_state['rebuild'] = FALSE;

      break;
  }
}

/**
 * Submission handler for Review form
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_submit($form, &$form_state) {
  $form_state[$form_state['current_state'] . '_values'] = $form_state['values'];
}

/**
 * AJAX submit handler.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_ajax($form, &$form_state) {
  // the form will have been rebuilt for the current state in hook_form_alter(), so this
  // is mostly a formality
  return $form;
}