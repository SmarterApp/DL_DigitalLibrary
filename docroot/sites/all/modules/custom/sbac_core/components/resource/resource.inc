<?php

define('FEEDBACK_DEFAULT_SET_COUNT', 2); // default number of gate keeper items;
define('FEEDBACK_REVIEW_TIMEOUT', 72); // value in hours;
define('FEEDBACK_REVIEW_REMINDER', 24); // value in hours
define('FEEDBACK_RESUBMISSION_TIMEOUT', 432000); // 5 days in seconds
define('FEEDBACK_MAX_REVIEW', 3); // number of reviews before publishing
define('FEEDBACK_REVIEW_NOTIFICATION', 24); // FEEDBACK_REVIEW_TIMEOUT - FEEDBACK_REVIEW_REMINDER); // we notify the user within 24 hours after review started;
define('FEEDBACK_REVIEWER_RID', 17); // id of the 'resource reviewer' role;
define('FEEDBACK_PUBLISHER_RID', 16); // id of the 'resource publisher' role;
define('FEEDBACK_AUTHENTICATED_RID', 2); // id of the 'authenticated' role;

/**
 * Access callback for custom Resource operations.
 * @param $op
 * @param $node
 * @param null $account
 * @return
 */
function resource_access($op, $node, $account = NULL) {
  if (is_numeric($node)) {
    $node = node_load($node);
  }
  if (!$node) {
    return FALSE;
  }

  if (is_null($account)) {
    global $user;
    $account = $user;
  }

  if (isset($_GET['sec']) && $_GET['sec'] == '1') {
    if (!in_array($op, array('access about process', 'view about'))) {
      return FALSE;
    }
  }
  if (isset($_GET['flag']) && in_array($_GET['flag'], array('view-resource-flags', 'view-resource-review-flags', 'resolve-resource-review-flags'))) {
    if (in_array($op, array('access about process', 'view about', 'access moderate flag', 'view moderate flag'))) {
      return TRUE;
    }
    return FALSE;
  }

  $access = &drupal_static(__FUNCTION__);
  if (empty($access) || empty($access[$account->uid]) || !isset($access[$account->uid][$op])) {
    if ('resource' == $node->type) {
      $perm = FALSE;
      switch ($op) {
        case 'edit gate keeper':
          $perm = _resource_access_edit_gate_keeper($node, $account);
          break;
        case 'start gate keeper':
        case 'view gate keeper':
          $perm = _resource_access_view_gate_keeper($node, $account);
          break;
        case 'view quality criteria':
          $perm = _resource_access_view_quality_criteria($node, $account);
          break;
        case 'edit quality criteria':
          $perm = _resource_access_edit_quality_criteria($node, $account);
          break;
        case 'access post process':
          $perm = sbac_central_user_has_role(array('resource publisher'), $account);
          break;
        case 'view post':
        case 'start post':
          $perm = _resource_access_view_post($node, $account);
          break;
        case 'edit post':
          $perm = _resource_access_edit_post($node, $account);
          break;
        case 'view tags':
        case 'edit tags':
          $perm = _resource_access_view_tags($node, $account);
          break;
        case 'access quality criteria revisions':
          $perm = _resource_access_access_quality_criteria_revisions($node, $account);
          break;
        case 'access quality criteria process':
          $perm = sbac_central_user_has_role(array('resource reviewer', 'resource publisher'), $account);
          break;
        case 'view related resources':
          $perm = _resource_access_node_has_state($node, array('published'));
          break;
        case 'view collaboration':
          $perm = FALSE;
          //$perm = _resource_access_node_has_state($node, array('published')) && !sbac_central_user_has_role(array('guest'), $account) && sbac_forum_get_resource_forum_id($node->nid);
          break;
        case 'access gk review comments':
          $perm = _resource_access_gk_review_comment($node, $account);
          break;
        case 'access share process':
        case 'view share':
        case 'access related resources':
        case 'view flag':
        case 'access flag':
        case 'view reviews':
        case 'access review process':
          $perm = _resource_access_node_has_state($node, array('published')) && !sbac_central_user_has_role(array('guest'), $account) && $account->uid > 0;
          break;
        case 'access about process':
        case 'view about':
          $perm = TRUE;
          break;
        case 'access qc review comments':
          $perm = _resource_access_access_qc_review_comment($node, $account);
          break;
      }
      $access[$account->uid][$op] = $perm;
    }
  }
  return $access[$account->uid][$op];
}

