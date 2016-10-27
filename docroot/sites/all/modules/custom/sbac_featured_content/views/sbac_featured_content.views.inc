<?php
/**
 * All of this is in progress, nothing is complete
 */

/**
 * Implements hook_views_data().
 * 
 * Use the flagging table as the base table to allow for collecting all flagged
 * content regardless of entity type.
 * 
 */
function sbac_featured_content_views_data() {

  $data['flagging']['table']['base'] = array(
    'field' => 'entity_id',
    'title' => t('Flagged Content'),
    'help' => t("Entity types flagged as featured content"),
    'weight' => -9,
  );
  
  
  $data['flagging']['fid'] = array(
    'title' => t('Flagging Flag ID'),
    'help' => t('Flag ID the flag is coming from'),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
  );
  $data['flagging']['entity_id'] = array(
    'title' => t('Entity ID'),
    'help' => t('Entity ID'),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  $data['flagging']['entity_type'] = array(
    'title' => t('Entity Type'),
    'help' => t('Entity Type'),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
//dpm($data);
  return $data;
}

function sbac_featured_content_views_default_views() {
  
  $flag_node = flag_get_flag('featured_node');

  $view = new view();
  $view->name = 'sbac_featured_content';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'flagging';
  $view->human_name = 'Flagged Featured Content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Featured Content';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'flexslider';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Flags: Entity Type */
  $handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['table'] = 'flagging';
  $handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
  /* Field: Flags: Array */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'flagging';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['label'] = 'Entity ID Entity ID';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'testing:page_1';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
  /* Filter criterion: Flags: Flagging Flag ID */
  $handler->display->display_options['filters']['fid']['id'] = 'fid';
  $handler->display->display_options['filters']['fid']['table'] = 'flagging';
  $handler->display->display_options['filters']['fid']['field'] = 'fid';
  $handler->display->display_options['filters']['fid']['value']['value'] = $flag_node->fid;

  /* Display: Draggable Flags */
  $handler = $view->new_display('page', 'Draggable Flags', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'entity_type' => 'entity_type',
    'entity_id' => 'entity_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'entity_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Flags: Array */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'flagging';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['label'] = 'Title';
  /* Field: Draggableviews: Flags */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'flagging';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['label'] = '';
  $handler->display->display_options['fields']['draggableviews']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 1;
  /* Field: Flags: Array */
  $handler->display->display_options['fields']['entity_id_1']['id'] = 'entity_id_1';
  $handler->display->display_options['fields']['entity_id_1']['table'] = 'flagging';
  $handler->display->display_options['fields']['entity_id_1']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id_1']['label'] = 'Status';
  /* Field: Flags: Array */
  $handler->display->display_options['fields']['entity_id_2']['id'] = 'entity_id_2';
  $handler->display->display_options['fields']['entity_id_2']['table'] = 'flagging';
  $handler->display->display_options['fields']['entity_id_2']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id_2']['label'] = 'Action';
  $handler->display->display_options['fields']['entity_id_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'sort-content/featured';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Featured Content';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Featured Content';
  $handler->display->display_options['tab_options']['weight'] = '0';
  // (Export ends here.)

  // Add view to list of views to provide.
  $views [$view->name] = $view;

  // Return array of default views.
  return $views;
  
}


function sbac_featured_content_views_pre_render(&$view) {
  if ($view->name=='sbac_featured_content') {
    foreach($view->result as $r => $result) {
      $entity_type = $result->flagging_entity_type;
      $entity_id = $result->entity_id;
      $entity = sbac_featured_content_flagged($entity_type,$entity_id);
      if($entity){
         $result->entity = $entity;
      }
    }
  }
  return $view;
}

class sbac_flag_handler_relationship_flags extends flag_handler_relationship {

  function option_definition() {
    $options = parent::option_definition();
    $options['user_scope'] = array('default' => 'current');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $entity_type = $this->definition['flag type'];
    $form['label']['#description'] .= ' ' . t('The name of the selected flag makes a good label.');
    $form['flag'] = flag_views_flag_config_form('checkboxes', $entity_type, $this->options['flag']);
    $form['user_scope'] = array(
      '#type' => 'radios', 
      '#title' => t('By'), 
      '#options' => array(
        'current' => t('Current user'),
        'any' => t('Any user'),
      ), 
      '#default_value' => $this->options['user_scope'],
    );

    $form['required']['#title'] = t('Include only flagged content');
    $form['required']['#description'] = t('If checked, only content that has this flag will be included. Leave unchecked to include all content; or, in combination with the <em>Flagged</em> filter, <a href="@unflagged-url">to limit the results to specifically unflagged content</a>.', array('@unflagged-url' => 'http://drupal.org/node/299335'));

    if (!$form['flag']['#options']) {
      $form = array(
        'error' => array(
          '#markup' => '<p class="error form-item">' . t('No %type flags exist. You must first <a href="@create-url">create a %type flag</a> before being able to use this relationship type.', array('%type' => $entity_type, '@create-url' => url(FLAG_ADMIN_PATH))) . '</p>',
        ),
      );
      $form_state['no flags exist'] = TRUE;
    }
    if (module_exists('session_api')) {
      $form['session_warning'] = array(
        '#markup' => '<p class="warning form-item">' . t('<strong>Warning</strong>: Adding this relationship for any flag that contains <strong>anonymous flagging access</strong> will disable page caching for anonymous users when this view is executed. (But this is only true when the relationship is constrained to "Current user", not to "Any user".) It is recommended to create a dedicated page for views containing anonymous user data.') . '</p>',
      );
    }
  }
  function options_validate(&$form, &$form_state) {
    if (!empty($form_state['no flags exist'])) {
      form_error($form, t('You must first create a flag'));
    }
  }

  function admin_summary() {
    return $this->options['user_scope'] == 'current' ? t('by current user') : t('by any user');
  }

  function ui_name($short = FALSE) {
    $flags = '';
    // We put the bookmark name in the UI string to save space.
    foreach($this->options['flag'] as $fl){
      if($fl !== 0){
        $flags .= $fl . ' ';
      }
    }
    return t('!group: !title', array('!group' => $this->definition['group'], '!title' => empty($this->options['flag']) ? t('(Please select a flag)') : $flags));
  }

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    if (!($flag = $this->get_flag())) {
      return;
    }
    $this->definition['extra'][] = array(
      'field' => 'fid', 
      'value' => 1, 
      'numeric' => TRUE,
    );
    if ($this->options['user_scope'] == 'current' && !$flag->global) {
      $this->definition['extra'][] = array(
        'field' => 'uid', 
        'value' => '***CURRENT_USER***', 
        'numeric' => TRUE,
      );
      $flag_roles = user_roles(FALSE, "flag $flag->name");
      if (isset($flag_roles[DRUPAL_ANONYMOUS_RID])) {
        // Disable page caching for anonymous users.
        drupal_page_is_cacheable(FALSE);

        // Add in the SID from Session API for anonymous users.
        $this->definition['extra'][] = array(
          'field' => 'sid', 
          'value' => '***FLAG_CURRENT_USER_SID***', 
          'numeric' => TRUE,
        );
      }
    }
    parent::query();
  }
}
