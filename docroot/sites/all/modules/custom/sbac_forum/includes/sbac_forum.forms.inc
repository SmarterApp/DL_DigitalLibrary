<?php


/**
 * =============================================================================
 *    Forum Category Filter form
 * =============================================================================
 */


/**
 * Form for submitting the forum category filters.
 *
 * @return array
 */
function sbac_forum_category_forum_form($form, &$form_state) {
  $form = array();

  $hide_categories_text = t('Hide Categories');
  $hide_categories_class = 'active';
  $should_hide_categories = '';

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  }

  $current_filters = NULL;
  // Get correct set of category filters based on subnav.
  switch($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_ALL:
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_COOKIE[SBAC_FORUM_FILTERS_CLOSED]) && $_COOKIE[SBAC_FORUM_FILTERS_CLOSED]) {
        $should_hide_categories = ' style="display:none;"';
      }
      break;
    case SBAC_FORUM_SUBNAV_OWN:
      if (isset($_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS];
      }
      if (isset($_COOKIE[SBAC_FORUM_MY_FORUM_FILTERS_CLOSED]) && $_COOKIE[SBAC_FORUM_MY_FORUM_FILTERS_CLOSED]) {
        $should_hide_categories = ' style="display:none;"';
      }
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }

  if ($should_hide_categories) {
    $hide_categories_text = t('Show Categories');
    $hide_categories_class = '';
  }

  $form['current_filters'] = array(
    '#prefix' => '<a class="category-hide js-hide '. $hide_categories_class .'" href="#">' . $hide_categories_text . '</a>',
    '#type' => 'hidden',
    '#value' => $current_filters,
    '#attributes' => array('id' => 'sbac-forum-current-filters'),
  );

  $form['search_categories'] = array(
    '#markup' => _sbac_forum_filter_categories(),
  );

  $form['filter'] = array(
    '#type' => 'submit',
    '#value' => ($current_filters != NULL) ? t('Edit Filters') : t('Apply Filters'),
    '#attributes' => array(
      'id' => 'sbac-forum-filter-button',
      'class' => array(
        ($current_filters != NULL) ? 'is-edit': 'is-apply',
        ($current_filters == NULL) ? 'js-hide': ''
      ),
    ),
    '#prefix' => '<div class="category-buttons slideable" '. $should_hide_categories .'>',
    '#ajax' => array(
      'wrapper' => '',
      'method' => 'replace',
      'effect' => 'fade'
    ),
    '#attached' => array(
      'js' => array(
        array(
          'data' => array('sbac_forum' => array('isEdit' => ($current_filters != NULL ? 1 : 0))),
          'type' => 'setting',
        ),
      ),
    ),
  );

  $form['reset_filters'] = array(
    '#type' => 'submit',
    '#value' => t('Reset Filters'),
    '#attributes' => array(
      'class' => array('js-hide'),
    ),
    '#suffix' => '</div>',
    '#submit' => array('sbac_forum_category_forum_form_reset_submit'),
  );

  return $form;
}


