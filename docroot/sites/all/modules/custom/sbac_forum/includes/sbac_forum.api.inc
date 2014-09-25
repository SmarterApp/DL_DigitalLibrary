<?php

// Used for implementing helper functions that will be used throughout module


function sbac_forum__api__get_active_subnav() {
  $active_subnav = SBAC_FORUM_SUBNAV_RESOURCE;

  if (isset($_SESSION[SBAC_FORUM_SUBNAV_ACTIVE])) {
    if (!empty($_SESSION[SBAC_FORUM_SUBNAV_ACTIVE])) {
      $active_subnav = $_SESSION[SBAC_FORUM_SUBNAV_ACTIVE];
    }
  }

  return $active_subnav;
}

function sbac_forum__api__set_active_subnav($value = NULL) {
  if (!empty($value)) {
    $_SESSION[SBAC_FORUM_SUBNAV_ACTIVE] = $value;
  }
  else {
    $_SESSION[SBAC_FORUM_SUBNAV_ACTIVE] = '';
  }
}


/**
 * Access check for forum term.
 *
 * @param Obj $user_obj user trying to view the forum.
 * @param Obj $forum term to check access restrictions of.
 *
 * @return Boolean True or False if user has access to view forum based on criteria.
 */
function sbac_forum__api__check_forum_view_access($user_obj, $forum) {

  // Load up forum data.
  $forum_data = entity_metadata_wrapper('taxonomy_term', $forum);
  $user_profile = user_load($user_obj->uid); // Load up profile.

  // Check to see if forum is role restricted.
  $validate_user_role = FALSE; // default to all roles have access
  $allowed_roles = array();
  if (isset($forum_data->field_forum_access_user_roles)) {
    $role_access = $forum_data->field_forum_access_user_roles->value();
    if (!$role_access) { // Have to check the role of the user.
      $validate_user_role = TRUE;
      if (isset($forum_data->field_forum_access_role_list)) {
        $allowed_roles = $forum_data->field_forum_access_role_list->value();
      }
    }
  }

  // Compare the forum restrictions to target user's roles.
  $has_role = array();
  if (($validate_user_role) &&
    (!empty($user_obj)) &&
    (!empty($allowed_roles))
  ) {
    $has_role = array_intersect($allowed_roles, array_keys($user_obj->roles));
  }


  // Check to see if forum is state restricted.
  $validate_user_state = FALSE; // Default to not care about state.
  $allowed_states = array();
  if (isset($forum_data->field_forum_access_states)) {
    $state_access = $forum_data->field_forum_access_states->value();
    if (!$state_access) { // Means forum is restricted to certain states
      $validate_user_state = TRUE;
      if (isset($forum_data->field_state)) {
        $states = $forum_data->field_state->value();
        if (!empty($states)) {
          foreach ($states as $state) {
            $allowed_states[] = $state->tid;
          }
        }
      }
    }
  }

  // Compare the forum restrictions with the target user's profile setting for state.
  $has_state = array();
  if (($validate_user_state) &&
    (!empty($user_obj)) &&
    (!empty($allowed_states))
  ) {
    $user_profile_wrapper = entity_metadata_wrapper('user', $user_profile);
    if (isset($user_profile_wrapper->field_state)) {
      $state_terms = $user_profile_wrapper->field_state->value();
      $users_states = array();
      if (!empty($state_terms)) {
        foreach ($state_terms as $state) {
          $users_states[] = $state->tid;
        }
        $has_state = array_intersect($allowed_states, $users_states);
      }
    }
  }

  $access = FALSE;
  // Bring it all together
  if ((!$validate_user_role && !$validate_user_state)) { // Forum is wide open.
    $access = TRUE;
  }
  else { // Forum needs to restrict by something.
    $pass = 0; // Both need to match. Its an "AND", role AND state.
    if ($validate_user_role) {
      if (!empty($has_role)) {
        $pass++;
      }
    }
    else { // Forum isnt role restricted.
      $pass++;
    }

    if ($validate_user_state) {
      if (!empty($has_state)) {
        $pass++;
      }
    }
    else {
      $pass++;
    }

    if ($pass == 2) {
      $access = TRUE;
    }
  }

  return $access;
}


