<?php

/**
 * Output for Display Suite field "Flagging Form"
 *
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_flagging_form($variables) {
  $output = '';

  $entity = &$variables['entity'];

  // don't show this on Preview
  if (isset($entity->id)) { 
    $entity_type_name = 'flag';
    $bundle_name = 'review_end_use';

    $entity_type = entity_type_load($entity_type_name);
    $bundle = bundle_load($entity_type_name, $bundle_name);
    
    $flag = entity_create($entity_type->name, array('type' => $bundle->name));
    $flag->target_type = 'review';
    $flag->target_id = $entity->id;
    $flag->nid = $entity->node_id;

    $form = drupal_get_form('eck__entity__form_add_' . $entity_type_name . '_' . $bundle_name, $flag);

    $output .= drupal_render($form);
  }

  return $output;
}