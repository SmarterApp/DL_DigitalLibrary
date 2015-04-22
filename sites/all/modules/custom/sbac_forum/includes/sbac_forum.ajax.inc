<?php

/**
 * Ajax callback for sbac_forum_join_button_form in includes/sbac_forum.forms.inc
 */
function sbac_forum__ajax__join_button_form_execute($form, $form_state) {
  ctools_include('ajax');
  $commands = array();
  $values = $form_state['values'];

  $forum_id = $values['forum_id'];
  $target_user_id = $values['target_user_id'];

  $forum_term = taxonomy_term_load($forum_id);
  $forum_name = $forum_term->name;

  // Create new field collection instance for member being added.
  $params = array(
    'field_name' => 'field_fc_forum_members'
  );
  $new_member_item = entity_create('field_collection_item', $params);
  $new_member_item->setHostEntity('taxonomy_term', $forum_term);
  $new_member_data = entity_metadata_wrapper('field_collection_item', $new_member_item);
  $new_member_data->field_fc_forum_member->set($target_user_id);
  $date = strtotime('today');
  $new_member_data->field_fc_forum_member_joined->set($date);
  $new_member_data->save(TRUE);

  // Need to update fields on forum entity
  $forum_term_data = entity_metadata_wrapper('taxonomy_term', $forum_term);

  // Update member counter field.
  if (isset($forum_term_data->field_forum_member_count)) {
    $current_member_count = $forum_term_data->field_forum_member_count->value();
    $current_member_count++;
    $forum_term_data->field_forum_member_count->set($current_member_count);
    $member_tab_selector = 'li.sbac-forum-vp-member-tab-item';
    $commands[] = ajax_command_invoke($member_tab_selector, 'addClass', array('sbac-qt-show'));
    $commands[] = ajax_command_invoke($member_tab_selector, 'removeClass', array('sbac-qt-hide'));
    $new_member_count_text = 'Members (' . $current_member_count . ')';
    $commands[] = ajax_command_invoke($member_tab_selector.' a', 'html', array($new_member_count_text));
  }

  $user_obj = user_load($target_user_id); // If user is facilitator, add them to the list of facis
  $is_facilitator = FALSE;
  if (in_array('facilitator', $user_obj->roles)) {
    if (isset($forum_term_data->field_forum_facilitators)) {
      $forum_term_data->field_forum_facilitators[] = $target_user_id;

      // Update facilitator field list.
      $faci_data = entity_metadata_wrapper('user', $user_obj);
      $fn = $faci_data->field_first_name->value();
      $ln = ''; // last name hide by default.
      if (isset($faci_data->field_privacy)) { // user is using non-default settings.
        $privacy_settings = $faci_data->field_privacy->value();
        if (in_array('field_last_name', $privacy_settings)) { // Check privacy settings
          $ln = ' ' . $faci_data->field_last_name->value();
        }
      }
      $full_name = $fn . $ln;
      $faci_list_selector = '.vp-faci-field ul.vp-auth-pane';
      $link = 'forum-auth-pane/'. $user_obj->uid;
      $link_ops = array('attributes' => array('class' => 'vp-auth-pane-item'));
      $faci_link = l($full_name, $link, $link_ops);
      $new_faci = '<li>' .$faci_link. '</li>';
      $commands[] = ajax_command_append($faci_list_selector, $new_faci);

      $removed_member_tab_selector = 'li.sbac-forum-vp-rem-members-tab-item';
      $commands[] = ajax_command_invoke($removed_member_tab_selector, 'addClass', array('sbac-qt-show'));
      $commands[] = ajax_command_invoke($removed_member_tab_selector, 'removeClass', array('sbac-qt-hide'));
      $is_facilitator = TRUE;
    }
  }
  $forum_term_data->save(TRUE);
  taxonomy_term_save($forum_term);

  $forum_controls = sbac_forum__api__create_forum_controls($is_facilitator, $forum_id);
  if (!empty($forum_controls['markup'])) {
    $controls_selector = '.sbac-forum-vp-controls-wrapper';
    $forum_controls_text = '<div class="sbac-forum-vp-controls"> Forum Settings</div>';
    $forum_controls_text .= '<div class="sbac-forum-vp-controls-popup">';
    $forum_controls_text .= $forum_controls . '</div>';
    $commands[] = ajax_command_invoke($controls_selector, 'html', array($forum_controls_text));
  }

  // invlidate memberlist cache when a new user joins.
  $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME. $forum_id;
  if (cache_get($cid)) {
    cache_clear_all($cid, 'cache');
  }
  sbac_forum__api__check_user_is_forum_member($forum_id, $target_user_id);

  // Ajax/js fancy behaviour.
  $message = 'Welcome to ' . $forum_name;
  // $message_selector = '.sbac-forum-confirm-message-region';
  // $commands[] = ajax_command_html($message_selector, $message);
  $_SESSION[SBAC_FORUM_SHOW_JOIN_MESSAGE] = $message;

  $button_selector = '#join-forum-form-wrapper';
  $link_text = sbac_forum__api__create_start_new_topic_link($forum_id);
  $commands[] = ajax_command_replace($button_selector, $link_text);

  // Partial implementation for not needing to refresh. Easier to call page refresh to reload tab contents.
  $commands_updated[] = ctools_ajax_command_reload();

  $page = array('#type' => 'ajax', '#commands' => $commands_updated);
  ajax_deliver($page);
  exit;
}


