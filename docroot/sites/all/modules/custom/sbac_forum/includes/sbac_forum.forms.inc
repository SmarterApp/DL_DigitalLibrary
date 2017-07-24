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

  $hide_categories_text = t('Filters');
  $hide_categories_class = 'active';

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_RESOURCE);
  }

  $current_filters = NULL;
  // Get correct set of category filters based on subnav.
  switch ($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_RESOURCE:
      if (!empty($_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS];
        $hide_categories_class = '';
      }
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      if (!empty($_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS])) {
        $current_filters = $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS];
        $hide_categories_class = '';
      }
      break;
    case SBAC_FORUM_SUBNAV_KEYWORD:
      break;
  }

  $form['current_filters'] = array(
    '#prefix' => '<div class="category-hide-container"><a class="category-hide ' . $hide_categories_class . '" href="#">' . $hide_categories_text . '</a></div>',
    '#type' => 'hidden',
    '#value' => $current_filters,
    '#attributes' => array('id' => 'sbac-forum-current-filters'),
  );

  $form['original_filters'] = array(
    '#type' => 'hidden',
    '#value' => $current_filters,
    '#attributes' => array('id' => 'sbac-forum-original-filters'),
  );

  $form['search_categories'] = array(
    '#markup' => _sbac_forum_filter_categories(),
  );

  $form['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Apply Filters'),
    '#attributes' => array(
      'id' => 'sbac-forum-filter-button',
      'class' => array('js-hide'),
    ),
    '#prefix' => '<div class="category-buttons">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'wrapper' => '',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  return $form;
}

/**
 * Create the filter categories for the forums
 *
 * @return null|string
 */
