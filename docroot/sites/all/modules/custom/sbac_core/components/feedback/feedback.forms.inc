<?php

/*----------------------------------------------------------------------------
      GENERAL FORMS
----------------------------------------------------------------------------*/

/**
 * Validation handler for ECK Feedback forms.
 */
function feedback_eck_feedback_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $lang = $values['entity']->language;

  // checks for profanity messages and updates the error text
  $profanity_check = function($container) use ($values) {
    if ($errors = form_get_errors()) {
      $profanity_error_text = profanity_error_message_text();

      foreach ($errors as $key => $text) {
        // make sure we're looking at an error from the profanity component
        if ($text !== $profanity_error_text) {
          continue;
        }

        $key_parts = explode('][', $key);

        // basic sanity check
        if ((sizeof($key_parts) == 7) && ($key_parts[0] == $container) && ($key_parts[3] == 'field_comments')) {
          $delta = $key_parts[2];

          $set_title = trim(check_plain(strip_tags($values[$container][$lang][$delta]['set_title'])));
          if ($values['entity']->type == 'gate_keeper') {
            $new_text= t('Please remove inappropriate language from the comment to Gate-Keeping Criteria to continue');
          }
          else {
            $new_text = t('Please remove inappropriate language from the comment in Quality Criterion below to continue');
          }

          // ugly, but works
          $location = array_search($text, $_SESSION['messages']['error']);
          $_SESSION['messages']['error'][$location] = $new_text;
        }
      }
    }
  };

  // we use this validation callback to override the error messages set by the
  // profanity component
  switch ($values['entity']->type) {
    case 'gate_keeper':
      $container = 'field_quality_set';

      switch ($values['action']) {
        case 'validate':
          $fields = array(
            $container => array(
              'field_comments' => 'Please add a comment to Gate-Keeping Criteria !delta_minus_1_friendly to continue',
              'field_meets_criterion' => 'You must make a decision in Quality Criteria !delta_minus_1_friendly to continue',
            ),
          );

          form_check_fields($fields, $form_state['values'], $lang);

          break;
      }

      $profanity_check($container);

      break;

    case 'qc':
      // there is an edge-case where too many users load the Quality Review form
      // at the same time; since we only want a maximum of three of these, we do an
      // extra permission check here (which will fail if the max number of entities
      // is reached)
      $node = node_load($values['node_id']);
      if (!resource_access('edit quality criteria', $node)) {
        form_set_error('', t('Maximum number of Quality Criteria Reviews reached.'));
        return;
      }

      $container = 'field_review_set';

      switch ($values['action']) {
        case 'validate':
          $fields = array(
            $container => array(
              'field_comments' => 'Please add a comment to Criteria !delta_minus_1_friendly to continue',
              'field_level' => 'You must make a decision in Criteria !delta_minus_1_friendly to continue',
            ),
            'field_rec_options' => 'You must select a Recommendation Option to continue',
            'field_rec_rationale' => 'You must enter Rationale for Recommendation to continue',
          );

          form_check_fields($fields, $form_state['values'], $lang);

          break;
      }

      $profanity_check($container);

      break;

    case 'post':

      switch ($values['action']) {
        case 'validate':

          $last_feedback = db_select('eck_feedback', 'f')
            ->condition('f.completed', 1)
            ->condition('f.node_id', $values['node_id'])
            ->fields('f', array('type'))
            ->orderBy('f.id', 'desc')
            ->range(0, 1)
            ->execute()
            ->fetchField();
          if ($last_feedback && 'post' == $last_feedback) {
            $fields = array(
              'field_to_contributor' => 'You must enter a comment for the Contributor to continue',
              'field_post_options' => 'You must select a Post Option to continue',
            );
          }
          else {
            $fields = array(
              'field_to_contributor' => 'You must enter a comment for the Contributor to continue',
              'field_to_reviewer_1' => 'You must enter a comment for Reviewer 1 to continue',
              'field_to_reviewer_2' => 'You must enter a comment for Reviewer 2 to continue',
              'field_to_reviewer_3' => 'You must enter a comment for Reviewer 3 to continue',
              'field_post_options' => 'You must select a Post Option to continue',
            );
          }

          form_check_fields($fields, $form_state['values'], $lang);

          break;
      }

      break;
  }
}

