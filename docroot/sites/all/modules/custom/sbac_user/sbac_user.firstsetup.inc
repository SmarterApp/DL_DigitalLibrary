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
 * @param  array  $vocab_name [description]
 * @return array              [description]
 */
function sbac_user_form_setup_select_taxonomy_options($vocab_name) {
  if ($vocab = taxonomy_vocabulary_machine_name_load($vocab_name)) {
    $terms = taxonomy_get_tree($vocab->vid);
    $options = array();
    foreach($terms AS $idx => $term) {
      $options[$term->tid] = $term->name;
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
  $form = array();

  $form['setup_nav'] = array(
    '#markup' => theme('user_setup_nav', array('current_page' => 'page' . $form_state['data']['page']))
  );

  $form['image_prefix'] = array(
    '#markup' => '<div class="sbac-setup-profile-container">',
  );

  $filepath = variable_get('user_picture_default', '');
  $form['dummy_image'] = array(
    '#prefix' => '<div class="sbac-setup-dummy-img">',
    '#suffix' => '</div>',
    '#markup' => theme('image', array('path' => '' . $filepath)),
  );

  $form['profile_image'] = array(
    '#type' => 'managed_file',
    '#description' => t('Your Profile Portrait will be visible to others in the Digital Library.'),
    '#default_value' => isset($_SESSION['user_setup']['profile_image']) ? $_SESSION['user_setup']['profile_image'] : '',
    '#upload_validators' => array(
      'file_validate_extensions' => array('png jpg jpeg gif'),
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

  $values = array();
  foreach ($options AS $idx => $name) {
    $values[] = array('value' => $idx);
  }

  $form['next_form'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
    '#states' => array(
      'enabled' => array(
        '#edit-user-title' => array(
          $values,
        ),
      ),
    ),
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

  /**
   * Returns an array to conform to Drupal FAPI standard.
   * @param  [type] $options [description]
   * @return [type]          [description]
   */
  function sbac_get_multi_select_dependencies($options) {
    $values = array();
    foreach ($options AS $idx => $name) {
      $values[] = array('value' => array((string) $idx));
    }
    return $values;
  }

  $form['is_complete'] = array(
    '#type' => 'checkbox',
    '#title' => 'completed',
    '#attributes' => array(
      'class' => array(
        'sbac-user-setup-hidden',
        'hidden',
      ),
    ),
    '#states' => array(
      'checked' => array(
        'select[name="subject_options[]"]' => array(
          sbac_get_multi_select_dependencies($subject_options),
        ),
        'select[name="grade_options[]"]' => array(
          sbac_get_multi_select_dependencies($grade_options),
        ),
        'select[name="student_population_options[]"]' => array(
          sbac_get_multi_select_dependencies($student_population_options),
        ),
      ),
    ),
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

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
    '#states' => array(
      'enabled' => array(
        ':input[name="is_complete"]' => array(
          'checked' => TRUE,
        ),
      ),
    ),
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
    '#default_value' => (isset($_SESSION['user_setup']['visibility_opt']) ? array_values($_SESSION['user_setup']['visibility_opt']) : array()),
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
    'Student Population(s)',
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

  $form['next'] = array(
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
 * Implements hook_form_submit().
 * Progresses setup form to next page.
 * [sbac_user_setup_pi_form_submit description]
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_user_setup_pi_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Next') {
    $_SESSION['user_setup']['profile_image'] = $form_state['input']['profile_image']['fid'];
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
    $_SESSION['user_setup']['visibility_opt'] = $form_state['input']['visibility_opt'];
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

    $updates['field_position']['und'][0]['tid'] = $_SESSION['user_setup']['user_title'];
    if ($_SESSION['user_setup']['user_retired']) {
      $updates['field_retired']['und'][0]['value'] = 'I am currently retired';
    }
    $updates['field_subject_s_']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['subject_options']);
    $updates['field_grade_level_s_']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['grade_options']);
    $updates['field_special_populations']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['student_population_options']);
    $updates['field_introduction']['und'][0]['value'] = $_SESSION['user_setup']['about_me'];
    $updates['field_privacy']['und'] = sbac_user_setup_set_options($_SESSION['user_setup']['visibility_opt']);

    user_save($account, $updates);
    $_SESSION['welcome-update'] = TRUE;
    unset($_SESSION['user_setup']);
    drupal_goto('');
  }
}