function _sbac_forum_filter_categories() {
  $categories = array();
  drupal_add_js(drupal_get_path('module', 'sbac_forum') . '/js/sbac_forum.filter_categories.js');
  libraries_load('jstree');

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_RESOURCE);
  }

  _sbac_search_api_create_taxonomy_filter($categories, 'subject', 'Subjects');
  _sbac_search_api_create_taxonomy_filter($categories, 'grades', 'Grades');
  _sbac_search_api_create_taxonomy_filter($categories, 'attributes', 'Formative Assessment Attributes');
  _sbac_search_api_create_taxonomy_filter($categories, 'title', 'Intended Participants');
  _sbac_search_api_create_taxonomy_filter($categories, 'intended_student_populations', 'Intended Student Populations');

  $cf_value = NULL;
  $cf_html = array();


  $current_filters = NULL;
  // Get correct set of category filters based on subnav.
  switch ($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_RESOURCE:
      if (isset($_SESSION[SBAC_FORUM_RESOURCE_FORUM_CATEGORY_FILTERS])) {
        $cf_value = $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS];
      }
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      if (isset($_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS])) {
        $cf_value = $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS];
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
            if ($vid == 'distinctions') {
              $cf_html[] = '<div class="current-filter" vid="' . $vid . '" tid="' . $tid . '">' . $tid . '</div>';
            }
            else {
              $term = taxonomy_term_load($tid);
              if ($term) {
                $cf_html[] = '<div class="current-filter" vid="' . $vid . '" tid="' . $tid . '">' . $term->name . '</div>';
              }
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
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_TOPIC);
  }

  // Get correct set of category filters based on subnav.
  switch ($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_RESOURCE:
      $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS] = $current_cat_filters;
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS] = $current_cat_filters;
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
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_TOPIC);
  }

  // Get correct set of category filters based on subnav.
  switch ($active_tab) { // Get correct current filter.
    case SBAC_FORUM_SUBNAV_RESOURCE:
      $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS] = '';
      unset($_SESSION['load_more']['forums']['page']);
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      $_SESSION[SBAC_FORUM_TOPIC_FORUM_CATEGORY_FILTERS] = '';
      unset($_SESSION['load_more']['forums']['page']);
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
  $default = '';
  $options = array();

  // Because of ajax, this can change, so hard code it.
  $form['#action'] = url('forums');

  $resource_forums_classes = '';
  $resource_forums_count_text = '';
  $topic_forums_classes = '';
  $topic_forums_count_text = '';
  $active_tab = sbac_forum__api__get_active_subnav();
  switch ($active_tab) {
    case SBAC_FORUM_SUBNAV_KEYWORD:
      // both should be off. Keyword search was performed.
      break;
    case SBAC_FORUM_SUBNAV_RESOURCE:
      $resource_forums_classes = 'is-pressed';
      $default = 'forum-recent-activity';
      if (!empty($_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS])) {
        $default = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS];
      }
      $options = array(
        'forum-recent-activity' => t('Recent Activity'),
        'forum-most-active' => t('Most Active'),
        'forum-newest' => t('Newest'),
        'forum-most-participants' => t('Most Participants'),
      );
      $sort_ajax_callback = 'sbac_forum__ajax__resource_forum_sort_form_change';
      break;
    case SBAC_FORUM_SUBNAV_TOPIC:
      $topic_forums_classes = 'is-pressed';
      $default = 'forum-recent-activity';
      if (!empty($_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS])) {
        $default = $_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS];
      }
      $options = array(
        'forum-recent-activity' => t('Recent Activity'),
        'forum-most-active' => t('Most Active'),
        'forum-newest' => t('Newest'),
        'forum-most-participants' => t('Most Participants'),
      );
      $sort_ajax_callback = 'sbac_forum__ajax__topic_forum_sort_form_change';
      break;
    default:
      $default = 'forum-most-active';
      if (!empty($_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS])) {
        $default = $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS];
      }
      $options = array(
        'forum-recent-activity' => t('Recent Activity'),
        'forum-most-active' => t('Most Active'),
        'forum-newest' => t('Newest'),
        'forum-most-participants' => t('Most Participants'),
      );
      break;
  }

  // Resource Forums tab

  //$form['resource_forums'] = array(
  //  '#prefix' => '<div class="forum-subnav-primary-wrapper">',
  //  '#type' => 'submit',
  //  '#value' => t('Resource Forums') . ' ' . $resource_forums_count_text,
  //  '#title' => t('Resource Forums '),
  //  '#attributes' => array(
  //    'class' => array($resource_forums_classes),
  //  ),
  //  '#submit' => array('_sbac_forum_sub_nav__set_resource__submit'),
  //);

  // Topic Forums tab
  $topic_forums_display = 'block_3';
  if (isset($count_values[$topic_forums_display]) && !empty($count_values[$topic_forums_display])) {
    $topic_forums_count_text = '(' . $count_values[$topic_forums_display] . ')';
  }
  $form['topic_forums'] = array(
    '#type' => 'submit',
    '#value' => t('Topic Forums') . ' ' . $topic_forums_count_text,
    '#title' => t('Topic Forums'),
    '#attributes' => array(
      'class' => array($topic_forums_classes),
    ),
    '#submit' => array('_sbac_forum_sub_nav__set_topic__submit'),
    '#suffix' => '</div>',
  );

  // Ajax submitted. Set Text if selected.
  if (isset($form_state['values']['forum_sort_order'])) {
    $new_value_key = $form_state['values']['forum_sort_order'];
    $old_value_text = $options[$new_value_key];
    $options[$new_value_key] = t('Sort by: ' . $old_value_text);
  }
  else {
    $options[$default] = t('Sort by: ' . $options[$default]);
  }

  // Needs to ajax submit to set the session variable that tracks default state.
  $form['forum_sort_order'] = array(
    '#prefix' => '<div class="forum-subnav-sort-wrapper">',
    '#suffix' => '</div>',
    '#type' => 'select',
    '#title' => t('Sort forum by'),
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => $sort_ajax_callback,
      'event' => 'change',
      'wrapper' => 'form-wrapper-forums-sort-element',
      'progress' => array('type' => 'none'),
    ),
  );

  drupal_add_js(drupal_get_path('module', 'sbac_forum') . '/js/sbac_forum.subnav_form.js');

  $vocab = taxonomy_vocabulary_machine_name_load('forum');
  $access_to_add = _sbac_forum_add_forum_user_access($vocab);
  if ($access_to_add) {
    $new_forum_link_text = '<div class="forum-subnav-start-link-wrapper">';
    $new_forum_link_text .= '<a class="new-forum-link" href="#">Start a Forum</a>';
    $new_forum_link_text .= '</div>';
    $form['forum_start'] = array(
      '#markup' => $new_forum_link_text,
    );
    $form['forum_modal'] = array(
      '#markup' => '<div class="forum-modal">
                      <h2>You are about to create a Forum.</h2>
                      <p>Before continuing, please confirm that you wish to be responsible for moderating this forum.  Click Continue to proceed.</p> 
                      <a id="forum-modal-continue" href="forums/forum/add" class="button right">Continue</a><button class="button right secondary close-reveal-modal" style="margin-right: 20px;">Cancel</button>   
                    </div>',
      '#prefix' => '<div id="forum-modal-container" class="reveal-modal">',
      '#suffix' => '</div>'
    );
  }

  $default = 0;
  if (isset($_GET['only-joined']) && $_GET['only-joined'] == 1) {
    $default = 1;
  }

  $form['forum_only_joined'] = array(
    '#type' => 'checkbox',
    '#title' => t('Joined Groups Only'),
    '#default_value' => $default,
    '#prefix' => '<div class="forum-subnav-joined-wrapper">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'sbac_forum__ajax__joined_only_trigger',
      'event' => 'change',
    ),
  );

  return $form;
}

function _sbac_forum_sub_nav__set_all__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
}

function _sbac_forum_sub_nav__set_own__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_OWN);
}

