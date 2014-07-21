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

  $form['sbac_setup_profile_image'] = array(
    '#type' => 'file',
    '#name' => 'sbac_setup_profile_image',
    '#description' => t('Your Profile Portrait will be visible to others in the Digital Library.'),
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

  $form['misc_container'] = array(
    '#markup' => '<div class="sbac-user-misc-container">',
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

  $form['misc_container_close'] = array(
    '#markup' => '</div>',
  );

  $form['next_form'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  return $form;
}

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
  );

  return $form;
}

function sbac_user_setup_privacy_form($form, &$form_state) {
  $form = array();

  $form['setup_nav'] = array(
    '#markup' => theme('user_setup_nav', array('current_page' => 'page' . $form_state['data']['page']))
  );

  $form['privacy_desc'] = array(
    '#markup' => t("Select the personal information and expertise you'd like to make visible to other educators in the Digital Library. Anything you choose to make visible will be displayed as shown on the next page. Note that no educators can access your full account and no information will be displayed publicly.")
  );

  $form['visibility_opt_title'] = array(
    '#type' => 'item',
    '#title' => t('Visibility Optional'),
    '#description' => t('Select the personal information you would like visible to other Digital Library users.'),
  );

  $form['visibility_opt'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'field_image' => 'Photo',
      'field_last_name' => 'Last Name',
      'mail' => 'Email Address',
      'field_school_s_' => 'School(s)',
      'field_district_s_' => 'District(s)',
      'field_about' => 'Other Professional Experiences and Accomplishments',
    ),
  );

  $form['visibility_req_title'] = array(
    '#type' => 'item',
    '#title' => t('Visibility Required'),
    '#description' => t('These fields will be shown to all users in the Digital Library.'),
  );

  $form['visibility_req'] = array(
    '#type' => 'checkboxes',
    '#disabled' => TRUE,
    '#options' => array(
      'First Name',
      'Title',
      'State(s)',
      'Grade(s)',
      'Subject(s)',
      'Student Population(s)',
    ),
    '#default_value' => array(
      0,
      1,
      2,
      3,
      4,
      5,
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
    '#value' => t('Preview'),
  );
  return $form;
}

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

function sbac_user_setup_pi_form_validate($form, &$form_state) {
  dpm($_FILE);
  $dir = 'private://setup-profile';
  file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
  $file = file_save_upload(
    'sbac_setup_profile_image',
    array(
      'file_validate_is_image' => array(),
      'file_validate_extensions' => array(),
    ),
    'private://setup-profile'
  );
  if ($file) {
    dpm('what');
  }
  dpm($form_state);
}

function sbac_user_setup_pi_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Next') {
    $_SESSION['user_setup']['user_title'] = $form_state['input']['user_title'];
    $_SESSION['user_setup']['user_retired'] = $form_state['input']['user_retired'];
    drupal_goto('sbac-user/setup/2');
  }
}

function sbac_user_setup_expertise_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Previous') {
    drupal_goto('sbac-user/setup');
  }
}

function sbac_user_setup_expertise_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Next') {
    $_SESSION['user_setup']['subject_options'] = $form_state['input']['subject_options'];
    $_SESSION['user_setup']['grade_options'] = $form_state['input']['grade_options'];
    $_SESSION['user_setup']['student_population_options'] = $form_state['input']['student_population_options'];
    $_SESSION['user_setup']['about_me'] = $form_state['input']['about_me'];
    drupal_goto('sbac-user/setup/3');
  }
}

function sbac_user_setup_privacy_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Previous') {
    drupal_goto('sbac-user/setup/2');
  }
}

function sbac_user_setup_privacy_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Preview') {
    $_SESSION['user_setup']['visibility_opt'] = $form_state['input']['visibility_opt'];
    drupal_goto('sbac-user/setup/4');
  }
}

function sbac_user_setup_preview_form_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Edit Profile') {
    drupal_goto('sbac-user/setup/3');
  }
}

function sbac_user_setup_preview_form_submit($form, &$form_state) {

}

