<?php

/**
 * Checks whether the  user has a review for the node.
 * 
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
 * Returns the total number of reviews on given node id;
 * 
 * @param  [type] $nid [description]
 * @return [type]      [description]
 */
function total_reviews($nid) {
  $count_query = "  SELECT    COUNT(id)
                    FROM      eck_review
                    WHERE     type = 'end_use'
                    AND       node_id = :node_id
                    AND       status = 1
                 ";

  return db_query($count_query, array(':node_id' => $nid))->fetchField();
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
    $query = "  SELECT    er.id,
                          SUM(IF(v.value = 1, 1, 0)) AS `yes`,
                          (
                            SUM(IF(v.value = 1, 1, 0))  -- YES
                                /                       --   divided by...
                            SUM(1)                      -- TOTAL
                          ) AS `percent`                --   = percent (decimal)
                FROM      eck_review er
                LEFT JOIN votingapi_vote v
                  ON      er.id = v.entity_id
                  AND     v.entity_type = 'review'
                WHERE     er.type = 'end_use'
                AND       er.node_id = :node_id
                AND       er.status = 1
                GROUP BY  er.id
                ORDER BY  `percent`     DESC, 
                          `yes`         DESC,
                          er.created    DESC
                LIMIT     " . $offset . ", " . $page_size . "
             ";

    $args = array(
      ':node_id' => $node->nid,
    );

    $result = db_query($query, $args);
  }

  $output = '';
  if ($result) {
    foreach ($result as $row) {
      $entity = entity_load_single('review', $row->id);
      $entity_renderable = entity_view('review', array($entity));
      $output .= render($entity_renderable);
    }
  }

  // do we show the 'load more reviews' button?
  if ($offset + $page_size < total_reviews($node->nid)) {
    $url = 'load_more/review/' . $node->nid . '/' . $sortby . '/' . ++$page;

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'button',
          'radius',
        ),
        'id' => 'reviews-load-more',
      ),
    );

    $output .= l('Show More Reviews', $url, $options);
  }

  return $output;
}

/**
 * Loads more reviews through an AJAX call.
 * 
 * @param  [type] $node   [description]
 * @param  [type] $sortby [description]
 * @param  [type] $page   [description]
 * @return [type]         [description]
 */
function review_load_more_ajax($node, $sortby, $page) {
  $output = review_load_more($node, $sortby, $page);

  $commands = array();
  $commands[] = ajax_command_replace('#reviews-load-more', $output);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
}