function _sbac_forum_sub_nav__set_resource__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_RESOURCE);
}

function _sbac_forum_sub_nav__set_topic__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_TOPIC);
}

/**
 * =============================================================================
 *    Forum Keyword search Sub-Nav form
 * =============================================================================
 */

function sbac_forum_keyword_search_sub_nav_form($form, &$form_state) {
  $form = array();

  $all_forums_classes = '';
  $all_forums_count_text = '';
  $my_forums_classes = '';
  $my_forums_count_text = '';

  $count_values = $_SESSION[SBAC_FORUM_FILTER_RESULTS_COUNTER];

  if (isset($count_values['block']) && !empty($count_values['block'])) {
    $all_forums_count_text = '(' . $count_values['block'] . ')';
  }
  $form['all_forums'] = array(
    '#prefix' => '<div class="forum-kw-search-subnav-primary-wrapper">',
    '#type' => 'submit',
    '#value' => t('All Forums') . ' ' . $all_forums_count_text,
    '#attributes' => array(
      'class' => array($all_forums_classes),
    ),
    '#submit' => array('_sbac_forum_kw_search_sub_nav__set_all__submit'),
  );

  if (isset($count_values['block_1']) && !empty($count_values['block_1'])) {
    $my_forums_count_text = '(' . $count_values['block_1'] . ')';
  }
  $form['my_forum'] = array(
    '#type' => 'submit',
    '#value' => t('My Forums') . ' ' . $my_forums_count_text,
    '#title' => t('My forums'),
    '#attributes' => array(
      'class' => array($my_forums_classes),
    ),
    '#submit' => array('_sbac_forum_kw_search_sub_nav__set_own__submit'),
    '#suffix' => '</div>',
  );

  return $form;
}

function _sbac_forum_kw_search_sub_nav__set_all__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  $form_state['redirect'] = 'forums';
}

function _sbac_forum_kw_search_sub_nav__set_own__submit($form, &$form_state) {
  sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_OWN);
  $form_state['redirect'] = 'forums';
}

/**
 * =============================================================================
 *    Forum Delete Form Button
 * =============================================================================
 */

function sbac_forum_delete_forum_confirm($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>' . t('
    If you continue, the forum and all its content will be permanently deleted. Members will receive a notification that the forum is no longer available.') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Forum',
    '#attributes' => array('class' => array('edit-delete-overlay', 'red'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('edit-cancel-delete-overlay', 'gray', 'cancel'))
  );

  return $form;
}


/**
 * =============================================================================
 *    Forum Join Button Form
 * =============================================================================
 */

function sbac_forum_join_button_form($form, &$form_state, $forum_id = FALSE, $user_id = FALSE) {
  $form = array();

  if (isset($form_state['ajax']) && $form_state['ajax']) {
    $forum_id = $form_state['forum_to_join'];
    $user_id = $form_state['uid'];

    $form['submit_description'] = array(
      '#markup' => '<h2>' . t('Are you sure you want to join this forum?') . '</h2><p> </p>',
    );
  }

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
    '#attributes' => array('class' => array('disabler')),
    '#prefix' => '<div id="join-forum-button-wrapper">',
    '#suffix' => '</div>',
    '#executes_submit_callback' => TRUE,
    '#ajax' => array(
      'effect' => 'fade',
      'wrapper' => 'join-forum-button-wrapper',
      'callback' => 'sbac_forum__ajax__join_button_form_execute',
    ),
  );

  if (isset($form_state['ajax']) && $form_state['ajax']) {
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => 'Cancel',
      '#attributes' => array('class' => array('edit-cancel-leave-overlay', 'gray', 'cancel'))
    );
  }

  return $form;
}


/**
 * =============================================================================
 *    Forum Leave Button Form
 * =============================================================================
 */

function sbac_forum_leave_forum_confirm($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<h2>' . t('You are about to leave this forum') . '</h2><p>' . t('
    If you leave this forum you will no longer be able to post topics or participate in group discussions.') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Leave Forum',
    '#attributes' => array('class' => array('edit-leave-overlay', 'blue'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('edit-cancel-leave-overlay', 'gray', 'cancel'))
  );

  return $form;
}


/**
 * =============================================================================
 *    Forum Remove Member Form
 * =============================================================================
 */

function sbac_forum_remove_member_confirm($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<h2>' . t('You are about to remove this user') . '</h2><p>' . t('
    If you continue this user will no longer be able to participate in the forum. Please provide rationale as to why they have been removed. This will be sent to the user via notification.') . '</p>',
  );

  $form['notification_message'] = array(
    '#type' => 'textarea',
    '#title' => t(''),
    '#default_value' => '',
    '#rows' => 10,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Remove User',
    '#attributes' => array('class' => array('edit-remove-overlay', 'red'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('edit-cancel-remove-overlay', 'gray', 'cancel'))
  );

  return $form;
}


