<?php
namespace sbac_core\components\user;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/
  
  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'user.pages.inc',
      'file path' => $this->_path,
    );

    $items['admin/sbac/users'] = array(
      'title' => 'User Settings', 
      'page callback' => 'sbac_core_index_page',
      'access arguments' => array('configure sbac'), 
      'type' => MENU_NORMAL_ITEM,
    ) + $base;

    return $items;
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}



