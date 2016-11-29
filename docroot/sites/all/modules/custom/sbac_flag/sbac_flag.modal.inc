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
    elseif (isset($_GET['forum_type'])) {
      $title = 'You are about to start forum moderation.';
    }

    $form_state = array(
      'title' => $title,
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
      'eck_review' => $_GET['eck_review'],
      'forum_type' => $_GET['forum_type'],
      'cid' => $_GET['cid'],
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
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array(
            'query' => array(
              'flag' => 'view-resource-review-flags',
              'review' => $form_state['eck_review']
            ),
            'fragment' => 'review-Moderate_flag'
          ));
        }
        elseif ($form_state['forum_type']) {
          $path_alias = drupal_get_path_alias('node/' . $node->nid);
          $output[] = ctools_ajax_command_redirect($path_alias, 0, array(
            'query' => array(
              'flag' => 'view-' . $form_state['forum_type'] . '-flags',
              'cid' => $form_state['cid'],
            ),
            'fragment' => 'review-moderate_flag',
          ));
        }
        elseif (!$form_state['eck_review'] && !$form_state['forum_type']) {
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'view-resource-flags'), 'fragment' => 'review-Moderate_flag'));
        }
      }

      if ($form_state['triggering_element']['#value'] == 'Start Moderation') {
        $node = node_load($form_state['nid']);
        if ($form_state['eck_review']) {
          sbac_flag_set_being_moderated($node, $form_state['eck_review']);
          $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'resolve-resource-review-flags', 'review' => $form_state['eck_review'], 'node' => $node->nid), 'fragment' => 'review-Moderate_flag'));
        }
        elseif ($form_state['forum_type']) {
          sbac_flag_collaboration_set_being_moderated($node, $form_state['cid']);
          $path_alias = drupal_get_path_alias('node/' . $node->nid);
          $output[] = ctools_ajax_command_redirect($path_alias, 0, array(
            'query' => array(
              'flag' => 'resolve-' . $form_state['forum_type'] . '-flags',
              'cid' => $form_state['cid'],
            ),
            'fragment' => 'review-moderate_flag',
          ));
        }
        elseif (!$form_state['eck_review'] && !$form_state['forum_type']) {
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
        // button to the Flag tab
        $node = node_load($form_state['nid']);
         $output[] = ctools_ajax_command_redirect($node->path['alias'], 0, array('query' => array('flag' => 'resolve-resource-review-flags', 'review' => $form_state['eck_review']), 'fragment' => 'review-Moderate_flag'));
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
        // button to the Flag tab
        $output[] = ctools_ajax_command_reload();
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

  $form['finish_moderation_review'] = array(
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
 * Form callback for collaboration flagging.
 * @param  boolean $js  ctools_js
 * @param  int     $nid Node ID.
 * @param  int     $cid Comment ID. 0 if topic.
 */
function sbac_flag_collaboration_callback($js = FALSE, $nid, $cid = 0) {
  if (!$js) {
    return;
  }
  $can_close = FALSE;
  drupal_add_js(drupal_get_path('module', 'sbac_flag') . '/js/sbac_flag.collaboration.js');
  ctools_add_css('sbac_flag.css', 'sbac_flag');
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();

  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Flag a Post'),
    'info' => array(
      'nid' => $nid,
      'cid' => $cid,
    ),
  );

  $output = ctools_modal_form_wrapper('sbac_flag_collaboration_form', $form_state);

  if (!empty($form_state['executed'])) {
    if ($form_state['triggering_element']['#value'] == 'Cancel') {
      $can_close = TRUE;
    }
    else if ($form_state['triggering_element']['#value'] == 'Flag') {
      $can_close = TRUE;
    }
  }
  if ($can_close) {
    $output = array();
    $output[] = ctools_modal_command_dismiss();
    if ($form_state['triggering_element']['#value'] == 'Flag') {
      $url = drupal_get_path_alias('node/' . $nid);
      $output[] = ctools_ajax_command_redirect($url);
    }
  }
  print ajax_render($output);
  exit();
}

/**
 * Implements hook_form().
 * Creates form for flagging modal.
 * @param  [type]  $form       [description]
 * @param  [type]  $form_state [description]
 * @return [type]              [description]
 */
function sbac_flag_collaboration_form($form, &$form_state) {
  $form['header'] = array(
    '#type'   => 'item',
    '#prefix' => '<div class="form-flag-content"><div class="form-item-title">',
    '#suffix' => '</div>',
  );

  $form['error'] = array(
    '#type' => 'markup',
    '#markup' => '',
  );

  $form['comment'] = array(
    '#type' => 'textarea',
    '#title' => 'Details',
    '#prefix' => '<div id="sbac-flag-optional-comment" style="display:none">',
    '#suffix' => '</div>',
    '#maxlength' => 600,
    '#maxlength_js' => TRUE,
    '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),
  );

  $vocab = taxonomy_vocabulary_machine_name_load('forum_flags');
  $terms = taxonomy_get_tree($vocab->vid);
  $options = array();
  foreach ($terms as $term) {
    $options[$term->tid] = $term->name;
  }

  $form['flag_options'] = array(
    '#type' => 'radios',
    '#title' => 'What issue did you find with this post? ' . theme('form_required_marker'),
    '#options' => $options,
    '#prefix' => '<div id="sbac-flag-options">',
    '#suffix' => '</div>',
  );

  $form['footer'] = array(
    '#type' => 'item',
    '#markup' => 'Flagged reviews and users are reviewed by the Smarter Balanced Assesment Consortium to determine whether they violate the terms of service. Violations can lead to account termination.',
    '#prefix' => '<div id="form-item-footer">',
    '#suffix' => '</div></div>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Flag'),
    '#prefix' => '<div class="flag-button-container">',
    '#attributes' => array(
      'class' => array(
        'button',
        'flag-resource-submit',
      ),
    ),
    '#ajax' => array(
      'wrapper' => 'sbac-flag-collaboration-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#suffix' => '</div>',
    '#attributes' => array(
      'class' => array(
        'button',
        'gray',
        'cancel',
        'flag-resource-cancel',
      ),
      'id' => array(
        'flag-edit-cancel',
      ),
    ),
  );

  return $form;
}

/**
 * Form validation for sbac_flag_collaboration_form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 */
function sbac_flag_collaboration_form_validate(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Cancel') {
    return;
  }
  if ($form_state['values']['flag_options'] == NULL) {
    form_set_error('flag_options', 'Please select a reason to flag this post.');
  }
  else {
    if ($form_state['values']['comment'] != NULL) {
      if (profanity_validate_text($form_state['values']['comment'])) {
        form_set_error('comment', 'Please remove any inappropriate language.');
      }
    }
    if ($form_state['values']['comment'] == NULL) {
      form_set_error('comment', 'Please validate your reason for flagging.');
    }
  }
  if ($error = drupal_get_messages('error', TRUE)) {
    $error = array_pop($error);
    $form['error']['#markup'] = '<div class="sbac-flag-error-msg">' . array_pop($error) . '</div>';
  }
}