/**
 * =============================================================================
 *    Forum Restore Member Form
 * =============================================================================
 */

function sbac_forum_restore_member_confirm($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<h2>' . t('You are about to re-add this user') . '</h2><p>' . t('
    If you continue, this user will recieve a notification indicating that they may once again participate in this forum') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Re-add User',
    '#attributes' => array('class' => array('edit-restore-overlay', 'blue'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('edit-cancel-restore-overlay', 'gray', 'cancel'))
  );

  return $form;
}

/**
 * =============================================================================
 *    Topic Delete Form Button
 * =============================================================================
 */

function sbac_forum_delete_topic_confirm($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>' . t('
    If you continue, all discusson information (including discussion details and any replies) will be permanently deleted and a notification will be sent to the originating user.') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Discussion',
    '#attributes' => array('class' => array('edit-delete-topic-overlay', 'red'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('edit-cancel-delete-topic-overlay', 'gray', 'cancel'))
  );

  return $form;
}

/**
 * =============================================================================
 *    Comment Delete Form Button
 * =============================================================================
 */

function sbac_forum_delete_comment_confirm($form, &$form_state, $target_comment_to_delete = NULL) {
  $form = array();

  $form['target_comment_to_delete'] = array(
    '#type' => 'value',
    '#value' => $target_comment_to_delete,
  );

  $form['submit_description'] = array(
    '#markup' => '<h2>' . t('You are about to delete this discussion reply') . '</h2><p>' . t('
    If you continue, this reply along with all related replies will be permanently deleted and a notification will be sent to the originating user.') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Reply',
    '#attributes' => array('class' => array('edit-delete-reply-overlay', 'red'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('edit-cancel-delete-reply-overlay', 'gray', 'cancel'))
  );

  return $form;
}

function sbac_forum_delete_comment_confirm_submit($form, &$form_state) {
  global $user;

  if (!isset($form_state['ajax'])) { // If not ajax, the value is stored within formstate values like normal submit.
    $comment_id_to_remove = $form_state['values']['target_comment_to_delete'];
  }
  else {
    $comment_id_to_remove = $form_state['target_comment_to_delete'];
  }

  $comment_entity = comment_load($comment_id_to_remove);

  if ($form_state['triggering_element']['#value'] != 'Cancel') {
    // Params for task.
    $from_user_id = $user->uid; // TriggeringUser
    $for_user_id = $comment_entity->uid; // OwningUser

    if ($from_user_id != $for_user_id) { // no need to notify if youre deleting your own comment
      // Create task notification.
      if ($task = taskit_get_object('deleted_forum_comment')) {
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('comment', $comment_id_to_remove);
        $task->addEntity('node', $comment_entity->nid);
        $task->addOwningUser($for_user_id);
        $task->addTriggeringUser($from_user_id);
        $task->save();
      }
    }

    // Delete comment
    comment_delete($comment_id_to_remove);
    $message = 'Forum Reply has been deleted successfully';
    drupal_set_message($message);
  }

  // If ajax was short-circuited, have to manually redirect.
  if (!isset($form_state['ajax'])) {
    $redirect_to = 'node/' . $comment_entity->nid;
    $form_state['redirect'] = $redirect_to;
  }
}

/**
 * =============================================================================
 *    Comment Sort Form
 * =============================================================================
 */
function sbac_forum_comment_sort_form($form, &$form_state) {
  $form = array();
  $default = 'comment-most-recent-activity';
  // If session var is set, make it the default.
  if (isset($_SESSION[SBAC_FORUM_TOPIC_COMMENT_SORTS]) &&
    $_SESSION[SBAC_FORUM_TOPIC_COMMENT_SORTS] != ''
  ) {
    $default = $_SESSION[SBAC_FORUM_TOPIC_COMMENT_SORTS];
  }
  $options = array(
    'comment-most-recent-activity' => t('Most Recent Activty'),
    'comment-most-recommended' => t('Most Recommended'),
    'comment-oldest' => t('Oldest'),
  );
  // Ajax submitted. Set Text if selected.
  if (isset($form_state['values']['comment_sort_order'])) {
    $new_value_key = $form_state['values']['comment_sort_order'];
    $old_value_text = $options[$new_value_key];
    $options[$new_value_key] = t('Sort by: ' . $old_value_text);
  }
  else {
    $options[$default] = t('Sort by: ' . $options[$default]);
  }

  // Needs to ajax submit to set the session variable that tracks default state.
  $form['comment_sort_order'] = array(
    '#type' => 'select',
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => 'sbac_forum__ajax__topic_comment_sort_form_change',
      'event' => 'change',
      'progress' => array('type' => 'none'),
    ),
    '#attributes' => array(
      'class' => array(
        'no-chosen'
      )
    )
  );
  return $form;
}
