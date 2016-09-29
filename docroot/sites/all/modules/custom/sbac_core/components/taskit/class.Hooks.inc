<?php
namespace sbac_core\components\taskit;

class Hooks extends \devtools\Hooks {

  /*
    List of notifications:

      1. Resource submitted for review
          -> to author

      TODO: 2. Resources fails Gate Keeper
          -> to author

      TODO: 3. Resource passes Gate Keeper
          -> to author

      TODO: 4. Quality Criteria - posted w/ distinction
          -> to author
          -> to all reviewers

      TODO: 5. Quality Criteria - posted
          -> to author
          -> to all reviewers

      TODO: 6. Quality Criteria - rejected
          -> to author
          -> to all reviewers
  */

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   */
  function hook_init() {
    // add the URI to to mark viewed user's notifications as read, so that we can
    // pull it in from taskit.js
    if (match_uri('user/([0-9]+)')) {
      $uid = arg(1);
    }
    else {
      global $user;
      $uid = $user->uid;
    }

    drupal_add_js(array(
      'sbac_taskit' => array(
        'mark_read_url' => url('user/' . $uid . '/notifications/read'),
      )
    ), 'setting');
  }

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'taskit.pages.inc',
      'file path' => $this->_path,
    );

    $items['user/%user/notifications/read'] = array(
        'title' => 'Mark all notificatons read',
        'page callback' => 'taskit_mark_all_read',
        'page arguments' => array(1),
        'access callback' => 'taskit_mark_all_read_access',
        'access arguments' => array(1),
        'type' => MENU_CALLBACK
      ) + $base;

    return $items;
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_taskit_types().
   */
  function hook_taskit_types() {
    $path = $this->_path . '/taskit_types/';

    $types = array(
      // resource is submitted for review
      array(
        'name' => 'review_completed',
        'description' => t('User has completed a review.'),
        'class' => 'ReviewCompleted',
      ),
      // resource is submitted for review
      array(
        'name' => 'resource_submitted',
        'description' => t('Resource has been submitted for review.'),
        'class' => 'ResourceSubmitted',
      ),
      // resource is re-submitted for review
      array(
        'name' => 'resource_resubmitted',
        'description' => t('Resource has been re-submitted for review.'),
        'class' => 'ResourceResubmitted',
      ),
      // resource rejected (at any step of the process)
      array(
        'name' => 'resource_rejected',
        'description' => t('Resource rejected.'),
        'class' => 'ResourceRejected',
      ),
      // resource is published (at any step of the process)
      array(
        'name' => 'resource_published',
        'description' => t('Resource published.'),
        'class' => 'ResourcePublished',
      ),
      // an incomplete review has reached reminder time
      array(
        'name' => 'review_reminder',
        'description' => t('Review reminder.'),
        'class' => 'ReviewReminder',
      ),
      // a published resource was changed by a DLRB member
      array(
        'name' => 'posting_action',
        'description' => t('Posting Action.'),
        'class' => 'PostingAction',
      ),
      array(
        'name' => 'resource_reposted',
        'description' => t('Resource Reposted'),
        'class' => 'ResourceReposted',
      ),
      array(
        'name' => 'resource_promoted',
        'description' => t('Resource Promoted'),
        'class' => 'ResourcePromoted',
      ),
      array(
        'name' => 'resource_demoted',
        'description' => t('Resource Demoted'),
        'class' => 'ResourceDemoted',
      ),
      // resource is flagged
      array(
        'name' => 'resource_flagged',
        'description' => t('Resource has been flagged for review.'),
        'class' => 'ResourceFlagged',
      ),
      // resolved all flags
      array(
        'name' => 'resolved_all_flags',
        'description' => t('Resolved all resource flags.'),
        'class' => 'ResolvedAllFlags',
      ),
      // removed resource
      array(
        'name' => 'removed_resource',
        'description' => t('Removed Resource'),
        'class' => 'RemovedResource',
      ),
      // removed resource review
      array(
        'name' => 'removed_resource_review',
        'description' => t('Removed Resource Review'),
        'class' => 'RemovedResourceReview',
      ),
      // removed forum user membership
      array(
        'name' => 'removed_forum_member',
        'description' => t('Removed Forum Member'),
        'class' => 'RemovedForumMember',
      ),
      // restored forum user membership
      array(
        'name' => 'restored_forum_member',
        'description' => t('Restored Forum Member'),
        'class' => 'RestoredForumMember',
      ),
      // deleting a forum term
      array(
        'name' => 'deleted_forum_term',
        'description' => t('Deleted Forum Term'),
        'class' => 'DeletedForumTerm',
      ),
      // deleting a topic node
      array(
        'name' => 'deleted_topic_node',
        'description' => t('Deleted Topic Node'),
        'class' => 'DeletedTopicNode',
      ),
      // creating a topic node
      array(
        'name' => 'created_topic_node',
        'description' => t('Created Topic Node'),
        'class' => 'CreatedTopicNode',
      ),
      // recommending a comment
      array(
        'name' => 'recommended_forum_comment',
        'description' => t('Recommended Forum Comment'),
        'class' => 'RecommendedForumComment',
      ),
      // creating a topic comment
      array(
        'name' => 'created_forum_comment',
        'description' => t('Created Forum Comment'),
        'class' => 'CreatedForumComment',
      ),
      // deleting a forum comment
      array(
        'name' => 'deleted_forum_comment',
        'description' => t('Deleted Forum Comment'),
        'class' => 'DeletedForumComment',
      ),
      // forum changed access criteria
      array(
        'name' => 'forum_access_change',
        'description' => t('Forum Access Change'),
        'class' => 'ForumAccessChange',
      ),
      // removed topic
      array(
        'name' => 'topic_removed',
        'description' => t('Removed Forum Topic'),
        'class' => 'TopicRemoved',
      ),
      // notify topic creator
      array(
        'name' => 'topic_removed_creator',
        'description' => t('Notify topic creator'),
        'class' => 'TopicRemovedCreator',
      ),
      // notify post creator
      array(
        'name' => 'post_removed_creator',
        'description' => t('Notify Post creator'),
        'class' => 'PostRemovedCreator',
      ),
      // notify poster of HTML5 content
      array(
        'name' => 'html5_upload_error',
        'description' => t('Notify HTML5 Poster'),
        'class' => 'HTML5UploadError',
      ),
      // notify user a rating goal has been met
      array(
        'name' => 'goal_complete_rating',
        'description' => t('Notify Rating Goal completer'),
        'class' => 'GoalCompleteRating',
      ),
      // notify user a reviewed goal has been met
      array(
        'name' => 'goal_complete_reviewed',
        'description' => t('Notify Reviewed Goal completer'),
        'class' => 'GoalCompleteReviewed',
      ),
      // notify user a contributed goal has been met
      array(
        'name' => 'goal_complete_contributed',
        'description' => t('Notify Reviewed Goal completer'),
        'class' => 'GoalCompleteContributed',
      ),
       // notify user when added to most active users rated board
      array(
        'name' => 'most_active_members_rated',
        'description' => t('Notify Most Active Rated member'),
        'class' => 'MostActiveMembersRated',
      ),
       // notify user when added to most active users reviewed board
      array(
        'name' => 'most_active_members_reviewed',
        'description' => t('Notify Most Active Reviewed member'),
        'class' => 'MostActiveMembersReviewed',
      ),
       // notify user when added to most active users reviewed board
      array(
        'name' => 'most_active_members_contributed',
        'description' => t('Notify Most Active Contributed member'),
        'class' => 'MostActiveMembersContributed',
      ),
       // notify user resource has been rated
      array(
        'name' => 'resource_rated',
        'description' => t('Notify resource contributor of rating'),
        'class' => 'ResourceRated',
      ),
       // notify user in process review has timed out
      array(
        'name' => 'review_timeout',
        'description' => t('Notify resource reviewer of review timeout'),
        'class' => 'ReviewTimeout',
      ), 
    );

    foreach ($types as &$type) {
      $type['file'] = $path . 'class.' . $type['class'] . '.inc';
    }

    return $types;
  }
}