/**
 * Submission handler for sbac_flag_collaboration_form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_flag_collaboration_form_submit(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Flag') {
    $flag_tid = $form_state['input']['flag_options'];
    $flag_txt = $form_state['input']['comment'];
    $flag_nid = $form_state['info']['nid'];
    $flag_cid = $form_state['info']['cid'];
    $node = node_load($flag_nid);

    $forum = taxonomy_term_load($node->field_topic_forum_parent['und'][0]['tid']);
    $forum_author = $forum->field_forum_facilitators['und'][0]['target_id'];
    $user_profile = user_load($node->uid);

    // Notify topic creator
    if ($task = taskit_get_object('forum_flagged')) {
      $task->addVisibility($task::VISIBILITY_USER);
      $task->addEntity('node', $node->nid);
      $task->addOwningUser($user_profile->uid);
      $task->addTriggeringUser($user_profile->uid);
      $task->save();
    }
    // Notify forum creator if different user
    if ($node->uid !== $forum_author) {
      if ($task = taskit_get_object('forum_flagged')) {
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('node', $node->nid);
        $task->addOwningUser($forum_author);
        $task->addTriggeringUser($forum_author);
        $task->save();
      }
    }
    // Send email to topic creator
    global $base_url;
    $values = array(
      'arguments' => array(
        '!forum-link' => $base_url . '/node/' . $node->nid,
      ),
      'uid' => $node->uid,
    );
    if ($user_profile->field_email_preference['und'][0]['value'] != 'never' && $user_profile->field_email_preference['und'][0]['value'] != '') {  
      // Create message
      $message = message_create('forum_flagged', $values);
      $wrapper = entity_metadata_wrapper('message', $message);
      $wrapper->save();
      if ($user_profile->field_email_preference['und'][0]['value'] == 'immediately') {
        // send email
        message_notify_send_message($message);
        // delete message after it is sent so it doesn't show up in digest if a user switches email preferences
        message_delete_multiple(array($message->mid));
      }
    }
    // Send email to forum creator if different user
    if ($node->uid !== $forum_author) {
      $user_profile = user_load($forum_author);
      $values = array(
        'arguments' => array(
          '!forum-link' => $base_url . '/content/' . $node->nid,
        ),
        'uid' => $user_profile->uid,
      );
      if ($user_profile->field_email_preference['und'][0]['value'] != 'never' && $user_profile->field_email_preference['und'][0]['value'] != '') {  
        // Create message
        $message = message_create('forum_flagged', $values);
        $wrapper = entity_metadata_wrapper('message', $message);
        $wrapper->save();
        if ($user_profile->field_email_preference['und'][0]['value'] == 'immediately') {
          // send email
          message_notify_send_message($message);
          // delete message after it is sent so it doesn't show up in digest if a user switches email preferences
          message_delete_multiple(array($message->mid));
        }
      }
    }
    sbac_flag_save_flag($flag_tid, $flag_txt, $flag_nid, $flag_cid);
    
  }
}

function sbac_flag_collaboration_resolve_callback($js = FALSE, $type, $nid, $cid) {
  if (!$js) {
    return;
  }

  ctools_add_css('sbac_flag.css', 'sbac_flag');
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();

  $form_state = array(
    'title' => t('You are about to resolve all flags'),
    'ajax' => TRUE,
    'info' => array(
      'form_type' => $type,
      'nid' => $nid,
      'cid' => $cid,
    ),
  );

  $output = ctools_modal_form_wrapper('sbac_flag_collaboration_resolve_form', $form_state);

  if (!empty($form_state['executed'])) {

    if ($form_state['triggering_element']['#value'] == 'Resolve Flags') {
//      sbac_flag_collaboration_unset_being_moderated($nid, $cid);
      sbac_flag_collaboration_resolve_forum($nid, $cid);
      $url = drupal_get_path_alias('node/' . $nid);
      $output[] = ctools_ajax_command_redirect($url);
    }
    $output[] = ctools_modal_command_dismiss();
  }

  print ajax_render($output);
  exit;
}

function sbac_flag_collaboration_resolve_form($form, &$form_state) {
  $form = array();
  $flags = sbac_flag_get_forum_flags($form_state['info']['nid'], $form_state['info']['cid']);
  $flag_list = array();

  $form['content_container_open'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="flag-modal-cont">',
  );

  $form['header'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="sbac-flag-collaboration-resolve-header">',
    '#markup' => '<span class="sbac-resolve-text">You are resolving the following flags</span>',
    '#suffix' => '</div>',
  );

  while ($flag = $flags->fetchAssoc()) {
    $flag_list[$flag['flag_selected']][] = $flag;
  }

  foreach ($flag_list as $tid => $flag_reports) {
    $flag_count = count($flag_reports);
    $num_text = $flag_count . ' ' . ($flag_count == 1 ? 'flag' : 'flags');
    $flag_term = taxonomy_term_load($tid);

    $form['flag' . $tid] = array(
      '#type' => 'item',
      '#markup' => $flag_term->name . ' <span class="sbac-flag-collaboration-flag-num"> - ' . $num_text,
    );
  }

  $form['warning'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="sbac-flag-collaboration-resolve-warning">',
    '#markup' => t('If you continue, all flags will be dismissed.'),
    '#suffix' => '</span></div>',
  );

  $form['content_container_close'] = array(
    '#type' => 'markup',
    '#markup' => '</div>',
  );

  $form['button_container_open'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="flag-modal-buttons">',
  );

	$form['resolve'] = array(
    '#type' => 'submit',
    '#value' => 'Resolve Flags',
		'#attributes' => array(
      'class' => array(
        'button',
      ),
		),
  );
 
  $form['cancel-resolve'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
		'#attributes' => array(
      'class' => array(
        'button',
        'gray',
        'cancel',
      ),
		),
  );
 
  $form['button_container_close'] = array(
    '#type' => 'markup',
    '#value' => '</div>',
  );

  return $form;
}

function sbac_flag_collaboration_remove_callback($js = FALSE, $type, $nid, $cid) {
  if (!$js) {
    return;
  }

  global $user;

  ctools_add_css('sbac_flag.css', 'sbac_flag');
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();

  $title = 'You are about to remove this ' . ($type == 'topic' ? 'topic' : 'post');

  $form_state = array(
    'title' => $title,
    'ajax' => TRUE,
    'info' => array(
      'type' => $type,
      'nid' => $nid,
      'cid' => $cid,
    ),
  );

  $output = ctools_modal_form_wrapper('sbac_flag_collaboration_remove_form', $form_state);

  if (!empty($form_state['executed'])) {
    if ($form_state['triggering_element']['#value'] == 'Remove Topic') {
//      sbac_flag_collaboration_unset_being_moderated($nid, $cid);
      sbac_flag_collaboration_remove_forum($nid, $cid, $form_state['values']['message']);

      // Notify poster
      $node = entity_metadata_wrapper('node', $nid);
      $forum_poster = $node->author->uid->value();


      if ($task = taskit_get_object('topic_removed_creator')) {
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('node', $nid);
        $task->addOwningUser($forum_poster);
        $task->addTriggeringUser($user->uid);
        $task->save();
      }

      //  Notify participants
      $recipients = array();

      $query = db_select('comment', 'c');
      $query->fields('c', array('uid'));
      $query->distinct();
      $query->condition('nid', $nid, '=');
      $result = $query->execute();

      while ($poster = $result->fetchAssoc()) {
        $recipients[] = $poster;
      }

      foreach ($recipients as $recipient) {
        if ($recipient['uid'] != $forum_poster && $task = taskit_get_object('topic_removed')) {
          $task->addVisibility($task::VISIBILITY_USER);
          $task->addEntity('node', $nid);
          $task->addOwningUser($recipient['uid']);
          $task->addTriggeringUser($user->uid);
          $task->save();
        }
      }

      //  Delete Topic
      node_delete($nid);

      //  Redirect
      $output[] = ctools_ajax_command_redirect('moderation');
    }
    elseif ($form_state['triggering_element']['#value'] == 'Remove Post') {
//      sbac_flag_collaboration_unset_being_moderated($nid, $cid);
      sbac_flag_collaboration_remove_forum($nid, $cid, $form_state['values']['message']);
      $comment = entity_metadata_wrapper('comment', $cid);
      $forum_poster = $comment->author->uid->value();

      if ($task = taskit_get_object('post_removed_creator')) {
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('node', $nid);
        $task->addEntity('comment', $cid);
        $task->addOwningUser($forum_poster);
        $task->addTriggeringUser($user->uid);
        $task->save();
      }

      // Check to see if it has children
      $comment_query = db_select('comment', 'c');
      $comment_query->fields('c');
      $comment_query->condition('pid', $cid, '=');
      $comment_results = $comment_query->execute();
      if (!($result = $comment_results->fetchAssoc())) {
        comment_delete($cid);
      }

      $output[] = ctools_ajax_command_redirect('moderation');
    }
    $output[] = ctools_modal_command_dismiss();
  }

  print ajax_render($output);
  exit();
}

function sbac_flag_collaboration_remove_form($form, &$form_state) {
  $form = array();

  $form['content_container_open'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="flag-modal-cont">',
  );

  $form['error'] = array(
    '#type' => 'markup',
    '#markup' => '',
  );

  if ($form_state['info']['type'] == 'topic') {
    $node = entity_metadata_wrapper('node', $form_state['info']['nid']);
    $post_count = $node->comment_count->value();
    $header_markup = $post_count . ' ' . ($post_count == 1 ? 'post' : 'posts');

    $form['header'] = array(
      '#type' => 'item',
      '#markup' => 'This topic contains <span class="sbac-forum-flagged-text">' . $header_markup . '</span> . If you remove the topic, the posts will be removed as well.'
    );

    $message_box = array(
      '#type' => 'textarea',
      '#title' => 'Please leave a message for the topic creator',
      '#rows' => 3,
      '#maxlength' => 1000,
      '#maxlength_js' => TRUE,
      '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),

    );

    $remove_button = array(
      '#type' => 'submit',
      '#value' => 'Remove Topic',
      '#attributes' => array(
        'class' => array(
          'button',
          'red',
          'remove',
        ),
      ),
    );
  }
  elseif ($form_state['info']['type'] == 'comment') {
    $message_box = array(
      '#type' => 'textarea',
      '#title' => 'Please leave a message for the poster',
      '#rows' => 3,
      '#maxlength' => 1000,
      '#maxlength_js' => TRUE,
      '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),
    );

    $remove_button = array(
      '#type' => 'submit',
      '#value' => 'Remove Post',
			'#attributes' => array(
	      'class' => array(
	        'button',
	        'red',
	        'remove',
	      ),
			),
    );
  }

  $form['message'] = $message_box;

  $form['content_container_close'] = array(
    '#type' => 'markup',
    '#markup' => '</div>',
  );

  $form['button_container_open'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="flag-modal-buttons">',
  );

	$form['remove_collaboration'] = $remove_button;
	
  $form['cancel_collaboration'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
		'#attributes' => array(
      'class' => array(
        'button',
        'gray',
        'cancel',
      ),
		),
  );

  $form['button_container_close'] = array(
    '#type' => 'markup',
    '#value' => '</div>',
  );

  return $form;
}

function sbac_flag_collaboration_remove_form_validate(&$form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Cancel') {
    return;
  }
  else {
    if ($form_state['values']['message'] != NULL) {
      if (profanity_validate_text($form_state['values']['message'])) {
        form_set_error('message', 'Please remove any inappropriate language.');
      }
    }
    if ($form_state['values']['message'] == NULL) {
      form_set_error('message', 'Please validate your reason for removal.');
    }
  }
  if ($error = drupal_get_messages('error', TRUE)) {
    $error = array_pop($error);
    $form['error']['#markup'] = '<div class="sbac-flag-error-msg">' . array_pop($error) . '</div>';
  }
}
