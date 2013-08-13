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
  $items['change_password'] = array(
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
  $vars['left_top_small'] = l(t('Learn More'),"http://www.smarterbalanced.org/");

  $vars['left_middle_big'] = t('The Smarter Balanced Digital Library');
  $vars['left_middle_small'] = t('Resources you need in one place');

  $vars['left_bottom_big'] = t('Help');
  $vars['left_bottom_small'] = t('Find answers to common topics');

  $vars['form']['actions']['submit']['#value'] = t('Log into the Digital Library');
}