/**
 * =============================================================================
 *
 *    Modal Callbacks
 *
 * =============================================================================
 */

function sbac_forum__ajax__delete_forum_modal_callback($js = FALSE, $term) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $form_state = array(
      'title' => 'You Are About To Delete This Forum',
      'ajax' => TRUE,
    );

    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('sbac_forum_delete_forum_confirm', $form_state);

    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {

        // Add cleanup task to drupalqueue to delete all topic nodes that belong to this forum
        $topics = taxonomy_select_nodes($term->tid);
        if (!empty($topics)) {
          $sbac_forum_delete_orphans_queue = DrupalQueue::get('sbac_forum_delete_orphaned_topics');
          foreach ($topics as $topic_node_id) {
            $sbac_forum_delete_orphans_queue->createItem($topic_node_id);
          }
        }

        // Notification taskit entity creation.
        sbac_forum__api__send_bulk_notifications($term, 'on-delete');


        // Then finally, delete the Forum.
        $name = $term->name;
        $delete = taxonomy_term_delete($term->tid);
        if ($delete) {
          $message = 'Forum: "'. $name .'" has been deleted successfully';
          $type = 'status';
        } else {
          $message = 'There was a problem deleting forum '. $name .'. Contact Administrator';
          $type = 'error';
        }
        drupal_set_message($message, $type);

        $url = 'forums';
        $output[] = ctools_ajax_command_redirect($url);
      }
    }
    print ajax_render($output);
    exit();
  } else {
    return drupal_get_form('sbac_forum_delete_forum_confirm');
  }
}


function sbac_forum__ajax__leave_forum_modal_callback($js = FALSE, $term) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();


    $form_state = array(
      'ajax' => TRUE,
      'forum_to_leave' => $term,
    );

    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('sbac_forum_leave_forum_confirm', $form_state);

    // If the form has been submitted, there may be additional instructions
    // such as dismissing the modal popup.
    // if (!empty($form_state['ajax_commands'])) {
    //   $output = $form_state['ajax_commands'];
    // }

    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        sbac_forum__api__leave_forum($term);
        $url = 'forums';
        $output[] = ctools_ajax_command_redirect($url);
      }
    }
    print ajax_render($output);
    exit();
  } else {
    return drupal_get_form('sbac_forum_leave_forum_confirm');
  }
}


function sbac_forum__ajax__delete_topic_modal_callback($js = FALSE, $term, $topic) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $form_state = array(
      'title' => t('You are about to delete this discussion topic'),
      'ajax' => TRUE,
    );

    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('sbac_forum_delete_topic_confirm', $form_state);

    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        global $user;

        // Create task notification.
        $from_user_id = $user->uid; // TriggeringUser
        $for_user_id = $topic->uid;    // OwningUser
        if ($from_user_id != $for_user_id) { // no need to notify if youre deleting your own topic
          if ($task = taskit_get_object('deleted_topic_node')) {
            $task->addVisibility($task::VISIBILITY_USER);
            $task->addEntity('node', $topic->nid);
            $task->addEntity('taxonomy_term', $term->tid);
            $task->addOwningUser($for_user_id);
            $task->addTriggeringUser($from_user_id);
            $task->save();
          }
        }

        // Then finally, delete the Topic.
        $name = $topic->title;
        $delete = node_delete($topic->nid);
        $message = 'Topic: "'. $name .'" has been deleted successfully';
        $type = 'status';
        drupal_set_message($message, $type);

        $url = 'forums/term/' . $term->tid;
        $output[] = ctools_ajax_command_redirect($url);
      }
    }
    print ajax_render($output);
    exit();
  } else {
    return drupal_get_form('sbac_forum_delete_topic_confirm');
  }
}