/**
 * AJAX submit callback for the ECK feedback forms.
 */
function feedback_eck_feedback_form_submit($form, &$form_state) {
  $entity = $form_state['values']['entity'];

  // set correct values to bundle-specific fields
    module_load_include('inc', 'sbac_core', '/components/feedback/includes/form_utility/class.Base');

    $rebuild_decision_radios = function($option, $states, $utility, &$form) use ($entity) {
      if ($option !== FALSE) {
        $state = $states[$option];

        $node = node_load($entity->node_id);

        unset($form['actions']['complete_button']);
        unset($form['actions']['complete']);

        try {
          $utility->completeButton($state);

          $utility_form = $utility->getForm();
          $form['actions'] += $utility_form['actions'];
          $form['actions']['complete_button']['#weight'] = 9999;
        }
        catch (\Exception $e) {
          drupal_set_message($e->getMessage(), 'error');
        }
      }
    };

    if ($entity->type == 'qc') {
      // we need to rebuild the complete review buttons when the recommendation
      // option changes
      try {
        module_load_include('inc', 'sbac_core', '/components/feedback/includes/form_utility/class.Qc');

        $option = field_get_value($form_state['values'], 'field_rec_options');
        $states = feedback_recommendation_states();

        $form_copy = $form;
        $state_copy = $form_state;

        $utility = new sbac_core\components\feedback\form_utility\Qc($form_copy, $state_copy, array());
        $rebuild_decision_radios($option, $states, $utility, $form);
      }
      catch (\Exception $e) {
        drupal_set_message($e->getMessage(), 'error');
      }

      // also rebuild the level radio buttons
      foreach ($form_state['values']['field_review_set'][$entity->language] as $key => $item) {
        if ($value = field_get_value($item, 'field_level')) {
          $states = feedback_recommendation_states();

          $desc = variable_get('qc_level_' . $value, '');
          $form['field_review_set'][$entity->language][$key]['field_level'][$entity->language]['#suffix'] = '<div class="desc">' . filter_text($desc)  . '</div>';
        }
      }
    }
    elseif ($entity->type == 'post') {
      // we need to rebuild the complete review buttons when the post
      // option changes
      module_load_include('inc', 'sbac_core', '/components/feedback/includes/form_utility/class.Post');

      $option = field_get_value($form_state['values'], 'field_post_options');
      $states = feedback_post_states();

      $form_copy = $form;
      $state_copy = $form_state;

      $utility = new sbac_core\components\feedback\form_utility\Post($form_copy, $state_copy, array());
      $rebuild_decision_radios($option, $states, $utility, $form);
    }

  // check for form errors and set a JS flag which can be used to prevent
  // modal from opening
    $errors = form_get_errors();
    $form_error = (int) !empty($errors);

  // Redirect to resource-review page on save and close
  $redirect_js = '';
  if($form_state['values']['action'] == 'save_close'){
    $redirect_js = 'window.location.href = "/resource-review"';
  }
    $form['run_js'] = array(
      '#markup' => '<script>Drupal.settings.feedback.form_error = ' . $form_error . ';' . $redirect_js . ';</script>',
    );

  sbac_resource_remove_default_status_messages();

  return $form;
}

/*----------------------------------------------------------------------------
      BUNDLE-SPECIFIC FORMS
----------------------------------------------------------------------------*/

/**
 * Submit handler for ECK Gate Keeper form.
 */