/**
 * 'view gate keeper' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_view_gate_keeper($node, $account) {
  $access = FALSE;

  // Specific check, if its an HTML5 module and it's published, do not show GK tab.
  if (_resource_access_node_has_state($node, array('published')) && isset($node->field_html5['und'][0]['value']) && $node->field_html5['und'][0]['value']) {
    $access = FALSE;
  }
  else {
    // Make sure we are still in GK and have the right role.
    if (_sbac_resource_is_in_gate_keeping($node) && sbac_central_user_has_role(array('resource reviewer'), $account)) {
      // if the user has an active GK (we don't care if it's completed or not), then allow
      $user_active_gk = _resource_access_count_feedback($node->nid, 'gate_keeper', $account->uid, 1);
      if ($user_active_gk) {
        $access = TRUE;
      }
      else {
        // if there are no other active GK (by anybody), then allow
        $other_active_gk = _resource_access_count_feedback($node->nid, 'gate_keeper', FALSE, 1);
        if (!$other_active_gk) {
          $access = TRUE;
        }
      }
    }
    else {
      // it is not in gate keeping, but we'll allow the owner of the GK review to view (read-only) his review
      if (!_resource_access_node_has_state($node, array('published'))) {
        $user_completed_gk = _resource_access_count_feedback($node->nid, 'gate_keeper', $account->uid, FALSE, 1);
        if ($user_completed_gk) {
          $access = TRUE;
        }
      }
    }
  }
  return $access;
}

/**
 * 'edit gate keeper' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_edit_gate_keeper($node, $account) {
  $access = _resource_access_view_gate_keeper($node, $account);
  if ($access) {
    // make sure haven't already completed a GK
    $completed_gk = _resource_access_count_feedback($node->nid, 'gate_keeper', $account->uid, FALSE, 1);
    $access = !$completed_gk;
  }
  return $access;
}

/**
 * 'view quality criteria' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_view_quality_criteria($node, $account) {
  $access = FALSE;
  if (_sbac_resource_is_in_quality_review($node) && sbac_central_user_has_role(array('resource reviewer'), $account)) {
    $submit_timestamp = _sbac_resource_resubmit_timestamp($node->nid);
    // If the user has a review in progress, allow
    $user_qc_in_progress = _resource_access_count_feedback($node->nid, 'qc', $account->uid, 1, 0);
    if ($user_qc_in_progress) {
      $access = TRUE;
    }
    else {
      $completed_reviews = _resource_access_count_feedback($node->nid, 'qc', FALSE, FALSE, 1);
      $in_progress_reviews = db_select('eck_feedback', 'f')
        ->condition('f.node_id', $node->nid)
        ->condition('f.type', 'qc')
        ->condition('f.current', 1)
        ->condition('f.completed', 0)
        ->condition('f.status', 1)
        ->condition('f.created', $submit_timestamp, '>')
        ->condition('f.uid', db_select('eck_feedback', 'f2')
          ->condition('f2.node_id', $node->nid)
          ->condition('f2.status', 1)
          ->condition('f2.completed', 1)
          ->condition('f2.current', 1)
          ->condition('f2.type', 'qc')
          ->condition('f2.created', $submit_timestamp, '>')
          ->fields('f2', array('uid'))->distinct(), 'NOT IN')
        ->fields('f', array('uid'))->distinct()->countQuery()->execute()->fetchField();
      if (0 == $completed_reviews && $in_progress_reviews < 3) {
        $access = TRUE;
      }
      elseif (1 == $completed_reviews && $in_progress_reviews < 2) {
        $access = TRUE;
      }
      elseif (2 == $completed_reviews && 0 == $in_progress_reviews) {
        $access = TRUE;
      }
    }
  }
  else {
    // it is not in QC, but we'll allow the owner of the QC review to view (read-only) his review
    if (!_resource_access_node_has_state($node, array('published'))) {
      $user_completed_qc = _resource_access_count_feedback($node->nid, 'qc', $account->uid, FALSE, 1, 1);
      if ($user_completed_qc) {
        $access = TRUE;
      }
    }
  }
  return $access;
}

/**
 * 'view post' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_view_post($node, $account) {
  $access = FALSE;
  if (_resource_access_node_has_state($node, array('approved')) && sbac_central_user_has_role(array('resource publisher'), $account)) {
    $submit_timestamp = _sbac_resource_resubmit_timestamp($node->nid);
    // check for active reviews by others
    $other_reviews = db_select('eck_feedback', 'f')
      ->condition('f.type', 'post')
      ->condition('f.node_id', $node->nid)
      ->condition('f.status', 1)
      ->condition('f.uid', $account->uid, '<>')
      ->condition('f.created', $submit_timestamp, '>')
      ->fields('f', array('id'))->countQuery()->execute()->fetchField();
    $access = !$other_reviews;
  }
  return $access;
}

/**
 * 'edit post' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_edit_post($node, $account) {
  $access = _resource_access_view_post($node, $account);
  if ($access) {
    // make sure the user hasn't completed a post review yet
    $user_post_completed = _resource_access_count_feedback($node->nid, 'post', $account->uid, FALSE, 1);
    $access = !$user_post_completed;
  }
  return $access;
}

/**
 * 'view tags' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_view_tags($node, $account) {
  $access = FALSE;
  if (sbac_central_user_has_role(array('resource publisher'), $account)) {
    // to access the tags screen the user must have an active post
    $access = _resource_access_count_feedback($node->nid, 'post', $account->uid, 1, 0);
  }
  return $access;
}

/**
 * 'edit quality criteria' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_edit_quality_criteria($node, $account) {
  $access = _resource_access_view_quality_criteria($node, $account);
  if ($access) {
    // make sure the user hasn't completed a review yet
    $user_qc_completed = _resource_access_count_feedback($node->nid, 'qc', $account->uid, FALSE, 1);
    $access = !$user_qc_completed;
  }

  return $access;
}

/**
 * Access control for reviewers on submitted/resubmitted resources
 *
 * @param $node
 * @param $account
 * @param $submit_timestamp
 * @return bool
 */
