<?php

/**
 * Disables & hides a form element.
 * @param  [type] $element [description]
 * @return [type]          [description]
 */
function form_hide(&$element) {
  list($handler, $handler_data) = devtools_func_handler(__FUNCTION__, func_get_args());

  if ($handler) {
    return $handler_data;
  }
  else {
    $element['#attributes']['disabled'] = TRUE;
    $element['#attributes']['class'][] = 'devtools-form-hide';
  }
}

/**
 * Determines the button which was clicked to trigger form submission and
 * returns its machine name.
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function form_get_op($form_state) {
  $operation = FALSE;  
  
  foreach ($form_state['buttons'] as $button) {
    if ($button['#value'] == $form_state['values']['op']) {
      $operation = $button['#parents'][0];
      break;
    }
  }

  return $operation;
}