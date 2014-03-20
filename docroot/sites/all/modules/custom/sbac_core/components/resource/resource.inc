<?php

define('FEEDBACK_DEFAULT_SET_COUNT',    2);  // default number of gate keeper items;
define('FEEDBACK_REVIEW_TIMEOUT',       72); // value in hours;
define('FEEDBACK_REVIEW_REMINDER',      24); // value in hours
//define('FEEDBACK_RESUBMISSION_TIMEOUT', 1209600); // 2 weeks in seconds
define('FEEDBACK_RESUBMISSION_TIMEOUT', 120); // 2 minutes for testing purposes
define('FEEDBACK_MAX_REVIEW',           3); // number of reviews before publishing
define('FEEDBACK_REVIEW_NOTIFICATION',  1); // FEEDBACK_REVIEW_TIMEOUT - FEEDBACK_REVIEW_REMINDER); // we notify the user with 24 hours left;
define('FEEDBACK_REVIEWER_RID',         17); // id of the 'resource reviewer' role;
define('FEEDBACK_PUBLISHER_RID',        16); // id of the 'resource publisher' role;
define('FEEDBACK_AUTHENTICATED_RID',    2);  // id of the 'authenticated' role;

/**
 * Access callback for custom Resource operations.
 */
function resource_access($op, $node, $account = NULL) {
  if (is_null($account)) {
    global $user;
    $account = $user;
  }

  if ($account->uid == 1) {
    // return TRUE;
  }

  if ($node->type == 'resource') {
    if (isset($_GET['sec']) && $_GET['sec'] == '1') {
      if (in_array($op, array('access about process', 'view about'))) {
        return TRUE;
      }
      return FALSE;
    }

    // TODO: maybe we should just load & statically cache all feedback records
    // for current node, instead of running individual queries?
    if (isset($_GET['flag']) && ($_GET['flag'] == 'view-resource-flags' || $_GET['flag'] == 'view-resource-review-flags' || $_GET['flag'] == 'resolve-resource-review-flags')) {
      if (in_array($op, array('access about process', 'view about'))) {
        return TRUE;
      }
      if (in_array($op, array('access moderate flag', 'view moderate flag'))) {
        return TRUE;
      }
      return FALSE;
    }

    if (isset($node->workbench_moderation['current']->state) && $node->workbench_moderation['current']->state == 'published') {
      if (($op == 'access about process' || $op == 'view about') || ($op == 'access review process' || $op == 'view reviews') || ($op == 'access share process' || $op == 'view share') || $op == 'access related resources' || $op == 'access flag') {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }

    if (in_array($op, array('access about process', 'view about'))) {
      return TRUE;
    }
    elseif ($op == 'access review comments') {
      if ($node->workbench_moderation['current']->state == 'rejected' && $node->uid == $account->uid) {
        return TRUE;
      }

      return FALSE;
    }
    elseif ($op == 'access qc review comments') {
      $qc_entities = entity_load('feedback', FALSE, array(
        'node_id' => $node->nid,
        'type' => 'qc',
        'status' => 1,
        'current' => 1,
        'completed' => 1,
      ));

      return (bool) $qc_entities;
    }

    if (!in_array(SBAC_SHARE_GUEST, $account->roles) &&
      isset($node->workbench_moderation['current']->state) &&
      $node->workbench_moderation['current']->state == 'published' &&
      $op == 'access share process' || $op == 'view share') {
      return TRUE;
    }

    if (isset($node->workbench_moderation['current']->state) &&
      $node->workbench_moderation['current']->state == 'published' &&
      $op == 'access flag' || $op == 'view flag') {
      return TRUE;
    }

    if (isset($node->workbench_moderation['current']->state) &&
      $node->workbench_moderation['current']->state == 'published' &&
      $op == 'access related resources' || $op == 'view related resources') {
      return TRUE;
    }

    if ($op == 'access quality criteria process') {
      return (in_array(FEEDBACK_REVIEWER_RID, array_keys($account->roles)));
    }
    elseif ($op == 'access post process') {
      return (in_array(FEEDBACK_PUBLISHER_RID, array_keys($account->roles)));
    }
    elseif (!in_array(SBAC_SHARE_GUEST, $account->roles) && in_array($op, array('access review process', 'view reviews'))) {
      $published = ($node->status && $node->workbench_moderation['current']->state == 'published');
      $role = in_array(FEEDBACK_AUTHENTICATED_RID, array_keys($account->roles));

      return ($published && $role);
    }

    if ($op == 'access quality criteria revisions') {
      // only allow access to the Revisions tab if this is a resubmission
      return db_query("SELECT
                          max(history.stamp)
                        FROM node
                          LEFT JOIN workbench_moderation_node_history history
                            ON history.nid = node.nid
                        WHERE node.nid = :nid AND from_state = 'draft' AND state = 'needs_review'
                        group by history.nid
                        having count(history.nid) > 1;", array(':nid' => $node->nid))->fetchField();
    }

    $args = array(
      ':node_id' => $node->nid,
      ':uid' => $account->uid,
    );

    $qc_perms = array(
      'view gate keeper',
      'start gate keeper',
      'edit gate keeper',

      'view quality criteria',
      'edit quality criteria',
    );

    $post_perms = array(
      'view post',
      'start post',
      'edit post',
      'view tags',
      'edit tags',
    );

    // if the user does not have the 'resource reviewer' role, they have no access
    // to anything in the review process
    if (in_array($op, $qc_perms)) {
      if (!in_array(FEEDBACK_REVIEWER_RID, array_keys($account->roles))) {
        return FALSE;
      }
    }
    elseif (in_array($op, $post_perms)) {
      if (!in_array(FEEDBACK_PUBLISHER_RID, array_keys($account->roles))) {
        return FALSE;
      }
    }
    // incorrect permssion string
    else {
      return FALSE;
    }

    // Specifc check, if its an HTML5 module and it's published, do not show GK tab.
    if ($op == 'view gate keeper'
      && isset($node->workbench_moderation['current']->state)
      && $node->workbench_moderation['current']->state == 'published'
      && isset($node->field_html5['und'][0]['value'])
      && $node->field_html5['und'][0]['value']) {
      return FALSE;
    }

    if (in_array($op, array('view gate keeper', 'start gate keeper', 'edit gate keeper'))) {

      // is this a resubmission?
      $resubmission_timestamp = db_query("SELECT
                                            max(history.stamp)
                                          FROM node
                                            LEFT JOIN workbench_moderation_node_history history
                                              ON history.nid = node.nid
                                          WHERE node.nid = :nid AND from_state = 'draft' AND state = 'needs_review'
                                          group by history.nid
                                          having count(history.nid) > 1;", array(':nid' => $node->nid))->fetchField();
      if ($resubmission_timestamp) {
        // if we're still within the 2 weeks (FEEDBACK_RESUBMISSION_TIMEOUT) limit
        if (time() - FEEDBACK_RESUBMISSION_TIMEOUT < $resubmission_timestamp) {
          // are there any original reviewers
          $original_reviewers = db_query("SELECT
                                            field_recent_reviewers_target_id
                                          FROM field_data_field_recent_reviewers
                                          WHERE entity_id = :nid", array(':nid' => $node->nid));
          if ($original_reviewers->rowCount()) {
            // deny anyone who's not an original reviewer
            $is_reviewer = FALSE;
            foreach ($original_reviewers as $reviewer) {
              if ($reviewer->field_recent_reviewers_target_id == $account->uid) {
                $is_reviewer = TRUE;
                break;
              }
            }
            if (!$is_reviewer) {
              return FALSE;
            }
          }
        }
      }
      // read-only access
      // users can view the GK if:
      //  1. there are no existing GK entities, AND
      //  2. there is an existing GK entity, created by the user, and it is active
      //
      // we check both criteria by looking for an active GK entity created by
      // someone else
      $query = "  SELECT  id
                  FROM    eck_feedback
                  WHERE   type = 'gate_keeper'
                  AND     node_id = :node_id
                  AND     uid != :uid
                  AND     status = 1
               ";

      $id = db_query($query, $args)->fetchField();

      // if we found an id matching our query, then access is denied
      if ($id) {
        return FALSE;
      }
      // user passed the read-only process, so the last check is to ensure the user
      // doesn't have an existing, active entity
      elseif ($op == 'start gate keeper') {
        $query = "  SELECT  id
                    FROM    eck_feedback
                    WHERE   type = 'gate_keeper'
                    AND     node_id = :node_id
                    AND     uid = :uid
                    AND     status = 1
                 ";
        return (bool) !($id = db_query($query, $args)->fetchField());
      }
      // user has read-only access, but wants to edit
      elseif ($op == 'edit gate keeper') {
        // if the user is starting a gate keeper, then we don't need to do anything
        // else
        if (resource_access('start gate keeper', $node, $account)) {
          return TRUE;
        }

        // if this is not the user's entity, then access will have been denied at the
        // read-only level (above). since the user has gotten this far, then the
        // entity belongs to the current user, and is active;
        // the only thing left to check is that the entity isn't in completed state
        $query = "  SELECT  completed
                    FROM    eck_feedback
                    WHERE   type = 'gate_keeper'
                    AND     node_id = :node_id
                    AND     uid = :uid
                    AND     status = 1
                 ";

        return (bool) (!$completed = db_query($query, $args)->fetchField());
      }
      elseif ($op == 'view gate keeper') {
        if ($node->uid == $account->uid) {
          return FALSE;
        }
      }

      // default read-only access
      return TRUE;
    }
    elseif (in_array($op, array('view quality criteria', 'edit quality criteria'))) {
      $access = FALSE;

      // If this node belongs to the user looking at it. Deny access.
      if ($node->uid == $account->uid) {
        return $access;
      }

      // first of all, if there's no completed & met criteria Gate Keeper, we deny access
      // right off the bat
      $query = "  SELECT  id
                  FROM    eck_feedback
                  WHERE   type = 'gate_keeper'
                  AND     node_id = :node_id
                  AND     completed = 1
                  AND     met_criteria = 1
                  AND     status = 1
                  AND     current = 1
               ";

      if (!$id = db_query($query, array(':node_id' => $node->nid))->fetchField()) {
        return FALSE;
      }

      // now, if a user already has a Review entity, we grant them immediate access;
      $query = "  SELECT  status, completed
                  FROM    eck_feedback
                  WHERE   type = 'qc'
                  AND     node_id = :node_id
                  AND     uid = :uid
                  AND     current = 1
               ";

      $result = db_query($query, $args);

      foreach ($result as $row) {
        // we don't care about disabled (status = 0) items, because the user is allowed to
        // let their reviews expire (thus, status -> 0) and start new ones
        if ($row->status) {
          // readonly is always okay
          if ($op == 'view quality criteria') {
            return TRUE;
          }
          // otherwise we're requesting edit, and that's allowed only on non-completed entities
          else if ($row->completed == 0) {
            return TRUE;
          }
          // edit on completed entity; not allowed
          else {
            return FALSE;
          }
        }
      }

      // if the user doesn't have a Review entity, then we're dealing with one of the following
      // scenarios:
      //
      //  1.  the first reviewer hit the time limit and their review expired, so there won't be
      //      any active or completed reviews in the system
      //
      $query = "  SELECT  COUNT(id)
                  FROM    eck_feedback
                  WHERE   type = 'qc'
                  AND     node_id = :node_id
                  AND     status = 1
                  AND     current = 1
               ";

      // no reviews in the system, so OK to create new one
      if (!$count = db_query($query, array(':node_id' => $node->nid))->fetchField()) {
        return TRUE;
      }

      //  2.  this a second or third reviewer, in which case we must make sure there's already
      //      at least one completed review, but not more than
      //      two completed/active reviews in total (the current user becoming the third, and
      //      last).

      $query = "  SELECT      COUNT(f.id) AS count
                  FROM        eck_feedback f
                  WHERE       f.type = 'qc'       -- 1. first we find the review:
                  AND         f.node_id = :node_id    --      it must match the resource
                  AND         f.status = 1            --      it must be active
                  AND         f.completed = 1         --      it must be completed
                  AND         f.current = 1           --      it must be current
               ";

      $completed_count = db_query($query, array(':node_id' => $node->nid))->fetch()->count;

      $query = "  SELECT      COUNT(f.id) AS count
                  FROM        eck_feedback f
                  WHERE       f.type = 'qc'       -- 1. first we find the review:
                  AND         f.node_id = :node_id    --      it must match the resource
                  AND         f.status = 1            --      it must be active
                  AND         f.completed = 0         --      must not be completed
                  AND         f.current = 1           --      must be current
               ";

      $active_count = db_query($query, array(':node_id' => $node->nid))->fetch()->count;

      /*
        // this will match if there are active Reviews in the system (since condition above didn't
        // match), but no completed ones, so the first reviewer must finish their work before
        // reviewers #2 and #3 can go in
        if ($completed_count == 0) {
          return FALSE;
        }
      */

      // the total number of completed and active reviews cannot be more than two
      if ($completed_count + $active_count > 2) {
        return FALSE;
      }
      else {
        return TRUE;
      }
    }
    elseif (in_array($op, array('view tags', 'edit tags'))) {
      // to access the tags screen the user must have a 'started' post
      $query = "  SELECT  completed
                  FROM    eck_feedback
                  WHERE   type = 'post'
                  AND     node_id = :node_id
                  AND     uid = :uid
                  AND     status = 1
               ";

      $completed = db_query($query, $args)->fetchField();

      // no result
      if ($completed === FALSE) {
        return FALSE;
      }
      // completed is 0 or 1
      else {
        // trying to edit a completed item -> deny
        if ($op == 'edit tags' && $completed) {
          return FALSE;
        }

        // either viewing the tabs screen and have an active post, or editing and the
        // post is not completed
        return TRUE;
      }
    }
    elseif (in_array($op, array('view post'))) {
      if (isset($node->workbench_moderation['current']->state) && $node->workbench_moderation['current']->state == 'approved') {
        // check for active reviews by other users
        $query = "  SELECT  COUNT(id)
                    FROM    eck_feedback
                    WHERE   type = 'post'
                    AND     uid != :uid
                    AND     status = 1
                    AND     node_id = :node_id
                 ";

        $id = db_query($query, $args)->fetchField();
        if ($id) {
          return FALSE;
        }

        return TRUE;
      }

      // TODO: user has existing review, regardless of node's current state
      return FALSE;
    }
    elseif (in_array($op, array('start post'))) {
      return TRUE;
    }
    elseif (in_array($op, array('edit post'))) {
      return TRUE;
    }
  }

  return FALSE;
}
