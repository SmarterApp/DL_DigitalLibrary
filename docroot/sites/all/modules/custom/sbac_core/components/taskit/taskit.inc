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
}