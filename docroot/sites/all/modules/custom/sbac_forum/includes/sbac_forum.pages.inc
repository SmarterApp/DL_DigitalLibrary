<?php

/**
 * Main Page - /Forums. Shows all forums and allows users to filter/sort them.
 *
 * @return HTML output from theme function.
 */
function sbac_forum_main_landing_page($page = NULL, $ajax = FALSE) {
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
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_RESOURCE);
  }
  // Get correct set of category filters based on subnav.
  switch ($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_RESOURCE:
      $active_display = 'block_3';
      $passive_display = 'block_3';
      if (isset($_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $passive_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
        // If there are filters applied, we need to remove the saved value.
        unset($_SESSION['forums'][$passive_display]);
      }
      if (isset($_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS]) &&
        $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS] != ''
      ) {
        $current_sorts = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS];
        $default_sort = 'forum-recent-activity';
      }
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      if (isset($_GET['only-joined']) && $_GET['only-joined'] == 1) {
        $active_display = 'block_1';
      } else {
        $active_display = 'block_3';
      }
      $passive_display = 'block_2';
      if (isset($_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $passive_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS]) &&
        $_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS] != ''
      ) {
        $current_sorts = $_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS];
        $default_sort = 'forum-recent-activity';
      }
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }

  // Passive
  if (!isset($_SESSION['forums'][$passive_display])) {
    $view_p = views_get_view('forum_list');
    $view_p->set_display($passive_display);
    sbac_forum_forum_listing_apply_filters($view_p, $passive_filters, $passive_display); // Set filters here.
    $view_p->pre_execute();
    $view_p->execute();
    // $view_p->post_execute();
    $count_values[$passive_display] = $view_p->total_rows;
    $view_p->destroy();

    $_SESSION['forums'][$passive_display] = $count_values[$passive_display];
  }
  else {
    $count_values[$passive_display] = $_SESSION['forums'][$passive_display];
  }

  // Active
  $view = views_get_view('forum_list');
  $view->set_display($active_display);
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
  else if (isset($_SESSION['load_more'][$view->name]['page'])) {
    $view->items_per_page = ($_SESSION['load_more'][$view->name]['page'] + 1) * 12;
  }
  sbac_forum_forum_listing_apply_filters($view, $current_filters, $active_display); // Set filters here.
  sbac_forum_listing_apply_sorts($view, $current_sorts, $default_sort);
  $view->pre_execute();
  $view->execute();
  // $view->post_execute();
  // dpq($view->build_info['query']);

  $forum_list_output = $view->preview();
  $active_view_count = $view->total_rows;
  $count_values[$active_display] = $active_view_count;
  $ajax_output = array();
  if ($ajax) {
    $ajax_output['view_dom_id'] = $view->dom_id;
    $ajax_output['view_display_id'] = $view->current_display;
    $ajax_output['view_args'] = $view->args;
    $ajax_output['view_name'] = $view->name;
    $ajax_output['view_path'] = 'forums';
    $ajax_output['pager_element'] = 0;
    $ajax_output['base_path'] = NULL;
  }

  // Empty
  if ((!$active_view_count) && (!empty($current_filters))) {
    if ($active_display == 'block') {
      $_SESSION[SBAC_FORUM_CATEGORY_FILTERS] = '';
      $_COOKIE[SBAC_FORUM_FILTERS_CLOSED] = TRUE;
    }
    else {
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

  // Generate top nav form.
  $_SESSION[SBAC_FORUM_FILTER_RESULTS_COUNTER] = $count_values;
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  $subnav = drupal_get_form('sbac_forum_sub_nav_form', $count_values);

  if (!$ajax) {
    $output .= drupal_render($subnav);
    $output .= '<div class="sbac-forum-main-container">';
    switch ($active_tab) {
      case SBAC_FORUM_SUBNAV_RESOURCE:
				$output .= '<p class="recource-forums">';
        $output .= t('<strong>Resource Forums</strong> provide opportunities to discuss specific resources in the Digital Library. The title of the forum is the title of the resource. View the <a href="@help-topics"> Help Topics</a> to learn more about Resource Forums.' , array(
        '@help-topics' => '/help-topics',
        ));
        break;

      case SBAC_FORUM_SUBNAV_TOPIC:
				$output .= '<p class="topic-forums">';
        $output .= t('<strong>Topic Forums</strong> provide opportunities to discuss the formative assessment process, standards, curriculum, summative and interim assessments, professional development, and other topics with colleagues across the country. The title reflects the focus of the discussion. View the <a href="@help-topics"> Help Topics</a> to learn more about Topic Forums.' , array(
        '@help-topics' => '/help-topics',
        ));
        break;
    }
    $output .= $forum_list_output;
	$output .= '</p>';
    $output .= '</div>';
    return $output;
  }
  else {
    $output .= drupal_render($subnav);
    $output .= '<div class="sbac-forum-main-container">';
    $output .= $forum_list_output;
    $output .= '</div>';
    $ajax_output['rendered_content'] = $output;
    return $ajax_output;
  }
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
      }
      else {
        $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS] = '';
        // sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
      }
      break;
    case 'topic-forums':
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_TOPIC);
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
  switch ($where) {
    case 'resource-forums':
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_RESOURCE);
      break;
    case 'topic-forums':
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_TOPIC);
      break;
    default:
      sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_TOPIC);
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

  $query = "INSERT INTO {sbac_forum_views} (uid, tid, hits) VALUES (:uid, :tid, 1) ON DUPLICATE KEY UPDATE hits = hits + 1";
  db_query($query, array(
    ':uid' => $user->uid,
    ':tid' => $term->tid,
  ));
  if ($term->field_add_to_leaderboard['und'][0]['value'] == 1 && $term->field_forum_access_states['und'][0]['value'] == 0) {
    sbac_goals_update_forum_goals($term->tid);
  }
  // Load up forum data.
  $forum_data = entity_metadata_wrapper('taxonomy_term', $term);
  // $test = $forum_data->getPropertyInfo();

  $description_text = '';
  if (isset($forum_data->field_forum_description)) {
    $description_text = more_less_text($forum_data->field_forum_description->value());
  }

  $is_facilitator = FALSE;
  $facilitator_text = '';
  $faci_details = '';
  if (!$forum_data->field_forum_resource_ref->value()) {
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
          'type' => 'ul',
          'items' => $item_list,
          'attributes' => array('class' => 'vp-auth-pane'),
        );
        $facilitator_text = theme('item_list', $list_args);
      }
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
        'type' => 'ul',
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
        'type' => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-grades-list'),
      );
      $grades_text = theme('item_list', $list_args);
    }
  }


  $end_user_text = '';
  if (isset($forum_data->field_intended_participants)) {
    $end_users = $forum_data->field_intended_participants->value();
    if (!empty($end_users)) {
      $item_list = array();
      foreach ($end_users as $end_user) {
        $item_list[] = $end_user->name;
      }
      $list_args = array(
        'type' => 'ul',
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
        'type' => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-grades-list'),
      );
      $student_text = theme('item_list', $list_args);
    }
  }

  $attributes_text = '';
  if (isset($forum_data->field_attributes)) {
    $attributes = $forum_data->field_attributes->value();
    if (!empty($attributes)) {
      $item_list = array();
      foreach ($attributes as $attribute) {
        $item_list[] = $attribute->name;
      }
      $list_args = array(
        'type' => 'ul',
        'items' => $item_list,
        'attributes' => array('class' => 'vp-attributes-list'),
      );
      $attributes_text = theme('item_list', $list_args);
    }
  }

  $tabs = array();
  $tab_classes = array();
  $current_topic_count = $forum_data->field_forum_topic_count->value();
  $topic_count_text = ' (0)';
  if ($current_topic_count) {
    $topic_count_text = ' (' . $current_topic_count . ')';
  }
  $tabs[] = array(
    'vid' => 'forum_topic_list',
    'display' => 'block',
    'args' => $term->tid,
    'title' => t('Discussions') . $topic_count_text,
    'weight' => -99,
    'type' => 'view',
  );
  $tab_classes[] = 'sbac-qt-show';

  $current_member_count = $forum_data->field_forum_member_count->value();
  $member_count_text = '(' . $current_member_count . ')';
  $tabs[] = array(
    'vid' => 'forum_member_list',
    'display' => 'block',
    'args' => $term->tid,
    'title' => t('Members ' . $member_count_text),
    'weight' => -98,
    'type' => 'view',
  );
  $tab_classes[] = 'sbac-forum-vp-member-tab-item ';

  $qtname = 'forum_content';
  $default_tab = 0;
  $overrides = array(
    'style' => 'sbac-forum', // Style available, none/zen/etc.
    'sorted' => TRUE, // TRUE or FALSE.
    'ajax' => TRUE, // TRUE or FALSE.
    'default_tab' => $default_tab, // Id of the tab - 0/1/2/etc.
  );
  $taxonomy_tabs = quicktabs_build_quicktabs($qtname, $overrides, $tabs);
  $tab_output = drupal_render($taxonomy_tabs);


  // Controls.
  $forum_control_links = array();
  $forum_control_link_list = sbac_forum__api__create_forum_controls($is_facilitator, $term->tid);
  drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.view_page.js");

  // Check if user had just joined. Show welcome message and then unset the variable.
  $welcome_message = '';
  if (isset($_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE])) {
    $welcome_message = $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE];
    $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE] = '';
  }

  // If this is a resource forum, then I am favoriting the resource itself (node)
  // Otherwise I'm favoriting the forum (taxonomy term)
  $id = $term->tid;
  $fav_type = 'term';
  if (!empty($term->field_forum_resource_ref)) {
    $resource_wrapper = $forum_data->field_forum_resource_ref;
    $id = $term->field_forum_resource_ref['und'][0]['target_id'];
    $fav_type = 'node';
    $resource_link = l('View Resource', 'node/' . $id, array('attributes' => array('target' => '_blank')));

    // resource image
    $default_file = 'no_img';
    $uri = NULL;
    $url = NULL;
    if ($resource_wrapper->__isset('field_thumbnail_uri')) {
      $thumbnail_uri = $forum_data->field_forum_resource_ref->field_thumbnail_uri->value();
      $thumbnail_uri = str_replace('<div class="field-content">', '', $thumbnail_uri);
      $thumbnail_uri = str_replace('</div>', '', $thumbnail_uri);
      $thumbnail_pieces = explode('::', $thumbnail_uri);
      $uri = $thumbnail_pieces[0];
      $url = $thumbnail_pieces[1];
      $ext = pathinfo($uri, PATHINFO_EXTENSION);
      $type = _sbac_resource_determine_extension($ext);
      $real_path = drupal_realpath($uri);
      if (!file_exists($real_path)) {
        $url = $default_file;
        $uri = $default_file;
      }

      if ($type != 'image') {
        $url = $default_file;
        $uri = $default_file;
      }
    }
    else {
      $url = $default_file;
      $uri = $default_file;
    }

    if ($uri != 'no_img' && $url != 'no_img') {
      $image_url = file_create_url($uri);
      $image_tag = '<img typeof="foaf:Image" src="' . $image_url . '" width="268" height="138" alt="Resource thumbnail image" />';
      $variables['image'] = $image_tag;
      $variables['mime-type'] = file_get_mimetype($url);
      $variables['file-type-icon'] = 'document';
    }

    // resource rating
    $resource_rating = sbac_resource_display_fivestar_rating(sbac_resource_get_rating_average($id));
    $resource_rating_count = sbac_resource_get_rating_count($id);

    // views
    $resource_views = 0;
    if ($resource_wrapper->__isset('field_unique_views')) {
      $resource_views = $resource_wrapper->field_unique_views->value();
    }

    // downloads
    $resource_downloads = 0;
    if ($resource_wrapper->__isset('field_asset_downloads')) {
    }
    $resource_downloads = $resource_wrapper->field_asset_downloads->value();
  }

  if (!empty($term->field_state_or_district_image)) {
      $forum_image_url = file_create_url($term->field_state_or_district_image['und'][0]['uri']);
      $image_tag = '<img typeof="foaf:Image" src="' . $forum_image_url . '" width="268" height="138" alt="Forum thumbnail image" />';
      $variables['image'] = $image_tag;
      $variables['mime-type'] = file_get_mimetype($forum_image_url);
      $variables['file-type-icon'] = 'document';
  }
  // Use default image for State forum if none uploaded
  if ($term->field_forum_access_states['und'][0]['value'] != '_none' && empty($term->field_state_or_district_image)) {
      $forum_image_url = '/' . drupal_get_path('theme', 'SBAC') . '/images/state-forum-default.png';
      $image_tag = '<img typeof="foaf:Image" src="' . $forum_image_url . '" width="268" height="138" alt="Forum thumbnail image" />';
      $variables['image'] = $image_tag;
      $variables['mime-type'] = file_get_mimetype($forum_image_url);
      $variables['file-type-icon'] = 'document';
  }
  $favorite_link = sbac_favorites_get_favorite_link($user->uid, $id, $fav_type);

  // Forum Goals
  $goals = FALSE;
  if ($term->field_add_to_leaderboard['und'][0]['value'] == 1 && $term->field_forum_access_states['und'][0]['value'] == 0) {
    $educator_goal = 0;
    $educator_complete = 0;
    $reviewer_goal = 0;
    $reviewer_complete = 0;
    $contributor_goal = 0;
    $contributor_complete = 0;
    if ($term->field_educator_goal['und'][0]['value'] > 0) {
      $educator_goal = $term->field_educator_goal['und'][0]['value'];  
    }
    if ($term->field_educator_goal_complete['und'][0]['value'] > 0) {
      $educator_complete = $term->field_educator_goal_complete['und'][0]['value'];
    }
    if ($term->field_reviewer_goal['und'][0]['value'] > 0) {
      $reviewer_goal = $term->field_reviewer_goal['und'][0]['value'];
    }
    if ($term->field_reviewer_goal_complete['und'][0]['value'] > 0) {
      $reviewer_complete = $term->field_reviewer_goal_complete['und'][0]['value'];
    }
    if ($term->field_contributor_goal['und'][0]['value'] > 0) {
      $contributor_goal = $term->field_contributor_goal['und'][0]['value'];
    }
    if ($term->field_contributor_goal_complete['und'][0]['value'] > 0) {
      $contributor_complete = $term->field_contributor_goal_complete['und'][0]['value'];
    }
    $educator_complete_perc = $educator_complete;
    if ($educator_complete >= $educator_goal) {
      $educator_complete_perc = $educator_goal;
    }
    $educator_perc = sbac_goals_calc_percent($educator_complete_perc, $educator_goal);
    $reviewer_complete_perc = $reviewer_complete;
    if ($reviewer_complete >= $reviewer_goal) {
      $reviewer_complete_perc = $reviewer_goal;
    }    
    $reviewer_perc = sbac_goals_calc_percent($reviewer_complete_perc, $reviewer_goal);
    $contributor_complete_perc = $contributor_complete;
    if ($contributor_complete >= $contributor_goal) {
      $contributor_complete_perc = $contributor_goal;
    }
    $contributor_perc = sbac_goals_calc_percent($contributor_complete_perc, $contributor_goal);
    $member_count = count($term->field_fc_forum_members['und']);
    $member_count > 1 ? $member_desc = ' Members' : $member_desc = ' Member';
    $goals = '<a class="goals-toggle">Show Member Goals</a>
              <div class="forum-goal-container">
                <div class="goal-container">
                  <div class="goal-header educator">
                    <span class="goal-title">Educator</span><span class="goal-perc"><strong>' . $educator_perc . '%</strong> Complete</span>
                  </div>
                  <div class="goal-body">
                    <div class="members">
                      <img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/user-default-image.png" width="30px" height="30px" alt="Anonymous\'s picture" title="Anonymous\'s picture">
                      <span class="member-count">' . $member_count . $member_desc . '</span>
                    </div>
                    <div class="goals">
                      <span class="complete educator">' . $educator_complete . '</span> of ' . $educator_goal . '
                    </div>
                  </div>
                </div>
                <div class="goal-container">
                  <div class="goal-header reviewer">
                    <span class="goal-title">Resource Reviewer</span><span class="goal-perc"><strong>' . $reviewer_perc . '%</strong> Complete</span>
                  </div>
                  <div class="goal-body">
                    <div class="members">
                      <img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/user-default-image.png" width="30px" height="30px" alt="Anonymous\'s picture" title="Anonymous\'s picture">
                      <span class="member-count">' . $member_count . $member_desc . '</span>
                    </div>
                    <div class="goals">
                      <span class="complete reviewer">' . $reviewer_complete . '</span> of ' . $reviewer_goal . '
                    </div>
                  </div>
                </div>
                <div class="goal-container last">
                  <div class="goal-header contributor">
                    <span class="goal-title">Resource Contributor</span><span class="goal-perc"><strong>' . $contributor_perc . '%</strong> Complete</span>
                  </div>
                  <div class="goal-body">
                    <div class="members">
                      <img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/user-default-image.png" width="30px" height="30px" alt="Anonymous\'s picture" title="Anonymous\'s picture">
                      <span class="member-count">' . $member_count . $member_desc . '</span>
                    </div>
                    <div class="goals">
                      <span class="complete contributor">' . $contributor_complete . '</span> of ' . $contributor_goal . '
                    </div>
                  </div>
                </div>';
  }
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
    'attributes' => $attributes_text,
    'tabs' => $tab_output,
    'resource_link' => $resource_link,
    'forum_image' => $image_tag,
    'resource_image' => $image_tag,
    'resource_rating' => $resource_rating,
    'resource_rating_count' => $resource_rating_count,
    'resource_views' => $resource_views,
    'resource_downloads' => $resource_downloads,
    'goals' => $goals,
  );

  $output = theme('sbac_forum_render_target_forum', array('fields' => $fields));
  return $output;
}

/**
 * Load more of the view data.
 */
function sbac_forum_load_more_ajax() {
  $page = $_POST['page'];
  module_load_include('inc', 'sbac_forum', 'sbac_forum.pages');
  $output = sbac_forum_main_landing_page($page, TRUE);
  print drupal_json_encode($output);
  exit;
}
