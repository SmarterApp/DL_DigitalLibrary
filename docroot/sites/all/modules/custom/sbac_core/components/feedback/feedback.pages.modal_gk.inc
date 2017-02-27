<?php

/**
 * The form to initialize Gate Keeper Modal.
 * @param  [type] $form           [description]
 * @param  [type] $form_state     [description]
 * @param  [type] $node           [description]
 * @param  [type] $state          [description]
 * @param  [type] $trigger_id     [description]
 * @param  [type] $ud             [description]
 * @return [type]                 [description]
 */
function feedback_gate_keeper_form($form, &$form_state, $node, $state, $trigger_id, $id) {
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
      '#value' => t('Cancel Review (!hours hrs)', array('!hours' => $hours_left)),
    );

  // does not meet state
    $form['state_not_meet']['intro'] = array(
      '#markup' => '
                    <div class="gate-keeper-modal-intro">
                      ' . t("You’ve indicated that this resource does not meet all the Gate-Keeping Criteria. If you wish to continue, the resource will be returned to the resource contributor with your comments. Be sure to provide actionable feedback.") . '
                    </div>
                   ',
    );

    $form['state_not_meet']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Does Not Meet All Criteria'),
    );

  // meets state
    $form['state_meet']['intro'] = array(
      '#markup' => '
                    <div class="gate-keeper-modal-intro">
                      ' . t("You’ve indicated that this resource meets all the Gate-Keeping Criteria. If you continue, you will review the resource using the Quality Criteria.") . '
                    </div>
                   ',
    );

    $form['state_meet']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Meets all Criteria'),
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
    );

    $state_redirect_options = array(
      'submit_autoclose' => TRUE,
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
          'submit_redirect' => url('node/' . $node->nid . '/feedback/redirect/review-gk'),
        ) + $state_common_options,

        'cancel' => array(
          'dialog' => array('title' => t('You are about to cancel the review')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_cancel']['submit'])),
        ) + $state_common_options + $state_redirect_options,

        'not_meet' => array(
          'dialog' => array('title' => t('This resource does not meet all Gate-Keeping criteria')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_not_meet']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_not_meet',
          )
        ) + $state_common_options,

        'meet' => array(
          'dialog' => array('title' => t('This resource meets all Gate-Keeping criteria.')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_meet']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_meet',
          )
        ) + $state_common_options,

      ),
    );

  dialog_form_prepare($form, $form_state);

  return $form;
}

/**
 * Submit handler for resource_gate_keeper_form().
 */
function feedback_gate_keeper_form_submit($form, &$form_state) {
  $node = $form_state['build_info']['args'][0];
  $feedback = new feedbackStatus($node);

  $state = $form_state['dialog_settings']['current_state'];

  switch ($state) {
    // the initial "start" state; upon submission the modal reloads the page, so the new
    // gate keeper entity is displayed in its form
    case 'start':
      // We only want to start a new gatekeeping review if there isn't one in progress already.
      if ($feedback->gatekeeper_started) {
        drupal_set_message(t('This resource is already in Gatekeeping review.'), 'error');
      } else {
        global $user;

        $entity = new stdClass;
        $entity->title = $node->title . ' - Gate Keeper - ' . $user->uid;
        $entity->type = 'gate_keeper';
        $entity->uid = $user->uid;
        $entity->created = REQUEST_TIME;
        $entity->changed = REQUEST_TIME;
        $entity->language = LANGUAGE_NONE;
        $entity->status = 1;
        $entity->completed = 0;
        $entity->current = 1;
        $entity->node_id = $node->nid;

        drupal_set_message(t('Gatekeeping review process started.'));

        entity_save('feedback', $entity);

        if ($node->workbench_moderation['current']->state == 'being_reviewed') {
          sbac_resource_save_current_state($node);
        }
      }

      break;

    case 'cancel':
      if ($entity = entity_load_single('feedback', $form_state['build_info']['args'][3])) {
        $entity->status = 0;
        entity_save('feedback', $entity);
        sbac_resource_save_current_state($node);
//        _sbac_resource_save_reviewers($node, NULL, FALSE, TRUE);
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
