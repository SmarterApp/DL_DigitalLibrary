<?php

/**
 * The sbac flag modal
 *
 * @param bool $js
 */
function sbac_flag_modal_content($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
    $form_state = array(
      'title' => t('You are about to flag this resource'),
      'ajax' => TRUE,
      'flag_option' => $_SESSION['sbac-flag']['flag_options'],
      'flag_comment' => $_SESSION['sbac-flag']['optional_comment'],
      'nid' => $_SESSION['sbac-flag']['nid'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_resource_modal_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        // Notify moderator and save a flag in the resource table.
        // remember to save option and message if provided.
        // then redirect user to the same page with new message.
        $flag = sbac_flag_save_flag($form_state['values']['flag_option'], $form_state['values']['flag_comment'], $form_state['values']['nid']);
        if ($flag['urgent']) {
          global $user;
          $node = node_load($form_state['values']['nid']);
          // Determine if the user has access to review the node.
          // This is determined by all users with role of "moderator"
          // and the nodes view permissions field.
          $accounts = sbac_flag_get_users_with_node_access($node);
          foreach ($accounts as $uid => $account) {
            if ($task = taskit_get_object('resource_flagged')) {
              $task->addVisibility($task::VISIBILITY_USER);
              $task->addEntity('node', $node->nid);
              $task->addOwningUser($account->uid);
              $task->addTriggeringUser($user->uid);
              $task->save();
            }
          }
        }

        $output[] = ajax_command_invoke('.section-flag .content', 'empty');
        $content = sbac_flag_confirmation($flag);
        $output[] = ajax_command_append('.section-flag .content', $content);
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

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
      'eck_review' => $_GET['eck_review'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_start_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();

      if ($form_state['triggering_element']['#value'] == 'Review Flags') {
        $node = node_load($form_state['nid']);
        if ($form_state['eck_review']) {
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'view-resource-review-flags', 'review' => $form_state['eck_review']), 'fragment' => 'review-Moderate_flag'));
        }
        else {
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'view-resource-flags'), 'fragment' => 'review-Moderate_flag'));
        }
      }

      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
        $node = node_load($form_state['nid']);
        if ($form_state['eck_review']) {
          sbac_flag_set_being_moderated($node, $form_state['eck_review']);
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'resolve-resource-review-flags', 'review' => $form_state['eck_review']), 'fragment' => 'review-Moderate_flag'));
        }
        else {
          sbac_flag_set_being_moderated($node);
          $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('query' => array('flag' => 'resolve-resource-flags'), 'fragment' => 'something-Moderate_flag'));
        }
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

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
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

/**
 * Displays the start resource review moderation modal.
 *
 * @param bool $js
 */
function sbac_flag_start_resource_moderation_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to start resource moderation';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_start_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Review Flags') {
        $node = node_load($form_state['nid']);
        $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('query' => array('flag' => 'resolve-resource-flags'), 'fragment' => 'something-Moderate_flag'));
      }

      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
//        $node = node_load($form_state['nid']);
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

/**
 * Displays the start resource review moderation modal.
 *
 * @param bool $js
 */
function sbac_flag_cancel_resource_moderation_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to cancel moderation of this resource';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_cancel_resource_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Cancel Moderation') {
        $node = node_load($form_state['nid']);
        sbac_flag_unset_being_moderated($node);
        $output[] = ctools_ajax_command_redirect('moderation');
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
 * Resolve all flags modal.
 *
 * @param bool $js
 */
function sbac_flag_resolve_all_flags_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to make changes to the resource and resolve all flags';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_resolve_all_flags_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Finish Moderation') {
        global $user;
        $node = node_load($form_state['nid']);
        // resolve all the flags
        sbac_flag_resolve_all_flags($node);

        // notify contributor of the resource
        if ($task = taskit_get_object('resolved_all_flags')) {
          $task->addVisibility($task::VISIBILITY_USER);
          $task->addEntity('node', $node->nid);
          $task->addOwningUser($node->uid);
          $task->addTriggeringUser($user->uid);
          $task->save();
        }

        $output[] = ctools_ajax_command_redirect('moderation');
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
 * The remove resource modal
 *
 * @param bool $js
 */
function sbac_flag_remove_resource_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to remove this resource';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_cancel_resource_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Cancel Moderation') {

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

  $form['submit_description'] = array(
    '#markup' => "<p>If you start moderation, you will have to resolve the flags in one session.
    You will not be able to save your work or continue later.</p>
    <p>If you aren't ready to resolve all flags, you can select to review flags.
    When you are ready to resolve all the flags, you can start moderation.</p>"
  );

	$form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Start Moderation',
  );

  $form['review_flags'] = array(
    '#type' => 'submit',
    '#value' => 'Review Flags',
    '#attributes' => array('class' => array('button', 'blue', 'cancel'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  return $form;
}

/**
 * Cancel form.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_flag_cancel_resource_moderation_form($form, $form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>' . t("
    If you continue, all of your changes will be discarded and
    resource will returned to the moderation queue in its original state.") . '</p>',
  );

  $form['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Continue Moderation',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel Moderation',
    '#attributes' => array('class' => array('button'))
  );

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function sbac_flag_resolve_all_flags_form($form, $form_state) {
  $form = array();

  $changes_made = FALSE;
  $form_state['changes-made'] = $changes_made;
  if ($_SESSION['sbac-flag']['changes-made']) {
    $changes_made = TRUE;
    $form_state['changes-made'] = $changes_made;
  }

  // Get all flags that will be resolved.
  $node = node_load($_GET['nid']);
  $categories = array();
  if ($node) {
    $flags = sbac_flag_get_all_flags_for_node($node, 'resource');
    $categories = sbac_flag_list_flag_categories($flags);
  }

  $form['categories'] = array(
    '#markup' => $categories,
  );

  if ($changes_made) {
    $form['submit_description'] = array(
      '#markup' => 'If you continue, the resource will no longer be available in your moderation queue.
      All of your changes will be saved and applied to the resource. The message will be sent to the
      contributor and all the flags will be dismissed.',
    );

    $form['contributor_message'] = array(
      '#type' => 'textarea',
      '#title' => 'Since you have edited this resource, please leave a message for contributor' . theme('form_required_marker'),
    );
  }
  else {
    $form['submit_description'] = array(
      '#markup' => 'If you continue, the resource will no longer be available in your
      moderation queue and all flags will be dismissed.',
    );
  }

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['finish_moderation'] = array(
    '#type' => 'submit',
    '#value' => 'Finish Moderation',
    '#attributes' => array('class' => array('button'))
  );

  return $form;
}

/**
 * Validates form.
 *
 * @param $form
 * @param $form_state
 */
function sbac_flag_resolve_all_flags_form_validate(&$form, &$form_state) {
  $changes_made = FALSE;
  if ($_SESSION['sbac-flag']['changes-made']) {
    $changes_made = TRUE;
  }

  if ($changes_made) {
    if (empty($form_state['values']['contributor_message'])) {
      form_set_error('contributor_message', 'Please leave a message for the contributor to continue');
    }
  }
}
