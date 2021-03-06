<?php
/**
 * @file
 * Views related code for the SBAC resource feature.
 */

/**
 * Implements hook_views_query_alter().
 *
 * @param $view
 * @param $query
 */
function sbac_resource_views_query_alter(&$view, &$query) {
  if ($view->name == 'resources') {
    _sbac_resource_resources_view_query_alter($view, $query);
  }
  if ($view->name == 'my_resources') {
    sbac_resource_my_resource_apply_filters($view);
    _sbac_resource_my_resources_view_query_alter($view, $query);
  }
  if ($view->name == 'resource_review') {
    _sbac_resource_resource_review_view_query_alter($view, $query);
  }
}

/**
 * Implements hook_view_post_render().
 *
 * @param $view
 * @param $output
 * @param $cache
 */
function sbac_resource_views_post_render(&$view, &$output, &$cache) {
  if ($view->name == 'resources' || $view->name == 'resource_review' || $view->name == 'my_resources') {
    if (isset($_POST['page'])) {
      $_SESSION['load_more'][$view->name]['page'] = $_POST['page'];
    }
  }
}

/**
 * Implements hook_views_default_views_alter().
 *
 * @param $views
 */
function sbac_resource_views_default_views_alter(&$views) {
  if (isset($views['help_topics'])) {
    $welcome_tutorial = taxonomy_get_term_by_name('Welcome Tutorial', 'help_page_topic');
    if ($welcome_tutorial) {
      $welcome_tutorial = array_shift($welcome_tutorial);
      $views['help_topics']->display['default']->display_options['filters']['field_help_page_topic_tid']['value'][$welcome_tutorial->tid] = $welcome_tutorial->tid;
      $views['help_topics']->display['block']->display_options['filters']['field_help_page_topic_tid']['value'][$welcome_tutorial->tid] = $welcome_tutorial->tid;
    }
  }

  if (isset($views['resource_tutorial'])) {
    $resource_tutorial = taxonomy_get_term_by_name('Resource Tutorial', 'help_page_topic');
    if ($resource_tutorial) {
      $resource_tutorial = array_shift($resource_tutorial);
      $views['resource_tutorial']->display['default']->display_options['filters']['field_help_page_topic_tid']['value'][$resource_tutorial->tid] = $resource_tutorial->tid;
      $views['help_topics']->display['page_1']->display_options['filters']['field_help_page_topic_tid']['value'][$resource_tutorial->tid] = $resource_tutorial->tid;
    }
  }

  if (isset($views['workbench_moderation'])) {
    $views['workbench_moderation']->disabled = TRUE;
  }
  if (isset($views['workbench_recent_content'])) {
    $views['workbench_recent_content']->disabled = TRUE;
  }
  if (isset($views['workbench_edited'])) {
    $views['workbench_edited']->disabled = TRUE;
  }
  if (isset($views['workbench_current_user'])) {
    $views['workbench_current_user']->disabled = TRUE;
  }
  if (isset($views['legal_terms'])) {
    $views['legal_terms']->disabled = TRUE;
  }
  if (isset($views['Maillog'])) {
    $views['Maillog']->disabled = TRUE;
  }
  if (isset($views['media_default'])) {
    $views['media_default']->disabled = TRUE;
  }
  if (isset($views['legal_users'])) {
    $views['legal_users']->disabled = TRUE;
  }
}


/**
 * Populates contextual filters with data if provided.
 *
 * @param $view
 *   The view object.
 *
 */
