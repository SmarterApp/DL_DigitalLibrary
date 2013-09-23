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

  $created = isset($entity->created) ? $entity->created : time();

  $output .= t('By !name on !date', array(
    // '!name' => l(),
    '!date' => format_date($created, 'medium'),
  ));

  return $output;
}