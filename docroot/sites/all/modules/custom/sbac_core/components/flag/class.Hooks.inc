<?php
namespace sbac_core\components\flag;

class Hooks extends \devtools\Hooks {

  /**
   * Post-initialization operations.
   * @return [type] [description]
   */
  function postInit() {
    // add custom Display Suite fields
    $ds_args = array(
      'path' => $this->_path,
      'file' => 'flag.theme.inc',
      'variables' => array(),
    );

    add_ds_field('review',  array(
      'key' => 'flagging_form',
      'name' => t('Flagging Form'),
    ) + $ds_args);
  }

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Don't remove!
   */
  function hook_init() {

  }

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $items = array();

    $base = array(
      'file' => 'flag.pages.inc',
      'file path' => $this->_path,
    );

    $items['flag/review/%'] = array(
      'title' => 'Flag Review',
      'page callback' => 'flag_review_ajax_page',
      'access callback' => 'flag_access',
      'access arguments' => array('create flag', 1 , 2),
      'type' => MENU_CALLBACK,
    ) + $base;

    return $items;
  }

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id, $data) {
    if ($form_id == 'eck__entity__form_add_flag_review_end_use') {
      $form['#attached']['css'][] = $this->_path . '/css/flag.css';
      $form['#attached']['js'][] = $this->_path . '/js/flag.js';

      $form['#prefix'] = '<div class="flag-review-end-use-wrap">';
      $form['#suffix'] = '</div>';

      if (isset($form_state['build_info']['args'][0])) {
        $flag = $form_state['build_info']['args'][0];

        $form['target_type']['#value'] = $flag->target_type;
        $form['target_type']['#access'] = FALSE;

        $form['target_id']['#value'] = $flag->target_id;
        $form['target_id']['#access'] = FALSE;

        $form['actions'] = array(
          '#prefix' => '<div class="actions">',
          '#suffix' => '</div>',
        );

        $form['actions']['cancel'] = array(
          '#markup' => '<a href="#" class="button secondary flag-cancel">' . t('Cancel') . '</a>',
        );

        $form['actions']['submit'] = $form['submit'];
        unset($form['submit']);

        $form['actions']['submit']['#value'] = t('Flag Review');
      }
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /*----------------------------------------------------------------------------
      INTERNAL / HELPERS
  ----------------------------------------------------------------------------*/
}