function sbac_resource_my_resource_apply_filters(&$view) {
  $view_filters = $view->display_handler->get_option('filters');

  // Current filter session - create the args where needed.
  if (isset($_SESSION[SBAC_SEARCH_API_MY_RESOURCES_FILTERS]) && $_SESSION[SBAC_SEARCH_API_MY_RESOURCES_FILTERS] !== '') {
    $current_filters = $_SESSION[SBAC_SEARCH_API_MY_RESOURCES_FILTERS];
    $filters = explode('::', $current_filters);
    if ($filters) {
      foreach ($filters as $filter) {
        $filter_info = explode(':', $filter);
        if ($filter_info && sizeof($filter_info) == 2) {
          $vid = $filter_info[0];
          $tid = $filter_info[1];
          if ($vid && $tid) {
            if ($vid === 'resource-status') {
              $view->custom_filters[$vid][] = $tid;
            }
            else {
              $vocabulary = taxonomy_vocabulary_load($vid);
              $term = taxonomy_term_load($tid);
              if ($vocabulary && $term) {
                switch ($vocabulary->machine_name) {
                  case 'focus':
                    $view_filters['field_focus_tid']['value'][] = $tid;
                    $view_filters['field_focus_tid']['operator'] = 'and';
                    break;
                  case 'grades':
                    $view_filters['field_grades_tid']['value'][] = $tid;
                    $view_filters['field_grades_tid']['operator'] = 'and';
                    break;
                  case 'subject':
                    $view_filters['field_subject_tid']['value'][] = $tid;
                    $view_filters['field_subject_tid']['operator'] = 'and';
                    break;
                }
              }
            }
          }
        }
      }
    }
    $view->display_handler->set_option('filters', $view_filters);
  }
}

/**
 * Populates sort options with data if provided.
 *
 * @param $view
 *   The view object.
 *
 */
function sbac_resource_my_resource_apply_sorts(&$view) {
  $view_sorts = $view->display_handler->get_option('sorts');

  if (isset($_SESSION[SBAC_SEARCH_API_MY_RESOURCES_SORTS]) &&
    $_SESSION[SBAC_SEARCH_API_MY_RESOURCES_SORTS] !== ''
  ) {
    $current_sorting = $_SESSION[SBAC_SEARCH_API_MY_RESOURCES_SORTS];
    $sort_field_key = 'created';
    switch ($current_sorting) {
      case 'mr-newest':
        $sort_field_key = 'created';
        break;
      case 'mr-oldest':
        $sort_field_key = 'created_1';
        break;
      case 'mr-alpha':
        $sort_field_key = 'title';
        break;
    }

    $new_sorts = array();
    foreach ($view_sorts as $key => $value) {
      if ($key == $sort_field_key) {
        $new_sorts[$key] = $value;
      }
    }
    if (!empty($new_sorts)) {
      $view->display_handler->set_option('sorts', $new_sorts);
    }
  }
}

/**
 * Populates contextual filters with data if provided.
 *
 * @param $view
 *   The view object.
 *
 */
function sbac_resource_digital_library_apply_filters(&$view) {
  $view_filters = $view->display_handler->get_option('filters');
}

/**
 * Populates sort options with data if provided.
 *
 * @param $view
 *   The view object.
 *
 */
function sbac_resource_digital_library_apply_sorts(&$view) {
  $view_sorts = $view->display_handler->get_option('sorts');
}

/**
 * Changes Digital Library output to display Distinct or mixed when provided.
 * @param  [type] $view The view object.
 */
function sbac_resource_digital_library_apply_pwd(&$view) {
  $view_filters = $view->display_handler->get_option('filters');
  $view_filters['sticky']['value'] = 'All';
  $view->display_handler->set_option('filters', $view_filters);
}

/**
 * Apply the pager and sticky to the view.
 *
 * @param $view
 */
function sbac_resource_digital_library_pwd_reel(&$view) {
  $view_filters = $view->display_handler->get_option('filters');
  $view_filters['sticky']['value'] = '1';
  $view->display_handler->set_option('filters', $view_filters);
  $views_pager = $view->display_handler->get_option('pager');
  $views_pager['type'] = 'some';
  $views_pager['options']['items_per_page'] = 4;
  $view->display_handler->set_option('pager', $views_pager);
}

/**
 * Populates contextual filters with data if provided.
 *
 * @param $view
 *   The view object.
 */