function _sbac_forum_filter_categories() {
  $categories = array();
  drupal_add_js(drupal_get_path('module', 'sbac_forum') . '/js/sbac_forum.filter_categories.js');

  $subject = taxonomy_vocabulary_machine_name_load('subject');
  $categories['subject']['display_name'] = 'Subjects';
  $categories['subject']['vocabulary'] = $subject;
  $categories['subject']['terms'] = taxonomy_get_tree($subject->vid);

  $grades = taxonomy_vocabulary_machine_name_load('grades');
  $categories['grades']['display_name'] = 'Grades';
  $categories['grades']['vocabulary'] = $grades;
  $categories['grades']['terms'] = taxonomy_get_tree($grades->vid);

  $intended_student_populations = taxonomy_vocabulary_machine_name_load('intended_student_populations');
  $categories['intended_student_populations']['display_name'] = 'Intended Student Populations';
  $categories['intended_student_populations']['vocabulary'] = $intended_student_populations;
  $categories['intended_student_populations']['terms'] = taxonomy_get_tree($intended_student_populations->vid);

  $intended_end_user = taxonomy_vocabulary_machine_name_load('intended_end_user');
  $categories['intended_end_user']['display_name'] = 'Intended End Users';
  $categories['intended_end_user']['vocabulary'] = $intended_end_user;
  $categories['intended_end_user']['terms'] = taxonomy_get_tree($intended_end_user->vid);

  $cf_value = NULL;
  $cf_html = array();

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  }

  $current_filters = NULL;
  // Get correct set of category filters based on subnav.
  switch($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_ALL:
      if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
        $cf_value = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
      }
      break;
    case SBAC_FORUM_SUBNAV_OWN:
      if (isset($_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS])) {
        $cf_value = $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS];
      }
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }

  if ($cf_value) {
    $filters = explode('::', $cf_value);
    if ($filters) {
      foreach ($filters as $filter) {
        $filter_info = explode(':', $filter);
        if ($filter_info && sizeof($filter_info) == 2) {
          $vid = $filter_info[0];
          $tid = $filter_info[1];
          if ($vid && $tid) {
            $term = taxonomy_term_load($tid);
            if ($term) {
              $cf_html[] = '<div class="current-filter"><span vid="' . $vid . '" tid="' . $tid . '" class="filter-name">' . $term->name . '</span></div>';
            }
          }
        }
      }
    }
  }

  $output = NULL;
  if ($categories) {
    $output = theme('sbac_forum_filter_categories', array('categories' => $categories, 'cf_value' => $cf_value, 'cf_html' => $cf_html));
  }
  return $output;
}

/**
 * Submit handler for categories.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum_category_forum_form_submit($form, &$form_state) {
  $current_cat_filters = $form_state['input']['current_filters'];

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  }

  // Get correct set of category filters based on subnav.
  switch($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_ALL:
      $_SESSION[SBAC_FORUM_CATEGORY_FILTERS] = $current_cat_filters;
      break;
    case SBAC_FORUM_SUBNAV_OWN:
      $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS] = $current_cat_filters;
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }
}

/**
 * Submit handler for category reset.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum_category_forum_form_reset_submit($form, &$form_state) {
  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  }

  // Get correct set of category filters based on subnav.
  switch($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_ALL:
      $_SESSION[SBAC_FORUM_CATEGORY_FILTERS] = '';
      break;
    case SBAC_FORUM_SUBNAV_OWN:
      $_SESSION[SBAC_FORUM_MY_FORUM_CATEGORY_FILTERS] = '';
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }
  $form_state['redirect'] = 'forums';
}


/**
 * =============================================================================
 *    Forum Sub-Nav form
 * =============================================================================
 */

