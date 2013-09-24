<?php

/**
 * The form to initialize End Use modal
 * @param  [type] $form           [description]
 * @param  [type] $form_state     [description]
 * @param  [type] $node           [description]
 * @param  [type] $state          [description]
 * @param  [type] $trigger_id     [description]
 * @return [type]                 [description]
 */
function review_end_use_form($form, &$form_state, $node, $state, $trigger_id) {
  $form = array();

  // cancel state
    $form['state_cancel']['intro'] = array(
      '#markup' => '
                    <div class="intro">
                      ' . t('Cancelling your review will permanently clear all the information you have entered from the system.') . '
                    </div>
                   ',
    );

    $form['state_cancel']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel Review'),
    );

  // submit state
    $form['state_submit']['intro'] = array(
      '#markup' => '
                    <div class="intro">
                      ' . t('Submitting your review will make it available to all the Digital Library members.') . '
                    </div>
                   ',
    );

    $form['state_submit']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );

  // dialog configuration
    $dialog_common_options = array(
      'width' => '700px',
      'position' => 'center',
    );

  // state configuration
    $state_common_options = array(
      'close_link' => TRUE,
      'close_link_class' => array(
        'button',
        'radius',
      ),
    );

    $form_state['dialog_settings'] = array(
      'current_state' => $state,
      'trigger_id' => $trigger_id,
      'states' => array(

        'cancel' => array(
          'dialog' => array('title' => t('You are about to cancel the review')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_cancel']['submit'])),
          'submit_autoclose' => TRUE,
          'submit_redirect' => url('node/' . $node->nid . '/feedback/redirect/review-reviews', array('absolute' => TRUE)),
          'close_link_text' => t('Continue Review'),
        ) + $state_common_options,

        'submit' => array(
          'dialog' => array('title' => t('You are about to submit your review')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_submit']['submit'])),
          'submit_autoclose' => TRUE,
          'close_link_text' => t('Cancel'),
          'submit_js_callback' => array(
            'behavior' => 'review',
            'method' => 'submit',
          )
        ) + $state_common_options,

      ),
    );

  dialog_form_prepare($form, $form_state);

  return $form;
}

/**
 * Submit handler for review_end_use_form().
 */
function review_end_use_form_submit($form, &$form_state) {
  $state = $form_state['dialog_settings']['current_state'];

  switch ($state) {
    case 'cancel':

      break;
  }
}
