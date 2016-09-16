<?php
namespace sbac_core\components\feedback;

class Hooks extends \devtools\Hooks {
  protected $_info = '';
  protected $_bundles = array();

  function __construct() {
    $this->_info = field_info_bundles('feedback');
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
      'file' => 'feedback.theme.inc',
      'variables' => array(),
    );

    add_ds_field('node',  array(
      'key' => 'resource_slideshow',
      'name' => t('Resource Slideshow'),
      'ui_limit' => array(
        'resource|*', // limit to displaying on Resource bundles
      ),
    ) + $ds_args);
  }

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   */
  function hook_init() {
    // redirect gate keeper entities to their appropriate resource node;
    // in the "natural" user-flow, the user will only end up here after
    // submitting a Gate Keeper entity as either "meets" or "doesn't meet."
    // we can use that info to direct the user to an appropriate tab
    if ($feedback = current_feedback()) {
      if (!isset($feedback->node_id)) {
        return;
      }

      if ($feedback->type == 'gate_keeper') {
        // figure out which review tab we want to default to
        $fragment = 'about';

        if ($feedback->completed) {
          if ($feedback->met_criteria) {
            $fragment = 'qc'; // quality review tab
          }
          else {
            $fragment = 'gk'; // gate keeper tab
          }
        }

        drupal_goto('node/' . $feedback->node_id, array(
          'fragment' => 'review-' . $fragment,
        ));
      }
      elseif ($feedback->type == 'qc') {
        drupal_goto('node/' . $feedback->node_id, array(
          'fragment' => 'review-qc',
        ));
      }
    }
    elseif (preg_match('#node/(\d+)/edit#', $_GET['q'], $matches)) {
      // can't edit resources unless they're in draft state
      $node = node_load($matches[1]);

      if ($node && $node->type == 'resource') {
        $states = array(
          'needs_review',
          'being_reviewed',
          'rejected',
          'approved',
          'published',
        );

        if (in_array($node->workbench_moderation['current']->state, $states) && !user_access('administer nodes')) {
          drupal_access_denied();
          exit();
        }
      }
    }

    // we need to re-arrange some hook calls to call our stuff *after* workbench, and
    // workbench attempts to set itself to run after everything else, so we run
    // workbench's stuff, and then our own.
    $hooks_cache = &drupal_static('module_implements');
    unset($hooks_cache['module_implements_alter']['workbench_email']);
    
    foreach ($hooks_cache as $hook => &$implementations) {
      if (strpos($hook, 'form') !== FALSE) {
        // call workbench's code
        if (module_exists('workbench_email')) {
          // workbench_email_module_implements_alter($implementations, $hook);
        }

        // now move our hook to the end
        if ($hook == 'form_node_form_alter' && isset($implementations['sbac_core'])) {
          $group = $implementations['sbac_core'];
          unset($implementations['sbac_core']);
          $implementations['sbac_core'] = $group;
        }
      }
    }
  }

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'feedback.pages.inc',
      'file path' => $this->_path,
    );

    $items['admin/sbac/feedback'] = array(
      'title' => 'Feedback Flow', 
      'page callback' => 'sbac_core_index_page',
      'access arguments' => array('configure sbac'), 
    ) + $base;

    $items['admin/sbac/feedback/gate_keeper'] = array(
      'title' => 'Gate Keeper', 
      'page callback' => 'drupal_get_form', 
      'page arguments' => array('feedback_gate_keeper_admin_form'),
      'access arguments' => array('configure sbac'), 
      'file' => 'feedback.admin.inc',
      'weight' => 0,
    ) + $base;

    $items['admin/sbac/feedback/quality_review'] = array(
      'title' => 'Quality Review', 
      'page callback' => 'drupal_get_form', 
      'page arguments' => array('feedback_quality_review_admin_form'),
      'access arguments' => array('configure sbac'), 
      'file' => 'feedback.admin.inc',
      'weight' => 1,
    ) + $base;

    $items['admin/sbac/feedback/post'] = array(
      'title' => 'Post', 
      'page callback' => 'drupal_get_form', 
      'page arguments' => array('feedback_post_admin_form'),
      'access arguments' => array('configure sbac'), 
      'file' => 'feedback.admin.inc',
      'weight' => 2,
    ) + $base;

    $items['node/%node/feedback'] = array(
      'title' => 'Feedback',
      'page callback' => 'resource_feedback_page',
      'page arguments' => array(1),
      'access callback' => 'resource_access',
      'access arguments' => array('view about', 1),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    ) + $base;

    $items['node/%node/feedback/gate-keeper'] = array(
      'title' => 'Gate Keeper',
      'page callback' => 'resource_feedback_ajax_page',
      'page arguments' => array('gate_keeper', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit gate keeper', 1),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CALLBACK,
    ) + $base;
    
    $items['node/%node/feedback/qc'] = array(
      'title' => 'Quality Criteria Review',
      'page callback' => 'resource_feedback_ajax_page',
      'page arguments' => array('qc', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit quality criteria', 1),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CALLBACK,
    ) + $base;

    $items['node/%node/feedback/post'] = array(
      'title' => 'Post',
      'page callback' => 'resource_feedback_ajax_page',
      'page arguments' => array('post', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit post', 1),
      'weight' => 3,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CALLBACK,
    ) + $base;

    $items['node/%node/feedback/redirect'] = array(
      'title' => 'Gate Keeper',
      'page callback' => 'resource_redirect_page',
      'page arguments' => array(1, 4),
      'access callback' => TRUE,
      'weight' => 2,
      'type' => MENU_CALLBACK,
    ) + $base;

    return $items;
  }

  /**
   * Extends hook_theme().
   */
  function hook_theme($existing, $type, $theme, $path) {
    $base = array(
      'path' => $this->_path . '/templates',
    );

    $items = array(
      'feedback_helpful_info' => array(
        'variables' => array(
          'helpful_info' => NULL,
        ),
        'template' => 'feedback_helpful_info',
      ),
      'qc_teaser' => array(
        'variables' => array(
          'id' => NULL,
          'author' => NULL,
          'created' => NULL,
          'headline' => NULL,
          'comments' => NULL,
        ),
        'template' => 'qc_teaser',
      ),
    );

    foreach ($items as &$item) {
      $item += $base;
    }

    return $items;
  }

  /**
   * Extends hook_permission().
   */
  function hook_permission() {
    return array(
      'edit feedback properties' => array(
        'title' => t('Edit Feedback properties.'),
        'description' => t('Grants permission to edit the properties on existing Feedback entities.'),
      ),
    );
  }

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    $args = func_get_args();

    // feedback add/edit form
    if (preg_match('/^eck__entity__form_(edit|add)_feedback_(' . implode('|', $this->_bundles) . ')$/', $form_id, $matches)) {
      // basic form data
        $bundle = $matches[2];

      // build form utility object to take care of the heavy lifting
        switch ($bundle) {
          case 'gate_keeper':
            $class_name = 'GateKeeper';
            break;

          case 'qc':
            $class_name = 'Qc';
            break;

          case 'post':
            $class_name = 'Post';
            break;
        }

        if ($class_name) {
          module_load_include('inc', 'sbac_core', 'components/feedback/includes/form_utility/class.Base');
          module_load_include('inc', 'sbac_core', 'components/feedback/includes/form_utility/class.' . $class_name);

          $full_class_name = 'sbac_core\\components\\feedback\\form_utility\\' . $class_name;
          $form_utility = new $full_class_name($form, $form_state, $this->_info[$bundle]);

          $form_utility->attachHelpfulInfo();
          $form_utility->process();
          $form_utility->postProcess();
        }
    }
    // resource node form on the main resource profile page (ie. edit tags)
    elseif ($form_id == 'resource_node_form' && isset($form_state['build_info']['args'][1]) && $form_state['build_info']['args'][1] == 'edit_tags') {
      $post_id = db_select('eck_feedback', 'f')
        ->condition('f.type', 'post')
        ->condition('f.node_id', $form_state['node']->nid)
        ->condition('f.created', _sbac_resource_resubmit_timestamp($form_state['node']->nid), '>')
        ->condition('f.status', 1)
        ->condition('f.completed', 0)
        ->condition('f.current', 1)
        ->fields('f', array('id'))
        ->orderBy('f.id', 'DESC')
        ->range(0, 1)
        ->execute()
        ->fetchField();
      $post = entity_load_single('feedback', $post_id);

      if (!empty($post)) {
        // remove data we're not interested in
          $remove = array(
            'group_basic',
            'group_materials',
            'group_summary',
            'group_advanced',
            'group_paradata'
          );

          foreach ($remove as $group) {
            unset($form['#groups'][$group], $form['#fieldgroups'][$group]);
          }

          foreach (array_keys($form) as $key) {
            $conditions = implode('|', array(
              'container_close',
              'container_open',
              'completed_flag',
              '_guidelines',
              'title_of_resource_',
            ));

            if (preg_match('#' . $conditions . '#', $key)) {
              unset($form[$key]);
            }
          }

          foreach ($form['#group_children'] as $field => $group) {
            if (in_array($group, $remove)) {
              unset($form['#group_children'][$field]);
              unset($form[$field]);
            }
          }

          unset($form['actions']);
          unset($form['#after_build']);
          unset($form['#validate']);
          unset($form['#submit']);

        // build the new submit buttons
          // cancel button
          $form['actions']['#weight'] = 999;

          $trigger_id = 'edit-tags-cancel';

          $text = t('Cancel review (!hours hrs)', array(
                    '!hours' => feedback_hours_left($post),
                  ));

          $url = implode('/', array(
            'node',
            $post->node_id,
            'feedback',
            'post',
            'cancel',
            $trigger_id,
            $post->id,
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

          $form['actions']['cancel'] = array(
            '#markup' => l($text, $url, $options),
          );

        // submit button
          $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Save and Close'),
            '#ajax' => array(
              'callback' => 'feedback_edit_tags_ajax_save',
              'wrapper' => 'sbac-resource-form',
            ),
            '#attributes' => array(
              'class' => array(
                'action-save',
              ),
            ),
            '#submit' => array(
              'feedback_edit_tags_form_submit',
            ),
          );

        // continue button
          $form['actions']['continue'] = array(
            '#type' => 'submit',
            '#value' => t('Save and Continue'),
            '#ajax' => array(
              'callback' => 'feedback_edit_tags_ajax_continue',
              'wrapper' => 'sbac-resource-form',
            ),
            '#attributes' => array(
              'class' => array(
                'action-continue',
                'secondary',
                'button',
              ),
            ),
            '#validate' => array(
              'feedback_edit_tags_form_validate',
            ),
            '#submit' => array(
              'feedback_edit_tags_form_submit',
            ),
          );
            
          $form['workbench_moderation_state_new'] = array(
            '#type' => 'value',
            '#value' => 'approved',
          );
      }
    }
  }

  /**
   * Extends hook_cron().
   */
  function hook_cron() {
    // send out reminder notifications for resources which are approaching expiry time
    $notification_time = strtotime('-' . FEEDBACK_REVIEW_NOTIFICATION . ' hours'); // - 48 hours

    $query = " SELECT    id, uid, node_id
                  FROM      eck_feedback
                  WHERE     status = 1
                  AND       completed = 0
                  AND       created  <= :time
                  AND       type = 'post'
                  AND       reminder = 0
                ";

    $args = array(
      ':time' => $notification_time,
    );

    $result = db_query($query, $args);

    foreach ($result as $row) {
      $task = taskit_get_object('review_reminder');
      $task->addVisibility($task::VISIBILITY_USER);
      $task->addEntity('node', $row->node_id);
      $task->addEntity('feedback', $row->id);
      $task->addOwningUser($row->uid);
      $task->addTriggeringUser(1);
      $task->save();

      // set the reminder flag for this feedback so that its only sent
      // once at the 24 hour mark.
      $query = 'UPDATE {eck_feedback} SET reminder = 1 WHERE id = :id';
      db_query($query, array(':id' => $row->id));
    }

    // disable feedback entities which have reached the expiry time
    // don't simply subtract seconds from the current timestamp - that'll get messed up
    // during daylight time changes
    $expiry_time = strtotime('-' . FEEDBACK_REVIEW_TIMEOUT . ' hours');

    $args = array(
      ':time' => $expiry_time,
    );

    // get incomplete reviews (gk, qc or post) and set them to inactive to allow for other people
    // to
    $query = "  SELECT    id, node_id
                  FROM      eck_feedback
                  WHERE     status = 1
                  AND       completed = 0
                  AND       created <= :time 
               ";

    $result = db_query($query, $args)->fetchAll();
    foreach ($result as $row) {
      if ($node = node_load($row->node_id)) {
        // if this is an incomplete gate keeper, then the resource won't have any reviews
        // and we can safely bump it back to draft; we don't need to worry about
        // review entities, because to have one of those in the system, the resource must
        // have a completed gate keeper, meaning we don't need to change any node workflow
        // properties
        // We were putting the resource back in draft state. Not wanted by client.
        // workbench_moderation_moderate($node, 'draft');
        $query = "  UPDATE  eck_feedback
                  SET     status = 0
                  WHERE   status = 1
                  AND     completed = 0
                  AND     created <= :time
                  AND     node_id = :nid
               ";

        db_query($query, array(':time' => $expiry_time, ':nid' => $node->nid));
        sbac_resource_save_current_state($node);
      }
    }
  }

  /**
   * Extends hook_node_view_alter().
   */
  function hook_node_view_alter(&$build) {
    // add the review tabs to resource nodes
    if ($build['#node']->type == 'resource' && $build['#view_mode'] == 'full') {
      module_load_include('inc', 'sbac_core', 'components/feedback/feedback.pages');

      $build['review'] = array(
        '#markup' => resource_feedback_page($build['#node']),
      );
    }
  }

  /**
   * Extends hook_js_alter().
   */
  function hook_js_alter(&$javascript) {
    // this JS is throwing errors and is breaking everything; we don't need it
    unset($javascript[drupal_get_path('theme', 'SBAC') . '/js/vendor/jquery.migrate.1.1.1.js']);
  }

  /**
   * Extends hook_theme_registry_alter().
   */
  function hook_theme_registry_alter(&$theme_registry) {
    // We alter the registry and add a new theme callback so we can append a div
    // right before the regular theme element; this div gets the 'error' class
    // whenever the subsequent element contains a validation error. By not 
    // wrapping the original element we don't break any selectors or markup,
    // and can still use CSS siblings selector to target it.
    // 
    // All this headache is required to add the red 'x' (validation fail icon)
    // on form elements, yet outside the element's immediate DOM structure

    $theme_registry['form_element_original'] = $theme_registry['form_element'];

    $theme_registry['form_element']['function'] = 'feedback_theme_form_element';
    $theme_registry['form_element']['file'] = 'feedback.theme.inc';
    $theme_registry['form_element']['theme path'] = $this->_path;
    $theme_registry['form_element']['includes'] = array(
      $this->_path . '/feedback.theme.inc',
    );
  }

  /**
   * Exends hook_field_attach_form().
   */
  function hook_field_attach_form($entity_type, $entity, &$form, &$form_state, $langcode) {
    // required to do proper field validation on Field Collection items;
    // see https://drupal.org/node/1289062#comment-7584113 for more info
    if ($entity_type == 'field_collection_item') {
      $info = entity_get_info($entity_type);
      $bundle_key = $info['entity keys']['bundle'];

      if (in_array($entity->{$bundle_key}, array('field_quality_set', 'field_review_set'))) {
        $form['#required'] = TRUE;
      }
    }
  }

  /**
   * Extends hook_entity_presave();
   */
  function hook_entity_presave($entity, $type) {
    // set active status for new Review entities
    if ($type == 'feedback' && $entity->type == 'qc' && (!isset($entity->id) || !$entity->id)) {
      $entity->status = 1;
    }
  }

  /**
   * Extends hook_entity_insert().
   */
  function hook_entity_insert($entity, $type) {
    // watchdog('sbac', 'feedback: entity_insert');

    if ($type == 'feedback') {
      $this->_check_resource_review_state($entity);
    }
  }

  /**
   * Extends hook_entity_update().
   */
  function hook_entity_update($entity, $type) {
    // watchdog('sbac', 'feedback: entity_update');

    if ($type == 'feedback') {
      $this->_check_resource_review_state($entity);
    }
  }

  /**
   * Extemds hook_entity_view_alter().
   */
  function hook_entity_view_alter(&$build, $type) {

  }

  /**
   * Extends hook_form_BASE_FORM_ID_alter().
   */
  function hook_form_node_form_alter(&$form, $form_state) {
    // this must be a node form and a type that has moderation enabled
    if (!workbench_moderation_node_type_moderated($form['type']['#value'])) {
      return;
    }

    // get current state
    if (isset($form['#node']->workbench_moderation['current']->state)) {
      $moderation_state = $form['#node']->workbench_moderation['current']->state;
    }
    else {
      $moderation_state = variable_get('workbench_moderation_default_state_' . $form['type']['#value'], workbench_moderation_state_none());
    }

    // if the current state is published, then workbench_moderation will have changed
    // the form's default value to Draft, in order to force the creation of a new
    // revision. We don't need/want this workflow, so we change the form's state back
    // to published.

    if ($moderation_state == workbench_moderation_state_published()) {
      $form['options']['workbench_moderation_state_new']['#default_value'] = $moderation_state;

      // workbench replaces the revision checkbox with a hardcoded value, let's put
      // the original back
      $form['revision_information']['revision'] = array(
        '#type' => 'checkbox',
        '#title' => t('Create new revision'),
        '#default_value' => 1,
        '#access' => user_access('administer nodes'),
      );
    }
    elseif (in_array($moderation_state, array('creation', workbench_moderation_state_none()))) {
      _sbac_resource_clean_workbench_moderation($form, $form_state);
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_workbench_moderation_transition().
   */
  function hook_workbench_moderation_transition($node, $previous_state, $new_state) {
    if ($node->type == 'resource' && $new_state == 'needs_review') {
      $query = "  UPDATE    eck_feedback
                  SET       archived = 1,
                            current = 0,
                            status = 0
                  WHERE     node_id = :node_id
               ";

      db_query($query, array(':node_id' => $node->nid));
    }
  }

  /*----------------------------------------------------------------------------
      INTERNAL / HELPERS
  ----------------------------------------------------------------------------*/

  protected function _check_resource_review_state($review) {
    // watchdog('sbac', 'feedback: ' . __FUNCTION__);

    $query = "SELECT state FROM workbench_moderation_node_history WHERE nid = :nid AND current = 1 ORDER BY vid DESC";
    $state = db_query($query, array(
      ':nid' => $review->node_id
    ))->fetchField();

    // watchdog('sbac', 'state: ' . $state);

    if ($state == 'needs_review' && $node = node_load($review->node_id)) {
      workbench_moderation_moderate($node, 'being_reviewed');
      sbac_resource_save_current_state($node);
    }
  }  
}



