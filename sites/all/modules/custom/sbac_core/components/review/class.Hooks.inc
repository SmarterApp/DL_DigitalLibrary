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

  /**
   * Post-initialization operations.
   * @return [type] [description]
   */
  function postInit() {
    // add custom Display Suite fields
    $ds_args = array(
      'path' => $this->_path,
      'file' => 'review.theme.inc',
      'variables' => array(),
    );

    add_ds_field('review',  array(
      'key' => 'review_author',
      'name' => t('Review Author'),
    ) + $ds_args);

    add_ds_field('review',  array(
      'key' => 'review_helpfulness',
      'name' => t('Review Helpfulness'),
    ) + $ds_args);

    add_ds_field('review',  array(
      'key' => 'review_vote',
      'name' => t('Helpful Vote Widget'),
    ) + $ds_args);

    add_ds_field('review',  array(
      'key' => 'review_delete',
      'name' => t('Delete Button'),
    ) + $ds_args);
  }

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   *
   * Don't remove this empty method!! We must have this in order for this class
   * to get instantiated (and thus the postInit() method called) before Display
   * Suite's hooks fire and collect field data, otherwise the DS fields from
   * the postInit() method will be added *after* DS collects field data, neve
   * actually make their way into the site, and you'll be banging your head on
   * the desk for hours wondering why. Source: dent in desk.
   */
  function hook_init() {

  }

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

    $items['load_more/review/%node/%/%'] = array(
      'title' => 'Show More Reviews',
      'page callback' => 'review_load_more_ajax',
      'page arguments' => array(2, 3, 4),
      'access callback' => 'resource_access',
      'access arguments' => array('access review process', 2),
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

      // prep structure for multi-step functionality
        if (!isset($form_state['current_state'])) {
          $form_state['current_state'] = 'create';
        }

      // we store the node in state because it won't always be available for grabs (ex. ajax requests, which have
      // a non-node URI)
        if (!isset($form_state['node_object'])) {
          if ($node = current_node(TRUE)) {
            $form_state['node_object'] = $node;
          }
          elseif ($node = node_load($form['#entity']->node_id)) {
            $form_state['node_object'] = $node;
          }
          else {
            drupal_set_message(t('Could not find resource associated with this review.'), 'error');
          }
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

  /**
   * Extends hook_entity_view_alter().
   */
  function hook_entity_view_alter(&$build, $type) {
    // make sure a review's details text is limited to 140 chars on display
    if ($type == 'review' && $build['#view_mode'] == 'full') {
      $build['field_details'][0]['#markup'] = more_less_text($build['field_details'][0]['#markup'], 140);
    }
  }

  /**
   * Extends hook_theme_registry_alter().
   */
  function hook_theme_registry_alter(&$theme_registry) {
    if (isset($theme_registry['rate_template_yesno'])) {
      // change the widget's template
      $theme_registry['rate_template_yesno']['path'] = drupal_get_path('theme', 'SBAC') . '/templates';

      // remove the junk that is the original preprocessor function
      if ($index = array_search('rate_preprocess_rate_template_yesno', $theme_registry['rate_template_yesno']['preprocess functions'])) {
        unset($theme_registry['rate_template_yesno']['preprocess functions'][$index]);

        // fix keys
        $theme_registry['rate_template_yesno']['preprocess functions'] = array_merge($theme_registry['rate_template_yesno']['preprocess functions']);
      }
    }
  }


  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_rate_widget_alter().
   */
  function hook_rate_widget_alter(&$widget, $context) {
    if ($context['content_type'] == 'review' && $widget->name == 'review_helpful') {
      unset($widget->css);
    }
  }

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
      give your review a title, enter your feedback and rate the resource. Your feedback is valuable and helps ensure
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
    // Title and details are no longer mandatory.
    $form['state_create']['title']['#required'] = FALSE;
    $form['field_details']['und'][0]['value']['#required'] = FALSE;

    // disable access to properties
    $form['status']['#access'] = FALSE;
    $form['node_id']['#access'] = FALSE;
    $form['field_avg_rating']['#access'] = FALSE;

    // ensure node_id property is always populated
    $form['node_id']['#default_value'] = $form_state['node_object']->nid;

    // cancel button
    drupal_add_library('dialog', 'dialog');
    $trigger_id = 'review-cancel';
    $url = 'node/' . $node->nid . '/review/end_use/cancel/' . $trigger_id;

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'button',
        ),
        'id' => $trigger_id,
        'title' => 'Cancel',
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
    // Hide the field that stores average score.
    $form['field_avg_rating']['#access'] = FALSE;

    $form['state_preview']['intro']['#markup'] = t('
      This is your review as it will appear to others. Your profile card will be included adjacent to
      your review (accessible by hovering your mouse over the link). You can adjust your !link to control
      what others see.', array(
        '!link' => l(t('privacy settings'), 'user')
    ));

    global $user;

    // create the entity data structure for preview rendering purposes
    $entity = entity_create('review', array(
      'type' => 'end_use',
      'status' => 1,
      'uid' => $user->uid,
      'node_id' => $node->nid,
      'id' => NULL,
    ));

    // set submitted form values on the entity
    $values = $form_state['create_values'];
    foreach ($this->_fields as $field_key) {
      if (isset($values[$field_key])) {
        $entity->{$field_key} = $values[$field_key];
      }
    }

    // create renderable array
    $entity_render = entity_view('review', array(
      $entity,
    ));

    // render & add entity to the form data
    $form['state_preview']['view'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="preview">' . render($entity_render) . '</div>',
    );

    // footer text
    $form['state_preview']['footer_title'] = array(
      '#markup' => '<div class="footer-title">' . t('Are you happy with your review?') . '</div>',
    );

    $form['state_preview']['footer_body'] = array(
      '#markup' => '
                      <div class="footer-body">
                      ' . t('If so, submit it for everyone to see. If not, click edit to make changes.') . '
                      ' . t('Note: Smarter Balanced reserves the right to remove reviews that do not adhere to the
                        Terms of Service'). '
                      </div>
                   ',
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

    // submit button (hidden)
    $form['state_preview']['actions']['submit']['#limit_validation_errors'] = array();
    $form['state_preview']['actions']['submit']['#attributes']['class'][] = 'final-submit';
    $form['state_preview']['actions']['submit']['#attributes']['class'][] = 'hidden';
    unset($form['state_preview']['actions']['submit']['#ajax']);

    // submit button (modal)
    drupal_add_library('dialog', 'dialog');

    $trigger_id = 'review-submit';
    $url = 'node/' . $node->nid . '/review/end_use/submit/' . $trigger_id;

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'button',
        ),
        'id' => $trigger_id,
        'title' => 'Submit',
      ),
    );

    $form['state_preview']['actions']['submit_link'] = array(
      '#markup' => l(t('Submit'), $url, $options),
      '#weight' =>  10,
    );
  }
}

