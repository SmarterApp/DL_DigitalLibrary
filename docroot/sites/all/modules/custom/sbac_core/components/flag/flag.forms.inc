<?php

/**
 * AJAX submit handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_ajax($form, &$form_state) {
  return $form;
}

/**
 * Validation handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_validate($form, &$form_state) {
  
}

/**
 * Submit handler for ECK Flag - Review End Use form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function flag_review_end_use_submit($form, &$form_state) {
  dsmm('submit handler');
}