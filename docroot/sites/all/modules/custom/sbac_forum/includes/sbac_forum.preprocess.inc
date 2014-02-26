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
  $current_user = $vars['user'];
  $row_data = $vars['row'];

  $facilitator_text = '';
  $member_text = '';

  $faci_field = $row_data->_field_data['tid']['entity']->field_forum_facilitators[LANGUAGE_NONE];
  $is_faci = FALSE;

  if (!empty($faci_field)) {
    foreach ($faci_field as $index => $values) {
      $faci_user_id = $values['target_id'];
      if ($current_user->uid == $faci_user_id) {
        $is_faci = TRUE;
      }
    }
    $facilitator_text = '<div class="sbac-forum-faci-status-label">';
    if (!$is_faci) { // Current user is not set as facilitator
      $first_item = array_shift($faci_field);
      $first_faci_user_id = $first_item['target_id'];
      $target_faci = user_load($first_faci_user_id);
      $faci_data = entity_metadata_wrapper('user', $target_faci);
      $fn = $faci_data->field_first_name->value();
      $ln = $faci_data->field_last_name->value();
      $full_name = $fn . ' ' . $ln;
      $link = 'forum-auth-pane/'. $faci->uid;
      $link_ops = array('attributes' => array('class' => 'forum-list-auth-pane-item'));
      $faci_link = l($full_name, $link, $link_ops);
      $facilitator_text .= 'Facilitator: '. $faci_link;
    } else{
      $facilitator_text .= 'You are the <span class="sbac-forum-is-faci-highlight">Facilitator</span>';
    }
    $facilitator_text .= '</div>';
  }

  if (!$is_faci) {
    $forum_tid = $row_data->tid;
    $is_member = sbac_forum__api__check_user_is_forum_member($forum_tid, $current_user->uid);
    if ($is_member === TRUE) {
      $member_text = '<div class="sbac-forum-membership-status-label">You are a <span class="sbac-forum-is-member-highlight">member</span></div>';
    }
  }

  $vars['fields']['nothing']->content = $member_text . $facilitator_text ;
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
