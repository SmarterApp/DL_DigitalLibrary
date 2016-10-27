<?php
namespace sbac_core\components\colorbox;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   */
  function hook_init() {
    drupal_add_js($this->_path . '/js/colorbox.js');
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}



