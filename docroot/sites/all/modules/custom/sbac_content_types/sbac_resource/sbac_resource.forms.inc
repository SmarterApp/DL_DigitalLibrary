<?php
/**
 * @file
 * Code for the SBAC resource feature.
 */

/**
 * Implements hook_form_alter().
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function sbac_resource_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'resource_node_form') {
    //global $user;
    $generate = _sbac_resource_setup_form($form, $form_state);
    _sbac_resource_module_flag($form, $form_state);
    if ($generate) {
      _sbac_resource_create_complete_flag($form, $form_state);
    }
    _sbac_resource_create_open_container($form, $form_state);
    _sbac_resource_create_resource_title($form, $form_state);
    _sbac_resource_content_type_description($form, $form_state);
    _sbac_resource_create_close_container($form, $form_state);
    _sbac_resource_form_basic($form, $form_state);
    _sbac_resource_form_summary($form, $form_state);
    _sbac_resource_form_materials($form, $form_state);
    _sbac_resource_form_tags($form, $form_state);
    _sbac_resource_form_revisions($form, $form_state);
    _sbac_resource_form_advanced($form, $form_state);
    _sbac_resource_form_cancel_all_changes_button($form, $form_state);
    _sbac_resource_form_save_all_changes_button($form, $form_state);
    _sbac_resource_form_submit_button($form, $form_state);
    _sbac_resource_form_save_continue_button($form, $form_state);
    _sbac_resource_form_cancel_button($form, $form_state);
    _sbac_resource_form_submit_resource($form, $form_state);
    _sbac_resource_form_required_fields($form, $form_state);
    _sbac_resource_form_remove_elements($form, $form_state);
    _sbac_resource_form_finalize($form, $form_state);
    _sbac_resource_form_flatten_term_tree($form, $form_state);
    
    //SBAC-80 Remove Playlist option for non-SLT's    
    //$is_slt  = sbac_report_is_slt($user);
    
    //if (!$is_slt && !in_array('administrator', $user->roles)) {
    //  unset($form['field_focus'][LANGUAGE_NONE]['#options']['Playlist']);
    //}
  }
}

/**
 * Flatten the taxonomy term tree.  Only show the children concatenated with parents
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_flatten_term_tree(&$form, &$form_state) {
  $configs = array(
    array('vid' => 'subject', 'field' => 'field_subject', 'wrapper' => ''),
    array('vid' => 'grades', 'field' => 'field_grades', 'wrapper' => ''),
    array('vid' => 'digital_media_type', 'field' => 'field_digital_media_type', 'wrapper' => 'tag_wrapper'),
    array('vid' => 'intended_student_populations', 'field' => 'field_intended_student', 'wrapper' => 'tag_wrapper'),
    array('vid' => 'geographical_settings', 'field' => 'field_geographical_settings', 'wrapper' => 'tag_wrapper'),
    array('vid' => 'educational_use', 'field' => 'field_educational_use', 'wrapper' => 'tag_wrapper'),
    array('vid' => 'technologies_for_classroom_use', 'field' => 'field_classroom_technologies', 'wrapper' => 'tag_wrapper'),
    array('vid' => 'smarter_balanced_keyword', 'field' => 'field_smarter_balanced_keyword', 'wrapper' => 'tag_wrapper'),
    array('vid' => 'intended_end_user', 'field' => 'field_intended_end_user', 'wrapper' => ''),
  );
  foreach ($configs as $config) {
    // Subject vocab
    $vocab = taxonomy_vocabulary_machine_name_load($config['vid']);
    $options = array();
    $terms = taxonomy_get_tree($vocab->vid);
    foreach ($terms as $term) {
      $children = taxonomy_get_children($term->tid);
      if (empty($children)) {
        $options[$term->tid] = sbac_resource_taxonomy_term_concat_parents($term->tid, $term->name);
      }
    }
    if (!empty($config['wrapper'])) {
      $form[$config['wrapper']][$config['field']]['und']['#options'] = $options;
    }
    else {
      $form[$config['field']]['und']['#options'] = $options;
    }
  }
}

/**
 * Initialize form variables.
 *
 * @param $form
 * @param $form_state
 * @return bool
 */
function _sbac_resource_setup_form(&$form, &$form_state) {
  // Attach required JS
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_set_title('');
  $form['#id'] = 'sbac-resource-form';

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'sbac_resource') . '/js/sbac_resource.form.js',
    drupal_get_path('module', 'sbac_alignment') . '/js/sbac_alignment.js',
    drupal_get_path('module', 'ctools') . "/js/ajax-responder.js",
    libraries_get_path('jquery.more') . '/jquery.more.js',
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css',
    libraries_get_path('jquery.more') . '/jquery.more.css',
  );

  // Set the state in JS for later use.
  if (isset($form['#node']->workbench_moderation['current']->state)) {
    drupal_add_js(array('resource_workbench_current_state' => $form['#node']->workbench_moderation['current']->state), 'setting');
  }
  else {
    drupal_add_js(array('resource_workbench_current_state' => 'creation'), 'setting');
  }

  if (!isset($form['#node']->nid)) {
    drupal_add_js(drupal_get_path("module", "sbac_help") . "/js/sbac_help.resource.js");
    drupal_add_js(array('resource_nid' => 0), 'setting');
  }
  else {
    drupal_add_js(array('resource_nid' => $form['#node']->nid), 'setting');
  }


  // Setup the form
  $generate = FALSE;
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#value'] != 'Upload') {
    $generate = TRUE;
  }
  else {
    if (!isset($form_state['triggering_element'])) {
      $generate = TRUE;
    }
  }

  $form_state['html5'] = FALSE;
  if (isset($_GET['type']) && $_GET['type'] == 'module') {
    $form_state['html5'] = TRUE;
  }
  if (isset($form['field_html5']['und']['#default_value']) && $form['field_html5']['und']['#default_value'] == 1) {
    $form_state['html5'] = TRUE;
  }

  return $generate;
}

/**
 * Adds option-specific classes to each child option for jQuery selection purposes.
 * @see Drupal.behaviors.sbac_resource_license in sbac_resource.form.js
 *
 * @param array $element
 *   The element.
 * @return array mixed
 *   The array.
 */
function sbac_resource_form_license_after_build($element) {
  if ($children = element_num_children($element)) {
    foreach ($children as $key => &$child) {
      $child['#attributes']['class'][] = 'license-option-' . $key;
    }
  }

  return $element;
}

