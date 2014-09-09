<?php
/**
 * @file
 * Include file for Forum Statistics Report
 *
 * Provides:
 *  - UI forms and handler
 *  - Batch functions for running the report
 *  - The column specifications for the report
 *  - Functions necessary to retrieve the values of the report
 */

/**
 * Forum types
 *
 * @return array
 */
function sbac_report_forum_type_options() {
  return array(
    '0' => 'All',
    'resource' => 'Resource',
    'topic' => 'Topic'
  );
}

/**
 * Form definition for forum statistic report
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function sbac_csv_report_forum_stats_form($form, &$form_state) {
  $form = array();

  $form['resource_type_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose a forum type:'),
    '#required' => TRUE,
    '#multiple' => TRUE,
    '#options' => sbac_report_forum_type_options(),
    '#default_value' => 0,
    '#attributes' => array('class' => array('chosen-widget')),

  );
  $form['resource_subject_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose subject:'),
    '#options' => sbac_report_resource_subject_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_subject_option($form_state),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_grade_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose grade:'),
    '#options' => sbac_report_resource_grade_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_grade_option($form_state),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
  );

  return $form;
}


/**
 * Form validate
 *
 * @param $form
 * @param $form_state
 */
function sbac_csv_report_forum_stats_form_validate($form, &$form_state) {
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_FORUM;
}

/**
 * Form submit handler
 *
 * @param $form
 * @param $form_state
 */
function sbac_csv_report_forum_stats_form_submit($form, &$form_state) {
  // State.
  $resource_filters = array();
  if ($form_state) {
    set_resource_filter($resource_filters, 'types', $form_state['values']['resource_type_dropdown'], sbac_report_forum_type_options());
    set_resource_filter($resource_filters, 'subject', $form_state['values']['resource_subject_dropdown'], sbac_report_resource_subject_options());
    set_resource_filter($resource_filters, 'grade', $form_state['values']['resource_grade_dropdown'], sbac_report_resource_grade_options());
  }

  $_SESSION['report_chosen_filters'] = $resource_filters;
  $resources = sbac_report_forum_get_forums($resource_filters);
  if ($resources) {
    batch_set(array(
        'title' => t('Forum Statistics Report'),
        'operations' => array(
          array('sbac_report_forum_statistics_batch', array($resources, $resource_filters)),
        ),
        'finished' => 'sbac_report_forum_statistics_finished_batch', // Finished batch callback.
      )
    );
    batch_process('reports');
  }
  else {
    drupal_set_message(SBAC_REPORT_FILTER_ERROR, 'error');
    $_SESSION['sbac_report']['first_time'] = 1;
  }
}

/**
 * Get forums according to the filters
 *
 * @param $resource_filters
 * @return array
 */
