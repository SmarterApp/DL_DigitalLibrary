<?php

/**
 * @file
 * Render function for morecomments module.
 */

/**
 * Custom implementation of comment_render from comment.module.
 */
function morecomments_comment_render($nid, $page) {
  $node = node_load($nid);
  $page = intval($page);

  if (empty($node)) {
    return;
  }
  $output = '';

  $GLOBALS['devel_shutdown'] = FALSE;

  if (($node->comment_count && user_access('access comments')) || user_access('administer comments')) {
    $mode = variable_get('comment_default_mode_' . $node->type, COMMENT_MODE_THREADED);
    $comments_per_page = variable_get('comment_default_per_page_' . $node->type, 50);

    // Code grabbed from comment_get_thread.
    $query = db_select('comment', 'c')
      ->fields('c', array('cid'))
      ->condition('c.nid', $node->nid)
      ->addTag('node_access')
      ->addTag('comment_filter')
      ->addMetaData('node', $node)
      ->range($comments_per_page * $page, $comments_per_page);

    if (!user_access('administer comments')) {
      $query->condition('c.status', COMMENT_PUBLISHED);
      $count_query->condition('c.status', COMMENT_PUBLISHED);
    }
    if ($mode === COMMENT_MODE_FLAT) {
      $query->orderBy('c.cid', 'ASC');
    }
    else {
      $query->addExpression('SUBSTRING(c.thread, 1, (LENGTH(c.thread) - 1))', 'torder');
      $query->orderBy('torder', $order_direction);
    }

    $cids = $query->execute()->fetchCol();
    if ($cids) {
      $comments = comment_load_multiple($cids);
      comment_prepare_thread($comments);
      $build = comment_view_multiple($comments, $node);
      $additions['comments'] = $build;
    }

    // Render the output without pager.
    $output = drupal_render($additions);

    $next = $page + 1;
    $num_of_comments = db_query('SELECT comment_count FROM {node_comment_statistics} WHERE nid = :nid', array('nid' => $node->nid))->fetchField();

    if ($comments_per_page * $next < $num_of_comments) {
      $output .= theme('morecomments_pager', array('nid' => $nid, 'next_page' => $next, 'node_type' => $node->type));
    }
  }

  print $output;
  exit();
}
