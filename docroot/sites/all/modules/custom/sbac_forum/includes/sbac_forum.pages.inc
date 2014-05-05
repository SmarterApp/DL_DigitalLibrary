<?php

/**
 * Main Page - /Forums. Shows all forums and allows users to filter/sort them.
 *
 * @return HTML output from theme function.
 */
function sbac_forum_main_landing_page() {
  // module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.views');
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  $output = '';
  $current_filters = '';
  $passive_filters = '';
  $current_sorts = '';
  $default_sort = 'forum-most-active';
  $count_values = array();
  $active_display = 'block';
  $passive_display = 'block_1';
  $forum_list_output = 'Forum Content';

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  }
  // Get correct set of category filters based on subnav.
  switch($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_ALL:
      $active_display = 'block';
      $passive_display = 'block_1';
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS])) {
        $passive_filters = $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_ALL_FORUM_SORTS]) &&
          $_SESSION[SBAC_FORUM_ALL_FORUM_SORTS] != '') {
        $current_sorts = $_SESSION[SBAC_FORUM_ALL_FORUM_SORTS];
      }
      break;
    case SBAC_FORUM_SUBNAV_OWN:
      $active_display = 'block_1';
      $passive_display = 'block';
      if (isset($_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $passive_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_MY_FORUM_SORTS]) &&
          $_SESSION[SBAC_FORUM_MY_FORUM_SORTS] != '') {
        $current_sorts = $_SESSION[SBAC_FORUM_MY_FORUM_SORTS];
        $default_sort = 'forum-recent-activity';
      }
      break;
    case SBAC_FORUM_SUBNAV_RESOURCE:
      $active_display = 'block_2';
      $passive_display = 'block_3';
      if (isset($_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $passive_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS]) &&
        $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS] != '') {
        $current_sorts = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS];
        $default_sort = 'forum-recent-activity';
      }
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      $active_display = 'block_3';
      $passive_display = 'block_2';
      if (isset($_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $passive_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS]) &&
        $_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS] != '') {
        $current_sorts = $_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS];
        $default_sort = 'forum-recent-activity';
      }
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }

  // Passive
  $view_p = views_get_view('forum_list');
  $view_p->set_display($passive_display);
  sbac_forum_forum_listing_apply_filters($view_p, $passive_filters, $passive_display); // Set filters here.
  $view_p->pre_execute();
  $view_p->execute();
  $view_p->_post_execute();
  $count_values[$passive_display] = $view_p->total_rows;
  $view_p->destroy();

  // Active
  $view = views_get_view('forum_list');
  $view->set_display($active_display);
  sbac_forum_forum_listing_apply_filters($view, $current_filters, $active_display); // Set filters here.
  sbac_forum_listing_apply_sorts($view, $current_sorts, $default_sort);
  $view->pre_execute();
  $view->execute();
  $view->_post_execute();
  $forum_list_output = $view->preview();
  $active_view_count = $view->total_rows;
  $count_values[$active_display] = $active_view_count;

  // Empty
  if ((!$active_view_count) && (!empty($current_filters)) ) {
      if ($active_display == 'block') {
        $_SESSION[SBAC_FORUM_CATEGORY_FILTERS] = '';
        $_COOKIE[SBAC_FORUM_FILTERS_CLOSED] = TRUE;
      } else {
        $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS] = '';
        $_COOKIE[SBAC_FORUM_MY_FORUM_FILTERS_CLOSED] = TRUE;
      }
      $view_e = views_get_view('forum_list_empty');
      $view_e->set_display('block');
      sbac_forum_forum_listing_empty_apply_filters($view_e); // Set filters here.
      $view_e->pre_execute();
      $view_e->execute();
      $view_e->_post_execute();
      $forum_list_empty_output = $view_e->preview();
      $forum_list_output .= $forum_list_empty_output;
  }

  $_SESSION[SBAC_FORUM_FILTER_RESULTS_COUNTER] = $count_values;
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  $subnav = drupal_get_form('sbac_forum_sub_nav_form', $count_values);
  $output .= drupal_render($subnav);

  $output .= '<div class="sbac-forum-main-container">';
  $output .= $forum_list_output;
  $output .= '</div>';

  return $output;
}

/**
 * Middleground cleanup page callback to reset session variables and perform redirection.
 *
 * @param string $item which page is requesting cleanup (all forums or my forums)
 * @param string $severity default or all. Tells function how extensive the clear needs to be.
 *
 */
function sbac_forum_main_landing_page_reset($item, $severity) {
  switch ($item) {
    case 'all-forums':
      $_SESSION[SBAC_FORUM_CATEGORY_FILTERS] = '';
      break;
    case 'my-forums':
      if ($severity == 'default') {
        sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
      } else {
        $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS] = '';
        // sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
      }
      break;
  }
  drupal_goto('forums');
}

/**
 * Middleground traffic controller. Used to set the active subnav element on forums then redirect to page.
 *
 * @param string $where where to redirect to.
 */
