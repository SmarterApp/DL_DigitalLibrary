<?php
namespace sbac_core\components\sections;

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
      'sections' => array(
        'variables' => array(
          'sections' => NULL,
          'name' => NULL,
        ),
        'template' => 'sections',
        'preprocess functions' => array(
          'sections_preprocess',
        ),
      ),
    );

    foreach ($items as &$item) {
      $item += $base;
    }

    return $items;
  }

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'sections.inc',
      'file path' => $this->_path,
    );

    $items['section-get-content'] = array(
      'title' => 'Get Section Content',
      'page callback' => 'section_get_content',
      'access arguments' => array('access content'),
      'file' => 'sections.inc',
    ) + $base;

    return $items;
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}