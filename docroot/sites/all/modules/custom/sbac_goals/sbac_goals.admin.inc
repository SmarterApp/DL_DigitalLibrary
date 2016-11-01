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
    '#description' => t("Enter a date in this format, Year-Month-Day i.e. '2016-06-17'"),
    '#required' => TRUE,
  );
  $form['goals_end_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Goal End Date'),
    '#default_value' => variable_get('goals_end_date', ''),
    '#maxlength' => 128,
    '#description' => t("Enter a date in this format, Year-Month-Day i.e. '2016-06-17'"),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}