function sbac_forum__ajax__remove_member_modal_callback($js = FALSE, $term, $uid_to_remove) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();


    $form_state = array(
      'ajax' => TRUE,
      'forum_to_update' => $term,
    );

    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('sbac_forum_remove_member_confirm', $form_state);

    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        global $user;
        $notification_message = $form_state['values']['notification_message'];
        $task_data = sbac_forum__api__leave_forum($term, 'remove', $uid_to_remove, $notification_message);

        // // Params for task.
        $from_user_id = $user->uid; // TriggeringUser
        $for_user_id = $uid_to_remove;    // OwningUser
        if (isset($task_data['removed_member_collection_eid'])) {
          $removed_member_collection_id = $task_data['removed_member_collection_eid'];
        }
        $forum_id = $term->tid;

        // Create task notification.
        if ($task = taskit_get_object('removed_forum_member')) {
          $task->addVisibility($task::VISIBILITY_USER);
          $task->addEntity('taxonomy_term', $forum_id);
          $task->addEntity('field_collection_item', $removed_member_collection_id);
          $task->addOwningUser($for_user_id);
          $task->addTriggeringUser($from_user_id);
          $task->save();
        }

        $output[] = ctools_ajax_command_reload();
      }
    }
    print ajax_render($output);
    exit();
  } else {
    return drupal_get_form('sbac_forum_remove_member_confirm');
  }
}


function sbac_forum__ajax__restore_member_modal_callback($js = FALSE, $term, $uid_to_restore) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();


    $form_state = array(
      'ajax' => TRUE,
      'forum_to_update' => $term,
    );

    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('sbac_forum_restore_member_confirm', $form_state);

    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        global $user;
        sbac_forum__api__leave_forum($term, 'restore', $uid_to_restore);

        // // Params for task.
        $from_user_id = $user->uid; // TriggeringUser
        $for_user_id = $uid_to_restore;    // OwningUser
        $forum_id = $term->tid;

        // Create task notification.
        if ($task = taskit_get_object('restored_forum_member')) {
          $task->addVisibility($task::VISIBILITY_USER);
          $task->addEntity('taxonomy_term', $forum_id);
          $task->addOwningUser($for_user_id);
          $task->addTriggeringUser($from_user_id);
          $task->save();
        }

        $output[] = ctools_ajax_command_reload();
      }
    }
    print ajax_render($output);
    exit();
  } else {
    return drupal_get_form('sbac_forum_restore_member_confirm');
  }
}

function sbac_forum__ajax__delete_comment_form_modal_callback($js = FALSE, $comment_id_to_remove) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();


    $form_state = array(
      'ajax' => TRUE,
      'target_comment_to_delete' => $comment_id_to_remove,
    );

    // Use ctools to generate ajax instructions for the browser to create
    // a form in a modal popup.
    $output = ctools_modal_form_wrapper('sbac_forum_delete_comment_confirm', $form_state);

    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        $output[] = ctools_ajax_command_reload();
      }
    }
    print ajax_render($output);
    exit();
  } else {
    return drupal_get_form('sbac_forum_delete_comment_confirm', $comment_id_to_remove);
  }
}
/**
 * =============================================================================
 *
 *    Ajax Callbacks
 *
 * =============================================================================
 */

function sbac_forum__ajax__inline_comment_form_modal_callback($topic, $comment_parent_id) {
  drupal_static_reset('drupal_add_css');
  drupal_static_reset('drupal_add_js');
  if (empty($comment_parent_id)) {
    $build = drupal_get_form("comment_node_topic_form", (object) array('nid' => $topic->nid));
  } else {
    $build = drupal_get_form("comment_node_topic_form", (object) array('nid' => $topic->nid, 'pid' => $comment_parent_id));
  }
  return drupal_render($build);
}


/**
 * Ajax Callback - All Forum sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum__ajax__all_forums_sort_form_change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['forum_sort_order'];
  $_SESSION[SBAC_FORUM_ALL_FORUM_SORTS] = $new_value_key;

  // Just return the form, dont force page refresh.
  // return $form['dl_sort_order'];

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit();
}

/**
 * Ajax Callback - My Forum sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum__ajax__my_forum_sort_form_change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['forum_sort_order'];
  $_SESSION[SBAC_FORUM_MY_FORUM_SORTS] = $new_value_key;

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit();
}

/**
 * Ajax Callback - Resource Forum sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum__ajax__resource_forum_sort_form_change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['forum_sort_order'];
  $_SESSION[SBAC_FORUM_RESOURCE_FORUM_SORTS] = $new_value_key;

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit();
}

/**
 * Ajax Callback - Topic Forum sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum__ajax__topic_forum_sort_form_change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['forum_sort_order'];
  $_SESSION[SBAC_FORUM_TOPIC_FORUM_SORTS] = $new_value_key;

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit();
}

/**
 * Ajax Callback - Topic comment sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function sbac_forum__ajax__topic_comment_sort_form_change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['comment_sort_order'];
  $_SESSION[SBAC_FORUM_TOPIC_COMMENT_SORTS] = $new_value_key;

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit();
}

function sbac_forum__ajax__keyword_search_trigger($form, $form_state) {
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  $keyword = $form_state['values']['forum_keyword'];
  $options = array(
    'query' => array(
      'keyword' => $keyword,
    ),
  );

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $url = 'forums-search';
  $output[] = ctools_ajax_command_redirect($url, 0 , $options);
  print ajax_render($output);
  exit();
}
