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

  $view = views_get_view('resources');
  $view->set_display($display);
  sbac_resource_digital_library_apply_filters($view);
  sbac_resource_digital_library_apply_sorts($view);
  $digital_library_output = $view->preview();
  $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_COUNT] = $view->total_rows;
  dpq($view->build_info['query']);
  $count = count($view->result);
  $view->destroy();

  // If we didn't find any results, we default to the user's filtered subject/grade items
  $ignore_smart_search = FALSE;
  if (!$count && ($search_string != '' || $current_filters != '')) {
    // Reset variables
    $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] = '';
    $_COOKIE[SBAC_SEARCH_DIGITAL_LIBRARY_FILTERS_CLOSED] = TRUE;

    // Load up the view.
    $view = views_get_view('resources');
    $view->set_display($display);

    // Views, in all of its wisdom, caches the exposed filters for each view. We need to
    // clear these in order to make sure out new filters kick in
    clear_views_exposed_filter_cache($view->name, $display);
    sbac_resource_filter_user_tags($view);
    $digital_library_output = $view->preview();
    // dpq($view->build_info['query']);
    $view->destroy();
    drupal_get_messages();
    $no_results = sbac_resource_no_search_results($search_string);
    $ignore_smart_search = TRUE;
  }
  menu_set_active_item('digital-library-resources');

  $smart_search_text = '';
  if ((isset($_SESSION[SBAC_RESOURCE_SMART_SEARCH_SHOW_STATUS])) && ($_SESSION[SBAC_RESOURCE_SMART_SEARCH_SHOW_STATUS] == TRUE)) {
    $_SESSION[SBAC_RESOURCE_SMART_SEARCH_SHOW_STATUS] = FALSE;
    if ($ignore_smart_search == FALSE) {
      $smart_search_text = theme('smart_search_welcome', array('current_filters' => $current_filters, 'kw' => $search_string));
    }
    else { // No search results. Diff behavour.
      // Reset variables
      $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] = '';
      $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS] = '';
      $_COOKIE[SBAC_SEARCH_DIGITAL_LIBRARY_FILTERS_CLOSED] = TRUE;
      $_SESSION[SBAC_RESOURCE_SMART_SEARCH_HIDE_FILTERS] = FALSE;
      drupal_goto('digital-library-resources'); // Reload dlr tab with no filters set.
    }
  }

  return theme('digital_library', array('digital_library_output' => $digital_library_output, 'no_results' => $no_results, 'smart_search_welcome' => $smart_search_text));
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
  sbac_resource_my_resource_apply_sorts($view);
  $my_resources_output = $view->preview();
  // dpq($view->build_info['query']);
  $_SESSION[SBAC_SEARCH_MY_RESOURCES_COUNT] = $view->total_rows;
  $view->destroy();

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
  sbac_resource_resource_review_apply_sorts($view);
  $resource_review_output = $view->preview();
  // dpq($view->build_info['query']);
  $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_COUNT] = $view->total_rows;
  $view->destroy();

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

/**
 * Yuriy's lack of comments ;)
 *
 * @param string $string
 * @return string
 */
function sbac_resource_no_search_results($string = '') {
  $output = '';
  if ($string) {
    if (strlen($string) < 3) {
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
    have been identified for you using the subject(s) and grade(s) in your profile.') . '</p>'; // <---- LIES!! LOL!

  return $output;
}

/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_smart_search_page() {
  $output = 'testing';

  $params = $_GET;
  unset($params['q']);
  if (empty($params)) { // No query string attached. No need to do anything.
    drupal_goto('digital-library-resources');
  }

  $current_filter_array = array();
  if (isset($params['kw'])) {
    $kw_search = $params['kw'];
    $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_KEYWORDS] = $kw_search;
    unset($params['kw']);
  }
  foreach ($params as $vocab => $term_ids) {
    $vocab_details = explode(':', $vocab);
    $terms = explode(',', $term_ids);
    if (!empty($terms)) {
      foreach ($terms as $term_id) {
        $current_filter_array[] = $vocab_details[1] . ':' . $term_id;
      }
    }
  }

  if (!empty($current_filter_array)) {
    $current_filters = implode('::', $current_filter_array);
    $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] = $current_filters;
    // setup more variables here. Collapsed filter tray etc.
  }

  // $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_FILTERS] = '';
  $_SESSION[SBAC_RESOURCE_SMART_SEARCH_HIDE_FILTERS] = TRUE; // Hide the filter block.
  $_SESSION[SBAC_RESOURCE_SMART_SEARCH_SHOW_STATUS] = TRUE; // Show the help message in content region.

  drupal_goto('digital-library-resources');

  return $output;
}
