<?php

$plugin = array(
  'label'                   => 'Textfield',
  // subhooks
    // 'entity_view'           => 'sbac_feedback_textfield_property_entity_view',
    // 'entity_save'        => '',
    // 'entity_insert'      => '',
    // 'entity_update'      => '',
    // 'entity_delete'      => '',
    
  // renderables
    'default_widget'        => 'sbac_feedback_textfield_property_widget',
    // 'default_formatter'  => '',

  // alters
    // 'entity_info'           => 'sbac_feedback_textfield_property_entity_info',
    // 'property_info'         => 'sbac_feedback_textfield_property_property_info'
);

/**
 * Defines the widget form for our property.
 */
function sbac_feedback_textfield_property_widget($property, $vars) {
  $entity = $vars['entity'];

  $textfield = 0;
  if (isset($entity->textfield)) {
    $textfield = $entity->textfield;
  }

  $type = 'hidden';
  if (user_access('edit feedback properties')) {
    $type = 'textfield';
  }

  return array(
    '#type' => $type,
    '#title' => $vars['properties'][$property]['label'],
    '#default_value' => $textfield,
    '#weight' => 0,
  );
}