function feedback_eck_gate_keeper_form_submit($form, &$form_state) {
  if ($form_state['values']['action'] == 'validate') {
    return;
  }

  $entity = $form_state['values']['entity'];
  $node = node_load($entity->node_id);
  drupal_set_message(t('@title - Gate Keeping Review has been saved', array('@title' => $node->title)));
  global $user;

  $task = FALSE;
  $completed_review = FALSE;
  switch ($form_state['values']['action']) {
    // TODO: we should probably do some additional validation here, just in case
    // the clever user modified DOM to enable disabled buttons and 'complete'
    // a resource that didn't meet all criteria

    case 'cancel':
      // the cancellation is handled in the modal form's submission. If we trigger
      // GK form submission, it can complain about empty fields, and we don't care
      // about those during the cancellation process

      break;

    case 'not_meet':
      $entity->completed = 1;
      $entity->met_criteria = 0;
      entity_save('feedback', $entity);

      // reject resource so author can make changes and re-submit
      workbench_moderation_moderate($node, 'rejected');
      $task = taskit_get_object('resource_rejected');
      sbac_resource_save_current_state($node);

      // Send email to user
      // Add resource link to message
      global $base_url;
      $values = array(
        'arguments' => array(
          '!resource-link' => $base_url . '/node/' . $node->nid,
        ),
        'uid' => $node->uid,
      );
      $message = message_create('gatekeeper_reject', $values);
    
      $wrapper = entity_metadata_wrapper('message', $message);
    
      // Replace explicit notification with subscription-based notification
      message_notify_send_message($message);
    
      if (module_exists('message_subscribe')) {
        // If Message-subscribe exists, let this example module use it.
        //message_subscribe_send_message('user', $node, $message, array('email' => $options));
      }
      $completed_review = TRUE;
      break;

    case 'meet':
      $entity->completed = 1;
      $entity->met_criteria = 1;
      entity_save('feedback', $entity);

      // now that we have a completed and 'met' gate keeper, the user should start
      // the Quality Criteria Review flow, so create the qc entity
      $qc = new stdClass;
      $qc->title = $node->title .' - Review - ' . $user->uid;
      $qc->type = 'qc';
      $qc->uid = $user->uid;
      $qc->created = REQUEST_TIME;
      $qc->changed = REQUEST_TIME;
      $qc->language = LANGUAGE_NONE;
      $qc->status = 1;
      $qc->completed = 0;
      $qc->current = 1;
      $qc->node_id = $node->nid;

      drupal_set_message(t('Quality Criteria Review has started.'));
      entity_save('feedback', $qc);
      sbac_resource_save_current_state($node);

      $completed_review = TRUE;
      break;
  }

  if ($task && $node = node_load($entity->node_id)) {
    $task->addVisibility($task::VISIBILITY_USER);
    $task->addEntity('node', $node->nid);
    $task->addEntity('feedback', $entity->id);
    $task->addOwningUser($node->uid);
    $task->addTriggeringUser(1);
    $task->save();
  }

  if ($completed_review && $node = node_load($entity->node_id)) {
    // Notify Reviewer
    $task = taskit_get_object('review_completed');
    $task->addVisibility($task::VISIBILITY_USER);
    $task->addEntity('node', $node->nid);
    $task->addEntity('feedback', $entity->id);
    $task->addOwningUser($user->uid);
    $task->addTriggeringUser(1);
    $task->save();
    // Notify Contributor
    $task2 = taskit_get_object('review_completed');
    $task2->addVisibility($task::VISIBILITY_USER);
    $task2->addEntity('node', $node->nid);
    $task2->addEntity('feedback', $entity->id);
    $task2->addOwningUser($node->uid);
    $task2->addTriggeringUser(1);
    $task2->save();
  }

  sbac_resource_remove_default_status_messages();
}

/**
 * Submit handler for ECK Qc form.
 */
