<?php
/**
 * @file 
 * Admin include file.
 */

/**
 * Main settings form.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function taskit_admin_settings_form($form, &$form_state) {
  $form['taskit_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Email alerts'),
    '#default_value' => variable_get('taskit_email', 0),
    '#description' => t('Enabling this will allow users to subscribe to daily email alerts for new notifications.'),
  );

  $form['taskit_breakdown'] = array(
    '#title' => t('Breakdown'),
    '#description' => t('How should taskit items be presented?'),
    '#type' => 'radios',
    '#options' => array(
      'role' => t('Separated (different tab for each role)'),
      'group' => t('All together on single page'),
    ),
    '#default_value' => variable_get('taskit_breakdown', 'group'),
  );

  $form['taskit_grouping'] = array(
    '#title' => t('Grouping'),
    '#description' => t('How should taskit items be grouped on each page?'),
    '#type' => 'radios',
    '#options' => array(
      'date' => t('By date'),
      'none' => t('No grouping (single list)'),
    ),
    '#default_value' => variable_get('taskit_grouping', 'none'),
  );

  $form['taskit_visibility'] = array(
    '#title' => t('Task visibility'),
    '#description' => t('Should a task applying to multiple users have global or per-user visibility?'),
    '#type' => 'radios',
    '#options' => array(
      'global' => t('Global'),
      'user' => t('Per user'),
    ),
    '#default_value' => variable_get('taskit_visibility', 'global'),
  );

  return system_settings_form($form);
}

/**
 * Taskit <--> Role settings
 *
 * @return
 *   array A structured array for use with Forms API.
 */
function taskit_admin_type_role_settings_form($form, &$form_state) {
  $options = taskit_role_priority();

  foreach (taskit_types() as $type) {
    $form[$type['name']] = array(
      '#type' => 'fieldset',
      '#title' => ucfirst(str_replace('_', ' ', $type['name'])),
      '#description' => $type['description'],
    );

    $default = array();

    $result = db_select('taskit_role', 'tr')
                ->fields('tr', array('role_id'))
                ->condition('type', $type['name'])
                ->execute();

    foreach ($result as $record) {
      $default[] = $record->role_id;
    }

    $form[$type['name']][$type['name']] = array(
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => $default,
    );
  }

  if ($form) {
    $form['title'] = array(
      '#markup' => t('Check each role that applies to the corresponding Taskit type.'),
      '#weight' => -100,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Save Configuration',
    ); 
  }
  else {
    $form['error'] = array(
      '#markup' => t('There are no Taskit types configured.'),
    );
  }

  return $form;
}

/**
 * Submit handler for taskit_admin_type_role_settings_form();
 */
function taskit_admin_type_role_settings_form_submit($form, &$form_state) {
  // delete all records in the table and rebuild
  db_delete('taskit_role')->execute();

  $types = taskit_types();
  $inserts = array();

  // iterate through taskit types and match form values, removing zeros and build insert
  foreach($types as $type) {
    $roles = array_filter($form_state['values'][$type['name']]);

    foreach ($roles as $role) {
      $inserts[] = array(
        'type' => $type['name'],
        'role_id' => $role,
      );
    }
  }

  // lets rebuild taskit_role table with our type/role combinations from form
  if ($inserts) {
    $query = db_insert('taskit_role')->fields(array('type', 'role_id'));
    foreach ($inserts as $insert) {
      $query->values($insert);
    }
    $query->execute();

    drupal_set_message('Taskit type roles were successfully rebuilt.');
  }
  else {
    drupal_set_message('All Taskit type roles were deleted and no new roles were added to types.');
  }
}