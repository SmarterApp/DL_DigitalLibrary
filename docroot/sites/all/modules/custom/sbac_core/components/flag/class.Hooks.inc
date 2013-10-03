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
      'page arguments' => array(2),
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
    if (preg_match('/eck__entity__form_(add|edit)_flag_review_end_use/', $form_id)) {
      $form['#attached']['css'][] = $this->_path . '/css/flag.css';
      $form['#attached']['js'][] = $this->_path . '/js/flag.js';

      $form['#prefix'] = '<div class="flag-review-end-use-wrap">';
      $form['#suffix'] = '</div>';

      if (isset($form_state['build_info']['args'][0])) {
        $flag = $form_state['build_info']['args'][0];
        $review = entity_load_single('review', $flag->target_id);

        $form['target_type']['#value'] = $flag->target_type;
        $form['target_type']['#weight'] = -99;
        $form['target_type']['#access'] = FALSE;

        $form['target_id']['#value'] = $flag->target_id;
        $form['target_id']['#weight'] = -99;
        $form['target_id']['#access'] = FALSE;

        $form['actions'] = array(
          '#prefix' => '<div class="actions">',
          '#suffix' => '</div>',
          '#weight' => 99,
        );

        if (!match_uri('admin')) {
          // cancel button
            $form['actions']['cancel'] = array(
              '#markup' => '<a href="#" class="button secondary flag-cancel">' . t('Cancel') . '</a>',
            );

          // flag button
            $trigger_id = 'flag-review-' . $review->id;

            $text = t('Flag Review');

            $url = implode('/', array(
              'flag',
              'review',
              $review->id,
              'submit',
              $trigger_id,
            ));

            $options = array(
              'attributes' => array(
                'class' => array(
                  'use-ajax',
                  'use-dialog',
                  'button',
                  'radius',
                ),
                'id' => $trigger_id,
              ),
            );

            $form['actions']['flag'] = array(
              '#markup' => l($text, $url, $options),
            );

          // submit button
            $form['actions']['submit'] = $form['submit'];
            unset($form['submit']);
        }
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



