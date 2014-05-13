<?php


function sbac_forum_forum_listing_apply_filters(&$view, $current_filters, $active_display = 'block') {
  // $arg_definitions = $view->display_handler->get_option('arguments');
  $view_filters = $view->display_handler->get_option('filters');
  $empty_text_url = 'forums-main-page/reset/all-forums/all';

  // Current filter session - create the args where needed.
  if (!empty($current_filters)) {
    $filters = explode('::', $current_filters);
    $views_filters = array();
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
                case 'grades':
                  $view_filters['field_grades_tid']['value'][] = $tid;
                  $view_filters['field_grades_tid']['operator'] = 'and';
                  break;
                case 'intended_student_populations':
                  $view_filters['field_intended_student_tid']['value'][] = $tid;
                  $view_filters['field_intended_student_tid']['operator'] = 'and';
                  break;
                case 'subject':
                  $view_filters['field_subject_tid']['value'][] = $tid;
                  $view_filters['field_subject_tid']['operator'] = 'and';
                  break;
                case 'intended_end_user':
                  $view_filters['field_intended_end_user_tid']['value'][] = $tid;
                  $view_filters['field_intended_end_user_tid']['operator'] = 'and';
                  break;
              }
            }
          }
        }
      }
    }

    $view->display_handler->set_option('filters', $view_filters);
  }


  if ($active_display == 'block_1') { // Machine name for second display for view "my forums".
    global $user;
    $view->set_arguments(array($user->uid));
    $empty_text_url = 'forums-main-page/reset/my-forums/all';
  }

  if (!empty($current_filters)) {
    // Empty Text programatically.
    $empty_text_class = $view->display_handler->get_option('empty');
    $link_text = t('Browse all Forums');
    $link_ops = array('attributes' => array('class' => 'forum-list-filter-empty-text-reset-link button'));
    $empty_text_link = l($link_text, $empty_text_url, $link_ops);
    $empty_text_content = '<div class="sbac-forum-filter-no-results-wrapper">';
    $empty_text_content .= '<h2>Your search returned no results</h2>';
    $empty_text_content .= '<p>Please try different search criteria or browse any of the forums below ';
    $empty_text_content .= 'that have been identified for you by using the subject(s) and grade(s) in your profile</p>';
    $empty_text_content .= '<div class="sbac-forum-filter-no-result-button-link">'.$empty_text_link.'</div>';
    $empty_text_content .= '</div>';
    $empty_text_class['area']['content'] = $empty_text_content;
    $view->display_handler->set_option('empty', $empty_text_class);
  }
}


/**
 * Populates sort options with data if provided.
 *
 * @param $view
 *   The view object.
 *
 */