function sbac_report_forum_get_forums($resource_filters) {

  $query = db_select('taxonomy_vocabulary', 'v');
  $query->innerJoin('taxonomy_term_data', 't', 't.vid = v.vid');
  $query->condition('v.machine_name', 'forum');

  // Filter: Forum Type
  if (!empty($resource_filters['types'])) {
    $query->leftJoin('field_data_field_forum_resource_ref', 'r', 'r.entity_id = t.tid AND r.bundle = \'forum\'');
    if (isset($resource_filters['types'][0])) {
      // User selected 'All', do nothing
    }
    elseif (isset($resource_filters['types']['resource']) && isset($resource_filters['types']['topic'])) {
      // user selected 'resource' and 'topic', this is the same as 'all', so do nothing
    }
    elseif (isset($resource_filters['types']['resource'])) {
      // user only wants resource forums
      $query->isNotNull('r.field_forum_resource_ref_target_id');
    }
    elseif (isset($resource_filters['types']['topic'])) {
      // user only wants topic forums
      $query->isNull('r.field_forum_resource_ref_target_id');
    }
  }

  // Filter: Subject
  if (!empty($resource_filters['subject'])) {
    if (isset($resource_filters['subject'][0])) {
      // user selected 'all', do nothing
    }
    elseif (isset($resource_filters['subject'][1])) {
      // user selected 'Not Yet Selected'
      $query->leftJoin('field_data_field_subject', 's', 's.entity_id = t.tid AND s.bundle = \'forum\'');
      $query->isNull('s.field_subject_tid');
    }
    else {
      $query->leftJoin('field_data_field_subject', 's', 's.entity_id = t.tid AND s.bundle = \'forum\'');
      $query->condition('s.field_subject_tid', array_keys($resource_filters['subject']), 'IN');
    }
  }

  // Filter: Grade
  if (!empty($resource_filters['grade'])) {
    if (isset($resource_filters['grade'][0])) {
      // user selected 'all', do nothing
    }
    elseif (isset($resource_filters['grade'][1])) {
      // user selected 'Not Yet Selected'
      $query->leftJoin('field_data_field_grades', 'g', 'g.entity_id = t.tid AND g.bundle = \'forum\'');
      $query->isNull('g.field_grades_tid');
    }
    else {
      $query->leftJoin('field_data_field_grades', 'g', 'g.entity_id = t.tid AND g.bundle = \'forum\'');
      $query->condition('g.field_grades_tid', array_keys($resource_filters['grade']), 'IN');
    }
  }

  return $query->fields('t', array('tid'))->groupBy('t.tid')->execute()->fetchCol();
}

/**
 * Forum Statistics report column configuration
 *
 * @return array
 */
function sbac_report_forum_get_columns() {
  return array(
    'Title' => array(
      'function' => 'sbac_report_get_entity_wrapper_value',
      'arguments' => array(
        'field_name' => 'name',
      )
    ),
    'Type' => array(
      'function' => 'sbac_report_forum_get_type'
    ),
    'Description' => array(
      'function' => 'sbac_report_get_entity_wrapper_value',
      'arguments' => array(
        'field_name' => 'field_forum_description',
      )
    ),
    'Date Created' => array(
      'function' => 'sbac_report_forum_get_date_created',
    ),
    'Created By Email' => array(
      'function' => 'sbac_report_forum_get_created_by_email',
    ),
    'Created By Name' => array(
      'function' => 'sbac_report_forum_get_created_by_name',
    ),
    'Created By State' => array(
      'function' => 'sbac_report_forum_get_created_by_state',
    ),
    'Visibility: States' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_state',
        'default' => 'All',
      )
    ),
    'Visibility: Users' => array(
      'function' => 'sbac_report_forum_get_visibility_users',
    ),
    'Subjects/Domain' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_subject',
      )
    ),
    'Grades' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_grades',
      )
    ),
    'Attributes of the Formative Assessment Process' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_attributes',
      )
    ),
    'Intended Student Populations' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_intended_student',
      )
    ),
    'Intended Forum Participants' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_intended_end_user',
      )
    ),
    'Geographic Settings' => array(
      'function' => 'sbac_report_get_entity_wrapper_multi_value',
      'arguments' => array(
        'field_name' => 'field_geographical_settings',
      )
    ),
    'Number of Participants' => array(
      'function' => 'sbac_report_get_entity_wrapper_value',
      'arguments' => array(
        'field_name' => 'field_forum_member_count',
      )
    ),
    'Number of Unique Views' => array(
      'function' => 'sbac_report_forum_get_unique_views'
    ),
    'Favorites: Total # Users' => array(
      'function' => 'sbac_report_forum_get_favorite_count'
    ),
    'Number of Topics' => array(
      'function' => 'sbac_report_get_entity_wrapper_value',
      'arguments' => array(
        'field_name' => 'field_forum_topic_count',
      )
    ),
    'Number of Posts' => array(
      'function' => 'sbac_report_get_entity_wrapper_value',
      'arguments' => array(
        'field_name' => 'field_forum_topic_comment_count',
      )
    ),
    'Last Activity Date' => array(
      'function' => 'sbac_report_forum_get_last_activity',
    ),
    'Number of Recommended Posts' => array(
      'function' => 'sbac_report_forum_get_recommended_count'
    ),
    'Number of Flagged Topics' => array(
      'function' => 'sbac_report_forum_get_flagged_topic_count'
    ),
    'Number of Flagged Posts' => array(
      'function' => 'sbac_report_forum_get_flagged_post_count'
    ),
  );
}

