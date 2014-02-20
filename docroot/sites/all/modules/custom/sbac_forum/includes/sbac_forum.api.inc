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
    $users_roles = array_keys($user_obj->roles);
    $has_role = array_intersect($allowed_roles, $users_roles);
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
    $user_profile = user_load($user_obj->uid);
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
