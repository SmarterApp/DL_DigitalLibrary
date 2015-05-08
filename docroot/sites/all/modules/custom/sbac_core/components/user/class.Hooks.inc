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

  /**
   * Extends hook_username_alter().
   */
  function hook_username_alter(&$name, $account) {
    // change username to first/last names when they're available
    if (isset($account->field_first_name[LANGUAGE_NONE][0]['safe_value'])) {
      $name = $account->field_first_name[LANGUAGE_NONE][0]['safe_value'];

      // if (isset($account->field_last_name[LANGUAGE_NONE][0]['safe_value'])) {
      //   $name .= ' ' . $account->field_last_name[LANGUAGE_NONE][0]['safe_value'];
      // }
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}



