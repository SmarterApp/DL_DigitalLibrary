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

  watchdog('sbac', 'previous: ' . $form_state['current_state']);
}

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

  watchdog('sbac', 'next: ' . $form_state['current_state']);
}

function review_form_submit($form, &$form_state) {
  $form_state[$form_state['current_state'] . '_values'] = $form_state['values'];

  watchdog('sbac', 'submit: ' . $form_state['current_state']);

  // if (isset($form_state['multistep_values']['form_build_id'])) {
  //   $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  // }
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

  watchdog('sbac', 'rebuild: ' . $form_state['current_state']);

  return $form;
}