/**
 * Cleans the moderation object, so it does what i say.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_clean_workbench_moderation($form, $form_state) {
  return;

  // Current clean up.
  if (isset($form_state['node']->workbench_moderation['current']->from_state)) {
    $form_state['node']->workbench_moderation['current']->from_state = workbench_moderation_state_none();
  }
  if (isset($form_state['node']->workbench_moderation['current']->state)) {
    $form_state['node']->workbench_moderation['current']->state = workbench_moderation_state_none();
  }
  if (isset($form_state['node']->workbench_moderation['current']->published)) {
    $form_state['node']->workbench_moderation['current']->published = FALSE;
  }
  // My Revision clean up.
  if (isset($form_state['node']->workbench_moderation['my_revision']->from_state)) {
    $form_state['node']->workbench_moderation['my_revision']->from_state = workbench_moderation_state_none();
  }
  if (isset($form_state['node']->workbench_moderation['my_revision']->state)) {
    $form_state['node']->workbench_moderation['my_revision']->state = workbench_moderation_state_none();
  }
  if (isset($form_state['node']->workbench_moderation['my_revision']->published)) {
    $form_state['node']->workbench_moderation['my_revision']->published = FALSE;
  }
}

/**
 * Submit handler for resource node form
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_save_and_close(&$form, &$form_state) {
  $node = $form_state['node'];
  sbac_resource_clean_text($form_state);
  // If there's a title, lets create a URL for the node.
  $form_state['values']['path']['pathauto'] = TRUE;
  $active_tab = NULL;
  if (isset($form_state['values']['additional_settings__active_tab']) &&
    $form_state['values']['additional_settings__active_tab']
  ) {
    $active_tab = $form_state['values']['additional_settings__active_tab'];
  }

  // If the save button was clicked via the modal, do the following.
  if ($active_tab == 'edit-group_advanced' &&
    isset($_SESSION['post_resource_clicked'])
    && $_SESSION['post_resource_clicked']
  ) {

    $original_posting_option = $_SESSION['sbac-original-posting-option'];
    $posting_option = $_SESSION['sbac-posting-option'];
    $chosen_option = $posting_option;
    if ($original_posting_option == $posting_option) {
      $chosen_option = 3;
    }
    if ($form_state['values']['workbench_moderation_state_current'] == 'draft') {
      if ($chosen_option > 1) {
        $chosen_option = 0;
      }
    }

    $task_type = '';
    switch ($chosen_option) {
      case 0:
        $form_state['values']['sticky'] = 0;
        $form_state['values']['workbench_moderation_state_new'] = 'published';
        if ('removed' == $node->workbench_moderation['current']->state) {
          $task_type = 'resource_reposted';
        }
        elseif ('published' == $node->workbench_moderation['current']->state && 1 == $node->sticky) {
          $task_type = 'resource_demoted';
        }
        break;
      case 1:
        $form_state['values']['sticky'] = 1;
        $form_state['values']['workbench_moderation_state_new'] = 'published';
        if ('removed' == $node->workbench_moderation['current']->state) {
          $task_type = 'resource_reposted';
        }
        elseif ('published' == $node->workbench_moderation['current']->state && 0 == $node->sticky) {
          $task_type = 'resource_promoted';
        }
        break;
      case 2:
        $form_state['values']['workbench_moderation_state_new'] = 'removed';
        if ('published' == $node->workbench_moderation['current']->state) {
          $task_type = 'removed_resource';
        }
        break;
      case 3:
        $form_state['values']['workbench_moderation_state_new'] = 'published';
        break;
      default:
        $form_state['values']['workbench_moderation_state_new'] = 'published';
    }

    if (!empty($task_type)) {
      if ($task = taskit_get_object($task_type)) {
        global $user;
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('node', $node->nid);
        // TODO: Figure out a way to keep a history of the comments. Right now it's just reading the current comment.
//            $task->addEntity('feedback', $form_state['values']['field_posting_options_comment']['und'][0]['value']);
        $task->addOwningUser($node->uid);
        $task->addTriggeringUser($user->uid);
        $task->save();
      }
    }

    unset($_SESSION['sbac-original-posting-option']);
    unset($_SESSION['sbac-posting-option']);
    unset($_SESSION['sbac-posting-option-comment']);
  }
  else { // User clicked the button.
    if (isset($form_state['values']['workbench_moderation_state_current']) &&
      $form_state['values']['workbench_moderation_state_current'] == 'published'
    ) {
      // Keep it in Published State.
      $form_state['values']['workbench_moderation_state_new'] = 'published';
    }
    else {
      // Set coming from state to Draft.
      $form_state['values']['workbench_moderation_state_current'] = 'draft';
      // Set state to Draft.
      $form_state['values']['workbench_moderation_state_new'] = 'draft';
    }
  }

  // Set the HTML5 flag.
  if ($form_state['html5']) {
    $form_state['values']['field_html5']['und'][0]['value'] = 1;
  }

  _sbac_resource_save_contributor_comments($form, $form_state);

  // Save the node.
  node_form_submit($form, $form_state);

  // Redirect the user to the correct place.
  if ($active_tab == 'edit-group_advanced' && isset($_SESSION['post_resource_clicked']) && $_SESSION['post_resource_clicked']) {
    unset($_SESSION['post_resource_clicked']);
    drupal_goto($form_state['redirect']);
  }
  else {
    // Check for an active tab, there should always be one.
    $active_tab = '';
    if (isset($form_state['values']['additional_settings__active_tab'])) {
      $active_tab = $form_state['values']['additional_settings__active_tab'];
    }

    $form_state['redirect'] = '/node/' . $form_state['node']->nid . '/edit#' . $active_tab;
    if (isset($_GET['destination'])) {
      unset($_GET['destination']);
    }
    drupal_custom_goto($form_state['redirect']);
  }
}


/**
 * After build function to remove workbench's form submit.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_after_build_resource_form(&$form, &$form_state) {
  foreach ($form['actions']['submit']['#submit'] as $key => $function) {
    if ($function == 'workbench_moderation_node_form_submit') {
      unset($form['actions']['submit']['#submit'][$key]);
    }
  }
  $form['field_alt_body'][LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE; // Note ‘und’, you may need to set your comment form language code instead
  $form['field_alt_body'][LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;

  return $form;
}


/**
 * Save and continue submit handler for resource node form.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_save_and_continue(&$form, &$form_state) {
  // Check for errors.
  $errors = form_get_errors();
  if ($errors) {
    $selector = NULL;
    foreach ($errors AS $field_name => $error_message) {
      if ($field_name == 'title' || $field_name == 'field_attributes' ||
        $field_name == 'field_focus' || $field_name == 'field_student_agency' ||
        $field_name == 'field_alt_body' || $field_name == 'field_connection_to_fap'
      ) {
        $selector = ".vertical-tabs-list li:nth-child(1) a";
        break;
      }
      if ($field_name == 'field_author' || $field_name == 'field_license') {
        $selector = ".vertical-tabs-list li:nth-child(2) a";
        break;
      }
      if ($field_name == 'field_contexts' || $field_name == 'field_connection_to_ccss' || $field_name == 'field_learning_goals' ||
        $field_name == 'field_success_criteria' || $field_name == 'field_supporting_evidence' || $field_name == 'field_principles' ||
        $field_name == 'field_subject' || $field_name == 'field_grades'
      ) {
        $selector = ".vertical-tabs-list li:nth-child(3) a";
        break;
      }
      if ($field_name == 'field_digital_media') {
        $selector = ".vertical-tabs-list li:nth-child(4) a";
        break;
      }
      if ($field_name == 'field_posting_options_comment') {
        $selector = ".vertical-tabs-list li:nth-child(5) a";
        break;
      }
    }

    if ($selector) {
      drupal_add_js(array('sbac_save_continue_tab' => $selector), 'setting');
    }
    drupal_add_js(array('sbac_resource_valid_state' => FALSE), 'setting');

    $active_tab = $form_state['values']['additional_settings__active_tab'];
    if ($active_tab == 'edit-group_materials') {
      if ($form_state['html5']) {
        $form = drupal_rebuild_form('resource_node_form', $form_state);
        return $form;
      }
    }
    
    $media_items = sbac_media_load_items($form['#node']->nid);
    $output = _sbac_media_create_list($media_items, $form_state);
    $form['field_file_container']['materials']['#markup'] = $output;
    $form['field_file_container']['materials']['#weight'] = -100;
    return $form;
  }

  if ($form_state['html5'] && isset($_SESSION['file_attributes'])) {
    $html5_progress = db_query('SELECT * FROM {sbac_html5_progress} WHERE nid = :nid', array(':nid' => $form['#node']->nid))->fetchObject();
    if (!$html5_progress) {
      error_log("TRYING TO REUPLOAD");
      // Setup callback options array; call sbac_media_html5_upload_asynchronous() in the background.
      $callback_options = array(
        array(
          'function' => 'sbac_media_html5_upload_asynchronous',
          // Setup options array.
          'options' => array(
            'timeout' => 1200,
            'global_timeout' => 1200,
          ),
        ),
        $_SESSION['file_attributes'],
      );
      // Queue up the request.
      httprl_queue_background_callback($callback_options);
      // Execute request.
      $response = httprl_send_request();
      error_log(print_r($response));
      if ($response === FALSE) {
        watchdog('SBAC Media', 'Failed to start background tasks', NULL, WATCHDOG_ERROR);
      }
    }
    unset($_SESSION['file_attributes']);
  }

  $duplicates = FALSE;
  $active_tab = $form_state['values']['additional_settings__active_tab'];
  if ($active_tab == 'edit-group_materials') {
    $media_items = sbac_media_load_items($form['#node']->nid);
    $duplicates = sbac_media_check_duplicates($media_items);
  }

  // Submit node, everything is good to go.
  $selector = NULL;
  $valid = FALSE;
  if ($active_tab != 'edit-group_advanced' && $active_tab != 'edit-group_flag') {
    ctools_include('ajax');
    switch ($active_tab) {
      case 'edit-group_materials':
        $selector = ".vertical-tabs-list li:nth-child(3) a";
        $valid = FALSE;
        break;
      case 'edit-group_basic':
        $selector = ".vertical-tabs-list li:nth-child(2) a";
        $valid = FALSE;
        break;
      case 'sbac-revisions-tab':
      case 'edit-group_tags':
        global $user;
        if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
          $valid = FALSE;
        }
        else {
          if ($active_tab == 'sbac-revisions-tab') {
            $valid = TRUE;
          }
          else {
            $query = new EntityFieldQuery();
            $submitted = (bool) $query->entityCondition('entity_type', 'feedback')
              ->entityCondition('bundle', 'gate_keeper')
              ->propertyCondition('completed', 1)
              ->propertyCondition('node_id', $form_state['node']->nid)
              ->count()
              ->execute();
            if ($submitted) {
              $valid = FALSE;
            }
            else {
              $valid = TRUE;
            }
          }
        }
        $selector = ".vertical-tabs-list li:nth-child(5) a";
        break;
      case 'edit-group_summary':
        $valid = FALSE;
        $selector = ".vertical-tabs-list li:nth-child(4) a";
        break;
    }

    if (isset($form_state['values']['workbench_moderation_state_current']) &&
      $form_state['values']['workbench_moderation_state_current'] == 'published'
    ) {
      // Keep it in Published State.
      $form_state['values']['workbench_moderation_state_new'] = 'published';
    }
    else {
      // Set coming from state to Draft.
      $form_state['values']['workbench_moderation_state_current'] = 'draft';
      // Set state to Draft.
      $form_state['values']['workbench_moderation_state_new'] = 'draft';
    }
  }

  $save_all_changes_modal = FALSE;
  global $user;
  if (isset($form_state['node']->workbench_moderation['current']->state) && $form_state['node']->workbench_moderation['current']->state == 'published') {
    if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
      $save_all_changes_modal = TRUE;
    }
  }
  // if the user is on the advanced tab, means they are a DLRB Member
  // or above, so pop the modal up when they click save.
  if ($active_tab == 'edit-group_advanced') {
    $save_all_changes_modal = TRUE;
  }

  // Cleans the text
  sbac_resource_clean_text($form_state);
  // Set path alias
  $form_state['values']['path']['pathauto'] = TRUE;
  // Set the HTML5 flag.
  if ($form_state['html5']) {
    $form_state['values']['field_html5']['und'][0]['value'] = 1;
  }

  // Handle the flag moderation.
  $sbac_flag = FALSE;
  $chosen_option = FALSE;
  if (isset($form_state['sbac-flag']) && $form_state['sbac-flag']) {
    $sbac_flag = TRUE;
    $chosen_option = $form_state['input']['chosen_flag_option'];
    if ($form_state['input']['changes_made'] == 1) {
      $_SESSION['sbac-flag']['changes-made'] = TRUE;
    }
    $form_state['values']['workbench_moderation_state_current'] = 'published';
    // Set state to Draft.
    $form_state['values']['workbench_moderation_state_new'] = 'published';
  }

  // Only save if non modal version.
  if (!$save_all_changes_modal) {
    // Save node and rebuild form.
    node_form_submit($form, $form_state);
    // Save the contributor's comments
    _sbac_resource_save_contributor_comments($form, $form_state);
  }
  // Rebuild form.
  $form = drupal_rebuild_form('resource_node_form', $form_state, $form);
  // Clear drupal messages.
  drupal_get_messages();

  if ($save_all_changes_modal) {
    $form['run_js'] = array(
      '#markup' => '<script>jQuery("#sbac-resource-save-all-changes").click();</script>',
    );
  }
  else {
    if ($duplicates) {
      $form['run_js'] = array(
        '#markup' => '<script>jQuery("#sbac-media-modal-duplicates").click();</script>',
      );
    }
    else {
      if ($sbac_flag) {
        if ($chosen_option == 1) { // resolve all flags.
          $form['run_js'] = array(
            '#markup' => '<script>jQuery("#sbac-flag-resolve-all-flags").click();</script>',
          );
        }
        else {
          $form['run_js'] = array(
            '#markup' => '<script>jQuery("#sbac-flag-remove-resource").click();</script>',
          );
        }
      }
      else {
        // Add appropriate JS.
        drupal_add_js(array('sbac_resource_valid_state' => $valid), 'setting');
        if ($selector) {
          drupal_add_js(array('sbac_save_continue_tab' => $selector), 'setting');
        }
      }
    }
  }

  return $form;
}

/**
 * Cancels the changes and redirects.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_cancel_all_changes_submit(&$form, &$form_state) {
  if (isset($form_state['clicked_button']['#value']) && $form_state['clicked_button']['#value'] == 'Close') {
    $form_state['redirect'] = 'digital-library-resources';
    drupal_redirect_form($form_state);
  }
}

/**
 * Implements hook_validate_form().
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_form(&$form, &$form_state) {
  // Do not validate on ajax events like "Upload"
  if ($form_state['submitted']) {
    switch ($form_state['values']['additional_settings__active_tab']) {
      case 'sbac-revisions-tab':
        sbac_resource_validate_general($form, $form_state);
        sbac_resource_validate_materials($form, $form_state);
        sbac_resource_validate_summary($form, $form_state);
        sbac_resource_validate_tags($form, $form_state);
        sbac_resource_validate_revisions($form, $form_state);
        break;
      case 'edit-group_materials':
        sbac_resource_validate_general($form, $form_state);
        sbac_resource_validate_materials($form, $form_state);
        break;
      case 'edit-group_basic':
        sbac_resource_validate_general($form, $form_state);
        break;
      case 'edit-group_tags':
        sbac_resource_validate_general($form, $form_state);
        sbac_resource_validate_materials($form, $form_state);
        sbac_resource_validate_summary($form, $form_state);
        sbac_resource_validate_tags($form, $form_state);
        break;
      case 'edit-group_summary':
        sbac_resource_validate_general($form, $form_state);
        sbac_resource_validate_materials($form, $form_state);
        sbac_resource_validate_summary($form, $form_state);
        break;
      case 'edit-group_advanced':
        sbac_resource_validate_general($form, $form_state);
        sbac_resource_validate_materials($form, $form_state);
        sbac_resource_validate_summary($form, $form_state);
        sbac_resource_validate_tags($form, $form_state);
        sbac_resource_validate_advanced($form, $form_state);
        break;
    }

    if (isset($form['#node']->nid)) {
      $check = node_last_changed($form['#node']->nid);
    }
    else {
      $check = $form['#node']->created;
    }

    $form_state['values']['changed'] = $check + 120;
  }
}

/**
 * Validation function for the title on save and close click.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_title(&$form, &$form_state) {
  if (!$form_state['values']['title']) {
    $error = 'Please add a title to save and close.';
    form_set_error('title', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:title:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:title:group:' . $error, 'sbac_resource_error');
  }
  else {
    $title = $form_state['values']['title'];
    $bad_words = profanity_validate_text($title);
    if ($bad_words) {
      $error = 'Please remove any inappropriate language to save and close.';
      form_set_error('title', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:title:single:' . $error, 'sbac_resource_error');
      drupal_set_message('general:title:group:' . $error, 'sbac_resource_error');
    }

    $dups = _sbac_resource_check_duplicated_title($form, $form_state, $title);
    if ($dups) {
      $error = "An identical title for the resource already exists in the Smarter Balanced Digital Library. Please enter a unique title to continue.";
      $error .= "<p class='smaller'>Tip: Incorporate audience grade, subject or topic details to differentiate your resource title</p>";
      form_set_error('title', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:title:single:' . $error, 'sbac_resource_error');
      drupal_set_message('general:title:group:' . $error, 'sbac_resource_error');
    }
  }
}

/**
 * Validation function for general section.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_general(&$form, &$form_state) {
  if (!$form_state['values']['title']) {
    $error = 'Please add a title to continue.';
    form_set_error('title', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:title:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:title:group:Add a title', 'sbac_resource_error');
  }
  else {
    $title = $form_state['values']['title'];
    $bad_words = profanity_validate_text($title);
    if ($bad_words) {
      $error = 'Please remove any inappropriate language to continue';
      form_set_error('title', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:title:single:Please remove any inappropriate language to continue', 'sbac_resource_error');
      drupal_set_message('general:title:group:Please remove any inappropriate language to continue', 'sbac_resource_error');
    }

    $dups = _sbac_resource_check_duplicated_title($form, $form_state, $title);
    if ($dups) {
      $error = "An identical title for the resource already exists in the Smarter Balanced Digital Library. Please enter a unique title to continue.";
      $error .= "<p class='smaller'>Tip: Incorporate audience grade, subject or topic details to differentiate your resource title</p>";
      form_set_error('title', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:title:single:' . $error, 'sbac_resource_error');
      drupal_set_message('general:title:group:' . $error, 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_focus']['und'][0]['tid']) {
    $error = 'You must select the resource type of this resource to continue';
    form_set_error('field_focus', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_focus:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_focus:group:Select the resource type', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_intended_end_user']['und'][0]['tid']) {
    $error = 'Please select an end user tag to continue';
    form_set_error('field_intended_end_user', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_intended_end_user:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_intended_end_user:group:Please select an end user tag to continue', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_attributes']['und'][0]['tid']) {
    $error = 'Please indicate at least one attribute to continue';
    form_set_error('field_attributes', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_attributes:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_attributes:group:Please indicate at least one attribute to continue', 'sbac_resource_error');
  }
  if ($form_state['values']['field_student_agency']['und'][0]['value'] == NULL) {
    $error = 'You must explain how the resource enables students to actively engage in the formative assessment process to continue';
    form_set_error('field_student_agency', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_student_agency:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_student_agency:group:Explain how the resource enables students to actively engage in the formative process', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_student_agency']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from student engagement to continue';
      form_set_error('field_student_agency', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:field_student_agency:single:' . $error, 'sbac_resource_error');
      drupal_set_message('general:field_student_agency:group:Remove inappropriate language from student engagement', 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_connection_to_fap']['und'][0]['value']) {
    $error = 'Please add a connection to the formative assessment process to continue';
    form_set_error('field_connection_to_fap', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_connection_to_fap:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_connection_to_fap:group:Add the connection to a connection to the formative assessment process', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_connection_to_fap']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the connection to the formative assessment process to continue';
      form_set_error('field_connection_to_fap', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:field_connection_to_fap:single:' . $error, 'sbac_resource_error');
      drupal_set_message('general:field_connection_to_fap:group:Remove inappropriate language from connection to the formative assessment process', 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_alt_body']['und'][0]['value']) {
    $error = 'Please add a resource summary to continue';
    form_set_error('field_alt_body', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_alt_body:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_alt_body:group:Please add a resource summary to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_alt_body']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the resource summary to continue';
      form_set_error('field_alt_body', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('general:field_alt_body:single:' . $error, 'sbac_resource_error');
      drupal_set_message('general:field_alt_body:group:Remove inappropriate language from the resource summary', 'sbac_resource_error');
    }
  }
}

/**
 * Validation function for summary section.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_summary(&$form, &$form_state) {
  if (!$form_state['values']['field_subject']['und'][0]['tid']) {
    $error = 'Please select a subject and domain tag to continue';
    form_set_error('field_subject', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_subject:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_subject:group:Please select a subject and domain tag to continue', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_grades']['und'][0]['tid']) {
    $error = 'Please select a grade tag to continue';
    form_set_error('field_grades', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_grades:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_grades:group:Please select a grade tag to continue', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_connection_to_ccss']['und'][0]['value']) {
    $error = 'Add a connection to the Common Core State Standards';
    form_set_error('field_connection_to_ccss', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_connection_to_ccss:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_connection_to_ccss:group:Add a connection to the Common Core State Standards', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_connection_to_ccss']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the Specific Connection to the Common Core State Standards to continue';
      form_set_error('field_connection_to_ccss', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_connection_to_ccss:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_connection_to_ccss:group:Remove inappropriate language from the Common Core Standards', 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_learning_goals']['und'][0]['value']) {
    $error = 'Please add learning goals to continue';
    form_set_error('field_learning_goals', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_learning_goals:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_learning_goals:group:Please add learning goals to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_learning_goals']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the learning goals to continue';
      form_set_error('field_learning_goals', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_learning_goals:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_learning_goals:group:Remove inappropriate language from the learning goals', 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_success_criteria']['und'][0]['value']) {
    $error = 'Please add success criteria to continue';
    form_set_error('field_success_criteria', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_success_criteria:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_success_criteria:group:Please add success criteria to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_success_criteria']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the success criteria to continue';
      form_set_error('field_success_criteria', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_success_criteria:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_success_criteria:group:Remove inappropriate language from the sucess criteria', 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_contexts']['und'][0]['value']) {
    $error = 'Add the context(s) in which the resource could be used';
    form_set_error('field_contexts', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_contexts:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_contexts:group:Add the context(s) in which the resource could be used', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_contexts']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the context(s) within which the resource could be used to continue';
      form_set_error('field_contexts', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_contexts:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_contexts:group:Remove inappropriate language from context(s) within which the resource could be used', 'sbac_resource_error');
    }
  }
  if (!$form_state['values']['field_supporting_evidence']['und'][0]['value']) {
    $error = 'Please add supporting evidence to continue';
    form_set_error('field_supporting_evidence', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_supporting_evidence:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_supporting_evidence:group:Please add supporting evidence to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_supporting_evidence']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the supporting evidence to continue';
      form_set_error('field_supporting_evidence', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_supporting_evidence:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_supporting_evidence:group:Remove inappropriate language from the supporting evidence', 'sbac_resource_error');
    }
  }

  if ($form_state['values']['field_principles']['und'][0]['value'] == NULL) {
    $error = 'Add Principles, Literature, or Research';
    form_set_error('field_principles', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_principles:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_principles:group:Add Principles, Literature, or Research', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_principles']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the principles, literature or research field to continue';
      form_set_error('field_principles', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_principles:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_principles:group:Remove inappropriate language from the principles, literature or research field', 'sbac_resource_error');
    }
  }
}

/**
 * Validation function for materials section.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_materials(&$form, &$form_state) {
  if ($form_state['html5']) {
    $media_items = sbac_media_load_html5_item($form['#node']->nid, TRUE);
    if (!$media_items) {
      $error = 'You must add a content module file to continue';
      form_set_error('field_content_module_picker', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('materials:field_content_module_picker:single:' . $error, 'sbac_resource_error');
      drupal_set_message('materials:field_content_module_picker:group:Provide a content module file', 'sbac_resource_error');
    }
  }
  else {
    $media_items = sbac_media_load_items($form['#node']->nid);
    if (!$media_items) {
      $error = 'You must add at least one material to continue';
      form_set_error('field_embed_video', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('materials:field_embed_video:single:' . $error, 'sbac_resource_error');
      drupal_set_message('materials:field_embed_video:group:Provide a material', 'sbac_resource_error');

      // field_file_upload
      form_set_error('field_file_upload', $error);
      _sbac_resource_remove_error_message($error);
    }
  }

  if ($form_state['values']['field_author']['und'][0]['value'] == NULL) {
    $error = 'Please enter an author to continue';
    form_set_error('field_author', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('materials:field_author:single:' . $error, 'sbac_resource_error');
    drupal_set_message('materials:field_author:group:Please enter an author to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_author']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the author to continue';
      form_set_error('field_author', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('materials:field_author:single:' . $error, 'sbac_resource_error');
      drupal_set_message('materials:field_author:group:Remove inappropriate language from the author', 'sbac_resource_error');
    }
  }
  if ($form_state['values']['field_publisher']['und'][0]['value'] == NULL) {
    $error = 'Please enter an owner to continue';
    form_set_error('field_publisher', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('materials:field_publisher:single:' . $error, 'sbac_resource_error');
    drupal_set_message('materials:field_publisher:group:Please enter an owner to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_publisher']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the source to continue';
      form_set_error('field_publisher', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('materials:field_publisher:single:' . $error, 'sbac_resource_error');
      drupal_set_message('materials:field_publisher:group:Remove inappropriate language from the owner', 'sbac_resource_error');
    }
  }
  if ($form_state['values']['field_license_information']['und'][0]['value'] != 0 && $form_state['values']['field_license']['und'][0]['tid'] == NULL) {
    $error = 'Please enter a license that allows you to post to continue';
    form_set_error('field_license', $error);
    form_set_error('field_license_information', 'nono');
    _sbac_resource_remove_error_message($error);
    _sbac_resource_remove_error_message('nono');
    drupal_set_message('materials:field_license:single:' . $error, 'sbac_resource_error');
    drupal_set_message('materials:field_license:group:Please enter a license that allows you to post to continue', 'sbac_resource_error');
  }
  if ($form_state['values']['field_pii']['und'][0]['value'] == NULL) {
    $error = 'Please certify that the files and Cover Profile adhere to the personally identifiable student information clause to continue';
    form_set_error('field_pii', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('materials:field_pii:single:' . $error, 'sbac_resource_error');
    drupal_set_message('materials:field_pii:group:' . $error, 'sbac_resource_error');
  }
  /*
  if ($form_state['values']['field_use_of_student_images']['und'][0]['value'] == NULL) {
    $error = 'You must certify that you have the necessary written approval, consent, and clearance to post any images of the specific students to continue';
    form_set_error('field_use_of_student_images', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('materials:field_use_of_student_images:single:' . $error, 'sbac_resource_error');
    drupal_set_message('materials:field_use_of_student_images:group:' . $error, 'sbac_resource_error');
  }
  */
}

