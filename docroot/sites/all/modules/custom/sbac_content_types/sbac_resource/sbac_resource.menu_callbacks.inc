<?php

/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_digital_library_page() {
  $no_results = NULL;
  (isset($_SESSION['sbac-search-keywords']) ? $search_string = $_SESSION['sbac-search-keywords'] : $search_string = '');
  (isset($_SESSION['sbac-current-filters']) ? $current_filters = $_SESSION['sbac-current-filters'] : $current_filters = '');
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.categories.js');

  // Load up the view.
  $view = views_get_view('resources');
  $view->set_display($display);
  sbac_resource_digital_library_apply_filters($view);
  $view->pre_execute();
  $view->execute();
  $view->_post_execute();
  $resource_layout_view = $view->preview();
  $_SESSION['sbac_search_count'] = $view->total_rows;
  dpq($view->build_info['query']);

  // if there is 0 rows.
  $count = count($view->result);
  if (!$count && ($search_string != '' || $current_filters != '')) {
    // Get all results
    $resource_layout_view = views_embed_view('all_resources', $display);

    // Reset variables
    $_SESSION['sbac-current-filters'] = '';
    $_SESSION['sbac-search-keywords'] = '';
    $_COOKIE['sbac_search_categories_closed'] = TRUE;

    // Set error message
    if ($search_string && strlen($search_string) < 3) {
      drupal_get_messages();
      $no_results = '<h3>You must enter 3 characters or more.</h3>';
      $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
      $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
    }
    else if ($search_string) {
      $no_results = '<h3>Your search for "' . $search_string . '" returned no results.</h3>';
      $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
      $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
    }
    else {
      $no_results = '<h3>Your search returned no results.</h3>';
      $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
      $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
    }
  }

  $view->destroy();
  menu_set_active_item('digital-library-resources');
  return theme('digital_library', array('resource_layout_view' => $resource_layout_view, 'no_results' => $no_results));
}

/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_my_resources_page() {
  $no_results = NULL;

  (isset($_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS]) ? $current_filters = $_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS] : $current_filters = '');
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.my_resources.categories.js');

  // Load up the view.
  $view = views_get_view('my_resources');
  $view->set_display($display);
  sbac_resource_my_resource_apply_filters($view);
  $view->pre_execute();
  $view->execute();
  $view->_post_execute();
  $my_resources_output = $view->preview();
  $_SESSION['sbac_mr_search_count'] = $view->total_rows;
  // dpq($view->build_info['query']);

  // if there is 0 rows.
  $count = count($view->result);
  if (!$count && $current_filters != '') {
    // Get all results
    $my_resources_output = views_embed_view('all_resources', $display);

    // Reset variables
    $_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS] = '';
    $_COOKIE['sbac_mr_filters_closed'] = TRUE;

    // Set error message
    $no_results = '<h3>Your search returned no results.</h3>';
    $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
    $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
  }

  $view->destroy();
  menu_set_active_item('my-resources');
  return theme('my_resources', array('my_resources_output' => $my_resources_output, 'no_results' => $no_results));
}


/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_resource_review_page() {
  $no_results = NULL;
  (isset($_SESSION['sbac-search-keywords']) ? $search_string = $_SESSION['sbac-search-keywords'] : $search_string = '');
  (isset($_SESSION['sbac-current-filters']) ? $current_filters = $_SESSION['sbac-current-filters'] : $current_filters = '');
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.categories.js');

  // Load up the view.
  $view = views_get_view('resources');
  $view->set_display($display);
  _sbac_resource_apply_filters($view);
  $view->pre_execute();
  $view->execute();
  $view->_post_execute();
  $resource_layout_view = $view->preview();
  $_SESSION['sbac_search_count'] = $view->total_rows;
  // dpq($view->build_info['query']);

  // if there is 0 rows.
  $count = count($view->result);
  if (!$count && ($search_string != '' || $current_filters != '')) {
    // Get all results
    $resource_layout_view = views_embed_view('all_resources', $display);

    // Reset variables
    $_SESSION['sbac-current-filters'] = '';
    $_SESSION['sbac-search-keywords'] = '';
    $_COOKIE['sbac_search_categories_closed'] = TRUE;

    // Set error message
    if ($search_string && strlen($search_string) < 3) {
      drupal_get_messages();
      $no_results = '<h3>You must enter 3 characters or more.</h3>';
      $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
      $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
    }
    else if ($search_string) {
      $no_results = '<h3>Your search for "' . $search_string . '" returned no results.</h3>';
      $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
      $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
    }
    else {
      $no_results = '<h3>Your search returned no results.</h3>';
      $no_results .= '<p>Please try a different search term or browse any of the resources below that ';
      $no_results .= 'have been identified for you using the subject(s) and grade(s) in your profile.</p>';
    }
  }

  $view->destroy();
  menu_set_active_item('digital-library-resources');
  return theme('digital_library', array('resource_layout_view' => $resource_layout_view, 'no_results' => $no_results));
}