function sbac_resource_resource_review_apply_filters(&$view) {
  if (isset($_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_FILTERS]) && $_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_FILTERS] !== '') {
    $view_filters = $view->display_handler->get_option('filters');
    $current_filters = $_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_FILTERS];
    $filters = explode('::', $current_filters);
    if ($filters) {
      foreach ($filters as $filter) {
        $filter_info = explode(':', $filter);
        if ($filter_info && count($filter_info) === 2) {
          $vid = $filter_info[0];
          $tid = $filter_info[1];
          if ($vid && $tid) {
            $vocabulary = taxonomy_vocabulary_load($vid);
            $term = taxonomy_term_load($tid);
            if ($vocabulary && $term) {
              switch ($vocabulary->machine_name) {
                case 'focus':
                  $view_filters['field_focus_tid']['value'][] = $tid;
                  $view_filters['field_focus_tid']['operator'] = 'and';
                  break;
                case 'grades':
                  $view_filters['field_grades_tid']['value'][] = $tid;
                  $view_filters['field_grades_tid']['operator'] = 'and';
                  break;
                case 'subject':
                  $view_filters['field_subject_tid']['value'][] = $tid;
                  $view_filters['field_subject_tid']['operator'] = 'and';
                  break;
              }
            }
          }
        }
      }
    }
    $view->display_handler->set_option('filters', $view_filters);
  }
  // Not searching/filtering, so we default to the user's profile data for filtering
  else {
    global $user;
    if (array_key_exists(FEEDBACK_REVIEWER_RID, $user->roles)) {
      sbac_resource_filter_user_tags($view, $user);
    }
  }
}

/**
 * Populates sort options with data if provided.
 *
 * @param $view
 *   The view object.
 *
 */
function sbac_resource_resource_review_apply_sorts(&$view) {
  $view_sorts = $view->display_handler->get_option('sorts');

  if (isset($_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_SORTS]) &&
    $_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_SORTS] !== ''
  ) {
    $current_sorting = $_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_SORTS];
    $sort_field_key = 'stamp';
    switch ($current_sorting) {
      case 'rr-oldest':
        $sort_field_key = 'stamp';
        break;
      case 'rr-newest':
        $sort_field_key = 'stamp_1';
        break;
    }

    $new_sorts = array();
    foreach ($view_sorts as $key => $value) {
      if ($key === $sort_field_key) {
        $new_sorts[$key] = $value;
      }
    }
    if (!empty($new_sorts)) {
      $view->display_handler->set_option('sorts', $new_sorts);
    }
  }
}

/**
 * Applies filtering options on View which restrict resources displayed to ones
 * matching the user's Subject & Grade values
 *
 * @param  [type] $view    [description]
 * @param  [type] $account [description]
 * @return [type]          [description]
 */
function sbac_resource_filter_user_tags(&$view, $account = NULL) {
  if (is_null($account)) {
    global $user;
    $account = $user;
  }

  // reload account
  $account = user_load($account->uid);

  $view_filters = $view->display_handler->get_option('filters');

  $get_tid = function ($element) {
    return $element['tid'];
  };

  foreach ($view_filters as &$field) {
    $field['group'] = 1;
  }

  $subject_tid_all = 153;
  $grade_tid_all = 122;

  // subject
  if (!isset($view_filters['field_subject_tid']['value'])) {
    $view_filters['field_subject_tid']['value'] = array();
  }

  $view_filters['field_subject_tid']['operator'] = 'or';
  $view_filters['field_subject_tid']['group'] = 2;

  if ($subjects = field_get_items('user', $account, 'field_subject_s_')) {
    $subjects = array_map($get_tid, $subjects);
    foreach ($subjects as $key => $value) {
      if ($value == NULL) {
        unset($subjects[$key]);
      }
    }

    // not subject specific - remove filters
    if (in_array($subject_tid_all, $subjects)) {
      unset($view_filters['field_subject_tid']);
    }
    else {
      $view_filters['field_subject_tid']['value'][] = $subject_tid_all;
      $view_filters['field_subject_tid']['value'] = array_merge($view_filters['field_subject_tid']['value'], $subjects);
    }
  }

  // grade
  if (!isset($view_filters['field_grades_tid']['value'])) {
    $view_filters['field_grades_tid']['value'] = array();
  }

  $view_filters['field_grades_tid']['operator'] = 'or';
  $view_filters['field_grades_tid']['group'] = 2;

  if ($grades = field_get_items('user', $account, 'field_grade_level_s_')) {
    $grades = array_map($get_tid, $grades);
    foreach ($grades as $key => $value) {
      if ($value == NULL) {
        unset($grades[$key]);
      }
    }

    // not grade specific - remove filters
    if (in_array($grade_tid_all, $grades)) {
      unset($view_filters['field_grades_tid']);
    }
    else {
      $view_filters['field_grades_tid']['value'][] = $grade_tid_all;
      $view_filters['field_grades_tid']['value'] = array_merge($view_filters['field_grades_tid']['value'], $grades);
    }
  }

  $groups = array(
    'operator' => 'AND',
    'groups' => array(
      1 => 'AND',
    ),
  );

  if (isset($view_filters['field_subject_tid']) || isset($view_filters['field_grades_tid'])) {
    $groups['groups'][2] = 'AND';
  }

  $view->display_handler->set_option('filter_groups', $groups);
  $view->display_handler->set_option('filters', $view_filters);
}

