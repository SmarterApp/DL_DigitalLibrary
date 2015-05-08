<?php
namespace sbac_core\components\more_less_text;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_theme().
   */
  function hook_theme($existing, $type, $theme, $path) {
    $base = array(
      'path' => $this->_path . '/templates',
    );

    $items = array(
      'more_less_text' => array(
        'variables' => array(
          'summary' => NULL,
          'full' => NULL,
          'show_open' => NULL,
        ),
        'template' => 'more_less_text',
      ),
    );

    foreach ($items as &$item) {
      $item += $base;
    }

    return $items;
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}