<?php
/**
 * The form to initialize Post Modal.
 * @param  [type] $form           [description]
 * @param  [type] $form_state     [description]
 * @param  [type] $node           [description]
 * @param  [type] $state          [description]
 * @param  [type] $trigger_id     [description]
 * @param  [type] $id             [description]
 * @return [type]                 [description]
 */
function feedback_post_form($form, &$form_state, $node, $state, $trigger_id, $id) {
  $form = array();
  global $user;

  $hours_left = NULL;
  if ($id) {
    $entity = entity_load_single('feedback', $id);
    $hours_left = feedback_hours_left($entity);
  }

  // start state
    $form['state_start']['intro'] = array(
      '#markup' => '
                    <div class="gate-keeper-modal-intro">
                      ' . t('If you continue, you will have !hours hours to complete the review. You can always save your
                        work and complete the review before the alloted time expires.', array(
                          '!hours' => FEEDBACK_REVIEW_TIMEOUT,
                        )) . '
                    </div>
                   ',
    );

    $form['state_start']['submit'] = array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('disabler')),
      '#value' => t('Start Review (!hours hrs)', array('!hours' => FEEDBACK_REVIEW_TIMEOUT)),
    );

  // cancel state
    $form['state_cancel']['intro'] = array(
      '#markup' => '
                    <div class="gate-keeper-modal-intro">
                      ' . t('If you continue, you will no longer be able to review this resource. All review information you have entered will be lost.') . '
                    </div>
                   ',
    );

    $form['state_cancel']['submit'] = array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('disabler')),
      '#value' => t('Cancel Review (!hours hrs)', array('!hours' => $hours_left)),
    );

  // reject state
    $form['state_reject']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . t('Returning this resource will send it and your comments back to the contributor for revision. It will also send a message to each of the reviewers. Be sure you’ve included actionable feedback.')  . '</div>',
    );

    $form['state_reject']['submit'] =  array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('disabler')),
      '#value' => t('Return Resource'),
    );

  // recommend state
    $form['state_post']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . t('Posting this resource will update its status and make it available to the Smart Balanced Digital Library community.')  . '</div>',
    );

    $form['state_post']['submit'] =  array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('disabler')),
      '#value' => t('Post Resource'),
    );

  // post_distinction state
    $form['state_post_distinction']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . t('Posting this resource will update its status and make it available to the Smarter Balanced Digital Library community. It will also be identified as having been posted with distinction.')  . '</div>',
    );

    $form['state_post_distinction']['submit'] =  array(
      '#type' => 'submit',
      '#attributes' => array('class' => array('disabler')),
      '#value' => t('Post Resource'),
    );

  // dialog configuration
    $dialog_common_options = array(
      'width' => '700px',
      'position' => 'center',
    );

  // state configuration
    $state_common_options = array(
      'close_link' => TRUE,
      'close_link_text' => t('Cancel'),
      'close_link_class' => array(
        'button',
        'radius',
      ),
      'submit_autoclose' => TRUE,
    );

    $state_redirect_options = array(
      'submit_redirect' => url('node/' . $node->nid, array('absolute' => TRUE)),
    );

    $form_state['dialog_settings'] = array(
      'current_state' => $state,
      'trigger_id' => $trigger_id,
      'states' => array(

        'start' => array(
          'dialog' => array('title' => t('You are about to start reviewing this Resource')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_start']['submit'])),
          'submit_autoclose' => TRUE,
          'submit_redirect' => url('node/' . $node->nid . '/feedback/redirect/review-post'),
        ) + $state_common_options,

        'cancel' => array(
          'dialog' => array('title' => t('You are about to cancel the review')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_cancel']['submit'])),
        ) + $state_common_options + $state_redirect_options,

        'reject' => array(
          'dialog' => array('title' => t('You are about to return this resource')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_reject']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_reject',
          )
        ) + $state_common_options,

        'post' => array(
          'dialog' => array('title' => t('You are about to post this resource')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_post']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_post',
          )
        ) + $state_common_options,

        'post_distinction' => array(
          'dialog' => array('title' => t('You are about to post this resource with distinction')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_post_distinction']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_post_distinction',
          )
        ) + $state_common_options,

      ),
    );

  dialog_form_prepare($form, $form_state);

  return $form;
}

/**
 * Submit handler for resource_post_form().
 */
function feedback_post_form_submit($form, &$form_state) {
  $node = $form_state['build_info']['args'][0];
  $feedback = new feedbackStatus($node);

  $state = $form_state['dialog_settings']['current_state'];

  switch ($state) {
    // the initial "start" state; upon submission the modal reloads the page, so the new
    // entity is displayed in its form
    case 'start':
      // We only want to start a new review if there isn't already a post review on progress
      if ($feedback->post_started) {
        drupal_set_message(t('This resource is already being reviewed for publication.'), 'error');
      } else {
        global $user;

        if (resource_access('view post', $node, $user)) {
          $entity = new stdClass;
          $entity->title = $node->title . ' - Post - ' . $user->uid;
          $entity->type = 'post';
          $entity->uid = $user->uid;
          $entity->created = REQUEST_TIME;
          $entity->changed = REQUEST_TIME;
          $entity->language = LANGUAGE_NONE;
          $entity->status = 1;
          $entity->completed = 0;
          $entity->current = 1;
          $entity->node_id = $node->nid;

          drupal_set_message(t('Post review process started.'));

          entity_save('feedback', $entity);
        } else {
          drupal_set_message(t('Post review process could not be started because another user is currently reviewing the resource.'), 'error');
        }
        sbac_resource_save_current_state($node);
      }

      break;

    case 'cancel':
      if ($entity = entity_load_single('feedback', $form_state['build_info']['args'][3])) {
        $entity->status = 0;
        entity_save('feedback', $entity);
        sbac_resource_save_current_state($node);
      }

      break;
    // nothing needs to happen in these cases as the processing is handled in
    // feedback_eck_gate_keeper_form_submit(), in order to make sure the form validation goes
    // through first
    case 'not_meet':
    case 'meet':
      break;
  }
}
