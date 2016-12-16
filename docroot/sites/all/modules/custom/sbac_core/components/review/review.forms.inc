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

      // create a fake entity object so we can use field_get_items to grab the field
      // value
      $entity = new stdClass;
      $entity->type = 'end_use';
      $entity->field_appropriate_for = $form_state['values']['field_appropriate_for'];
      $values = field_get_items('review', $entity, 'field_appropriate_for');

      // check for empty value and remove the field if so
      $remove = TRUE;
      foreach ($values as $value) {
        if (isset($value['tid']) && !empty($value['tid'])) {
          $remove = FALSE;
        }
      }

      if ($remove) {
        unset($form_state['values']['field_appropriate_for']);
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
    global $user;
    $node = $form_state['node_object'];

    $entity = entity_create('review', array(
      'type' => 'end_use',
      'uid' => $user->uid,
      'status' => 1,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'node_id' => $node->nid,
      'entity_type' => 'review',
    ));

    // Added array values to track field info.
    //  TRUE = fivestar rating field
    //  FALSE = Not fivestar field.
    $fields = array(
      'title'                   => FALSE,
      'field_details'           => FALSE,
      'field_student_learning'  => TRUE,
      'field_pro_dev'           => TRUE,
      'field_ease_use'          => TRUE,
      'field_appropriate_for'   => FALSE,
    );

    $score_storage = array();
    foreach ($fields as $field_key => $is_rating_field) {
      if (isset($form_state['create_values'][$field_key])) {
        $entity->{$field_key} = $form_state['create_values'][$field_key];

        // Check if the field stores node ratings.
        if($is_rating_field) { //if (in_array($field_key, $rating_fields)) { // Need to compute averages.
          $current_rating = 0;
          if (!empty($form_state['create_values'][$field_key])) {
            $current_rating = $form_state['create_values'][$field_key][LANGUAGE_NONE][0]['rating'];
          }
          $score_storage[] = $current_rating;
        }
      }
    }

    // Compute the average rating. Save it into the field.
    $total_score = 0;
    $avg_field_key = 'field_avg_rating';
    $result = array();
    if (!empty($score_storage)) {
      foreach ($score_storage as $score) {
        $total_score += $score;
      }
      $avg_score = $total_score / count($score_storage);
      $result[LANGUAGE_NONE][0]['value'] = $avg_score;
      $entity->{$avg_field_key} = $result;
    } else {
      $result[LANGUAGE_NONE][0]['value'] = 0;
      $entity->{$avg_field_key} = $result;
    }

    entity_save('review', $entity);

    // Ensure the parent node gets its total avg rating recalculated.
    sbac_resource_update_average_rating_score($node->nid);

    // Notify author of resource review
    if ($task = taskit_get_object('resource_rated')) {
      global $user;
      $task->addVisibility($task::VISIBILITY_USER);
      $task->addEntity('node', $node->nid);
      $task->addOwningUser($node->uid);
      $task->addTriggeringUser($user->uid);
      $task->save();
    }
    drupal_set_message(t('Your review posted successfully.'));

    // create redirect 
    global $user;
    $user_profile = user_load($user->uid);
    if (!in_array('resource contributor', $user_profile->roles) && !in_array('resource reviewer', $user_profiel->roles) && !in_array('resource publisher', $user_profile->roles)) {
      $star_rating_goal = $user_profile->field_star_rating_goal['und'][0]['value'];
      $resources_rated = $user_profile->field_resources_rated['und'][0]['value'];
      // Create popup for star rating complete
      // Do this for star rating goal - rated resources <= 1 because the current rating hasn't been counted yet
      if (($star_rating_goal - $resources_rated) <= 1) {
        $form_state['redirect'] = url('node/' . $node->nid, array('absolute' => TRUE, 'query' => array('rating-goal' => 'complete')));
      }
      // Create popup for star rating in-process
      else {  
        $form_state['redirect'] = url('node/' . $node->nid, array('absolute' => TRUE, 'query' => array('rating-goal' => 'in-process')));
      }
    }
    else {
      $form_state['redirect'] = url('node/' . $node->nid . '/feedback/redirect/review-reviews', array('absolute' => TRUE));
    }
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
