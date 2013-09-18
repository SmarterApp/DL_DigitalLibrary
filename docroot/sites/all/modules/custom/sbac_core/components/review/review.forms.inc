<?php

/**
 * Validation handler for Review form
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function review_form_validate($form, &$form_state) {
  // perform profanity validation on title
  if (profanity_validate_text($form_state['values']['title'])) {
    form_set_error('title', profanity_error_message_text());
  }
}