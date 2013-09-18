<?php
namespace sbac_core\components\review;

class Hooks extends \devtools\Hooks {
  protected $_info = '';
  protected $_bundles = array();

  function __construct() {
    $this->_info = field_info_bundles('review');
    $this->_bundles = array_keys($this->_info);
  }

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'review.pages.inc',
      'file path' => $this->_path,
    );

    $items['node/%node/review/end_use'] = array(
      'title' => 'End Use Review',
      'page callback' => 'resource_review_ajax_page',
      'page arguments' => array('end_use', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('access review process', 1),
      'type' => MENU_CALLBACK,
    ) + $base;

    return $items;
  }

  /**
   * Extends hook_page_build().
   */
  function hook_page_build(&$page) {
    $node = current_node();
    if ($node && $node->type == 'resource') {
      drupal_add_css($this->_path . '/css/review.css');
      drupal_add_js($this->_path . '/js/review.js');
    }
  }

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    $args = func_get_args();

    // feedback add/edit form
    if (preg_match('/^eck__entity__form_(edit|add)_review_(' . implode('|', $this->_bundles) . ')$/', $form_id, $matches)) {
      $node = current_node();

      if (!isset($form_state['stage'])) {
        $form_state['stage'] = 'create';
      }

      $form['title']['#weight'] = -10;
      element_maxlength($form['title'], 100, 'Character count: <strong>@remaining</strong>');
      
      $form['status']['#access'] = FALSE;

      $form['actions'] = array(
        '#type' => 'container',
        '#weight' => 10,
        '#prefix' => '<div class="actions">',
        '#suffix' => '</div>',
      );

      // cancel button
      $trigger_id = 'review-cancel';
      $url = 'node/' . $node->nid . '/review/end_use/cancel/' . $trigger_id;

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

      $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), $url, $options),
      );

      switch ($form_state['stage']) {
        case 'create':
          $intro_text = t('Have you used this resource? If so, share your feedback in the space provided below. Be sure to
          give your review a title, enter your feedback and rate the resource. Your feedback is valuable and helps insure
          that the Digital Library continues to meet your needs.');

          $form['actions']['preview'] = array(
            '#type' => 'submit',
            '#value' => t('Preview'),
            '#ajax' => array(
              'callback' => 'review_form_submit',
              'wrapper' => 'eck-entity-form-add-review-end-use',
            ),
          );

          break;

        case 'preview':
          $intro_text = t('This is your review as it will appear to others. Your profile card will be included adjacent to 
          your review (accessible by hovering your mouse over the link). You can adjust your !link to control
          what others see.', array('!link' => l(t('privacy settings'), 'user')));

          $disable = array(
            'title',
            'field_details',
            'field_student_learning',
            'field_pro_dev',
            'field_ease_use',
            'field_appropriate_for',
          );

          foreach ($disable as $field_name) {
            $form[$field_name]['#access'] = FALSE;
          }

          $form['actions']['submit'] = $form['submit'];

          break;
      }

      unset($form['submit']);
  
      $form['intro'] = array(
        '#type' => 'markup',
        '#weight' => -15,
        '#prefix' => '<div class="intro">',
        '#suffix' => '</div>',
        '#markup' => $intro_text,
      );

      $form['#validate'][] = 'review_form_validate';
      $form['#submit'] = array('review_form_submit');
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /*----------------------------------------------------------------------------
      INTERNAL / HELPERS
  ----------------------------------------------------------------------------*/
}

