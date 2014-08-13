<?php

define('FEEDBACK_DEFAULT_SET_COUNT', 2); // default number of gate keeper items;
define('FEEDBACK_REVIEW_TIMEOUT', 72); // value in hours;
define('FEEDBACK_REVIEW_REMINDER', 24); // value in hours
define('FEEDBACK_RESUBMISSION_TIMEOUT', 432000); // 5 days in seconds
define('FEEDBACK_MAX_REVIEW', 3); // number of reviews before publishing
define('FEEDBACK_REVIEW_NOTIFICATION', 48); // FEEDBACK_REVIEW_TIMEOUT - FEEDBACK_REVIEW_REMINDER); // we notify the user with 24 hours left;
define('FEEDBACK_REVIEWER_RID', 17); // id of the 'resource reviewer' role;
define('FEEDBACK_PUBLISHER_RID', 16); // id of the 'resource publisher' role;
define('FEEDBACK_AUTHENTICATED_RID', 2); // id of the 'authenticated' role;

/**
 * Access callback for custom Resource operations.
 */
function resource_access($op, $node, $account = NULL) {
  if (is_null($account)) {
    global $user;
    $account = $user;
  }

  if (isset($_GET['sec']) && $_GET['sec'] == '1') {
    if (!in_array($op, array('access about process', 'view about'))) {
      return FALSE;
    }
  }
  if (isset($_GET['flag']) && ($_GET['flag'] == 'view-resource-flags' || $_GET['flag'] == 'view-resource-review-flags' || $_GET['flag'] == 'resolve-resource-review-flags')) {
    if (!in_array($op, array('access about process', 'view about', 'access moderate flag', 'view moderate flag'))) {
      return FALSE;
    }
  }

  $access = & drupal_static(__FUNCTION__);
  if (empty($access) || !isset($access[$op])) {
    if ($node->type == 'resource') {
      switch ($op) {
        case 'start gate keeper':
          $perm = _resource_access_start_gate_keeper($node, $account);
          break;
        case 'edit gate keeper':
          $perm = _resource_access_edit_gate_keeper($node, $account);
          break;
        case 'view gate keeper':
          $perm = _resource_access_view_gate_keeper($node, $account);
          break;
        case 'view quality criteria':
          $perm = _resource_access_view_quality_criteria($node, $account);
          break;
        case 'edit quality criteria':
          $perm = _resource_access_edit_quality_criteria($node, $account);
          break;
        case 'view post':
        case 'start post':
        case 'edit post':
        case 'view tags':
        case 'edit tags':
        case 'access post process':
          $perm = in_array(FEEDBACK_PUBLISHER_RID, array_keys($account->roles));
          break;
        case 'access quality criteria revisions':
          $perm = _sbac_resource_resubmit_timestamp($node->nid) && _sbac_resource_is_recent_reviewers($node->nid, $account->uid);
          break;
        case 'access quality criteria process':
          $perm = in_array(FEEDBACK_REVIEWER_RID, array_keys($account->roles));
          break;
        case 'view related resources':
          $perm = _resource_access_node_has_state('published');
          break;
        case 'view collaboration':
          $perm = _resource_access_node_has_state('published') && !in_array(SBAC_SHARE_GUEST, $account->roles) && sbac_forum_get_resource_forum_id($node->nid);
        case 'access review comments':
          $perm = _resource_access_node_has_state('rejected') && $node->uid == $account->uid;
          break;
        case 'access share process':
        case 'view share':
        case 'access related resources':
        case 'view flag':
        case 'access flag':
        case 'view reviews':
        case 'access review process':
          $perm = _resource_access_node_has_state('published') && !in_array(SBAC_SHARE_GUEST, $account->roles) && in_array(FEEDBACK_AUTHENTICATED_RID, array_keys($account->roles));
          break;
        case 'access about process':
        case 'view about':
          $perm = TRUE;
          break;
        case
        'access qc review comments':
          $qc_entities = entity_load('feedback', FALSE, array(
            'node_id' => $node->nid,
            'type' => 'qc',
            'status' => 1,
            'current' => 1,
            'completed' => 1,
          ));

          $perm = (bool) $qc_entities;
          break;
      }
      $access[$op] = $perm;
    }
  }
  return $access[$op];
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

  // Specifc check, if its an HTML5 module and it's published, do not show GK tab.
  if (_resource_access_node_has_state('published') && isset($node->field_html5['und'][0]['value']) && $node->field_html5['und'][0]['value']) {
    $access = FALSE;
  }
  else {
    // Make sure we are still in GK and have the right role.
    if (_sbac_resource_is_in_gate_keeping($node->nid) && in_array(FEEDBACK_REVIEWER_RID, array_keys($account->roles))) {
      $submit_timestamp = _sbac_resource_resubmit_timestamp($node->nid);
      // if this is a new submission, or if it is a resubmission and the user has access
      if (!$submit_timestamp || ($submit_timestamp && _resource_access_resubmission_access($node, $account, $submit_timestamp))) {
        // if the user has an active GK (we don't care if it's completed or not), then allow
        $user_active_gk = db_select('eck_feedback', 'f')
          ->condition('f.node_id', $node->nid)
          ->condition('f.status', 1)
          ->condition('f.current', 1)
          ->condition('f.type', 'gate_keeper')
          ->condition('f.uid', $account->uid)
          ->condition('f.created', _sbac_resource_resubmit_timestamp($node->nid), '>')
          ->fields('f', array('id'))->countQuery()->execute()->fetchField();
        if ($user_active_gk) {
          $access = TRUE;
        }
        else {
          // if there are no other active GK (by anybody), then allow
          $other_active_gk = db_select('eck_feedback', 'f')
            ->condition('f.node_id', $node->nid)
            ->condition('f.status', 1)
            ->condition('f.current', 1)
            ->condition('f.type', 'gate_keeper')
            ->condition('f.created', _sbac_resource_resubmit_timestamp($node->nid), '>')
            ->fields('f', array('id'))->countQuery()->execute()->fetchField();
          if (!$other_active_gk) {
            $access = TRUE;
          }
        }
      }
    }
  }
  return $access;
}

