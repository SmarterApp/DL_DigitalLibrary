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
            $task = taskit_get_object('resource_flagged');
            if ($task && _sbac_resource_determine_state_access($node, $user) == TRUE) {
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
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'resolve-resource-review-flags', 'review' => $form_state['eck_review'], 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
        }
        else {
          sbac_flag_set_being_moderated($node);
          $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('query' => array('flag' => 'resolve-resource-flags', 'node' => $node->nid), 'fragment' => 'something-Moderate_flag'));
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
      'eck_review' => $_GET['eck_review'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_start_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Review Flags') {
        // button acts like cancel
      }

      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
        // start moderation and send to resource review page
        $node = node_load($form_state['nid']);
        sbac_flag_set_being_moderated($node, $form_state['eck_review']);
        $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'resolve-resource-review-flags', 'review' => $form_state['eck_review'], 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
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
        // button acts like cancel
      }

      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
        $node = node_load($form_state['nid']);
        sbac_flag_set_being_moderated($node);
        $output[] = ctools_ajax_command_redirect('node/' . $node->nid . '/edit', 0, array('query' => array('flag' => 'resolve-resource-flags', 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
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
        $output[] = ajax_command_invoke('.sbac-resource-cancel-button', 'click');
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

        if ($form_state['changes-made'] == TRUE) {
          // notify contributor of the resource
          if ($task = taskit_get_object('resolved_all_flags')) {
            $task->addVisibility($task::VISIBILITY_USER);
            $task->addEntity('node', $node->nid);
            $task->addEntity('feedback', $form_state['feedback']);
            $task->addOwningUser($node->uid);
            $task->addTriggeringUser($user->uid);
            $task->save();
          }
        }
        // redirect
        $output[] = ctools_ajax_command_redirect('moderation');
        // remove session variables
        unset($_SESSION['sbac-flag']);
      }

      if ($form_state['triggering_element']['#value'] == 'Cancel') {
        unset($_SESSION['sbac-flag']);
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
    $output = ctools_modal_form_wrapper('sbac_flag_remove_resource_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Finish Moderation') {
        $node = node_load($form_state['nid']);
        // if the node is stickied, remove that.
        if ($node->sticky == 1) {
          $node->sticky = 0;
          node_save($node);
        }
        // remove resource, rebuild permissions.
        workbench_moderation_moderate($node, 'removed');
        sbac_resource_save_current_state($node);
        // send notification
        if ($task = taskit_get_object('removed_resource')) {
          global $user;
          $task->addVisibility($task::VISIBILITY_USER);
          $task->addEntity('node', $node->nid);
          $task->addEntity('feedback', $form_state['feedback']);
          $task->addOwningUser($node->uid);
          $task->addTriggeringUser($user->uid);
          $task->save();
        }
        // dismiss all flags
        sbac_flag_remove_resource($node);
        // redirect to moderation
        $output[] = ctools_ajax_command_redirect('moderation');
        // remove session variables
        unset($_SESSION['sbac-flag']);
      }

      if ($form_state['triggering_element']['#value'] == 'Finish Moderation') {
        unset($_SESSION['sbac-flag']);
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
function sbac_flag_cancel_resource_review_moderation_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to cancel moderation of this resource review';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
      'review' => $_GET['review'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_cancel_resource_review_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Cancel Moderation') {
        $node = node_load($form_state['nid']);
        $eck_review = $form_state['review'];
        sbac_flag_unset_being_moderated($node, $eck_review);
        // redirect to moderation
        $output[] = ctools_ajax_command_redirect('moderation');
        unset($_SESSION['sbac-flag']);
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
 * The Resolve All Resource Review Flags modal.
 *
 * @param bool $js
 */
function sbac_flag_resolve_all_resource_review_flags_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to resolve all flags';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
      'review' => $_GET['review'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_resolve_all_resource_review_moderation_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Finish Moderation') {
        // resolve all flags
        $node = node_load($form_state['nid']);
        $eck_review = $form_state['review'];
        sbac_flag_resolve_all_flags($node, $eck_review);
        // redirect
        $output[] = ctools_ajax_command_redirect('moderation');
        // remove session variables
        unset($_SESSION['sbac-flag']);
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
 * Remove resource review modal
 *
 * @param bool $js
 */
function sbac_flag_remove_resource_review_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'You are about to delete resource review';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
      'review' => $_GET['review'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_remove_resource_review_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Delete Resource Review') {
        $node = node_load($form_state['nid']);
        // remove resource review
        $entity = entity_load_single('review', $form_state['review']);
        $entity_wrapper = entity_metadata_wrapper('review', $entity);
        $entity_wrapper->status->set(0);
        $entity_wrapper->save();
        // send notification
        if ($task = taskit_get_object('removed_resource_review')) {
          global $user;
          $task->addVisibility($task::VISIBILITY_USER);
          $task->addEntity('node', $node->nid);
          $task->addOwningUser($node->uid);
          $task->addTriggeringUser($user->uid);
          $task->save();
        }
        // dismiss all flags
        sbac_flag_resolve_all_flags($node, $form_state['review']);
        // redirect to moderation
        $output[] = ctools_ajax_command_redirect('moderation');
        // remove session variables
        unset($_SESSION['sbac-flag']);
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
 * Session expire modal.
 *
 * @param bool $js
 */
function sbac_flag_session_expire_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $title = 'Your moderation session is about to end';

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    module_load_include('inc', 'sbac_flag', 'sbac_flag.modal');
    $output = ctools_modal_form_wrapper('sbac_flag_session_expire_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] == 'Continue Moderation') {
        // refresh the user session somehow.
        sbac_sso_session_regenerate();
        $output[] = ajax_command_callback('sbac_node_form', 'reset_timers');
      }
      else {
        // cancel was clicked.
        sbac_sso_session_regenerate();
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
 * Start moderation form.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_flag_start_moderation_form($form, &$form_state) {
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
    '#attributes' => array('class' => array('button', 'blue'))
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
function sbac_flag_cancel_resource_moderation_form($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>' . t("
    If you continue, all of your changes will be discarded and
    resource will returned to the moderation queue in its original state.") . '</p>',
  );

  $form['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Continue Moderation',
    '#attributes' => array('class' => array('button', 'blue'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel Moderation',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function sbac_flag_resolve_all_flags_form($form, &$form_state) {
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

  $form['container_prefix'] = array(
    '#prefix' => '<div class="flag-modal-cont">',
  );

  $form['categories'] = array(
    '#markup' => $categories,
  );

  if ($changes_made) {
    $form['submit_description'] = array(
      '#markup' => '<p>If you continue, the resource will no longer be available in your moderation queue.
      All of your changes will be saved and applied to the resource. The message will be sent to the
      contributor and all the flags will be dismissed.</p>',
    );

    $form['contributor_message'] = array(
      '#type' => 'textarea',
      '#title' => 'Since you have edited this resource, please leave a message for contributor' . theme('form_required_marker'),
      '#maxlength' => 1000,
      '#maxlength_js' => TRUE,
      '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),
    );
  }
  else {
    $form['submit_description'] = array(
      '#markup' => '<p>If you continue, the resource will no longer be available in your
      moderation queue and all flags will be dismissed.</p>',
    );
  }

  $form['container_suffix'] = array(
    '#suffix' => '</div>',
  );

  $form['button_prefix'] = array(
    '#prefix' => '<div class="flag-button-cont">',
  );

  $form['finish_moderation'] = array(
    '#type' => 'submit',
    '#value' => 'Finish Moderation',
    '#attributes' => array('class' => array('button', 'blue')),
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['button_suffix'] = array(
    '#suffix' => '</div>',
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
  if ($form_state['triggering_element']['#value'] == 'Finish Moderation') {
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
}

/**
 * Form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function sbac_flag_resolve_all_flags_form_submit(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Finish Moderation' && isset($form_state['values']['contributor_message'])) {
    $node = node_load($form_state['nid']);
    if ($node) {
      $flags = sbac_flag_get_all_flags_for_node($node, 'resource');
      if ($flags) {
        foreach ($flags as $flag) {
          db_query('UPDATE {eck_flag} ef SET ef.moderation_comment = :comment WHERE ef.id = :id', array(':comment' => $form_state['values']['contributor_message'], ':id' => $flag->id));
          // we only need one feedback comment here so it doesn't matter if it gets overridden in the loop because the comments are the same anyway
          $form_state['feedback'] = $flag->id;
        }
      }
    }
  }
}

/**
 * Remove resource form.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_flag_remove_resource_form($form, &$form_state) {
  $form = array();

  $form['container_prefix'] = array(
    '#prefix' => '<div class="flag-modal-cont">',
  );

  $form['submit_description'] = array(
    '#markup' => '<p>If you continue, the resource will no longer be available in the
    Digital Library Resource will be returned to the contributor in the locked state. The
    message will be sent to the contributor, all the flags will be dismissed and all the
    changes will be discarded.</p>',
  );

  $form['contributor_message'] = array(
    '#type' => 'textarea',
    '#title' => 'Please leave a message for contributor' . theme('form_required_marker'),
    '#maxlength' => 1000,
    '#maxlength_js' => TRUE,
    '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),
  );

  $form['container_suffix'] = array(
    '#suffix' => '</div>',
  );

  $form['button_prefix'] = array(
    '#prefix' => '<div class="flag-button-cont">',
  );

  $form['finish_moderation'] = array(
    '#type' => 'submit',
    '#value' => 'Finish Moderation',
    '#attributes' => array('class' => array('button', 'blue'))
  );

	$form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['button_suffix'] = array(
    '#suffix' => '</div>',
  );
  return $form;
}

/**
 * Validates form.
 *
 * @param $form
 * @param $form_state
 */
function sbac_flag_remove_resource_form_validate(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Finish Moderation') {
    if (empty($form_state['values']['contributor_message'])) {
      form_set_error('contributor_message', 'Please leave a message for the contributor to continue');
    }
  }
}

/**
 * Form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function sbac_flag_remove_resource_form_submit(&$form, &$form_state) {
  $node = node_load($form_state['nid']);
  if ($node) {
    $flags = sbac_flag_get_all_flags_for_node($node, 'resource');
    if ($flags) {
      foreach ($flags as $flag) {
        db_query('UPDATE {eck_flag} ef SET ef.moderation_comment = :comment WHERE ef.id = :id', array(':comment' => $form_state['values']['contributor_message'], ':id' => $flag->id));
        // we only need one feedback comment here so it doesn't matter if it gets overridden in the loop because the comments are the same anyway
        $form_state['feedback'] = $flag->id;
      }
    }
  }
}

/**
 * Resource review cancel form.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_flag_cancel_resource_review_moderation_form($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>If you continue, the resource review will be
    returned to the moderation queue in its original state.</p>',
  );

  $form['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Continue Moderation',
    '#attributes' => array('class' => array('button', 'blue'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel Moderation',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  return $form;
}

/**
 * Resolve all resource review form.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_flag_resolve_all_resource_review_moderation_form($form, &$form_state) {
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
    $flags = sbac_flag_get_all_flags_for_node($node, 'review', $form_state['review']);
    $categories = sbac_flag_list_flag_categories($flags, 'review');
  }

  $form['container_prefix'] = array(
    '#prefix' => '<div class="flag-modal-cont">',
  );

  $form['categories'] = array(
    '#markup' => $categories,
  );

  $form['submit_description'] = array(
    '#markup' => '<p>If you continue, the resource review will
    no longer be available in your moderation queue and all flags will be dismissed.</p>',
  );

  $form['container_suffix'] = array(
    '#suffix' => '</div>',
  );

  $form['button_prefix'] = array(
    '#prefix' => '<div class="flag-button-cont">',
  );

  $form['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Finish Moderation',
    '#attributes' => array('class' => array('button', 'blue'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['button_suffix'] = array(
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Remove resource review form.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_flag_remove_resource_review_form($form, &$form_state) {
  $form = array();

  $form['container_prefix'] = array(
    '#prefix' => '<div class="flag-modal-cont">',
  );

  $form['submit_description'] = array(
    '#markup' => '<p>If you continue, the resource review will no longer
    be available in your moderation queue and will be removed from the resource.</p>',
  );

  $form['contributor_message'] = array(
    '#type' => 'textarea',
    '#title' => 'Please leave a message for review contributor' . theme('form_required_marker'),
    '#maxlength' => 1000,
    '#maxlength_js' => TRUE,
    '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),
  );

  $form['container_suffix'] = array(
    '#suffix' => '</div>',
  );

  $form['button_prefix'] = array(
    '#prefix' => '<div class="flag-button-cont">',
  );

  $form['finish_moderation'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Resource Review',
    '#attributes' => array('class' => array('button', 'red'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );

  $form['button_suffix'] = array(
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Validates form.
 *
 * @param $form
 * @param $form_state
 */
function sbac_flag_remove_resource_review_form_validate(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Delete Resource Review') {
    if (empty($form_state['values']['contributor_message'])) {
      form_set_error('contributor_message', 'Please leave a message for the review contributor to continue');
    }
  }
}

/**
 * Form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function sbac_flag_remove_resource_review_form_submit(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Delete Resource Review') {
    $node = node_load($form_state['nid']);
    if ($node) {
      $flags = sbac_flag_get_all_flags_for_node($node, 'review', $form_state['review']);
      if ($flags) {
        foreach ($flags as $flag) {
          db_query('UPDATE {eck_flag} ef SET ef.moderation_comment = :comment WHERE ef.id = :id', array(':comment' => $form_state['values']['contributor_message'], ':id' => $flag->id));
        }
      }
    }
  }
}

/**
 * Session expire form.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_flag_session_expire_form($form, &$form_state) {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => "<p>If you don't click continue moderation, the
    session will timeout and the resource review will be returned to
    moderation queue in its initial state."
  );
	
	$form['continue'] = array(
    '#type' => 'submit',
    '#value' => 'Continue Moderation',
    '#attributes' => array('class' => array('button', 'blue'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel Moderation',
    '#attributes' => array('class' => array('button', 'gray', 'cancel'))
  );  

  $form['button_suffix'] = array(
    '#suffix' => '</div>',
  );

  return $form;
}
