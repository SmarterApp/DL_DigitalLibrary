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
      drupal_get_path('module','sbac_resource').'/css/sbac_resource.css',
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
      drupal_add_js(drupal_get_path("module", "sbac_help") . "/js/resource.js");
    }

    // Hide the Advanced fieldset if not DLRB member.
    global $user;
    if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
      drupal_add_js(array('sbac_dlrb_member' => TRUE), 'setting');
    }
    else {
      field_group_hide_field_groups($form, array('group_advanced'));
      drupal_add_js(array('sbac_dlrb_member' => FALSE), 'setting');
    }

    // Setup the form
    $generate = FALSE;
    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#value'] != 'Upload') {
      $generate = TRUE;
    }
    else if (!isset($form_state['triggering_element'])) {
      $generate = TRUE;
    }

    $form_state['html5'] = FALSE;
    if (isset($_GET['type']) && $_GET['type'] == 'module') {
      $form_state['html5'] = TRUE;
    }
    if (isset($form['field_html5']['und']['#default_value']) && $form['field_html5']['und']['#default_value'] == 1) {
      $form_state['html5'] = TRUE;
    }

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
    _sbac_resource_form_advanced($form, $form_state);
    _sbac_resource_form_cancel_all_changes_button($form, $form_state);
    _sbac_resource_form_save_all_changes_button($form, $form_state);
    _sbac_resource_form_submit_button($form, $form_state);
    _sbac_resource_form_save_continue_button($form, $form_state);
    _sbac_resource_form_cancel_button($form, $form_state);
    _sbac_resource_form_submit_resource($form, $form_state);
    _sbac_resource_form_required_fields($form, $form_state);
    _sbac_resource_form_remove_elements($form, $form_state);
  }
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
  sbac_resource_clean_text($form_state);
  // If there's a title, lets create a URL for the node.
  $form_state['values']['path']['pathauto'] = TRUE;
  $active_tab = NULL;
  if (isset($form_state['values']['additional_settings__active_tab']) &&
    $form_state['values']['additional_settings__active_tab']) {
    $active_tab = $form_state['values']['additional_settings__active_tab'];
  }


  // If the save button was clicked via the modal, do the following.
  if ($active_tab == 'edit-group_advanced' &&
    isset($_SESSION['post_resource_clicked'])
    && $_SESSION['post_resource_clicked']) {

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

    switch ($chosen_option) {
      case 0:
        $form_state['values']['sticky'] = 0;
        $form_state['values']['workbench_moderation_state_new'] = 'published';
        break;
      case 1:
        $form_state['values']['sticky'] = 1;
        $form_state['values']['workbench_moderation_state_new'] = 'published';
        break;
      case 2:
        $form_state['values']['workbench_moderation_state_new'] = 'removed';
        break;
      case 3:
        $form_state['values']['workbench_moderation_state_new'] = 'published';
        break;
      default:
        $form_state['values']['workbench_moderation_state_new'] = 'published';
    }

    if (isset($_SESSION['sbac-posting-option-comment']) && $_SESSION['sbac-posting-option-comment']) {
      // Create notificaton for contributor.
      if ($task = taskit_get_object('posting_action')) {
        global $user;
        $node = $form_state['node'];
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('node', $node->nid);
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
      $form_state['values']['workbench_moderation_state_current'] == 'published') {
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
    if (isset($form_state['values']['additional_settings__active_tab'])){
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
      if ($field_name == 'title' || $field_name == 'field_attributes' || $field_name == 'field_focus' || $field_name == 'field_student_agency') {
        $selector = ".vertical-tabs-list li:nth-child(1) a";
        break;
      }
      if ($field_name == 'field_author' || $field_name == 'field_license') {
        $selector = ".vertical-tabs-list li:nth-child(2) a";
        break;
      }
      if ($field_name == 'field_alt_body' || $field_name == 'field_contexts' || $field_name == 'field_connection_to_ccss' || $field_name == 'field_connection_to_fap' ||
        $field_name == 'field_learning_goals' || $field_name == 'field_success_criteria' || $field_name == 'field_supporting_evidence' || $field_name == 'field_principles'
      ) {
        $selector = ".vertical-tabs-list li:nth-child(3) a";
        break;
      }
      if ($field_name == 'field_subject' || $field_name == 'field_grades') {
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

      $media_items = sbac_media_load_items($form['#node']->nid);
      $output = _sbac_media_create_list($media_items, $form_state);
      $form['field_file_container']['materials']['#markup'] = $output;
      $form['field_file_container']['materials']['#weight'] = -100;
    }
    return $form;
  }

  $duplicates = FALSE;
  $active_tab = $form_state['values']['additional_settings__active_tab'];
  if ($active_tab == 'edit-group_materials') {
    $media_items = sbac_media_load_items($form['#node']->nid);
    $duplicates = sbac_media_check_duplicates($media_items);
  }

  // Submit node, everything is good to go.
  if ($active_tab != 'edit-group_advanced') {
    ctools_include('ajax');
    $selector = NULL;
    $valid = FALSE;
    $active_tab = $form_state['values']['additional_settings__active_tab'];
    switch ($active_tab) {
      case 'edit-group_materials':
        $selector = ".vertical-tabs-list li:nth-child(3) a";
        $valid = FALSE;
        break;
      case 'edit-group_basic':
        $selector = ".vertical-tabs-list li:nth-child(2) a";
        $valid = FALSE;
        break;
      case 'edit-group_tags':
        global $user;
        if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
          $valid = FALSE;
        }
        else {
          $valid = TRUE;
        }
        $selector = ".vertical-tabs-list li:nth-child(5) a";
        break;
      case 'edit-group_summary':
        $valid = FALSE;
        $selector = ".vertical-tabs-list li:nth-child(4) a";
        break;
    }

    if (isset($form_state['values']['workbench_moderation_state_current']) &&
      $form_state['values']['workbench_moderation_state_current'] == 'published') {
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
  // Only save if non modal version.
  if (!$save_all_changes_modal) {
    // Save node and rebuild form.
    node_form_submit($form, $form_state);
  }
  // Rebuild form.
  $form = drupal_rebuild_form('resource_node_form', $form_state, $form);
  // Clear drupal messages.
  drupal_get_messages();

  if ($duplicates) {
    $form['run_js'] = array(
      '#markup' => '<script>jQuery("#sbac-media-modal-duplicates").click();</script>',
    );
  }
  else if (!$save_all_changes_modal) {
    // Add appropriate JS.
    drupal_add_js(array('sbac_resource_valid_state' => $valid), 'setting');
    if ($selector) {
      drupal_add_js(array('sbac_save_continue_tab' => $selector), 'setting');
    }
  }
  else {
    $form['run_js'] = array(
      '#markup' => '<script>jQuery("#sbac-resource-save-all-changes").click();</script>',
    );
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
  if (isset($form_state['clicked_button']['#value']) && $form_state['clicked_button']['#value'] == 'Close') {
    $form_state['redirect'] = 'my-resources';
    drupal_redirect_form($form_state);
  }
  // Do not validate on ajax events like "Upload"
  if ($form_state['submitted']) {
    switch ($form_state['values']['additional_settings__active_tab']) {
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

  if (!$form_state['values']['field_attributes']['und'][0]['tid']) {
    $error = 'Please indicate at least one attribute to continue';
    form_set_error('field_attributes', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_attributes:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_attributes:group:Please indicate at least one attribute to continue', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_focus']['und'][0]['tid']) {
    $error = 'You must select the resource type of this resource to continue';
    form_set_error('field_focus', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('general:field_focus:single:' . $error, 'sbac_resource_error');
    drupal_set_message('general:field_focus:group:Select the resource type', 'sbac_resource_error');
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
}

/**
 * Validation function for summary section.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_summary(&$form, &$form_state) {
  if (!$form_state['values']['field_alt_body']['und'][0]['value']) {
    $error = 'Please add a resource summary to continue';
    form_set_error('field_alt_body', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_alt_body:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_alt_body:group:Please add a resource summary to continue', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_alt_body']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the resource summary to continue';
      form_set_error('field_alt_body', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_alt_body:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_alt_body:group:Remove inappropriate language from the resource summary', 'sbac_resource_error');
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

  if (!$form_state['values']['field_connection_to_fap']['und'][0]['value']) {
    $error = 'Please add a connection to the formative assessment process to continue';
    form_set_error('field_connection_to_fap', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('summary:field_connection_to_fap:single:' . $error, 'sbac_resource_error');
    drupal_set_message('summary:field_connection_to_fap:group:Add the connection to a connection to the formative assessment process', 'sbac_resource_error');
  }
  else {
    $text = $form_state['values']['field_connection_to_fap']['und'][0]['value'];
    $bad_words = profanity_validate_text($text);
    if ($bad_words) {
      $error = 'You must remove inappropriate language from the connection to the formative assessment process to continue';
      form_set_error('field_connection_to_fap', $error);
      _sbac_resource_remove_error_message($error);
      drupal_set_message('summary:field_connection_to_fap:single:' . $error, 'sbac_resource_error');
      drupal_set_message('summary:field_connection_to_fap:group:Remove inappropriate language from connection to the formative assesment process', 'sbac_resource_error');
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
    $media_items = sbac_media_load_html5_item($form['#node']->nid);
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
 * Validation function for tags section.
 *
 * @param $form
 * @param $form_state
 */
function sbac_resource_validate_tags(&$form, &$form_state) {
  // Select all alignments with this nid
  if (!$form_state['values']['field_subject']['und'][0]['tid']) {
    $error = 'Please select a subject and domain tag to continue';
    form_set_error('field_subject', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('tags:field_subject:single:' . $error, 'sbac_resource_error');
    drupal_set_message('tags:field_subject:group:Please select a subject and domain tag to continue', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_grades']['und'][0]['tid']) {
    $error = 'Please select a grade tag to continue';
    form_set_error('field_grades', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('tags:field_grades:single:' . $error, 'sbac_resource_error');
    drupal_set_message('tags:field_grades:group:Please select a grade tag to continue', 'sbac_resource_error');
  }
  if (!$form_state['values']['field_intended_end_user']['und'][0]['tid']) {
    $error = 'Please select an end user tag to continue';
    form_set_error('field_intended_end_user', $error);
    _sbac_resource_remove_error_message($error);
    drupal_set_message('tags:field_intended_end_user:single:' . $error, 'sbac_resource_error');
    drupal_set_message('tags:field_intended_end_user:group:Please select an end user tag to continue', 'sbac_resource_error');
  }
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
    $output[] = ajax_command_before('#sbac-resource-alignment-tag-view',theme('status_messages'));
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
            workbench_moderation_moderate($node, 'needs_review');
            node_access_acquire_grants($node, TRUE);
            $output[] = ctools_ajax_command_redirect('my-resources');

            // create notificaton for resource author
            if ($task = taskit_get_object('resource_submitted')) {
              global $user;

              $task->addVisibility($task::VISIBILITY_USER);
              $task->addEntity('node', $node->nid);
              $task->addOwningUser($node->uid);
              $task->addTriggeringUser($user->uid);
              $task->save();
            }
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
      'title' => t('You are about to delete this draft resource'),
      'ajax' => TRUE,
    );

    $output = ctools_modal_form_wrapper('sbac_resource_delete_resource_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {
        if (isset($_GET['nid'])) {
          node_delete($_GET['nid']);
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
  else {
    drupal_add_js(array('sbac_general' => FALSE), 'setting');
  }

  $summary_valid = sbac_resource_check_summary($form, $form_state);
  $form['completed_flag_summary'] = array(
    '#markup' => ($summary_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div class="completed-flag" id="completed-flag-basic">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_summary'] = "group_summary";
  if ($summary_valid) {
    drupal_add_js(array('sbac_summary' => TRUE), 'setting');
  }
  else {
    drupal_add_js(array('sbac_summary' => FALSE), 'setting');
  }

  $materials_valid = sbac_resource_check_materials($form, $form_state);
  $form['completed_flag_materials'] = array(
    '#markup' => ($materials_valid ? '<span class="section-complete"></span>' : '<span class="section-incomplete"></span>'),
    '#prefix' => '<div class="completed-flag" id="completed-flag-basic">',
    '#suffix' => '</div>'
  );
  $form['#group_children']['completed_flag_materials'] = "group_materials";
  if ($materials_valid) {
    drupal_add_js(array('sbac_materials' => TRUE), 'setting');
  }
  else {
    drupal_add_js(array('sbac_materials' => FALSE), 'setting');
  }

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
  else {
    drupal_add_js(array('sbac_tags' => FALSE), 'setting');
  }

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
  else {
    drupal_add_js(array('sbac_advanced' => FALSE), 'setting');
  }
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

  $form['submisison_general_guidelines'] = array (
    '#markup'   => '<div class="short more-less active">'.sbac_resource_truncate($submission_general_guidelines, 300).'<a href="#" class="more">Read More</a></div><div class="long more-less">'.$submission_general_guidelines .'<a href="#" class="less">Read Less</a></div>',
    '#prefix'   => '<div id="submission-general-guidelines">',
    '#suffix'   => '</div>'
  );
  $form['#group_children']['submisison_general_guidelines'] = "group_basic";

  $form['submisison_material_guidelines'] = array (
    '#markup'   => '<div class="short more-less active">'.sbac_resource_truncate($submission_material_guidelines, 300).'<a href="#" class="more">Read More</a></div><div class="long more-less">'.$submission_material_guidelines .'<a href="#" class="less">Read Less</a></div>',
    '#prefix'   => '<div id="submission-materials-guidelines">',
    '#suffix'   => '</div>'
  );
  $form['#group_children']['submisison_material_guidelines'] = "group_materials";

  $form['submisison_tags_guidelines'] = array (
    '#markup'   => '<div class="short more-less active">'.sbac_resource_truncate($submission_tags_guidelines, 300).'<a href="#" class="more">Read More</a></div><div class="long more-less">'.$submission_tags_guidelines .'<a href="#" class="less">Read Less</a></div>',
    '#prefix'   => '<div id="submission-tags-guidelines">',
    '#suffix'   => '</div>'
  );
  $form['#group_children']['submisison_tags_guidelines'] = "group_tags";

  $form['submisison_summary_guidelines'] = array (
    '#markup'   => '<div class="short more-less active">'.sbac_resource_truncate($submission_summary_guidelines, 300).'<a href="#" class="more">Read More</a></div><div class="long more-less">'.$submission_summary_guidelines .'<a href="#" class="less">Read Less</a></div>',
    '#prefix'   => '<div id="submission-summary-guidelines">',
    '#suffix'   => '</div>'
  );
  $form['#group_children']['submisison_summary_guidelines'] = "group_summary";

  $form['submisison_advanced_guidelines'] = array (
    '#markup'   => '<div class="short more-less active">'.sbac_resource_truncate($submission_advanced_guidelines, 300).'<a href="#" class="more">Read More</a></div><div class="long more-less">'.$submission_advanced_guidelines .'<a href="#" class="less">Read Less</a></div>',
    '#prefix'   => '<div id="submission-advanced-guidelines">',
    '#suffix'   => '</div>'
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
  // Title.
  $form['title']['#title'] = t('Title') . ' ' . theme('form_required_marker');
  $form['title']['#theme_options']['description at top'] = t('Enter a user-friendly name for the resource.');
  $form['title']['#maxlength'] = 75;
  $form['title']['#attributes']['maxlength_js_label'][0] = 'Character count: @remaining';
  $form['title']['#maxlength_js'] = TRUE;
  $form['title']['#required'] = FALSE;

  // Attributes
  $title = "Attributes of Formative Assessment Process";
  $form['field_attributes']['und']['#title'] = t('@title', array('@title' => $title)) . ' ' . theme('form_required_marker');

  // Student Engagement
  $form['field_student_agency']['und'][0]['value']['#title'] .= ' ' . theme('form_required_marker');

  // Focus
  unset($form['field_focus']['und']['#options']['_none']);
  $form['field_focus']['und']['#title'] = t('Resource Type') . ' ' . theme('form_required_marker');
}


/**
 * Alters the summary elements.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_summary(&$form, $form_state) {
  // Resource Summary.
  $form['field_resource_summary'] = array(
    '#type' => 'item',
    '#markup' => '<p>'.t('The following fields represent an abstract of the resource that includes the topics covered by the resource and how the resource should be used. Please enter information into each of the following sub-sections.').'</p>',
    '#weight' => 1,
  );
  $form['#group_children']['field_resource_summary'] = "group_summary";
  // Body
  $form['field_alt_body']['und'][0]['value']['#title'] = t('Resource Summary') . ' ' . theme('form_required_marker');
  // Contexts
  $form['field_contexts']['und'][0]['value']['#title'] = t('Context(s) Within Which the Resource Could Be Used') . ' ' . theme('form_required_marker');
  // Connection to CCSS
  $form['field_connection_to_ccss']['und'][0]['value']['#title'] = t('Specific Connection to the Common Core State Standards') . ' ' . theme('form_required_marker');
  // Connection to FAP
  $form['field_connection_to_fap']['und'][0]['value']['#title'] = t('Specific Connection to the Formative Assessment Process') . ' ' . theme('form_required_marker');
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

  // $state_license_2 = array(
  //   'input[name="field_license_information[und]"]' => array(
  //     array('value' => '2'),
  //   ),
  // );

  $form['field_author']['#states']['visible'] = $state_license_either;
  $form['field_author']['#states']['required'] = $state_license_either;
  // $form['field_author']['#states']['invisible'] = $state_license_2;
  $form['field_author']['und'][0]['value']['#maxlength'] = 75;

  //Show this when field_license_information option 0 or 1 is selected
  $form['field_publisher']['#states']['visible'] = $state_license_either;
  $form['field_publisher']['#states']['required'] = $state_license_either;
  // $form['field_publisher']['#states']['invisible'] = $state_license_2;
  $form['field_publisher']['und'][0]['value']['#maxlength'] = 75;

  /*
  //Show this when field_license_information option 0  is selected
  $form['field_license_text'] = array(
    '#markup' => '
      <div id="field_static_license_text" class="form-item">
        <label>' . $form['field_license']['und']['#title'] . '</label>
        <div class="description">' . t('The license language is identified in detail under Section 6 of the Terms of Service') . '</div>
        <div class="field-content">' . l(url('terms-of-service', array('absolute' => TRUE)), 'terms-of-service') . '</div>
      </div>
    ',
    '#weight' => $form['field_license']['#weight'],
  );
  */

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

  $form['group_license_information'] = array(
    '#prefix' => '<div id="license-information-group">',
    '#suffix' => '</div>',
  );

  $form['group_license_information']['field_license_url'] = array(
    '#weight' => 40,
  );

  sbac_resource_license_url($form, $form_state);

  global $user;
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
  unset($form['field_author'], $form['field_publisher'], $form['field_license'], $form['field_license_secondary']/*, $form['field_license_text']*/);
  unset($form['#group_children']['field_author'], $form['#group_children']['field_publisher'], $form['#group_children']['field_license'], $form['#group_children']['field_license_secondary']/*, $form['#group_children']['field_license_text']*/);

  $form['no license'] = array(
    '#markup' => sbac_resource_licensing_form_has_no_license(),
    '#prefix' => "<div id= 'no-license-text'>",
    '#suffix' => '</div>',
    '#weight' => '130',
  );
  $form['#group_children']['no license'] = 'group_materials';

  $form['field_pii']['und']['#title'] .= ' ' . theme('form_required_marker');
  unset($form['field_pii']['und']['#options'][0]);
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
          ' . l($term->description, $term->description) . '
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
  // Hide access to smarter balanced keywords to non DLRB members or above.
  global $user;
  if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
  }
  else {
    $form['field_smarter_balanced_keyword']['#access'] = FALSE;
  }

  // Resource Title
  $form['resource_tag_title'] = array(
    '#type' => 'item',
    '#markup' => '<h2>'.t('Resource Tags') . ' ' . theme('form_required_marker').'</h2>',
    '#description' => t('Select tags that best describe this resource. You may choose as many as apply.'),
    '#prefix' => '<div class="form-item-title resource-tag-title">',
    '#suffix' => '</div>',
  );
  $form['#group_children']['resource_tag_title'] = "group_tags";

  $form['tag_wrapper'] = array(
    '#prefix'=>'<div id="sbac-tags-wrapper">',
    '#suffix'=>'</div>',
  );
  $form['#group_children']['tag_wrapper'] = "group_tags";

  $form['field_subject']['und']['#title'] = t('Subjects and Domains') . ' ' . theme('form_required_marker');
  if (isset($form['field_subject']['und']['#options']['_none'])) {
    unset($form['field_subject']['und']['#options']['_none']);
  }
  $form['field_grades']['und']['#title'] = t('Grade(s)') . ' ' . theme('form_required_marker');
  if (isset($form['field_grades']['und']['#options']['_none'])) {
    unset($form['field_grades']['und']['#options']['_none']);
  }
  $form['field_intended_end_user']['und']['#title'] = t('Intended End User(s)') . ' ' . theme('form_required_marker');
  if (isset($form['field_intended_end_user']['und']['#options']['_none'])) {
    unset($form['field_intended_end_user']['und']['#options']['_none']);
  }
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

  $form['tag_wrapper']['field_subject'] = $form['field_subject'];
  $form['tag_wrapper']['field_grades'] = $form['field_grades'];
  $form['tag_wrapper']['field_intended_end_user'] = $form['field_intended_end_user'];
  $form['tag_wrapper']['field_intended_student'] = $form['field_intended_student'];
  $form['tag_wrapper']['field_geographical_settings'] = $form['field_geographical_settings'];
  $form['tag_wrapper']['field_smarter_balanced_keyword'] = $form['field_smarter_balanced_keyword'];
  $form['tag_wrapper']['field_educational_use'] = $form['field_educational_use'];
  $form['tag_wrapper']['field_classroom_technologies'] = $form['field_classroom_technologies'];
  $form['tag_wrapper']['field_digital_media_type'] = $form['field_digital_media_type'];

  unset($form['field_subject']);
  unset($form['field_grades']);
  unset($form['field_intended_end_user']);
  unset($form['field_intended_student']);
  unset($form['field_geographical_settings']);
  unset($form['field_smarter_balanced_keyword']);
  unset($form['field_educational_use']);
  unset($form['field_classroom_technologies']);
  unset($form['field_digital_media_type']);

  // Title
  $form['alignment_tag_title'] = array(
    '#markup' => '<h2>'.t('Common Core State Standard(s)').'</h2>',
    '#prefix' => '<div class="form-item-title alignment-tag-title">',
    '#suffix' => '</div>',
    '#weight' => 100,
  );
  $form['#group_children']['alignment_tag_title'] = "group_tags";

  // Description
  $form['alignment_tag_description'] = array(
    '#markup' => '<p>'.t('Identify the standard(s) to which this resource is aligned. Note that Anchor Standards and Mathematical Practices are included alongside content standards for all grades.').'</p>',
    '#prefix' => '<div class="form-item-title-help alignment-tag-title-help">',
    '#suffix' => '</div>',
    '#weight' => 101,
  );
  $form['#group_children']['alignment_tag_description'] = "group_tags";
  // Alignment View -> The initial load of the form does not have an nid.
  if (isset($form['#node']->nid)) {
    $form['alignment_tag_view'] = array(
      '#markup' => views_embed_view('alignment', 'resource_admin_view', $form['#node']->nid),
      '#prefix' => '<div id="sbac-resource-alignment-tag-view">',
      '#suffix' => '</div>',
      '#weight' => 102,
    );
    $form['#group_children']['alignment_tag_view'] = "group_tags";

    // Alignment Button
    $form['add_alignment_tag_button'] = array(
      '#markup' => l('Add Standard(s)', 'sbac_resource/nojs/add-alignment', array(
        'attributes' => array('class' => 'ctools-use-modal small button ctools-modal-ctools-ccss-style', 'id' => 'sbac-resource-modal-alignment'),
        'query' => array('nid' => $form['#node']->nid))),
      '#weight' => 103,
    );
    $form['#group_children']['add_alignment_tag_button'] = "group_tags";
  }

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

  // Permissions field.
  if ($form['field_view_permissions']['und']['#default_value'] == NULL) {
    $form['field_view_permissions']['und']['#default_value'] = 0;
  }
  $form['field_view_permissions']['und']['#prefix'] = '<div id="sbac-permissions-per-state">';
  $form['field_view_permissions']['und']['#suffix'] = '</div>';

  // View permissions per state.
  $form['field_view_permissions_per_state']['und']['#title'] = '';
  $form['field_view_permissions_per_state']['und']['#prefix'] = '<div id="sbac-permissions-state">';
  $form['field_view_permissions_per_state']['und']['#suffix'] = '</div>';

  // Resource Actions.
  if ($form['field_resource_actions']['und']['#default_value'] == NULL) {
    $form['field_resource_actions']['und']['#default_value'] = array(0, 1);
  }

  // Sharing options
  $form['resource_sharing_options'] = array(
    '#type' => 'item',
    '#markup' => '<h2>'.t('Sharing Options') . '</h2>',
    '#description' => t('By default, all resources have permanent private link that could be shared only with other users of the Digital Library.'),
    '#prefix' => '<div class="form-item-title resource-sharing-options">',
    '#suffix' => '</div>',
    '#weight' => 41,
  );
  $form['#group_children']['resource_sharing_options'] = "group_advanced";

  // Permanent link settings
  unset($form['field_permanent_link_settings']['und']['#options']['_none']);
  if ($form['field_permanent_link_settings']['und']['#default_value'] == NULL) {
    $form['field_permanent_link_settings']['und']['#default_value'] = 0;
  }

  $form['field_temporary_public_link']['und']['#attributes']['class'][] = 'sbac-temporary-public-link';

  // Temporary Link Time
  $class = 'inactive';
  if ($form['field_permanent_link_settings']['und']['#default_value']) {
    $class = 'active';
  }
  $form['field_temporary_public_link_time']['und']['#title'] = t('Set the limit from the time of link generation');
  $form['field_temporary_public_link_time']['#prefix'] = '<div class="sbac-temporary-link-time ' . $class . '">';
  $form['field_temporary_public_link_time']['#suffix'] = '</div>';

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
//  if (isset($form_state['node']->workbench_moderation['current']->state) && $form_state['node']->workbench_moderation['current']->state == 'draft') {
//    return;
//  }

  global $user;
  if ($user->uid == 1 ||
    in_array('DLRB member', $user->roles) ||
    in_array('digital library administrator', $user->roles) ||
    in_array('system administrator', $user->roles)) {

    if (isset($form_state['node']->workbench_moderation['current']->state) && $form_state['node']->workbench_moderation['current']->state == 'published') {
      return;
    }
  }

  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Close',
    '#weight' => 0,
    '#attributes' => array('class' => array('sbac-cancel-blue')),
    '#validate' => array('sbac_resource_validate_form'),
    "#executes_submit_callback" => FALSE,
    '#limit_validation_errors' => array(),
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
          'id' => 'sbac-resource-modal-submit-resource'
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
          'height' => 160,
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
    $form['#node']->workbench_moderation['current']->state == 'published') {

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
          'id' => 'sbac-resource-save-all-changes'
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
      ),
    );
    drupal_add_js($js_settings, 'setting');
  }
}

/**
 * Creates the tags form field.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_resource_form_required_fields(&$form, &$form_state) {
  $form['required_fields_basic'] = array (
    '#markup'   => '* Required Information',
    '#prefix'   => '<p class="sbac-resource-required">',
    '#suffix'   => '</p>',
    '#weight'   => 150,
  );
  $form['#group_children']['required_fields_basic'] = "group_basic";

  $form['required_fields_summary'] = array (
    '#markup'   => '* Required Information',
    '#prefix'   => '<p class="sbac-resource-required">',
    '#suffix'   => '</p>',
    '#weight'   => 150,
  );
  $form['#group_children']['required_fields_summary'] = "group_summary";

  $form['required_fields_materials'] = array (
    '#markup'   => '* Required Information',
    '#prefix'   => '<p class="sbac-resource-required">',
    '#suffix'   => '</p>',
    '#weight'   => 150,
  );
  $form['#group_children']['required_fields_materials'] = "group_materials";

  $form['required_fields_tags'] = array (
    '#markup'   => '* Required Information',
    '#prefix'   => '<p class="sbac-resource-required">',
    '#suffix'   => '</p>',
    '#weight'   => 150,
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

  $form['revision_information']['#access'] = FALSE;
  $form['author']['#access'] = FALSE;
  $form['options']['#access'] = FALSE;
  $form['field_alignment_tags']['#access'] = FALSE;
  $form['field_temp']['#access'] = FALSE;
  $form['field_asset_downloads']['#access'] = FALSE;
  $form['field_total_views']['#access'] = FALSE;
  $form['field_unique_views']['#access'] = FALSE;
  $form['field_alignment_term']['#access'] = FALSE;
  $form['field_document_id']['#access'] = FALSE;
  $form['field_document_information']['#access'] = FALSE;
  $form['field_resource_state']['#access'] = FALSE;
  $form['field_html5']['#access'] = FALSE;
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

  if(isset($form_state['values'])) {
    if (!$form_state['values']['field_alt_body']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_contexts']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_connection_to_ccss']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_connection_to_fap']['und'][0]['value']) {
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
    if (!$form['field_alt_body']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_contexts']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_connection_to_ccss']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_connection_to_fap']['und'][0]['value']['#default_value']) {
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
          $valid = FALSE;
        }
      }
      else{
        $media_items = sbac_media_load_items($form_state['node']->nid);
        if (!$media_items) {
          $valid = FALSE;
        }
      }
    }
    if (!$form_state['values']['field_author']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_publisher']['und'][0]['value']) {
      $valid = FALSE;
    }
    if (isset($form_state['field_license_information']['und'][0]['value']) && $form_state['field_license_information']['und'][0]['value'] == 0) {
      if (!$form_state['values']['field_license']['und'][0]['tid']) {
        $valid = FALSE;
      }
    }
    if (!$form_state['values']['field_pii']['und'][0]['value']) {
      $valid = FALSE;
    }
  }
  else {
    if (isset($form['#node']->nid)) {
      if ($form_state['html5']) {
        $media_items = sbac_media_load_html5_item($form['#node']->nid);
        if (!$media_items) {
          $valid = FALSE;
        }
      }
      else {
        $media_items = sbac_media_load_items($form['#node']->nid);
        if (!$media_items) {
          $valid = FALSE;
        }
      }
    }
    if (!$form['field_author']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (!$form['field_publisher']['und'][0]['value']['#default_value']) {
      $valid = FALSE;
    }
    if (isset($form['field_license_information']['und']['#default_value']) && $form['field_license_information']['und']['#default_value'] == 1) {
      if (!$form['field_license']['und']['#default_value']) {
        $valid = FALSE;
      }
    }
    if (!$form['field_pii']['und']['#default_value']) {
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
function sbac_resource_check_tags($form, $form_state) {
  $valid = TRUE;

  if (isset($form_state['values'])) {
    if (!$form_state['values']['field_subject']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_grades']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_intended_end_user']['und'][0]['tid']) {
      $valid = FALSE;
    }
    if (!$form_state['values']['field_digital_media_type']['und'][0]['tid']) {
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
    if (!$form['field_intended_end_user']['und']['#default_value']) {
      $valid = FALSE;
    }
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
    '#markup' => '<p>'.t($description).'</p>',
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
    '#markup' => '<p>'.t('
    Submitting this resource may make it accessible to Smarter Balanced Digital Library resource reviewers. You cannot edit your resource once it is submitted unless a reviewer returns it to you.').'</p>',
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('id' => array('edit-cancel-overlay'))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit Resource',
    '#attributes' => array('id' => array('edit-submit-overlay'))
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

  $form['hidden_url'] = array(
    '#type' => 'hidden',
    '#value' => arg(0),
  );

  $form['submit_description'] = array(
    '#markup' => '<p>' . t('
    If you continue, you will no longer be able to review this resource. All review information you have entered will be lost.') . '</p>',
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => 'Cancel',
    '#attributes' => array('id' => array('edit-cancel-overlay'))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Delete Draft Resource',
    '#attributes' => array('id' => array('edit-delete-overlay'))
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
