<?php

/**
 * Implementation of hook_theme().
 *
 * @return array
 */
function sbac_user_theme__theme() {
  $items = array();

  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('module', 'sbac_user') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
      'template_preprocess',
      'sbac_user_theme__preprocess_user_login'
    ),
  );
  $items['user_pass'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('module', 'sbac_user') . '/templates',
    'template' => 'user-pass',
    'preprocess functions' => array(
      'template_preprocess',
    ),
  );
  $items['sbac_user_change_password_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('module', 'sbac_user') . '/templates',
    'template' => 'change-password',
    'preprocess functions' => array(
      'template_preprocess',
    ),
  );
  $items['user_pass_confirmation'] = array(
    'path' => drupal_get_path('module', 'sbac_user') . '/templates',
    'template' => 'user-pass-confirmation',
  );

  $items['user_profile']['preprocess functions'][] = 'sbac_user_theme__preprocess_user_profile';

  $items['user_setup_nav'] = array(
    'path' => drupal_get_path('module', 'sbac_user') . '/templates',
    'template' => 'user-setup-nav',
    'variables' => array(
      'page1' => NULL,
      'page2' => NULL,
      'page3' => NULL,
    ),
  );

  $items['user_setup_preview'] = array(
    'path' => drupal_get_path('module', 'sbac_user') . '/templates',
    'template' => 'user-setup-preview',
  );

  return $items;
}

/*
 * Preprocess function for user view page.
 * Just tweaking bunched up array values.
 */
function sbac_user_theme__preprocess_user_profile(&$vars) {

  // add spacing between array values for these fields
  $tweakme = array('field_subject_s_', 'field_grade_level_s_');
  for ($z=0; $z<count($tweakme); $z++) {
    $field = $tweakme[$z];
    if (isset($vars['elements'][$field]) &&
      is_array($vars['elements'][$field])) {
      for ($i=0; $i<count($vars['elements'][$field]); $i++) {
        if (isset($vars['elements'][$field][$i]['#markup'])) {
          $vars['elements'][$field][$i]['#markup'] .= "&nbsp;";
        }
      }
    }
  }

}

/**
 * Preprocess function for user login
 *
 * @param $vars
 */
function sbac_user_theme__preprocess_user_login(&$vars) {
  $vars['left_top_big'] = t('Smarter Balanced Assessment Consortium');
  $vars['left_top_small'] = t('<div class="login-text">The Smarter Balanced Assessment Consortium is a state-led consortium working to develop next-generation assessments that accurately measure student progress toward college- and career-readiness.</div>').l(t('Click here to learn more'),"http://www.smarterbalanced.org/", array('attributes' => array('target' => '_blank', 'class' => 'login-text')));

  $vars['left_middle_big'] = t('The Smarter Balanced Digital Library');
  $vars['left_middle_small'] = t('<div class="login-text">The Digital Library is an online, user friendly, searchable library for educators that contains only high quality vetted resources. It is interactive and allows educators from member states to use and rate resources and to collaborate.</div>');

  // $vars['left_bottom_big'] = t('Help');
  // $vars['left_bottom_small'] = t('Find answers to common topics');

  $vars['form']['actions']['submit']['#value'] = t('Log into the Digital Library');
}

function sbac_user_preprocess_user_setup_nav(&$vars) {
  $page = $vars['current_page'];
  switch ($page) {
    case 'page1':
      $vars['page1']['nav'] = 'sbac-user-setup-nav-current-cont';
      $vars['page1']['text'] = 'sbac-user-setup-nav-current-text';
      break;
    case 'page2':
      $vars['page2']['nav'] = 'sbac-user-setup-nav-current-cont';
      $vars['page2']['text'] = 'sbac-user-setup-nav-current-text';
      break;
    case 'page3':
      $vars['page3']['nav'] = 'sbac-user-setup-nav-current-cont';
      $vars['page3']['text'] = 'sbac-user-setup-nav-current-text';
      break;
  }
}

function sbac_user_preprocess_user_setup_preview(&$vars) {

  function sbac_user_make_list($options) {
    $list = '';
    foreach ($options AS $idx => $tid) {
      $term = taxonomy_term_load($tid);
      $list .= '<li>' . $term->name . '</li>';
    }
    return $list;
  }

  $grades = '';
  $subjects = '';
  $populations = '';

  $title_term = taxonomy_term_load($_SESSION['user_setup']['user_title']);
  $vars['first_name'] = $_SESSION['user_setup']['first_name'];
  $vars['title'] = $title_term->name . ($_SESSION['user_setup']['user_retired'] ? ' (Retired)' : '');
  $vars['grades'] = '<ul>' . sbac_user_make_list($_SESSION['user_setup']['grade_options']) . '</ul>';
  $vars['subjects'] = '<ul>' . sbac_user_make_list($_SESSION['user_setup']['subject_options']) . '</ul>';
  $vars['population'] = '<ul>' . sbac_user_make_list($_SESSION['user_setup']['student_population_options']) . '</ul>';

  // $vars['profile_picture'] = '';
  if (isset($_SESSION['user_setup']['visibility_opt']['field_last_name'])) {
    $vars['last_name'] = $_SESSION['user_setup']['last_name'];
  }
  else {
   $vars['last_name'] = '';
  }
  if (isset($_SESSION['user_setup']['visibility_opt']['mail'])) {
    $vars['email'] = l($_SESSION['user_setup']['mail'], 'mailto:' . $_SESSION['user_setup']['mail'], array('absolute' => TRUE));
  }
  else {$vars['email'] = '';

  }
  if (isset($_SESSION['user_setup']['about_me'])) {
    $vars['about'] = $_SESSION['user_setup']['about_me'];
  }
  else {
   $vars['about'] = '';
  }
}
