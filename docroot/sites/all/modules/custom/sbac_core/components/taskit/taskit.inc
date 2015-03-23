<?php

/**
 * Access callback for /user/%user/notifications/read
 * @param  [type] $account [description]
 * @return [type]          [description]
 */
function taskit_mark_all_read_access($account) {
  global $user;

  return ($account->uid == $user->uid);
}

/**
 * Menu callback for /user/%user/notifications/read
 * @param  [type] $account [description]
 * @return [type]          [description]
 */
function taskit_mark_all_read($account) {
  // first we make sure that all tasks are marked as read in 'core'
  $query = "  UPDATE      taskit t
              INNER JOIN  taskit_user_owner tuo
                ON        tuo.task_id = t.task_id
                AND       tuo.user_id = :uid
              SET         t.viewed = :time
              WHERE       t.viewed = 0
           ";

  db_query($query, array(
    ':uid' => $account->uid,
    ':time' => REQUEST_TIME,
  ));

  // if we're using user-specific visibility, we should add appropriate records
  switch (variable_get('taskit_visibility', 'global')) {
    case 'user':
      // pull up all 'viewed' records that don't have a corresponding record in
      // taskit_viewed, and add the record
      $query = "  SELECT      t.task_id
                  FROM        taskit t
                  INNER JOIN  taskit_user_owner tuo
                    ON        tuo.task_id = t.task_id
                    AND       tuo.user_id = :uid
                  LEFT JOIN   taskit_viewed tv
                    ON        tv.task_id = t.task_id
                    AND       tv.user_id = :uid
                  WHERE       t.viewed > 0
                  AND         tv.user_id IS NULL
               ";

        $result = db_query($query, array(
          ':uid' => $account->uid,
        ));

        foreach ($result as $row) {
          db_query("INSERT INTO taskit_viewed (task_id, user_id) VALUES (:task_id, :uid)", array(
            ':task_id' => $row->task_id,
            ':uid' => $account->uid,
          ));
        } 

      break;
  }

  // reset unread count
  db_update('taskit_user_unread_notifications_count')
    ->fields(array('count' => 0))
    ->condition('uid', $account->uid)
    ->execute();
}