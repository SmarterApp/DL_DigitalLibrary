<?php
namespace sbac_core\components\resource;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_library_alter().
   */
  function hook_library_alter(&$libraries, $module) {
    if ($module == 'chosen') {
      $js = $libraries['chosen']['js']['sites/all/libraries/chosen/chosen.jquery.min.js'];
      $libraries['chosen']['js']['sites/all/libraries/chosen/chosen/chosen.jquery.min.js'] = $js;
      unset($libraries['chosen']['js']['sites/all/libraries/chosen/chosen.jquery.min.js']);

      $css = $libraries['chosen']['css']['sites/all/libraries/chosen/chosen.css'];
      $libraries['chosen']['css']['sites/all/libraries/chosen/chosen/chosen.css'] = $css;
      unset($libraries['chosen']['css']['sites/all/libraries/chosen/chosen.css']);
    }
  }

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