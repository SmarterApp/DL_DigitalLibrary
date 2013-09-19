<?php

/**
 * Validation handler for Review form
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Edit') {
    return;
  }  

  watchdog('sbac', 'validate: ' . $form_state['current_state']);

  switch ($form_state['current_state']) { 
    case 'create':
      // perform profanity validation on title
      if (profanity_validate_text($form_state['values']['title'])) {
        form_set_error('title', profanity_error_message_text());
      }

      break;  
  
    case 'preview': 
      
      break;
  }
}

function review_form_submit($form, &$form_state) {
  $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];

  watchdog('sbac', 'submit: ' . $form_state['current_state']);

  switch ($form_state['current_state']) {
    case 'create':
      $form_state['current_state'] = 'preview';
      $form_state['rebuild'] = TRUE;  

      break;

    case 'preview':
      if ($form_state['triggering_element']['#value'] == 'Edit') {
        $form_state['current_state'] = 'create';
        $form_state['rebuild'] = TRUE;  
      }
      else {
        $form_state['complete'] = TRUE;
      }

      break;
  } 
   
  if (isset($form_state['complete'])) {
    // do something
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }

  return $form;
}

/**
 * AJAX submit handler.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_rebuild($form, &$form_state) {
  if (isset($form_state['current_state']) && $form_state['current_state'] == 'Edit') {
    $form_state['current_state'] = 'create';
  }

  foreach ($form as $key => $item) {
    if (  $key{0} != '#' && 
          strpos($key, 'state_') === 0 && 
          $key != 'state_' . $form_state['current_state'] &&
          $key != 'actions') {
      $form[$key]['#access'] = FALSE;
    }
  }

  return $form;
}