function sbac_forum__api__check_user_is_forum_member($forum_id, $uid) {
  $is_member = FALSE;
  $cid = '';
  $forum_details = array(
    'members' => array(),
    'removed' => array(),
  );

  if (!empty($forum_id)) {
    $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME . $forum_id;
  }
  else {
    return $is_member;
  }

  if ($cache = cache_get($cid)) {
    $forum_details = $cache->data;
  }
  else {
    $forum_term = taxonomy_term_load($forum_id);
    $forum_data = entity_metadata_wrapper('taxonomy_term', $forum_term);

    // Organize current members.
    $member_id_list = array();
    $blocked_list = array();
    $members = $forum_data->field_fc_forum_members->value();
    if (!empty($members)) {
      foreach ($members as $member) {
        $member_wrapper = entity_metadata_wrapper('field_collection_item', $member);
        $member_id = 0;
        $member_is_removed = 0;
        if (isset($member_wrapper->field_fc_forum_member)) {
          $member_entity = $member_wrapper->field_fc_forum_member->value();
          $member_id = $member_entity->uid;
        }
        if (isset($member_wrapper->field_fc_forum_member_is_removed)) {
          $member_is_removed = $member_wrapper->field_fc_forum_member_is_removed->value();
        }

        if ($member_id) {
          if ($member_is_removed) {
            $blocked_list[$member_id] = $member_id;
          }
          else {
            $member_id_list[$member_id] = $member_id;
          }

        }
      }
    }

    $forum_details['members'] = $member_id_list;
    $forum_details['removed'] = $blocked_list;
    $timestamp = strtotime('+1 week'); // persist the member list for a week.
    // Ensure that if new users are added, the member list is re-cached.
    cache_set($cid, $forum_details, 'cache', $timestamp);
  }

  if (!empty($forum_details)) {
    if (in_array($uid, $forum_details['members'])) {
      $is_member = TRUE;
    }
    else {
      $is_member = FALSE;
    }

    if (in_array($uid, $forum_details['removed'])) {
      $is_member = 'removed';
    }
  }

  return $is_member;
}


function sbac_forum__api__create_start_new_topic_link($forum_id) {
  $link_ops = array(
    'attributes' => array(
      'class' => 'new-topic-link',
    ),
    'query' => array('target-forum' => $forum_id),
  );
  $link = l('Start a Topic', 'node/add/topic', $link_ops);
  $link_text = '<div class="join-forum-start-topic-wrapper">' . $link . '</div>';

  return $link_text;
}

/**
 * Function to create list element for the forum settings. Used on View page and ajax callback
 *   when a user becomes a member of the forum.
 *
 * @param Mixed $is_member should be TRUE for this function to return anything
 * @param Boolean $is_facilitator facilitator users get different set of links
 * @param INT $term_id the forum these settings are for.
 *
 * @return string themed list elements or empty string.
 */
