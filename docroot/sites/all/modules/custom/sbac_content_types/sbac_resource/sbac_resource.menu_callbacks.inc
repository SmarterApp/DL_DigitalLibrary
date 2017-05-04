<?php

/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_digital_library_page($page = NULL, $ajax = FALSE) {
  $no_results = NULL;
  $digital_library_pwd = '';
  $pwd_showhide = '';
  $pwd_showmore = '<a href="#" id="sbac-pwd-show-fewer">Show Fewer</a>';
  $search_string = '';
  $current_filters = '';
  $pwd_enabled = '';
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.digital_library.categories.js');
  drupal_add_js(drupal_get_path('module', 'sbac_resource') . '/js/sbac_resource.pwd.js');
  $output = array();

  $view = views_get_view('resources');
  $view->set_display($display);
  // Remove session load more attribute when search is applied.
  if (isset($_POST['current_filters']) || isset($_POST['search_keywords'])) {
    unset($_SESSION['load_more'][$view->name]);
  }
  // If pager in URL is provided, change pager
  if ($page) {
    $view->items_per_page = ($page + 1) * 12;
    $_SESSION['load_more'][$view->name]['page'] = $page;
  }
  // If session is set, change pager.
  else {
    if (isset($_SESSION['load_more'][$view->name]['page'])) {
      $view->items_per_page = ($_SESSION['load_more'][$view->name]['page'] + 1) * 12;
    }
  }

  sbac_resource_digital_library_apply_filters($view);
  sbac_resource_digital_library_apply_pwd($view);
  sbac_resource_digital_library_apply_sorts($view);
  if (!$pwd_enabled) {
    $pwd_view = views_get_view('resources');
    $pwd_view->set_display($display);
    sbac_resource_digital_library_apply_filters($pwd_view);
    sbac_resource_digital_library_apply_sorts($pwd_view);
    sbac_resource_digital_library_pwd_reel($pwd_view);
    $digital_library_pwd = $pwd_view->preview();
    if (!count($pwd_view->result)) {
      $digital_library_pwd = '';
      $pwd_showhide = '';
      $pwd_showmore = '';
    }
    else {
      $pwd_showhide = '<a href="#" id="sbac-pwd-show-hide">Hide</a>';
      $pwd_showmore = '<a href="#" id="sbac-pwd-show-more">Show More</a>';
    }
    // dpq($pwd_view->build_info['query']);
    $pwd_view->destroy();
    clear_views_exposed_filter_cache($pwd_view->name, $display);
  }
  else {
    $pwd_showhide = '<a href="#" id="sbac-pwd-hide-pwd">Hide</a>';
  }
  $digital_library_output = $view->preview();
  // dpq($view->build_info['query']);
  $count = count($view->result);
  if ($ajax) {
    $output['view_dom_id'] = $view->dom_id;
    $output['view_display_id'] = $view->current_display;
    $output['view_args'] = $view->args;
    $output['view_name'] = $view->name;
    $output['view_path'] = 'digital-library-resources';
    $output['pager_element'] = 0;
    $output['base_path'] = NULL;
  }
  $view->destroy();

  // If we didn't find any results, we default to the user's filtered subject/grade items
  $ignore_smart_search = FALSE;
  if (!$count && ($search_string != '' || $current_filters != '')) {
    // Reset variables

    // Load up the view.
    $view = views_get_view('resources');
    $view->set_display($display);

    // Views, in all of its wisdom, caches the exposed filters for each view. We need to
    // clear these in order to make sure out new filters kick in
    clear_views_exposed_filter_cache($view->name, $display);
    sbac_resource_filter_user_tags($view);
    sbac_resource_digital_library_apply_pwd($view);
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
      drupal_goto('digital-library-resources'); // Reload dlr tab with no filters set.
    }
  }

  if ($ajax) {
    $output['rendered_content'] = theme('digital_library', array(
      'digital_library_output' => $digital_library_output,
      'no_results' => $no_results,
      'smart_search_welcome' => $smart_search_text,
      'pwd' => $pwd_enabled,
      'pwd_highlights' => $digital_library_pwd,
      'pwd_showhide' => $pwd_showhide,
      'pwd_showmore' => $pwd_showmore
    ));
    return $output;
  }
  else {
    return theme('digital_library', array(
      'digital_library_output' => $digital_library_output,
      'no_results' => $no_results,
      'smart_search_welcome' => $smart_search_text,
      'pwd' => $pwd_enabled,
      'pwd_highlights' => $digital_library_pwd,
      'pwd_showhide' => $pwd_showhide,
      'pwd_showmore' => $pwd_showmore
    ));
  }
}

/**
 * Menu Callback.
 *
 * @return string
 */
