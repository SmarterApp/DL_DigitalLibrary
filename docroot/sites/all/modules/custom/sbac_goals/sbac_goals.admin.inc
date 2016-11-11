<?php
/* 
 * @file.
 * Includes forms for all admin settings pages.
 */

/**
 * Page callback: Google CDN variables.
 *
 * @see sbac_central_menu()
 */

function sbac_goals_admin() {
  $form = array();

  $form['goals_start_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Goal Start Date'),
    '#default_value' => variable_get('goals_start_date', ''),
    '#maxlength' => 128,
    '#description' => t("Enter a date in this format, Year-Month-Day (e.g. - '2016-06-17')"),
    '#required' => TRUE,
  );
  $form['goals_end_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Goal End Date'),
    '#default_value' => variable_get('goals_end_date', ''),
    '#maxlength' => 128,
    '#description' => t("Enter a date in this format, Year-Month-Day (e.g. - '2016-06-17')"),
    '#required' => TRUE,
  );
  $form['goals_previous_start_date'] = array(
    '#type' => 'hidden',
    '#value' => variable_get('goals_previous_start_date', FALSE),
  );
  $form['goals_current_start_date'] = array(
    '#type' => 'hidden',
    '#value' => variable_get('goals_start_date', FALSE),
  );

  return system_settings_form($form);
}

function sbac_goals_admin_validate($form, &$form_state) {
  if (!preg_match("/^\d{4}-\d{2}-\d{2}$/", $form_state['values']['goals_start_date'])) {
    form_set_error('goals_start_date', t("Date has to be in the format Year-Month-Day (e.g. - '2016-06-17')"));
  }
  if (!preg_match("/^\d{4}-\d{2}-\d{2}$/", $form_state['values']['goals_end_date'])) {
    form_set_error('goals_end_date', t("Date has to be in the format Year-Month-Day (e.g. - '2016-06-17')"));
  }
  if ($form_state['values']['goals_current_start_date'] && $form_state['values']['goals_start_date'] != $form_state['values']['goals_current_start_date']) {
    $form_state['values']['goals_previous_start_date'] = $form_state['values']['goals_current_start_date'];
  }
  unset($form_state['values']['goals_current_start_date']);
}