function sbac_forum__api__create_forum_controls($is_facilitator, $term_id) {
  global $user;
  $forum_control_link_list = '';
  $extra_classes = '';
  if (($is_facilitator) ||
    ($user->uid == 1)
  ) { // Edit and delete forum
    $link_ops = array(
      'attributes' => array(
        'class' => 'vp-control-link',
      ),
    );

    $link_text = t('Edit Forum');
    $link_url = 'taxonomy/term/' . $term_id . '/edit';
    $link = l($link_text, $link_url, $link_ops);
    $forum_control_links[] = $link;

    $link_text = t('Delete Forum');
    $link_ops = array(
      'attributes' => array(
        'class' => 'ctools-use-modal vp-control-link ctools-modal-sbac-forum-delete-forum-link',
        'id' => 'sbac-forum-delete-forum-link'
      ),
    );
    $link_url = 'sbac-forum/nojs/forum-delete/' . $term_id;
    $link = l($link_text, $link_url, $link_ops);
    $forum_control_links[] = $link;
    drupal_add_js(drupal_get_path("module", "sbac_forum") . "/js/sbac_forum.ctools.js");
    $js_settings = array(
      'sbac-forum-delete-forum-link' => array( // Link has to have ctools-modal- namespace class along with this id.
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 560,
          'height' => 240,
        ),
        'modalTheme' => 'CtoolSbacForumModal'
      ),
    );
    drupal_add_js($js_settings, 'setting'); // Styles the modal.
    $extra_classes = 'hover-over-large-popup';
  }

  $js_settings = array(
    'sbac-forum-leave-forum-link' => array( // Link has to have ctools-modal- namespace class along with this id.
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 560,
        'height' => 230,
      ),
    ),
  );
  drupal_add_js($js_settings, 'setting'); // Styles the modal.

  if (!empty($forum_control_links)) {
    $list_args = array(
      'type' => 'ul',
      'items' => $forum_control_links,
      'attributes' => array('class' => 'vp-control-links'),
    );
    $forum_control_link_list = theme('item_list', $list_args);
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
  }

  $output = array(
    'markup' => $forum_control_link_list,
    'classes' => $extra_classes,
  );
  return $output;
}

function sbac_forum__api__get_author_picture($user_id, $image_style_name) {
  $output = '';
  $target_user = NULL;
  if (is_numeric($user_id)) {
    $target_user = user_load($user_id);
  }
  else {
    $target_user = $user_id; // Account is already passed in.
  }

  $account_data = entity_metadata_wrapper('user', $target_user);
  if (isset($account_data->field_privacy)) {
    $privacy_settings = $account_data->field_privacy->value();
    if (in_array('picture', $privacy_settings)) { // Check privacy settings
      if (!empty($target_user->picture)) { // Check if user has uploaded a picture
        $picture = theme('image_style', array(
          'style_name' => $image_style_name,
          'path' => $target_user->picture->uri,
          'attributes' => array('class' => 'topic-node-auth-pane-img profile-pic')
        ));
        $output = $picture;
      }
    }
  }

  return $output;
}

function sbac_forum__api__get_authpane_hoverover($user_id, $add_comma = FALSE) {
  $account = user_load($user_id);
  $account_renderable = user_view($account, 'tooltip');

  $account_data = entity_metadata_wrapper('user', $account);
  $fn = $account_data->field_first_name->value();
  $ln = ''; // last name hide by default.
  if (isset($account_data->field_privacy)) { // user is using non-default settings.
    $privacy_settings = $account_data->field_privacy->value();
    if (in_array('field_last_name', $privacy_settings)) { // Check privacy settings
      $ln = ' ' . $account_data->field_last_name->value();
    }
  }
  $full_name = $fn . $ln;

  $tooltip = '
              <div class="devtools-tooltip account-tooltip">
                <a href="#" class="devtools-tooltip-trigger" onclick="return false;">' . $full_name . '</a>' . ($add_comma ? ', ' : '') . '
                <div class="devtools-tooltip-body">' . render($account_renderable) . '</div>
              </div>
             ';

  $created = isset($account->created) ? $account->created : time();

  $output = t('!name', array(
    '!name' => $tooltip,
    '!date' => format_date($created, 'simple'),
  ));

  return $output;
}


/**
 * Handles updating all required entities when user either leaves,is removed or is added back to a forum.
 *
 * @param [type] $forum_term Forum being modified
 * @param string $operation is either "leave", 'remove', 'restore'
 * @param [type] $account_uid user being modified.
 * @param [type] $reason_message optional message as to why user is being removed.
 *
 * @return array any information that is needed by caller. Removed op returns field_collection entity id.
 */
