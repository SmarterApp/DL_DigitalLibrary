<?php

/**
 * The form to initialize Review Flagging Form.
 * @param  [type] $form           [description]
 * @param  [type] $form_state     [description]
 * @param  [type] $review         [description]
 * @param  [type] $state          [description]
 * @param  [type] $trigger_id     [description]
 * @return [type]                 [description]
 */
function flag_review_modal_form($form, &$form_state, $review, $state, $trigger_id) {
  $form = array();

  // submit state
    $form['state_submit']['intro'] = array(
      '#markup' => '
                    <div class="intro">
                      ' . t("If you proceed the Digital Library moderators will be notified. 
                        They will review this resource based on your input, so please be 
                        sure any comments you've provided are clear and actionable.") . '
                    </div>
                   ',
    );

    $form['state_submit']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Flag Review'),
    );

  // state configuration
    $form_state['dialog_settings'] = array(
      'current_state' => $state,
      'trigger_id' => $trigger_id,
      'states' => array(

        'submit' => array(
          'dialog' => array(
            'title' => t('You are about to flag this review'),
            'width' => '700px',
            'position' => 'center',
          ),
          'submit' => array('submit' => array('element' => &$form['state_submit']['submit'])),
          'submit_autoclose' => TRUE,
          'submit_js_callback' => array(
            'behavior' => 'flag',
            'method' => 'submit_modal_callback_flag',
            'data' => array(
              'review_id' => $review->id,
              'review_wrapper' => '#flag-review-end-use-wrap-' . $review->id,
            ),
          ),
          'close_link' => TRUE,
          'close_link_text' => t('Cancel'),
          'close_link_class' => array(
            'button',
            'radius',
          ),
        ),

      ),
    );

  dialog_form_prepare($form, $form_state);

  return $form;
}

/**
 * Submit handler for flag_review_modal_form().
 */
function flag_review_modal_form_submit($form, &$form_state) {
  $review = $form_state['build_info']['args'][0];

  $state = $form_state['dialog_settings']['current_state'];

  switch ($state) {
    case 'start':
      global $user;

      break;

    case 'cancel':

      break;
  }
}
