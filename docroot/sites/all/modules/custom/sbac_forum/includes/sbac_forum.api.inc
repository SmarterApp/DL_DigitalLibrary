<?php

// Used for implementing helper functions that will be used throughout module


function sbac_forum__api__get_active_subnav() {
  $active_subnav = '';

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
  } else {
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
  $role_access = 0; // Set default just in case. 0 = closed forum
  $state_access = 0; // Set default just in case.

  // Load up forum data.
  $forum_data = entity_metadata_wrapper('taxonomy_term', $forum);
  $user_profile = user_load($user_obj->uid); // Load up profile.
  $user_profile_wrapper = entity_metadata_wrapper('user', $user_profile);

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
      (!empty($allowed_roles)) ){
    if (isset($user_profile_wrapper->field_position)) {
      $title_terms = $user_profile_wrapper->field_position->value();
      if (!empty($title_terms)) {
        $users_title = $title_terms->tid;
        $has_role = in_array($users_title, $allowed_roles);
      }
    }
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
      (!empty($allowed_states)) ) {
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
  } else { // Forum needs to restrict by something.
    $pass = 0; // Both need to match. Its an "AND", role AND state.
    if ($validate_user_role) {
      if (!empty($has_role)) {
        $pass++;
      }
    } else { // Forum isnt role restricted.
      $pass++;
    }

    if ($validate_user_state) {
      if (!empty($has_state)) {
        $pass++;
      }
    }else {
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
    'removed'=> array(),
  );

  if (!empty($forum_id)) {
    $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME. $forum_id;
  } else {
    return $is_member;
  }

  if ($cache = cache_get($cid)) {
    $forum_details = $cache->data;
  } else {
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
          } else {
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
    } else {
      $is_member = FALSE;
    }

    if (in_array($uid, $forum_details['removed'])) {
      $is_member = 'removed';
    }
  }

  return $is_member;
}


function sbac_forum__api__create_start_new_topic_link() {
  $link_ops = array(
    'attributes' => array(
      'class' => 'new-topic-link',
    )
  );
  $link = l('Start a Topic', '#', $link_ops);
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
function sbac_forum__api__create_forum_controls($is_member, $is_facilitator, $term_id) {
  global $user;
  $forum_control_link_list = '';
  if ($is_member === TRUE) {
    if (($is_facilitator) ||
        ($user->uid == 1) ) { // Edit and delete
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
      $link_url = 'forums/term/' . $term_id . '/delete';;
      $link = l($link_text, $link_url, $link_ops);
      $forum_control_links[] = $link;

    } else { // leave forum
      $link_text = t('Leave this Forum');
      $link_url = 'sbac-forum/nojs/forum-leave/' . $term_id;
      $link_ops = array(
        'attributes' => array(
          'class' => 'ctools-use-modal vp-control-link ctools-modal-sbac-forum-leave-forum-link',
          'id'    => 'sbac-forum-leave-forum-link'
        ),
      );
      $link = l($link_text, $link_url, $link_ops);
      $forum_control_links[] = $link;
    }
  }
  if (!empty($forum_control_links)) {
    $list_args = array(
      'type'  => 'ul',
      'items' => $forum_control_links,
      'attributes' => array('class' => 'vp-control-links'),
    );
    $forum_control_link_list = theme('item_list', $list_args);
  }
  return $forum_control_link_list;
}


function sbac_forum__api__leave_forum($forum_term, $operation = 'leave', $account = NULL) {
  if ($account == NULL) {
    global $user;
    $account = $user;
  }

  $forum_term_wrapper = entity_metadata_wrapper('taxonomy_term', $forum_term);
  if (isset($forum_term_wrapper->field_fc_forum_members)) {
    $member_list = $forum_term_wrapper->field_fc_forum_members->value();
    if (!empty($member_list)) {
      foreach ($member_list as $key => $field_collection_item) {
        $member_wrapper = entity_metadata_wrapper('field_collection_item', $field_collection_item);
        if (isset($member_wrapper->field_fc_forum_member)) {
          $current_member = $member_wrapper->field_fc_forum_member->value();
          if ($current_member->uid == $account->uid) { // Matches current member
            if ($operation == 'leave') {
              // Delete item. Cleans up after itself.
              $field_collection_item->delete();

              // Set New Member count
              $current_member_count = $forum_term_wrapper->field_forum_member_count->value();
              $new_member_count = $current_member_count - 1;
              $forum_term_wrapper->field_forum_member_count->set($new_member_count);

              $forum_term_wrapper->save(TRUE);
              taxonomy_term_save($forum_term);

              // invalidate memberlist cache when a new user joins.
              $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME. $forum_term->tid;
              if (cache_get($cid)) {
                cache_clear_all($cid, 'cache');
              }

            } elseif ($operation == 'remove') {

            }
            break;
          }
        }

      }
    }
  }

  // dsm($member_list);

}
