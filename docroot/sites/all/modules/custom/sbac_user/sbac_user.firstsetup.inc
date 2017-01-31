<?php

/**
 * Callback for SBAC User's first setup.
 * @return [type] [description]
 */
function sbac_user_setup_callback($page = '1') {
  global $user;
  $account = user_load($user->uid);
  $form_state = array(
    'data' => array(
      'page' => $page,
    ),
  );

  switch ($page) {
    case '1':
      return drupal_build_form('sbac_user_setup_pi_form', $form_state);
      break;
    case '2':
      return drupal_build_form('sbac_user_setup_expertise_form', $form_state);
      break;
    case '3':
      return drupal_build_form('sbac_user_setup_privacy_form', $form_state);
      break;
    case '4':
      return drupal_build_form('sbac_user_setup_preview_form', $form_state);
      break;
    default:
      return drupal_build_form('sbac_user_setup_pi_form', $form_state);
      break;
  }
}

/**
 * Returns an associated array of tid => name.
 * @param  string  $vocab_name [description]
 * @return array              [description]
 */
function sbac_user_form_setup_select_taxonomy_options($vocab_name) {
  if ($vocab = taxonomy_vocabulary_machine_name_load($vocab_name)) {
    $terms = taxonomy_get_tree($vocab->vid);
    $options = array();
    foreach ($terms as $term) {
      $children = taxonomy_get_children($term->tid);
      if (empty($children)) {
        $options[$term->tid] = sbac_resource_taxonomy_term_concat_parents($term->tid, $term->name);
      }
    }
    return $options;
  }
}

