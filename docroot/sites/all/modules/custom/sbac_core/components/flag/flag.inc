<?php

/**
 * Access callback for custom Flag operations.
 */
function flag_access($op, $entity_type, $entity_id, $account = NULL) {
  if (is_null($account)) {
    global $user;
    $account = $user;
  }

  if ($op == 'create flag') {
    $query = "  SELECT    id
                FROM      eck_flag 
                WHERE     target_type = 'review'
                AND       target_id = :target_id
                AND       uid = :uid
             ";

    $id = db_query($query, array(
            ':target_id' => $entity_id,
            ':uid' => $account->uid
          ))->fetchField();

    return !((bool) $id);
  }
}

function get_user_review_flag() {
  // return !((bool) $id)
}