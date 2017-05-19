<?php

/**
 * Creates the moderation list.
 *
 * @return string
 */
function sbac_flag_moderation() {
  drupal_add_css(drupal_get_path('module', 'sbac_flag') . '/css/sbac_flag.css');
  drupal_add_js(drupal_get_path('module', 'sbac_flag') . '/js/sbac_flag.js');
  drupal_set_title('');

  $result = sbac_flag_get_flags();
  $count = 0;
  $offset = 0;

  $list_output = sbac_flag_moderation_output($result, $count, $offset);
  $_SESSION['sbac-flag']['count'] = $count;
  $load_more_button = NULL;
  if ($count > SBAC_FLAG_MODERATION_COUNT && !isset($list_output['remove_button'])) {
    // create load more button.
    $load_more_button = '<a href="#" offset="' . $offset . '" class="load-more button green" id="sbac-load-more">Show More Items</a>';
  }

  $output = '';
  if ($list_output) {
    ctools_include('modal');
    ctools_include('ajax');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
    drupal_add_library('system', 'drupal.ajax');
    $output = theme('sbac_flag_moderation', array('list_output' => $list_output['list_output'], 'load_more' => $load_more_button));
  }

  return $output;
}

/**
 * Loads more flag content into the moderation page.
 */
function sbac_flag_load_more() {
  $list_output = '';
  $offset = $_POST['offset'];
  $hash_loading = $_POST['hash_load'];
  ($hash_loading == 'true' ? $hash_loading = TRUE : $hash_loading = FALSE);
  $remove_button = FALSE;
  if ($offset) {
    $result = sbac_flag_get_flags();
    $count = 0;
    $list_output = sbac_flag_moderation_output($result, $count, $offset, TRUE, $hash_loading);
    if (isset($list_output['remove_button'])) {
      $remove_button = TRUE;
    }
    $_SESSION['load_more']['moderation']['page'] = $offset;
  }
  $output = array('list_output' => $list_output['list_output'], 'offset' => $offset, 'remove_button' => $remove_button);
  print drupal_json_encode($output);
  exit;
}

/**
 * Gets a set of flags.
 */
function sbac_flag_get_flags() {
  global $user;

  $query = db_select('eck_flag', 'ef');
  $query->fields('ef');
  $query->orderBy('ef.being_moderated', 'DESC');
  $query->orderBy('ef.created', 'ASC');
  $query->condition(db_or()->condition('ef.being_moderated', $user->uid)->condition('ef.being_moderated', 0));
  $query->condition('ef.resolved', 0);
  $result = $query->execute();
  return $result;
}

/**
 * Returns moderation output.
 *
 * @param $result
 * @param $count
 * @return string
 */