/**
 * 'start gate keeper' access control
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_start_gate_keeper($node, $account) {
  return _resource_access_view_gate_keeper($node, $account);
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
    $completed_gk = db_select('eck_feedback', 'f')
      ->condition('f.node_id', $node->nid)
      ->condition('f.completed', 1)
      ->condition('f.type', 'gate_keeper')
      ->condition('f.uid', $account->uid)
      ->condition('f.created', _sbac_resource_resubmit_timestamp($node->nid), '>')
      ->fields('f', array('id'))->countQuery()->execute()->fetchField();
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
  if (_sbac_resource_is_in_quality_review($node->nid) && in_array(FEEDBACK_REVIEWER_RID, array_keys($account->roles))) {
    $submit_timestamp = _sbac_resource_resubmit_timestamp($node->nid);
    // if this is a new submission, or if it is a resubmission and the user has access
    if (!$submit_timestamp || ($submit_timestamp && _resource_access_resubmission_access($node, $account, $submit_timestamp))) {
      // If the user has a review in progress, allow
      $user_qc_in_progress = db_select('eck_feedback', 'f')
        ->condition('f.node_id', $node->nid)
        ->condition('f.type', 'qc')
        ->condition('f.current', 1)
        ->condition('f.completed', 0)
        ->condition('f.status', 1)
        ->condition('f.uid', $account->uid)
        ->condition('f.created', $submit_timestamp, '>')
        ->fields('f', array('id'))->countQuery()->execute()->fetchField();
      if ($user_qc_in_progress) {
        $access = TRUE;
      }
      else {
        $completed_reviews = db_select('eck_feedback', 'f')
          ->condition('f.node_id', $node->nid)
          ->condition('f.type', 'qc')
          ->condition('f.current', 1)
          ->condition('f.completed', 1)
          ->condition('f.created', $submit_timestamp, '>')
          ->fields('f', array('uid'))->distinct()->countQuery()->execute()->fetchField();
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
    $user_qc_completed = db_select('eck_feedback', 'f')
      ->condition('f.node_id', $node->nid)
      ->condition('f.type', 'qc')
      ->condition('f.current', 1)
      ->condition('f.completed', 1)
      ->condition('f.uid', $account->uid)
      ->condition('f.created', _sbac_resource_resubmit_timestamp($node->nid), '>')
      ->fields('f', array('id'))->countQuery()->execute()->fetchField();
    $access = !$user_qc_completed;
  }

  return $access;
}

/**
 * Access control for submitted/resubmitted resources
 *
 * @param $node
 * @param $account
 * @return bool
 */
function _resource_access_resubmission_access($node, $account, $submit_timestamp) {
  // if we're still within the FEEDBACK_RESUBMISSION_TIMEOUT limit, then only original reviewers can review this resource
  if (time() - FEEDBACK_RESUBMISSION_TIMEOUT < $submit_timestamp) {
    $access = _sbac_resource_is_recent_reviewers($node->nid, $account->uid);
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
 * @param $state
 * @return bool
 */
function _resource_access_node_has_state($node, $state) {
  return isset($node->workbench_moderation['current']->state) && $node->workbench_moderation['current']->state == $state;
}