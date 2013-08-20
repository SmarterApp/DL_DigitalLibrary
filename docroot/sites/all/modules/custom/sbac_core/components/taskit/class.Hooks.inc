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
        'name' => 'resource_submitted',
        'description' => t('Resource has been submitted for review.'),
        'class' => 'ResourceSubmitted',
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
    );

    foreach ($types as &$type) {
      $type['file'] = $path . 'class.' . $type['class'] . '.inc';
    }

    return $types;
  }
}



