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
              <span class="devtools-tooltip account-tooltip">
                <a href="#" class="devtools-tooltip-trigger">' . format_username($account) . '</a>
                <div class="devtools-tooltip-body">' . render($account_renderable) . '</div>
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
 * Output for Display Suite field "Review Helpfulness"
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_review_helpfulness($variables) {
  $output = '';

  $entity = $variables['entity'];

  $query = "  SELECT  SUM(IF(value = 1, 1, 0)) AS `yes`,
                      SUM(IF(value = 1, 0, 1)) AS `no`
              FROM    votingapi_vote
              WHERE   entity_type = 'review'
              AND     entity_id = :id
           ";

  $vals = db_query($query, array(
    ':id' => $entity->id,
  ))->fetchObject();

  $count = 0;
  $total = 0;
  $percent = 0;

  if ($vals && isset($vals->yes)) {
    $count = $vals->yes;
    $total = ($vals->yes + $vals->no);

    // no division by zero
    if ($total) {
      $percent = round(($count / $total * 100));
    }
  }

  $output .= t('!count of !total people (!percent%) found this review helpful', array(
    '!count' => '<span class="count">' . $count . '</span>',
    '!total' => '<span class="total">' . $total . '</span>',
    '!percent' => '<span class="percent">' . $percent . '</span>',
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
  if ($entity->id && ($entity->uid == $user->uid || in_array('administrator', $user->roles))) {
    $trigger_id = 'review-delete';
    $url = 'node/' . $entity->node_id . '/review/end_use/delete/' . $trigger_id . '/' . $entity->id;

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'button',
        ),
        'id' => $trigger_id,
      ),
    );

    $output = l(t('Delete'), $url, $options);
  }
  return $output;
}

/**
 * Helpful Vote Widget
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_review_vote($variables) {
  $output = '';

  $entity = $variables['entity'];

  $machine_name = 'review_helpful';
  $widgets = variable_get(RATE_VAR_WIDGETS, array());
  foreach ($widgets as $widget_id => $widget) {
    if ($widget->name != $machine_name) {
      continue;
    }

    $output .= rate_generate_widget($widget_id, 'review', $entity->id);
  }

  return $output;
}