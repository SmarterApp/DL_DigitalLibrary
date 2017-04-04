<?php

function theme_taskit_tabs($variables) {
  $output = '
              <div id="taskit-tabs">
                <div class="clearfix">
                  ' . $variables['tabs'] . '
                </div>
                <div class="taskit-clear"></div>
              </div>
            ';

  return $output;
}

function theme_taskit_interval($variables) {
  $name = $variables['interval']['name'];
  $class = preg_replace('/[^a-zA-Z0-9]/', '_', strtolower($name));
  if ($name == 'prior') {
    $name = t(strtolower(date('l', $variables['interval']['from'])));
  }
  if ($variables['js_interval'] != NULL && $variables['js_interval'] == 'interval-' . $class) {
    $output = $variables['content'];
  }
  else {
    if (!empty($name)) {
      $variables['content'] = '<h3>' . $name . '</h3>' . $variables['content'];
    }
    $output = '<div class="taskit-interval interval-' . $class . '">' . $variables['content'] . '</div>';
  }
  return $output;
}

function theme_taskit_group($variables) {
  $name = $variables['name'];
  $class = preg_replace('/[^a-zA-Z0-9]/', '_', strtolower($name));
  if ($name == 'prior') {
    $name = t(strtolower(date('l', $variables['interval']['from'])));
  }
  if ($variables['js_interval'] != NULL && $variables['js_interval'] == 'interval-' . $class) {
    $output = $variables['content'];
  }
  else {
    if (!empty($name)) {
      $variables['content'] = '<h3>' . $name . '<span class="taskit-group-expander"><i class="material-icons"></i></span></h3>'
        . '<div class="taskit-interval-content">'
        . $variables['content']
        . '</div>';
    }
    $collapsed = (!empty($variables['collapsed'])) ? 'taskit-group-collapsed' : '';
    $output = "<div class='taskit-interval taskit-interval-group {$collapsed} interval-{$class}'>"
      . $variables['content']
      . '</div>';
  }
  return $output;
}

function theme_taskit_row($variables) {
  $task_id = $variables['task']->getTaskId();

  $output = '
              <div id="taskit-' . $task_id . '" class="taskit-row ' . $variables['task']->getClasses() . '">
                <div class="item">
                  ' . $variables['rendered'] . '
                </div>

                <div class="remove">
                  ' . l(t('x'), 'taskit/state/nojs/' . $task_id . '/remove', array('attributes' => array('class' => 'remove-trigger use-ajax'))) . '
                </div>
                
                <div class="taskit-clear"></div>
              </div>
            ';

  return $output;
}


function theme_taskit_row_historical($variables) {
  $task_id = $variables['task']->getTaskId();

  if (isset($variables['task']->is_completed) && $variables['task']->is_completed) {
    $state = t('Completed');
    $state_class = 'completed';
  }
  else {
    $state = t('Removed');
    $state_class = 'removed';
  }

  $output = '
              <div id="taskit-' . $task_id . '" class="taskit-row ' . $variables['class'] . ' taskit-historical">
                <div class="item">
                  ' . $variables['rendered'] . '
                </div>

                <div class="state ' . $state_class . '">
                  <div class="content">' . $state . '</div>
                </div>
                
                <div class="taskit-clear"></div>
              </div>
            ';

  return $output;
}
