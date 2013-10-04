<?php

/**
 * Access callback for custom Flag operations.
 */
function flag_access($op, $entity_type, $entity_id, $account = NULL) {
  return TRUE;

  if ($op == 'create flag') {
    $query = "  SELECT    id
                FROM      eck_flag 
                WHERE     target_type = 'review'
                AND       target_id = :target_id

             ";

    $id = db_query($query, array('target_id' => $entity_id))->fetchField();

    return !((bool) $id);
  }
}