/**
 * Batch function
 *
 * @param $forums
 * @param $forum_filters
 * @param $context
 */
function sbac_report_forum_statistics_batch($forums, $forum_filters, &$context) {
  $limit = 50;
  $context['sandbox']['finished'] = 0;
  ini_set('max_execution_time', 300);

  // First time through.
  if (!isset($context['sandbox']['file'])) {
    $columns = sbac_report_forum_get_columns();
    $context['sandbox']['report_configuration'] = $columns;

    // CSV Headers.
    $column_titles = array();
    foreach ($columns as $title => $field_config) {
      $column_titles[] = $title;
    }

    $directory = "private://forum_stats_csv/";
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'Forum_Statistics_' . date('M_d_Y_g_i_s') . '.csv';
    $directory .= $filename;
    $directory_real_path = drupal_realpath($directory);
    $handle = fopen($directory_real_path, 'w'); // Create the file.
    fputcsv($handle, $column_titles); // Write the labels to the header row.
    fclose($handle);

    // Store info in sandbox during processing.
    $context['sandbox']['file'] = $directory_real_path;

    // Store some values in the results array for processing when finished.
    $context['results']['filename'] = $filename;
    $context['results']['file'] = $directory_real_path;

    if (file_exists($directory_real_path)) {
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['forums'] = $forums;
      $context['sandbox']['forum_filters'] = $forum_filters;
      $context['sandbox']['forum_total'] = count($context['sandbox']['forums']);
    }

    unset($column_titles);
    unset($columns);
    unset($directory);
    unset($directory_real_path);
    unset($filename);
  }

  unset($forums);
  unset($forum_filters);

  // Open the file for writing ('a' puts pointer at end of file).
  $handle = fopen($context['sandbox']['file'], 'a');

  if (!isset($context['results']['count'])) {
    $context['results']['count'] = 0;
  }

  // Loop until we hit the batch limit.
  $report_configuration = $context['sandbox']['report_configuration'];
  for ($i = 0; $i < $limit; $i++) {
    if ($context['sandbox']['forums']) {
      $tid = array_shift($context['sandbox']['forums']);
      $term = taxonomy_term_load($tid);
      $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
      if ($term_wrapper) {
        $data = array();
        $row = array();
        foreach ($report_configuration as $title => $field_config) { // (columns)
          try {
            $val = '';
            if (!empty($field_config['function'])) {
              $function = $field_config['function'];
              if (!empty($field_config['arguments'])) {
                $val = $function($term_wrapper, $field_config['arguments']);
              }
              else {
                $val = $function($term_wrapper);
              }
            }
            $row[] = $val;
          } catch (EntityMetadataWrapperException $e) {
            $row[] = '';
          }
        }
        fputcsv($handle, $row);
        unset($row);
        unset($data);
        $context['results']['count']++;
        $context['finished'] = $context['results']['count'] / $context['sandbox']['forum_total'];
      }
      unset($term);
      unset($term_wrapper);
    }
  }

  fclose($handle);
  unset($handle);

  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total resources.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['forum_total'],
  ));
}

