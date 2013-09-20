<?php
namespace sbac_core\components\review;

class Hooks extends \devtools\Hooks {
  const AJAX_CALLBACK = 'review_form_ajax';
  const FORM_WRAPPER = 'review-end-use-wrap';

  protected $_info = '';
  protected $_bundles = array();

  protected $_fields = array(
    'title',
    'field_details',
    'field_student_learning',
    'field_pro_dev',
    'field_ease_use',
    'field_appropriate_for',
  );

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
      // wrap in a selector that'll be targeted for AJAX replacement on form submissions
        $form['#prefix'] = '<div id="' . $this::FORM_WRAPPER . '">';
        $form['#suffix'] = '</div>';

      // we store the node in state because it won't always be available for grabs (ex. ajax requests, which have
      // a non-node URI)
        if (!isset($form_state['node_object'])) {
          $node = current_node();
          $form_state['node_object'] = $node;
        }

      // prep structure for multi-step functionality
        if (!isset($form_state['current_state'])) {
          $form_state['current_state'] = 'create';
        }

      // common elements
        $intro = array(
          '#type' => 'markup',
          '#weight' => -15,
          '#prefix' => '<div class="intro">',
          '#suffix' => '</div>',
        );

        $actions = array(
          '#type' => 'container',
          '#weight' => 10,
          '#attributes' => array(
            'class' => array(
              'actions-wrapper'
            ),
          ),
          'submit' => array(
            '#type' => 'submit',
            '#value' => t('Submit'),
            '#submit' => array(
              'review_form_submit',
              'review_form_next',
            ),
            '#ajax' => array(
              'callback' => $this::AJAX_CALLBACK,
              'wrapper' => $this::FORM_WRAPPER,
            ),
          ),
        );

        // remove default submit button
        unset($form['submit']);
        
        // add our validation handler in addition to existing ECK one
        $form['#validate'][] = 'review_form_validate';

      // set up the 'create' state
        $form['state_create']['intro'] = $intro;
        $form['state_create']['actions'] = $actions;
        $this->hook_form_alter_review_create($form, $form_state, $form_state['node_object']);

      // set up the 'preview' state
        $form['state_preview']['intro'] = $intro;
        $form['state_preview']['actions'] = $actions;
        $this->hook_form_alter_review_preview($form, $form_state, $form_state['node_object']);

      // handle state
        foreach ($form as $key => $item) {
          if (  $key{0} != '#' && 
                strpos($key, 'state_') === 0 && 
                $key != 'state_' . $form_state['current_state']) {
            $form[$key]['#access'] = FALSE;
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

  /**
   * Form helper for review 'create' state.
   * @param  [type] $form       [description]
   * @param  [type] $form_state [description]
   * @param  [type] $node       [description]
   * @return [type]             [description]
   */
  function hook_form_alter_review_create(&$form, &$form_state, $node) {
    // add intro text
    $form['state_create']['intro']['#markup'] = t('
      Have you used this resource? If so, share your feedback in the space provided below. Be sure to
      give your review a title, enter your feedback and rate the resource. Your feedback is valuable and helps insure
      that the Digital Library continues to meet your needs.
    ');

    // when a form step is submitted, review_form_submit() stores the form values in form state, and we must pull
    // those values back so they can be used to re-populate the form
    $values = array();
    if (isset($form_state[$form_state['current_state'] . '_values'])) {
      $values = $form_state[$form_state['current_state'] . '_values'];
    
      form_set_defaults($this->_fields, $values, $form);
    }

    // move 'regular' fields into state
    foreach ($this->_fields as $field_key) {
      $form['state_create'][$field_key] = $form[$field_key];
      unset($form[$field_key]);
    }

    // move title field to the top of the form and enable max
    // character count
    $form['state_create']['title']['#weight'] = -10;
    element_maxlength($form['state_create']['title'], 100, 'Character count: <strong>@remaining</strong>');

    // disable access to properties
    $form['status']['#access'] = FALSE;
    $form['node_id']['#access'] = FALSE;

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

    $form['state_create']['actions']['cancel'] = array(
      '#markup' => l(t('Cancel'), $url, $options),
      '#weight' => -10,
    );

    // preview button
    $form['state_create']['actions']['submit']['#value'] = t('Preview');
  }

  /**
   * Form helper for review 'preview' state.
   * @param  [type] $form       [description]
   * @param  [type] $form_state [description]
   * @param  [type] $node       [description]
   * @return [type]             [description]
   */
  function hook_form_alter_review_preview(&$form, &$form_state, $node) {
    if (!isset($form_state['create_values'])) {
      return;
    }

    $form['state_preview']['intro']['#markup'] = t('
      This is your review as it will appear to others. Your profile card will be included adjacent to 
      your review (accessible by hovering your mouse over the link). You can adjust your !link to control
      what others see.', array(
        '!link' => l(t('privacy settings'), 'user')
    ));

    global $user;

    $entity = new \stdClass();
    $entity->status = 1;
    $entity->type = 'end_use';
    $entity->is_new = 1;
    $entity->uid = $user->uid;
    $entity->node_id = $node->nid;

    $values = $form_state['create_values'];
    foreach ($this->_fields as $field_key) {
      if (isset($values[$field_key])) {
        $entity->{$field_key} = $values[$field_key];
      }
    }

    entity_save('review', $entity);

    /*
    foreach ($this->_fields as $field_key) {
      if (in_array($field_key, array(
        'field_student_learning',
        'field_pro_dev',
        'field_ease_use',
        // 'field_appropriate_for',
      ))) {
        continue;
      }

      $tree = array();
      flatten_tree($values[$field_key], $tree);

      if (sizeof($tree) > 1) {
        $val = array();

        foreach ($tree as $path_tree) {
          $val[] = array_pop($path_tree);
        }
      }
      else {
        $val = array_pop($tree[0]);
      }

      // dsmm($field_key);
      // dsmm($val);
      $wrapper->{$field_key}->set($val);
      dsmm('set: ' . $field_key);
    }

    */
    // dsmm($new);

    // $entity = entity_load_single('review', 1);
    // dsmm($entity);

    // $entity_render = entity_view('review', array(1 => $entity));

    $form['state_preview']['view'] = array(
      '#type' => 'markup',
      '#markup' => 'test',//render($entity_render),
    );

    //edit button
    $form['state_preview']['actions']['edit'] = array(
      '#type' => 'submit',
      '#value' => t('Edit'),
      '#weight' => -10,
      '#limit_validation_errors' => array(),
      '#submit' => array(
        'review_form_submit',
        'review_form_previous',
      ),
      '#ajax' => array(
        'callback' => $this::AJAX_CALLBACK,
        'wrapper' => $this::FORM_WRAPPER,
      ),
    );
  }
}

