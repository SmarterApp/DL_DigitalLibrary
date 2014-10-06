<?php

/**
 * The form to initialize End Use modal
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @param  [type] $node       [description]
 * @param  [type] $state      [description]
 * @param  [type] $trigger_id [description]
 * @param  [type] $id         [description]
 * @return [type]             [description]
 */
function review_end_use_form($form, &$form_state, $node, $state, $trigger_id, $id = NULL) {
  $form = array();

  // save entity id
    if ($id) {
      $form['entity_id'] = array(
        '#type' => 'hidden',
        '#value' => $id,
      );
    }

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

  // delete state
    $form['state_delete']['intro'] = array(
      '#markup' => '
                    <div class="intro">
                      ' . t('Deleting this review will remove it permanently from the system. All votes and flags
                        will also be deleted.') . '
                    </div>
                   ',
    );

    $form['state_delete']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Review'),
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
          'dialog' => array('title' => t('You are about to cancel the Review')) + $dialog_common_options,
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
          ),
        ) + $state_common_options,

        'delete' => array(
          'dialog' => array('title' => t('You are about to delete this review')) + $dialog_common_options,
          'submit' => array('submit' => array('element' => &$form['state_delete']['submit'])),
          'submit_autoclose' => TRUE,
          'close_link_text' => t('Cancel'),
          'submit_redirect' => url('node/' . $node->nid . '/feedback/redirect/review-reviews', array('absolute' => TRUE)),
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

    case 'submit':

      break;

    case 'delete':

      if (isset($form_state['values']['entity_id'])) {
        entity_delete('review', $form_state['values']['entity_id']);

        drupal_set_message(t('Your review has been deleted.'));
      }

      break;
  }
}
