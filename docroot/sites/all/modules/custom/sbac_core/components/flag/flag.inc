<?php

/**
 * Access callback for custom Flag operations.
 */
function flag_access($op, $entity_type, $entity_id, $account = NULL) {
  if ($op == 'create flag') {
    
    
    $id = db_query($query, array('entity_id' => $entity_id))->fetchField();
  }
}