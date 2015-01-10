<?php

/**
 * @file
 * Drush-related callbacks for SBAC User module.
 */

/**
 * Implementation of hook_drush_command()
 *
 */
function sbac_user_drush_command() {
  $items = array();

  $items['sbac-user-accept-terms'] = array(
    'description' => "Accept terms of service for test users on sbacloadtest environment.",
    'examples' => array(
      'drush sbac-user-accept-terms',
    ),
    'callback' => 'drush_sbac_user_accept_terms',
  );

  $items['sbac-user-notifications-count'] = array(
    'description' => "Add values to the taskit user notifications table.",
    'examples' => array(
      'drush sbac-user-notifications-count',
    ),
    'callback' => 'drush_sbac_user_notifications_count',
  );

  return $items;
}


/**
 * Accept the terms of service for the test users that we created
 * on the sbacloadtest environment.
 */
function drush_sbac_user_accept_terms() {
  $sql = "SELECT * FROM {users} WHERE name like 'appnovation_%'";
  $result = db_query($sql);
  foreach ($result as $row) {
    $insert = "INSERT INTO {legal_accepted} VALUES (NULL, 30, 1, 'en', " . $row->uid . ", " . time() . ")";
    db_query($insert);
  }
}

/**
 * Update the user notifications count table.
 */
function drush_sbac_user_notifications_count() {
  ini_set('memory_limit', '1048M');
  $sql = "select count(u.uid)
    from users u
    left outer join taskit_user_unread_notifications_count t on u.uid = t.uid
    WHERE t.uid IS NULL;";
  $result = db_query($sql);
  foreach ($result as $row) {
    $user = user_load($row->uid);
    if ($user) {
      $taskit_counts = taskit_count_tasks($user->uid, array_keys($user->roles), TRUE);
      drush_sbac_user_update_user_notifications_count($user->uid, $taskit_counts['_no_role_']);
      unset($taskit_counts);
    }
    unset($user);
  }
}

/**
 * Update the user notifications count.
 *
 * @param $uid
 * @throws \Exception
 */
function drush_sbac_user_update_user_notifications_count($uid, $count) {
  db_insert('taskit_user_unread_notifications_count')
    ->fields(array(
      'uid' => $uid,
      'count' => $count,
    ))
    ->execute();
}