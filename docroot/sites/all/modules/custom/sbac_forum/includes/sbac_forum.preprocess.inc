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
function sbac_forum_preprocess_views_view__forum_member_list(&$vars) {
  drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.member_list.js");
}

/**
 * views_view_unformatted preprocess
 */
function sbac_forum_preprocess_views_view_unformatted__forum_member_list(&$vars) {

}

/**
 * views_view_fields preprocess
 */
function sbac_forum_preprocess_views_view_fields__forum_member_list(&$vars) {
  $current_user = $vars['user'];
  $output = '';
  if ($vars['view']->current_display == 'block') { // Only add member controls for member list. Not removed members list.
    if (in_array('facilitator', $current_user->roles)) { // Only show controls for facilitator users.
      $row_uid = $vars['row']->users_field_data_field_fc_forum_member_uid;
      if ($row_uid != $current_user->uid) {
        $args = $vars['view']->args;
        $term_id = array_shift($args);
        $link_ops = array(
          'attributes' => array(
            'class' => 'members-control-link',
          ),
        );

        $link_text = t('Remove Member');
        $link_url = 'forums/term/' . $term_id . '/members-edit/' . $row_uid . '/remove';
        $link = l($link_text, $link_url, $link_ops);
        $output = $link;
      }
    }
  }

  $vars['sbac_forum_indv_member_controls'] = $output;
}
