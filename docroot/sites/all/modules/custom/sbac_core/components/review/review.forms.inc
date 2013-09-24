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

  // final submission from Preview state
  if ($form_state['triggering_element']['#value'] == 'Submit') {
    // watchdog('sbac', 'title is: ' . $form_state['create_values']['title']);
    global $user;
    $node = $form_state['node_object'];

    $entity = entity_create('review', array(
      'type' => 'end_use',
      'uid' => $user->uid,
      'status' => 1,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'node_id' => $node->nid,
    ));

    $fields = array(
      'title',
      'field_details',
      'field_student_learning',
      'field_pro_dev',
      'field_ease_use',
      'field_appropriate_for',
    );

    foreach ($fields as $field_key) {
      if (isset($form_state['create_values'][$field_key])) {
        $entity->{$field_key} = $form_state['create_values'][$field_key];
      }
    }

    entity_save('review', $entity);

    drupal_set_message(t('Your review posted successfully.'));

    $form_state['redirect'] = url('node/' . $node->nid . '/feedback/redirect/review-reviews', array('absolute' => TRUE));
  }
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