function sbac_forum_listing_apply_sorts(&$view, $current_sorting, $default_sort) {
  if (!empty($current_sorting)) {
    $view_sorts = $view->display_handler->get_option('sorts');

    $sort_field_key = $default_sort;
    switch ($current_sorting) {
      case 'forum-recent-activity':
        $sort_field_key = 'field_forum_last_activity_value';
        break;
      case 'forum-most-active':
        $sort_field_key = 'field_forum_topic_comment_count_value';
        break;
      case 'forum-newest':
        $sort_field_key = 'field_forum_created_value';
        break;
      case 'forum-most-participants':
        $sort_field_key = 'field_forum_member_count_value';
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


function sbac_forum_forum_listing_empty_apply_filters(&$view, $account = NULL) {
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


  $subject_all_term_obj = taxonomy_get_term_by_name('Not Subject Specific', 'subject');
  if (!empty($subject_all_term_obj) ){
    $subject_all_term = array_shift($subject_all_term_obj);
    $subject_tid_all = $subject_all_term->tid;
  } else {
    $subject_tid_all = 153; // fallback to hardcoded??
  }


  $grade_all_term_obj = taxonomy_get_term_by_name('Not Grade Specific', 'grades');
  if (!empty($grade_all_term_obj) ){
    $grade_all_term = array_shift($grade_all_term_obj);
    $grade_tid_all = $grade_all_term->tid;
  } else {
    $grade_tid_all = 122; // fallback to hardcoded??
  }

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


function sbac_forum_views_query_alter(&$view, &$query) {
  if (($view->name == 'forum_list') ||
      ($view->name == 'forum_list_empty')) {

    $condition_groups = count($query->where) + 1;

    // Get User data.
    global $user;
    $user_profile = user_load($user->uid);
    $user_profile_wrapper = entity_metadata_wrapper('user', $user_profile);
    $users_roles = array();
    if (isset($user_profile_wrapper->field_position)) {
      $position_term = $user_profile_wrapper->field_position->value();
      $users_roles[] = $position_term->tid;
    }
    $users_states = array();
    if (isset($user_profile_wrapper->field_state)) {
      $state_terms = $user_profile_wrapper->field_state->value();
      if (!empty($state_terms)) {
        foreach ($state_terms as $state) {
          $users_states[] = $state->tid;
        }
      }
    }
    $user_removed_from_forum_list = array();
    if (isset($user->data[SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME])) {
      $user_removed_from_forum_list = $user->data[SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME];
    }

    // create the join object. STATE
    $join = new views_join;
    $join->table ='field_data_field_state';
    $join->left_table = 'taxonomy_term_data';
    $join->left_field = 'tid';
    $join->field = 'entity_id';
    $join->extra = array(
       0 => array('field' => 'entity_type', 'value' => 'taxonomy_term'),
       1 => array('field' => 'deleted', 'value' => 0),
    );
    $join->type = "LEFT";
    $join->extra_type = 'AND';
    $join->adjusted = 'TRUE';

    $view->query->table_queue['field_data_field_state'] = array(
      'table' => 'field_data_field_state',
      'num' => 1,
      'alias' => 'field_data_field_state',
      'join' => $join,
      'relationship' => 'taxonomy_term'
    );

    $state_condtion_group = $condition_groups++;
    if (!empty($users_states)) {
      $query->add_where($state_condtion_group, 'field_data_field_state.field_state_tid', $users_states, 'IN');
    }
    $query->add_where($state_condtion_group, 'field_data_field_state.field_state_tid', array(), 'IS NULL');
    $query->where[$state_condtion_group]['type'] = "OR";


    // create the join object. ROLE
    $join = new views_join;
    $join->table ='field_data_field_forum_access_role_list';
    $join->left_table = 'taxonomy_term_data';
    $join->left_field = 'tid';
    $join->field = 'entity_id';
    $join->extra = array(
       0 => array('field' => 'entity_type', 'value' => 'taxonomy_term'),
       1 => array('field' => 'deleted', 'value' => 0),
    );
    $join->type = "LEFT";
    $join->extra_type = 'AND';
    $join->adjusted = 'TRUE';

    $view->query->table_queue['field_data_field_forum_access_role_list'] = array(
      'table' => 'field_data_field_forum_access_role_list',
      'num' => 1,
      'alias' => 'field_data_field_forum_access_role_list',
      'join' => $join,
      'relationship' => 'taxonomy_term'
    );

    $role_condition_group = $condition_groups++;
    $query->add_where($role_condition_group, 'field_data_field_forum_access_role_list.field_forum_access_role_list_value', $users_roles, 'IN');
    $query->add_where($role_condition_group, 'field_data_field_forum_access_role_list.field_forum_access_role_list_value', array(), 'IS NULL');
    $query->where[$role_condition_group]['type'] = "OR";

    // Should have group on its own.
    if (!empty($user_removed_from_forum_list)) { // Exclude all forums user has been removed from.
      $query->add_where($condition_groups, 'taxonomy_term_data.tid', $user_removed_from_forum_list, 'NOT IN');
    }

  }
}
