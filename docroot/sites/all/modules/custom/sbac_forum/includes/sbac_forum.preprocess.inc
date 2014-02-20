<?php


/**
 * ---------- Forum list View.---------------
 */

/**
 * views_view preprocess
 */
function sbac_forum_preprocess_views_view__forum_list__block(&$vars) {

}

/**
 * views_view_unformatted preprocess
 */
function sbac_forum_preprocess_views_view_unformatted__forum_list__block(&$vars) {

}

/**
 * views_view_fields preprocess
 */
function sbac_forum_preprocess_views_view_fields__forum_list__block(&$vars) {

}


/**
 * ---------- Topic list View.---------------
 */

/**
 * views_view preprocess
 */
function sbac_forum_preprocess_views_view__forum_topic_list__block(&$vars) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');

  global $user;
  $join_button = '';

  $forum_id = array_shift($vars['view']->args);
  $is_member = sbac_forum__api__check_user_is_forum_member($forum_id, $user->uid);

  if ($is_member === TRUE) {
    $join_button = sbac_forum__api__create_start_new_topic_link();
  } elseif ($is_member === FALSE) {
    $join_form = drupal_get_form('sbac_forum_join_button_form', $forum_id, $user->uid);
    $join_button = drupal_render($join_form);
  } elseif ($is_member === 'removed') {
    // There is nothing for removed members.
  }

  $vars['join_button'] = $join_button;
}

/**
 * views_view_unformatted preprocess
 */
function sbac_forum_preprocess_views_view_unformatted__forum_topic_list__block(&$vars) {

}

/**
 * views_view_fields preprocess
 */
function sbac_forum_preprocess_views_view_fields__forum_topic_list__block(&$vars) {

}


/**
 * ---------- Member list View.---------------
 */

/**
 * views_view preprocess
 */
function sbac_forum_preprocess_views_view__member_topic_list(&$vars) {

}

/**
 * views_view_unformatted preprocess
 */
function sbac_forum_preprocess_views_view_unformatted__member_topic_list(&$vars) {

}

/**
 * views_view_fields preprocess
 */
function sbac_forum_preprocess_views_view_fields__member_topic_list(&$vars) {

}
