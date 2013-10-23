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
  if ($view->name == 'resource_review' || $view->name == 'all_resource_review') {
    global $user;

    if (in_array('resource reviewer', $user->roles) && in_array('resource publisher', $user->roles)) {
      // do nothing, roles can be combined to see all states.
    }
    else {
      if (in_array('resource reviewer', $user->roles)) {
        // Can see needs review, being reviewed
        unset($query->where[1]['conditions'][3]['value'][2]);
      }

      if (in_array('resource publisher', $user->roles)) {
        // Can see approved
        unset($query->where[1]['conditions'][3]['value'][0]);
        unset($query->where[1]['conditions'][3]['value'][1]);
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
      if (isset($_ENV['AH_SITE_ENVIRONMENT'])) {
        switch ($_ENV['AH_SITE_ENVIRONMENT']) {
          case 'dev':
            $sr_view = views_get_view('search_resources_dev', TRUE);
            break;

          case 'test':
            $sr_view = views_get_view('search_resources_test', TRUE);
            break;

          case 'prod':
            $sr_view = views_get_view('search_resources_prod', TRUE);
            break;
        }
      }
      else {
        $sr_view = views_get_view('search_resources', TRUE);
      }

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
 * Implements hook_views_pre_render().
 *
 * @param $view
 */
function sbac_resource_views_pre_render(&$view) {
  if ($view->name == 'resource_review') {
    $filter_terms = array();
    // Check for the resource_state filter option.
//    if (isset($_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS]) && $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS] != '') {
//      $current_filters = $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS];
//      $filters = explode('::', $current_filters);
//      if ($filters) {
//        foreach ($filters as $filter) {
//          $filter_info = explode(':', $filter);
//          if ($filter_info && sizeof($filter_info) == 2) {
//            $vid = $filter_info[0];
//            $tid = $filter_info[1];
//            if ($vid && $tid) {
//              $vocabulary = taxonomy_vocabulary_load($vid);
//              $term = taxonomy_term_load($tid);
//              if ($vocabulary && $term) {
//                if ($vocabulary->machine_name == 'resource_states') {
//                  $filter_terms[] = $term->name;
//                }
//              }
//            }
//          }
//        }
//      }
//    }

    // Determine the user who is loading the view.
//    global $user;
//    $roles = array();
//    if (in_array('resource reviewer', $user->roles) && in_array('resource publisher', $user->roles)) {
//      $roles['both_roles'] = TRUE;
//    }
//    else {
//      if (in_array('resource reviewer', $user->roles)) {
//        $roles['rr'] = TRUE;
//      }
//      if (in_array('resource publisher', $user->roles)) {
//        $roles['rp'] = TRUE;
//      }
//    }

    // if the user is a resource reviewer.
//    if (isset($roles['rr']) && $roles['rr']) {
//      foreach ($view->result as $key => $result) {
//        if (isset($result->workbench_moderation_node_history_state) && $result->workbench_moderation_node_history_state == 'being_reviewed') {
//          // Do not show nodes to resource reviewer when the node is in the process of the gate keeper review.
//          $gate_keeper = _sbac_resource_determine_feedback($result->nid, 'gate_keeper', $user->uid, 1, 0, 1, 'set', TRUE);
//          if ($gate_keeper) {
//            unset($view->result[$key]);
//          }
//          // Do not show nodes to resource reviewers when the node is being reviewed by 3 people.
//          $feedback = _sbac_resource_determine_feedback($result->nid, 'qc', $user->uid, 1, FALSE, 1, 'set', TRUE);
//          if (count($feedback) == 3) {
//            unset($view->result[$key]);
//          }
//          // Do not show nodes to the resource reviewers when the node has been reviewed by this person and is complete.
//          $feedback = _sbac_resource_determine_feedback($result->nid, 'qc', $user->uid, 1, 1, FALSE, 'single');
//          if ($feedback) {
//            unset($view->result[$key]);
//          }
//        }
//      }
//    }

    // If the user if a resource publisher.
//    if (isset($roles['rp']) && $roles['rp']) {
//      foreach ($view->result as $key => $result) {
//        if (isset($result->workbench_moderation_node_history_state) && $result->workbench_moderation_node_history_state == 'approved') {
//          // Do not show nodes to the resource publishers when the node has been reviewed by another resource publisher
//          $feedback = _sbac_resource_determine_feedback($result->nid, 'post', $user->uid, 1, 0, 1, 'set', TRUE);
//          if ($feedback) {
//            unset($view->result[$key]);
//          }
//        }
//      }
//    }

    if ($filter_terms) {
      sbac_resource_determine_view_output($view, $filter_terms, $roles);
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
 *
 */
function sbac_resource_resource_review_apply_filters(&$view) {
  $view_filters = $view->display_handler->get_option('filters');

  global $user;
  $both_roles = $rr = $rp = FALSE;
  if (in_array('resource reviewer', $user->roles) && in_array('resource publisher', $user->roles)) {
    $both_roles = TRUE;
  }
  else {
    if (in_array('resource reviewer', $user->roles)) {
      $rr = TRUE;
    }
    if (in_array('resource publisher', $user->roles)) {
      $rp = TRUE;
    }
  }

  $allowed_both_states = array('being_reviewed' => 'Being Reviewed', 'needs_review' => 'Needs Review', 'approved' => 'Needs Posting');
  $allowed_rr_states = array('being_reviewed' => 'Being Reviewed', 'needs_review' => 'Needs Review');
  $allowed_rp_states = array('approved' => 'Being Reviewed', 'approved' => 'Needs Posting');

  if (isset($_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS]) && $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS] != '') {
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

    // Bring back all states for the given user roles regardless of what they selected.
    // This is because the database state does not mean what the ouputted label for that state does.
    if ($both_roles) {
      foreach ($allowed_both_states AS $state => $label) {
        $view_filters['state']['value'][$state] = $state;
        $view_filters['state']['operator'] = 'in';
      }
    }
    else if ($rr) {
      foreach ($allowed_rr_states AS $state => $label) {
        $view_filters['state']['value'][$state] = $state;
        $view_filters['state']['operator'] = 'in';
      }
    }
    else if ($rp) {
      foreach ($allowed_rp_states AS $state => $label) {
        $view_filters['state']['value'][$state] = $state;
        $view_filters['state']['operator'] = 'in';
      }
    }
    $view->display_handler->set_option('filters', $view_filters);
  }
  // Not searching/filtering, so we default to the user's profile data for filtering
  else {
    global $user;

    if (in_array(FEEDBACK_REVIEWER_RID, array_keys($user->roles))) {
      $account = user_load($user->uid);

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
          array_merge($view_filters['field_subject_tid']['value'], $subjects);
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
        $groups['groups'][2] = 'OR';
      }

      $view->display_handler->set_option('filter_groups', $groups);
      $view->display_handler->set_option('filters', $view_filters);
    }
  }
}

/**
 * Determines the view output when filters are selected.
 *
 * @param $view
 * @param $filter_terms
 * @param $roles
 */
function sbac_resource_determine_view_output(&$view, $filter_terms, $roles) {
  if ($filter_terms) {
    global $user;
    foreach ($view->result as $key => $result) {
      // To remove rows that should not be displayed because of the filter option.
      if (isset($result->workbench_moderation_node_history_state)) {
        switch ($result->workbench_moderation_node_history_state) {
          case 'being_reviewed':
            if ($completed = _sbac_resource_determine_feedback($result->nid, 'gate_keeper', FALSE, 1, 1, 1, 'single')) {
              // check for an active Review by the current user to continue review
              if ($active = _sbac_resource_determine_feedback($result->nid, 'qc', $user->uid, 1, 0, 1, 'single')) {
                $view->result[$key]->state_label = 'Being Reviewed';
              }
              else {
                $view->result[$key]->state_label = 'Needs Review';
              }
            }
            else {
              // check for an active GK by the current user to continue review
              if ($active = _sbac_resource_determine_feedback($result->nid, 'gate_keeper', $user->uid, 1, 0, 1, 'single')) {
                $view->result[$key]->state_label = 'Being Reviewed';
              }
              else {
                $view->result[$key]->state_label = 'Needs Review';
              }
            }
            break;
          case 'needs_review':
            if ($completed = _sbac_resource_determine_feedback($result->nid, 'gate_keeper', FALSE, 1, 1, 1, 'single')) {
              // check for an active Review by the current user to continue review
              if ($active = _sbac_resource_determine_feedback($result->nid, 'qc', $user->uid, 1, 0, 1, 'single')) {
                $view->result[$key]->state_label = 'Being Reviewed';
              }
              else {
                $view->result[$key]->state_label = 'Needs Review';
              }
            }
            else {
              // check for an active GK by the current user to continue review
              if ($active = _sbac_resource_determine_feedback($result->nid, 'gate_keeper', $user->uid, 1, 0, 1, 'single')) {
                $view->result[$key]->state_label = 'Being Reviewed';
              }
              else {
                $view->result[$key]->state_label = 'Needs Review';
              }
            }
            break;
          case 'approved':
            $feedback = _sbac_resource_determine_feedback($result->nid, 'post', $user->uid, 1, 0, 1, 'single');
            if ($feedback) {
              $view->result[$key]->state_label = 'Being Reviewed';
            }
            else {
              $view->result[$key]->state_label = 'Needs Posting';
            }
        }
      }
    }

    // Loop around results. Determine if the filter(s) chosen are in the
    // results. If not, remove the items that are not part of the filter
    // criteria. Else, keep the result as it is part of the return set.
    foreach ($view->result as $key => $result) {
      switch ($result->state_label) {
        case 'Being Reviewed':
          if (!in_array($result->state_label, $filter_terms)) {
            unset($view->result[$key]);
          }
          break;
        case 'Needs Review':
          if (!in_array($result->state_label, $filter_terms)) {
            unset($view->result[$key]);
          }
          break;
        case 'Needs Posting':
          if (!in_array($result->state_label, $filter_terms)) {
            unset($view->result[$key]);
          }
          break;
      }
    }
  }
}
