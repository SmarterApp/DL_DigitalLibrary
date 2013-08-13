<?php
namespace sbac_core\components\resource;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    // resource node add/edit form
    if ($form_id == 'resource_node_form' && isset($form['nid']['#value']) && $form['nid']['#value']) {
        
    }
  }


  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}