/**
 * Batch finish function
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_forum_statistics_finished_batch($success, $results, $operations) {
  if ($success) {
    $directory = "private://forum_stats_csv/";
    $directory .= $results['filename'];
    $directory_real_path = drupal_realpath($directory);
    $mime_type = file_get_mimetype($directory);

    global $user;
    $dir_file = new stdClass();
    $dir_file->uid = $user->uid;
    $dir_file->filename = $results['filename'];
    $dir_file->uri = $directory;
    $dir_file->filemime = $mime_type;
    $dir_file->filesize = filesize($directory_real_path);
    $dir_file->status = 1;
    $dir_file->timestamp = time();
    $dir_file->type = $mime_type;
    drupal_write_record('file_managed', $dir_file);

    $web_url = file_create_url($directory);
    $download_link = l(t('click here to download the file'), $web_url, array('attributes' => array('class' => array('sbac-report-download-link'))));
    $message = '<span class="sbac-report-download">' . t('The resource statistics CSV report file is now ready for download. Please !download_link.', array('!download_link' => $download_link)) . '</span>';

    gc_enable();
    gc_collect_cycles();
    gc_disable();
    //_cex_download($csv_resource_stats_result, 'output.csv');
    $_SESSION['report_chosen_filters'] = '';
  }
  else {
    $message = t('Finished with an error. Please try again.');
  }
  drupal_set_message($message);
}


/**
 * Get the forum type
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_type($term_wrapper) {
  $type = 'Topic Forum';
  if ($term_wrapper->field_forum_resource_ref->value()) {
    $type = 'Resource Forum';
  }
  return $type;
}

/**
 * Get the forum's created date
 *
 * @param $term_wrapper
 * @return bool|string
 */
function sbac_report_forum_get_date_created($term_wrapper) {
  if ($term_wrapper->field_forum_resource_ref->value()) {
    $date = $term_wrapper->field_forum_resource_ref->created->value();
  }
  else {
    $date = $term_wrapper->field_forum_created->value();
  }
  return date('m/d/Y', $date);
}

/**
 * Get the forum's author's mail
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_created_by_email($term_wrapper) {
  if ($term_wrapper->field_forum_resource_ref->value()) {
    $email = $term_wrapper->field_forum_resource_ref->author->mail->value();
  }
  else {
    $email = $term_wrapper->field_forum_facilitators[0]->mail->value();
  }
  return $email;
}

/**
 * Get the forum's author's name
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_created_by_name($term_wrapper) {
  if ($term_wrapper->field_forum_resource_ref->value()) {
    $name = $term_wrapper->field_forum_resource_ref->author->field_first_name->value() . ' ' . $term_wrapper->field_forum_resource_ref->author->field_last_name->value();
  }
  else {
    $name = $term_wrapper->field_forum_facilitators[0]->field_first_name->value() . ' ' . $term_wrapper->field_forum_facilitators[0]->field_last_name->value();
  }
  return $name;
}

/**
 * Get the forum's author's state
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_created_by_state($term_wrapper) {
  if ($term_wrapper->field_forum_resource_ref->value()) {
    $states = $term_wrapper->field_forum_resource_ref->author->field_state->value();
    $state_terms = array();
    if (!empty($states)) {
      foreach ($states as $state) {
        $state_terms[] = $state->name;
      }
    }
  }
  else {
    $state_terms[] = $term_wrapper->field_forum_facilitators[0]->author->field_state->value();
  }
  return implode(', ', $state_terms);
}

/**
 * Get the forum's visibility
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_visibility_users($term_wrapper) {
  $output = array();
  if (!$term_wrapper->field_forum_resource_ref->value()) {
    $roles = $term_wrapper->field_forum_access_role_list->value();
    if (!empty($roles)) {
      foreach ($roles as $role) {
        $user_role = user_role_load($role);
        $output[] = $user_role->name;
      }
    } else {
      $output[] = 'All';
    }
  }
  return implode(', ', $output);
}

/**
 * Get the number of unique forum views
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_unique_views($term_wrapper) {
  return db_select('sbac_forum_views', 'v')->condition('tid', $term_wrapper->tid->value())->fields('v', array('uid'))->distinct()->countQuery()->execute()->fetchField();
}

/**
 * Get the number of people that have favorited the forum
 *
 * @param $term_wrapper
 * @return mixed
 */