function sbac_flag_moderation_output($result, &$count, &$offset = NULL, $load_more_ajax = FALSE, $hash_load_more = FALSE) {
  global $user;
  $list_output = '';
  $sorted_flags = array();

  if (!$load_more_ajax && isset($_SESSION['load_more']['moderation']['page'])) {
    $start = 0;
    $end = $_SESSION['load_more']['moderation']['page'] * SBAC_FLAG_MODERATION_COUNT;
    $offset = $_SESSION['load_more']['moderation']['page'];
  }
  else if ($hash_load_more) {
    $start = 0;
    $end = ($offset + 1) * SBAC_FLAG_MODERATION_COUNT;
    $offset++;
  }
  else if ($offset) {
    $start = SBAC_FLAG_MODERATION_COUNT * $offset;
    $end = $start + SBAC_FLAG_MODERATION_COUNT;
    $offset++;
  }
  else {
    $start = 0;
    $end = SBAC_FLAG_MODERATION_COUNT;
    $offset = 1;
  }

  // Loop through all flags, determine access,
  // determine urgency then create output.
  foreach ($result as $row) {
    $node = FALSE;
    $eck_review = FALSE;
    $eck_review_wrapper = FALSE;
    if ($row->type == 'resource') {
      // resource node flag
      $node = node_load($row->nid);
    }
    else if ($row->type == 'topic') {
      // topic or comment flag
      continue;
      /*
      $node = node_load($row->nid);
      $row->type = $row->target_type;
      */
    }
    else if ($row->type == 'review_end_use') {
      // review flag
      $eck_review = entity_load_single('review', $row->target_id);
      $eck_review_wrapper = entity_metadata_wrapper('review', $row->target_id);
      if ($eck_review) {
        $nid = $eck_review_wrapper->node_id->value();
        $node = node_load($nid);
      }
    }

    if ($node) {
      unset($node->eck_flag);
      unset($node->eck_review);
      unset($node->eck_review_title);
      $access = sbac_flag_determine_access_for_user($node, $user->uid);
      if ($access) {
        // determine urgency
        $variables = array();
        $urgent = sbac_flag_create_flag_content($row, $node, $eck_review, $eck_review_wrapper, $variables);
        if ($row->being_moderated) {
          $key = 'being_moderated';
        }
        else {
          if ($urgent) {
            $key = 'urgent';
          }
          else {
            $key = 'y_urgent';
          }
        }
        $sorted_flags[$key][$row->type][$node->nid]['node'] = $node;
        $sorted_flags[$key][$row->type][$node->nid]['variables'] = $variables;
        $count++;
      }
    }
  }

  $count = 0;
  ksort($sorted_flags);
  $outputted = array();

  // Remove dupicate nodes from y_urgent, as they already show up on urgent.
  if (isset($sorted_flags['y_urgent']['resource']) && isset($sorted_flags['urgent']['resource'])) {
    $unique_flags = array_diff_key($sorted_flags['y_urgent']['resource'], $sorted_flags['urgent']['resource']);
    $sorted_flags['y_urgent']['resource'] = $unique_flags;
  }
  if (isset($sorted_flags['y_urgent']['review_end_use']) && isset($sorted_flags['urgent']['review_end_use'])) {
    $unique_flags = array_diff_key($sorted_flags['y_urgent']['review_end_use'], $sorted_flags['urgent']['review_end_use']);
    $sorted_flags['y_urgent']['review_end_use'] = $unique_flags;
  }
  if (isset($sorted_flags['y_urgent']['topic']) && isset($sorted_flags['urgent']['topic'])) {
    $unique_flags = array_diff_key($sorted_flags['y_urgent']['topic'], $sorted_flags['urgent']['topic']);
    $sorted_flags['y_urgent']['topic'] = $unique_flags;
  }
  if (isset($sorted_flags['y_urgent']['comment']) && isset($sorted_flags['urgent']['comment'])) {
    $unique_flags = array_diff_key($sorted_flags['y_urgent']['comment'], $sorted_flags['urgent']['comment']);
    $sorted_flags['y_urgent']['comment'] = $unique_flags;
  }

  foreach ($sorted_flags as $type => $rows) {
    foreach ($rows as $flag_type => $nodes) {
      foreach ($nodes as $nid => $element) {
        $node = $element['node'];
        if (!in_array($type . '::' . $node->nid, $outputted)) {
          $count++;
          if ($count > $start && $count <= $end) {
            $variables = $element['variables'];
            if ($node && $variables) {
              if ($node->type == 'resource') {
                $list_output .= theme('sbac_flag_list_card', array('node' => $node, 'flag_content' => $variables));
              }
              elseif ($node->type == 'topic') {
                $list_output .= theme('sbac_flag_list_card_topic', array('node' => $node, 'flag_content' => $variables));
              }
            }
          }
        }
        $outputted[] = $type . '::' . $flag_type . '::' . $node->nid;
      }
    }
  }

  if ($count < $end) {
    $return['remove_button'] = TRUE;
  }
  $return['list_output'] = $list_output;

  return $return;
}

/**
 * Determine if this row is urgent or not.
 *
 * @param $row
 * @param $node
 * @param $eck_flag
 * @param $eck_review
 * @return bool
 */
