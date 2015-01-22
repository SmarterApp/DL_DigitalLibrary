<?php


function sbac_forum_preprocess_node__topic(&$vars) {
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');

  ctools_include('ajax');
  ctools_include('modal');
  ctools_modal_add_js();

  $flag_property = isset($_GET['flag']) ? $_GET['flag'] : 0;
  if ($flag_property && !sbac_flag_moderation_access()) {
    return drupal_access_denied();
  }

  global $user;
  $node_data = entity_metadata_wrapper('node', $vars['node']);
  $forum_term = $node_data->field_topic_forum_parent->value();

  $id = $forum_term->tid;
  $type = 'term';
  if (!empty($forum_term->field_forum_resource_ref)) {
    $id = $forum_term->field_forum_resource_ref['und'][0]['target_id'];
    $type = 'node';
  }
  // Declare variables.
  $forum_name_text = '';
  $back_link = '';
  $delete_link = '';
  $edit_link = '';
  $flag_link = '';
  $has_materials = FALSE;
  $moderation_topic_header = '';
  $moderation_topic_content = '';
  $moderation_post_header = '';
  $moderation_post_content = '';

  $welcome_message = '';
  if (isset($_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE])) {
    $welcome_message = $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE];
    $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE] = '';
  }

  $is_faci = FALSE;
  if (in_array('facilitator', $user->roles)) {
    $is_faci = TRUE;
  }

  if (!empty($forum_term)) {
    $forum_name_text = $forum_term->name;

    $is_member = sbac_forum__api__check_user_is_forum_member($forum_term->tid, $user->uid);
    if ($is_member === TRUE) {
      drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.topic_view.js");
      drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.topic_comments_form.js");
      module_load_include('module', 'sbac_flag');
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
  $can_delete = node_access('delete', $vars['node']);
  try {
    if ($node_data->field_topic_default->value()) {
      $can_edit = $can_delete = sbac_central_user_has_role(array(SBAC_RESOURCE_FACILITATOR_ROLE, SBAC_RESOURCE_ADMINISTRATOR_ROLE));
    }
  } catch (EntityMetadataWrapperException $e) {
  }
  if ($can_edit) {
    $edit_link = '<span class="tertiary-edit-link">' . l('Edit Topic', $node_data->edit_url->value()) . '</span>';
  }

  if ($can_delete) {
    drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.ctools.js");
    $link_ops = array(
      'attributes' => array(
        'class' => 'ctools-use-modal vp-control-link ctools-modal-sbac-forum-delete-topic-link',
        'id' => 'sbac-forum-delete-topic-link'
      ),
    );
    $delete_link = 'sbac-forum/nojs/topic-delete/' . $forum_term->tid . '/' . $node_data->nid->value();
    $delete_link = '<span class="tertiary-delete-link">' . l('Delete Topic', $delete_link, $link_ops) . '</span>';
    $js_settings = array(
      'sbac-forum-delete-topic-link' => array( // Link has to have ctools-modal- namespace class along with this id.
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 560,
          'height' => 200,
        ),
        'modalTheme' => 'CtoolSbacForumModal',
      ),
    );
    drupal_add_js($js_settings, 'setting'); // Styles the modal.
  }

  if (!$can_edit && !$can_delete) {
    $flagged = sbac_flag_get_collaboration_flag($node_data->nid->value(), 0, $user->uid);

    if ($flagged) {
      $flag = taxonomy_term_load($flagged['flag_selected']);
      $vars['flags']['reason'] = '<span class="tertiary-flag-head">You flagged this post because ' . lcfirst($flag->name) . '</span>';
      $vars['flags']['comment'] = '<span class="tertiary-flag-desc">"' . $flagged['flag_comment'] . '"</span>';
    }
    else {
      // Flag link
      $is_default_topic = FALSE;
      try {
        $is_default_topic = $node_data->field_topic_default->value();
      } catch (EntityMetadataWrapperException $e) {
        // Don't worry about it, not all topics are default topics
      }
      if (!$is_default_topic) {
        $link_ops_flag = array(
          'attributes' => array(
            'class' => 'ctools-use-modal ctools-modal-sbac-forum-flag-post-link',
            'id' => 'sbac-forum-flag-post-link',
          ),
        );
        $flag_link = 'sbac-forum/flag/nojs/' . $node_data->nid->value() . '/0';
        $flag_link = '<span class="tertiary-flag-link">' . l('Flag', $flag_link, $link_ops_flag) . '</span>';
        $js_settings_flag = array(
          'sbac-forum-flag-post-link' => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 700,
              'height' => 414,
            ),
          ),
        );
        drupal_add_js($js_settings_flag, 'setting'); // Styles the modal.
      }
    }
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
  $action_link_ops = array(
    'attributes' => array(
      'class' => 'button blue sbac-forum-topic-node-direct-comment-link',
    ),
  );
  $new_comment_url = 'sbac-forum/custom/comment-reply/' . $node_data->nid->value() . '/0';
  $topic_author_first_name = $topic_author->field_first_name['und'][0]['value'];
  if ($node_data->field_topic_default->value()) {
    $reply_to = 'Resource Contributor';
  }
  else {
    $reply_to = 'Topic Creator';
  }
  $action_section = l('Reply to ' . $reply_to . ', ' . $topic_author_first_name, $new_comment_url, $action_link_ops);
  if (isset($forum_term->field_forum_resource_ref) && !empty($forum_term->field_forum_resource_ref[LANGUAGE_NONE])) {
    $control_data = sbac_forum__api__create_forum_controls(sbac_central_user_has_role(array('administrator')), $forum_term->tid);
  }
  else {
    $control_data = sbac_forum__api__create_forum_controls($is_faci, $forum_term->tid);
  }
  drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.topic_view.js");
  drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.topic_comments_form.js");
  $vars['action_section'] = $action_section;

  if ($flag_property) {
    $flags = sbac_flag_get_forum_flags($node_data->nid->value(), $_GET['cid']);
    $flag_out = array();

    while ($flag = $flags->fetchAssoc()) {
      $flag_out[$flag['flag_selected']][] = $flag;
    }

    // Moderator view
    if ($flag_property == 'view-topic-flags' || $flag_property == 'resolve-topic-flags') {
      $moderation_topic_header = '<div class="sbac-forum-flagged-topic-header"><span class="sbac-forum-flagged-text">Flagged</span></div>';
      $moderation_topic_content = '<div class="sbac-forum-flagged-topic-content-container">';
      foreach ($flag_out as $tid => $flag_reports) {
        $num_flags = count($flag_reports);
        $flag_term = taxonomy_term_load($tid);
        $moderation_topic_content .= '<div class="sbac-forum-flagged-topic-subheader">';
        $moderation_topic_content .= '<div class="sbac-forum-flagged-type">' . $flag_term->name . '</div>';
        $moderation_topic_content .= '<div class="sbac-forum-flagged-num">' . $num_flags . ' ' . ($num_flags == 1 ? 'flag' : 'flags') . '</div>';
        foreach ($flag_reports as $flag_report) {
          $flag_auth = entity_metadata_wrapper('user', $flag_report['uid']);
          $auth_state_wrapper = $flag_auth->field_state->value();
          $auth_state = $auth_state_wrapper[0]->name;
          $auth_email = $flag_auth->mail->value();
          $moderation_topic_content .= '<div class="sbac-forum-report-header">';
          $moderation_topic_content .= '<div class="sbac-forum-report-details">';
          $moderation_topic_content .= '<span class="sbac-forum-report-author">By ' . $flag_auth->field_first_name->value() . ' ' . $flag_auth->field_last_name->value() . ' ';
          $moderation_topic_content .= ' on ' . date('M d, Y', $flag_report['created']). '</span>';
           if ($auth_email) {
            $moderation_topic_content .= '<div class="sbac-forum-author-email"><a href = "mailto:' . $auth_email  . '">' . $auth_email . '</a>,</div>';
          }
          if ($auth_state) {
            $moderation_topic_content .= '<div class="sbac-forum-author-state">' . $auth_state . '</div>';
          }
          $moderation_topic_content .= '</div>';
          $moderation_topic_content .= '<div class="sbac-forum-report-content">' . $flag_report['flag_comment'] . '</div>';
          $moderation_topic_content .= '</div>';
        }
        $moderation_topic_content .= '</div>';
      }
      $moderation_button = '';
      $resolve_button = '';
      $remove_button = '';
      $js_settings = array();
      if ($flag_property == 'view-topic-flags') {
        $moderation_button = l(t('Start Moderation'), 'sbac-flag/nojs/start-moderation', array(
          'attributes' => array(
            'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-start-moderation',
            'id' => 'sbac-flag-start-moderation'
          ),
          'query' => array(
            'eck_review' => 0,
            'forum_type' => 'topic',
            'nid' => $node_data->nid->value(),
            'cid' => $_GET['cid'],
          ),
        ));
        $js_settings['sbac-flag-start-moderation'] = array(
          'modalSize' => array(
            'type' => 'fixed',
            'width' => 600,
            'height' => 230,
          ),
        );
      }
      else {
        // $resolve_button = l(t('Resolve Flags'), 'sbac-flag/forum/nojs/resolve-all/topic', array(
        $resolve_button = l(t('Resolve Flags'), 'sbac-forum/flag/resolve/nojs/topic/' . $node_data->nid->value() . '/' . $_GET['cid'], array(
            'attributes' => array(
              'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-resolve-button',
              'id' => 'sbac-flag-resolve-button',
            ),
          ));
        $remove_button = l(t('Remove Topic'), 'sbac-forum/flag/remove/nojs/topic/' . $node_data->nid->value() . '/' . $_GET['cid'], array(
            'attributes' => array(
              'class' => 'ctools-use-modal red button use-ajax ctools-modal-sbac-flag-remove-button',
              'id' => 'sbac-flag-remove-button',
            ),
          ));
        $js_settings = array(
          'sbac-flag-resolve-button' => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 640,
              'height' => 310,
            ),
          ),
          'sbac-flag-remove-button' => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 640,
              'height' => 310,
            ),
          ),
        );
      }
      drupal_add_js($js_settings, 'setting');
      $moderation_topic_content .= $moderation_button . $resolve_button . $remove_button;
      $moderation_topic_content .= '</div>';
    }
    elseif ($flag_property == 'view-post-flags') {
      $moderation_content_header = '<div class="sbac-forum-flagged-content-header"><span class="sbac-forum-flagged-text">Flagged</span></div>';
    }
    // Moderator moderate
  }


  // Put everything into arrays and register in vars for tpl. ------------

  $parent_forum_markup = array(
    'welcome_message' => $welcome_message,
    'forum_name' => $forum_name_text,
    'controls' => $control_data, // Has key "markup" and "classes"
  );
  $vars['parent_forum_markup'] = $parent_forum_markup;

  $tertiary_nav = array(
    'back' => $back_link,
    'delete' => $delete_link,
    'edit' => $edit_link,
    'favorite' => sbac_favorites_get_favorite_link($user->uid, $id, $type),
    'flag' => $flag_link,
  );
  $vars['tertiary_nav'] = $tertiary_nav;

  $main_content = array(
    'author_image' => $author_image_markup,
    'author_name_popup' => $author_info,
    'posted' => $posted,
    'has_materials' => $has_materials,
  );
  $vars['main_content'] = $main_content;
  $vars['moderation'] = array(
    'topic' => array(
      'header' => $moderation_topic_header,
      'content' => $moderation_topic_content,
    ),
    'post' => array(
      'header' => $moderation_post_header,
      'content' => $moderation_post_content,
    ),
  );

  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  $sort_form = drupal_get_form('sbac_forum_comment_sort_form');
  $vars['sort_by'] = drupal_render($sort_form);
}


