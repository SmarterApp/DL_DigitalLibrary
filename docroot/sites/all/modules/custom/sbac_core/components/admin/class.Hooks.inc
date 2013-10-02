<?php
namespace sbac_core\components\admin;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   * @return [type] [description]
   */
  function hook_init() {
    if (variable_get('no_puke_design', FALSE)) {
      drupal_add_css($this->_path . '/css/normal_colors.css');
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