<?php

/**
 * Creates the moderation list.
 *
 * @return string
 */
function sbac_flag_moderation() {
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
  $query->groupBy('ef.target_type');
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
      'eck_review' => ($eck_review ? 1 : 0),
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
    $node->eck_flag->button = '<a href="" class="button">Continue Moderation</a>';
  }
  return $node;
}

/**
 * @param bool $js
 */
function sbac_flag_start_moderation($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to start resource moderation';
    if (isset($_GET['eck_review'])) {
      $title = 'You are about to start resource review moderation';
    }

    $goto_edit = FALSE;
    if (isset($_GET['goto_edit'])) {
      $goto_edit = TRUE;
    }

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
      'eck_review' => $_GET['eck_review'],
      'goto_edit' => $goto_edit,
    );

    $output = ctools_modal_form_wrapper('sbac_flag_start_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Review Flags') {
        $node = node_load($form_state['values']['nid']);
        if (isset($form_state['values']['goto_edit'])) {
          $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('query' => array('flag' => 'moderate-flags'), 'fragment' => 'moderate-flags'));
        }
        else {
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'view-resource-flags'), 'fragment' => 'review-Moderate_flag'));
        }
      }
      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
        $node = node_load($form_state['values']['nid']);
        sbac_flag_set_being_moderated($node, $form_state['eck_review']);
        $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('fragment' => 'resolve-flags'));
      }
    }
    print ajax_render($output);
    exit();
  }
  else {
    return;
  }
}

/**
 * Start moderation form.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_flag_start_moderation_form($form, $form_state) {
  $form = array();

  $form['eck_review'] = array(
    '#type' => 'hidden',
    '#value' => $form_state['eck_review'],
  );

  $form['goto_edit'] = array(
    '#type' => 'hidden',
    '#value' => $form_state['goto_edit'],
  );

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $form_state['nid'],
  );

  $form['submit_description'] = array(
    '#markup' => '<p>' . t("
    If you start moderation, you will have to resolve the flags in one session.
    You will not be able to save your work or continue later.

    If you aren't ready to resolve all flags, you can select to review flags.
    When you are ready to resolve all the flags, you can start moderation.") . '</p>',
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['review_flags'] = array(
    '#type' => 'submit',
    '#value' => 'Review Flags',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Start Moderation',
  );

  return $form;
}
