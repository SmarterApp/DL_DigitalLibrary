<?php

/**
 * Checks whether the  user has a review for the node.
 * @return [type] [description]
 */
function user_has_review($nid, $uid) {
  $id = db_select('eck_review', 'er')
        ->fields('er', array('id'))
        ->condition('type', 'end_use')
        ->condition('node_id', $nid)
        ->condition('uid', $uid)
        ->condition('status', 1)
        ->execute()
        ->fetch();

  return (bool) $id;
}

/**
 * Returns rendered Review entities.
 * @param  [type] $node   [description]
 * @param  [type] $sortby [description]
 * @param  [type] $page   [description]
 * @return [type]         [description]
 */
function review_load_more($node, $sortby, $page) {
  $page_size = 10;
  $offset = $page * $page_size;

  $result = FALSE;
  if ($sortby == 'newest') {
    $result = db_select('eck_review', 'er')
              ->fields('er', array('id'))
              ->condition('type', 'end_use')
              ->condition('node_id', $node->nid)
              ->condition('status', 1)
              ->orderBy('created', 'DESC')
              ->range($offset, $page_size)
              ->execute();
  }
  elseif ($sortby == 'helpful') {

  }

  $output = '';
  if ($result) {
    foreach ($result as $row) {
      $entity = entity_load_single('review', $row->id);
      $entity_renderable = entity_view('review', array($entity));
      $output .= render($entity_renderable);
    }
  }

  return $output;
}