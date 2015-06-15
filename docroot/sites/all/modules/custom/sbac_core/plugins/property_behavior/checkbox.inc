<?php

$plugin = array(
  'label'           => 'Checkbox',
  'default_widget'  => 'sbac_feedback_checkbox_property_widget',
);

/**
 * Defines the widget form for our property.
 */
function sbac_feedback_checkbox_property_widget($property, $vars) {
  $entity = $vars['entity'];

  $checkbox = 0;
  if (isset($entity->checkbox)) {
    $checkbox = $entity->checkbox;
  }

  $type = 'hidden';
  if (user_access('edit feedback properties')) {
    $type = 'checkbox';
  }

  return array(
    '#type' => $type,
    '#title' => $vars['properties'][$property]['label'],
    '#default_value' => $checkbox,
    '#weight' => 0,
  );
}
