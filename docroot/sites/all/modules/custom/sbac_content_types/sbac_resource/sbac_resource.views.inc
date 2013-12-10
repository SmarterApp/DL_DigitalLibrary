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
  if ($view->name == 'resource_review') {
    global $user;

    if (in_array('resource reviewer', $user->roles) && in_array('resource publisher', $user->roles)) {
      // do nothing, roles can be combined to see all states.
      $roles['both'] = TRUE;
    }
    else {
      if (in_array('resource reviewer', $user->roles)) {
        // Can see needs review, being reviewed
        unset($query->where[1]['conditions'][3]['value'][2]);
        $roles['rr'] = TRUE;
      }

      if (in_array('resource publisher', $user->roles)) {
        // Can see approved
        unset($query->where[1]['conditions'][3]['value'][0]);
        unset($query->where[1]['conditions'][3]['value'][1]);
        $roles['rp'] = TRUE;
      }
    }

    /**
     * Since the values displayed to the user are not the values displayed in the database (information is dependant on who is viewing it),
     * we must manipulate the provided values so that the correct database values are searched.
     */
    if (isset($_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS]) && $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS] != '') {
      $current_filters = $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS];
      $filters = explode('::', $current_filters);
      if ($filters) {
        $values = array();
        $view->query->add_table('sbac_node_resource_state');
        $view->query->table_queue['sbac_node_resource_state']['join']->extra[0] = array('field' => 'uid', 'value' => $user->uid);
        foreach ($filters as $filter) {
          $filter_info = explode(':', $filter);
          if ($filter_info && sizeof($filter_info) == 2) {
            $vid = $filter_info[0];
            $tid = $filter_info[1];
            if ($vid && $tid) {
              $vocabulary = taxonomy_vocabulary_load($vid);
              $term = taxonomy_term_load($tid);
              if ($vocabulary && $term) {
                if ($vocabulary->machine_name = 'resource_states') {

                  if (isset($roles['rp'])) {
                    switch ($term->name) {
                      case 'Needs Posting':
                        $values[] = 'post_needs_review';
                        break;
                      case 'Being Reviewed':
                        $values[] = 'post_being_reviewed';
                        break;
                    }
                  }

                  if (isset($roles['rr'])) {
                    switch ($term->name) {
                      case 'Needs Review':
                        $values[] = 'gk_needs_review';
                        $values[] = 'qc_needs_review';
                        $values[] = 'needs_review';
                        break;
                      case 'Being Reviewed':
                        $values[] = 'gk_being_reviewed';
                        $values[] = 'qc_being_reviewed';
                        break;
                    }
                  }

                  if (isset($roles['both'])) {
                    switch ($term->name) {
                      case 'Needs Review':
                        $values[] = 'gk_needs_review';
                        $values[] = 'qc_needs_review';
                        $values[] = 'needs_review';
                        break;
                      case 'Being Reviewed':
                        $values[] = 'post_being_reviewed';
                        $values[] = 'gk_being_reviewed';
                        $values[] = 'qc_being_reviewed';
                        break;
                      case 'Needs Posting':
                        $values[] = 'post_needs_review';
                        break;
                    }
                  }

                }
              }
            }
          }
        }

        if ($values) {
          $condition = db_or()->condition('sbac_node_resource_state.state', $values, 'IN');
          $view->query->add_where('AND', $condition);
        }
      }
    }
  }
}

/**
 * Implements hook_views_post_execute();
 *
 * This hook is implement to combine two view results into one.
 * When the user searches via keyword, the results are retrieved
 * from the apache solr view. Those are then jammed into the results
 * of the resource view and displayed. I chose to do this in order
 * to make the resource view react on local DB data instead of
 * getting the data from apache solr.
 *
 * @param $view
 */
