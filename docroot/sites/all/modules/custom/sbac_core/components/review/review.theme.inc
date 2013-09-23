<?php

/**
 * Output for Display Suite field "Review Title"
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_review_title($variables) {
  $output = '';

  if (isset($variables['entity'])) {
    $review = $variables['entity'];
    
    $output = $review->title;
  }

  return $output;
}

/**
 * Output for Display Suite field "Review Author"
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_review_author($variables) {
  $output = '';

  $entity = $variables['entity'];

  $account = user_load($entity->uid);
  $account_output = user_view($account, 'tooltip');

  $created = isset($entity->created) ? $entity->created : time();

  $output .= t('By !name on !date', array(
    '!name' => '<a href="#">' . $account_output . '</a>',
    '!date' => format_date($created, 'simple'),
  ));

  return $output;
}