function _resource_access_resubmission_reviewer_access($node, $account, $submit_timestamp) {
  // if we're still within the FEEDBACK_RESUBMISSION_TIMEOUT limit, then only original reviewers can review this resource
  if (time() - FEEDBACK_RESUBMISSION_TIMEOUT < $submit_timestamp) {
    $access = _sbac_resource_is_recent_reviewers($node, $account->uid);
  }
  else {
    // FEEDBACK_RESUBMISSION_TIMEOUT has expired
    $access = TRUE;
  }
  return $access;
}

/**
 * Access control for publishers on submitted/resubmitted resources
 *
 * @param $node
 * @param $account
 * @param $submit_timestamp
 * @return bool
 */
function _resource_access_resubmission_publisher_access($node, $account, $submit_timestamp) {
  // if we're still within the FEEDBACK_RESUBMISSION_TIMEOUT limit, then only original publisher can review this resource
  if (time() - FEEDBACK_RESUBMISSION_TIMEOUT < $submit_timestamp) {
    $access = _sbac_resource_is_recent_publishers($node, $account->uid);
  }
  else {
    // FEEDBACK_RESUBMISSION_TIMEOUT has expired
    $access = TRUE;
  }
  return $access;
}

/**
 * Checks the current state of the node
 *
 * @param $node
 * @param $states
 * @return bool
 */
function _resource_access_node_has_state($node, $states) {
  return isset($node->workbench_moderation['current']->state) && in_array($node->workbench_moderation['current']->state, $states);
}

/**
 * Count the feedback
 *
 * @param $nid
 * @param $type
 * @param bool $uid
 * @param bool $status
 * @param bool $completed
 * @param bool $current
 * @return int
 */
function _resource_access_count_feedback($nid, $type, $uid = FALSE, $status = FALSE, $completed = FALSE, $current = FALSE) {
  $query = db_select('eck_feedback', 'f')
    ->condition('f.node_id', $nid)
    ->condition('f.type', $type)
    ->condition('f.created', _sbac_resource_resubmit_timestamp($nid), '>');
  if ($uid !== FALSE) {
    $query->condition('f.uid', $uid);
  }
  if ($status !== FALSE) {
    $query->condition('f.status', $status);
  }
  if ($completed !== FALSE) {
    $query->condition('f.completed', $completed);
  }
  if ($current !== FALSE) {
    $query->condition('f.current', $current);
  }
  $query->fields('f', array('id'));
  return $query->countQuery()->execute()->fetchField();
}

