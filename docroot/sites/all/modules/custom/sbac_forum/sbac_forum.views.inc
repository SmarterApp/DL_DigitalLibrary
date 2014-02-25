<?php


function sbac_forum_forum_listing_apply_filters(&$view, $current_filters, $active_display = 'block') {
  // $arg_definitions = $view->display_handler->get_option('arguments');
  $view_filters = $view->display_handler->get_option('filters');

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
  }
}