function sbac_resource_views_post_execute(&$view) {
  if ($view->name == 'resources' && ($view->current_display == 'grid_view' || $view->current_display == 'list_view')) {
    if (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS]) && $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS] != '') {
      // Search apache solr for keyword.
      $sr_view = views_get_view('search_resource_keywords', TRUE);
      $sr_view->set_display('search');
      $view_filters = $sr_view->display_handler->get_option('filters');
      $view_filters['keyword']['value'] = apachesolr_clean_text($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS]);
      $view_filters['keyword']['operator'] = 'LIKE';
      $sr_view->display_handler->set_option('filters', $view_filters);
      $sr_view->pre_execute();
      $sr_view->execute();
      $sr_results = $sr_view->result;
      $sr_view->destroy();

      // Collect nids.
      if ($sr_results) {
        foreach ($sr_results as $sr_result) {
          $nids[] = $sr_result->entity_id;
        }
        // Load up all the local data needed for display since all i have is a nid. used views again.
        $data_results = views_get_view_result('resources', 'load_data', implode('+', $nids));
        if ($data_results) {
          if (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS]) && $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] != '') {
            // Category filters are set, append the keyword view results into the resource view.
            $combined_results = array();
            foreach ($view->result as $result) {
              foreach ($data_results as $key => $data_result) {
                  if ($result->nid == $data_result->nid) {
                    $combined_results[] = $data_result;
                  }
              }
            }

            $view->result = $combined_results;
            $view->total_rows = count($view->result);
          }
          else {
            // Category filters are not set, remove results and only use the keyword view results.
            $view->result = array();
            $view->result = $data_results;
            $view->total_rows = count($data_results);
          }
        }
      }
      else {
        if (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS]) && $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] != '') {
          // if there are filters, return whatever the view found.
        }
        else {
          // if no filters, just a keyword, return 0 results.
          $view->result = array();
        }
      }
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
  $available_states = array('draft', 'needs_review', 'being_reviewed', 'rejected', 'published', 'removed');
  $resource_states = array();

  // Current filter session - create the args where needed.
  if (isset($_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS]) && $_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS] != '') {
    $current_filters = $_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS];
    $filters = explode('::', $current_filters);
    if ($filters) {
      foreach ($filters as $filter) {
        $filter_info = explode(':', $filter);
        if ($filter_info && sizeof($filter_info) == 2) {
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
                case 'resource_states':
                  switch($term->name) {
                    case 'Draft':
                      $state = 'draft';
                      break;
                    case 'In Review':
                      $state = 'being_reviewed';
                      break;
                    case 'Posted':
                      $state = 'published';
                      break;
                    case 'Returned':
                      $state = 'rejected';
                      break;
                    case 'Submitted':
                      $state = 'needs_review';
                      break;
                    case 'Removed':
                      $state = 'removed';
                      break;
                    default:
                      $state = 'draft';
                      break;
                  }

                  $resource_states[$state] = $state;
                  break;
              }
            }
          }
        }
      }
    }

    if (!$resource_states) {
      foreach ($available_states AS $state) {
        $view_filters['state']['value'][$state] = $state;
        $view_filters['state']['operator'] = 'in';
      }
    }
    else {
      $view_filters['state']['value'] = array();
      foreach ($resource_states AS $state) {
        $view_filters['state']['value'][$state] = $state;
        $view_filters['state']['operator'] = 'in';
      }
    }
    $view->display_handler->set_option('filters', $view_filters);
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

  // Current filter session - create the args where needed.
  if (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS]) && $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] != '') {
    $current_filters = $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS];
    $filters = explode('::', $current_filters);
    if ($filters) {
      foreach ($filters as $filter) {
        $filter_info = explode(':', $filter);
        if ($filter_info && sizeof($filter_info) == 2) {
          $vid = $filter_info[0];
          $tid = $filter_info[1];
          if ($vid && $tid) {
            $vocabulary = taxonomy_vocabulary_load($vid);
            $term = taxonomy_term_load($tid);
            if ($vocabulary && $term) {
              switch ($vocabulary->machine_name) {
                case 'attributes':
                  $view_filters['field_attributes_tid']['value'][] = $tid;
                  $view_filters['field_attributes_tid']['operator'] = 'and';
                  break;
                case 'focus':
                  $view_filters['field_focus_tid']['value'][] = $tid;
                  $view_filters['field_focus_tid']['operator'] = 'and';
                  break;
                case 'grades':
                  $view_filters['field_grades_tid']['value'][] = $tid;
                  $view_filters['field_grades_tid']['operator'] = 'and';
                  break;
                case 'intended_student_populations':
                  $view_filters['field_intended_student_tid']['value'][] = $tid;
                  $view_filters['field_intended_student_tid']['operator'] = 'and';
                  break;
                case 'digital_media_type':
                  $view_filters['field_digital_media_type_tid']['value'][] = $tid;
                  $view_filters['field_digital_media_type_tid']['operator'] = 'and';
                  break;
                case 'subject':
                  $view_filters['field_subject_tid']['value'][] = $tid;
                  $view_filters['field_subject_tid']['operator'] = 'and';
                  break;
                case 'geographical_settings':
                  $view_filters['field_geographical_settings_tid']['value'][] = $tid;
                  $view_filters['field_geographical_settings_tid']['operator'] = 'and';
                  break;
                case 'educational_use':
                  $view_filters['field_educational_use_tid']['value'][] = $tid;
                  $view_filters['field_educational_use_tid']['operator'] = 'and';
                  break;
                case 'intended_end_user':
                  $view_filters['field_intended_end_user_tid']['value'][] = $tid;
                  $view_filters['field_intended_end_user_tid']['operator'] = 'and';
                  break;
                case 'smarter_balanced_keyword':
                  $view_filters['field_smarter_balanced_keyword_tid']['value'][] = $tid;
                  $view_filters['field_smarter_balanced_keyword_tid']['operator'] = 'and';
                  break;
                case 'technologies_for_classroom_use':
                  $view_filters['field_classroom_technologies_tid']['value'][] = $tid;
                  $view_filters['field_classroom_technologies_tid']['operator'] = 'and';
                  break;
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
 * Populates contextual filters with data if provided.
 *
 * @param $view
 *   The view object.
 */
function sbac_resource_resource_review_apply_filters(&$view) {
  if (isset($_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS]) && $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS] != '') {
    $view_filters = $view->display_handler->get_option('filters');
    $current_filters = $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS];
    $filters = explode('::', $current_filters);
    if ($filters) {
      foreach ($filters as $filter) {
        $filter_info = explode(':', $filter);
        if ($filter_info && sizeof($filter_info) == 2) {
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

    if (in_array(FEEDBACK_REVIEWER_RID, array_keys($user->roles))) {
      sbac_resource_filter_user_tags($view, $user);
    }
  }
}

function sbac_resource_views_data() {
//  | sbac_node_resource_state |
//  CREATE TABLE `sbac_node_resource_state` (
//  `nid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'The nid of the resource',
//  `uid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'The uid who modified the resource',
//  `state` varchar(255) NOT NULL COMMENT 'The actual resource state',
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
      'title' => t('Title shown when adding the relationship'),
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

  return $data;
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

  $get_tid = function($element) {
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