/**
 * Implements hook_form().
 * Sets up the first page of the user setup form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_pi_form($form, &$form_state) {
  global $user;
  $account = user_load($user->uid);
  drupal_add_js(drupal_get_path('module', 'sbac_user') . '/js/sbac_user.firstsetup_p1.js');

  $form = array();

  $form['setup_nav'] = array(
    '#markup' => theme('user_setup_nav', array('current_page' => 'page' . $form_state['data']['page']))
  );

  $form['image_prefix'] = array(
    '#markup' => '<div class="sbac-setup-profile-container">',
  );

  $file_path = variable_get('user_picture_default', '');
  $default = '';
  if (isset($_SESSION['user_setup']['temp_profile_image'])) {
    $profile_file = file_load($_SESSION['user_setup']['temp_profile_image']);
    $file_path = file_create_url($profile_file->uri);
    $default = $_SESSION['user_setup']['temp_profile_image'];
  }

  $form['field_file_container']['#tree'] = TRUE;
  $form['field_file_container'] = array(
    '#prefix'=>'<div id="sbac-user-profile-file-container">',
    '#suffix'=>'</div>',
  );

  $form['field_file_container']['dummy_image'] = array(
    '#prefix' => '<div class="sbac-setup-dummy-img">',
    '#suffix' => '</div>',
    '#markup' => theme('image', array('path' => '' . $file_path)),
  );

  $form['field_file_container']['field_file_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload2'),
    '#title_display' => 'invisible',
    '#description' => t('Your Profile Portrait will be visible to others in the Digital Library.'),
    '#size' => 22,
    '#upload_location' => 'public://',
  );

  $form['field_file_container']['field_file_upload_button'] = array(
    '#type' => 'submit',
    '#value' => 'Upload File',
    '#description' => t('Your Profile Portrait will be visible to others in the Digital Library.'),
    '#ajax'=> array(
      'callback'=>'sbac_user_widget_form_element_upload',
      'wrapper'=> 'sbac-user-profile-file-container',
      'method'=> 'replace',
      'effect'=> 'fade',
    ),
  );

  $form['image_suffix'] = array(
    '#markup' => '</div>',
  );

  $form['name_container'] = array(
    '#markup' => '<div class="sbac-user-name-container">',
  );

  $form['name_desc'] = array(
    '#type' => 'item',
    '#title' => t('Name'),
    '#description' => t('As provided by your state.'),
  );

  $first_name = field_get_items('user', $account, 'field_first_name');
  $first_name = array_pop($first_name);
  $_SESSION['user_setup']['first_name'] = $first_name['value'];

  $form['first_name'] = array(
    '#type' => 'textfield',
    '#default_value' => $first_name['value'],
    '#disabled' => TRUE,
  );

  $last_name = field_get_items('user', $account, 'field_last_name');
  $last_name = array_pop($last_name);
  $_SESSION['user_setup']['last_name'] = $last_name['value'];

  $form['last_name'] = array(
    '#type' => 'textfield',
    '#default_value' => $last_name['value'],
    '#disabled' => TRUE,
  );

  $form['name_container_close'] = array(
    '#markup' => '</div>',
  );

  $form['email_container'] = array(
    '#markup' => '<div class="sbac-user-email-container">',
  );

  $form['user_email_desc'] = array(
    '#type' => 'item',
    '#title' => t('Email'),
    '#description' => t('As provided by your state.'),
  );

  $_SESSION['user_setup']['mail'] = $user->mail;

  $form['user_email'] = array(
    '#type' => 'textfield',
    '#default_value' => $user->mail,
    '#disabled' => TRUE,
  );

  $form['email_container_close'] = array(
    '#markup' => '</div>',
  );

  $form['title_container'] = array(
    '#markup' => '<div class="sbac-user-title-container">',
  );

  $form['user_title_desc'] = array(
    '#type' => 'item',
    '#title' => t('Title'),
    '#description' => t('Select your current or former title.'),
    '#required' => TRUE,
  );

  $options = sbac_user_form_setup_select_taxonomy_options('title');

  $form['user_title'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#required' => TRUE,
    '#empty_option' => t('Select'),
    '#default_value' => isset($_SESSION['user_setup']['user_title']) ? $_SESSION['user_setup']['user_title'] : '',
  );

  $form['user_retired'] = array(
    '#type' => 'checkbox',
    '#title' => t('I am currently retired'),
    '#default_value' => isset($_SESSION['user_setup']['user_retired']) ? $_SESSION['user_setup']['user_retired'] : '',
  );

  $form['title_container_close'] = array(
    '#markup' => '</div>',
  );

  // $form['hover_div_pi'] = array(
  //   '#markup' => '<div id="sbac-setup-hover-pi" data-dropdown="pi-form-drop"></div>',
  // );

  $form['next_form'] = array(
    // '#prefix' => '<div id="sbac-setup-hover-pi-button" data-dropdown="pi-form-drop">',
    // '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  $form['dropdown'] = array(
    '#markup' => '<div id="pi-form-drop" data-dropdown-content class="f-dropdown content">
                    <p>Please complete the <span class="sbac-user-setup-bold">required fields</span> (<span class="sbac-user-setup-req-marker">*</span>).</p>
                  </div>',
  );

  return $form;
}

/**
 * Implements hook_form().
 * Sets up page 2 of the profile setup form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_expertise_form($form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'sbac_user') . '/js/sbac_user.firstsetup_p2.js');

  $form = array();

  $form['setup_nav'] = array(
    '#markup' => theme('user_setup_nav', array('current_page' => 'page' . $form_state['data']['page']))
  );

  $form['subject_title'] = array(
    '#type' => 'item',
    '#title' => t('Subject(s)'),
    '#description' => t('Indicate the subject area(s) in which you have expertise.'),
    '#required' => TRUE,
  );

  $subject_options = sbac_user_form_setup_select_taxonomy_options('subject');

  $form['subject_options'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#attributes' => array(
      'class' => array(
        'chosen-widget',
      ),
    ),
    '#required' => TRUE,
    '#options' => $subject_options,
    '#default_value' => isset($_SESSION['user_setup']['subject_options']) ? array_values($_SESSION['user_setup']['subject_options']) : '',
  );

  $form['grade_title'] = array(
    '#type' => 'item',
    '#title' => t('Grade(s)'),
    '#description' => t('Indicate the grade(s) in which you have expertise.'),
    '#required' => TRUE,
  );

  $grade_options = sbac_user_form_setup_select_taxonomy_options('grades');

  $form['grade_options'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#attributes' => array(
      'class' => array(
        'chosen-widget',
      ),
    ),
    '#required' => TRUE,
    '#options' => $grade_options,
    '#default_value' => isset($_SESSION['user_setup']['grade_options']) ? array_values($_SESSION['user_setup']['grade_options']) : '',
  );

  $form['student_population_title'] = array(
    '#type' => 'item',
    '#title' => t('Student Population(s)'),
    '#description' => t('Indicate the student population(s) in which you have expertise.'),
    '#required' => TRUE,
  );

  $student_population_options = sbac_user_form_setup_select_taxonomy_options('intended_student_populations');

  $form['student_population_options'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#attributes' => array(
      'class' => array(
        'chosen-widget',
      ),
    ),
    '#required' => TRUE,
    '#options' => $student_population_options,
    '#default_value' => isset($_SESSION['user_setup']['student_population_options']) ? array_values($_SESSION['user_setup']['student_population_options']) : '',
  );

  $form['about_me_desc'] = array(
    '#type' => 'item',
    '#title' => t('Other Professional Experiences and Accomplishments'),
    '#description' => t('Share other professional experiences, certifications, awards, and accomplishments.'),
  );

  $form['about_me'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($_SESSION['user_setup']['about_me']) ? $_SESSION['user_setup']['about_me'] : '',
    '#maxlength' => 300,
    '#maxlength_js' => TRUE,
    '#attributes' => array('maxlength_js_label' => array('Character count: @remaining')),
  );

  $form['previous'] = array(
    '#type' => 'submit',
    '#value' => t('Previous'),
    '#attributes' => array(
      'class' => array(
        'gray',
      ),
    ),
  );

  // $form['hover_div_pi'] = array(
  //   '#markup' => '<div id="sbac-setup-hover-expertise" data-dropdown="expertise-form-drop"></div>',
  // );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  $form['dropdown'] = array(
    '#markup' => '<div id="expertise-form-drop" data-dropdown-content class="f-dropdown content">
                    <p>Please complete the <span class="sbac-user-setup-bold">required fields</span> (<span class="sbac-user-setup-req-marker">*</span>).</p>
                  </div>',
  );

  return $form;
}

/**
 * Implements hook_form().
 * Sets up page 3 of profile setup.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_privacy_form($form, &$form_state) {
  $form = array();

  $form['setup_nav'] = array(
    '#markup' => theme('user_setup_nav', array('current_page' => 'page' . $form_state['data']['page']))
  );

  $form['privacy_desc'] = array(
    '#prefix' => '<div class="sbac-setup-pg3-txt">',
    '#suffix' => '</div>',
    '#markup' => t("Select the personal information and expertise you'd like to make visible to other educators in the Digital Library. Anything you choose to make visible will be displayed as shown on the next page. Note that no educators can access your full account and no information will be displayed publicly.")
  );

  $form['opt_container'] = array(
    '#markup' => '<div class="sbac-setup-pg3-container">',
  );

  $form['visibility_opt_title'] = array(
    '#type' => 'item',
    '#title' => t('Visibility Optional'),
    '#description' => t('Select the personal information you would like visible to other Digital Library users.'),
  );

  $visibility_dv = array();
  if (isset($_SESSION['user_setup']['visibility_opt'])) {
    foreach ($_SESSION['user_setup']['visibility_opt'] AS $idx => $val) {
      $visibility_dv[] = $val['value'];
    }
  }

  $form['visibility_opt'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'picture' => 'Photo',
      'field_last_name' => 'Last Name',
      'mail' => 'Email Address',
      'field_school_name' => 'School(s)',
      'field_district_name' => 'District(s)',
      'field_introduction' => 'Other Professional Experiences and Accomplishments',
    ),
    '#default_value' => $visibility_dv,
  );

  $form['opt_container_close'] = array(
    '#markup' => '</div>',
  );

  $form['req_container'] = array(
    '#markup' => '<div class="sbac-setup-pg3-container last">',
  );

  $form['visibility_req_title'] = array(
    '#type' => 'item',
    '#title' => t('Visibility Required'),
    '#description' => t('These fields will be shown to all users in the Digital Library.'),
  );

  $visibility_options = array(
    'First Name',
    'Title',
    'State(s)',
    'Grade(s)',
    'Subject(s)',
    'Student Populations',
  );

  $form['visibility_req'] = array(
    '#type' => 'checkboxes',
    '#disabled' => TRUE,
    '#options' => $visibility_options,
    '#default_value' => array_keys($visibility_options),
  );

  $form['req_container_close'] = array(
    '#markup' => '</div>',
  );

  $form['previous'] = array(
    '#type' => 'submit',
    '#value' => t('Previous'),
    '#attributes' => array(
      'class' => array(
        'gray',
      ),
    ),
  );

  $form['next3'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
  );
  return $form;
}

/**
 * Implements hook_form().
 * Sets up the profile setup preview.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_preview_form($form, &$form_state) {
  $form = array();

  $form['preview_desc'] = array(
    '#markup' => 'This is a preview of your profile. Use the edit button to make changes.',
  );

  $form['profile_render'] = array(
    '#prefix' => '<div class="sbac-user-setup-preview">',
    '#suffix' => '</div>',
    '#markup' => theme('user_setup_preview', array()),
  );

  $form['edit_profile'] = array(
    '#type' => 'submit',
    '#value' => t('Edit Profile'),
    '#attributes' => array(
      'class' => array(
        'gray',
      ),
    ),
  );

  $form['done'] = array(
    '#type' => 'submit',
    '#value' => t('Done'),
  );

  return $form;
}

/**
 * Handle the upload button and the temporary picture location.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_user_widget_form_element_upload(&$form, &$form_state) {
  $errors = form_get_errors();
  if ($errors && !isset($errors['user_title'])) {
    // if the user has an error on user_title, don't worry about it
    // when the user clicks upload picture but, if that is not
    // the error, then return the container
    form_set_error($errors, t('There was a problem with the upload'));
    return $form['field_file_container'];
  }

  // save the file
  sbac_user_widget_save_media($form, $form_state);

  // Update the view
  if (isset($_SESSION['user_setup']['temp_profile_image'])) {
    $file = file_load($_SESSION['user_setup']['temp_profile_image']);
    if ($file) {
      $file_path = file_create_url($file->uri);
      $form['field_file_container']['dummy_image'] = array(
        '#prefix' => '<div class="sbac-setup-dummy-img">',
        '#suffix' => '</div>',
        '#markup' => theme('image', array('path' => '' . $file_path)),
      );
    }
  }

  return $form['field_file_container'];
}

/**
 * Save the media item.
 *
 * @param $form
 * @param $form_state
 */