function sbac_forum_preprocess_sbac_forum_comment__node_topic(&$vars) {
  $moderation_type = isset($_GET['flag']) ? $_GET['flag'] : '';
  if ($moderation_type && !sbac_flag_moderation_access()) {
    return drupal_access_denied();
  }

  global $user;
  $comment_entity = $vars['comment'];
  $comment_data = entity_metadata_wrapper('comment', $comment_entity);
  $vars['removed'] = FALSE;

  $vars['comment_id'] = $comment_entity->cid;

  $new_status_message = '';
  if (isset($_SESSION[SBAC_FORUM_SHOW_NEW_COMMENT_MESSAGE])) {
    if (!empty($_SESSION[SBAC_FORUM_SHOW_NEW_COMMENT_MESSAGE])) {
      $current_sesh_val = $_SESSION[SBAC_FORUM_SHOW_NEW_COMMENT_MESSAGE];
      if ($current_sesh_val == $comment_entity->cid) {
        $new_status_message = 'Thank you for joining the conversation';
        $_SESSION[SBAC_FORUM_SHOW_NEW_COMMENT_MESSAGE] = 0;
      }
    }
  }

  $comment_auth_uid = $comment_entity->uid;
  $is_comment_author = $comment_auth_uid == $user->uid;
  $user_image = sbac_forum__api__get_author_picture($comment_auth_uid, 'forum_profile_image_60x60');
  $user_name_w_hoverover = sbac_forum__api__get_authpane_hoverover($comment_auth_uid);

  $posted_date = date('M jS, Y g:ia', $comment_entity->created);

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

  $vars['new_comment_status_message'] = $new_status_message;
  $vars['picture'] = $user_image;
  $vars['auth_name_hover'] = $user_name_w_hoverover;
  $vars['depth_extra'] = $depth_extra;
  $vars['posted_date'] = $posted_date;
  $vars['has_materials'] = $has_materials;

  // If post was removed by moderator
  $resolved_query = sbac_flag_get_forum_flags($comment_entity->nid, $comment_entity->cid);
  while ($resolved = $resolved_query->fetchAssoc()) {
    if ($resolved['resolved'] == 2) {
      $vars['removed'] = TRUE;
      $vars['new_comment_status_message'] = '';
      $vars['picture'] = '';
      $vars['auth_name_hover'] = '';
      $vars['depth_extra'] = '';
      $vars['posted_date'] = '';
      $vars['has_materials'] = '';
      $vars['content']['comment_body'][0]['#markup'] = '';
      $vars['removed'] = '<span class="sbac-forum-post-removed">Post removed by moderator.</span>';
      return;
    }
  }

  // Override reply link
  if (isset($vars['content']['links']['comment']['#links']['comment-reply'])) {
    $new_url = 'sbac-forum/custom/comment-reply/' . $comment_entity->nid . '/' . $comment_entity->cid;
    $vars['reply_link'] = l(t('Reply'), $new_url, array('attributes' => array('class' => array('comment-reply'))));
  }

  // Recommend count
  $vars['recommend_count'] = $comment_data->field_topic_comment_recommended->count();

  if ($_SESSION['sbac-topic-comment-sorts'] == 'comment-most-recommended') {
    $nid = $comment_entity->nid;
    $cid = $comment_entity->cid;
    $vars['go_to_thread_link'] = l(t('Go to Thread'), "sbac-forum/go-to-thread/$nid/$cid", array('attributes' => array('class' => array('sbac-forum-go-thread'))));
  }

  if ($is_comment_author) {
    if (isset($vars['content']['links']['comment']['#links']['comment-edit'])) {
      $vars['edit_link'] = l(t('Edit'), $vars['content']['links']['comment']['#links']['comment-edit']['href'], array('attributes' => array('class' => array('comment-edit'))));
    }
  }
  else {
    // Recommend link
    if (!sbac_forum_user_has_recommended($comment_entity->cid, $user->uid)) {
      $vars['recommend_link'] = l(t('Recommend'), current_path(), array(
        'attributes' => array(
          'cid' => $comment_entity->cid,
          'id' => 'sbac-recommend-' . $comment_entity->cid,
          'class' => array(
            'sbac-recommend-link'
          )
        )
      ));
    }

    // Flag link
    $link_ops = array(
      'class' => 'ctools-use-modal ctools-modal-sbac-forum-flag-post-' . $comment_entity->cid . '-link',
      'id' => 'sbac-forum-flag-post-' . $comment_entity->cid . '-link',
    );
    $flagged = sbac_flag_get_collaboration_flag($comment_entity->nid, $comment_entity->cid, $user->uid);
    if ($flagged) {
      $reason = taxonomy_term_load($flagged['flag_selected']);
      $vars['flags']['comments']['reason'] = '<span class="tertiary-flag-head">You flagged this post because ' . lcfirst($reason->name) . '</span>';
      $vars['flags']['comments']['comment'] = '<span class="tertiary-flag-desc">"' . $flagged['flag_comment'] . '"</span>';
    }
    else {
      $js_settings_flag = array(
        'sbac-forum-flag-post-' . $comment_entity->cid . '-link' => array(
          'modalSize' => array(
            'type' => 'fixed',
            'width' => 700,
            'height' => 414,
          ),
        ),
      );
      drupal_add_js($js_settings_flag, 'setting'); // Styles the modal.

      $flag_link = 'sbac-forum/flag/nojs/' . $comment_entity->nid . '/' . $comment_entity->cid;
      $vars['flag_link'] = l(t('Flag'), $flag_link, array('attributes' => $link_ops));
    }
    $moderation_type = isset($_GET['flag']) ? $_GET['flag'] : '';
    $moderate_cid = isset($_GET['cid']) ? $_GET['cid'] : '';
    if ($moderation_type && $comment_entity->cid == $moderate_cid) {
      unset($vars['content']['links']['comment']['#links']['flag_post']);

      $flags = sbac_flag_get_forum_flags($comment_entity->nid, $moderate_cid);
      $flags_out = array();
      while ($flag = $flags->fetchAssoc()) {
        $flags_out[$flag['flag_selected']][] = $flag;
      }


      $moderation_post_header = '<div class="sbac-flag-section">';
      $moderation_post_header .= '<div class="sbac-forum-flagged-post-header">';
      $moderation_post_header .= '<span class="sbac-forum-flagged-text">Flagged</span>';
      $moderation_post_header .= '</div>';
      $moderation_post_header .= '</div>';
      $vars['flags']['moderation']['post']['header'] = $moderation_post_header;

      $moderation_post_content = '<div class="sbac-forum-flagged-post-container">';

      foreach ($flags_out as $tid => $flag_reports) {
        $num_flags = count($flag_reports);
        $flag_term = taxonomy_term_load($tid);

        $moderation_post_content .= '<div class="sbac-forum-flagged-topic-subheader">';
        $moderation_post_content .= '<div class="sbac-forum-flagged-type">' . $flag_term->name . '</div>';
        $moderation_post_content .= '<div class="sbac-forum-flagged-num>' . $num_flags . ' ' . ($num_flags == 1 ? 'flag' : 'flags') . '</div>';
        $moderation_post_content .= '</div>';

        foreach ($flag_reports as $flag_report) {
          $flag_auth = entity_metadata_wrapper('user', $flag_report['uid']);
          $auth_state_wrapper = $flag_auth->field_state->value();
          $auth_state = $auth_state_wrapper[0]->name;
          $auth_email = $flag_auth->mail->value();
          $moderation_post_content .= '<div class"Ssbac-forum-report-header">';
          $moderation_post_content .= '<div class="sbac-forum-report-details">';
          $moderation_post_content .= 'By <span class="sbac-forum-report-author">' . $flag_auth->field_first_name->value() . ' ' . $flag_auth->field_last_name->value() . '</span>';
          $moderation_post_content .= ' on ' . date('M d, Y', $flag_report['created']);
          if ($auth_email) {
            $moderation_post_content .= '<div class="sbac-forum-author-email"><a href = "mailto:' . $auth_email  . '">' . $auth_email . '</a></div>';
          }
          if ($auth_state) {
            $moderation_post_content .= '<div class="sbac-forum-author-state">,' . $auth_state . '</div>';
          }
          $moderation_post_content .= '</div>';
          $moderation_post_content .= '<div class="sbac-forum-report-content">' . $flag_report['flag_comment'] . '</div>';
        }
        $moderation_post_content .= '</div>';
        $moderation_post_content .= '</div>';
      }
      $moderation_button = '';
      $resolve_button = '';
      $remove_button = '';
      $js_settings = array();
      if ($moderation_type == 'view-comment-flags') {
        $moderation_button = l(t('Start Moderation'), 'sbac-flag/nojs/start-moderation', array(
          'attributes' => array(
            'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-start-moderation',
            'id' => 'sbac-flag-start-moderation'
          ),
          'query' => array(
            'eck_review' => 0,
            'forum_type' => 'topic',
            'nid' => $comment_entity->nid,
            'cid' => $moderate_cid,
          ),
        ));
        $js_settings['sbac-flag-start-moderation'] = array(
          'modalSize' => array(
            'type' => 'fixed',
            'width' => 600,
            'height' => 230,
          ),
        );
      }
      elseif ($moderation_type == 'resolve-comment-flags') {
        $resolve_button = l(t('Resolve Flags'), 'sbac-forum/flag/resolve/nojs/comment/' . $comment_entity->nid . '/' . $moderate_cid, array(
            'attributes' => array(
              'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-resolve-button',
              'id' => 'sbac-flag-resolve-button',
            ),
          ));
        $remove_button = l(t('Remove Post'), 'sbac-forum/flag/remove/nojs/comment/' . $comment_entity->nid . '/' . $moderate_cid, array(
            'attributes' => array(
              'class' => 'ctools-use-modal red button use-ajax ctools-modal-sbac-flag-remove-button',
              'id' => 'sbac-flag-remove-button',
            ),
          ));
        $js_settings = array(
          'sbac-flag-resolve-button' => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 640,
              'height' => 310,
            ),
          ),
          'sbac-flag-remove-button' => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 640,
              'height' => 310,
            ),
          ),
        );
      }
      drupal_add_js($js_settings, 'setting');
      $moderation_post_content .= $moderation_button . $resolve_button . $remove_button;
      $moderation_post_content .= '</div>';
      $vars['flags']['moderation']['post']['content'] = $moderation_post_content;

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
  global $user;
  $current_user = $vars['user'];
  $row_data = $vars['row'];

  $facilitator_text = '';

  if (empty($row_data->field_field_forum_resource_ref)) { // only facilitator for Topic forums
    $faci_field = array();
    if (isset($row_data->_field_data['tid']['entity']->field_forum_facilitators[LANGUAGE_NONE])) {
      $faci_field = $row_data->_field_data['tid']['entity']->field_forum_facilitators[LANGUAGE_NONE];
    }
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
          if ($first_faci_user_id = $first_item['target_id']) {
            $faci_link = sbac_forum__api__get_authpane_hoverover($first_faci_user_id);
            $facilitator_text .= 'Facilitator: ' . $faci_link;
          }
          else { // No facilitator set
            $facilitator_text .= 'Facilitator: None';
          }
        }
        else { // No facilitator set
          $facilitator_text .= 'Facilitator: None';
        }
      }
      else {
        $facilitator_text .= '<span class="facilitator">You are the <span class="sbac-forum-is-faci-highlight">Facilitator</span></span>';
      }
      $facilitator_text .= '</div>';
    }
  }

  $vars['fields']['nothing']->content = $facilitator_text;

  if (!empty($row_data->field_field_forum_resource_ref)) {
    $favorites = sbac_favorites_get_favorites($user->uid, $row_data->field_field_forum_resource_ref[0]['raw']['target_id']);
    if ($favorites) {
      $vars['fields']['nothing_1']->content = '<div class="favorites-link">' . t('FAVORITE') . '</div>';
    }
  }
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
      $ln = ''; // last name hide by default.
      if (isset($faci_data->field_privacy)) { // user is using non-default settings.
        $privacy_settings = $faci_data->field_privacy->value();
        if (in_array('field_last_name', $privacy_settings)) { // Check privacy settings
          $ln = ' ' . $faci_data->field_last_name->value();
        }
      }
      $full_name = $fn . $ln;
      $link = 'forum-auth-pane/' . $first_faci_user_id;
      $link_ops = array('attributes' => array('class' => 'forum-list-auth-pane-item'));
      $faci_link = l($full_name, $link, $link_ops);
      $facilitator_text .= 'Facilitator: ' . $faci_link;
    }
    else {
      $facilitator_text .= '<span class="facilitator">You are the <span class="sbac-forum-is-faci-highlight">Facilitator</span></span>';
    }
    $facilitator_text .= '</div>';
  }

  $vars['fields']['nothing']->content = $facilitator_text;
}

