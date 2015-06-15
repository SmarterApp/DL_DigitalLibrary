<?php

/**
 * Returns the user's full name.
 * @param  [type]  $account   [description]
 * @param  boolean $show_last [description]
 * @return [type]             [description]
 */
function full_name($account, $show_last = TRUE) {
  if (is_numeric($account)) {
    $account = user_load($account);
  }
  else {
    // force reload for full account data
    $account = user_load($account->uid);
  }

  // build first/last
  $name = '';
  if (isset($account->field_first_name) && $first = field_entity_value($account, 'field_first_name')) {
    $name .= $first;

    if ($show_last && isset($account->field_last_name) && $last = field_entity_value($account, 'field_last_name')) {
      $name .= ' ' . $last;
    }
  }
  // default to username  
  else {
    $name = $account->name;
  }

  return $name;
}