function sbac_resource_my_resources_page($page = NULL, $ajax = FALSE) {
  $no_results = NULL;

  $current_filters = '';
  $display = sbac_resource_determine_grid_or_list();
  // Add appropriate JS.
  // drupal_add_js(drupal_get_path('module', 'sbac_search_api') . '/js/sbac_search_api.my_resources.categories.js');

  // Load up the view.
  $view = views_get_view('my_resources');
  $view->set_display($display);
  // Remove session load more attribute when search is applied.
  if (isset($_POST['current_filters']) || isset($_POST['search_keywords'])) {
    unset($_SESSION['load_more'][$view->name]);
  }
  // If pager in URL is provided, change pager
  if ($page) {
    $view->items_per_page = ($page + 1) * 12;
    $_SESSION['load_more'][$view->name]['page'] = $page;
  }
  // If session is set, change pager.
  else {
    if (isset($_SESSION['load_more'][$view->name]['page'])) {
      $view->items_per_page = ($_SESSION['load_more'][$view->name]['page'] + 1) * 12;
    }
  }
  sbac_resource_my_resource_apply_filters($view);
  sbac_resource_my_resource_apply_sorts($view);
  $my_resources_output = $view->preview();
  // dpq($view->build_info['query']);
  $output = array();
  if ($ajax) {
    // Create the Drupal.settings attribute
    $output['view_dom_id'] = $view->dom_id;
    $output['view_display_id'] = $view->current_display;
    $output['view_args'] = $view->args;
    $output['view_name'] = $view->name;
    $output['view_path'] = 'my-resources';
    $output['pager_element'] = 0;
    $output['base_path'] = NULL;
  }
  $view->destroy();

  if (!$view->total_rows && $current_filters != '') {
    // Reset variables

    drupal_get_messages();
    $no_results = sbac_resource_no_search_results();
  }
  menu_set_active_item('my-resources');
  if ($ajax) {
    $output['rendered_content'] = theme('my_resources', array('my_resources_output' => $my_resources_output, 'no_results' => $no_results));
    return $output;
  }
  else {
    return theme('my_resources', array('my_resources_output' => $my_resources_output, 'no_results' => $no_results));
  }
}

/**
 * Generates the two tabs' (resources and resubmission) content
 *
 * @param null $page
 * @param bool $ajax
 * @param bool $resubmission_only
 * @param bool $apply_filter
 * @return array
 */
function _sbac_resource_resource_review_page_setup_resource_tab($page = NULL, $ajax = FALSE, $resubmission_only = FALSE, $apply_filter = TRUE) {
  $display = sbac_resource_determine_grid_or_list();
  $view = views_get_view('resource_review');
  $view->set_display($display);

  $view->apply_filter = $apply_filter;
  $view->resubmission_only = $resubmission_only;
  if ($apply_filter === TRUE) {
    sbac_resource_resource_review_apply_filters($view);
  }
  sbac_resource_resource_review_apply_sorts($view);
  $resource_review_output = $view->preview();
  $total_rows = $view->total_rows;

  $output = array();
  if ($ajax) {
    // Create the Drupal.settings attribute
    $output['view_dom_id'] = $view->dom_id;
    $output['view_display_id'] = $view->current_display;
    $output['view_args'] = $view->args;
    $output['view_name'] = $view->name;
    $output['view_path'] = 'resource-review';
    $output['pager_element'] = 0;
    $output['base_path'] = NULL;
  }
  clear_views_exposed_filter_cache($view, $display);
  $view->destroy();
  return array(
    'output' => $resource_review_output,
    'ajax_output' => $output,
    'count' => $total_rows,
  );
}

/**
 * Menu callback
 */
function sbac_resource_resource_review_page_reset() {
  drupal_goto('resource-review');
}

/**
 * Menu Callback.
 *
 * @param null $page
 * @param bool $ajax
 * @return string
 */
function sbac_resource_resource_review_page($page = NULL, $ajax = FALSE) {
  $no_results = NULL;
  $current_filters = '';
  // Add appropriate JS.
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.resource_review.categories.js');

  // Get the tabs' content
  $resubmission_tab = _sbac_resource_resource_review_page_setup_resource_tab($page, $ajax, TRUE, FALSE);
  $_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB] = FALSE;
  if (0 < $resubmission_tab['count']) {
    $_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB] = TRUE;
    $resubmission_tab = _sbac_resource_resource_review_page_setup_resource_tab($page, $ajax, TRUE);
  }
  $resource_tab = _sbac_resource_resource_review_page_setup_resource_tab($page, $ajax);

  // Save the count
  $_SESSION[SBAC_RESOURCE_SUBNAV_RESOURCES_COUNT] = $resource_tab['count'];
  $_SESSION[SBAC_RESOURCE_SUBNAV_RESUBMISSIONS_COUNT] = $resubmission_tab['count'];

  if ($_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB] === FALSE) {
    $active_tab = SBAC_RESOURCE_SUBNAV_RESOURCES;
  }
  else {
    $active_tab = sbac_resource_get_active_subnav();
  }
  // Get the active tab content
  $active_tab_content = array();
  switch ($active_tab) {
    case SBAC_RESOURCE_SUBNAV_RESOURCES:
      $active_tab_content = $resource_tab;
      break;
    case SBAC_RESOURCE_SUBNAV_RESUBMISSIONS:
      $active_tab_content = $resubmission_tab;
      break;
  }
  $resource_output = $active_tab_content['output'];
  if (0 == $active_tab_content['count']) {
    // Set error message
    $no_results = sbac_resource_no_search_results();
  }

  menu_set_active_item('resource-review');
  if ($ajax) {
    $active_tab_content['ajax_output']['rendered_content'] = theme('resource_review', array('resource_review_output' => $resource_output, 'no_results' => $no_results));
    return $active_tab_content['ajax_output'];
  }
  else {
    return theme('resource_review', array('resource_review_output' => $resource_output, 'no_results' => $no_results));
  }
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
    // setup more variables here. Collapsed filter tray etc.
  }

  $_SESSION[SBAC_RESOURCE_SMART_SEARCH_HIDE_FILTERS] = TRUE; // Hide the filter block.
  $_SESSION[SBAC_RESOURCE_SMART_SEARCH_SHOW_STATUS] = TRUE; // Show the help message in content region.

  drupal_goto('digital-library-resources');

  return $output;
}
