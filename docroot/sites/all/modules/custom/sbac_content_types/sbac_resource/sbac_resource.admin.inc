<?php

/**
 * @file
 * Code for the SBAC resource feature.
 */

/**
 * Implements hook_FORM_ID_alter().
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function sbac_resource_form_messages() {
  $form['#attached']['css'] = array(
    drupal_get_path('module','sbac_resource').'/css/sbac_resource.css',
  );

  $form['sbac_resource_general_guide'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('General Submission Guidelines'),
    '#default_value' => variable_get('sbac_resource_general_guide', NULL),
    '#description' => t('These guidelines will be displayed on the General tab of the Resource creation screen.'),
    '#format' => 'full_html',
  );

  $form['sbac_resource_materials_guide'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Materials Submission Guidelines'),
    '#default_value' => variable_get('sbac_resource_materials_guide', NULL),
    '#description' => t('These guidelines will be displayed on the Materials tab of the Resource creation screen.'),
    '#format' => 'full_html',
  );

  $form['sbac_resource_summary_guide'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Summary Submission Guidelines'),
    '#default_value' => variable_get('sbac_resource_summary_guide', NULL),
    '#description' => t('These guidelines will be displayed on the Submission tab of the Resource creation screen.'),
    '#format' => 'full_html',
  );

  $form['sbac_resource_tags_guide'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Tags Submission Guidelines'),
    '#default_value' => variable_get('sbac_resource_tags_guide', NULL),
    '#description' => t('These guidelines will be displayed on the Tags tab of the Resource creation screen.'),
    '#format' => 'full_html',
  );

  $form['sbac_resource_advanced_guide'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Advanced Submission Guidelines'),
    '#default_value' => variable_get('sbac_resource_advanced_guide', NULL),
    '#description' => t('These guidelines will be displayed on the Advanced tab of the Resource creation screen.'),
    '#format' => 'full_html',
  );

  $form['sbac_resource_flag_guide'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Flag Submission Guidelines'),
    '#default_value' => variable_get('sbac_resource_flag_guide', NULL),
    '#description' => t('These guidelines will be displayed on the Flag tab of the Resource creation screen.'),
    '#format' => 'full_html',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}


/**
 * Implements hook_FORM_ID_alter().
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function sbac_resource_form_messages_submit(&$form, &$form_state) {
  variable_set('sbac_resource_general_guide', $form_state['values']['sbac_resource_general_guide']['value']);
  variable_set('sbac_resource_materials_guide', $form_state['values']['sbac_resource_materials_guide']['value']);
  variable_set('sbac_resource_summary_guide', $form_state['values']['sbac_resource_summary_guide']['value']);
  variable_set('sbac_resource_tags_guide', $form_state['values']['sbac_resource_tags_guide']['value']);
  variable_set('sbac_resource_advanced_guide', $form_state['values']['sbac_resource_advanced_guide']['value']);
  variable_set('sbac_resource_flag_guide', $form_state['values']['sbac_resource_flag_guide']['value']);

  drupal_set_message(t('The help text has been updated.'));
}
