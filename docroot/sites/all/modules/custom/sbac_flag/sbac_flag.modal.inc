<?php

/**
 * Displays the start resource review moderation modal.
 *
 * @param bool $js
 */
function sbac_flag_start_resource_review_moderation_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to start resource review moderation';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    $output = ctools_modal_form_wrapper('sbac_flag_start_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Review Flags') {
        $node = node_load($form_state['values']['nid']);
//        if ($form_state['eck_review']) {
//          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'view-resource-review-flags', 'review' => $form_state['eck_review']), 'fragment' => 'review-Moderate_flag'));
//        }
//        else {
//          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'view-resource-flags'), 'fragment' => 'review-Moderate_flag'));
//        }
      }

      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
//        $node = node_load($form_state['values']['nid']);
//        sbac_flag_set_being_moderated($node, $form_state['eck_review']);
//        $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('fragment' => 'resolve-flags'));
      }
    }
    print ajax_render($output);
    exit();
  }
  else {
    return;
  }
}