<?php
namespace sbac_core\components\flag;

class Hooks extends \devtools\Hooks {
  const AJAX_CALLBACK = 'flag_review_end_use_ajax';
  const FORM_WRAPPER = 'flag-review-end-use-wrap';

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
      if (isset($form_state['build_info']['args'][0])) {
        $form['#attached']['css'][] = $this->_path . '/css/flag.css';
        $form['#attached']['js'][] = $this->_path . '/js/flag.js';

        $flag = $form_state['build_info']['args'][0];
        $review = entity_load_single('review', $flag->target_id);

        $form['#validate'][] = 'flag_review_end_use_validate';
        $form['#submit']= array(
          // we overwrite rather than append, as we'll call the eck submit
          // handler in our own
          'flag_review_end_use_submit',
        );

        $form['#prefix'] = '<div class="' . $this::FORM_WRAPPER . '" id="' . $this::FORM_WRAPPER . '-' . $review->id . '">';
        $form['#suffix'] = '</div>';
      
        $form['target_type']['#value'] = $flag->target_type;
        $form['target_type']['#weight'] = -99;
        $form['target_type']['#access'] = FALSE;

        $form['target_id']['#value'] = $flag->target_id;
        $form['target_id']['#weight'] = -99;
        $form['target_id']['#access'] = FALSE;

        $form['nid']['#value'] = $flag->nid;
        $form['nid']['#weight'] = -99;
        $form['nid']['#access'] = FALSE;

        $form['being_moderated']['#value'] = 0;
        $form['being_moderated']['#weight'] = -99;
        $form['being_moderated']['#access'] = FALSE;

        $form['flag_selected']['#value'] = 0;
        $form['flag_selected']['#weight'] = -99;
        $form['flag_selected']['#access'] = FALSE;

        $form['flag_comment']['#value'] = '';
        $form['flag_comment']['#weight'] = -99;
        $form['flag_comment']['#access'] = FALSE;

        $form['urgent']['#value'] = 0;
        $form['urgent']['#weight'] = -99;
        $form['urgent']['#access'] = FALSE;

        $form['action'] = array(
          '#type' => 'select',
          '#options' => array(
            'validate' => 'validate',
            'submit' => 'submit',
          ),
          '#default_value' => 'validate',
          '#attributes' => array(
            'class' => array(
              'submit-action',
              'hide',
            ),
          ),
        );

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
            drupal_add_library('dialog', 'dialog');
            $trigger_id = 'flag-review-' . $review->id;

            $text = t('Flag Review Modal');

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
                  'hide',
                ),
                'id' => $trigger_id,
              ),
            );

            $form['actions']['flag'] = array(
              '#markup' => l($text, $url, $options),
            );

          // submit button
            $form['actions']['submit'] = $form['submit'];
            $form['actions']['submit']['#value'] = t('Flag Review');
            $form['actions']['submit']['#ajax'] = array(
              'callback' => $this::AJAX_CALLBACK,
              'wrapper' => $this::FORM_WRAPPER . '-' . $review->id,
            );
            $form['actions']['submit']['#attributes']['class'][] = 'final-submit';

            unset($form['submit']);
        }

        $settings = array(
          'flag' => array(
            'form_error' => -1,
          )
        );

        drupal_add_js($settings, 'setting');
      }
    }
  }

  /**
   * Extends hook_entity_view().
   */
  function hook_entity_view_alter(&$build, $type) {
    if ($type == 'review') {
      $build['#prefix'] = '<div class="entity-review-wrap" id="entity-review-' . $build['#entity']->id . '">';
      $build['#suffix'] = '</div>';
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /*----------------------------------------------------------------------------
      INTERNAL / HELPERS
  ----------------------------------------------------------------------------*/
}