function sbac_forum__api__leave_forum($forum_term, $operation = 'leave', $account_uid = NULL, $reason_message = NULL) {
  $return_data = array();
  if ($account_uid == NULL) {
    global $user;
    $account_uid = $user->uid;
  }

  $forum_term_wrapper = entity_metadata_wrapper('taxonomy_term', $forum_term);
  if (isset($forum_term_wrapper->field_fc_forum_members)) {
    $member_list = $forum_term_wrapper->field_fc_forum_members->value();
    if (!empty($member_list)) {
      foreach ($member_list as $key => $field_collection_item) {
        $member_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);
        if (isset($member_wrapper->field_fc_forum_member)) {
          $current_member = $member_wrapper->field_fc_forum_member->value();
          if ($current_member->uid == $account_uid) { // Matches current member
            if ($operation == 'leave') {
              // Delete item. Cleans up after itself.
              $field_collection_item->delete();

              if (in_array('facilitator', $current_member->roles)) { // Faci is trying to leave
                $current_facis = $forum_term_wrapper->field_forum_facilitators->value();
                $new_facis = array();
                if (!empty($current_facis)) {
                  foreach ($current_facis as $site_user_obj) {
                    if ($site_user_obj->uid != $account_uid) {
                      $new_facis[] = $site_user_obj->uid;
                    }
                  }
                  $forum_term_wrapper->field_forum_facilitators->set($new_facis);
                }
              }

              // Set New Member count. Decrement.
              $current_member_count = $forum_term_wrapper->field_forum_member_count->value();
              $new_member_count = $current_member_count - 1;
              $forum_term_wrapper->field_forum_member_count->set($new_member_count);

            }
            elseif ($operation == 'remove') {
              // Set the current member flag to "removed".
              $member_wrapper->field_fc_forum_member_is_removed->set(1);
              $date = strtotime('today');
              $member_wrapper->field_fc_forum_member_removed->set($date);
              if (!empty($reason_message)) {
                $member_wrapper->field_fc_forum_member_removedmsg->set($reason_message);
              }
              else {
                $member_wrapper->field_fc_forum_member_removedmsg->set('');
              }
              $member_wrapper->save(TRUE);
              $return_data['removed_member_collection_eid'] = $member_wrapper->item_id->value();
              // Set New removed member count. increment.
              $current_removed_member_count = $forum_term_wrapper->field_forum_removed_member_count->value();
              $new_removed_member_count = $current_removed_member_count + 1;
              $forum_term_wrapper->field_forum_removed_member_count->set($new_removed_member_count);

              // Set New Member count. Decrement.
              $current_member_count = $forum_term_wrapper->field_forum_member_count->value();
              $new_member_count = $current_member_count - 1;
              $forum_term_wrapper->field_forum_member_count->set($new_member_count);

              // Update user data field that stores tids of all forums user is removed from.
              $this_user = user_load($account_uid);
              $existing_removed_list = array();
              if (isset($this_user->data[SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME])) {
                $existing_removed_list = $this_user->data[SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME];
                $existing_removed_list[$forum_term->tid] = $forum_term->tid;
              }
              else {
                $existing_removed_list = array($forum_term->tid => $forum_term->tid);
              }
              $data = array(
                SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME => $existing_removed_list,
              );
              user_save($this_user, array('data' => $data));

            }
            elseif ($operation == 'restore') {
              // UnSet the current removed member flag.
              $member_wrapper->field_fc_forum_member_is_removed->set(0);
              $date = strtotime('today');
              $member_wrapper->field_fc_forum_member_joined->set($date);
              $member_wrapper->save(TRUE);

              // Set New removed member count. decrement.
              $current_removed_member_count = $forum_term_wrapper->field_forum_removed_member_count->value();
              $new_removed_member_count = $current_removed_member_count - 1;
              $forum_term_wrapper->field_forum_removed_member_count->set($new_removed_member_count);

              // Set New Member count. inrement.
              $current_member_count = $forum_term_wrapper->field_forum_member_count->value();
              $new_member_count = $current_member_count + 1;
              $forum_term_wrapper->field_forum_member_count->set($new_member_count);

              // Update user data field that stores tids of all forums user is removed from.
              $this_user = user_load($account_uid);
              $existing_removed_list = array();
              if (isset($this_user->data[SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME])) {
                $existing_removed_list = $this_user->data[SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME];
                unset($existing_removed_list[$forum_term->tid]);
              }
              $data = array(
                SBAC_FORUM_USER_DATA_REMOVED_LIST_VAR_NAME => $existing_removed_list,
              );
              user_save($this_user, array('data' => $data));

            }

            // Update all enties.
            $forum_term_wrapper->save(TRUE);
            taxonomy_term_save($forum_term);

            // invalidate memberlist cache when a user is removed or leaves.
            $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME . $forum_term->tid;
            if (cache_get($cid)) {
              cache_clear_all($cid, 'cache');
            }
            break;
          }
        }

      }
    }
  }
  return $return_data;
}

