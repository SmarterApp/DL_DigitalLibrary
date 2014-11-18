<?php
namespace sbac_core\components\admin;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   */
  function hook_init() {
    if (variable_get('no_puke_design', FALSE)) {
      drupal_add_css($this->_path . '/css/normal_colors.css');
    }

    if (match_uri('admin')) {
      drupal_add_css($this->_path . '/css/admin.css');
    }
  }

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $items['admin/sbac'] = array(
      'title' => 'SBAC Configuration',
      'page callback' => 'sbac_core_index_page',
      'access arguments' => array('configure sbac'),
      'weight' => 9,
    );

    return $items;
  }

  /**
   * Extends hook_menu_alter().
   */
  function hook_menu_alter(&$items) {
    // override the people page with a custom callback
    $items['admin/people']['page callback'] = 'sbac_user_admin';
    $items['admin/people']['file'] = 'admin.pages.inc';
    $items['admin/people']['file path'] = $this->_path;
  }

  /**
   * Extends hook_permission().
   */
  function hook_permission() {
    return array(
      'configure sbac' => array(
        'title' => t('Configure SBAC.'),
        'description' => t('Grants permission to configure SBAC settings.'),
      ),
    );
  }
  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}