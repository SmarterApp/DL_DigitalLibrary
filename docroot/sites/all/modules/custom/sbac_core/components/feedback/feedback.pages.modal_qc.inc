<?php

/**
 * The form to initialize Quality Criteria Review Modal.
 * @param  [type] $form           [description]
 * @param  [type] $form_state     [description]
 * @param  [type] $node           [description]
 * @param  [type] $state          [description]
 * @param  [type] $trigger_id     [description]
 * @param  [type] $id             [description]
 * @return [type]                 [description]
 */
function feedback_qc_form($form, &$form_state, $node, $state, $trigger_id, $id) {
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
      '#value' => t('Start Review (!hours hrs)', array('!hours' => FEEDBACK_REVIEW_TIMEOUT)),
    );

  // cancel state
    $form['state_cancel']['intro'] = array(
      '#markup' => '
                    <div class="gate-keeper-modal-intro">
                      ' . t('If you continue, you will no longer be able to view this resource. All of your comments and answers will be lost.') . '
                    </div>
                   ',
    );

    $form['state_cancel']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel Review (!hours hrs)', array('!hours' => $hours_left)),
    );

  // elements common to recommendation states
    $reco_desc = t("If you continue, you will no longer be able to adjust your Quality Criteria levels.
                    Comments you have entered will be saved and provided either to the publisher for use during the final review or directly to the contributor for use in revising the resource. Be sure you've provided actionable feedback.");

    $reco_submit = array('submit' => array(
      '#type' => 'submit',
      '#value' => t('Complete Review'),
    ));

  // not_recommend state
    $form['state_not_recommend']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . $reco_desc  . '</div>',
    );

    $form['state_not_recommend'] += $reco_submit;

  // recommend_reservation state
    $form['state_recommend_reservation']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . $reco_desc  . '</div>',
    );

    $form['state_recommend_reservation'] += $reco_submit;

  // recommend state
    $form['state_recommend']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . $reco_desc  . '</div>',
    );

    $form['state_recommend'] += $reco_submit;

  // recommend_distinction state
    $form['state_recommend_distinction']['intro'] = array(
      '#markup' => '<div class="gate-keeper-modal-intro">' . $reco_desc  . '</div>',
    );

    $form['state_recommend_distinction'] += $reco_submit;

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

    $form_state['dialog_settings'] = array(
      'current_state' => $state,
      'trigger_id' => $trigger_id,
      'states' => array(

        'start' => array(
          'dialog' => array('title' => t('You are about to start reviewing this Resource')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_start']['submit'])),
          'submit_autoclose' => TRUE,
          'submit_redirect' => url('node/' . $node->nid . '/feedback/redirect/review-qc'),
        ) + $state_common_options,

        'cancel' => array(
          'dialog' => array('title' => t('You are about to cancel the Review')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_cancel']['submit'])),
          'submit_redirect' => url('node/' . $node->nid . '/feedback/redirect/review-qc', array('absolute' => TRUE)),
        ) + $state_common_options,

        'not_recommend' => array(
          'dialog' => array('title' => t('You do not recommend this Resource')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_not_recommend']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_not_recommend',
          )
        ) + $state_common_options,

        'recommend_reservation' => array(
          'dialog' => array('title' => t('You recommend this resource with revisions')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_recommend_reservation']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_recommend_reservation',
          )
        ) + $state_common_options,

        'recommend' => array(
          'dialog' => array('title' => t('You recommend this resource')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_recommend']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_recommend',
          )
        ) + $state_common_options,

        'recommend_distinction' => array(
          'dialog' => array('title' => t('You recommend this resource with distinction')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_recommend_distinction']['submit'])),
          'submit_js_callback' => array(
            'behavior' => 'feedback',
            'method' => 'submit_modal_callback_recommend_distinction',
          )
        ) + $state_common_options,

      ),
    );

  dialog_form_prepare($form, $form_state);

  return $form;
}

/**
 * Submit handler for resource_qc_form().
 */
function feedback_qc_form_submit($form, &$form_state) {
  $node = $form_state['build_info']['args'][0];

  $state = $form_state['dialog_settings']['current_state'];

  switch ($state) {
    // the initial "start" state; upon submission the modal reloads the page, so the new
    // gate keeper entity is displayed in its form
    case 'start':
      global $user;

      $entity = new stdClass;
      $entity->title = $node->title .' - Review - ' . $user->uid;
      $entity->type = 'qc';
      $entity->uid = $user->uid;
      $entity->created = REQUEST_TIME;
      $entity->changed = REQUEST_TIME;
      $entity->language = LANGUAGE_NONE;
      $entity->status = 1;
      $entity->completed = 0;
      $entity->current = 1;
      $entity->node_id = $node->nid;

      drupal_set_message(t('Quality criteria review process started.'));
      entity_save('feedback', $entity);
      sbac_resource_save_current_state($node);

      break;

    case 'cancel':
      if ($entity = entity_load_single('feedback', $form_state['build_info']['args'][3])) {
        $entity->status = 0;
        entity_save('feedback', $entity);
        sbac_resource_save_current_state($node);
//        _sbac_resource_save_reviewers($node, NULL, FALSE, TRUE);
      }

      break;

    case 'not_recommend':
    case 'recommend_reservation':
    case 'recommend':
    case 'recommend_distinction':
      break;
  }
}