function feedback_eck_qc_form_submit($form, &$form_state) {
  if ($form_state['values']['action'] == 'validate') {
    return;
  }

  $entity = $form_state['values']['entity'];
  $node = node_load($entity->node_id);
  drupal_set_message(t('@title - Quality Criteria Review has been saved', array('@title' => $node->title)));

  global $user;

  $is_playlist = FALSE;

  $quality_count = FEEDBACK_MAX_REVIEW;
  // Reduce qc reviews for playlists to 2
  if ($node->field_focus[LANGUAGE_NONE][0]['tid'] == '78306') {
    $quality_count = 2;
    $is_playlist = TRUE;
  }

  $task = FALSE;
  $completed_review = FALSE;
  switch ($form_state['values']['action']) {
    // handled in the modal's submit callback, otherwise we can run
    // into empty-field validation errors
    case 'cancel':
      break;

    // don't need to do anything
    case 'save_close':
      break;

    // check the number of submitted reviews, collate recommendations and make
    // a workflow decision
    case 'complete':
      $entity->completed = 1;
      entity_save('feedback', $entity);

      // count the number of completed reviews
      $args = array(
        ':node_id' => $node->nid,
      );

      $query = "  SELECT  COUNT(id) as count
                  FROM    eck_feedback
                  WHERE   type = 'qc'
                  AND     node_id = :node_id
                  AND     status = 1
                  AND     completed = 1
                  AND     current = 1
               ";

      $count = db_query($query, $args)->fetchField();

      if ($count == $quality_count) {
        $query = "  SELECT  id
                    FROM    eck_feedback
                    WHERE   type = 'qc'
                    AND     node_id = :node_id
                    AND     status = 1
                    AND     completed = 1
                    AND     current = 1
                 ";

        $reviews = array();
        $result = db_query($query, $args);

        foreach ($result as $row) {
          $reviews[] = entity_load_single('feedback', $row->id);
        }

        // figure out the recommend/not values for workflow states
        $do_not = 0;
        $do_res = 0;
        $do     = 0;
        $do_dis = 0;

        foreach ($reviews as $entity) {
          $rec_value = field_entity_value($entity, 'field_rec_options');
          switch ($rec_value) {
            case 0: $do_not++; break; // do not recommend
            case 1: $do_res++; break; // recommend w/ reservations
            case 2: $do++;     break; // recommend
            case 3: $do_dis++; break; // recommend w/ distinction
          }
        }

        $task = FALSE;
        $do_post = 3;
        // Allow publishing with only 2 recommendations for playlists
        if ($is_playlist) {
          $do_post = 2;        
        }

        // post with distinction
        if ($do_dis == 3 || ($do_dis == 2 && $do == 1)) {
          $node->sticky = 1;
          node_save($node);

          // we need to go through the approved state in order to not confuse
          // workbench_moderation
          workbench_moderation_moderate($node, 'approved');
          workbench_moderation_moderate($node, 'published');

          $task = taskit_get_object('resource_published');
        }
        // post
        elseif (($do_dis == 1 && $do == 2) || $do == $do_post) {
          // we need to go through the approved state in order to not confuse
          // workbench_moderation
          workbench_moderation_moderate($node, 'approved');
          workbench_moderation_moderate($node, 'published');

          $task = taskit_get_object('resource_published');
        }
        // publishing workflow
        elseif (($do_dis == 2 && ($do_res == 1 || $do_not == 1)) || ($do_dis == 1 && $do == 1) || ($do == 2)) {
          // send to publisher
          workbench_moderation_moderate($node, 'approved');
        }
        // reject
        else {
          workbench_moderation_moderate($node, 'rejected');

          $task = taskit_get_object('resource_rejected');
        }
        send_review_notifications($task, $node, $reviews);
        sbac_resource_save_current_state($node);
      }
      sbac_resource_save_current_state($node);

      $completed_review = TRUE;

      break;
  }

  if ($completed_review && $node) {
    $task = taskit_get_object('review_completed');
    $task->addVisibility($task::VISIBILITY_USER);
    $task->addEntity('node', $node->nid);
    $task->addEntity('feedback', $entity->id);
    $task->addOwningUser($user->uid);
    $task->addTriggeringUser(1);
    $task->save();
  }

  $form_state['redirect'] = array(
    'resource-review'
  );

  sbac_resource_remove_default_status_messages();
}

/**
 * Submit handler for ECK Post form.
 */
