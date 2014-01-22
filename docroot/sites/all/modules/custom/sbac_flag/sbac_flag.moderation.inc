<?php

/**
 * Creates the moderation list.
 *
 * @return string
 */
function sbac_flag_moderation() {
  drupal_add_css(drupal_get_path('module', 'sbac_flag') . '/css/sbac_flag.css');

  global $user;
  $display_nodes = array();
  $list_output = '';
  $output = '';

  //loop through all flags in eck_flag, determine access, display results.
  // only display 7, count all.
  // list view only.
  $query = db_select('eck_flag', 'ef');
  $query->fields('ef');
  $query->orderBy('ef.urgent', 'DESC');
  $query->orderBy('ef.created', 'ASC');
  $query->groupBy('ef.target_id');
  $query->groupBy('ef.nid');
  $query->condition(db_or()->condition('ef.being_moderated', $user->uid)->condition('ef.being_moderated', 0));
  $result = $query->execute();
  $count = 0;
  foreach ($result as $row) {
    $node = FALSE;
    $eck_review = FALSE;
    $eck_flag = entity_load_single('flag', $row->id);
    if ($row->type == 'resource') {
      // resource node flag
      $node = node_load($row->nid);
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
        $count++;
        if (count($display_nodes) < SBAC_FLAG_MODERATION_COUNT) {
          $display_node = sbac_flag_list_content($row, $node, $eck_flag, $eck_review);
          $list_output .= theme('sbac_flag_list_card', array('node' => $display_node));
          $display_nodes[] = $display_node;
        }
      }
    }
  }

  $_SESSION['sbac-flag']['count'] = $count;
  if ($count > SBAC_FLAG_MODERATION_COUNT) {
    // create load more button.
    $var = '';
  }

  if ($display_nodes) {
    ctools_include('modal');
    ctools_include('ajax');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
    drupal_add_library('system', 'drupal.ajax');
    $output = theme('sbac_flag_moderation', array('list_output' => $list_output));
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
  $node->eck_flag = $row;
  if ($eck_review) {
    $node->eck_review = $eck_review;
    $title = field_entity_value($eck_review, 'title');
    $node->eck_review_title = $title;
    $issue_type = field_entity_value($eck_flag, 'field_issue_type');
    if ($issue_type == 'pii') {
      $node->eck_flag->urgent = 1;
    }
  }

  if ($node->eck_flag->urgent) {
    $node->eck_flag->display_status = 'Needs Urgent Moderation';
    $node->eck_flag->display_status_css = 'urgent';
  }
  else {
    $node->eck_flag->display_status = 'Needs Moderation';
  }

  $moderation_button = l(t('Start Moderation'), 'sbac-flag/nojs/start-moderation', array(
    'attributes' => array(
      'class' => 'ctools-use-modal button use-ajax ctools-modal-sbac-flag-start-moderation',
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
        'height' => 160,
      ),
    ),
  );
  drupal_add_js($js_settings, 'setting');

  $node->eck_flag->button = $moderation_button;
  if ($row->being_moderated) {
    $node->eck_flag->display_status = 'Being Moderated';
    if ($eck_review) {
      $url = l('Continue Moderation', $node->path['alias'], array('attributes' => array('class' => array('button')), 'query' => array('flag' => 'resolve-resource-review-flags'), 'fragment' => 'something-Moderate_flag'));
      $node->eck_flag->button = $url;
    }
    else {
      $url = l('Continue Moderation', 'node/' . $node->nid . '/edit', array('attributes' => array('class' => array('button')), 'query' => array('flag' => 'resolve-resource-flags'), 'fragment' => 'something-Moderate_flag'));
      $node->eck_flag->button = $url;
    }
  }
  return $node;
}