function sbac_flag_create_flag_content($row, $node, $eck_review, $eck_review_wrapper, &$variables) {
  $urgent = FALSE;

  $variables['eck_flag'] = (array) $row;

  if ($row->urgent) {
    $variables['eck_flag']['urgent'] = $row->urgent;
    $urgent = TRUE;
  }

  $eck_flag = entity_load_single('flag', $row->id);
  $eck_flag_wrapper = FALSE;
  if ($eck_flag) {
    $eck_flag_wrapper = entity_metadata_wrapper('flag', $eck_flag);
  }

  if ($eck_review) {
    if ($eck_flag_wrapper) {
      $urgent = sbac_flag_determine_urgent($eck_flag_wrapper->field_issue_type->value(), 'review');
    }
  }
  else {
    $urgent = sbac_flag_determine_urgent($row->flag_selected);
  }


  $variables['eck_flag']['urgent'] = $urgent;
  if ($eck_flag) {
    $issue_type = field_entity_value($eck_flag, 'field_issue_type');
    if ($issue_type == 'pii') {
      $variables['eck_flag']['urgent'] = 1;
    }
  }

  if ($eck_review) {
    $variables['eck_review']['title'] = ($eck_review_wrapper->title->value() ? $eck_review_wrapper->title->value() : $node->title);
  }

  if ($row->type == 'topic') {
    $user_tooltip = sbac_forum__api__get_authpane_hoverover($node->uid);
    $user = entity_metadata_wrapper('user', $node->uid);
    $account = user_load($node->uid);
    $account_renderable = user_view($account, 'tooltip');

    $variables['eck_post']['topic_author'] = $user_tooltip;
    $variables['eck_post']['topic_author_picture'] = render($account_renderable['user_picture']);
    $variables['eck_post']['post_body'] = $node->body['und'][0]['safe_value'];
  }

  if ($row->type == 'comment') {
    $post = entity_metadata_wrapper('comment', $row->target_id);
    try {
      $user_tooltip = sbac_forum__api__get_authpane_hoverover($post->author->uid->value());
      $account = user_load($post->author->uid->value());
      $account_renderable = user_view($account, 'tooltip');

      $variables['eck_post']['topic_author'] = $user_tooltip;
      $variables['eck_post']['topic_author_picture'] = render($account_renderable['user_picture']);
      $variables['eck_post']['post_body'] = $post->comment_body->value();
    } catch (EntityMetadataWrapperException $e) {
    }
  }

  if ($variables['eck_flag']['urgent']) {
    $variables['eck_flag']['display_status'] = 'Needs Urgent Moderation';
    $variables['eck_flag']['display_status_css'] = 'urgent';
    $urgent = TRUE;
  }
  else {
    $variables['eck_flag']['display_status'] = 'Needs Moderation';
    $variables['eck_flag']['display_status_css'] = '';
  }

  if ($row->being_moderated) {
    $variables['eck_flag']['display_status'] = 'Being Moderated';
    $variables['eck_flag']['display_status_css'] = '';
    if ($row->type == 'topic' || $row->type == 'comment') {
      $path_alias = drupal_get_path_alias('node/' . $node->nid);
      $url = l('Continue Moderation', $path_alias, array(
        'attributes' => array(
          'class' => array(
            'button',
            'blue',
          ),
        ),
        'query' => array(
          'flag' => 'resolve-' . $row->type . '-flags',
          'cid' => ($node->nid == $row->target_id ? 0 : $row->target_id),
        ),
        'fragment' => 'review-moderate_flag',
      ));
      $variables['eck_flag']['button'] = $url;

    }
    else {
      if ($eck_review) {
        $url = l('Continue Moderation', $node->path['alias'], array('attributes' => array('class' => array('button', 'blue')), 'query' => array('flag' => 'resolve-resource-review-flags', 'review' => $eck_review->id, 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
        $variables['eck_flag']['button'] = $url;
        $variables['eck_flag']['title_href'] = url($node->path['alias'], array('attributes' => array('class' => array('button', 'blue')), 'query' => array('flag' => 'resolve-resource-review-flags', 'review' => $eck_review->id, 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
      }
      else {
        $url = l('Continue Moderation', 'node/' . $node->nid . '/edit', array('attributes' => array('class' => array('button', 'blue')), 'query' => array('flag' => 'resolve-resource-flags', 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
        $variables['eck_flag']['button'] = $url;
        $variables['eck_flag']['title_href'] = url('node/' . $node->nid . '/edit', array('attributes' => array('class' => array('button', 'blue')), 'query' => array('flag' => 'resolve-resource-flags', 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
      }
    }
  }
  else {
    if ($row->type == 'resource' || $row->type == 'review_end_use') {
      $moderation_button = l(t('Start Moderation'), 'sbac-flag/nojs/start-moderation', array(
        'attributes' => array(
          'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-start-moderation',
          'id' => 'sbac-flag-start-moderation'
        ),
        'query' => array(
          'nid' => $node->nid,
          'eck_review' => ($eck_review ? $eck_review->id : 0),
          'forum_type' => 0,
          'cid' => 0,
        ),
      ));
    }
    elseif ($row->type == 'topic' || $row->type == 'comment') {
      $moderation_button = l(t('Start Moderation'), 'sbac-flag/nojs/start-moderation', array(
        'attributes' => array(
          'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-start-moderation',
          'id' => 'sbac-flag-start-moderation'
        ),
        'query' => array(
          'eck_review' => 0,
          'forum_type' => $row->type,
          'nid' => $node->nid,
          'cid' => ($node->nid == $row->target_id ? 0 : $row->target_id),
        ),
      ));
    }
    $js_settings = array(
      'sbac-flag-start-moderation' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 600,
          'height' => 230,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting');
    $variables['eck_flag']['button'] = $moderation_button;

    if ($eck_review) {
      $url = url($node->path['alias'], array('query' => array('flag' => 'view-resource-review-flags', 'review' => $eck_review->id), 'fragment' => 'review-Moderate_flag'));
      $variables['eck_flag']['title_href'] = $url;
    }
    else {
      if (isset($node->path)) {
        $url = url($node->path['alias'], array('query' => array('flag' => 'view-resource-flags'), 'fragment' => 'review-Moderate_flag'));
        $variables['eck_flag']['title_href'] = $url;
      }
      else {
        $path = drupal_lookup_path('alias', 'node/' . $node->nid);
        $url = url($path, array('query' => array('flag' => 'view-topic-flags')));
        $variables['eck_flag']['title_href'] = $url;
      }
    }
  }

  return $urgent;
}