<?php
namespace sbac_core\components\maxlength_above;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    // add the new checkbox for maxlength settings
    if ($form_id == 'field_ui_field_edit_form' && module_exists('maxlength')) {
      if (isset($form['instance']['widget']['settings']['maxlength_js'])) {
        $default = NULL;
        if (isset($form['#instance']['widget']['settings']['maxlength_above'])) {
          $default = $form['#instance']['widget']['settings']['maxlength_above'];
        }

        $form['instance']['widget']['settings']['maxlength_above'] = array(
          '#type' => 'checkbox',
          '#title' => t('Display the character count down above the field.'),
          '#default_value' => $default,
        );
      }
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}