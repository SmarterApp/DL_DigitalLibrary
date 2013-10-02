<?php

/**
 * Output for Display Suite field "Flagging Form"
 *
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_flagging_form($variables) {
  $entity = &$variables['element'];

  $form = eck__entity__add('flag', 'review_end_use');

  return drupal_render($form);
}