<?php

/**
 * Creates the moderation list.
 *
 * @return string
 */
function sbac_flag_moderation() {
  $output = '';

  //loop through all flags in sbac_flag, determine access, display results.
  // only display 7, count all.
  // list view only.
  $query = db_select('eck_flag', 'ef');
  $query->fields('ef');
  $query->orderBy('ef.urgent', 'DESC');
  $query->orderBy('ef.created', 'ASC');
  $result = $query->execute();
  foreach ($result as $row) {
    $node = node_load($row->nid);
    if ($node) {

    }
  }

  return $output;
}