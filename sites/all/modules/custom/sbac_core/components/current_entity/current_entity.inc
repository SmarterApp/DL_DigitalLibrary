<?php

/**
 * Checks for the node page, and loads the node
 */
function current_node() {
  if (match_uri('node/[0-9]+') && $node = node_load((int) arg(1))) {
    return $node;
  }
  
  return FALSE;
}

/**
 * Checks for user page, loads the user
 */
function current_user() {
  if (match_uri('user/[0-9]+') && $account = user_load((int) arg(1))) {
    return $account;
  }
  
  return FALSE;
}

/**
 * Checks for feedback page, and loads the entity
 */
function current_feedback() {
  if (match_uri('feedback/gate_keeper/\d+')) {
    return entity_load_single('feedback', arg(2));
  }

  return FALSE;
}