/**
 * Implements hook_views_data().
 *
 * @return mixed
 */
function sbac_resource_views_data() {
//  | sbac_node_resource_state |
//  CREATE TABLE `sbac_node_resource_state` (
//  `nid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'The nid of the resource',
//  `uid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'The uid who modified the resource',
//  `state` varchar(255) NOT NULL COMMENT 'The actual resource state',
//  `flag` varchar(1000) NOT NULL DEFAULT '0' COMMENT 'The flag on the resource',
//  PRIMARY KEY (`nid`,`uid`),
//  KEY `nid` (`nid`),
//  KEY `uid` (`uid`)

  $data['sbac_node_resource_state']['table']['group'] = t('SBAC Resource Node State');
  // Base table.
  $data['sbac_node_resource_state']['table']['base'] = array(
    'field' => 'nid', // This is the identifier field for the view.
    'title' => t('SBAC Resource Node Table'),
    'help' => t('Custom data for the resource states.'),
    'weight' => -10,
  );
  // Join.
  $data['sbac_node_resource_state']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );


  // Node ID table field.
  $data['sbac_node_resource_state']['nid'] = array(
    'title' => t('Resource NID'),
    'help' => t('Custom data for the resource states.'),
    'relationship' => array(
      'base' => 'node', // The name of the table to join with.
      'base field' => 'nid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => t('Default label for the relationship'),
      'title' => t('Nid'),
      'help' => t('More information on this relationship'),
    ),
  );

  // User ID field.
  $data['sbac_node_resource_state']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('User ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // State field.
  $data['sbac_node_resource_state']['state'] = array(
    'title' => t('State field.'),
    'help' => t('State field.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Flag field.
  $data['sbac_node_resource_state']['flag'] = array(
    'title' => t('Flag field.'),
    'help' => t('Flag field.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Process the resources view.
 *
 * @param $view
 */
function _sbac_resource_resources_view_query_alter(&$view, &$query) {
  $view->query->add_table('sbac_node_resource_state');
  $view->query->add_field('sbac_node_resource_state', 'uid', 'sbac_node_resource_state_uid');
  $view->query->add_field('sbac_node_resource_state', 'state', 'sbac_node_resource_state_state');
  $view->query->add_field('sbac_node_resource_state', 'flag', 'sbac_node_resource_state_flag');
  $all_condition = db_and()->condition('sbac_node_resource_state.state', "published")->condition('sbac_node_resource_state.uid', 0);
  $view->query->add_where('AND', $all_condition);

  // Users cannot see resources that are flagged with a state restriction
  global $user;
  $has_role = array_intersect($user->roles, array('administrator'));
  if (empty($has_role)) { // Administrator role is exempted from this. They see all.
    $user_profile = user_load($user->uid);
    $user_profile_wrapper = entity_metadata_wrapper('user', $user_profile);
    $users_states = array();
    if (isset($user_profile_wrapper->field_state)) {
      $state_terms = $user_profile_wrapper->field_state->value();
      if (!empty($state_terms)) {
        foreach ($state_terms as $state) {
          $users_states[] = $state->tid;
        }
      }
    }

    // create the join object. STATE
    $join = new views_join;
    $join->table = 'field_data_field_view_permissions_per_state';
    $join->left_table = 'node';
    $join->left_field = 'nid';
    $join->field = 'entity_id';
    $join->extra = array(
      0 => array('field' => 'entity_type', 'value' => 'node'),
      1 => array('field' => 'deleted', 'value' => 0),
    );
    $join->type = "LEFT";
    $join->extra_type = 'AND';
    $join->adjusted = 'TRUE';

    $view->query->table_queue['field_data_field_view_permissions_per_state'] = array(
      'table' => 'field_data_field_view_permissions_per_state',
      'num' => 1,
      'alias' => 'field_data_field_view_permissions_per_state',
      'join' => $join,
      'relationship' => 'node'
    );
    $condition_groups = count($query->where) + 1;
    if (!empty($users_states)) {
      $query->add_where($condition_groups, 'field_data_field_view_permissions_per_state.field_view_permissions_per_state_tid', $users_states, 'IN');
    }
    $query->add_where($condition_groups, 'field_data_field_view_permissions_per_state.field_view_permissions_per_state_tid', array(), 'IS NULL');
    $query->where[$condition_groups]['type'] = "OR";
  }
}

/**
 * Process the my resources view.
 *
 * @param $view
 */
function _sbac_resource_my_resources_view_query_alter(&$view, &$query) {
  global $user;
  $node_condition = db_or()->condition('node.uid', $user->uid);
  $view->query->add_where('AND', $node_condition);
  $view->query->add_groupby('node.nid');

  if (!empty($view->custom_filters)) {
    if (!empty($view->custom_filters['resource-status'])) {
      $join = new views_join();
      $join->construct('eck_feedback', 'node', 'nid', 'node_id', "eck_feedback.created > IFNULL((SELECT max(h2.stamp) FROM workbench_moderation_node_history h2 WHERE h2.nid = node.nid AND h2.from_state = 'draft'  and h2.state = 'needs_review' and h2.stamp > (SELECT max(h3.stamp) FROM workbench_moderation_node_history h3 WHERE h3.nid = node.nid AND h3.state = 'rejected')), 0)");
      $query->add_table('eck_feedback', 'node', $join);

      $having = array();
      foreach ($view->custom_filters['resource-status'] as $filter) {
        switch ($filter) {
          case 'gk':
            $having[] = '(workbench_moderation_node_history.state = \'being_reviewed\' AND max(eck_feedback.completed) = 0)';
            break;
          case 'qc':
            $having[] = '(workbench_moderation_node_history.state = \'being_reviewed\' AND max(eck_feedback.completed) = 1)';
            break;
          case 'draft':
            $having[] = '(workbench_moderation_node_history.state = \'draft\')';
            break;
          case 'posted':
            $having[] = '(workbench_moderation_node_history.state = \'published\')';
            break;
          case 'submitted':
            $having[] = '(workbench_moderation_node_history.state = \'needs_review\')';
            break;
          case 'artbitration':
            $having[] = '(workbench_moderation_node_history.state = \'approved\')';
            break;
          case 'returned':
            $having[] = '(workbench_moderation_node_history.state = \'rejected\')';
            break;
          case 'removed':
            $having[] = '(workbench_moderation_node_history.state = \'removed\')';
            break;
        }
      }
      if (!empty($having)) {
        $query->add_having_expression(count($query->having), implode(' OR ', $having));
      }
    }
  }
}

/**
 * Process the resource review view.
 *
 * @param $view
 */
function _sbac_resource_resource_review_view_query_alter(&$view, &$query) {
  global $user;
  // Remove playlists for non-SLTs
  $is_slt = sbac_report_is_slt($user);

  if (!$is_slt) {
    $alias = $view->query->ensure_table('field_data_field_focus');
    $playlist_condition = db_and();
    $playlist_condition->condition($alias . '.field_focus_tid', '78306', '<>');

    $view->query->add_where('AND', $playlist_condition);
  }

  // don't allow the node author to see / review own nodes.
  $node_condition = db_or()->condition('node.uid', $user->uid, '<>');
  $view->query->add_where('AND', $node_condition);

  // only allow the user to see nodes if they are in the following states.
  // (gk_need_review, gk_being_reviewed, qc_needs_review, qc_being_reviewed, qc_reviewed, gk_view_rejected, post_being_reviewed, post_needs_review)
  $view->query->add_table('sbac_node_resource_state');
  $view->query->add_field('sbac_node_resource_state', 'uid', 'sbac_node_resource_state_uid');
  $view->query->add_field('sbac_node_resource_state', 'state', 'sbac_node_resource_state_state');
  $view->query->add_field('sbac_node_resource_state', 'flag', 'sbac_node_resource_state_flag');
  $view->query->add_table('field_data_field_recent_reviewers');
  $view->query->add_table('field_data_field_recent_publishers');

  $roles = array();
  if (in_array('resource reviewer', $user->roles) && in_array('resource publisher', $user->roles)) {
    // do nothing, roles can be combined to see all states.
    $roles['both'] = TRUE;
  }
  else {
    if (in_array('resource reviewer', $user->roles)) {
      $roles['rr'] = TRUE;
    }

    if (in_array('resource publisher', $user->roles)) {
      $roles['rp'] = TRUE;
    }
  }

  $current_filters = array();
  if ((!isset($view->apply_filter) || $view->apply_filter === TRUE) && isset($_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_FILTERS]) && $_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_FILTERS] != '') {
    $current_filters = explode('::', $_SESSION[SBAC_SEARCH_API_RESOURCE_REVIEW_FILTERS]);
  }

  if ($current_filters) {
    _sbac_resource_resource_review_apply_state_filter($view, $current_filters, $roles);
  }
  if (isset($roles['both']) && $roles['both']) {
    _sbac_resource_resource_review_apply_stock_both_role($view);
  }
  else {
    if (isset($roles['rp']) && $roles['rp']) {
      _sbac_resource_resource_review_apply_stock_rp_role($view);
    }
    if (isset($roles['rr']) && $roles['rr']) {
      _sbac_resource_resource_review_apply_stock_rr_role($view);
    }
  }
  if (isset($view->resubmission_only) && $view->resubmission_only === TRUE) {
    // If this is the resubmission tab, show all of the resubmitted resources (anything that has a completed but not current GK review).
    $query->add_where_expression(count($query->where), "(SELECT COUNT(*) FROM `eck_feedback` f WHERE `type` = 'gate_keeper' AND `completed` = 1 AND `current` = 0 AND `node_id` = node.nid) > 0");
  } else {
    // If this is the main tab, show non-resubmissions, unless they are resources that the current user is currently reviewing.
    $query->add_where_expression(count($query->where), "
      (
        (SELECT COUNT(*) FROM `eck_feedback` WHERE `type` = 'gate_keeper' AND `completed` = 1 AND `current` = 0 AND `node_id` = node.nid) = 0 OR
        (
          (SELECT COUNT(*) FROM `eck_feedback` WHERE `type` = 'gate_keeper' AND `completed` = 1 AND `current` = 0 AND `node_id` = node.nid) > 0 AND
          (SELECT COUNT(*) FROM `eck_feedback` WHERE `current` = 1 AND `completed` = 0 AND `uid` = " . $user->uid . " AND `node_id` = node.nid) > 0
        )
      )
      ");
  }

  // Create a sub query to get a count of the number of reviews that have been completed for the item.
  $count_sub_query = db_select('eck_feedback', 'eck_feedback_reviews');
  $count_sub_query->addField('eck_feedback_reviews', 'node_id');
  $count_sub_query->addExpression('COUNT(*)', 'reviews');
  $count_sub_query->condition('current', 1, '=');
  $count_sub_query->condition('status', 1, '=');
  $count_sub_query->condition('completed', 1, '=');
  $count_sub_query->groupBy('node_id');

  // Create a sub query to get determine if this item is currently being reviewed.
  $in_process_sub_query = db_select('eck_feedback', 'eck_feedback_reviewing');
  $in_process_sub_query->addField('eck_feedback_reviewing', 'node_id');
  $in_process_sub_query->addExpression('TRUE', 'reviewing');
  $in_process_sub_query->condition('status', 1, '=');
  $in_process_sub_query->condition('completed', 0, '=');

  // Create the join between the sub query with the count of reviews and the main query.
  $count_join = new views_join();
  $count_join->definition = array('table formula' => $count_sub_query, 'left_field' => 'nid', 'field' => 'node_id', 'left_table' => 'node');
  $count_join->field = 'node_id';
  $count_join->left_table = 'node';
  $count_join->left_field = 'nid';
  $count_join->type = 'LEFT';

  // Create the join between the sub query with the review state and the main query.
  $in_process_join = new views_join();
  $in_process_join->definition = array('table formula' => $in_process_sub_query, 'left_field' => 'nid', 'field' => 'node_id', 'left_table' => 'node');
  $in_process_join->field = 'node_id';
  $in_process_join->left_table = 'node';
  $in_process_join->left_field = 'nid';
  $in_process_join->type = 'LEFT';

  // Add the review count join.
  $view->query->table_queue['eck_feedback_reviews'] = array(
    'alias' => 'count_join',
    'table' => $count_sub_query,
    'join' => $count_join,
    'relationship' => 'node'
  );

  // Add the review state join
  $view->query->table_queue['eck_feedback_reviewing'] = array(
    'alias' => 'in_process_join',
    'table' => $in_process_sub_query,
    'join' => $in_process_join,
    'relationship' => 'node'
  );

  // Add the review count and review state to the view row.
  $view->query->add_field('count_join', 'reviews', 'eck_feedback_reviews');
  $view->query->add_field('in_process_join', 'reviewing', 'eck_feedback_reviewing');

  // Order the items by the review state (items being reviewed at top) and then by number of reviews (most at top).
  $view->query->add_orderby('in_process_join', 'reviewing', 'DESC');
  $view->query->add_orderby('count_join', 'reviews', 'DESC');
  $view->query->add_orderby('node', 'nid');
}

/**
 * Apply the resource state filter to view.
 *
 * @param $view
 * @param $current_filters
 * @param $roles
 */
function _sbac_resource_resource_review_apply_state_filter(&$view, $current_filters, $roles) {
  // apply filters
  $values = array();
  foreach ($current_filters as $filter) {
    $filter_info = explode(':', $filter);
    if ($filter_info && sizeof($filter_info) == 2) {
      $vid = $filter_info[0];
      $tid = $filter_info[1];
      if ($vid && $tid) {
        $vocabulary = taxonomy_vocabulary_load($vid);
        $term = taxonomy_term_load($tid);
        if ($vocabulary && $term) {
          if ('resource_states' == $vocabulary->machine_name) {
            if (isset($roles['rp'])) {
              switch ($term->name) {
                case 'Needs Arbitration':
                  if (!in_array('post_needs_review', $values)) {
                    $values[] = 'post_needs_review';
                    $all_states = array('post_needs_review');
                    $all_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $all_states, 'IN');
                    $view->query->add_where('AND', $all_condition);
                  }
                  break;
                case 'Being Reviewed':
                  if (!in_array('post_being_reviewed', $values)) {
                    $values[] = 'post_being_reviewed';
                    $user_states = array('post_being_reviewed');
                    $user_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $user_states, 'IN');
                    $view->query->add_where('AND', $user_condition);
                  }
                  break;
              }
            }

            if (isset($roles['rr'])) {
              switch ($term->name) {
                case 'Needs Review':
                  if (!in_array('gk_needs_review', $values)) {
                    $values[] = 'gk_needs_review';
                    $values[] = 'qc_needs_review';
                    $all_states = array('gk_needs_review', 'qc_needs_review');
                    $all_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $all_states, 'IN');
                    $view->query->add_where('AND', $all_condition);
                  }
                  break;
                case 'Being Reviewed':
                  if (!in_array('gk_being_reviewed', $values)) {
                    $values[] = 'gk_being_reviewed';
                    $values[] = 'qc_being_reviewed';
                    $user_states = array('gk_being_reviewed', 'qc_being_reviewed');
                    $user_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $user_states, 'IN');
                    $view->query->add_where('AND', $user_condition);
                  }
                  break;
              }
            }

            if (isset($roles['both'])) {
              switch ($term->name) {
                case 'Needs Review':
                  if (!in_array('gk_needs_review', $values)) {
                    $values[] = 'gk_needs_review';
                    $all_states = array('gk_needs_review', 'qc_needs_review');
                    $all_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $all_states, 'IN');
                    $view->query->add_where('AND', $all_condition);
                  }
                  break;
                case 'Being Reviewed':
                  if (!in_array('post_being_reviewed', $values)) {
                    $values[] = 'post_being_reviewed';
                    $user_states = array('gk_being_reviewed', 'qc_being_reviewed', 'post_being_reviewed');
                    $user_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $user_states, 'IN');
                    $view->query->add_where('AND', $user_condition);
                  }
                  break;
                case 'Needs Arbitration':
                  if (!in_array('post_needs_review', $values)) {
                    $values[] = 'post_needs_review';
                    $all_states = array('post_needs_review');
                    $all_condition = db_and()
                      ->condition('sbac_node_resource_state.state', $all_states, 'IN');
                    $view->query->add_where('AND', $all_condition);
                  }
                  break;
              }
            }
          }
        }
      }
    }
  }
}