function sbac_report_forum_get_favorite_count($term_wrapper) {
  $query = db_select('sbac_favorites', 'f');
  if ($term_wrapper->field_forum_resource_ref->value()) {
    $query->condition('f.type', 'node');
    $query->condition('f.id', $term_wrapper->field_forum_resource_ref->nid->value());
  }
  else {
    $query->condition('f.type', 'term');
    $query->condition('f.id', $term_wrapper->tid->value());
  }
  $query->condition('f.uid', 0, '>');
  return $query->fields('f', array('id'))->countQuery()->execute()->fetchField();
}

/**
 * Get the forum's last activity date
 *
 * @param $term_wrapper
 * @return bool|string
 */
function sbac_report_forum_get_last_activity($term_wrapper) {
  return date('m/d/Y', $term_wrapper->field_forum_last_activity->value());
}

/**
 * Get the number of recommended posts
 *
 * @param $term_wrapper
 * @return mixed
 */
function sbac_report_forum_get_recommended_count($term_wrapper) {
  $query = db_select('comment', 'c');
  $query->innerJoin('field_data_field_topic_comment_recommended', 'r', 'r.entity_id = c.cid AND r.entity_type = \'comment\'');
  $query->innerJoin('field_data_field_topic_forum_parent', 'p', 'p.entity_id = c.nid');
  $query->condition('p.field_topic_forum_parent_tid', $term_wrapper->tid->value());
  return $query->fields('c', array('cid'))->countQuery()->execute()->fetchField();
}

/**
 * Get the number of flagged topics in a forum
 *
 * @param $term_wrapper
 * @return string
 */
function sbac_report_forum_get_flagged_topic_count($term_wrapper) {
  $query = db_select('eck_flag', 'f');
  $query->innerJoin('field_data_field_topic_forum_parent', 'p', 'p.entity_id = f.target_id AND f.target_type = \'topic\'');
  $query->condition('p.field_topic_forum_parent_tid', $term_wrapper->tid->value());
  return $query->fields('f', array('id'))->countQuery()->execute()->fetchField();
}

/**
 * Get the number of flagged posts
 *
 * @param $term_wrapper
 * @return mixed
 */
function sbac_report_forum_get_flagged_post_count($term_wrapper) {
  $query = db_select('eck_flag', 'f');
  $query->innerJoin('comment', 'c', 'c.cid = f.target_id AND f.target_type = \'comment\'');
  $query->innerJoin('field_data_field_topic_forum_parent', 'p', 'p.entity_id = c.nid');
  $query->condition('f.type', 'topic');
  $query->condition('p.field_topic_forum_parent_tid', $term_wrapper->tid->value());
  return $query->fields('c', array('cid'))->groupBy('c.cid')->countQuery()->execute()->fetchField();

}

/**
 * Get a field value from the entity wrapper
 *
 * @param $entity_wrapper
 * @param $args
 * @return string
 */
function sbac_report_get_entity_wrapper_value($entity_wrapper, $args) {
  if (!empty($args['field_name'])) {
    return $entity_wrapper->{$args['field_name']}->value();
  }
  return '';
}

/**
 * Get a multi value field from the entity wrapper
 *
 * @param $term_wrapper
 * @param $args
 * @return string
 */
function sbac_report_get_entity_wrapper_multi_value($term_wrapper, $args) {
  $output = array();
  if (!empty($args['field_name'])) {
    $attributes = $term_wrapper->{$args['field_name']}->value();
    if (!empty($attributes)) {
      foreach ($attributes as $attr) {
        $output[] = $attr->name;
      }
    }
    else {
      if (!empty($args['default'])) {
        $output[] = $args['default'];
      }
    }
  }
  return implode(', ', $output);
}