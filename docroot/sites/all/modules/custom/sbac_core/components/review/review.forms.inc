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

  switch ($form_state['stage']) { 
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

  switch ($form_state['stage']) {
    case 'create':
      $form_state['stage'] = 'preview';
      $form_state['rebuild'] = TRUE;  

      break;

    case 'preview':
      if ($form_state['triggering_element']['#value'] == 'Edit') {
        $form_state['stage'] = 'preview';
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

  // check for form errors and set a JS flag which can be used to prevent
  // modal from opening
  $errors = form_get_errors();
  $form_error = (int) !empty($errors);

  $form['run_js'] = array(
    '#markup' => '<script>Drupal.settings.review.form_error = ' . $form_error . ';</script>',
  );

  return $form;
}