<?php
namespace sbac_core\components\field_xss;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'field_ui_field_edit_form' && in_array($form['#field']['type'], array('text', 'text_with_summary', 'text_long'))) {
      $form['instance']['xss'] = array(
        '#type' => 'checkbox',
        '#default_value' => isset($form['#instance']['xss']) ? $form['#instance']['xss'] : 0,
        '#title' => t('Perform XSS validation'),
      );
    }
  }

  /**
   * Extends hook_field_attach_validate().
   */
  function hook_field_attach_validate($entity_type, $entity, &$errors) {
    $info = entity_get_info($entity_type);

    if (!isset($info['entity keys']['bundle']) || !$info['entity keys']['bundle']) {
      return;
    }
    
    $bundle_key = $info['entity keys']['bundle'];

    $lang = isset($entity->language) ? $entity->language : LANGUAGE_NONE;
    $fields_list = field_info_instances($entity_type, $entity->{$bundle_key});

    foreach ($fields_list as $field_name => $field_settings) {
      if (isset($field_settings['xss']) && $field_settings['xss']) {
        $field_items = field_get_items($entity_type, $entity, $field_name, $lang);

        foreach ($field_items as $delta => $item) {
          if (isset($item['value']) && $item['value'] != filter_xss($item['value'])) {
            $errors[$field_name][$lang][$delta][] = array(
              'error' => $field_name,
              'message' => t('Field contains invalid content.'),
            );
          }
        }
      }
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}