function sbac_forum_keyword_search_redirect($where = FALSE) {
  switch($where) {
    case 'all-forums':
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
      break;
    case 'my-forums':
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_OWN);
      break;
    default:
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
      break;
  }
  drupal_goto('forums');
}

/**
 * Custom taxonomy term view page for forum terms.
 *
 * @param [type] $term [description]
 *
 * @return [type] [description]
 */
function sbac_forum_view_forum_page($term) {
	global $user;
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  $output = '';

  // Load up forum data.
  $forum_data = entity_metadata_wrapper('taxonomy_term', $term);
  // $test = $forum_data->getPropertyInfo();

  $description_text = '';
  if (isset($forum_data->field_forum_description)) {
    $description_text = more_less_text($forum_data->field_forum_description->value());
  }
  $add_comma = FALSE;
  $is_facilitator = FALSE;
  $facilitator_text = '';
  $faci_details = '';
  if (isset($forum_data->field_forum_facilitators)) {
    $facilitators = $forum_data->field_forum_facilitators->value();
    if (!empty($facilitators)) {
      $add_comma = sizeof($facilitators);
      $item_list = array();
      foreach ($facilitators as $faci) {
        if ($faci->uid == $user->uid) {
          $is_facilitator = TRUE;
        }
        $item_list[] = sbac_forum__api__get_authpane_hoverover($faci->uid, --$add_comma);
      }

      $list_args = array(
        'type'  => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-auth-pane'),
      );
      $facilitator_text = theme('item_list', $list_args);
    }
  }


  $subject_text = '';
  if (isset($forum_data->field_subject)) {
    $subjects = $forum_data->field_subject->value();
    if (!empty($subjects)) {
      $item_list = array();
      foreach ($subjects as $subject) {
        $item_list[] = $subject->name;
      }
      $list_args = array(
        'type'  => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-subject-list'),
      );
      $subject_text = theme('item_list', $list_args);
    }
  }


  $grades_text = '';
  if (isset($forum_data->field_grades)) {
    $grades = $forum_data->field_grades->value();
    if (!empty($grades)) {
      $item_list = array();
      foreach ($grades as $grade) {
        $item_list[] = $grade->name;
      }
      $list_args = array(
        'type'  => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-grades-list'),
      );
      $grades_text = theme('item_list', $list_args);
    }
  }


  $end_user_text = '';
  if (isset($forum_data->field_intended_end_user)) {
    $end_users = $forum_data->field_intended_end_user->value();
    if (!empty($end_users)) {
      $item_list = array();
      foreach ($end_users as $end_user) {
        $item_list[] = $end_user->name;
      }
      $list_args = array(
        'type'  => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-grades-list'),
      );
      $end_user_text = theme('item_list', $list_args);
    }
  }


  $student_text = '';
  if (isset($forum_data->field_intended_student)) {
    $students = $forum_data->field_intended_student->value();
    if (!empty($students)) {
      $item_list = array();
      foreach ($students as $student) {
        $item_list[] = $student->name;
      }
      $list_args = array(
        'type'  => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-grades-list'),
      );
      $student_text = theme('item_list', $list_args);
    }
  }

  $tabs = array();
  $tab_classes = array();
  $current_topic_count = $forum_data->field_forum_topic_count->value();
  $topic_count_text = ' (0)';
  if ($current_topic_count) {
    $topic_count_text = ' (' .$current_topic_count .')';
  }
  $tabs[] = array(
    'vid' => 'forum_topic_list',
    'display' => 'block',
    'args' => $term->tid,
    'title' => t('Topics'). $topic_count_text,
    'weight' => -99,
    'type' => 'view',
  );
  $tab_classes[] = 'sbac-qt-show';


  $is_member = sbac_forum__api__check_user_is_forum_member($term->tid, $user->uid);
  if ($is_member === TRUE) {
    $show_members = 'sbac-qt-show';
  } elseif ($is_member === FALSE) {
    $show_members = 'sbac-qt-hide';
  } elseif ($is_member == 'removed') {
    $show_members = '';
  }

  if (!empty($show_members)) {
    $current_member_count = $forum_data->field_forum_member_count->value();
    $member_count_text = '';
    if ($current_member_count) {
      $member_count_text = '(' .$current_member_count .')';
    }
    $tabs[] = array(
      'vid' => 'forum_member_list',
      'display' => 'block',
      'args' => $term->tid,
      'title' => t('Members '.$member_count_text),
      'weight' => -98,
      'type' => 'view',
    );
    $tab_classes[] = 'sbac-forum-vp-member-tab-item ' . $show_members;
  }


  if (in_array('facilitator', $user->roles)) { // User is a facilitator
    if (($is_member === TRUE) ||
        ($is_member === FALSE) ){ // Show tab as long as user is not removed.
      $removed_member_count = $forum_data->field_forum_removed_member_count->value();
      $removed_member_count_text = '';
      if ($removed_member_count) {
        $removed_member_count_text = '(' .$removed_member_count .')';
      }
      $tabs[] = array(
        'vid' => 'forum_member_list',
        'display' => 'block_1',
        'args' => $term->tid,
        'title' => t('Removed Members '. $removed_member_count_text),
        'weight' => -97,
        'type' => 'view',
      );
      $tab_classes[] = 'sbac-forum-vp-rem-members-tab-item ' . $show_members;
    }
  }


  $qtname = 'forum_content';
  $default_tab = 0;
  $overrides = array(
    'style' => 'sbac-forum', // Style available, none/zen/etc.
    'sorted' => TRUE, // TRUE or FALSE.
    'ajax' => FALSE, // TRUE or FALSE.
    'default_tab' => $default_tab, // Id of the tab - 0/1/2/etc.
    'list_classes' => $tab_classes,
  );
  $taxonomy_tabs = quicktabs_build_quicktabs($qtname, $overrides, $tabs);
  $tab_output = drupal_render($taxonomy_tabs);


  // Controls.
  $forum_control_links = array();
  $forum_control_link_list = sbac_forum__api__create_forum_controls($is_member, $is_facilitator, $term->tid);
  drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.view_page.js");

  // Check if user had just joined. Show welcome message and then unset the variable.
  $welcome_message = '';
  if (isset($_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE]) ) {
    $welcome_message = $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE];
    $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE] = '';
  }

  // If this is a resource forum, then I am favoriting the resource itself (node)
  // Otherwise I'm favoriting the forum (taxonomy term)
  $id = $term->tid;
  $type = 'term';
  if (!empty($term->field_forum_resource_ref)) {
    $resource_wrapper  = $forum_data->field_forum_resource_ref;
    $id = $term->field_forum_resource_ref['und'][0]['target_id'];
    $type = 'node';
    $resource_link = l('View Resource', 'node/' . $id, array('attributes' => array('target' => '_blank')));

    // resource image
    $default_file = 'public://file.png';
    $uri = $default_file;
    if ($resource_wrapper->__isset('field_thumbnail_uri')) {
      $thumbnail_uri = $forum_data->field_forum_resource_ref->field_thumbnail_uri->value();
      $thumbnail_uri  = str_replace('<div class="field-content">', '', $thumbnail_uri);
      $thumbnail_uri  = str_replace('</div>', '', $thumbnail_uri);
      $thumbnail_pieces = explode('::', $thumbnail_uri);
      $uri = $thumbnail_pieces[0];
      $ext = pathinfo($uri, PATHINFO_EXTENSION);
      $file_type = _sbac_resource_determine_extension($ext);
      if ($file_type != 'image') {
        $uri = $default_file;
      }
    }
    $resource_image = theme('image_style', array(
      'style_name' => 'resource_image_grid',
      'path' => $uri,
      'attributes' => array('class' => array()),
      'alt'=>'Resource thumbnail image'
    ));

    // resource rating
    $resource_rating = sbac_resource_display_fivestar_rating(sbac_resource_get_rating_average($id));
    $resource_rating_count = sbac_resource_get_rating_count($id);

    // views
    $resource_views = 0;
    if ($resource_wrapper->__isset('field_unique_views')){
      $resource_views = $resource_wrapper->field_unique_views->value();
    }

    // downloads
    $resource_downloads = 0;
    if ($resource_wrapper->__isset('field_asset_downloads')){}
    $resource_downloads = $resource_wrapper->field_asset_downloads->value();
  }
  // if the user has this entity as a favorite.
  $favorites_class = 'sbac-favorites-link-no';
  $favorite_text = t('Add to Favorites');
  $favorites = sbac_favorites_get_favorites($user->uid, $id, $type);
  if ($favorites) {
    $favorites_class = 'sbac-favorites-link-yes';
    $favorite_text = t('Unfavorite');
  }

  drupal_add_js(drupal_get_path("module", "sbac_favorites") . "/js/sbac_favorites.js");
  $favorite_link = l($favorite_text, $_GET['q'], array(
    'attributes' => array(
      'class' => array(
        'sbac-favorites-link',
        $favorites_class
      ),
      'id' => $id,
      'uid' => $user->uid,
      'type' => $type,
    )
  ));

  // Add all the markup to variable for tpl.
  $fields = array(
    'welcome_message' => $welcome_message,
    'controls_link_list' => $forum_control_link_list,
    'description' => $description_text,
    'facilitators' => $facilitator_text,
    'faciliatator_details' => $faci_details,
    'grades' => $grades_text,
    'subjects' => $subject_text,
    'end_users' => $end_user_text,
    'students' => $student_text,
    'tabs' => $tab_output,
    'favorites_link' => $favorite_link,
    'resource_link' => $resource_link,
    'resource_image' => $resource_image,
    'resource_rating' => $resource_rating,
    'resource_rating_count' => $resource_rating_count,
    'resource_views' => $resource_views,
    'resource_downloads' => $resource_downloads,
  );

  $output = theme('sbac_forum_render_target_forum', array('fields' => $fields) );
  return $output;
}
