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
    $load_more_button = '<a href="#" offset="' . $offset . '" class="load-more button green" id="sbac-load-more">Load More</a>';
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
 * Creates the content necassary for the card output.
 *
 * @param $row
 * @param $node
 * @param $eck_review
 */
function sbac_flag_list_content($row, $node, $eck_flag, $eck_review) {
  $moderation_button = l(t('Start Moderation'), 'sbac-flag/nojs/start-moderation', array(
    'attributes' => array(
      'class' => 'ctools-use-modal blue button use-ajax ctools-modal-sbac-flag-start-moderation',
      'id' => 'sbac-flag-start-moderation'
    ),
    'query' => array(
      'nid' => $node->nid,
      'eck_review' => ($eck_review ? $eck_review->id : 0),
    ),
  ));

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

  $node->eck_flag->button = $moderation_button;
  if ($row->being_moderated) {
    $node->eck_flag->display_status = 'Being Moderated';
    $node->eck_flag->display_status_css = '';
    if ($eck_review) {
      $url = l('Continue Moderation', $node->path['alias'], array('attributes' => array('class' => array('button')), 'query' => array('flag' => 'resolve-resource-review-flags', 'review' => $eck_review->id), 'fragment' => 'review-Moderate_flag'));
      $node->eck_flag->button = $url;
    }
    else {
      $url = l('Continue Moderation', 'node/' . $node->nid . '/edit', array('attributes' => array('class' => array('button')), 'query' => array('flag' => 'resolve-resource-flags'), 'fragment' => 'review-Moderate_flag'));
      $node->eck_flag->button = $url;
    }
  }
  return $node;
}

/**
 * Loads more flag content into the moderation page.
 */
function sbac_flag_load_more() {
  $list_output = '';
  $offset = $_POST['offset'];
  $remove_button = FALSE;
  if ($offset) {
    $result = sbac_flag_get_flags();
    $count = 0;
    $list_output = sbac_flag_moderation_output($result, $count, $offset);
    if (isset($list_output['remove_button'])) {
      $remove_button = TRUE;
    }
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
//  $query->orderBy('ef.urgent', 'DESC');
  $query->orderBy('ef.created', 'ASC');
  $query->groupBy('ef.target_id');
  $query->groupBy('ef.nid');
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
function sbac_flag_moderation_output($result, &$count, &$offset = NULL) {
  global $user;
  $display_nodes = array();
  $list_output = '';

  if ($offset) {
    $start = SBAC_FLAG_MODERATION_COUNT * $offset;
    $end = $start + SBAC_FLAG_MODERATION_COUNT;
    $offset++;
  }
  else {
    $start = 0;
    $end = SBAC_FLAG_MODERATION_COUNT;
    $offset = 1;
  }

  foreach ($result as $row) {
    $node = FALSE;
    $eck_review = FALSE;
    $eck_flag = entity_load_single('flag', $row->id);
    if ($row->type == 'resource') {
      // resource node flag
      $node = node_load($row->nid);
      unset($node->eck_flag);
      unset($node->eck_review);
      unset($node->eck_review_title);
    }
    else {
      // review flag
      $eck_review = entity_load_single('review', $row->target_id);
      if ($eck_review) {
        $nid = field_entity_value($eck_review, 'node_id');
        $node = node_load($nid);
      }
    }

    if ($node) {
      $access = sbac_flag_determine_access_for_user($node, $user->uid);
      if ($access) {
        // determine urgency
        $urgent = sbac_flag_is_urgent($row, $node, $eck_flag, $eck_review);
        if ($urgent) {
          $sorted_flags['urgent'][$count]['row'] = $row;
          $sorted_flags['urgent'][$count]['node'] = $node;
          $sorted_flags['urgent'][$count]['eck_flag'] = $eck_flag;
          $sorted_flags['urgent'][$count]['eck_review'] = $eck_review;
        }
        else {
          $sorted_flags['y_urgent'][$count]['row'] = $row;
          $sorted_flags['y_urgent'][$count]['node'] = $node;
          $sorted_flags['y_urgent'][$count]['eck_flag'] = $eck_flag;
          $sorted_flags['y_urgent'][$count]['eck_review'] = $eck_review;
        }
        $count++;
      }
    }
    unset($node);
  }

  $count = 0;
  ksort($sorted_flags);
  foreach ($sorted_flags as $type => $rows) {
    foreach ($rows as $row) {
      $count++;
      if ($count > $start && $count <= $end) {
        $node = $row['node'];
        $eck_review = $row['eck_review'];
        $eck_flag = $row['eck_flag'];
        $row = $row['row'];
        if ($node) {
          $display_node = sbac_flag_list_content($row, $node, $eck_flag, $eck_review);
          $list_output .= theme('sbac_flag_list_card', array('node' => $display_node));
          $display_nodes[] = $display_node;
        }
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
function sbac_flag_is_urgent($row, &$node, $eck_flag, $eck_review) {
  $urgent = FALSE;

  $node->eck_flag = $row;
  if ($eck_review) {
    $node->eck_review = $eck_review;
    $title = field_entity_value($eck_review, 'title');
    $node->eck_review_title = $title;
    $issue_type = field_entity_value($eck_flag, 'field_issue_type');
    if ($issue_type == 'pii') {
      $urgent = TRUE;
      $node->eck_flag->urgent = 1;
    }
  }

  if ($node->eck_flag->urgent) {
    $node->eck_flag->display_status = 'Needs Urgent Moderation';
    $node->eck_flag->display_status_css = 'urgent';
    $urgent = TRUE;
  }
  else {
    $node->eck_flag->display_status = 'Needs Moderation';
    $node->eck_flag->display_status_css = '';
  }

  return $urgent;
}