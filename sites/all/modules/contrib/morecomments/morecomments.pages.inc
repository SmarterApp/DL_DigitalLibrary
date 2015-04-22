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
    $order_direction = 'ASC';

    // Compatibility with Comment goodness module
    if (module_exists('comment_goodness')) {
      $sort = variable_get('comment_default_sorting_' . $node->type, comment_goodness_OLDER_FIRST);
      $order_direction = ($sort == comment_goodness_NEWER_FIRST) ? 'DESC' : 'ASC';
    }

    // Compatibility with Sort Comments module
    if (module_exists('sort_comments')) {
      $sort = variable_get('comment_default_sorting_' . $node->type, SORT_COMMENTS_OLDER_FIRST);
      $order_direction = ($sort == SORT_COMMENTS_NEWER_FIRST) ? 'DESC' : 'ASC';
    }

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
    }

    if ($mode === COMMENT_MODE_FLAT) {
      $query->orderBy('c.cid', $order_direction);
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
