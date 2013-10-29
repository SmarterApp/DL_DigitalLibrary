<?php

/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_digital_library_page() {
  $no_results = NULL;
  (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS]) ? $search_string = $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS] : $search_string = '');
  (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS]) ? $current_filters = $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] : $current_filters = '');
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.digital_library.categories.js');

  // Load up the view.
  $view = views_get_view('resources');
  $view->set_display($display);
  sbac_resource_digital_library_apply_filters($view);
  $view->pre_execute();
  $view->execute();
  $view->_post_execute();
  $digital_library_output = $view->preview();
  $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_COUNT] = $view->total_rows;

  $count = count($view->result);
  $view->destroy();

  // If we didn't find any results, we default to the user's filtered subject/grade items
  if (!$count && ($search_string != '' || $current_filters != '')) {
    // Reset variables
    $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] = '';
    $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS] = '';
    $_COOKIE[SBAC_SEARCH_DIGITAL_LIBRARY_FILTERS_CLOSED] = TRUE;

    // Load up the view.
    $view = views_get_view('resources');
    $view->set_display($display);

    // Views, in all of its wisdom, caches the exposed filters for each view. We need to
    // clear these in order to make sure out new filters kick in
    clear_views_exposed_filter_cache($view->name, $display);
    sbac_resource_filter_user_tags($view);

    $view->pre_execute();
    $view->execute();
    $view->_post_execute();

    $digital_library_output = $view->preview();
    $view->destroy();

    drupal_get_messages();
    $no_results = sbac_resource_no_search_results($search_string);
  }

  menu_set_active_item('digital-library-resources');
  return theme('digital_library', array('digital_library_output' => $digital_library_output, 'no_results' => $no_results));
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
  $view->destroy();
  $_SESSION[SBAC_SEARCH_MY_RESOURCES_COUNT] = $view->total_rows;

  if (!$view->total_rows && $current_filters != '') {
    // Reset variables
    $_SESSION[SBAC_SEARCH_MY_RESOURCES_FILTERS] = '';
    $_COOKIE[SBAC_SEARCH_MY_RESOURCES_FILTERS_CLOSED] = TRUE;

    drupal_get_messages();
    $no_results = sbac_resource_no_search_results();
  }
  
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
  (isset($_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS]) ? $current_filters = $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS] : $current_filters = '');
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.resource_review.categories.js');

  // Load up the view.
  $view = views_get_view('resource_review');
  $view->set_display($display);
  sbac_resource_resource_review_apply_filters($view);
  $view->pre_execute();
  $view->execute();
  $view->_post_execute();
  $resource_review_output = $view->preview();
  $view->destroy();
  $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_COUNT] = $view->total_rows;

  if (!$view->total_rows && $current_filters != '') {
    // Reset variables
    $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS] = '';
    $_COOKIE[SBAC_SEARCH_RESOURCE_REVIEW_FILTERS_CLOSED] = TRUE;

    // Set error message
    $no_results = sbac_resource_no_search_results();
  }

  menu_set_active_item('resource-review');
  return theme('resource_review', array('resource_review_output' => $resource_review_output, 'no_results' => $no_results));
}

function sbac_resource_no_search_results($string = '') {
  $output = '';
  if ($string) {
    if (strlen($string < 3)) {
      $output .= '<h3>' . t('You must enter 3 characters or more.') . '</h3>';
    }
    else {
      $output .= '<h3>' . t('Your search for %string returned no results.', array('%string' => $string)) . '</h3>';
    }
  }
  else {
    $output .= '<h3>' . t('Your search returned no results') . '</h3>';
  }

  $output .= '<p>' . t('Please try a different search term or browse any of the resources below that 
    have been identified for you using the subject(s) and grade(s) in your profile.') . '</p>'; // <---- LIES!!

  return $output;
}