function sbac_user_widget_save_media(&$form, &$form_state) {
  global $user;
  $allowed_file_types = array('png jpg jpeg');
  // First param is file limit. second param is limit for total size for all uploads for user.
  $allowed_size = array(SBAC_MEDIA_100MB, 0);
  $directory = "public://temp_profile_pictures/" . $user->uid;
  $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
  if ($writable) {
    $validators = array(
      'file_validate_extensions' => $allowed_file_types,
      'file_validate_size' => $allowed_size,
    );
    $file = file_save_upload('field_file_upload', $validators, $directory, FILE_EXISTS_REPLACE);
    if ($file) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      $_SESSION['user_setup']['temp_profile_image'] = $file->fid;
    }
  }
}

/**
 * Implements hook_form_submit().
 * Progresses setup form to next page.
 * [sbac_user_setup_pi_form_submit description]
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_pi_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Next') {
    if (isset($form_state['input']['profile_image']['fid'])) {
      $_SESSION['user_setup']['profile_image'] = $form_state['input']['profile_image']['fid'];
    }
    $_SESSION['user_setup']['user_title'] = $form_state['input']['user_title'];
    $_SESSION['user_setup']['user_retired'] = $form_state['input']['user_retired'];
    drupal_goto('sbac-user/setup/2');
  }
}

/**
 * Implements hook_form_validate().
 * Bypasses required fields to return to previous page.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_expertise_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Previous') {
    drupal_goto('sbac-user/setup');
  }
}

/**
 * Implements hook_form_submit().
 * Progresses setup form to next page.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_expertise_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Next') {
    $_SESSION['user_setup']['subject_options'] = $form_state['input']['subject_options'];
    $_SESSION['user_setup']['grade_options'] = $form_state['input']['grade_options'];
    $_SESSION['user_setup']['student_population_options'] = $form_state['input']['student_population_options'];
    $_SESSION['user_setup']['about_me'] = $form_state['input']['about_me'];
    drupal_goto('sbac-user/setup/3');
  }
}

/**
 * Implements hook_form_validate().
 * Bypasses required fields to return to previous page.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_privacy_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Previous') {
    drupal_goto('sbac-user/setup/2');
  }
}

/**
 * Implements hook_form_submit().
 * Progresses setup form to next page.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_privacy_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Preview') {
    $_SESSION['user_setup']['visibility_opt'] = array();
    foreach ($form_state['input']['visibility_opt'] AS $idx => $value) {
      if ($value) {
        $_SESSION['user_setup']['visibility_opt'][] = array('value' => $idx);
      }
    }
    $visibility_options = array(
      'field_first_name' => 'First Name',
      'field_position' => 'Title',
      'field-state' => 'State(s)',
      'field-grade-level-s-' => 'Grade(s)',
      'field-subject-s-' => 'Subject(s)',
      'special-populations' => 'Student Populations',
    );
    foreach ($visibility_options AS $idx => $name) {
      $_SESSION['user_setup']['visibility_opt'][] = array('value' => $idx);
    }
    drupal_goto('sbac-user/setup/4');
  }
}

/**
 * Implements hook_form_submit().
 * Submit handler for the profile setup preview form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_preview_form_submit($form, &$form_state) {
  /**
   * Sets up the tid values array.
   * @param  array  $options [description]
   * @return array           [description]
   */
  function sbac_user_setup_set_options($options) {
    $values = array();
    foreach ($options AS $idx => $tid) {
      $values[] = array('tid' => $tid);
    }
    return $values;
  }

  if ($form_state['clicked_button']['#value'] == 'Edit Profile') {
    drupal_goto('sbac-user/setup/3');
  }
  else if ($form_state['clicked_button']['#value'] == 'Done') {
    global $user;
    $account = user_load($user->uid);

    $updates = array();
    foreach ($_SESSION['user_setup']['visibility_opt'] AS $name => $value) {
      $updates['field_privacy']['und'][] = array('value' => $value);
    }

    $updates['field_position']['und'][0]['tid'] = $_SESSION['user_setup']['user_title'];
    if ($_SESSION['user_setup']['user_retired']) {
      $updates['field_retired']['und'][0]['value'] = 'I am currently retired';
    }
    $updates['field_subject_s_']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['subject_options']);
    $updates['field_grade_level_s_']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['grade_options']);
    $updates['field_special_populations']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['student_population_options']);
    $updates['field_introduction']['und'][0]['value'] = $_SESSION['user_setup']['about_me'];

    // Update user information.
    sbac_user_update_data($account);
    $account = user_save($account, $updates);
    if ($account !== FALSE) {
      if (isset($_SESSION['user_setup']['temp_profile_image'])) {
        sbac_user_save_temp_image($account);
      }
      $_SESSION['welcome-update'] = TRUE;
      unset($_SESSION['user_setup']);
      sbac_user_redirect_on_login();
    }
  }
}