/**
 * Notification Router for forum. Used when multiple notifications have to be created.
 *   Function has to decide who to send notifications to based on $op field.
 *
 * Possible operations:
 *   1. on-delete
 *   2. access-change
 *
 * @param Object $forum_term Forum being modified. Expects fields are already loaded.
 * @param string $op is either "on-delete", 'access-change'
 *
 */
function sbac_forum__api__send_bulk_notifications($forum_term, $op, $users_to_notify = array()) {
  global $user;
  switch ($op) {
    case 'on-delete': // Send notification to all members.
      $term_wrapper = entity_metadata_wrapper('taxonomy_term', $forum_term);
      if (isset($term_wrapper->field_fc_forum_members)) {
        $members = $term_wrapper->field_fc_forum_members->value();
        foreach ($members as $field_collection_item_member) {
          $fci_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item_member);
          $is_removed = FALSE;
          if (isset($fci_wrapper->field_fc_forum_member_is_removed)) {
            $is_removed = $fci_wrapper->field_fc_forum_member_is_removed->value();
          }
          if (!$is_removed) { // only notify non-removed members.
            if (isset($fci_wrapper->field_fc_forum_member)) {
              if ($member_info = $fci_wrapper->field_fc_forum_member->value()) {
                if ($member_info->uid != $user->uid) { // No need to notify person deleting the forum.
                  // Create task notification.
                  if ($task = taskit_get_object('deleted_forum_term')) {
                    $task->addVisibility($task::VISIBILITY_USER);
                    $task->addEntity('taxonomy_term', $forum_term->tid);
                    $task->addOwningUser($member_info->uid);
                    $task->addTriggeringUser($user->uid);
                    $task->save();
                  }
                }
              }
            }
          }
        }
      }
      break;
    case 'access-change':
      if (!empty($users_to_notify)) {
        foreach ($users_to_notify as $user_to_remove) {
          // Create task notification.
          if ($task = taskit_get_object('forum_access_change')) {
            $task->addVisibility($task::VISIBILITY_USER);
            $task->addEntity('taxonomy_term', $forum_term->tid);
            $task->addOwningUser($user_to_remove);
            $task->addTriggeringUser($user->uid);
            $task->save();
          }
        }
      }
      break;
  }
}

function sbac_forum__api__get_deleted_log_entry($entity_id, $entity_type) {
  $query = db_select('sbac_forum_deleted_log', 'dl');
  $query->fields('dl', array('title'));
  $query->condition('dl.entity_id', $entity_id);
  $query->condition('dl.entity_type', $entity_type);
  $query->orderBy('dl.entity_id', 'DESC');
  $query->range(0, 1);
  return $query->execute()->fetchAssoc();
}