/**
 * ---------- Topic list View.---------------
 */

/**
 * views_view preprocess
 */
function sbac_forum_preprocess_views_view__forum_topic_list__block(&$vars) {
  $view = $vars['view'];
  $forum_id = array_shift($view->args);
  if ($view->current_display == 'collaboration') {
    $forum_wrapper = entity_metadata_wrapper('taxonomy_term', taxonomy_term_load($forum_id));
    $vars['topic_count'] = $view->total_rows;
    $participant_count = $forum_wrapper->__isset('field_forum_member_count') ? $forum_wrapper->field_forum_member_count->value() : 0;
    $vars['participants'] = l("Participants ({$participant_count})", 'forums/term/' . $forum_id, array('query' => array('qt-forum_content' => 1), 'fragment' => 'qt-forum_content'));
    if ($forum_wrapper->__isset('field_forum_resource_ref')) {
      $resource_id = $forum_wrapper->field_forum_resource_ref->nid->value();
      $vars['warning'] = t('Be aware this is a public site. You are participating as an employee of your district or institution.');
      $vars['review'] = t('Have you used this resource? If so, please take a moment to !review',
        array(
          '!review' => '<a href="javascript:jQuery(\'a[href=#review-reviews]\').click()">review it.</a>',
        ));
      $vars['rating'] = sbac_resource_display_fivestar_rating(sbac_resource_get_rating_average($resource_id));
      $vars['review_count'] = '<span class="collab-num-participants">' . ($collab_count = sbac_resource_get_rating_count($resource_id)) . '</span> ' . ($collab_count == 1 ? 'reviewer' : 'reviewers');
    }
  }
  $vars['join_button'] = sbac_forum__api__create_start_new_topic_link($forum_id);
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


/**
 * =============================================================================
 *    Preprocessors for keyword search.
 *
 *    There was a problem putting them in the module.
 * =============================================================================
 */

/** ---------- Forum keyword search view ---------
 *
 */
function sbac_forum_preprocess_views_view__forums_keyword_search__page(&$vars) {
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  $link_ops = array(
    'attributes' => array(
      'class' => 'kw-search-back-button-link',
    )
  );
  $link_back = l('Back to All Forums', 'keyword-search-redirect/all-forums', $link_ops);
  $vars['link_back'] = $link_back;

  // Form implementation doesnt work after ajax submission of keyword exposed filter field. No time to fix.
  // module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  // $kw_subnav = drupal_render(drupal_get_form('sbac_forum_keyword_search_sub_nav_form'));
  $count_values = $_SESSION[SBAC_FORUM_FILTER_RESULTS_COUNTER];
  $all_forums_count_text = '';
  $link_ops = array(
    'attributes' => array(
      'class' => 'button kw-search-all-forums-button-link',
    )
  );
  if (isset($count_values['block_2']) && !empty($count_values['block_2'])) {
    $all_forums_count_text = ' (' . $count_values['block_2'] . ')';
  }
  $link_all_forums = l('Resource Forums' . $all_forums_count_text, 'keyword-search-redirect/resource-forums', $link_ops);

  $my_forums_count_text = '';
  $link_ops = array(
    'attributes' => array(
      'class' => 'button kw-search-my-forums-button-link',
    )
  );
  if (isset($count_values['block_3']) && !empty($count_values['block_3'])) {
    $my_forums_count_text = ' (' . $count_values['block_3'] . ')';
  }
  $link_my_forums = l('Topic Forums' . $my_forums_count_text, 'keyword-search-redirect/topic-forums', $link_ops);

  $kw_subnav = $link_all_forums . $link_my_forums;
  $vars['keyword_subnav'] = $kw_subnav;

  $new_forum_link_text = '';
  $vocab = taxonomy_vocabulary_machine_name_load('forum');
  $access_to_add = _sbac_forum_add_forum_user_access($vocab);
  if ($access_to_add) {
    $link_options = array(
      'attributes' => array(
        'class' => 'new-forum-link',
      ),
    );
    $new_forum_link_text = '<div class="forum-subnav-start-link-wrapper">';
    $new_forum_link_text .= l('Start a Forum', 'forums/forum/add', $link_options);
    $new_forum_link_text .= '</div>';

  }
  $vars['new_forum_link_text'] = $new_forum_link_text;

  $vars['target_keyword'] = '';
  $target_keyword = $vars['view']->exposed_raw_input['keyword'];
  if (!empty($target_keyword)) {
    $vars['target_keyword'] = 'with <strong>"' . $target_keyword . '"</strong>';
  }

  $is_empty = isset($vars['empty']);
  $empty_text_content = '';
  $forum_list_empty_output = '';
  if (!empty($is_empty)) {
    $empty_text_url = 'forums';
    $link_text = t('Browse all Forums');
    $link_ops = array('attributes' => array('class' => 'forum-list-filter-empty-text-reset-link button'));
    $empty_text_link = l($link_text, $empty_text_url, $link_ops);
    $empty_text_content = '<div class="sbac-forum-filter-no-results-wrapper">';
    $empty_text_content .= '<h2>Your search returned no results</h2>';
    $empty_text_content .= '<p>Please try different search criteria or browse any of the forums below ';
    $empty_text_content .= 'that have been identified for you by using the subject(s) and grade(s) in your profile</p>';
    $empty_text_content .= '<div class="sbac-forum-filter-no-result-button-link">' . $empty_text_link . '</div>';
    $empty_text_content .= '</div>';

    $view_e = views_get_view('forum_list_empty');
    $view_e->set_display('block');
    sbac_forum_forum_listing_empty_apply_filters($view_e); // Set filters here.
    $view_e->pre_execute();
    $view_e->execute();
    $view_e->_post_execute();
    $forum_list_empty_output = $view_e->preview();
  }
  $vars['empty_text_content'] = $empty_text_content;
  $vars['forum_list_empty_output'] = $forum_list_empty_output;
}

function sbac_forum_preprocess_views_view_fields__forums_keyword_search__page(&$vars) {
  $current_user = $vars['user'];
  $row_info = $vars['row'];

  switch ($row_info->entity_type) {
    case 'taxonomy_term':
      if ($row_info->bundle_name == "Forum") {
        $params = array();
        $forum_term = taxonomy_term_load($row_info->entity_id);
        $forum_wrapper = entity_metadata_wrapper('taxonomy_term', $forum_term);

        // Term Name.
        $term_name = $forum_term->name;
        $link_path = 'forums/term/' . $forum_term->tid;
        $link_to_term = l($term_name, $link_path);
        $params['title'] = $link_to_term;

        // Membership text.
        $facilitator_text = '';
        $member_text = '';

        $faci_field = $forum_term->field_forum_facilitators[LANGUAGE_NONE];
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
              $facilitator_text .= 'Facilitator: ' . $faci_link;
            }
            else { // No facilitator set
              $facilitator_text .= 'Facilitator: None';
            }
          }
          else {
            $facilitator_text .= '<span class="facilitator">You are the <span class="sbac-forum-is-faci-highlight">Facilitator</span></span>';
          }
          $facilitator_text .= '</div>';
        }

        $membership_output = $facilitator_text;
        $params['membership'] = $membership_output;

        // Last activity
        $last_activity = date('M jS Y, g:i a', $forum_wrapper->field_forum_last_activity->value());
        $params['last_activity'] = $last_activity;

        //Stats
        $topic_count = $forum_wrapper->field_forum_topic_count->value();
        $reply_count = $forum_wrapper->field_forum_topic_comment_count->value();
        $member_count = $forum_wrapper->field_forum_member_count->value();
        $params['topic_count'] = $topic_count;
        $params['reply_count'] = $reply_count;
        $params['member_count'] = $member_count;

        $output = theme('sbac_forum_keyword_search_render_forum', array('fields' => $params));
        $new_fields = new stdClass();
        $new_fields->separator = '';
        $new_fields->wrapper_prefix = '';
        $new_fields->wrapper_suffix = '';
        $new_fields->label_html = '';
        $new_fields->content = $output;
        $vars['fields'] = array('forum_entity' => $new_fields);
      }
      break;
    case 'node':
      if ($row_info->bundle_name == "Topic") {
        $topic_node = node_load($row_info->entity_id);
        $topic_wrapper = entity_metadata_wrapper('node', $topic_node);

        // Title
        $node_title = $topic_wrapper->title->value();
        $params['title'] = l($node_title, 'node/' . $topic_node->nid);

        // Forum parent
        $forum_parent = $topic_wrapper->field_topic_forum_parent->value();
        $term_name = $forum_parent->name;
        $link_path = 'forums/term/' . $forum_parent->tid;
        $link_to_term = l($term_name, $link_path);
        $params['forum_parent'] = $link_to_term;

        // Author
        $auth_hover = sbac_forum__api__get_authpane_hoverover($topic_wrapper->author->uid->value());
        $params['started'] = $auth_hover;

        // Last comment time
        $last_activity = date('M jS Y, g:i a', $topic_node->last_comment_timestamp);
        $params['last_activity'] = $last_activity;

        $params['reply_count'] = $topic_node->comment_count;

        $output = theme('sbac_forum_keyword_search_render_topic', array('fields' => $params));
        $new_fields = new stdClass();
        $new_fields->separator = '';
        $new_fields->wrapper_prefix = '';
        $new_fields->wrapper_suffix = '';
        $new_fields->label_html = '';
        $new_fields->content = $output;
        $vars['fields'] = array('topic_entity' => $new_fields);
      }
      break;
    case 'comment':
      if ($row_info->bundle_name == "Topic comment") {
        $comment_entity = comment_load($row_info->entity_id);
        $author_uid = $comment_entity->uid;

        $auth_image = sbac_forum__api__get_author_picture($author_uid, 'forum_profile_image_60x60');
        $auth_name = sbac_forum__api__get_authpane_hoverover($author_uid);
        $params['auth_image'] = $auth_image;
        $params['auth_name'] = $auth_name;

        $created = date('M jS Y, g:i a', $comment_entity->created);
        $params['created'] = $created;

        $comment_wrapper = entity_metadata_wrapper('comment', $comment_entity);
        $topic_node = $comment_wrapper->node->value();
        $params['topic_link'] = l($topic_node->title, 'node/' . $topic_node->nid);
        $forum_parent = $comment_wrapper->node->field_topic_forum_parent->value();
        $params['forum_link'] = l($forum_parent->name, 'forums/term/' . $forum_parent->tid);

        $snippet = $vars['fields']['content']->raw;
        $trimmed_content = truncate_utf8($snippet, 220, TRUE, TRUE);
        $params['content'] = ' ... ' . $trimmed_content;

        $output = theme('sbac_forum_keyword_search_render_comment', array('fields' => $params));
        $new_fields = new stdClass();
        $new_fields->separator = '';
        $new_fields->wrapper_prefix = '';
        $new_fields->wrapper_suffix = '';
        $new_fields->label_html = '';
        $new_fields->content = $output;
        $vars['fields'] = array('comment_entity' => $new_fields);
      }
      break;
  }

}
