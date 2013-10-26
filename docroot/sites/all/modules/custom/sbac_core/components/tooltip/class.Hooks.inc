<?php
namespace sbac_core\components\tooltip;

class Hooks extends \devtools\Hooks {
  /**
   * Extends hook_init().
   */
  public function hook_init() {
    devtools_add_js($this->_path . '/js/tooltip.js');
    devtools_add_css($this->_path . '/css/tooltip.css');
  }
}