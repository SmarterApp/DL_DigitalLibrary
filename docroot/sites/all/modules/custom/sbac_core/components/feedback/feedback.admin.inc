<?php

/*----------------------------------------------------------------------------
      CALLBACKS
----------------------------------------------------------------------------*/

/**
 * Callback for /admin/sbac/feedback/gate_keeper
 */
function feedback_gate_keeper_admin_form($form, &$form_state) {
  // form into
    $form['#prefix'] = t('This form provides configuration options for
      elements found in the "Gate Keeper" tab on Resource pages.');

    $form['gate_keeper'] = array(
      '#markup' => '<h2>' . t('Gate Keeper') . '</h2>',
    );

  // gate keeper introduction text
    $gk_intro_content = variable_get('resource_gate_keeper_intro', input_default_full_html());
    $form['resource_gate_keeper_intro'] = array(
      '#title' => t('Introduction'),
      '#type' => 'text_format',
      '#default_value' => $gk_intro_content['value'],
      '#format' => $gk_intro_content['format'],
      '#description' => t('The Introduction text is displayed above the "Start Review" button in
        the Gate Keeper tab, prior to the start of the review.'),
    );

    $form += feedback_admin_review_fields('resource_gate_keeper', $form_state);

  // custom submit handler to update criteria fieldset cardinality
    $form['#submit'][] = 'feedback_gate_keeper_admin_form_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for feedback_gate_keeper_admin_form();
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function feedback_gate_keeper_admin_form_submit($form, &$form_state) {
  // update the field count/cardinality
  // maybe instead of a direct query, this should be ran through one of the field_instance_* functions?
    db_update('field_config')
      ->fields(array(
        'cardinality' => (int) $form_state['values']['resource_gate_keeper_criteria_num'],
      ))
      ->condition('field_name', 'field_quality_set')
      ->execute();

  // we must clear the field cache in order for the changes to take immediate effect
    field_cache_clear();
}

/**
 * Callback for /admin/sbac/feedback/quality_review
 * @return [type] [description]
 */
function feedback_quality_review_admin_form($form, &$form_state) {
  // form into
    $form['#prefix'] = t('This form provides configuration options for
      elements found in the "Quality Review" tab on Resource pages.');

    $form['quality_review'] = array(
      '#markup' => '<h2>' . t('Quality Review') . '</h2>',
    );

  // introduction text
    $intro_content = variable_get('resource_review_intro', input_default_full_html());
    $form['resource_review_intro'] = array(
      '#title' => t('Introduction'),
      '#type' => 'text_format',
      '#default_value' => $intro_content['value'],
      '#format' => $intro_content['format'],
      '#description' => t('The Introduction text is displayed above the "Start Review" button in
        the Review tab, prior to the start of the review.'),
    );

  // descriptions for Quality Criterion Level radios
    if ($level_options = field_allowed_values('field_level')) {
      $form['level'] = array(
        '#type' => 'fieldset',
        '#title' => t('Quality Criterion Level Descriptions'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

        foreach ($level_options as $value => $label) {
          $field_name = 'qc_level_' . $value;

          $level_content = variable_get($field_name, input_default_full_html());

          $form['level'][$field_name] = array(
            '#title' => t('Description for Level !level', array('!level' => $label)),
            '#type' => 'text_format',
            '#default_value' => $level_content['value'],
            '#format' => $level_content['format'],
          );
        }
    }

  // descriptions for Recommendation Options radios
    if ($rec_options = field_allowed_values('field_rec_options')) {
      $form['recommendation'] = array(
        '#type' => 'fieldset',
        '#title' => t('Recommendation Options Descriptions'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#suffix' => '<br />',
      );

        foreach ($rec_options as $value => $label) {
          $field_name = 'qc_rec_' . $value;

          $option_content = variable_get($field_name, input_default_full_html());

          $form['recommendation'][$field_name] = array(
            '#title' => t('Description for option !option', array('!option' => $label)),
            '#type' => 'text_format',
            '#default_value' => $option_content['value'],
            '#format' => $option_content['format'],
          );
        }
    }

  // we need to log the term ids of terms in this vocab, so we can easily access them
  // in the submit handler
    $form_state['feedback_focus_tids'] = array();

  // we'll generate a set of fields for every term in the vocab
    if ($vocab = taxonomy_vocabulary_machine_name_load('focus')) {
      foreach (taxonomy_get_tree($vocab->vid) as $term) {
        $form_state['feedback_focus_tids'][] = $term->tid;

        $form['term_' . $term->tid] = array(
          '#type' => 'fieldset',
          '#title' => t('Quality Review Criteria for !title', array('!title' => $term->name)),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );

        $form['term_' . $term->tid] += feedback_admin_review_fields('qc_' . $term->tid, $form_state);
      }
    }

  // custom submit handler to update criteria fieldset cardinality
    $form['#submit'][] = 'feedback_quality_review_admin_form_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for feedback_gate_keeper_admin_form();
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function feedback_quality_review_admin_form_submit($form, &$form_state) {
  /*
  if (isset($form_state['feedback_focus_tids']) && $form_state['feedback_focus_tids']) {
    $max = 0;
    foreach ($form_state['feedback_focus_tids'] as $tid) {
      $field_name = 'qc_' . $tid . '_criteria_num';

      if (isset($form_state['values'][$field_name]) && $form_state['values'][$field_name] > $max) {
        $max = $form_state['values'][$field_name];
      }
    }

    // update the field count/cardinality
      db_update('field_config')
        ->fields(array(
          'cardinality' => (int) $max,
        ))
        ->condition('field_name', 'field_review_set')
        ->execute();

    // we must clear the field cache in order for the changes to take immediate effect
      field_cache_clear();
  }
  */
}

/**
 * Callback for /admin/sbac/feedback/post
 */
function feedback_post_admin_form($form, &$form_state) {
  // form into
    $form['#prefix'] = t('This form provides configuration options for
      elements found in the "Post" tab on Resource pages.');

    $form['post'] = array(
      '#markup' => '<h2>' . t('Post') . '</h2>',
    );

  // introduction text
    $intro_content = variable_get('resource_post_intro', input_default_full_html());
    $form['resource_post_intro'] = array(
      '#title' => t('Introduction'),
      '#type' => 'text_format',
      '#default_value' => $intro_content['value'],
      '#format' => $intro_content['format'],
      '#description' => t('The Introduction text is displayed above the "Start Review" button in
        the Post tab, prior to the start of the review.'),
    );

  // helpful info text
    $help_content = variable_get('resource_post_help', input_default_full_html());
    $form['resource_post_help'] = array(
      '#title' => t('Helpful Information'),
      '#type' => 'text_format',
      '#default_value' => $help_content['value'],
      '#format' => $help_content['format'],
      '#description' => t('The Helpful Information text is displayed at the top of the 
        form once the review has been started.'),
    );

  // descriptions for Quality Criterion Level radios
    if ($post_options = field_allowed_values('field_post_options')) {
      $form['post_options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Post Options Descriptions'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

        foreach ($post_options as $value => $label) {
          $field_name = 'post_options_' . $value;

          $post_content = variable_get($field_name, input_default_full_html());

          $form['post_options'][$field_name] = array(
            '#title' => t('Description for Level !level', array('!level' => $label)),
            '#type' => 'text_format',
            '#default_value' => $post_content['value'],
            '#format' => $post_content['format'],
          );
        }
    }

  return system_settings_form($form);
}

/**
 * Common form elements for admin forms on the Gate Keeper & Quality review pages.
 * @param  [type] $prefix [description]
 * @return [type]         [description]
 */
function feedback_admin_review_fields($prefix, $form_state) {
  $form = array();

  $prefix .= '_';

  // helpful info text
    $help_content = variable_get($prefix . 'help', input_default_full_html());
    $form[$prefix . 'help'] = array(
      '#title' => t('Helpful Information'),
      '#type' => 'text_format',
      '#default_value' => $help_content['value'],
      '#format' => $help_content['format'],
      '#description' => t('The Helpful Information text is displayed at the top of the 
        form once the review has been started.'),
    );

  // hide criteria for non superadmins
    global $user;
    if ($user->uid !== '1') {
      $form['hide_criteria'] = array(
        '#markup' => '<div class="hide-criteria">',
      );
    }

  // number of criteria sets
    $num_sets = variable_get($prefix . 'criteria_num', FEEDBACK_DEFAULT_SET_COUNT);
    $options = range(1, 100);
    $options = array_combine(array_values($options), array_values($options));

    $criteria_wrapper_id = $prefix . 'criteria_fieldsets';

    $form[$prefix . 'criteria_num'] = array(
      '#type' => 'select',
      '#title' => t('Criteria Set Count'),
      '#options' => $options,
      '#default_value' => $num_sets,
      '#description' => t('How many Criteria Sets should be displayed?'),
      '#ajax' => array(
        'callback' => 'feedback_admin_form_criteria_sets',
        'wrapper' => $criteria_wrapper_id,
        'effect' => 'fade',
      ),
    );

  // create the criteria sets
    if (isset($form_state['values'][$prefix . 'criteria_num'])) {
      $num_sets = $form_state['values'][$prefix . 'criteria_num'];
    }

    $set_fields = array(
      array(
        'name' => t('Title'),
        'desc' => '',
      ),
      array(
        'name' => t('Description'),
        'desc' => '',
      ),
      array(
        'name' => t('Radio buttons help text'),
        'desc' => t('Text diplayed under the radio buttons.'),
      ),
    );

    $form['criteria_sets'] = array(
      '#prefix' => '<div id="' . $criteria_wrapper_id . '">',
      '#suffix' => '</div>',
    );

    for ($i = 1; $i <= $num_sets; $i++) {
      $weight = 0;
      $fieldset_name = $prefix . 'criteria_' . $i;

      $form['criteria_sets'][$fieldset_name] = array(
        '#type' => 'fieldset',
        '#title' => t('Criteria Set !num', array('!num' => $i)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      foreach ($set_fields as $field) {
        $field_name = $field['name'];
        $machine_field_name = strtolower(preg_replace('/[^0-9a-zA-Z]/', '', $field_name));
        $full_field_name = $prefix . 'criteria_' . $i . '_' . $machine_field_name;

        $description = isset($field['desc']) ? $field['desc'] : '';
        $content = variable_get($full_field_name, input_default_full_html());

        if (strtolower($field_name) == 'title' && $content['value']) {
          $form['criteria_sets'][$fieldset_name]['#title'] .= ' (' . check_plain(strip_tags($content['value'])) . ')';
        }

        $form['criteria_sets'][$fieldset_name][$full_field_name] = array(
          '#title' => $field_name,
          '#description' => $description,
          '#type' => 'text_format',
          '#default_value' => $content['value'],
          '#format' => $content['format'],
          '#weight' => $weight,
        );

        $weight += 2;
      }

      $desc_state_field_name = $prefix . 'criteria_' . $i . '_desc_state';
      $form['criteria_sets'][$fieldset_name][$desc_state_field_name] = array(
        '#type' => 'radios',
        '#title' => t('Display description'),
        '#options' => array(
          'collapsed' => t('Collapsed'),
          'expanded' => t('Expanded'),
        ),
        '#default_value' => variable_get($desc_state_field_name, 'collapsed'),
        '#description' => t('Choose how the description will be displayed.'),
        '#weight' => 3,
      );
    }

    if ($user->uid !== '1') {
      $form['hide_criteria_close'] = array(
        '#markup' => '</div >',
      );
    }
  return $form;
}

/**
 * Callback for AJAX event to rebuild the quality criteria form sets.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function feedback_admin_form_criteria_sets($form, $form_state) {
  $parents = $form_state['triggering_element']['#array_parents'];

  // in the Quality Criteria form, the criteria sets are nested inside a fieldset, so
  // we need to pull from from the appropriate place within the form array
  if (sizeof($parents) == 2) {
    return $form[$parents[0]]['criteria_sets'];
  }
  // in the Gate Keeper form, the criteria sets are right in the root of the form
  else {
    return $form['criteria_sets'];
  }
}






