function sbac_forum_sub_nav_form($form, &$form_state, $count_values = array()) {
  $form = array();

  $all_forums_classes = '';
  $all_forums_count_text = '';
  $my_forums_classes = '';
  $my_forums_count_text = '';
  $active_tab = sbac_forum__api__get_active_subnav();
  switch($active_tab) {
    case SBAC_FORUM_SUBNAV_ALL:
      $all_forums_classes = 'is-pressed';
      break;
    case SBAC_FORUM_SUBNAV_OWN:
      $my_forums_classes = 'is-pressed';
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      // both should be off. Keyword search was performed.
      break;
    default:
      // set all forums if it ends up empty.
      $all_forums_classes = 'is-pressed';
      break;
  }

  if (isset($count_values['block']) && !empty($count_values['block'])) {
    $all_forums_count_text = '('.$count_values['block'].')';
  }
  $form['all_forums'] = array(
    '#prefix'       => '<div class="forum-subnav-primary-wrapper">',
    '#type'         => 'submit',
    '#value'        => t('All Forums'). ' ' . $all_forums_count_text,
    '#attributes'   => array(
      'class'   => array($all_forums_classes),
    ),
    '#submit' => array('_sbac_forum_sub_nav__set_all__submit'),
  );

  if (isset($count_values['block_1']) && !empty($count_values['block_1'])) {
    $my_forums_count_text = '('.$count_values['block_1'].')';
  }
  $form['my_forum'] = array(
    '#type'         => 'submit',
    '#value'        => t('My Forums'). ' '. $my_forums_count_text,
    '#attributes'   => array(
      'class' => array($my_forums_classes),
    ),
    '#submit' => array('_sbac_forum_sub_nav__set_own__submit'),
    '#suffix'       => '</div>',
  );

  $default = 'forum-most-active';
  // // If session var is set, make it the default.
  // if (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS]) &&
  //     $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS] != '') {
  //   $default = $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS];
  // }

  $options = array(
    'forum-most-active'   => t('Most Active'),
    'forum-newest'        => t('Newest'),
    'forum-most-members'  => t('Most Members'),
  );

  // Ajax submitted. Set Text if selected.
  if (isset($form_state['values']['forum_sort_order'])) {
    $new_value_key = $form_state['values']['forum_sort_order'];
    $old_value_text = $options[$new_value_key];
    $options[$new_value_key] = t('Sort by: ' . $old_value_text);
  } else {
    $options[$default] = t('Sort by: ' . $options[$default]);
  }


  // Needs to ajax submit to set the session variable that tracks default state.
  $form['forum_sort_order'] = array(
    '#prefix'         => '<div class="forum-subnav-sort-wrapper">',
    '#suffix'         => '</div>',
    '#type'           => 'select',
    '#title'          => t(''),
    '#required'       => FALSE,
    '#options'        => $options,
    '#default_value'  => $default,
    // '#ajax'           => array(
    //   'callback'  => '_sbac_resource_digital_library_sort_form__ajax__change',
    //   'event'     => 'change',
    //   'wrapper'   => 'form-wrapper-dl-sort-element',
    //   'progress'  => array('type' => 'none'),
    // )
  );


  $form['forum_keyword'] = array(
    '#prefix'         => '<div class="forum-subnav-keyword-wrapper">',
    '#suffix'         => '</div>',
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#default_value'  => 'Search Forums',
    '#size'           => 30,
  );

  $vocab = taxonomy_vocabulary_machine_name_load('forum');
  $access_to_add = _sbac_forum_add_forum_user_access($vocab);
  if ($access_to_add) {
    $link_options = array(
      'attributes' => array(
        'class'=> 'new-forum-link',
      ),
    );
    $new_forum_link_text = '<div class="forum-subnav-start-link-wrapper">';
    $new_forum_link_text .= l('Start a Forum', 'forums/forum/add', $link_options);
    $new_forum_link_text .= '</div>';
    $form['forum_start'] = array(
      '#markup' => $new_forum_link_text,
    );
  }


  return $form;
}

function _sbac_forum_sub_nav__set_all__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
}

function _sbac_forum_sub_nav__set_own__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_OWN);
}


/**
 * =============================================================================
 *    Forum Join Button Form
 * =============================================================================
 */

function sbac_forum_join_button_form($form, &$form_state, $forum_id, $user_id) {
  $form = array();

  // Store these values for the ajax handler.
  $form['forum_id'] = array(
    '#type' => 'value',
    '#value' => $forum_id,
  );
  $form['target_user_id'] = array(
    '#type' => 'value',
    '#value' => $user_id,
  );

  $form['join_forum'] = array(
    '#type' => 'submit',
    '#value' => t('Join Forum'),
    '#prefix' => '<div id="join-forum-button-wrapper">',
    '#suffix' => '</div>',
    '#executes_submit_callback' => TRUE,
    '#ajax' => array(
      'effect' => 'fade',
      'wrapper' => 'join-forum-button-wrapper',
      'callback' => 'sbac_forum__ajax__join_button_form_execute',
    ),
  );
  return $form;
}