function sbac_user_save_temp_image($account) {
  $file = file_load($_SESSION['user_setup']['temp_profile_image']);
  $hashdir = sbac_user_util_compute_hash_dir($account->uid);
  $new_uri = sbac_user_util_compute_new_path($file->uri, $hashdir);
  $new_uri = str_replace('temp_profile_pictures', 'pictures', $new_uri);
  $old_absolute_path = drupal_realpath($file->uri);
  $new_absolute_path = sbac_user_util_compute_new_path($old_absolute_path, $hashdir);
  $new_absolute_path = str_replace('temp_profile_pictures', 'pictures', $new_absolute_path);
  $res = sbac_user_util_move_file($old_absolute_path, $new_absolute_path);
  if (!$res) {
    drupal_set_message(t('Error moving your profile image.'));
  }
  $file->uri = $new_uri;
  file_save($file);
  // Update account record
  db_query("UPDATE {users} SET picture = :fid WHERE uid = :uid", array(':fid' => $file->fid, ':uid' => $account->uid));
  // remove temp_user_profile image
  file_unmanaged_delete_recursive($old_absolute_path);
}

/**
 * Enables next button if options have values.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_is_complete_after_build($form, &$form_state) {
  if (!empty($form_state['values']['subject_options']) && !empty($form_state['values']['grade_options']) && !empty($form_state['values']['student_population_options'])) {
    $form['#checked'] = TRUE;
  }
  return $form;
}