function feedback_eck_post_form_submit($form, &$form_state) {
  if ($form_state['values']['action'] == 'validate') {
    return;
  }

  $entity = $form_state['values']['entity'];
  $node = node_load($entity->node_id);
  drupal_set_message(t('@title - Posting Review has been saved', array('@title' => $node->title)));

  global $user;

  // find the associated reviews
  $query = "  SELECT  id
              FROM    eck_feedback
              WHERE   type = 'qc'
              AND     node_id = :node_id
              AND     status = 1
              AND     completed = 1
           ";

  $args = array(
    ':node_id' => $node->nid,
  );

  $reviews = array();
  $result = db_query($query, $args);
  foreach ($result as $row) {
    $reviews[] = entity_load_single('feedback', $row->id);
  }

  $task = FALSE;
  $completed_review = FALSE;
  switch ($form_state['values']['action']) {
    // these are handled in the modal's submit callback
    case 'cancel':
    case 'start':
      break;

    case 'reject':
      $entity->completed = 1;
      entity_save('feedback', $entity);
      // reject resource so author can make changes and re-submit
      workbench_moderation_moderate($node, 'rejected');
      $task = taskit_get_object('resource_rejected');
      sbac_resource_save_current_state($node);

      // Send email to user
      global $base_url;
      $values = array(
        'arguments' => array(
          '!resource-link' => $base_url . '/node/' . $node->nid,
        ),
        'uid' => $node->uid,
      );
      $message = message_create('post_reject', $values);
    
      $wrapper = entity_metadata_wrapper('message', $message);
    
      // Replace explicit notification with subscription-based notification
      message_notify_send_message($message);
    
      if (module_exists('message_subscribe')) {
        // If Message-subscribe exists, let this example module use it.
        //message_subscribe_send_message('user', $node, $message, array('email' => $options));
      }

      $completed_review = TRUE;

      break;

    case 'post':
      $entity->completed = 1;
      entity_save('feedback', $entity);
      workbench_moderation_moderate($node, 'published');
      $task = taskit_get_object('resource_published');
      sbac_resource_save_current_state($node);

      $completed_review = TRUE;

      break;

    case 'post_distinction':
      $entity->completed = 1;
      entity_save('feedback', $entity);

      // distinction = sticky
      $node->sticky = 1;
      node_save($node);
      workbench_moderation_moderate($node, 'published');
      $task = taskit_get_object('resource_published');
      sbac_resource_save_current_state($node);

      $completed_review = TRUE;

      break;
  }

  $reviews[] = $entity;

  send_review_notifications($task, $node, $reviews);

  if ($completed_review && $node) {
    $task = taskit_get_object('review_completed');
    $task->addVisibility($task::VISIBILITY_USER);
    $task->addEntity('node', $node->nid);
    $task->addEntity('feedback', $entity->id);
    $task->addOwningUser($user->uid);
    $task->addTriggeringUser(1);
    $task->save();
  }

  $form_state['redirect'] = 'node/' . $node->nid;

  sbac_resource_remove_default_status_messages();
}

/*----------------------------------------------------------------------------
      MISC FORMS
----------------------------------------------------------------------------*/

/**
 * Validation handler for the node form on the 'Edit Resource Tags' form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function feedback_edit_tags_form_validate($form, &$form_state) {
  sbac_resource_validate_tags($form, $form_state);
}

/**
 * Submit handler for the node form on the 'Edit Resource Tags' form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function feedback_edit_tags_form_submit($form, &$form_state) {
  module_load_include('inc', 'node', 'node.pages');

  sbac_resource_clean_text($form_state);
  $form_state['values']['path']['pathauto'] = TRUE;
  node_form_submit($form, $form_state);
}

/**
 * AJAX 'Save & Close' callback for the 'Edit Resource Tags' form.
 */
function feedback_edit_tags_ajax_save($form, &$form_state) {
  $errors = form_get_errors();
  $form_error = (int) !empty($errors);

  if ($form_error) {
    $js = 'Drupal.settings.feedback.form_error = ' . $form_error . ';';
  }
  else {
    $url = url('digital-library-resources', array('absolute' => TRUE));
    $js = 'document.location = "' . $url . '";';
  }

  $form['run_js'] = array(
    '#markup' => '<script>' . $js . '</script>',
  );

  return $form;
}

/**
 * AJAX 'Save and Continue' callback for the 'Edit Resource Tags' form.
 */
function feedback_edit_tags_ajax_continue($form, &$form_state) {
  $errors = form_get_errors();
  $form_error = (int) !empty($errors);

  if ($form_error) {
    $js = 'Drupal.settings.feedback.form_error = ' . $form_error . ';';
  }
  else {
    $js = 'Drupal.behaviors.sections.switch_tab("#review-post");';
  }

  $form['run_js'] = array(
    '#markup' => '<script>' . $js . '</script>',
  );

  return $form;
}