/**
 * Validation function for revisions section
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_revisions(&$form, &$form_state) {
  if (!empty($form_state['values']['sbac_revisions'])) {
    $i = 1;
    foreach ($form_state['values']['sbac_revisions'] as $index => $feedback) {
      $text = $feedback['contributor_comment'];
      if ($text == '') {
        $error = "Please add a comment to question $i.";
      }
      else {
        $bad_words = profanity_validate_text($text);
        if ($bad_words) {
          $error = "Please remove any inappropriate language from question $i.";
        }
      }
      if (isset($error)) {
        form_set_error('sbac_revisions][' . $index . '][contributor_comment', $error);
        _sbac_resource_remove_error_message($error);
        drupal_set_message('revisions:field_contributor_comment_' . $index . ':single:' . $error, 'sbac_resource_error');
        drupal_set_message('revisions:field_contributor_comment_' . $index . ':group:' . $error, 'sbac_resource_error');
      }
      $i++;
    }
  }
}

/**
 * Validation function for tags section.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_tags(&$form, &$form_state) {
  if (!$form_state['values']['field_digital_media_type']['und'][0]['tid']) {
    $error = 'Please select a media type to continue';
    form_set_error('field_digital_media_type', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('tags:field_digital_media_type:single:' . $error, 'sbac_resource_error');
    drupal_set_message('tags:field_digital_media_type:group:Please select a media type to continue', 'sbac_resource_error');
  }
}

/**
 * Validation function for the
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_advanced($form, $form_state) {
  $error = FALSE;
  $required = FALSE;

  if (isset($form_state['html5']) && $form_state['html5'] == TRUE) {
    $html5_progress = db_query("SELECT * FROM {sbac_html5_progress} WHERE nid = " . $form['#node']->nid)->fetchObject();
    // If there is HTML5 progress record and its set to Finished or Error.
    if ($html5_progress && $html5_progress->status == SBAC_MEDIA_HTML5_ERROR) {
      $error = 'Module upload did not complete. Please try again.';
      form_set_error('field_posting_options_comment', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('advanced:html5:single:' . $error, 'sbac_resource_error');
      $error = TRUE;
    }
  }

  if (isset($form_state['values']['field_posting_options']['und'][0]['value'])) {
    if ($form_state['values']['field_posting_options']['und'][0]['value'] == 2) {
      $required = TRUE;
    }
  }

  if ($required) {
    if ($form_state['values']['field_posting_options_comment']['und'][0]['value'] == NULL) {
      $error = 'Please add a comment to contributor to continue';
      form_set_error('field_posting_options_comment', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('advanced:field_posting_options_comment:single:' . $error, 'sbac_resource_error');
      $error = TRUE;
    }
  }

  $text = NULL;
  if ($form_state['values']['field_posting_options_comment']['und'][0]['value'] != NULL) {
    $text = $form_state['values']['field_posting_options_comment']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the comment to contributor to continue';
      form_set_error('field_posting_options_comment', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('advanced:field_posting_options_comment:single:' . $error, 'sbac_resource_error');
      $error = TRUE;
    }
  }

  if (!$error) {
    $_SESSION['sbac-posting-option-comment'] = $text;
    $_SESSION['sbac-posting-option'] = $form_state['values']['field_posting_options']['und'][0]['value'];
    $_SESSION['sbac-original-posting-option'] = $form_state['values']['field_posting_option_hidden'];
    // remove the comment so that it doesn't show up on the node next time.
    $form_state['values']['field_posting_options_comment']['und'][0]['value'] = NULL;
  }
}

/**
 * Remove disabled from submit.
 *
 * @param $errors
 */
function sbac_resource_enable_submit($errors) {
  if (!drupal_get_messages(NULL, FALSE) && !$errors) {
    ctools_include('ajax');
    $output = array();
    $output[] = ajax_command_invoke('#sbac-resource-save-continue #edit-submit', 'removeAttr', array('disabled'));
    $output[] = ajax_command_invoke('#edit-save-continue', 'removeAttr', array('disabled'));
    print ajax_render($output);
    exit();
  }
}

/**
 * Modal callback
 *
 * @param bool $js
 * @return array|mixed
 */
function sbac_resource_modal_callback($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    drupal_add_js(drupal_get_path("module", "sbac_alignment") . "/js/sbac_alignment.js");

    drupal_add_js(array(
      'ctools-ccss-style' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 800,
          'height' => 580,
        ),
      ),
    ), 'setting');
    $output = array();
    $output[] = ctools_modal_command_dismiss();
    $output[] = ajax_command_before('#sbac-resource-alignment-tag-view', theme('status_messages'));
    $output[] = ajax_command_html('#sbac-resource-alignment-tag-view', views_embed_view('alignment', 'resource_admin_view', $_GET['nid']));

    module_load_include('inc', 'sbac_alignment', 'sbac_alignment.ajax');
    $output[] = ctools_modal_command_display('Common Core Standards Browser', sbac_alignment_ajax_alignment_page($_GET['nid']));

    print ajax_render($output);
    exit();
  }
  else {
    return;
  }
}

/**
 * Modal callback
 *
 * @param bool $js
 * @return array|mixed
 */
function sbac_resource_filter_modal_callback($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
    drupal_add_js(drupal_get_path("module", "sbac_alignment") . "/js/sbac_filter_alignment.js");

    drupal_add_js(array(
      'ctools-ccss-style' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 800,
          'height' => 580,
        ),
      ),
    ), 'setting');
    $output = array();
    $output[] = ctools_modal_command_dismiss();
    $output[] = ajax_command_before('#sbac-resource-alignment-tag-view', theme('status_messages'));
    $output[] = ajax_command_html('#sbac-resource-alignment-tag-view', views_embed_view('alignment', 'resource_admin_view', 0));

    module_load_include('inc', 'sbac_alignment', 'sbac_alignment.ajax');
    $output[] = ctools_modal_command_display('Select Common Core Standards', sbac_alignment_ajax_filter_alignment_page());

    print ajax_render($output);
    exit();
  }
  else {
    return;
  }
}

/**
 * Modal callback
 *
 * @param bool $js
 * @return array|mixed
 */