/**
 * Apply stock filtering to resource review, rp role.
 *
 * @param $view
 */
function _sbac_resource_resource_review_apply_stock_rp_role(&$view) {
  $all_states = array('post_needs_review');
  $user_states = array('post_being_reviewed', 'post_view_rejected');

  $all_condition = db_and()
    ->condition('sbac_node_resource_state.state', $all_states, 'IN');

  $user_condition = db_and()
    ->condition('sbac_node_resource_state.state', $user_states, 'IN');

  $view->query->add_where('AND', db_or()->condition($all_condition)->condition($user_condition));
}

/**
 * Apply stock filtering to resource review, rr role.
 *
 * @param $view
 */
function _sbac_resource_resource_review_apply_stock_rr_role(&$view) {
  $all_states = array('gk_needs_review', 'qc_needs_review');
  $user_states = array('gk_being_reviewed', 'qc_being_reviewed', 'gk_view_rejected');

  $all_condition = db_and()
    ->condition('sbac_node_resource_state.state', $all_states, 'IN');

  $user_condition = db_and()
    ->condition('sbac_node_resource_state.state', $user_states, 'IN');
  $view->query->add_where('AND', db_or()->condition($all_condition)->condition($user_condition));
}

/**
 * Apply stock filtering to resource review, both roles.
 *
 * @param $view
 */
function _sbac_resource_resource_review_apply_stock_both_role(&$view) {
  $all_states = array('gk_needs_review', 'qc_needs_review', 'post_needs_review');

  $all_condition = db_and()
    ->condition('sbac_node_resource_state.state', $all_states, 'IN')
    ->condition('sbac_node_resource_state.uid', 0);

  $user_states = array('gk_being_reviewed', 'qc_being_reviewed', 'gk_view_rejected', 'post_being_reviewed', 'post_view_rejected');
  $user_condition = db_and()
    ->condition('sbac_node_resource_state.state', $user_states, 'IN');

  $view->query->add_where('AND', db_or()->condition($all_condition)->condition($user_condition));
}
