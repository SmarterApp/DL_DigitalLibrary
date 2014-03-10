<?php


function sbac_forum_preprocess_node__topic(&$vars) {
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  drupal_add_js('/misc/form.js');
  drupal_add_js('/misc/collapse.js');

  global $user;
  $node_data = entity_metadata_wrapper('node', $vars['node']);
  $forum_term = $node_data->field_topic_forum_parent->value();

  // Declare variables.
  $forum_name_text = '';
  $control_data = array();
  $back_link = '';
  $delete_link = '';
  $edit_link = '';
  $author_image_markup = '';
  $author_info = '';
  $posted = '';
  $has_materials = FALSE;

  $welcome_message = '';
  if (isset($_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE]) ) {
    $welcome_message = $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE];
    $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE] = '';
  }

  $is_faci = FALSE;
  if (in_array('facilitator', $user->roles)) {
    $is_faci = TRUE;
  }

  $is_member = FALSE;
  if (!empty($forum_term)) {
    $forum_name_text = $forum_term->name;
    $is_member = sbac_forum__api__check_user_is_forum_member($forum_term->tid, $user->uid);
    if ($is_member === TRUE) {
      $control_data = sbac_forum__api__create_forum_controls($is_member, $is_faci, $forum_term->tid);
      drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.topic_view.js");
    }

    $link_ops = array(
      'attributes' => array(
        'class' => 'topic-node-back-link',
      ),
    );
    $link_url = 'forums/term/' . $forum_term->tid;
    $back_link = '<span class="tertiary-back-link-img"></span>' . l('All Topics', $link_url, $link_ops);
  }

  // Access Check this.
	$can_edit = node_access('update', $vars['node']);
  if ($can_edit) {
    $edit_link = '<span class="tertiary-edit-link">' . l('Edit Topic', $node_data->edit_url->value()). '</span>';
  }

  $can_delete = node_access('delete', $vars['node']);
  if ($can_delete) {
    $link_ops = array(
      'attributes' => array(
        'class' => 'ctools-use-modal vp-control-link ctools-modal-sbac-forum-delete-topic-link',
        'id'    => 'sbac-forum-delete-topic-link'
      ),
    );
    $delete_link = 'sbac-forum/nojs/topic-delete/'.$forum_term->tid .'/' . $node_data->nid->value();
    $delete_link = '<span class="tertiary-delete-link">' . l('Delete Topic', $delete_link, $link_ops) . '</span>';
    $js_settings = array(
      'sbac-forum-delete-topic-link' => array( // Link has to have ctools-modal- namespace class along with this id.
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 560,
          'height' => 260,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting'); // Styles the modal.
  }

  // Author Pane Info.
  $topic_author = $node_data->author->value();
  $author_image_markup = sbac_forum__api__get_author_picture($topic_author, 'forum_profile_image_120x120');
  $author_info = sbac_forum__api__get_authpane_hoverover($topic_author->uid);
  $posted = date('M jS, Y', $node_data->created->value());

  $has_files = FALSE;
  if (isset($node_data->field_topic_files)) {
    $topic_files = $node_data->field_topic_files->value();
    if (!empty($topic_files)) {
      $has_files = TRUE;
    }
  }
  $has_links = FALSE;
  if (isset($node_data->field_topic_links)) {
    $topic_links = $node_data->field_topic_links->value();
    if (!empty($topic_links)) {
      $has_links = TRUE;
    }
  }
  if ($has_links || $has_files) {
    $has_materials = TRUE;
  }

  // action section.
  $action_section = '';
  if ($is_member === TRUE) {
    $action_link_ops = array(
      'attributes' => array(
        'class' => 'button blue sbac-forum-topic-node-direct-comment-link',
      ),
    );
    $new_comment_url = 'sbac-forum/custom/comment-reply/'. $node_data->nid->value() . '/0';
    $action_section = l('Post a Reply', $new_comment_url, $action_link_ops);

  } elseif($is_member === FALSE) { // User not a member.
    module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
    $join_form = drupal_get_form('sbac_forum_join_button_form', $forum_term->tid, $user->uid);
    $join_button = drupal_render($join_form);
    $action_section = $join_button;
  }
  $vars['action_section'] = $action_section;


  // Put everything into arrays and register in vars for tpl. ------------

  $parent_forum_markup = array(
    'welcome_message'  => $welcome_message,
    'forum_name'       => $forum_name_text,
    'controls'         => $control_data, // Has key "markup" and "classes"
  );
  $vars['parent_forum_markup'] = $parent_forum_markup;

  $tertiary_nav = array(
    'back'             => $back_link,
    'delete'           => $delete_link,
    'edit'             => $edit_link,
  );
  $vars['tertiary_nav'] = $tertiary_nav;

  $main_content = array(
    'author_image'      => $author_image_markup,
    'author_name_popup' => $author_info,
    'posted'            => $posted,
    'has_materials'     => $has_materials,
  );
  $vars['main_content'] = $main_content;
}


function sbac_forum_preprocess_sbac_forum_comment__node_topic(&$vars) {
  $comment_entity = $vars['comment'];
  $comment_data = entity_metadata_wrapper('comment', $comment_entity);

  $comment_auth_uid = $comment_entity->uid;
  $user_image = sbac_forum__api__get_author_picture($comment_auth_uid, 'forum_profile_image_60x60');
  $user_name_w_hoverover = sbac_forum__api__get_authpane_hoverover($comment_auth_uid);

  $posted_date = date('M jS, Y g:ia' , $comment_entity->created);

  $depth_extra = '';
  $depth = $comment_entity->depth;
  if ($depth > 5) { // If nesting is passed 5 levels deep, get parent info
    $parent_comment = $comment_data->parent->value();
    if (!empty($parent_comment)) { // Extra check.
      $parent_uid = $parent_comment->uid;
      $parent_name = sbac_forum__api__get_authpane_hoverover($parent_uid);
      $depth_extra = ', replying to ' . $parent_name;
    }
  }

  $has_materials = FALSE;
  $has_files = FALSE;
  if (isset($comment_data->field_topic_comment_files)) {
    $topic_files = $comment_data->field_topic_comment_files->value();
    if (!empty($topic_files)) {
      $has_files = TRUE;
    }
  }
  $has_links = FALSE;
  if (isset($comment_data->field_topic_comment_links)) {
    $topic_links = $comment_data->field_topic_comment_links->value();
    if (!empty($topic_links)) {
      $has_links = TRUE;
    }
  }
  if ($has_links || $has_files) {
    $has_materials = TRUE;
  }

  $vars['picture'] = $user_image;
  $vars['auth_name_hover'] = $user_name_w_hoverover;
  $vars['depth_extra'] = $depth_extra;
  $vars['posted_date'] = $posted_date;
  $vars['has_materials'] = $has_materials;

  global $user;
  $is_member = FALSE;
  $topic_node = $vars['node'];
  $parent_forum = $topic_node->field_topic_forum_parent[LANGUAGE_NONE][0]['tid'];
  if (!empty($parent_forum)) {
    $is_member = sbac_forum__api__check_user_is_forum_member($parent_forum, $user->uid);
  }
  $vars['is_member'] = $is_member;

  if ($is_member === TRUE) {
    if (isset($vars['content']['links']['comment']['#links']['comment-delete'])) {
      $vars['content']['links']['comment']['#links']['comment-delete']['title'] = 'Delete';
      $new_url = 'sbac-forum/nojs/custom/comment-delete/' . $comment_entity->cid;
      $vars['content']['links']['comment']['#links']['comment-delete']['href'] = $new_url;
      $del_link_class = 'sbac-forum-del-comment-link-'.$comment_entity->cid;
      $link_ops = array(
        'class' => 'ctools-use-modal ctools-modal-' . $del_link_class,
        'id'    => $del_link_class,
      );
      $vars['content']['links']['comment']['#links']['comment-delete']['attributes'] = $link_ops;
      // Modal requirements.
      $js_settings = array(
        $del_link_class => array( // Link has to have ctools-modal- namespace class along with this id.
          'modalSize' => array(
            'type' => 'fixed',
            'width' => 560,
            'height' => 230,
          ),
        ),
      );
      drupal_add_js($js_settings, 'setting'); // Styles the modal.
      ctools_include('ajax');
      ctools_include('modal');
      ctools_add_js('ajax-responder');
      ctools_modal_add_js();
    }
    if (isset($vars['content']['links']['comment']['#links']['comment-edit'])) {
      $vars['content']['links']['comment']['#links']['comment-edit']['title'] = 'Edit';
    }
    if (isset($vars['content']['links']['comment']['#links']['comment-reply'])) {
      $vars['content']['links']['comment']['#links']['comment-reply']['title'] = 'Reply';
      $new_url = 'sbac-forum/custom/comment-reply/'. $comment_entity->nid . '/' . $comment_entity->cid;
      $vars['content']['links']['comment']['#links']['comment-reply']['href'] = $new_url;
    }
  }
}
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
      if (!empty($faci_field)) {
        $first_item = array_shift($faci_field);
        $first_faci_user_id = $first_item['target_id'];
        $faci_link = sbac_forum__api__get_authpane_hoverover($first_faci_user_id);
        $facilitator_text .= 'Facilitator: '. $faci_link;
      } else { // No facilitator set
        $facilitator_text .= 'Facilitator: None';
      }
    } else{
      $facilitator_text .= '<span class="facilitator">You are the <span class="sbac-forum-is-faci-highlight">Facilitator</span></span>';
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
 * ---------- Forum list EMPTY View.---------------
 */

/**
 * views_view preprocess
 */
function sbac_forum_preprocess_views_view__forum_list_empty__block(&$vars) {

}

/**
 * views_view_unformatted preprocess
 */
function sbac_forum_preprocess_views_view_unformatted__forum_list_empty__block(&$vars) {

}

/**
 * views_view_fields preprocess
 */
function sbac_forum_preprocess_views_view_fields__forum_list_empty__block(&$vars) {
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
      $link = 'forum-auth-pane/'. $first_faci_user_id;
      $link_ops = array('attributes' => array('class' => 'forum-list-auth-pane-item'));
      $faci_link = l($full_name, $link, $link_ops);
      $facilitator_text .= 'Facilitator: '. $faci_link;
    } else{
      $facilitator_text .= '<span class="facilitator">You are the <span class="sbac-forum-is-faci-highlight">Facilitator</span></span>';
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
    $join_button = sbac_forum__api__create_start_new_topic_link($forum_id);
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
 * views_view_field preprocess
 */
function sbac_forum_preprocess_views_view_field__forum_topic_list__block__uid(&$vars) {
  $user_uid = $vars['output'];
  $new_output = '';
  if (!empty($user_uid)) {
    $author_name = sbac_forum__api__get_authpane_hoverover($user_uid);
    $new_output = 'Started by: ' . $author_name . ' <span class="topic-listing-field-divider"></span> ';
  }

  $vars['output'] = $new_output;
}

/**
 * views_view_field preprocess
 */
function sbac_forum_preprocess_views_view_field__forum_topic_list__block__last_comment_uid(&$vars) {
  $user_uid = $vars['output'];
  $new_output = '';
  if (!empty($user_uid)) {
    $author_name = sbac_forum__api__get_authpane_hoverover($user_uid);
    $new_output = '' . $author_name . ' <span class="topic-listing-field-divider2"></span> ';
  }

  $vars['output'] = $new_output;
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
  $output = '';
  $current_user = $vars['user'];
  $row_uid = $vars['row']->users_field_data_field_fc_forum_member_uid;
  if ((in_array('facilitator', $current_user->roles) ) &&
      ($row_uid != $current_user->uid) ) { // Only show controls for facilitator users.

      $args = $vars['view']->args;
      $term_id = array_shift($args);
      $link_dom_id = '';
      $link_text = '';
      $link_url = '';

      if ($vars['view']->current_display == 'block') { // Only add member controls for member list.
        $link_dom_id = 'forum-remove-member-link-'. $term_id . '-' . $row_uid;
        $link_text = t('Remove Member');
        $link_url = 'sbac-forum/nojs/' . $term_id . '/members-edit/' . $row_uid . '/remove';
      } elseif ($vars['view']->current_display == 'block_1') { // Add "re-add" controls to removed member list.
        $link_dom_id = 'forum-readd-member-link-'. $term_id . '-' . $row_uid;
        $link_text = t('Re-Add User');
        $link_url = 'sbac-forum/nojs/' . $term_id . '/members-edit/' . $row_uid . '/restore';
      }

      $link_ops = array(
        'attributes' => array(
          'class' => 'members-control-link ctools-use-modal ctools-modal-'.$link_dom_id,
          'id'    => $link_dom_id,
        ),
      );
      $link = l($link_text, $link_url, $link_ops);
      $output = $link;
      $js_settings = array(
        $link_dom_id => array( // Link has to have ctools-modal- namespace class along with this id.
          'modalSize' => array(
            'type' => 'fixed',
            'width' => 660,
            'height' => 320,
          ),
        ),
      );
      drupal_add_js($js_settings, 'setting'); // Styles the modal.
      // attach all modal requirements.
      ctools_include('ajax');
      ctools_include('modal');
      ctools_add_js('ajax-responder');
      ctools_modal_add_js();
  }

  $vars['sbac_forum_indv_member_controls'] = $output;
}

/**
 * views_view_field preprocess
 */
function sbac_forum_preprocess_views_view_field__forum_member_list__picture(&$vars) {
  $show_image = FALSE;
  $row_data = $vars['row'];
  if (isset($row_data->field_field_privacy)) {
    foreach ($row_data->field_field_privacy as $privacy_option) {
      if ($privacy_option['raw']['value'] == 'picture') {
        $show_image = TRUE;
      }
    }
  }

  if ($show_image == FALSE) { // Ensure privacy field is respected.
    $vars['output'] = '';
  }
}

/**
 * views_view_field preprocess
 */
function sbac_forum_preprocess_views_view_field__forum_member_list__uid(&$vars) {
  $user_uid = $vars['output'];
  $new_output = '';
  if (!empty($user_uid)) {
    $author_name = sbac_forum__api__get_authpane_hoverover($user_uid);
    $new_output = '' . $author_name . '';
  }

  $vars['output'] = $new_output;
}