function sbac_resource_save_all_changes_modal_callback($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');

    $original_posting_option = $_SESSION['sbac-original-posting-option'];
    $posting_option = $_SESSION['sbac-posting-option'];
    $chosen_option = $posting_option;
    if ($original_posting_option == $posting_option) {
      $chosen_option = 3;
    }
    if (isset($_GET['state']) && $_GET['state'] == 'draft') {
      if ($chosen_option > 1) {
        $chosen_option = 0;
      }
    }

    switch ($chosen_option) {
      case 0:
        $description = 'You are about to post this resource without distinction.';
        break;
      case 1:
        $description = 'You are about to post this resource with distinction.';
        break;
      case 2:
        $description = 'You are about to remove this resource.';
        break;
      case 3:
        $description = 'You are about to save changes to a posted resource.';
        break;
      default:
        $description = 'You are about to save changes to a posted resource.';
    }

    $form_state = array(
      'title' => t($description),
      'ajax' => $js,
      'chosen_option' => $chosen_option,
      'state' => $_GET['state'],
    );

    $output = ctools_modal_form_wrapper('sbac_resource_save_all_changes_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        // All changes are saved in the save_and_close submit handler.
        $_SESSION['post_resource_clicked'] = TRUE;
        switch ($chosen_option) {
          case 0: // post without distinction.
            $output[] = ajax_command_callback('save_and_close', 'click');
            break;
          case 1: // post with distinction.
            $output[] = ajax_command_callback('save_and_close', 'click');
            break;
          case 2: // remove post.
            $output[] = ajax_command_callback('save_and_close', 'click');
            break;
          case 3: // save changes.
            $output[] = ajax_command_callback('save_and_close', 'click');
            break;
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
 * Modal callback
 *
 * @param bool $js
 * @return array|mixed
 */
function sbac_resource_submit_resource_modal_callback($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $form_state = array(
      'title' => t('To continue, confirm that you wish to submit this resource'),
      'ajax' => $js,
    );

    $output = ctools_modal_form_wrapper('sbac_resource_submit_resource_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        // TODO: using the nid from $_GET isn't safe - the user can modify it; can we pull
        // this value from $form_state?
        if (isset($_GET['nid'])) {
          $node = node_load($_GET['nid']);
          if ($node) {
            $output[] = ctools_ajax_command_redirect('my-resources');

            // create notification for resource author
            // is this a first submission or a re-submission?
            $recipients = array();
            $query = new EntityFieldQuery();
            $submitted = (bool) $query->entityCondition('entity_type', 'feedback')
              ->entityCondition('type', 'gate_keeper')
              ->propertyCondition('completed', 1)
              ->propertyCondition('node_id', $node->nid)
              ->count()
              ->execute();
            workbench_moderation_moderate($node, 'needs_review');
            if ($submitted) {
              if (!empty($node->field_recent_publishers[LANGUAGE_NONE])) {
                // If the node was returned by the poster, send them back to the poster, skip the QC and GK reviews
                workbench_moderation_moderate($node, 'approved');
                $task_type = 'resource_resubmitted';
                // get the current feedback for this node so we can notify the gk/reviewers
                $query = new EntityFieldQuery();
                $feedbacks = $query->entityCondition('entity_type', 'feedback')
                  ->propertyCondition('completed', 1)
                  ->propertyCondition('type', 'post')
                  ->propertyCondition('node_id', $node->nid)
                  ->execute();
                if (isset($feedbacks['feedback'])) {
                  foreach ($feedbacks['feedback'] as $feedback) {
                    $recipients[] = entity_load_single('feedback', $feedback->id);
                  }
                }
              }
              else {
                // if there is already a gatekeeper entry, then this is a re-submission
                $task_type = 'resource_resubmitted';
                // get the current feedback for this node so we can notify the gk/reviewers
                $query = new EntityFieldQuery();
                $feedbacks = $query->entityCondition('entity_type', 'feedback')
                  ->propertyCondition('completed', 1)
                  ->propertyCondition('type', array('qc', 'gate_keeper'), 'IN')
                  ->propertyCondition('node_id', $node->nid)
                  ->execute();
                if (isset($feedbacks['feedback'])) {
                  foreach ($feedbacks['feedback'] as $feedback) {
                    $recipients[] = entity_load_single('feedback', $feedback->id);
                  }
                }
              }
            }
            else {
              $task_type = 'resource_submitted';
            }

            // Save the current state of the node.
            sbac_resource_save_current_state($node);

            if ($task_type == 'resource_submitted') {
              if ($task = taskit_get_object($task_type)) {
                global $user;
                $task->addVisibility($task::VISIBILITY_USER);
                $task->addEntity('node', $node->nid);
                $task->addOwningUser($node->uid);
                $task->addTriggeringUser($user->uid);
                $task->save();
              }
            }
            else {
              if ($task = taskit_get_object($task_type)) {
                global $user;
                $task->addVisibility($task::VISIBILITY_USER);
                $task->addEntity('node', $node->nid);
                $task->addOwningUser($node->uid);
                $task->addTriggeringUser($user->uid);
                if (!empty($recipients)) {
                  send_review_notifications($task, $node, $recipients);
                }
              }
            }

            sbac_resource_print_about_this_tab($node);
          }
        }
      }
      else {
        drupal_add_js(array('sbac_resource_valid_state' => FALSE), 'setting');
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
 * Modal callback
 *
 * @param bool $js
 * @return array|mixed
 */
function sbac_resource_delete_resource_modal_callback($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
    $form_state = array(
      'title' => t('You are about to delete this resource'),
      'ajax' => TRUE,
      'nid' => $_GET['nid'],
    );

    $output = ctools_modal_form_wrapper('sbac_resource_delete_resource_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        if (isset($_GET['nid'])) {
          global $user;
          $node = node_load($_GET['nid']);
          if ($node && $node->uid == $user->uid) {
            $node->field_is_hidden[LANGUAGE_NONE][0]['value'] = 1;
            field_attach_update('node', $node);
          }
          $url = 'my-resources';
          $output[] = ctools_ajax_command_redirect($url);
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
 * Creates the completed flag for the form.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_create_complete_flag(&$form, &$form_state) {
  $general_valid = sbac_resource_check_general($form, $form_state);
  $form['completed_flag_basic'] = array(
    '#markup' => ($general_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div class="completed-flag" id="completed-flag-basic">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_basic'] = "group_basic";
  if ($general_valid) {
    drupal_add_js(array('sbac_general' => TRUE), 'setting');
  }
  // else {
  //   drupal_add_js(array('sbac_general' => FALSE), 'setting');
  // }

  $summary_valid = sbac_resource_check_summary($form, $form_state);
  $form['completed_flag_summary'] = array(
    '#markup' => ($summary_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div class="completed-flag" id="completed-flag-summary">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_summary'] = "group_summary";
  if ($summary_valid) {
    drupal_add_js(array('sbac_summary' => TRUE), 'setting');
  }
  // else {
  //   drupal_add_js(array('sbac_summary' => FALSE), 'setting');
  // }

  $materials_valid = sbac_resource_check_materials($form, $form_state);
  $form['completed_flag_materials'] = array(
    '#markup' => ($materials_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div class="completed-flag" id="completed-flag-materials">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_materials'] = "group_materials";
  if ($materials_valid) {
    drupal_add_js(array('sbac_materials' => TRUE), 'setting');
  }
  // else {
  //   drupal_add_js(array('sbac_materials' => FALSE), 'setting');
  // }

  $tags_valid = sbac_resource_check_tags($form, $form_state);
  $form['completed_flag_tags'] = array(
    '#markup' => ($tags_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div class="completed-flag" id="completed-flag-tags">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_tags'] = "group_tags";
  if ($tags_valid) {
    drupal_add_js(array('sbac_tags' => TRUE), 'setting');
  }
  // else {
  //   drupal_add_js(array('sbac_tags' => FALSE), 'setting');
  // }

  $advanced_valid = TRUE;
  // $advanced_valid = sbac_resource_check_advanced($form, $form_state);
  $form['completed_flag_advanced'] = array(
    '#markup' => ($advanced_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div id="completed-flag-advanced">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_advanced'] = "group_advanced";
  if ($advanced_valid) {
    drupal_add_js(array('sbac_advanced' => TRUE), 'setting');
  }
  // else {
  //   drupal_add_js(array('sbac_advanced' => FALSE), 'setting');
  // }
}

/**
 * Creates the opening title / description container.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_create_open_container(&$form, &$form_state) {
  $form['resource_basic_container_open'] = array(
    '#markup' => '<div class="sbac-resource-container">',
  );
  $form['#group_children']['resource_basic_container_open'] = "group_basic";
  $form['resource_summary_container_open'] = array(
    '#markup' => '<div class="sbac-resource-container">',
  );
  $form['#group_children']['resource_summary_container_open'] = "group_summary";
  $form['resource_materials_container_open'] = array(
    '#markup' => '<div class="sbac-resource-container">',
  );
  $form['#group_children']['resource_materials_container_open'] = "group_materials";
  $form['resource_tags_container_open'] = array(
    '#markup' => '<div class="sbac-resource-container">',
  );
  $form['#group_children']['resource_tags_container_open'] = "group_tags";
  $form['resource_advanced_container_open'] = array(
    '#markup' => '<div class="sbac-resource-container">',
  );
  $form['#group_children']['resource_advanced_container_open'] = "group_advanced";
}

/**
 * Creates the title of the resource field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_create_resource_title(&$form, &$form_state) {
  $default_value = "Untitled Resource";
  if ($form['title']['#default_value']) {
    $default_value = $form['title']['#default_value'];
  }
  if (isset($form_state['values']['title']) && $form_state['values']['title']) {
    $default_value = $form_state['values']['title'];
  }

  $form['title_of_resource_basic'] = array(
    '#markup' => $default_value,
    '#prefix' => '<h2 class="title-of-resource">',
    '#suffix' => '</h2>'
  );
  $form['#group_children']['title_of_resource_basic'] = "group_basic";

  $form['title_of_resource_summary'] = array(
    '#markup' => $default_value,
    '#prefix' => '<h2 class="title-of-resource">',
    '#suffix' => '</h2>'
  );
  $form['#group_children']['title_of_resource_summary'] = "group_summary";

  $form['title_of_resource_materials'] = array(
    '#markup' => $default_value,
    '#prefix' => '<h2 class="title-of-resource">',
    '#suffix' => '</h2>'
  );
  $form['#group_children']['title_of_resource_materials'] = "group_materials";

  $form['title_of_resource_tags'] = array(
    '#markup' => $default_value,
    '#prefix' => '<h2 class="title-of-resource">',
    '#suffix' => '</h2>'
  );
  $form['#group_children']['title_of_resource_tags'] = "group_tags";

  $form['title_of_resource_advanced'] = array(
    '#markup' => $default_value,
    '#prefix' => '<h2 class="title-of-resource">',
    '#suffix' => '</h2>'
  );
  $form['#group_children']['title_of_resource_advanced'] = "group_advanced";
}

/**
 * Creates the content type description.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_content_type_description(&$form, &$form_state) {
  $submission_general_guidelines = variable_get('sbac_resource_general_guide');
  $submission_material_guidelines = variable_get('sbac_resource_materials_guide');
  $submission_tags_guidelines = variable_get('sbac_resource_tags_guide');
  $submission_summary_guidelines = variable_get('sbac_resource_summary_guide');
  $submission_advanced_guidelines = variable_get('sbac_resource_advanced_guide');

  $form['submisison_general_guidelines'] = array(
    '#markup' => '<div class="short more-less active">' . sbac_resource_truncate($submission_general_guidelines, 300) . '<a href="#" class="more">Read More</a></div><div class="long more-less">' . $submission_general_guidelines . '<a href="#" class="less">Read Less</a></div>',
    '#prefix' => '<div id="submission-general-guidelines">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['submisison_general_guidelines'] = "group_basic";

  $form['submisison_material_guidelines'] = array(
    '#markup' => '<div class="short more-less active">' . sbac_resource_truncate($submission_material_guidelines, 300) . '<a href="#" class="more">Read More</a></div><div class="long more-less">' . $submission_material_guidelines . '<a href="#" class="less">Read Less</a></div>',
    '#prefix' => '<div id="submission-materials-guidelines">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['submisison_material_guidelines'] = "group_materials";

  $form['submisison_tags_guidelines'] = array(
    '#markup' => '<div class="short more-less active">' . sbac_resource_truncate($submission_tags_guidelines, 300) . '<a href="#" class="more">Read More</a></div><div class="long more-less">' . $submission_tags_guidelines . '<a href="#" class="less">Read Less</a></div>',
    '#prefix' => '<div id="submission-tags-guidelines">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['submisison_tags_guidelines'] = "group_tags";

  $form['submisison_summary_guidelines'] = array(
    '#markup' => '<div class="short more-less active">' . sbac_resource_truncate($submission_summary_guidelines, 300) . '<a href="#" class="more">Read More</a></div><div class="long more-less">' . $submission_summary_guidelines . '<a href="#" class="less">Read Less</a></div>',
    '#prefix' => '<div id="submission-summary-guidelines">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['submisison_summary_guidelines'] = "group_summary";

  $form['submisison_advanced_guidelines'] = array(
    '#markup' => '<div class="short more-less active">' . sbac_resource_truncate($submission_advanced_guidelines, 300) . '<a href="#" class="more">Read More</a></div><div class="long more-less">' . $submission_advanced_guidelines . '<a href="#" class="less">Read Less</a></div>',
    '#prefix' => '<div id="submission-advanced-guidelines">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['submisison_advanced_guidelines'] = "group_advanced";
}

/**
 * Creates the "content module" html output.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_module_flag(&$form, &$form_state) {
  if ($form_state['html5']) {
    $form['html5_identifier_basic'] = array(
      '#markup' => '<p class="html5-content"><span><i class="general foundicon-website"></i> Content Module</span></p>',
      '#prefix' => '<div class="html5-identifier" id="html5-identifier-basic">',
      '#suffix' => '</div>'
    );
    $form['#group_children']['html5_identifier_basic'] = "group_basic";

    $form['html5_identifier_materials'] = array(
      '#markup' => '<p class="html5-content"><span><i class="general foundicon-website"></i> Content Module</span></p>',
      '#prefix' => '<div class="html5-identifier" id="html5-identifier-materials">',
      '#suffix' => '</div>'
    );
    $form['#group_children']['html5_identifier_materials'] = "group_materials";

    $form['html5_identifier_summary'] = array(
      '#markup' => '<p class="html5-content"><span><i class="general foundicon-website"></i> Content Module</span></p>',
      '#prefix' => '<div class="html5-identifier" id="html5-identifier-summary">',
      '#suffix' => '</div>'
    );
    $form['#group_children']['html5_identifier_summary'] = "group_summary";

    $form['html5_identifier_tags'] = array(
      '#markup' => '<p class="html5-content"><span><i class="general foundicon-website"></i> Content Module</span></p>',
      '#prefix' => '<div class="html5-identifier" id="html5-identifier-tags">',
      '#suffix' => '</div>'
    );
    $form['#group_children']['html5_identifier_tags'] = "group_tags";

    $form['html5_identifier_advanced'] = array(
      '#markup' => '<p class="html5-content"><span><i class="general foundicon-website"></i> Content Module</span></p>',
      '#prefix' => '<div class="html5-identifier" id="html5-identifier-advanced">',
      '#suffix' => '</div>'
    );
    $form['#group_children']['html5_identifier_advanced'] = "group_advanced";
  }
}

/**
 * Creates the closing title / description container.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_create_close_container(&$form, &$form_state) {
  $form['resource_basic_container_close'] = array(
    '#markup' => '</div>',
  );
  $form['#group_children']['resource_basic_container_close'] = "group_basic";

  $form['resource_summary_container_close'] = array(
    '#markup' => '</div>',
  );
  $form['#group_children']['resource_summary_container_close'] = "group_summary";

  $form['resource_materials_container_close'] = array(
    '#markup' => '</div>',
  );
  $form['#group_children']['resource_materials_container_close'] = "group_materials";

  $form['resource_tags_container_close'] = array(
    '#markup' => '</div>',
  );
  $form['#group_children']['resource_tags_container_close'] = "group_tags";

  $form['resource_advanced_container_close'] = array(
    '#markup' => '</div>',
  );
  $form['#group_children']['resource_advanced_container_close'] = "group_advanced";
}

/**
 * Alters the general (basic) tab elements.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_basic(&$form, &$form_state) {
  global $user;
  // Title.
  $form['title']['#title'] = t('Title') . ' ' . theme('form_required_marker');
  $form['title']['#theme_options']['description at top'] = t('Enter a user-friendly name for the resource.');
  $form['title']['#maxlength'] = 120;
  $form['title']['#attributes']['maxlength_js_label'][0] = 'Character count: @remaining';
  $form['title']['#maxlength_js'] = TRUE;
  $form['title']['#required'] = FALSE;

  // Attributes
  $title = "Attributes of Formative Assessment Process";
  $form['field_attributes']['und']['#title'] = t('@title', array('@title' => $title)) . ' ' . theme('form_required_marker');

  // Student Engagement
  $form['field_student_agency']['und'][0]['value']['#title'] .= ' ' . theme('form_required_marker');

  $form['field_intended_end_user']['und']['#title'] = t('Intended End User(s)') . ' ' . theme('form_required_marker');
  if (isset($form['field_intended_end_user']['und']['#options']['_none'])) {
    unset($form['field_intended_end_user']['und']['#options']['_none']);
  }

  // Focus
  unset($form['field_focus']['und']['#options']['_none']);
  $form['field_focus']['und']['#title'] = t('Resource Type') . ' ' . theme('form_required_marker');

  // Remove Spotlight form option for non-admins
  if (!in_array('administrator', $user->roles)) {
    unset($form['field_focus'][LANGUAGE_NONE]['#options']['78686']);
  }

  // Remove Playlist form option for non-SLT's
  $is_slt  = sbac_report_is_slt($user);
  
  if (!$is_slt && !in_array('administrator', $user->roles)) {
    unset($form['field_focus'][LANGUAGE_NONE]['#options']['78306']);
  }
  else {
    $form['playlist_modal'] = array(
      '#markup' => '<div class="playlist-modal">
                      <h2>You are about to create a Playlist.</h2>
                      <p>Before continuing, please confirm that you have completed the training for this content type. Select "Continue" if you have completed the training.</p> 
                      <button id="playlist-modal-continue" class="button right close-reveal-modal">Continue</button><button class="button right secondary close-reveal-modal">Cancel</button>   
                    </div>',
      '#prefix' => '<div id="playlist-modal-container" class="reveal-modal">',
      '#suffix' => '</div>'        
    );
    $form['#group_children']['playlist_modal'] = 'group_basic';
    
  }

  // Connection to FAP
  $form['field_connection_to_fap']['und'][0]['value']['#title'] = t('Specific Connection to the Formative Assessment Process') . ' ' . theme('form_required_marker');

  // Body
  $form['field_alt_body']['und'][0]['value']['#title'] = t('Resource Summary') . ' ' . theme('form_required_marker');
}


/**
 * Alters the summary elements.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_summary(&$form, $form_state) {
  $form['field_subject']['und']['#title'] = t('Subjects and Domains') . ' ' . theme('form_required_marker');
  if (isset($form['field_subject']['und']['#options']['_none'])) {
    unset($form['field_subject']['und']['#options']['_none']);
  }
  $form['field_grades']['und']['#title'] = t('Grade(s)') . ' ' . theme('form_required_marker');
  if (isset($form['field_grades']['und']['#options']['_none'])) {
    unset($form['field_grades']['und']['#options']['_none']);
  }

  // Title
  $form['alignment_tag_title'] = array(
    '#markup' => '<h2>' . t('Common Core State Standard(s)') . '</h2>',
    '#prefix' => '<div class="form-item-title alignment-tag-title">',
    '#suffix' => '</div>',
    '#weight' => 22,
  );
  $form['#group_children']['alignment_tag_title'] = "group_summary";
  // Description
  $form['alignment_tag_description'] = array(
    '#markup' => '<p>' . t('Identify the standard(s) to which this resource is aligned. Note that Anchor Standards and Mathematical Practices are included alongside content standards for all grades.') . '</p>',
    '#prefix' => '<div class="form-item-title-help alignment-tag-title-help">',
    '#suffix' => '</div>',
    '#weight' => 23,
  );
  $form['#group_children']['alignment_tag_description'] = "group_summary";
  // Alignment View -> The initial load of the form does not have an nid.
  if (isset($form['#node']->nid)) {
    $form['alignment_tag_view'] = array(
      '#markup' => views_embed_view('alignment', 'resource_admin_view', $form['#node']->nid),
      '#prefix' => '<div id="sbac-resource-alignment-tag-view">',
      '#suffix' => '</div>',
      '#weight' => 23.5,
    );
    $form['#group_children']['alignment_tag_view'] = "group_summary";

    // Alignment Button
    $form['add_alignment_tag_button'] = array(
      '#markup' => l('Add Standard(s)', 'sbac_resource/nojs/add-alignment', array(
        'attributes' => array('title' => 'Add Standard(s)', 'class' => 'ctools-use-modal small button ctools-modal-ctools-ccss-style', 'id' => 'sbac-resource-modal-alignment'),
        'query' => array('nid' => $form['#node']->nid)
      )),
      '#weight' => 23.6,
    );
    $form['#group_children']['add_alignment_tag_button'] = "group_summary";
  }

  // Contexts
  $form['field_contexts']['und'][0]['value']['#title'] = t('Context(s) Within Which the Resource Could Be Used') . ' ' . theme('form_required_marker');
  // Connection to CCSS
  $form['field_connection_to_ccss']['und'][0]['value']['#title'] = t('Specific Connection to the Common Core State Standards') . ' ' . theme('form_required_marker');
  // Learning Goals
  $form['field_learning_goals']['und'][0]['value']['#title'] .= ' ' . theme('form_required_marker');
  // Success Critieria
  $form['field_success_criteria']['und'][0]['value']['#title'] .= ' ' . theme('form_required_marker');
  // Supporting Evidence
  $form['field_supporting_evidence']['und'][0]['value']['#title'] .= ' ' . theme('form_required_marker');
  // Principles
  $form['field_principles']['und'][0]['value']['#title'] = t('Principles, Literature, or Research') . ' ' . theme('form_required_marker');
}

/**
 * Creates the materials form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_materials(&$form, $form_state) {
  sbac_media_widget_form_element($form, $form_state);
  global $user;

  // Add Playlist template to Materials help text for SLTs 
  $is_slt  = sbac_report_is_slt($user);
   
  if ($is_slt || in_array('administrator', $user->roles)) {
    drupal_add_js(drupal_get_path('module', 'sbac_resource') . '/js/sbac_resource.playlist.form.js');
  }

  // License Informations
  // Let's remove the N/A Option from the license information section
  unset($form['field_license_information'][LANGUAGE_NONE]['#options']['_none']);
  $form['field_license_information'][LANGUAGE_NONE]['#after_build'][] = 'sbac_resource_form_license_after_build';
  $form['field_license_information'][LANGUAGE_NONE]['#id'] = 'sbac-license-information-field';

  //Show this when field_license_information option 0 or 1 is selected
  $state_license_either = array(
    'input[name="field_license_information[und]"]' => array(
      array('value' => '0'),
      array('value' => '1'),
    ),
  );

  $state_license_1 = array(
    'input[name="field_license_information[und]"]' => array(
      array('value' => '1'),
    ),
  );

  $form['field_author']['#states']['visible'] = $state_license_either;
  $form['field_author']['#states']['required'] = $state_license_either;
  // $form['field_author']['#states']['invisible'] = $state_license_2;
  $form['field_author']['und'][0]['value']['#maxlength'] = 150;

  //Show this when field_license_information option 0 or 1 is selected
  $form['field_publisher']['#states']['visible'] = $state_license_either;
  $form['field_publisher']['#states']['required'] = $state_license_either;
  // $form['field_publisher']['#states']['invisible'] = $state_license_2;
  $form['field_publisher']['und'][0]['value']['#maxlength'] = 150;

  //Show this when field_license_information option 1 is selected
  $form['field_license']['#states']['visible'] = $state_license_1;
  $form['field_license']['#states']['required'] = $state_license_1;
  $form['field_license']['und']['#options']['_none'] = '--Select License--';
  $form['field_license']['und']['#ajax'] = array(
    'wrapper' => 'sbac-resource-license-url',
    'callback' => 'sbac_resource_license_url',
    'method' => 'replace',
    'effect' => 'fade',
    'event' => 'change',
  );
  $form['field_license']['#suffix'] = '<div id="sbac-resource-license-url"></div>';

  $form['field_license_secondary']['#states']['visible'] = $state_license_1;
  $form['field_license_secondary']['und']['#options']['_none'] = '--Select License--';

  $copyright_access = FALSE;
  $owner_match = FALSE;
  $has_role = array_intersect($user->roles, array('administrator', 'DLRB member', 'moderator'));
  if (isset($form['#node'])) {
    $owner_uid = $form['#node']->uid;
    if ($user->uid == $owner_uid) {
      $owner_match = TRUE;
    }
  }
  if ((!empty($has_role)) || ($user->uid == 1) || ($owner_match)) {
    $copyright_access = TRUE;
  }
  $form['field_copyright_clearace_forms']['#access'] = $copyright_access;
  // $form['field_copyright_clearace_forms'][LANGUAGE_NONE]['#file_upload_title'] = '';
  $form['field_copyright_clearace_forms'][LANGUAGE_NONE]['#file_upload_description'] = '';
  $form['field_copyright_clearace_forms']['#states']['visible'] = $state_license_1;

  $form['group_license_information'] = array(
    '#prefix' => '<div id="license-information-group">',
    '#suffix' => '</div>',
  );

  $form['group_license_information']['field_license_url'] = array(
    '#weight' => 40,
  );

  sbac_resource_license_url($form, $form_state);

  $form['user_name'] = array(
    '#type' => 'hidden',
    '#value' => ucwords(full_name($user)),
    '#prefix' => '<div id="sbac-resource-user-name">',
    '#suffix' => '</div>',
  );
  $form['#group_children']['user_name'] = 'group_materials';
  $form['#group_children']['group_license_information'] = 'group_materials';
  $form['group_license_information']['field_author'] = $form['field_author'];
  $form['group_license_information']['field_publisher'] = $form['field_publisher'];
  $form['group_license_information']['field_license'] = $form['field_license'];
  $form['group_license_information']['field_license_secondary'] = $form['field_license_secondary'];
  // $form['group_license_information']['field_license_text'] = $form['field_license_text'];
  unset($form['field_author'], $form['field_publisher'], $form['field_license'], $form['field_license_secondary'] /*, $form['field_license_text']*/);
  unset($form['#group_children']['field_author'], $form['#group_children']['field_publisher'], $form['#group_children']['field_license'], $form['#group_children']['field_license_secondary'] /*, $form['#group_children']['field_license_text']*/);

  $form['no license'] = array(
    '#markup' => sbac_resource_licensing_form_has_no_license(),
    '#prefix' => "<div id= 'no-license-text'>",
    '#suffix' => '</div>',
    '#weight' => '130',
  );
  $form['#group_children']['no license'] = 'group_materials';

  $form['field_pii']['und']['#title'] .= ' ' . theme('form_required_marker');
  unset($form['field_pii']['und']['#options'][0]);

  if (isset($_GET['flag']) && ($_GET['flag'] == 'resolve-resource-flags' || $_GET['flag'] == 'view-resource-flags')) {
    if (isset($form['field_pii']['und'])) {
      $form['field_pii']['und']['#attributes']['checked'] = 'checked';
      $form['field_pii']['und']['#attributes']['onclick'] = 'return false;';
    }
  }
}

/**
 * Create revisions tab
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_revisions(&$form, $form_state) {
  global $user;
  if (isset($form['#node']->nid)) {
    if ($user->uid == $form['#node']->uid) {
      // what was the last feedback?
      $last_feedback_type = db_query("SELECT type FROM eck_feedback WHERE node_id = :nid AND completed = 1 ORDER BY changed DESC LIMIT 0, 1", array(':nid' => $form['#node']->nid))->fetchField();
      switch ($last_feedback_type) {
        case 'post':
        case 'qc':
          $post = NULL;
          if ($last_feedback_type == 'post') {
            $post_id = db_query("SELECT id FROM eck_feedback WHERE node_id = :nid AND type = 'post' AND completed = 1 ORDER BY changed DESC LIMIT 0, 1", array(':nid' => $form['#node']->nid))->fetchCol();
            $post_entities = entity_load('feedback', $post_id);

            if ($post_entities) {
              $post = current($post_entities);
            }
          }
          // Get the last 3 QC
          $qc_ids = db_query("SELECT id FROM {eck_feedback} WHERE node_id = :nid AND type = 'qc' AND completed = 1 AND changed > IFNULL((SELECT max(h.stamp) FROM {workbench_moderation_node_history} h WHERE h.state = 'needs_review' AND h.nid = :nid), 0) ORDER BY created ASC LIMIT 0, 3", array(
            ':nid' => $form['#node']->nid,
          ))->fetchCol();
          if (empty($qc_ids)) {
              $qc_ids = db_query("SELECT id FROM {eck_feedback} WHERE node_id = :nid AND type = 'qc' AND completed = 1 ORDER BY created ASC LIMIT 0, 3", array(
                  ':nid' => $form['#node']->nid,
              ))->fetchCol();
          }

          // check for QC feedbacks first
          $qc_entities = entity_load('feedback', $qc_ids);
          if (!empty($qc_entities)) {
            $form['sbac_revisions'] = array(
              '#type' => 'fieldset',
              '#title' => t('Revisions'),
              '#tree' => TRUE,
              '#group' => 'additional_settings',
              '#attributes' => array(
                'id' => 'sbac-revisions-tab',
              )
            );
            $form['sbac_revisions']['header'] = array(
              '#markup' => t('Quality Criteria'),
              '#prefix' => '<h2>',
              '#suffix' => '</h2>'
            );
            if (!empty($post)) {
              $post_comment = filter_xss(field_entity_value($post, 'field_to_contributor'));
              if ($post_comment != '') {
                $form['sbac_revisions']['post_comment'] = array(
                  '#markup' => $post_comment,
                  '#prefix' => '<h2>Posting comments</h2><p>',
                  '#suffix' => '</p>'
                );
              }
            }
            $form['sbac_revisions']['sub_header'] = array(
              '#markup' => t("Reviewer's Resource Recommendation"),
              '#prefix' => '<h5>',
              '#suffix' => '</h5>',
            );
            // QC recommendations
            $recommendations = '';
            $i = 1;
            foreach ($qc_entities as $entity) {
              $created = format_date($entity->created, 'full');
              $options = field_allowed_values('field_rec_options');
              $headline = $options[field_entity_value($entity, 'field_rec_options')];
              $comments = filter_xss(field_entity_value($entity, 'field_rec_rationale'));
              $recommendations .= theme('qc_teaser', array(
                'id' => $entity->id,
                'author' => t('Reviewer !count', array('!count' => $i)),
                'created' => $created,
                'headline' => $headline,
                'comments' => more_less_text($comments, 140),
              ));
              $form['sbac_revisions']['recommendations'] = array(
                '#markup' => $recommendations,
              );
              $i++;
            }
            // QC questions
            // get the resource type at the point where it was rejected. This is because the set of questions is determined by this value at that time.
            $query = "
              SELECT
                focus.field_focus_tid
              FROM {field_revision_field_focus} focus
              WHERE focus.entity_id = :nid
                    AND focus.revision_id =
                        (
                          SELECT
                            max(revision.vid)
                          FROM {node_revision} revision
                          WHERE revision.nid = :nid
                                AND revision.timestamp <
                                    (
                                      SELECT
                                        max(history.stamp)
                                      FROM {workbench_moderation_node_history} history
                                      WHERE history.state = 'rejected' AND history.nid = :nid
                                    )
                        )";
            $focus = db_query($query, array(':nid' => $form['#node']->nid))->fetchField();
            $questions_count = sizeof(field_entity_value(reset($qc_entities), 'field_review_set'));
            for ($i = 0; $i < $questions_count; $i++) {
              $question_title = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_title');
              $question_title = filter_text($question_title);
              $question_desc = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_description');
              $question_desc = filter_text($question_desc);
              $question_desc = more_less_text($question_desc, 300);
              $form['sbac_revisions']['feedback_' . $i] = array(
                '#type' => 'fieldset',
              );
              $form['sbac_revisions']['feedback_' . $i]['label'] = array(
                '#markup' => $i + 1 . '. ' . strip_tags($question_title),
              );
              $form['sbac_revisions']['feedback_' . $i]['description'] = array(
                '#markup' => $question_desc,
              );
              $form['sbac_revisions']['feedback_' . $i]['comments'] = array(
                '#markup' => t("Reviewer's Comments"),
              );
              $form['sbac_revisions']['feedback_' . $i]['reviewers_comments'] = array(
                '#type' => 'container',
              );
              // Reviewers' comments
              $j = 1;
              $question_ids = array();
              foreach ($qc_entities as $entity) {
                $questions = field_entity_value($entity, 'field_review_set');
                $level = field_entity_value($questions[$i], 'field_level');
                $comments = filter_xss(field_entity_value($questions[$i], 'field_comments'));
                $comments = more_less_text($comments, 140);
                $form['sbac_revisions']['feedback_' . $i]['reviewers_comments'][$j] = array(
                  '#type' => 'container',
                  '#attributes' => array(
                    'class' => array(
                      'col'
                    )
                  )
                );
                $form['sbac_revisions']['feedback_' . $i]['reviewers_comments'][$j]['author'] = array(
                  '#markup' => t('Reviewer !j', array('!j' => $j)),
                  '#prefix' => '<div class="author">',
                  '#suffix' => '</div>',
                );
                $form['sbac_revisions']['feedback_' . $i]['reviewers_comments'][$j]['created'] = array(
                  '#markup' => format_date($entity->changed, 'full'),
                  '#prefix' => '<div class="created">',
                  '#suffix' => '</div>',
                );
                $form['sbac_revisions']['feedback_' . $i]['reviewers_comments'][$j]['headline'] = array(
                  '#markup' => t('Quality Criteria Level: !level', array('!level' => $level)),
                  '#prefix' => '<div class="headline">',
                  '#suffix' => '</div>',
                );
                $form['sbac_revisions']['feedback_' . $i]['reviewers_comments'][$j]['comments'] = array(
                  '#markup' => $comments,
                  '#prefix' => '<div class="comments">',
                  '#suffix' => '</div>',
                );
                $question_ids[] = $questions[$i]->item_id;
                $j++;
              }
              $form['sbac_revisions']['feedback_' . $i]['contributor_comment'] = array(
                '#type' => 'textarea',
                '#title' => t("Contributor's comment <span class='form-required'>*</span><br/><span class='sub-title'>Please enter how this criterion has been addressed in this resubmission.</span>"),
                '#default_value' => field_entity_value($questions[$i], 'field_contributor_comment') ? filter_xss(field_entity_value($questions[$i], 'field_contributor_comment')) : ''
              );
              $form['sbac_revisions']['feedback_' . $i]['question_id'] = array(
                '#type' => 'hidden',
                '#value' => implode('::', $question_ids),
              );
            }
          } else {
            $form['sbac_revisions'] = array(
              '#type' => 'fieldset',
              '#title' => t('Revisions'),
              '#tree' => TRUE,
              '#group' => 'additional_settings',
              '#attributes' => array(
                'id' => 'sbac-revisions-tab',
              )
            );
            $form['sbac_revisions']['header'] = array(
              '#markup' => t('Quality Criteria'),
              '#prefix' => '<h2>',
              '#suffix' => '</h2>'
            );
            if (!empty($post)) {
              $post_comment = filter_xss(field_entity_value($post, 'field_to_contributor'));
              if ($post_comment != '') {
                $form['sbac_revisions']['post_comment'] = array(
                  '#markup' => $post_comment,
                  '#prefix' => '<h2>Posting comments</h2><p>',
                  '#suffix' => '</p>'
                );
              }
              $form['sbac_revisions']['feedback']['contributor_comment'] = array(
                '#type' => 'textarea',
                '#title' => t("Contributor's comment <span class='form-required'>*</span><br/><span class='sub-title'>Please enter how this criterion has been addressed in this resubmission.</span>"),
                '#default_value' => field_entity_value($post, 'field_contributor_comment') ? filter_xss(field_entity_value($post, 'field_contributor_comment')) : ''
              );
              $form['sbac_revisions']['feedback']['post_id'] = array(
                '#type' => 'hidden',
                '#value' => $post->id,
              );
            }
          }
          break;
        case 'gate_keeper':
          // Get the last gatekepper comment
          $gk_id = db_query("SELECT id FROM eck_feedback WHERE node_id = :nid AND type = 'gate_keeper' AND completed = 1 ORDER BY id DESC LIMIT 0, 1", array(':nid' => $form['#node']->nid))->fetchCol();
          // check for gk feedback
          $gk = entity_load('feedback', $gk_id);
          if (!empty($gk)) {
            $form['sbac_revisions'] = array(
              '#type' => 'fieldset',
              '#title' => t('Revisions'),
              '#tree' => TRUE,
              '#group' => 'additional_settings',
              '#attributes' => array(
                'id' => 'sbac-revisions-tab',
              )
            );
            $form['sbac_revisions']['header'] = array(
              '#markup' => t('Gate Keeping Criteria'),
              '#prefix' => '<h2>',
              '#suffix' => '</h2>'
            );
            $feedback = current($gk);
            $i = 1;
            foreach (field_entity_value($feedback, 'field_quality_set') as $question) {
              $question_title = variable_get('resource_gate_keeper_criteria_' . $i . '_title');
              $question_title = filter_text($question_title);

              $question_desc = variable_get('resource_gate_keeper_criteria_' . $i . '_description');
              $question_desc = filter_text($question_desc);
              $question_desc = more_less_text($question_desc, 300);

              $level = field_entity_value($question, 'field_meets_criterion');
              $level = $level ? t('Yes') : t('No');

              $form['sbac_revisions']['feedback_' . $i] = array(
                '#type' => 'fieldset'
              );
              $form['sbac_revisions']['feedback_' . $i]['question'] = array(
                '#markup' => $i . '. ' . strip_tags($question_title),
                '#prefix' => '<h5>',
                '#suffix' => '</h5>'
              );
              $form['sbac_revisions']['feedback_' . $i]['question_id'] = array(
                '#type' => 'hidden',
                '#value' => $question->item_id,
              );
              $form['sbac_revisions']['feedback_' . $i]['description'] = array(
                '#markup' => $question_desc
              );
              $form['sbac_revisions']['feedback_' . $i]['gk_info'] = array(
                '#type' => 'item',
                '#title' => t('Reviewer 1'),
                '#markup' => format_date($feedback->created, 'full')
              );
              $form['sbac_revisions']['feedback_' . $i]['gk_comment'] = array(
                '#type' => 'item',
                '#title' => t('Quality Criteria Level: !level', array('!level' => $level)),
                '#markup' => more_less_text(filter_xss(field_entity_value($question, 'field_comments')))
              );
              $form['sbac_revisions']['feedback_' . $i]['contributor_comment'] = array(
                '#type' => 'textarea',
                '#title' => t("Contributor's comment <span class='form-required'>*</span><br/><span class='sub-title'>Please enter how this criterion has been addressed in this resubmission.</span>"),
                '#default_value' => field_entity_value($question, 'field_contributor_comment') ? filter_xss(field_entity_value($question, 'field_contributor_comment')) : ''
              );
              $i++;
            }
          }
          break;
      }
    }
  }
}

/**
 * Container for the license url.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_license_url(&$form, &$form_state) {
  if (isset($form_state['values']['field_license']['und'][0]['tid'])) {
    if ($term = taxonomy_term_load($form_state['values']['field_license']['und'][0]['tid'])) {
      $content = '';

      if ($term->description) {
        $content = '
          <div id="edit-field-license-url" class="form-item form-type-item">
            <label for="edit-field-license-url">' . t('License URL') . '</label>
          ' . l($term->description, $term->description, array('attributes' => array('title' => $term->description))) . '
          </div>
        ';
      }

      $content = '<div id="sbac-resource-license-url">' . $content . '</div>';
      $form['group_license_information']['field_license_url']['#markup'] = $content;
    }
  }

  return $form['group_license_information']['field_license_url'];
}

/**
 * Creates the tags form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_tags(&$form, &$form_state) {
  // Hide access to Module Type to non DLRB members or above.
  global $user;
  if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
  }
  else {
    $form['field_smarter_balanced_keyword']['#access'] = FALSE;
  }

  // Resource Title
  $form['resource_tag_title'] = array(
    '#type' => 'item',
    '#markup' => '<h2>' . t('Resource Tags') . ' ' . theme('form_required_marker') . '</h2>',
    '#description' => t('Select tags that best describe this resource. You may choose as many as apply.'),
    '#prefix' => '<div class="form-item-title resource-tag-title">',
    '#suffix' => '</div>',
  );
  $form['#group_children']['resource_tag_title'] = "group_tags";

  $form['tag_wrapper'] = array(
    '#prefix' => '<div id="sbac-tags-wrapper">',
    '#suffix' => '</div>',
  );
  $form['#group_children']['tag_wrapper'] = "group_tags";

  if (isset($form['field_intended_student']['und']['#options']['_none'])) {
    unset($form['field_intended_student']['und']['#options']['_none']);
  }
  if (isset($form['field_geographical_settings']['und']['#options']['_none'])) {
    unset($form['field_geographical_settings']['und']['#options']['_none']);
  }
  if (isset($form['field_smarter_balanced_keyword']['und']['#options']['_none'])) {
    unset($form['field_smarter_balanced_keyword']['und']['#options']['_none']);
  }
  if (isset($form['field_educational_use']['und']['#options']['_none'])) {
    unset($form['field_educational_use']['und']['#options']['_none']);
  }
  if (isset($form['field_classroom_technologies']['und']['#options']['_none'])) {
    unset($form['field_classroom_technologies']['und']['#options']['_none']);
  }
  $form['field_digital_media_type']['und']['#title'] = t('Media Type(s)') . ' ' . theme('form_required_marker');
  if (isset($form['field_digital_media_type']['und']['#options']['_none'])) {
    unset($form['field_digital_media_type']['und']['#options']['_none']);
  }
  if (isset($form['field_view_permissions']['und']['#options']['_none'])) {
    unset($form['field_view_permissions']['und']['#options']['_none']);
  }
  $form['field_classroom_technologies']['und']['#title'] = t('Technologies Required for Use in Classroom');

  $form['tag_wrapper']['field_intended_student'] = $form['field_intended_student'];
  $form['tag_wrapper']['field_geographical_settings'] = $form['field_geographical_settings'];
  $form['tag_wrapper']['field_smarter_balanced_keyword'] = $form['field_smarter_balanced_keyword'];
  $form['tag_wrapper']['field_educational_use'] = $form['field_educational_use'];
  $form['tag_wrapper']['field_classroom_technologies'] = $form['field_classroom_technologies'];
  $form['tag_wrapper']['field_digital_media_type'] = $form['field_digital_media_type'];

  unset($form['field_intended_student']);
  unset($form['field_geographical_settings']);
  unset($form['field_smarter_balanced_keyword']);
  unset($form['field_educational_use']);
  unset($form['field_classroom_technologies']);
  unset($form['field_digital_media_type']);
}

/**
 * Creates the advanced section.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_advanced(&$form, &$form_state) {
  // Subscription Package Type.
  unset($form['field_subscription_package_type']['und']['#options']['_none']);
  if ($form['field_subscription_package_type']['und']['#default_value'] == NULL) {
    $form['field_subscription_package_type']['und']['#default_value'] = 0;
  }
  $form['field_subscription_package_type']['#weight'] = 37;

  // Permissions field.
  if ($form['field_view_permissions']['und']['#default_value'] == NULL) {
    $form['field_view_permissions']['und']['#default_value'] = 0;
  }
  $form['field_view_permissions']['und']['#prefix'] = '<div id="sbac-permissions-per-state">';
  $form['field_view_permissions']['und']['#suffix'] = '</div>';
  $form['field_subscription_package_type']['#weight'] = 38;

  // View permissions per state.
  $form['field_view_permissions_per_state']['und']['#title'] = '';
  $form['field_view_permissions_per_state']['und']['#prefix'] = '<div id="sbac-permissions-state">';
  $form['field_view_permissions_per_state']['und']['#suffix'] = '</div>';
  $form['field_view_permissions_per_state']['#weight'] = 40;

  // Resource Actions.
  $form['field_resource_actions']['#weight'] = 40;

  // Sharing options
  $form['resource_sharing_options'] = array(
    '#type' => 'item',
    '#markup' => '<h2>' . t('Sharing Options') . '</h2>',
    '#description' => t('By default, all resources have permanent private link that could be shared only with other users of the Digital Library.'),
    '#prefix' => '<div class="form-item-title resource-sharing-options">',
    '#suffix' => '</div>',
    '#weight' => 41,
  );
  $form['#group_children']['resource_sharing_options'] = "group_advanced";

  // Permanent link settings
  $form['field_permanent_link_settings']['und']['#attributes']['class'][] = 'sbac-permanent-link-settings';
  unset($form['field_permanent_link_settings']['und']['#options']['_none']);
  if ($form['field_permanent_link_settings']['und']['#default_value'] == NULL) {
    $form['field_permanent_link_settings']['und']['#default_value'] = 0;
  }
  $class = 'active';
  $disabled = FALSE;
  if (isset($form['field_permanent_link_settings']['und']['#default_value']) && $form['field_permanent_link_settings']['und']['#default_value'] == 1) {
    $class = 'inactive';
    $disabled = TRUE;
  }

  // Open a container
  $form['field_temp_container_open']['#markup'] = '<div id="sbac-temp-container" class="' . $class . '">';
  $form['field_temp_container_open']['#weight'] = 42;
  $form['#group_children']['field_temp_container_open'] = "group_advanced";

  // Temporary Link
  $form['field_temporary_public_link']['und']['#attributes']['class'][] = 'sbac-temporary-public-link';
  if ($disabled) {
    $form['field_temporary_public_link']['und']['#attributes']['disabled'] = 'disabled';
  }
  // Temporary Link Time
  $class = 'inactive';
  if (isset($form['field_temporary_public_link']['und']['#default_value'][0]) && $form['field_temporary_public_link']['und']['#default_value'][0] == 1) {
    $class = 'active';
  }
  if (!isset($form['field_temporary_public_link_time']['und']['#default_value'][0])) {
    $form['field_temporary_public_link_time']['und']['#default_value'][0] = 7; // 7 Days
  }
  unset($form['field_temporary_public_link_time']['und']['#options']['_none']);
  $form['field_temporary_public_link_time']['und']['#title'] = t('Set the limit from the time of link generation');
  $form['field_temporary_public_link_time']['#prefix'] = '<div class="sbac-temporary-link-time ' . $class . '">';
  $form['field_temporary_public_link_time']['#suffix'] = '</div>';
  $form['field_temporary_public_link_time']['#attributes']['class'][] = 'sbac-temp-link-list';
  if ($disabled) {
    $form['field_temporary_public_link_time']['und']['#attributes']['disabled'] = 'disabled';
  }

  $form['field_temp_container_close']['#markup'] = '</div>';
  $form['field_temp_container_close']['#weight'] = 45;
  $form['#group_children']['field_temp_container_close'] = "group_advanced";

  // Posting options.
  unset($form['field_posting_options']['und']['#options']['_none']);
  $form['field_posting_options']['und']['#prefix'] = '<div id="sbac-posting-options">';
  $form['field_posting_options']['und']['#suffix'] = '</div>';
  if (isset($form['#node']->workbench_moderation['current']->state) && $form['#node']->workbench_moderation['current']->state != 'published') {
    unset($form['field_posting_options']['und']['#options'][2]);
  }

  $form['field_posting_options_comment']['und']['#prefix'] = '<div id="sbac-posting-options-comment">';
  $form['field_posting_options_comment']['und']['#suffix'] = '</div>';
  if ($form['field_posting_options']['und']['#default_value'] == 2) {
    $form['field_posting_options_comment']['und'][0]['value']['#title'] .= ' ' . theme('form_required_marker');
  }

  $default_value = 0;
  if (isset($form['#node']->workbench_moderation)) {
    if ($form['#node']->workbench_moderation['current']->state == 'published') {
      $default_value = 0;
    }
    if ($form['#node']->workbench_moderation['current']->state == 'published' && $form['#node']->sticky == 1) {
      $default_value = 1;
    }
    if ($form['#node']->workbench_moderation['current']->state == 'removed') {
      $default_value = 2;
    }
  }
  $form['field_posting_options']['und']['#default_value'] = $default_value;

  // Hidden field to store original value.
  $form['field_posting_option_hidden'] = array(
    '#type' => 'hidden',
    '#value' => $default_value,
    '#attributes' => array('id' => 'sbac-posting-option-hidden'),
  );

  // Markup for js.
  $form['field_markup_for_js'] = array(
    '#markup' => '<div id="sbac-markup-for-js"></div>'
  );
}

/**
 * Creates the tags form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_submit_button(&$form, &$form_state) {
  unset($form['#submit']);
  unset($form['#validate']);
  unset($form['actions']['submit']['#submit']);
  $form['actions']['submit']['#validate'][] = 'sbac_resource_validate_title';
  $form['actions']['submit']['#value'] = t('Save');
  $form['actions']['submit']['#submit'] = array('sbac_resource_save_and_close');
  $form['actions']['submit']['#prefix'] = '<div id="sbac-resource-save-continue">';
  $form['actions']['submit']['#suffix'] = '</div>';
  $form['actions']['submit']['#weight'] = 1;
  $form['actions']['submit']['#attributes'] = array('id' => 'edit-submit');
}

/**
 * Creates the tags form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_save_continue_button(&$form, &$form_state) {
  $form['actions']['save_continue'] = array(
    '#type' => 'submit',
    '#value' => 'Continue',
    '#weight' => 2,
    '#validate' => array('sbac_resource_validate_form'),
    '#attributes' => array('id' => 'edit-save-continue'),
    '#ajax' => array(
      'wrapper' => 'sbac-resource-form',
      'callback' => 'sbac_resource_save_and_continue',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );
  $form['#after_build'][] = 'sbac_resource_after_build_resource_form';
}

/**
 * Creates the tags form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_cancel_button(&$form, &$form_state) {
  global $user;
  if ($user->uid == 1 ||
    in_array('DLRB member', $user->roles) ||
    in_array('digital library administrator', $user->roles) ||
    in_array('system administrator', $user->roles)
  ) {

    if (isset($form_state['node']->workbench_moderation['current']->state) && $form_state['node']->workbench_moderation['current']->state == 'published') {
      return;
    }
  }

  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Close',
    '#weight' => 0,
    '#attributes' => array('class' => array('sbac-cancel-blue', 'sbac-resource-cancel-button')),
    '#limit_validation_errors' => array(),
    '#submit' => array('sbac_media_widget_form_element_submit_handler', '_sbac_resource_my_resource_redirect'),
  );
}

/**
 * Submit the resource button.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_submit_resource(&$form, &$form_state) {
  if (isset($form['#node']->nid)) {
    $form['actions']['submit_resource'] = array(
      '#markup' => l(t('Submit Resource'), 'sbac_resource/nojs/submit-resource', array(
        'attributes' => array(
          'class' => 'ctools-use-modal button use-ajax ctools-modal-sbac-resource-modal-submit-resource',
          'id' => 'sbac-resource-modal-submit-resource',
          'title' => 'Submit Resource',
        ),
        'query' => array(
          'nid' => $form['#node']->nid
        )
      )),
      '#weight' => 3,
    );

    // JS to properly size the modal when submit resource is clicked.
    $js_settings = array(
      'sbac-resource-modal-submit-resource' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 600,
          'height' => 190,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting');
  }
}

/**
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_cancel_all_changes_button(&$form, &$form_state) {
  global $user;
  if (($user->uid == 1 ||
      in_array('DLRB member', $user->roles) ||
      in_array('digital library administrator', $user->roles) ||
      in_array('system administrator', $user->roles)) &&
    isset($form['#node']->workbench_moderation['current']->state) &&
    $form['#node']->workbench_moderation['current']->state == 'published'
  ) {

    $form['actions']['cancel_all_changes'] = array(
      '#type' => 'submit',
      '#value' => 'Close',
      '#weight' => 0,
      '#attributes' => array('class' => array('sbac-cancel-blue')),
      '#validate' => array('sbac_resource_cancel_all_changes_submit'),
      "#executes_submit_callback" => FALSE,
      '#limit_validation_errors' => array(),
    );
  }
}

/**
 * Save all changes button.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_save_all_changes_button(&$form, &$form_state) {
  if (isset($form['#node']->nid)) {
    $default_value = 0;
    if ($form['#node']->workbench_moderation['current']->state == 'published') {
      $default_value = 0;
    }
    if ($form['#node']->workbench_moderation['current']->state == 'published' && $form['#node']->sticky == 1) {
      $default_value = 1;
    }
    if ($form['#node']->workbench_moderation['current']->state == 'removed') {
      $default_value = 2;
    }

    $form['actions']['save_all_changes'] = array(
      '#markup' => l(t('Save All Changes (Modal)'), 'sbac_resource/nojs/save-all-changes', array(
        'attributes' => array(
          'class' => 'ctools-use-modal button use-ajax ctools-modal-sbac-resource-save-all-changes',
          'id' => 'sbac-resource-save-all-changes',
          'title' => 'Save All Changes',
        ),
        'query' => array(
          'nid' => $form['#node']->nid,
          'posting_option' => $default_value,
          'original_posting_option' => $default_value,
          'state' => $form['#node']->workbench_moderation['current']->state,
        )
      )),
      '#weight' => 4,
    );

    // JS to properly size the modal when submit resource is clicked.
    $js_settings = array(
      'sbac-resource-save-all-changes' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 600,
          'height' => 160,
        ),
        'modalTheme' => 'CtoolSbacResourceChangesModal',
      ),
    );
    drupal_add_js($js_settings, 'setting');
    drupal_add_js(drupal_get_path('module', 'sbac_resource') . '/js/sbac_resource.ctools.js');
  }
}

/**
 * Creates the tags form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_required_fields(&$form, &$form_state) {
  $form['required_fields_basic'] = array(
    '#markup' => 'Required Information',
    '#prefix' => '<p class="sbac-resource-required">',
    '#suffix' => '</p>',
    '#weight' => 150,
  );
  $form['#group_children']['required_fields_basic'] = "group_basic";

  $form['required_fields_summary'] = array(
    '#markup' => 'Required Information',
    '#prefix' => '<p class="sbac-resource-required">',
    '#suffix' => '</p>',
    '#weight' => 150,
  );
  $form['#group_children']['required_fields_summary'] = "group_summary";

  $form['required_fields_materials'] = array(
    '#markup' => 'Required Information <br /> <strong>**</strong> Temporary Files are not displayed on the front end until save or continue is clicked. Clicking close will remove the file.',
    '#prefix' => '<p class="sbac-resource-required">',
    '#suffix' => '</p>',
    '#weight' => 150,
  );
  $form['#group_children']['required_fields_materials'] = "group_materials";

  $form['required_fields_tags'] = array(
    '#markup' => 'Required Information',
    '#prefix' => '<p class="sbac-resource-required">',
    '#suffix' => '</p>',
    '#weight' => 150,
  );
  $form['#group_children']['required_fields_tags'] = "group_tags";
}

/**
 * Removes unwanted form elements.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_remove_elements(&$form, &$form_state) {
  (isset($form['actions']['preview_changes']) ? $form['actions']['preview_changes']['#access'] = FALSE : '');
  (isset($form['actions']['delete']) ? $form['actions']['delete']['#access'] = FALSE : '');

  $form['comment_settings']['#access'] = FALSE;
  $form['menu']['#access'] = FALSE;
  $form['path']['#access'] = FALSE;
  $form['print']['#access'] = FALSE;
  $form['revision_information']['#access'] = FALSE;
  $form['author']['#access'] = FALSE;
  $form['options']['#access'] = FALSE;
  $form['field_alignment_tags']['#access'] = FALSE;
  $form['field_temp']['#access'] = FALSE;
  $form['field_asset_downloads']['#access'] = FALSE;
  $form['field_total_views']['#access'] = FALSE;
  $form['field_unique_views']['#access'] = FALSE;
  $form['field_unique_downloads']['#access'] = FALSE;
  $form['field_node_avg_rating']['#access'] = FALSE;
  $form['field_alignment_term']['#access'] = FALSE;
  $form['field_document_id']['#access'] = FALSE;
  $form['field_document_information']['#access'] = FALSE;
  $form['field_resource_state']['#access'] = FALSE;
  $form['field_html5']['#access'] = FALSE;
  $form['field_thumbnail_uri']['#access'] = FALSE;
  $form['field_recent_reviewers']['#access'] = FALSE;
  $form['field_recent_publishers']['#access'] = FALSE;
  $form['field_is_hidden']['#access'] = FALSE;
}

/**
 * Finish of the form generation.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_finalize(&$form, &$form_state) {
  // Hide the Advanced fieldset if not DLRB member.
  global $user;
  if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
    drupal_add_js(array('sbac_dlrb_member' => TRUE), 'setting');
  }
  else {
    field_group_hide_field_groups($form, array('group_advanced'));
    drupal_add_js(array('sbac_dlrb_member' => FALSE), 'setting');
  }
}

/**
 * Checks if the section is in a valid state or not
 *
 * @param array $form
 * @param array $form_state
 * @return bool
 */
function sbac_resource_check_general($form, $form_state) {
  $valid = TRUE;

  // Submitted via ajax.
  if (isset($form_state['values'])) {
    if (!$form_state['values']['title']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_attributes']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_student_agency']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_focus']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_connection_to_fap']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_alt_body']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_intended_end_user']['und'][0]['tid']) {
      $valid = FALSE;
    }
  }
  else {
    if (empty($form['title']['#default_value'])) {
      $valid = FALSE;
    }
    if (empty($form['field_attributes']['und']['#default_value'][0])) {
      $valid = FALSE;
    }
    if (empty($form['field_student_agency']['und'][0]['value']['#default_value'])) {
      $valid = FALSE;
    }
    if (empty($form['field_focus']['und']['#default_value'])) {
      $valid = FALSE;
    }
    if (!$form['field_alt_body']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_connection_to_fap']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_intended_end_user']['und']['#default_value']) {
      $valid = FALSE;
    }
  }
  return $valid;
}

/**
 * Checks if the section is in a valid state or not.
 *
 * @param $form
 * @return bool
 */
function sbac_resource_check_summary($form, $form_state) {
  $valid = TRUE;

  if (isset($form_state['values'])) {
    if (!$form_state['values']['field_subject']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_grades']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_contexts']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_connection_to_ccss']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_learning_goals']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_success_criteria']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_supporting_evidence']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_principles']['und'][0]['value']) {
      $valid = FALSE;
    }

  }
  else {
    if (!$form['field_subject']['und']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_grades']['und']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_contexts']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_connection_to_ccss']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_learning_goals']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_success_criteria']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_supporting_evidence']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_principles']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
  }
  return $valid;
}

/**
 * Checks if the section is in a valid state or not.
 *
 * @param $form
 * @return bool
 */
function sbac_resource_check_materials($form, $form_state) {
  $valid = TRUE;
  if (isset($form_state['values'])) {
    if (isset($form_state['node']->nid)) {
      if ($form_state['html5']) {
        $media_items = sbac_media_load_html5_item($form_state['node']->nid);
        if (!$media_items) {
          // $valid = FALSE;
          return FALSE;
        }
      }
      else {
        $media_items = sbac_media_load_items($form_state['node']->nid);
        if (!$media_items) {
          // $valid = FALSE;
          return FALSE;
        }
      }
    }
    if (!$form_state['values']['field_author']['und'][0]['value']) {
      // $valid = FALSE;
      return FALSE;
    }
    if (!$form_state['values']['field_publisher']['und'][0]['value']) {
      // $valid = FALSE;
      return FALSE;
    }
    if (isset($form_state['field_license_information']['und'][0]['value']) && $form_state['field_license_information']['und'][0]['value'] == 0) {
      if (!$form_state['values']['field_license']['und'][0]['tid']) {
        // $valid = FALSE;
        return FALSE;
      }
    }
    if (!$form_state['values']['field_pii']['und'][0]['value']) {
      // $valid = FALSE;
      return FALSE;
    }
  }
  else {
    if (isset($form['#node']->nid)) {
      if ($form_state['html5']) {
        $media_items = sbac_media_load_html5_item($form['#node']->nid);
        if (!$media_items) {
          // $valid = FALSE;
          return FALSE;
        }
      }
      else {
        $media_items = sbac_media_load_items($form['#node']->nid);
        if (!$media_items) {
          // $valid = FALSE;
          return FALSE;
        }
      }
    }
    if (!$form['field_author']['und'][0]['value']['#default_value']) {
      // $valid = FALSE;
      return FALSE;
    }
    if (!$form['field_publisher']['und'][0]['value']['#default_value']) {
      // $valid = FALSE;
      return FALSE;
      // return TRUE;
    }
    if (isset($form['field_license_information']['und']['#default_value']) && $form['field_license_information']['und']['#default_value'] == 1) {
      if (!$form['field_license']['und']['#default_value']) {
        // $valid = FALSE;
        return FALSE;
      }
    }
    if (!isset($_GET['flag']) && !$form['field_pii']['und']['#default_value']) {
      // $valid = FALSE;
      return FALSE;
    }
  }
  return $valid;
}

/**
 * Checks if the section is in a valid state or not.
 *
 * @param $form
 * @return bool
 */
function sbac_resource_check_tags($form, $form_state) {
  $valid = TRUE;

  if (isset($form_state['values'])) {
    if (!$form_state['values']['field_digital_media_type']['und'][0]['tid']) {
      $valid = FALSE;
    }
  }
  else {
    if (!$form['field_digital_media_type']['und']['#default_value']) {
      $valid = FALSE;
    }
  }
  return $valid;
}

/**
 * Save all changes.
 *
 * @return array
 */
function sbac_resource_save_all_changes_form($form, $form_state) {
  switch ($form_state['chosen_option']) {
    case 0:
      $description = 'Posting this resource without distinction will display the resource in the Digital Library without the distinction badge.';
      if ($form_state['state'] == 'published') {
        $description .= ' Notification ´will be sent to the contributor.';
      }
      $button_text = 'Post Resource';
      break;
    case 1:
      $description = 'Posting this resource with distinction will display the resource in the Digital Library with the distinction badge.';
      if ($form_state['state'] == 'published') {
        $description .= ' Notification ´will be sent to the contributor.';
      }
      $button_text = 'Post Resource with Distinction';
      break;
    case 2:
      $description = 'Removing this resource will make it unavailable to Digital Library Community, including the contributor. You no longer will have
                      the ability to edit this resource. You can access this resource by going to a resource list in the administrative options.';
      $button_text = 'Remove Resource';
      break;
    case 3:
      $description = 'Save changes to this resource will make these changes visible to all users of the Digital Library.';
      $button_text = 'Save All Changes';
      break;
    default:
      $description = 'Save changes to this resource will make these changes visible to all users of the Digital Library.';
      $button_text = 'Save All Changes';
  }

  $form['submit_description'] = array(
    '#markup' => '<p>' . t($description) . '</p>',
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('id' => array('edit-cancel-overlay'))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t($button_text),
    '#attributes' => array('id' => array('edit-submit-overlay'))
  );

  return $form;
}

/**
 * The cancel / submit form
 *
 * @return array
 */
function sbac_resource_submit_resource_form() {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>' . t('
    Submitting this resource may make it accessible to Smarter Balanced Digital Library resource reviewers. You cannot edit your resource once it is submitted unless a reviewer returns it to you.') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit Resource',
    '#attributes' => array('id' => array('edit-submit-overlay'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('id' => array('edit-cancel-overlay'))
  );

  return $form;
}

/**
 * The cancel / delete form
 *
 * @return array
 */
function sbac_resource_delete_resource_form() {
  $form = array();

  $form['submit_description'] = array(
    '#markup' => '<p>' . t('
    If you continue, you will no longer be able to access this resource') . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete',
    '#attributes' => array('id' => array('edit-delete-overlay'))
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('id' => array('edit-cancel-overlay'))
  );

  return $form;
}

/**
 * Helper to remove error message from session.
 *
 * @param $value
 */
function _sbac_resource_remove_error_message($value) {
  if (isset($_SESSION['messages']['error'])) {
    $key = array_search($value, $_SESSION['messages']['error']);
    if ($key !== FALSE) {
      unset($_SESSION['messages']['error'][$key]);
    }
  }
}

/**
 * Checks for duplicated titles.
 *
 * @param $form
 * @param $form_state
 * @param $title
 * @return array
 */
function _sbac_resource_check_duplicated_title($form, $form_state, $title) {
  $duplicates = array();

  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->condition('n.title', $title);
  $query->condition('n.type', 'resource');
  if (isset($form_state['node']->nid)) {
    $query->condition('n.nid', $form_state['node']->nid, '<>');
  }

  $result = $query->execute();
  foreach ($result AS $row) {
    $duplicates[$row->nid] = $row;
  }

  return $duplicates;
}

/**
 * Digital Library page/tab - form for sorting the view.
 *
 *  Uses session variable to track user selected status. Defaults to "Newest"
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_resource_digital_library_sort_form($form, $form_state) {
  $form = array();
  $default = 'dl-newest'; // Hardcoded default. Change?
  $pwd_only = 0;

  // If session var is set, make it the default.
  if (isset($_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS]) &&
    $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS] != ''
  ) {
    $default = $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS];
  }
  if (isset($_SESSION[SBAC_SEARCH_DIGIAL_LIBRARY_RESOURCES_PWD]) &&
    $_SESSION[SBAC_SEARCH_DIGIAL_LIBRARY_RESOURCES_PWD] != ''
  ) {
    $pwd_only = $_SESSION[SBAC_SEARCH_DIGIAL_LIBRARY_RESOURCES_PWD];
  }

  $options = array(
    'dl-newest' => t('Newest'),
    'dl-most-viewed' => t('Most Viewed'),
    'dl-highest-rated' => t('Highest Rated'),
  );

  // Ajax submitted. Set Text if selected.
  if (isset($form_state['values']['dl_sort_order'])) {
    $new_value_key = $form_state['values']['dl_sort_order'];
    $old_value_text = $options[$new_value_key];
    $options[$new_value_key] = t('Sort by: ' . $old_value_text);
  }
  else {
    $options[$default] = t('Sort by: ' . $options[$default]);
  }


  // Needs to ajax submit to set the session variable that tracks default state.
  $form['dl_sort_order'] = array(
    '#prefix' => '<div id="form-wrapper-dl-sort-element">',
    '#suffix' => '</div>',
    '#type' => 'select',
    '#title' => t('Sort'),
    '#title_display' => 'invisible',
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => '_sbac_resource_digital_library_sort_form__ajax__change',
      'event' => 'change',
      'wrapper' => 'form-wrapper-dl-sort-element',
      'progress' => array('type' => 'none'),
    ),
  );

  $form['dl_pwd'] = array(
    '#prefix' => '<div id="sbac-pwd-check">',
    '#suffix' => '</div>',
    '#type' => 'checkbox',
    '#title' => "Posted with Distinction Only",
    '#default_value' => $pwd_only,
    '#ajax' => array(
      'callback' => '_sbac_resource_digital_library_sort_form__pwd',
      'event' => 'change',
      'wrapper' => 'sbac-pwd-check',
      'progress' => array('type' => 'none'),
    ),
  );

  return $form;
}

/**
 * Ajax Callback - Digital library sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_digital_library_sort_form__ajax__change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['dl_sort_order'];
  $_SESSION[SBAC_SEARCH_DIGITAL_LIBRARY_RESOURCES_SORTS] = $new_value_key;
  unset($_SESSION['load_more']['resources']['page']);

  // Just return the form, dont force page refresh.
  // return $form['dl_sort_order'];

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit;
}

/**
 * Sets value to determine posted with distinction
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_digital_library_sort_form__pwd($form, $form_state) {
  $key = $form_state['values']['dl_pwd'];
  $_SESSION[SBAC_SEARCH_DIGIAL_LIBRARY_RESOURCES_PWD] = $key;
  unset($_SESSION['load_more']['resources']['page']);

  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit;
}

/**
 * Resource Review page/tab - form for sorting the view.
 *
 *  Uses session variable to track user selected status. Defaults to "Oldest".
 *  Uses workbench moderation history timestamp as sorting.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_resource_resource_review_sort_form($form, $form_state) {
  $form = array();
  $default = 'rr-oldest'; // Hardcoded default. Change?

  // If session var is set, make it the default.
  if (isset($_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_SORTS]) &&
    $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_SORTS] != ''
  ) {
    $default = $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_SORTS];
  }

  $options = array(
    'rr-oldest' => t('Oldest'),
    'rr-newest' => t('Newest'),
  );

  // Ajax submitted. Set Text if selected.
  if (isset($form_state['values']['rr_sort_order'])) {
    $new_value_key = $form_state['values']['rr_sort_order'];
    $old_value_text = $options[$new_value_key];
    $options[$new_value_key] = t('Sort by: ' . $old_value_text);
  }
  else {
    $options[$default] = t('Sort by: ' . $options[$default]);
  }


  // Needs to ajax submit to set the session variable that tracks default state.
  $form['rr_sort_order'] = array(
    '#prefix' => '<div id="form-wrapper-rr-sort-element">',
    '#suffix' => '</div>',
    '#type' => 'select',
    '#title' => t('Sort'),
    '#title_display' => 'invisible',
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => '_sbac_resource_resource_review_sort_form__ajax__change',
      'event' => 'change',
      'wrapper' => 'form-wrapper-rr-sort-element',
      'progress' => array('type' => 'none'),
    ),
    '#attributes' => array(
      'class' => array(
        'no-chosen'
      )
    )
  );

  return $form;
}

/**
 * Ajax Callback - Resource Review sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_resource_review_sort_form__ajax__change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['rr_sort_order'];
  $_SESSION[SBAC_SEARCH_RESOURCE_REVIEW_SORTS] = $new_value_key;
  unset($_SESSION['load_more']['resource_review']['page']);

  // Just return the form, dont force page refresh.
  // return $form['rr_sort_order'];

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit;
}

/**
 * My Resources page/tab - form for sorting the view.
 *
 *  Uses session variable to track user selected status. Defaults to "Newest"
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_resource_my_resources_sort_form($form, $form_state) {
  $form = array();
  $default = 'mr-newest'; // Hardcoded default. Change?

  // If session var is set, make it the default.
  if (isset($_SESSION[SBAC_SEARCH_MY_RESOURCES_SORTS]) &&
    $_SESSION[SBAC_SEARCH_MY_RESOURCES_SORTS] != ''
  ) {
    $default = $_SESSION[SBAC_SEARCH_MY_RESOURCES_SORTS];
  }

  $options = array(
    'mr-newest' => t('Newest'),
    'mr-oldest' => t('Oldest'),
    'mr-alpha' => t('Alphabetical (A-Z)'),
  );

  // Ajax submitted. Set Text if selected.
  if (isset($form_state['values']['mr_sort_order'])) {
    $new_value_key = $form_state['values']['mr_sort_order'];
    $old_value_text = $options[$new_value_key];
    $options[$new_value_key] = t('Sort by: ' . $old_value_text);
  }
  else {
    $options[$default] = t('Sort by: ' . $options[$default]);
  }


  // Needs to ajax submit to set the session variable that tracks default state.
  $form['mr_sort_order'] = array(
    '#prefix' => '<div id="form-wrapper-mr-sort-element">',
    '#suffix' => '</div>',
    '#type' => 'select',
    '#title' => t('Sort'),
    '#title_display' => 'invisible',
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $default,
    '#ajax' => array(
      'callback' => '_sbac_resource_my_resources_sort_form__ajax__change',
      'event' => 'change',
      'wrapper' => 'form-wrapper-mr-sort-element',
      'progress' => array('type' => 'none'),
    ),
  );

  return $form;
}

/**
 * Ajax Callback - My Resources sort form
 *
 *  Ajax callback for the sort form. Sets corresponding session variable value
 *  that tracks the desired sorting method. On submission, triggers a page refresh.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_my_resources_sort_form__ajax__change($form, $form_state) {
  // Set session variable here. Session only gets set when form submits a change.
  $new_value_key = $form_state['values']['mr_sort_order'];
  $_SESSION[SBAC_SEARCH_MY_RESOURCES_SORTS] = $new_value_key;
  unset($_SESSION['load_more']['my_resources']['page']);

  // Just return the form, dont force page refresh.
  // return $form['mr_sort_order'];

  // Ctools ajax implementation using commands to refresh page.
  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_reload();
  print ajax_render($commands);
  exit;
}

/**
 * Displays the unsubmit modal.
 *
 * @param bool $js
 */
function sbac_resource_unsubmit_resource_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'title' => t("You are about to un-submit your resource"),
      'ajax' => $js,
      'nid' => $_GET['nid'],
    );

    $output = ctools_modal_form_wrapper('sbac_resource_unsubmit_resource_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        $node = node_load($form_state['nid']);
        if ($node) {
          workbench_moderation_moderate($node, 'draft');
          sbac_resource_save_current_state($node);
          $output[] = ctools_ajax_command_redirect('my-resources');
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
 * The unsubmit modal form.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_resource_unsubmit_resource_form($form, &$form_state) {
  $form['submit_description'] = array(
    '#markup' => '<p>Unsubmitting your resource will return your resource back to draft.
                 Your resource will no longer be in the review process until it is resubmitted.</p>',
  );

  $form['unsubmit'] = array(
    '#type' => 'submit',
    '#value' => 'Un-submit',
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
 * Jon's lack of comments.
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_resource_smart_search_builder_form($form, &$form_state) {
  $form = array();

  $vocabs = array(
    'subject' => t('Subjects'),
    'grades' => t('Grades'),
    'attributes' => t('Attributes of the Formative Assessment Process'),
    'digital_media_type' => t('Media Types'),
    'focus' => t('Resource Type'),
    'intended_end_user' => t('Intended End Users'),
    'intended_student_populations' => t('Intended Student Populations'),
    'educational_use' => t('Educational Use'),
    'smarter_balanced_keyword' => t('Module Type'),
    'geographical_settings' => t('Geographic Settings'),
  );
  $form['help_text'] = array(
    '#markup' => '<p>Select filters from the available options to create a url</p>',
    '#weight' => -3,
  );

  // Show the current setting. Clicking reset will unset the variable.
  $current_label = '<strong>Smart Search URL: </strong>';
  $current_value = variable_get(SBAC_RESOURCE_SMART_SEARCH_URL_VAR_NAME, '');
  if (empty($current_value)) {
    $current_value = '-- None --';
  }
  $form['current_url'] = array(
    '#type' => 'fieldset',
    '#title' => $current_label,
    '#collapsible' => FALSE,
    '#collapsed' => TRUE,
    '#weight' => -2,
  );
  $form['current_url']['cu_markup'] = array(
    '#markup' => $current_value,
    '#weight' => -1,
  );

  // Process any current filter settings. This is to set the default so user can see what the url filters by.
  $current_filters = array();
  $raw_url = explode('?', $current_value);
  if (count($raw_url) == 2) {
    $current_filters = drupal_get_query_array($raw_url[1]);
  }

  // Loop through list of vocabs to get the terms.
  $index = 0;
  foreach ($vocabs as $machine_name => $label) {
    $vocab_entity = taxonomy_vocabulary_machine_name_load($machine_name);
    $collapsed = TRUE;
    $defaults = array();

    // Process default settings.
    $default_key = $machine_name . ':' . $vocab_entity->vid;
    if (isset($current_filters[$default_key])) {
      $defaults = explode(',', $current_filters[$default_key]);
      $collapsed = FALSE;
    }

    // Create fieldset grouping
    $form[$machine_name] = array(
      '#type' => 'fieldset',
      '#title' => $label,
      '#weight' => $index,
      '#collapsible' => TRUE,
      '#collapsed' => $collapsed,
    );

    // Hide the vid so form_state has access to it.
    $form[$machine_name][$machine_name . '_vid'] = array(
      '#type' => 'value',
      '#value' => $vocab_entity->vid,
    );

    // Set options.
    $vocab_terms = array();
    $vocab_tree = taxonomy_get_tree($vocab_entity->vid);
    foreach ($vocab_tree as $term) {
      $children = taxonomy_get_children($term->tid);
      if (empty($children)) {
        $vocab_terms[$term->tid] = sbac_resource_taxonomy_term_concat_parents($term->tid, $term->name);
      }
    }
    $form[$machine_name][$machine_name . '_terms'] = array(
      '#type' => 'checkboxes',
      '#options' => $vocab_terms,
      '#default_value' => $defaults,
    );
    $index++;
  }

  $ccss_vocab = taxonomy_vocabulary_machine_name_load('education_alignment');
  $ccss_defaults = array();
  $ccss_default_key = 'education_alignment:' . $ccss_vocab->vid;
  $ccss_collapsed = TRUE;
  if (isset($current_filters[$ccss_default_key])) {
    $ccss_defaults = explode(',', $current_filters[$ccss_default_key]);
    $ccss_collapsed = FALSE;
  }
  $form['ccss_vid'] = array(
    '#type' => 'value',
    '#value' => $ccss_vocab->vid,
  );
  $form['ccss_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Common Core State Standards'),
    '#weight' => 97,
    '#collapsible' => TRUE,
    '#collapsed' => $ccss_collapsed,
  );
  $form['ccss_wrapper']['ccss_elements'] = array(
    '#type' => 'taxonomy_manager_tree',
    '#vid' => $ccss_vocab->vid,
    '#pager' => TRUE,
    '#default_value' => $ccss_defaults,
    '#terms_to_expand' => $ccss_defaults,
  );


  // Keyword search field
  $kw_collapsed = TRUE;
  $kw_default = '';
  if (isset($current_filters['kw'])) {
    $kw_default = urldecode($current_filters['kw']);
    $kw_collapsed = FALSE;
  }
  $form['kw_field'] = array(
    '#type' => 'fieldset',
    '#title' => t('Keyword Search'),
    '#weight' => 98,
    '#collapsible' => TRUE,
    '#collapsed' => $kw_collapsed,
  );
  $form['kw_field']['kw_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter keyword(s) to search by'),
    '#default_value' => $kw_default,
  );


  // Submit handlers.
  $form['generate'] = array(
    '#type' => 'submit',
    '#value' => 'Generate New',
    '#attributes' => array('class' => array('button', 'blue')),
    '#weight' => 99,
  );

  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => 'Reset',
    '#attributes' => array('class' => array('button', 'gray', 'cancel')),
    '#weight' => 100,
  );

  $history_links = variable_get(SBAC_RESOURCE_SMART_SEARCH_URL_HISTORY_VAR_NAME, array());
  if (!empty($history_links)) {
    $history_params = array(
      'items' => $history_links,
      'type' => 'ul',
    );
    $history = theme('item_list', $history_params);
    $form['history'] = array(
      '#type' => 'fieldset',
      '#title' => t('Generated URL History'),
      '#collapsible' => FALSE,
      '#collapsed' => TRUE,
      '#weight' => 101,
    );
    $form['history']['history_markup'] = array(
      '#markup' => $history,
      '#weight' => 1,
    );
    $form['history']['clear_history'] = array(
      '#type' => 'submit',
      '#value' => 'Clear History',
      '#attributes' => array('class' => array('button', 'blue')),
      '#weight' => 2,
    );

  }

  // Use to test existing urls.
  $form['tester'] = array(
    '#type' => 'fieldset',
    '#title' => t('Test URL'),
    '#description' => 'Paste a url here to test what filters it sets.',
    '#collapsible' => FALSE,
    '#collapsed' => TRUE,
    '#weight' => 102,
  );
  $form['tester']['test_url'] = array(
    '#type' => 'textfield',
    '#weight' => 103,
  );
  $form['tester']['test_url_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Test',
    '#attributes' => array('class' => array('button', 'blue')),
    '#weight' => 104,
  );

  return $form;
}

/**
 * Pulled a Jon.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_smart_search_builder_form_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Reset') {
    variable_set(SBAC_RESOURCE_SMART_SEARCH_URL_VAR_NAME, '');
  }
  elseif ($form_state['triggering_element']['#value'] == 'Test') {
    $values = $form_state['values'];
    $test_url = $values['test_url'];
    variable_set(SBAC_RESOURCE_SMART_SEARCH_URL_VAR_NAME, $test_url);
  }
  elseif ($form_state['triggering_element']['#value'] == 'Clear History') {
    variable_set(SBAC_RESOURCE_SMART_SEARCH_URL_HISTORY_VAR_NAME, array());
  }
  else { // Generate new.
    $values = $form_state['values'];
    $vocabs = array(
      'subject',
      'grades',
      'attributes',
      'digital_media_type',
      'focus',
      'intended_end_user',
      'intended_student_populations',
      'educational_use',
      'smarter_balanced_keyword',
      'geographical_settings',
      // 'technologies_for_classroom_use',
      // 'education_alignment',
    );

    $query_params = array();
    if (!empty($values['kw_text'])) {
      $query_params['kw'] = urlencode($values['kw_text']);
    }

    foreach ($vocabs as $machine_name) {
      $vid = $values[$machine_name . '_vid'];
      $term_key = $machine_name . '_terms';
      $checkboxes = $values[$term_key];
      $checked = array_filter($checkboxes);
      if (!empty($checked)) {
        $key = $machine_name . ':' . $vid;
        $value = implode(',', $checked);
        $query_params[$key] = $value;
      }
    }

    if (!empty($values['ccss_elements']['selected_terms'])) {
      $ccss_key = 'education_alignment:' . $values['ccss_vid'];
      $ccss_value = implode(',', $values['ccss_elements']['selected_terms']);
      $query_params[$ccss_key] = $ccss_value;
    }

    if (!empty($query_params)) {
      $url_params = array(
        'absolute' => TRUE,
        'query' => $query_params,
      );
      $link = url('dlr-smart-search', $url_params);
      $clean_link = urldecode($link);
      variable_set(SBAC_RESOURCE_SMART_SEARCH_URL_VAR_NAME, $clean_link);

      $history = variable_get(SBAC_RESOURCE_SMART_SEARCH_URL_HISTORY_VAR_NAME, array());
      $history[] = $clean_link;
      variable_set(SBAC_RESOURCE_SMART_SEARCH_URL_HISTORY_VAR_NAME, $history);
    }
  }
}

/**
 * Save the contributor's comments on the Revisions tab
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_save_contributor_comments(&$form, &$form_state) {
  // Save the contributor's comments
  if (!empty($form_state['values']['sbac_revisions'])) {
    foreach ($form_state['values']['sbac_revisions'] as $feedback) {
      if (!empty($feedback['question_id'])) {
        $question_ids = explode('::', $feedback['question_id']);
        foreach ($question_ids as $item_id) {
          $question = field_collection_item_load($item_id);
          if ($question) {
            $question_wrapper = entity_metadata_wrapper('field_collection_item', $question);
            $question_wrapper->field_contributor_comment->set($feedback['contributor_comment']);
            $question_wrapper->field_contributor_comment_date->set(time());
            $question_wrapper->save();
          }
        }
      }
      if(!empty($feedback['post_id'])){
        $post = entity_load_single('feedback', $feedback['post_id']);
        $post_wrapper = entity_metadata_wrapper('feedback', $post);
        $post_wrapper->field_contributor_comment->set($feedback['contributor_comment']);
        $post_wrapper->field_contributor_comment_date->set(time());
        $post_wrapper->save();
      }
    }
  }
}

/**
 * Submit action for 'Close' button.
 */
function _sbac_resource_my_resource_redirect() {
  drupal_goto('my-resources');
}

/**
 * Displays the two subnav/tabs
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_resource_resource_review_subnav_form($form, &$form_state) {
  $form = array();
  $resource_tab_classes = '';
  $resubmission_tab_classes = '';
  $active_tab = sbac_resource_get_active_subnav();
  switch ($active_tab) {
    case SBAC_RESOURCE_SUBNAV_RESOURCES:
      $resource_tab_classes = 'is-pressed';
      break;
    case SBAC_RESOURCE_SUBNAV_RESUBMISSIONS:
      $resubmission_tab_classes = 'is-pressed';
      break;
    default:
      break;
  }
  $form['container'] = array(
    '#type' => 'container'
  );

  $resource_tab_count_text = '0';
  if (isset($_SESSION[SBAC_RESOURCE_SUBNAV_RESOURCES_COUNT]) && !empty($_SESSION[SBAC_RESOURCE_SUBNAV_RESOURCES_COUNT])) {
    $resource_tab_count_text = $_SESSION[SBAC_RESOURCE_SUBNAV_RESOURCES_COUNT];
  }
  // Resources tab
  if (!isset($_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB]) || $_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB] === FALSE) {
    $form['container'] ['resources_tab'] = array(
      '#markup' => '<h3 class="left" style="color:#fff"><span>' . $resource_tab_count_text . '</span>' . t(' Resources') . '</h3>',
    );
  }
  else {
    $form['container'] ['resources_tab'] = array(
      '#type' => 'submit',
      '#value' => t('Resources') . ' (' . $resource_tab_count_text . ')',
      '#title' => t('Resources'),
      '#attributes' => array(
        'class' => array($resource_tab_classes),
      ),
      '#submit' => array('_sbac_resource_sub_nav__set_resource__submit'),
    );
  }

  // Resubmissions tab
  if (isset($_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB]) && $_SESSION[SBAC_RESOURCE_SUBNAV_SHOW_RESUBMISSION_TAB] === TRUE) {
    $resubmission_tab_count_text = '';
    $resubmission_tab_count_text = '(' . $_SESSION[SBAC_RESOURCE_SUBNAV_RESUBMISSIONS_COUNT] . ')';
    $form['container'] ['resubmissions_tab'] = array(
      '#type' => 'submit',
      '#value' => t('Resubmissions') . ' ' . $resubmission_tab_count_text,
      '#title' => t('Resubmissions'),
      '#attributes' => array(
        'class' => array($resubmission_tab_classes),
      ),
      '#submit' => array('_sbac_resource_sub_nav__set_resubmission__submit'),
    );
    $form['container']['#attributes'] = array('class' => array('with-resubmission'));
  }

  return $form;
}

/**
 * Submit handler for the resource tab
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_sub_nav__set_resource__submit($form, &$form_state) {
  sbac_resource_set_active_subnav(SBAC_RESOURCE_SUBNAV_RESOURCES);
}

/**
 * Submit handler for the resubmission tab
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_sub_nav__set_resubmission__submit($form, &$form_state) {
  sbac_resource_set_active_subnav(SBAC_RESOURCE_SUBNAV_RESUBMISSIONS);
}

/**
 * Get the current active subnav/tab
 *
 * @return string
 */
function sbac_resource_get_active_subnav() {
  $active_subnav = SBAC_RESOURCE_SUBNAV_RESOURCES;

  if (isset($_SESSION[SBAC_RESOURCE_SUBNAV_ACTIVE])) {
    if (!empty($_SESSION[SBAC_RESOURCE_SUBNAV_ACTIVE])) {
      $active_subnav = $_SESSION[SBAC_RESOURCE_SUBNAV_ACTIVE];
    }
  }
  return $active_subnav;
}

/**
 * Set the current subnav/tab
 *
 * @param null $value
 */
function sbac_resource_set_active_subnav($value = NULL) {
  if (!empty($value)) {
    $_SESSION[SBAC_RESOURCE_SUBNAV_ACTIVE] = $value;
  }
  else {
    $_SESSION[SBAC_RESOURCE_SUBNAV_ACTIVE] = '';
  }
}

/**
 * Form to update resource thumbnails.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_resource_update_thumb_form($form, &$form_state) {
  $form = array();

  $form['node_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Resource nid',
    '#required' => TRUE,
    '#description' => t('Enter the Node ID to be updated.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update Thumbnail',
  );

  return $form;
}

/**
 * Implements hook_form_validate().
 * Ensures that the node ID is a valid resource node.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_resource_update_thumb_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['node_id'])) {
    form_set_error('node_id', t('Please enter a number value.'));
  }
  $query = db_select('node', 'node');
  $query->fields('node', array('type'));
  $query->condition('nid', $form_state['values']['node_id'], '=');
  $result = $query->execute()->fetchAssoc();
  if (array_pop($result) != 'resource') {
    form_set_error('node_id', t($form_state['values']['node_id'] . ' is not a resource node type.'));
  }
}

/**
 * Implements hook_form_submit().
 * Updates the resource node's thumbnail.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_resource_update_thumb_form_submit($form, &$form_state) {
  if ($node = node_load($form_state['values']['node_id'])) {
    sbac_resource_determine_thumbnail_uri($node);
    entity_save_field(array('field_thumbnail_uri'), $node, 'node', $node->nid);
    $path = drupal_get_path_alias('node/' . $node->nid);
    drupal_goto($path);
  }
}
