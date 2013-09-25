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
  $account_renderable = user_view($account, 'tooltip');

  $tooltip = '
              <span class="account-tooltip">
                <a href="#" class="account-tooltip-trigger">' . format_username($account) . '</a>
                <div class="account-tooltip-body">' . render($account_renderable) . '</div>
              </span>
             ';

  $created = isset($entity->created) ? $entity->created : time();

  $output .= t('By !name on !date', array(
    '!name' => $tooltip,
    '!date' => format_date($created, 'simple'),
  ));

  return $output;
}

/**
 * Output for Display Suite field "Delete Button"
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_review_delete($variables) {
  $output = '';

  $entity = $variables['entity'];

  global $user;
  if ($entity->uid == $user->uid || in_array('administrator', $user->roles)) {
    $trigger_id = 'review-delete';
    $url = 'node/' . $entity->node_id . '/review/end_use/delete/' . $trigger_id . '/' . $entity->id;

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'button',
          'radius',
        ),
        'id' => $trigger_id,
      ),
    );

    $output = l(t('Delete'), $url, $options);
  }
  return $output;
}