/**
 * 'access quality criteria revisions' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_access_quality_criteria_revisions($node, $account) {
  $access = FALSE;

  // If the current user is reviewing this, and it's a resubmission, mark it as such.
  $resub_reviewer = FALSE;
  if ($node->feedback_status->resubmission) {
    if ($account->uid == $node->feedback_status->gatekeeper_uid && !$node->feedback_status->gatekeeper_finished) {
      $resub_reviewer = TRUE;
    }
    foreach ($node->feedback_status->qc_status as $qc_status) {
      if ($account->uid == $qc_status['uid'] && !$qc_status['finished']) {
        $resub_reviewer = TRUE;
      }
    }
  }

  // Allow access to the revisions tab if the user is an admin, DLRB, or if they are reviewing this as a resubmission.
  if (in_array('administrator', $account->roles) || in_array('DLRB member', $account->roles) || $resub_reviewer) {
    $access = TRUE;
  }

  return $access;
}

/**
 * 'access qc review comment' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_access_qc_review_comment($node, $account) {
  $access = FALSE;
  $rejected = db_select('workbench_moderation_node_history', 'h')
    ->condition('h.state', 'rejected')
    ->condition('h.nid', $node->nid)
    ->fields('h', array('hid'))
    ->countQuery()
    ->execute()
    ->fetchField();
  if ($rejected) {
    if (_resource_access_node_has_state($node, array('draft', 'rejected'))) {
      // contributor can see it
      $access = $node->uid == $account->uid && (_resource_access_count_feedback($node->nid, 'qc', FALSE, 1, 1, 1) || sbac_resource_failed_arbitration_twice($node->nid));
      if (!$access && sbac_central_user_has_role(array('reports administrator', 'resource publisher'), $account)) {
        if (_resource_access_count_feedback($node->nid, 'qc', FALSE, 1, 1, 1) || sbac_resource_failed_arbitration_twice($node->nid)) {
          // reports administrator in the same state as contributor can see it
          $query = db_select('node', 'n');
          $query->leftJoin('field_data_field_state', 's1', 's1.entity_id = n.uid AND s1.entity_type = \'user\'');
          $query->leftJoin('field_data_field_state', 's2', 's2.entity_id = :uid AND s2.entity_type = \'user\'', array(':uid' => $account->uid));
          $query->condition('n.nid', $node->nid);
          $query->where('s1.field_state_tid = s2.field_state_tid');
          $query->fields('n', array('nid'));
          $access = (bool) $query->countQuery()->execute()->fetchField();
        }
      }
    }
  }
  return $access;
}

/**
 * 'access gk review comment' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_gk_review_comment($node, $account){
  $access = false;
  $rejected = db_select('workbench_moderation_node_history', 'h')
    ->condition('h.state', 'rejected')
    ->condition('h.nid', $node->nid)
    ->fields('h', array('hid'))
    ->countQuery()
    ->execute()
    ->fetchField();
  if ($rejected) {
    // don't show this tab if the resource failed arbitration 2+ times
    if (!sbac_resource_failed_arbitration_twice($node->nid)) {
      if (_resource_access_node_has_state($node, array('draft', 'rejected'))) {
        // contributor has access
        $access = $node->uid == $account->uid;
        if (!$access && sbac_central_user_has_role(array('reports administrator', 'resource publisher'), $account)) {
          // reports administrator has access if they are from the same state
          $query = db_select('node', 'n');
          $query->leftJoin('field_data_field_state', 's1', 's1.entity_id = n.uid AND s1.entity_type = \'user\'');
          $query->leftJoin('field_data_field_state', 's2', 's2.entity_id = :uid AND s2.entity_type = \'user\'', array(':uid' => $account->uid));
          $query->condition('n.nid', $node->nid);
          $query->where('s1.field_state_tid = s2.field_state_tid');
          $query->fields('n', array('nid'));
          $access = (bool) $query->countQuery()->execute()->fetchField();
        }
      }
    }
  }
  return $access;
}