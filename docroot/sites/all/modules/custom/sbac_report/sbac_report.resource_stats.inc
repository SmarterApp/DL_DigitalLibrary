<?php
/**
 * CSV Report resource statistics form.
 */

function sbac_csv_report_resource_stats_form($form, &$form_state) {
  $form = array();

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'sbac_report') . '/js/sbac_report.csv.js',
  );

  $form['resource_type_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose resource type:'),
    '#options' => sbac_report_resource_type_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_type_option($form_state),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_status_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose resource status'),
    '#options' => sbac_report_resource_status_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_status_option($form_state),
    '#required' => TRUE,
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
  $form['resource_attribute_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose attribute of the formative assessment process:'),
    '#options' => sbac_report_resource_attribute_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_attribute_option($form_state),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_state_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose contributor state'),
    '#options' => sbac_report_state_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_get_default_state_tid(),
    '#attributes' => array('class' => array('chosen-widget')),
    '#ajax' => array(
      'callback' => 'sbac_report_state_ajax',
    ),
    '#required' => TRUE,
  );
  // Reports administrator only sees their own state
  if (sbac_central_user_has_role(array('reports administrator'))) {
    $form['resource_state_dropdown']['#multiple'] = FALSE;
    // $form['resource_state_dropdown']['#disabled'] = TRUE;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
    '#submit' => array('sbac_csv_report_resource_stats_export_form_submit'),
//    '#attributes' => array('OnSubmit' => 'closeSecondaryAlert();'),
  );

  $form['#validate'][] = 'sbac_csv_report_resource_stats_form_validate';

  return $form;
}

/**
 * CSV Report: form validate.
 */
function sbac_csv_report_resource_stats_form_validate($form, &$form_state) {
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_STATES;

  if (sbac_central_user_has_role(array('reports administrator'))) {
    if ($form_state['values']['resource_state_dropdown'] != sbac_report_get_default_state_tid()) {
      form_set_error('state', t('You\'re only allowed to select your own state'));
    }
  }
}

/**
 * Submit to do the export for the detailed resource statistics csv report.
 */
function sbac_csv_report_resource_stats_export_form_submit($form, &$form_state) {
  // State.
  $resource_filters = array();
  if ($form_state) {
    set_resource_filter($resource_filters, 'types', $form_state['values']['resource_type_dropdown'], sbac_report_resource_type_options());
    set_resource_filter($resource_filters, 'subject', $form_state['values']['resource_subject_dropdown'], sbac_report_resource_subject_options());
    set_resource_filter($resource_filters, 'grade', $form_state['values']['resource_grade_dropdown'], sbac_report_resource_grade_options());
    set_resource_filter($resource_filters, 'status', $form_state['values']['resource_status_dropdown'], sbac_report_resource_status_options());
    set_resource_filter($resource_filters, 'attribute', $form_state['values']['resource_attribute_dropdown'], sbac_report_resource_attribute_options());
    set_resource_filter($resource_filters, 'state', $form_state['values']['resource_state_dropdown'], sbac_report_state_options());
  }

  $_SESSION['report_chosen_filters'] = $resource_filters;
  $resources = sbac_report_get_resources($resource_filters);
  if ($resources) {
    batch_set(array(
        'title' => t('Resource Statistics Report'),
        'operations' => array(
          array('sbac_report_resource_statistics_batch', array($resources, $resource_filters)),
        ),
        'finished' => 'sbac_report_resource_statistics_finished_batch', // Finished batch callback.
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
 * Filter out resources that don't match a criteria
 */
function set_resource_filter(&$resource_filters, $key, $form_value, $all_values) {
  if (in_array('1', $form_value) && $key != 'status') { // not yet assigned
    $resource_filters[$key] = $all_values;
    unset($resource_filters[$key][0]); // remove 'All'.
  }
  else {
    $resource_filters[$key] = $form_value;
  }
}


/**
 * @param $resources
 * @param $resource_filters
 * @param $context
 */
function sbac_report_resource_statistics_batch($resources, $resource_filters, &$context) {
  $limit = 50;
  $context['sandbox']['finished'] = 0;
  ini_set('max_execution_time', 300);

  // First time through.
  if (!isset($context['sandbox']['file'])) {
    $columns = set_report_columns();
    $context['sandbox']['report_configuration'] = $columns;

    // CSV Headers.
    $column_titles = array();
    foreach ($columns as $configuration) {
      foreach ($configuration['fieldkeys'] as $fieldkey) {
        if (array_key_exists(1, $fieldkey)) {
          $column_titles[] = $fieldkey[1];
        }
        else {
          $column_titles[] = '';
        }
      }
    }

    $directory = "private://resource_stats_csv/";
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'Resource_Statistics_' . date('M_d_Y_g_i_s') . '.csv';
    $directory .= $filename;
    $directory_real_path = drupal_realpath($directory);
    $handle = fopen($directory_real_path, 'w'); // Create the file.
    fputcsv($handle, $column_titles); // Write the labels to the header row.
    fclose($handle);

    // Store info in sandbox during processing.
    $context['sandbox']['file'] = $directory_real_path;

    // Store some values in the results array for processing when finshed.
    $context['results']['filename'] = $filename;
    $context['results']['file'] = $directory_real_path;

    if (file_exists($directory_real_path)) {
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['resources'] = $resources;
      $context['sandbox']['resource_filters'] = $resource_filters;
      $context['sandbox']['resources_total'] = count($context['sandbox']['resources']);
    }

    unset($column_titles);
    unset($columns);
    unset($configuration);
    unset($directory);
    unset($directory_real_path);
    unset($fieldkey);
    unset($filename);
  }

  unset($resources);
  unset($resource_filters);

  // Open the file for writing ('a' puts pointer at end of file).
  $handle = fopen($context['sandbox']['file'], 'a');

  if (!isset($context['results']['count'])) {
    $context['results']['count'] = 0;
  }

  // Loop until we hit the batch limit.
  $report_configuration = $context['sandbox']['report_configuration'];
  $schema = $report_configuration['node_schema'];
  for ($i = 0; $i < $limit; $i++) {
    if ($context['sandbox']['resources']) {
      $nid = array_shift($context['sandbox']['resources']);
      $node = node_load($nid);
      if ($node) {
        $entity_node = entity_metadata_wrapper('node', $node);
        if ($entity_node) {
          $resource_feedback = get_entities_for_resources($nid);
          $workbench_moderation = get_workbench_moderation_history($entity_node);
          $share_data = get_share_data_for_resource($entity_node);
          ksort($workbench_moderation);

          $data = array();
          $data['resource_node'] = $entity_node;
          $data['resource_feedback'] = $resource_feedback;
          $data['workbench_moderation'] = $workbench_moderation;
          $data['share'] = $share_data;
          get_counts_for_resource_stats($entity_node, $data);
          get_counts_for_flags($entity_node, $data);
          $review_count = get_reviews_for_resources($entity_node, $data);
          if (!isset($context['results']['review_count'])) {
            $context['results']['review_count'] = $review_count;
          }
          else {
            if ($review_count > $context['results']['review_count']) {
              $context['results']['review_count'] = $review_count;
            }
          }

          unset($resource_feedback);
          unset($workbench_moderation);
          unset($share_data);
          unset($authors);
          unset($reviewers);

          $row = array();
          foreach ($schema['fieldkeys'] as $field_key) { // (columns)
            if (isset($field_key['skip']) && $field_key['skip']) {
              continue;
            }

            $primary_key = 'nid';
            if (array_key_exists('primarykey', $field_key)) {
              $primary_key = $field_key['primarykey'];
            }
            $value = get_field_value_using_schema($field_key, $data, $entity_node, $primary_key, $is_date);
            if (array_key_exists('field', $field_key)) {
              $final_value = format_metadata_value_field($value, $is_date, $field_key['field'], $entity_node);
            }
            else {
              $final_value = format_metadata_value_field($value, $is_date, NULL, $entity_node);
            }
            $row[] = $final_value;

            unset($final_value);
            unset($field_key);
            unset($is_date);
            unset($primary_key);
            unset($value);
          }
          unset($field_key);

          fputcsv($handle, $row);
          unset($row);
          unset($data);
          $context['results']['count']++;
          $context['finished'] = $context['results']['count'] / $context['sandbox']['resources_total'];
        }
        unset($entity_node);
      }
      unset($node);
    }
  }

  fclose($handle);
  unset($handle);

  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total resources.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['resources_total'],
  ));
}


/**
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_resource_statistics_finished_batch($success, $results, $operations) {
  if ($success) {
    $directory = "private://resource_stats_csv/";
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
 * Query for a taxonomy term given an sql string, add 'All' to the query result.  Used for dropdowns on the
 * detailed resource stats csv report.
 */
function query_taxonomy_term($sql) {
  $result = db_query($sql);
  $values = array();
  $values[0] = 'All';

  foreach ($result as $record) {
    $children = taxonomy_get_children($record->tid);
    if (empty($children)) {
      $values[$record->tid] = sbac_resource_taxonomy_term_concat_parents($record->tid, $record->name);
    }
  }
  return $values;
}

/**
 * Resource Type Dropdown options extracted from the taxonomy table.
 */
function sbac_report_resource_type_options() {
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'focus')";

  return query_taxonomy_term($sql);
}

/**
 * Default options for the resource type option list
 */
function sbac_report_default_resource_type_option($form_state = array()) {
  if (isset($_SESSION['report_chosen_filters']['types']) && $_SESSION['report_chosen_filters']['types']) {
    $options = $_SESSION['report_chosen_filters']['types'];
    if (in_array('All', $options)) {
      return 0;
    }
    else {
      return $options;
    }
  }
  return 0;
}

/**
 * Resource Status Dropdown options extracted from the taxonomy table.
 */
function sbac_report_resource_status_options() {
  $options = array(
    'All',
    'Draft',
    'Submitted',
    'Gate-Keeping Review',
    'Quality Criteria Review 1',
    'Quality Criteria Review 2',
    'Quality Criteria Review 3',
    'Arbitration Review',
    'Returned',
    'Posted',
    'Posted with Distinction',
    'Removed',
  );
  return $options;
}

/**
 * Default options for the resource status option list
 */
function sbac_report_default_resource_status_option($form_state = array()) {
  if (isset($_SESSION['report_chosen_filters']['status']) && $_SESSION['report_chosen_filters']['status']) {
    $options = $_SESSION['report_chosen_filters']['status'];
    if (in_array('All', $options)) {
      return 0;
    }
    else {
      return $options;
    }
  }
  return 0;
}

/**
 * Resource Subject Dropdown options extracted from the taxonomy table.
 */
function sbac_report_resource_subject_options() {
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'subject')";

  $values = query_taxonomy_term($sql);
  $sql = NULL;
  unset($sql); //memory management
  $values[1] = 'Not Yet Selected';
  ksort($values);
  return $values;
}

/**
 * Default options for the resource subject option list
 */
function sbac_report_default_resource_subject_option($form_state = array()) {
  if (isset($_SESSION['report_chosen_filters']['subject']) && $_SESSION['report_chosen_filters']['subject']) {
    $options = $_SESSION['report_chosen_filters']['subject'];
    if (in_array('All', $options)) {
      return 0;
    }
    else {
      return $options;
    }
  }
  return 0;
}

/**
 * Resource Grade Dropdown options extracted from the taxonomy table.
 */
function sbac_report_resource_grade_options() {
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'grades')";

  $values = query_taxonomy_term($sql);
  $sql = NULL;
  unset($sql); //memory management
  $values[1] = 'Not Yet Selected';
  ksort($values);
  return $values;
}

/**
 * Default options for the resource grade option list
 */
function sbac_report_default_resource_grade_option($form_state = array()) {
  if (isset($_SESSION['report_chosen_filters']['grade']) && $_SESSION['report_chosen_filters']['grade']) {
    $options = $_SESSION['report_chosen_filters']['grade'];
    if (in_array('All', $options)) {
      return 0;
    }
    else {
      return $options;
    }
  }
  return 0;
}

/**
 * Resource Attribute Dropdown options extracted from the taxonomy table.
 */
function sbac_report_resource_attribute_options() {
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'attributes')";
  $values = query_taxonomy_term($sql);
  $sql = NULL;
  unset($sql); //memory management
  $values[1] = 'Not Yet Selected';
  ksort($values);
  return $values;
}

/**
 * Default options for the resource attributes option list
 */
function sbac_report_default_resource_attribute_option($form_state = array()) {
  if (isset($_SESSION['report_chosen_filters']['attribute']) && $_SESSION['report_chosen_filters']['attribute']) {
    $options = $_SESSION['report_chosen_filters']['attribute'];
    if (in_array('All', $options)) {
      return 0;
    }
    else {
      return $options;
    }
  }
  return 0;
}

/**
 * Get the resources from the node table using five constraints: type, status, grade, attribute, and grade.
 * Returns an array of node ids to the resources.
 */
function sbac_report_get_resources($resource_filters) {
  $query = db_select('node', 'n');
  $query->condition('n.type', 'resource');
  $query->condition('n.status', 1);

  // Resource type filter
  if (!empty($resource_filters['types'])) {
    if (isset($resource_filters['types'][0])) {
      // User selected 'All', do nothing
    }
    else {
      $query->innerJoin('field_data_field_focus', 'f', 'n.nid = f.entity_id AND f.bundle = \'resource\'');
      $query->condition('f.field_focus_tid', array_keys($resource_filters['types']));
    }
  }

  // Subject filter
  if (!empty($resource_filters['subject'])) {
    if (isset($resource_filters['subject'][0])) {
      // User selected 'All', do nothing
    }
    elseif (isset($resource_filters['subject'][1])) {
      $query->innerJoin('field_data_field_subject', 's', 'n.nid = s.entity_id AND s.bundle = \'resource\'');
      $query->isNull('s.field_subject_tid');
    }
    else {
      $query->innerJoin('field_data_field_subject', 's', 'n.nid = s.entity_id AND s.bundle = \'resource\'');
      $query->condition('s.field_subject_tid', array_keys($resource_filters['subject']));
    }
  }

  // Status filter
  if (!empty($resource_filters['status'])) {
    if (isset($resource_filters['status'][0])) {
      // User selected 'All', do nothing
    }
    else {
      $query->innerJoin('workbench_moderation_node_history', 'h', 'h.nid = n.nid');
      $query->condition('h.current', 1);
      $status_condition = db_or();
      $sub_condition = 'h.state = \'being_reviewed\' AND :completed_reviews = (
            SELECT count(*)
            FROM eck_feedback f3
            WHERE f3.node_id = n.nid AND f3.completed = 1 AND f3.created > IFNULL((SELECT max(h4.stamp)
                  FROM workbench_moderation_node_history h4
                  WHERE h4.nid = n.nid AND h4.from_state = \'draft\' AND h4.state = \'needs_review\' AND h4.stamp > (
                    SELECT max(h5.stamp)
                    FROM workbench_moderation_node_history h5
                    WHERE h5.state = \'rejected\' AND h5.nid = n.nid
                  )), 0)
            )';
      // see sbac_report_resource_status_options() for the statuses
      foreach ($resource_filters['status'] as $status) {
        switch ($status) {
          case 1:
            // Draft
            $status_condition->condition('h.state', 'draft');
            break;
          case 2:
            // Submitted
            $status_condition->condition('h.state', 'needs_review');
            break;
          case 3:
            // GK
            $status_condition->where(str_replace(':completed_reviews', 0, $sub_condition));
            break;
          case 4:
            // QC1
            $status_condition->where(str_replace(':completed_reviews', 1, $sub_condition));
            break;
          case 5:
            // QC2
            $status_condition->where(str_replace(':completed_reviews', 2, $sub_condition));
            break;
          case 6:
            // QC3
            $status_condition->where(str_replace(':completed_reviews', 3, $sub_condition));
            break;
          case 7:
            // Arbitration Review
            $status_condition->condition('h.state', 'approved');
            break;
          case 8:
            // Returned
            $status_condition->condition('h.state', 'rejected');
            break;
          case 9:
            // Posted
            $status_condition->condition(db_and()->condition('h.state', 'published')->condition('n.sticky', 0));
            break;
          case 10:
            // Posted with Distinction
            $status_condition->condition(db_and()->condition('h.state', 'published')->condition('n.sticky', 1));
            break;
          case 11:
            // Removed
            $status_condition->condition('h.state', 'removed');
            break;
        }
      }
      $query->condition($status_condition);
    }
  }

  // Grade filter
  if (!empty($resource_filters['grade'])) {
    if (isset($resource_filters['grade'][0])) {
      // User selected 'All', do nothing
    }
    elseif (isset($resource_filters['grade'][1])) {
      // 'Not Yet Selected'
      $query->innerJoin('field_data_field_grades', 'g', 'n.nid = g.entity_id AND g.bundle = \'resource\'');
      $query->isNull('g.field_grades_tid');
    }
    else {
      $query->innerJoin('field_data_field_grades', 'g', 'n.nid = g.entity_id AND g.bundle = \'resource\'');
      $query->condition('g.field_grades_tid', array_keys($resource_filters['grade']));
    }
  }

  // Attributes filter
  if (!empty($resource_filters['attribute'])) {
    if (isset($resource_filters['attribute'][0])) {
      // User selected 'All', do nothing
    }
    elseif (isset($resource_filters['attribute'][1])) {
      // 'Not Yet Selected'
      $query->innerJoin('field_data_field_attributes', 'a', 'n.nid = a.entity_id AND a.bundle = \'resource\'');
      $query->isNull('a.field_attributes_tid');
    }
    else {
      $query->innerJoin('field_data_field_attributes', 'a', 'n.nid = a.entity_id AND a.bundle = \'resource\'');
      $query->condition('a.field_attributes_tid', array_keys($resource_filters['attribute']));
    }
  }

  // State filter
  if (!empty($resource_filters['state'])) {
    if (isset($resource_filters['state']['all'])) {
      // do nothing
    }
    else {
      $query->innerJoin('field_data_field_state', 's', 'n.uid = s.entity_id AND s.entity_type = \'user\'');
      if (is_array($resource_filters['state'])) {
        $query->condition('s.field_state_tid', array_keys($resource_filters['state']));
      } else {
        $query->condition('s.field_state_tid', $resource_filters['state']);
      }
    }
  }
  $query->fields('n', array('nid'));
  $query->groupBy('n.nid');
  $query->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');
  return $query->execute()->fetchCol();
}

/**
 * Helper function to add a field condition based on a filter.  Uses each filter in the list to narrow the selection
 * of the resource.  I.E the resource must have all attributes to be include in the result set.
 *
 * @param $entities
 * @param $resource_filter
 * @param $field
 */
function set_field_condition_filter_restrictive(&$entities, $resource_filter, $field) {
  if (!array_key_exists(0, $resource_filter)) {
    if (array_key_exists(1, $resource_filter)) {
      unset($resource_filter[1]); //remove niether option so that the other half of the query is correct below
    }
    $entities->condition($field, $resource_filter, 'IN');
  }
}

/**
 * Helper function to add a field condition based on a filter.   Resources that don't match the query criteria
 * are included in the query result.
 *
 * @param $entities
 * @param $resource_filter
 * @param $field
 */
function set_field_condition_niether_filter(&$entities, $resource_filter, $field) {
  if (array_key_exists(1, $resource_filter)) {
    unset($resource_filter[1]); //remove niether option so that the other half of the query is correct below
    $entities->condition($field, array_keys($resource_filter), 'NOT IN');
  }
}

/**
 * Helper function to add a field condition based on a filter.  Uses a list of filter values to define an inclusive
 * filter where a resource with any of the given attributes is included in the query result.
 *
 * @param $entities
 * @param $resource_filter
 * @param $field
 */
function set_field_condition_filter_additive(&$entities, $resource_filter, $field) {
  if (!array_key_exists(0, $resource_filter)) {
    if (array_key_exists(1, $resource_filter)) {
      unset($resource_filter[1]); //remove niether option so that the other half of the query is correct below
    }
    $entities->condition($field, 'tid', array_keys($resource_filter));
  }
}

/**
 * Remove resources from the list that don't match a criteria in the fitler_values.
 * @param $nodes
 *   The list that get's paired down.
 * @param $field
 *   Which field in the object to compare against the filter.  The objects are in the list.
 * @param $filter_values
 *   criteria for the filter.
 * @return array
 */
function filter_resource_on_field($nodes, $field, $filter_values) {
  if (array_key_exists(0, $filter_values)) {
    return $nodes;
  }
  $filtered_nodes = array();
  if (array_key_exists(1, $filter_values)) { // not yet assigned
    foreach ($nodes as $key => $node) {
      if (!$node->{$field}) {
        $filtered_nodes[$key] = $node;
      }
    }
  }

  foreach ($nodes as $key => $node) {
    if (in_array($node->{$field}, $filter_values)) {
      $filtered_nodes[$key] = $node;
    }
  }
  return $filtered_nodes;
}

/**
 * Filter out resources based on the workbench moderation history's status.
 * @param $nodes
 * @param $statuses
 * @return array
 */
function fitler_resource_status($node, $statuses) {
  $filtered_node = NULL;
  $statuses = array_map('strtolower', $statuses);
  if ($node->workbench_moderation['current']->state != 'creation') {
    $state = str_replace('_', ' ', $node->workbench_moderation['current']->state);
    if (in_array('posted_distinction', $statuses) && $state == 'published' && $node->sticky == 1) {
      $filtered_node = $node;
    }
    if (in_array($state, $statuses)) {
      $filtered_node = $node;
    }
  }
  return $filtered_node;
}

/**
 * Get the entities related to resource nodes (review, feedback, etc).
 * @param $nid
 * @return array
 */
function get_entities_for_resources($nid) {
  $query = db_select('eck_feedback', 'f');
  $query->leftJoin('users', 'u', 'u.uid = f.uid');
  $query->leftJoin('field_data_field_first_name', 'fn', 'fn.entity_id = u.uid AND fn.entity_type = \'user\'');
  $query->leftJoin('field_data_field_last_name', 'ln', 'ln.entity_id = u.uid AND fn.entity_type = \'user\'');
  $query->leftJoin('field_data_field_state', 's', 's.entity_id = u.uid AND s.entity_type = \'user\'');
  $query->leftJoin('taxonomy_term_data', 't', 't.tid = s.field_state_tid');
  $query->leftJoin('field_data_field_rec_options', 'o', 'o.entity_id = f.id');
  $query->leftJoin('field_data_field_rec_rationale', 'r', 'r.entity_id = f.id');
  $query->leftJoin('field_data_field_post_options', 'p', 'p.entity_id = f.id');
  $query->leftJoin('field_data_field_to_contributor', 'c', 'c.entity_id = f.id AND c.entity_type = \'feedback\' AND c.bundle = \'post\'');
  $query->leftJoin('field_data_field_to_reviewer_1', 'rv1', 'rv1.entity_id = f.id AND rv1.entity_type = \'feedback\' AND rv1.bundle = \'post\'');
  $query->leftJoin('field_data_field_to_reviewer_2', 'rv2', 'rv2.entity_id = f.id AND rv2.entity_type = \'feedback\' AND rv2.bundle = \'post\'');
  $query->leftJoin('field_data_field_to_reviewer_3', 'rv3', 'rv3.entity_id = f.id AND rv3.entity_type = \'feedback\' AND rv3.bundle = \'post\'');
  $query->condition('f.node_id', $nid)
    ->condition('f.status', 1)
    ->condition('f.current', 1);
  $query->fields('u', array('mail'))
    ->fields('f', array('status', 'completed', 'type'))
    ->fields('o', array('field_rec_options_value'))
    ->fields('r', array('field_rec_rationale_value'))
    ->fields('c', array('field_to_contributor_value'))
    ->fields('rv1', array('field_to_reviewer_1_value'))
    ->fields('rv2', array('field_to_reviewer_2_value'))
    ->fields('rv3', array('field_to_reviewer_3_value'))
    ->fields('t', array('name'));
  $query->addExpression('
  CASE
    WHEN f.completed = 1 THEN p.field_post_options_value
    ELSE \'\'
  END', 'field_post_options_value');
  $query->addExpression('CONCAT(fn.field_first_name_value, \' \', ln.field_last_name_value)', 'reviewer_name');
  $query->addExpression('
  CASE
    WHEN f.completed = 1 THEN FROM_UNIXTIME(f.changed, \'%c/%d/%Y\')
    ELSE \'\'
  END', 'changed');
  $query->addExpression('
  CASE
    WHEN f.met_criteria = 1 AND f.completed = 1 THEN \'Met all Criteria\'
    WHEN f.met_criteria = 0 AND f.completed = 1 THEN \'Does not Meet all Criteria\'
    ELSE \'\'
  END', 'met_criteria');
  $query->groupBy('f.uid')->groupBy('f.type')->orderBy('f.created', 'ASC');
  return $query->execute()->fetchAll();
}

/**
 * Returns the share data for the resource.
 *
 * @param $resource
 * @return mixed
 */
function get_share_data_for_resource($resource) {
  // Type
  $type = $resource->field_permanent_link_settings->value();
  if (!$type) {
    $type = 0;
  }
  $share_data['permanent_link_type'] = $type;

  // # Unique Permanent Links Copied
  $sql = "SELECT uid FROM {sbac_share_link_copy_count} WHERE nid = :nid GROUP BY uid";
  $result = db_query($sql, array(':nid' => $resource->nid->value()));
  $perm_links_copied = 0;
  foreach ($result as $row) {
    $perm_links_copied++;
  }
  $share_data['permanent_links_copied'] = $perm_links_copied;

  // Link Status
  $temp_link_status = $resource->field_temporary_public_link->value();
  if (!$temp_link_status) {
    $temp_link_status[0] = 0;
  }
  $share_data['temp_public_link_status'] = $temp_link_status[0];

  // Link Expiration Time.
  $temp_link_expiration = $resource->field_temporary_public_link_time->value();
  if (!$temp_link_expiration) {
    $temp_link_expiration = 0;
  }
  if ($temp_link_status[0] == 0) {
    $temp_link_expiration = 0;
  }
  $share_data['temp_public_link_expiration'] = $temp_link_expiration;

  // # Temp Links Generated.
  $sql = "SELECT count(nid) AS count FROM {sbac_share} WHERE nid = :nid";
  $temp_links_generated = db_query($sql, array(':nid' => $resource->nid->value()))->fetchField();
  if (!$temp_links_generated) {
    $temp_links_generated = 0;
  }
  $share_data['temp_public_links_generated'] = $temp_links_generated;

  // # Temp Links Accessed
  $sql = "SELECT access_count FROM {sbac_share} WHERE nid = :nid";
  $result = db_query($sql, array(':nid' => $resource->nid->value()));
  $temp_link_accesses = 0;
  foreach ($result as $row) {
    $temp_link_accesses += $row->access_count;
  }
  $share_data['temp_public_link_accesses'] = $temp_link_accesses;

  return $share_data;
}

/**
 * A query to get a resource's workbench moderation history (wbmh).  Gets the wbmh for multiple resources.
 * @param $resources
 * @return array
 */
function get_workbench_moderation_history($resource) {
  $query = <<<SQL
    select * from workbench_moderation_states;
SQL;
  $result = db_query($query);
  $lookup = array();
  foreach ($result as $record) {
    $lookup[$record->name] = $record->label;
  }

  $sql = <<<SQL
SELECT
  h.*,
  IF(h.state = 'removed', h.stamp, '') AS removed_date,
  IF(h.state = 'removed', CONCAT(f.field_first_name_value, ' ', l.field_last_name_value), '') AS removed_name,
  IF(h.state = 'removed', u.mail, '') AS removed_mail,
  IF(h.state = 'removed', c.field_posting_options_comment_value, '') AS removed_comment
FROM {workbench_moderation_node_history} h
  LEFT JOIN {field_data_field_first_name} f
    ON f.entity_id = h.uid AND f.bundle = 'user'
  LEFT JOIN {field_data_field_last_name} l
    ON l.entity_id = h.uid AND l.bundle = 'user'
  LEFT JOIN users u
    ON h.uid = u.uid
  LEFT JOIN field_data_field_posting_options_comment c
    ON c.revision_id = h.vid
WHERE h.current = 1 AND h.nid = :nid
SQL;
  $query = sprintf($sql);
  $sql = NULL;
  unset($sql); //memory management

  $result = db_query($query, array(':nid' => $resource->nid->value()));
  $query = NULL;
  unset($query); //memory management

  $values = array();
  foreach ($result as $record) {
    if (array_key_exists($record->state, $lookup)) {
      $record->state = $lookup[$record->state];
    }
    $values[$record->nid] = $record;
  }
  return $values;
}

/**
 *  Get the four different users involved in creating and reviewing a resource:
 *   Author/Contributor
 *   Reviewer 1
 *   Reviewer 2
 *   Reviewer 3
 *   Poster
 */
function get_users_for_resources_stats_report($resource, $feedback_reviews) {
  // authors
  $authors = array();
  $reviewers = array();

  $internal_authors = array();
  try {
    $value = $resource->field_author->value();
    if (!is_null($value)) {
      $internal_authors[$value] = $value;
    }
  } catch (EntityMetadataWrapperException $e) {
    print $e->getMessage();
  }

  if ($internal_authors) {
    $sql = "select * from users where name in (:authors)";
    $result = db_query($sql, array(':authors' => array_keys($internal_authors)));
    $query = NULL;
    unset($query);
    $sql = NULL;
    unset($sql);

    foreach ($result as $record) {
      $authors[$record->uid] = entity_metadata_wrapper('user', $record);
    }

    foreach ($feedback_reviews as $reviews) {
      foreach ($reviews as $review) {
        try {
          $uid = $review->uid->value(); /// get's the actual user.
          $value = entity_metadata_wrapper('user', $uid);
          if (is_object($uid)) {
            $reviewers[$uid->uid] = $value;
          }
          else {
            $reviewers[$uid] = $value;
          }
        } catch (EntityMetadataWrapperException $e) {
          print $e->getMessage();
        }
      }
    }
  }

  return array($authors, $reviewers);
}

/**
 * Query helper function for nodes.
 * @param $sql_template
 * @param $nodes
 *   A list of ids to be queried for.
 * @param bool $merge_necessary
 * @return array
 */
function count_with_nodes_query($sql, $node, $merge_necessary = TRUE, $increment_array = FALSE) {
  // done this way because the prepared statement didn't work passing array or comma separated string.
  // TODO: make prepared statement work here, or escape string???
  if ($merge_necessary) {
    $result = db_query($sql, array(':nid' => $node->nid->value()));
  }
  else {
    $result = db_query($sql);
  }
  $values = array();
  foreach ($result as $record) {
    if ($increment_array) {
      $values[] = $record;
    }
    else {
      if (isset($record->nid)) {
        $values[$record->nid] = $record;
      }
    }
  }
  ksort($values);
  return $values;
}

/**
 * Takes a list of node ids for resources, retrieves various things about each resource in the list.
 * @param $nodes
 * @param $data
 */
function get_counts_for_resource_stats($node, &$data) {
  # Number of Uploaded Materials
  $sql = "SELECT nid, count(id) as number_uploaded FROM eck_media where nid = :nid group by nid";
  $data['count_uploaded_materials'] = count_with_nodes_query($sql, $node, TRUE);

  # Return date
  $sql = "SELECT nid, max(stamp) as stamp FROM workbench_moderation_node_history where state = 'rejected' and
          nid = :nid";
  $data['return_date'] = count_with_nodes_query($sql, $node, TRUE);

  # Current student learning rating (average)
  $sql = "select n.nid, AVG(sl.field_student_learning_rating) as average from
            eck_review as er
            join field_data_field_student_learning as sl
            join node as n
            on er.node_id = n.nid
            and sl.entity_id = er.id group by n.nid";

  $data['student_learning_rating_average'] = count_with_nodes_query($sql, $node, FALSE);

  # Current professional development rating (average)
  $sql = "select n.nid, AVG(sl.field_pro_dev_rating) as average from
            eck_review as er
            join field_data_field_pro_dev as sl
            join node as n
            on er.node_id = n.nid
            and sl.entity_id = er.id group by n.nid";

  $data['pro_dev_rating_average'] = count_with_nodes_query($sql, $node, FALSE);

  # Current ease of use rating (average)
  $sql = "select n.nid, AVG(sl.field_ease_use_rating) as average from
            eck_review as er
            join field_data_field_ease_use as sl
            join node as n
            on er.node_id = n.nid
            and sl.entity_id = er.id group by n.nid";

  $data['ease_use_rating_average'] = count_with_nodes_query($sql, $node, FALSE);

  # number of reviews per resource
  $sql = "select node_id as nid, count(node_id) as total_reviews From eck_feedback where ((status = 1) OR (status = 0 AND archived = 1)) group by node_id";
  $data['total_reviews_per_node'] = count_with_nodes_query($sql, $node, FALSE);
}

/**
 * Gets the eck flag information for the node.
 *
 * @param $node
 * @param $data
 */
function get_counts_for_flags($node, &$data) {
  # Is Flagged
  $sql = "SELECT ef.id FROM {eck_flag} ef WHERE ef.type = 'resource' AND ef.nid = :nid AND ef.resolved = 0";
  $data['is_flagged'] = count_with_nodes_query($sql, $node, TRUE);

  # Resource Flag Reason(s)
  $sql = "SELECT ef.* FROM {eck_flag} ef WHERE ef.type = 'resource' AND ef.nid = :nid AND ef.resolved = 0";
  $data['resource_flag_reasons'] = count_with_nodes_query($sql, $node, TRUE, TRUE);

  # Has Flagged Reviews
  $sql = "SELECT ef.* FROM {eck_flag} ef WHERE ef.type = 'review_end_use' AND ef.nid = :nid AND ef.resolved = 0";
  $data['has_flagged_reviews'] = count_with_nodes_query($sql, $node, TRUE);

  # Resource Review Flag Reason(s)
  $sql = "SELECT ef.* FROM {eck_flag} ef WHERE ef.type = 'review_end_use' AND ef.nid = :nid AND ef.resolved = 0";
  $data['resource_review_flag_reasons'] = count_with_nodes_query($sql, $node, TRUE, TRUE);
}

/**
 * Gets all reviews for a given node.
 *
 * @param $node
 * @param $data
 */
function get_reviews_for_resources($node, &$data) {
  // Current Top Three "Appropriate For" Categories
  // find vocab id of our taxonomy
  $vid = db_query("SELECT vid FROM taxonomy_vocabulary WHERE machine_name = 'applied_category'")->fetchField();
  $tree = taxonomy_get_tree($vid);

  // figure out how many reviews are applicable to each term
  $query = "  SELECT        COUNT(fd.entity_id) AS count,
                                  fd.field_appropriate_for_tid AS tid
                    FROM          eck_review er
                    INNER JOIN    field_data_field_appropriate_for fd
                      ON          fd.bundle = 'end_use'
                      AND         fd.entity_id = er.id
                    WHERE         er.type = 'end_use'
                    AND           er.status = 1
                    AND           er.node_id = :node_id
                    GROUP BY      fd.field_appropriate_for_tid
                    ORDER BY      count DESC
                 ";

  $result = db_query($query, array(':node_id' => $node->nid->value()));
  $i = 0;
  $top_three_categories = array();
  foreach ($result as $row) {
    foreach ($tree as &$term_ref) {
      if ($term_ref->tid == $row->tid) {
        $term_ref->count = $row->count;
        if ($i < 3) {
          $term_ref->highlight = TRUE;
          $top_three_categories[] = $term_ref->name . ' (' . $term_ref->count . ')';
        }
        break;
      }
    }
    $i++;
  }

  if ($top_three_categories) {
    $data['review']['top_three_appropriate_for_categories'] = implode(',', $top_three_categories);
  }

  $count = 0;
  $sql = "SELECT * FROM {eck_review} WHERE node_id = :node_id";
  $result = db_query($sql, array(':node_id' => $node->nid->value()));
  foreach ($result as $eck_review) {
    $review_entity = entity_load_single('review', $eck_review->id);
    $review_entity_wrapper = entity_metadata_wrapper('review', $review_entity);
    if ($review_entity) {
      // Reviewer/Rater Name
      $account = user_load($review_entity->uid);
      $data['review'][$review_entity->id]['name'] = $account->field_first_name['und'][0]['value'] . ' ' . $account->field_last_name['und'][0]['value'];
      unset($account);

      // Review/Rating Date
      $data['review'][$review_entity->id]['date'] = date('M d, Y - g:h a', $review_entity->created);

      // Review/Rating Title
      $data['review'][$review_entity->id]['title'] = $review_entity->title;

      // Review/Rating Description
      $data['review'][$review_entity->id]['description'] = $review_entity_wrapper->field_details->value();

      // Student Learning Rating
      $data['review'][$review_entity->id]['student_learning_rating'] = sbac_report_determine_rating($review_entity_wrapper->field_student_learning->value());

      // Professional Development Rating
      $data['review'][$review_entity->id]['professional_development_rating'] = sbac_report_determine_rating($review_entity_wrapper->field_pro_dev->value());

      // Ease of Use Rating
      $data['review'][$review_entity->id]['ease_of_use_rating'] = sbac_report_determine_rating($review_entity_wrapper->field_ease_use->value());

      // "Appropriate For" Categories
      $data['review'][$review_entity->id]['appropriate_for_categories'] = $review_entity_wrapper->field_appropriate_for->value();

      $count++;
    }
  }
  return $count;
}

/**
 * Returns the human readable value.
 *
 * @param $value
 * @return int
 */
function sbac_report_determine_rating($value) {
  $var = '';
  switch ($value) {
    case 25:
      $new_value = 1;
      break;
    case 50:
      $new_value = 2;
      break;
    case 75:
      $new_value = 3;
      break;
    case 100:
      $new_value = 4;
      break;
    default:
      $new_value = 0;
      break;
  }
  return $new_value;
}

/**
 * Creates the resource report given a list of node ids.
 * @param $data : queried data for the report.  Values will be pulled from this array based on the configured columns.
 * @param $report_configuration
 * @param string $primary_data_source
 * @param string $primary_data_key
 * @return string
 */
function create_resource_stats_from_data($data, $report_configuration, $primary_data_source = 'resource_nodes', $primary_data_key = 'nid') {
  $csv_configuration = array();

  $csv_configuration['separator'] = ',';
  $csv_configuration['encloseer'] = '"';
  $csv_configuration['quote_arrays'] = TRUE;
  $csv_configuration['subseparator'] = ',';
  $csv_configuration['subquote'] = "";
  $csv_configuration['line_ending'] = "\r\n";

  ksort($data);

  // set the title
  $titles = '';
  foreach ($report_configuration as $configuration) {
    foreach ($configuration['fieldkeys'] as $fieldkey) {
      if (array_key_exists(1, $fieldkey)) {
        $titles .= $fieldkey[1] . $csv_configuration['separator'];
      }
      else {
        $titles .= '' . $csv_configuration['separator'];
      }
    }
  }
  $titles = substr($titles, 0, -1) . $csv_configuration['line_ending'];

  $csv = $titles;
  $resources = $data[$primary_data_source];
  $schema = $report_configuration['node_schema'];
  $count = count($resources);
  $ix = 0;
  foreach ($resources as $resource) {
    $row = '';
    foreach ($schema['fieldkeys'] as $fieldkey) { // (columns)
      $primarykey = $primary_data_key;
      if (array_key_exists('primarykey', $fieldkey)) {
        $primarykey = $fieldkey['primarykey'];
      }
      $value = get_field_value_using_schema($fieldkey, $data, $resource, $primarykey, $is_date);
      if (array_key_exists('field', $fieldkey)) {
        format_metadata_value_field($row, $value, $csv_configuration, $is_date, $fieldkey['field'], $resource);
      }
      else {
        format_metadata_value_field($row, $value, $csv_configuration, $is_date, NULL, $resource);
      }
    }
    if (++$ix == $count) {
      $row = substr($row, 0, -1);
    }
    // reduce length by one removing the last separator
    $csv .= $row . $csv_configuration['line_ending'];
  }
  return $csv;
}

/**
 * Calculates the total number of tags applied to a given resource node.
 * @param $fieldkey
 * @param $data
 * @param $resource
 * @return string
 */
function get_total_tags($fieldkey, $data, $resource) {
  // count of these fields:

  $count = count($resource->field_grades->value());
  $count += count($resource->field_subject->value());
  $count += count($resource->field_intended_end_user->value());
  $count += count($resource->field_intended_student->value());
  $count += count($resource->field_geographical_settings->value());
  $count += count($resource->field_smarter_balanced_keyword->value());
  $count += count($resource->field_digital_media_type->value());
  $count += count($resource->field_educational_use->value());
  $count += count($resource->field_classroom_technologies->value());
  $count += count($resource->field_alignment_tags->value());

  return "$count";
}

/**
 * Returns the value for the share data.
 *
 * @param $fieldkey
 * @param $data
 * @param $resource
 * @return null
 */
function get_share_data($fieldkey, $data, $resource) {
  $value = NULL;
  if (isset($fieldkey[0])) {
    switch ($fieldkey[0]) {
      case 'permanent_link_type':
        $value = $data['share'][$fieldkey[0]];
        ($value == 0 ? $value = 'private' : $value = 'public');
        break;
      case 'permanent_links_copied':
        $value = $data['share'][$fieldkey[0]];
        break;
      case 'temp_public_link_status':
        $value = $data['share'][$fieldkey[0]];
        ($value == 0 ? $value = 'disabled' : $value = 'enabled');
        break;
      case 'temp_public_link_expiration':
        $value = $data['share'][$fieldkey[0]];
        if ($value != 0) {
          if ($value == 100) {
            $value = '5 mins';
          }
          else {
            $value .= ' days';
          }
        }
        else {
          $value = NULL;
        }
        break;
      case 'temp_public_links_generated':
        $value = $data['share'][$fieldkey[0]];
        break;
      case 'temp_public_link_accesses';
        $value = $data['share'][$fieldkey[0]];
        break;
    }
  }
  return $value;
}

/**
 * Helper function to retrieve the Flag data.
 *
 * @param $fieldkey
 * @param $data
 * @param $resource
 * @return null|string
 */
function get_eck_flag_data($fieldkey, $data, $resource) {
  $value = NULL;
  if (isset($fieldkey[0])) {
    switch ($fieldkey[0]) {
      case 'is_flagged':
        $value = $data[$fieldkey[0]];
        ($value ? $value = 'Yes' : $value = 'No');
        break;
      case 'resource_flag_reasons':
        $flag_reasons = array();
        foreach ($data[$fieldkey[0]] as $flag) {
          $term = taxonomy_term_load($flag->flag_selected);
          if ($term) {
            $flag_reasons[] = strip_tags($term->name);
          }
        }
        if ($flag_reasons) {
          $value = implode(', ', $flag_reasons);
        }
        break;
      case 'has_flagged_reviews':
        $value = $data[$fieldkey[0]];
        ($value ? $value = 'Yes' : $value = 'No');
        break;
      case 'resource_review_flag_reasons':
        $flag_review_reasons = array();
        foreach ($data[$fieldkey[0]] as $flag) {
          $entity_flag = entity_load_single('flag', $flag->id);
          if ($entity_flag) {
            $issue_type = field_entity_value($entity_flag, 'field_issue_type');
            switch ($issue_type) {
              case 'inaccurate':
                $flag_review_reasons[] = 'Inaccurate / misleading';
                break;
              case 'unintelligible':
                $flag_review_reasons[] = 'Unintelligible';
                break;
              case 'biased':
                $flag_review_reasons[] = strip_tags('Biased and objectionable or culturally insensitive <p class="new-line">(e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)</p>');
                break;
              case 'pii':
                $flag_review_reasons[] = 'Contains personally identifiable information (PII)';
                break;
              case 'spam':
                $flag_review_reasons[] = 'Appears to be spam';
                break;
            }
          }
        }
        if ($flag_review_reasons) {
          $value = implode(', ', $flag_review_reasons);
        }
        break;
    }
  }
  return $value;
}

/**
 * Get the resource review data.
 *
 * @param $fieldkey
 * @param $data
 * @param $resource
 * @return null
 */
function get_resource_review_data($fieldkey, $data, $resource) {
  $value = NULL;

  if ($fieldkey[0] == 'top_three_appropriate_for_categories') {
    if (isset($data['review'][$fieldkey[0]])) {
      $value = $data['review'][$fieldkey[0]];
    }
  }

  return $value;
}

/**
 * Generates an absolute URL for the report generated.
 * @param  [type] $fieldkey [description]
 * @param  [type] $data     [description]
 * @param  [type] $resource [description]
 * @return string           Absolute URL for the report.
 */
function get_node_url($fieldkey, $data, $resource) {
  $path = drupal_get_path_alias('node/' . $resource->nid->value());
  return url($path, array('absolute' => TRUE));
}

function sbac_report_get_resource_status($fieldkey, $data, $resource) {
  $results = _sbac_resource_get_review_progress($resource->nid->value());
  $result = $results->fetchAssoc();
  if ($result) {
    return $result['state'];
  }
  else {
    return 'Draft';
  }
}

function sbac_report_get_qc_info($fieldkey, $data, $resource) {
  $current_qc = 1;
  foreach ($data['resource_feedback'] as $feedback) {
    if (!empty($fieldkey['type'])) {
      if ($feedback->type == $fieldkey['type']) {
        if (!empty($fieldkey['qc_number']) && !empty($fieldkey['field'])) {
          if ($fieldkey['qc_number'] == $current_qc) {
            if ('field_rec_options_value' == $fieldkey['field']) {
              // get the allowed values
              $allowed_values = list_allowed_values(field_info_field('field_rec_options'));
              return $allowed_values[$feedback->{$fieldkey['field']}];
            }
            elseif ('field_post_options_value' == $fieldkey['field']){
              // get the allowed values
              $allowed_values = list_allowed_values(field_info_field('field_post_options'));
              return $allowed_values[$feedback->{$fieldkey['field']}];
            }
            else {
              return $feedback->{$fieldkey['field']};
            }
          }
        }
        $current_qc++;
      }
    }
  }
}

function sbac_report_get_total_reviews($fieldkey, $data, $resource) {
  return db_select('eck_review', 'r')
    ->condition('r.node_id', $resource->nid->value())
    ->condition('r.status', 1)
    ->fields('r', array('id'))
    ->countQuery()
    ->execute()
    ->fetchField();
}

function sbac_report_get_total_resource_flags($fieldkey, $data, $resource) {
  return db_select('eck_flag', 'f')
    ->condition('f.type', 'resource')
    ->condition('f.target_type', 'resource')
    ->condition('f.nid', $resource->nid->value())
    ->condition('f.resolved', 0)
    ->fields('f', array('id'))
    ->countQuery()
    ->execute()
    ->fetchField();
}

function sbac_report_get_first_flag_date($fieldkey, $data, $resource) {
  $date = db_select('eck_flag', 'f')
    ->condition('f.type', 'resource')
    ->condition('f.target_type', 'resource')
    ->condition('f.nid', $resource->nid->value())
    ->condition('f.resolved', 0)
    ->fields('f', array('created'))
    ->orderBy('f.created', 'ASC')
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if ($date) {
    return date('m/d/Y', $date);
  }
}

function sbac_report_get_user_rating_flags($fieldkey, $data, $resource) {
  return db_select('eck_flag', 'f')
    ->condition('f.type', 'review_end_use')
    ->condition('f.target_type', 'review')
    ->condition('f.nid', $resource->nid->value())
    ->condition('f.resolved', 0)
    ->fields('f', array('id'))
    ->countQuery()
    ->execute()
    ->fetchField();
}

function sbac_report_get_user_rating_flag_date($fieldkey, $data, $resource) {
  $date = db_select('eck_flag', 'f')
    ->condition('f.type', 'review_end_use')
    ->condition('f.target_type', 'review')
    ->condition('f.nid', $resource->nid->value())
    ->condition('f.resolved', 0)
    ->fields('f', array('created'))
    ->orderBy('f.created', 'ASC')
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if ($date) {
    return date('m/d/Y', $date);
  }
}

function sbac_report_get_average_rating($fieldkey, $data, $resource) {
  if (!empty($fieldkey['type'])) {
    $query = db_select('eck_review', 'r');
    switch ($fieldkey['type']) {
      case 'student_learning':
        $query->leftJoin('field_data_field_student_learning', 'l', 'l.entity_id = r.id');
        $query->addExpression('AVG(l.field_student_learning_rating)', 'rating');
        break;
      case 'professional_development':
        $query->leftJoin('field_data_field_pro_dev', 'd', 'd.entity_id = r.id');
        $query->addExpression('AVG(d.field_pro_dev_rating)', 'rating');
        break;
      case 'ease_of_use':
        $query->leftJoin('field_data_field_ease_use', 'e', 'e.entity_id = r.id');
        $query->addExpression('AVG(e.field_ease_use_rating)', 'rating');
        break;
    }
    $query->condition('r.node_id', $resource->nid->value());
    $query->condition('r.status', 1);
    return $query->execute()->fetchField() * 4 / 100;
  }
}

function sbac_report_get_publish_date($fieldkey, $data, $resource) {
  if (_resource_access_node_has_state($resource->value(), array('published'))) {
    $date = db_select('workbench_moderation_node_history', 'h')
      ->condition('h.state', 'published')
      ->condition('h.nid', $resource->nid->value())
      ->fields('h', array('stamp'))
      ->orderBy('h.stamp', 'DESC')
      ->range(0, 1)
      ->execute()
      ->fetchField();
    if ($date) {
      return date('m/d/Y', $date);
    }
  }
}


/**
 * Get the total completed review count
 *
 * @param $fieldkey
 * @param $data
 * @param $resource
 * @return int
 */
function sbac_report_count_completed_reviews($fieldkey, $data, $resource) {
  $count = db_select('eck_feedback', 'f')
    ->condition('f.completed', 1)
    ->condition('f.node_id', $resource->nid->value())
    ->condition('f.status', 1)
    ->condition('f.current', 1)
    ->fields('f', array('id'))
    ->countQuery()
    ->execute()
    ->fetchField();
  if (0 == $count) {
    $count = '0';
  }
  return $count;
}

function sbac_report_get_review_cycle($fieldkey, $data, $resource) {
  return db_select('workbench_moderation_node_history', 'h')
    ->condition('h.nid', $resource->nid->value())
    ->condition('h.state', 'rejected')
    ->fields('h', array('hid'))
    ->countQuery()
    ->execute()
    ->fetchField() + 1;
}

function sbac_report_get_submission_date($fieldkey, $data, $resource) {
  $date = '';
  $resubmit = _sbac_resource_resubmit_timestamp($resource->nid->value());
  if ($resubmit) {
    $date = date('m/d/Y', $resubmit);
  }
  else {
    $submit = db_select('workbench_moderation_node_history', 'h')
      ->condition('h.from_state', 'draft')
      ->condition('h.state', 'needs_review')
      ->condition('h.nid', $resource->nid->value())
      ->fields('h', array('stamp'))->execute()->fetchField();
    if ($submit) {
      $date = date('m/d/Y', $submit);
    }
  }
  return $date;
}

function sbac_report_get_clearance_forms($fieldkey, $data, $resource) {
  $query = db_select('field_data_field_copyright_clearace_forms', 'forms');
  $query->leftJoin('file_managed', 'file', 'forms.field_copyright_clearace_forms_fid = file.fid');
  $query->condition('forms.entity_id', $resource->nid->value());
  $query->fields('file', array('filename'));
  $results = $query->orderBy('file.timestamp', 'ASC')->execute()->fetchCol();
  return implode(', ', $results);
}

function sbac_report_get_materials($fieldkey, $data, $resource) {
  $files = array();
  $materials = db_select('eck_media', 'm')->condition('m.nid', $resource->nid->value())->fields('m', array('filename', 'embed_url'))->execute()->fetchAll();
  foreach ($materials as $file) {
    if (!empty($file->embed_url)) {
      $type = '';
      if (strpos($file->embed_url, 'schooltube') !== FALSE) {
        $type = 'SchoolTube';
      }
      elseif (strpos($file->embed_url, 'teachertube') !== FALSE) {
        $type = 'TeacherTube';
      }
      elseif (strpos($file->embed_url, 'slideshare') !== FALSE) {
        $type = 'Slideshare';
      }
      elseif (strpos($file->embed_url, 'youtube') !== FALSE) {
        $type = 'YouTube';
      }
      elseif (strpos($file->embed_url, 'vimeo') !== FALSE) {
        $type = 'Vimeo';
      }
      if ($type != '') {
        $type .= ': ';
      }
      $files[] = $type . $file->embed_url;
    }
    elseif (!empty($file->filename)) {
      $files[] = $file->filename;
    }
  }
  return implode(', ', $files);
}

function sbac_report_get_contributor_email($fieldkey, $data, $resource) {
  return $resource->author->mail->value();
}

/**
 *   Here is where the Resource Detail Statistics Report is defined.  The array created here defines where to find
 * the data for each column of the report within the queried data.
 *
 * @return array
 */

function set_report_columns() {
  return
    array(
      'node_schema' => array( // sheet 1
        'fieldkeys' => array( // row schema definition of the fields.
          array('', 'URL', 'function' => 'get_node_url'),
          array('title', 'Title'),
          array('created', 'Create Date', 'fieldtype' => 'date'),
          array('', 'Status', 'function' => 'sbac_report_get_resource_status'),
          array(
            'author',
            'Contributor Name',
            'field' => array(
              array('field_first_name', 'und', 0, 'value',),
              array('field_last_name', 'und', 0, 'value',),
            ),
          ),
          array('', 'Contributor Email Address', 'function' => 'sbac_report_get_contributor_email'),
          array(
            'field_position',
            'Contributor Title',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'field_state',
            'Contributor State',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'field_district_name',
            'Contributor School District',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'field_grade_level_s_',
            'Contributor Grade(s)',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'field_subject_s_',
            'Contributor Subject(s)',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'field_special_populations',
            'Contributor Student Population(s)',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'roles',
            'Contributor Roles',
            'accessor' => 'label',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array('field_focus', 'Resource Type'),
          array('field_intended_end_user', 'Intended End User(s)'),
          array('field_attributes', 'Attribute of Formative Assessment Process'),
          array('field_connection_to_fap', 'Specific Connection to the Formative Assessment Process'),
          array('field_student_agency', 'Student Engagement in the Formative Process'),
          array('field_alt_body', 'Resource Summary'),
          array('', 'Materials', 'function' => 'sbac_report_get_materials'),
          array('field_author', 'Author'),
          array('field_publisher', 'Owner'),
          array('field_license', 'Specific License', 'accessor' => 'label'),
          array(
            'foreign',
            'License URL',
            'field' => 'description',
            'foreignkey' => array('field_license', '', 'accessor' => 'value'),
          ),
          array('', 'Copyright Clearance Forms', 'function' => 'sbac_report_get_clearance_forms'),
          array('field_subject', 'Subjects and Domains'),
          array('field_grades', 'Grade(s)'),
          array('field_alignment_term', 'Common Core State Standards', 'accessor' => 'label'),
          array('field_connection_to_ccss', 'Specific Connection to the Common Core State Standards'),
          array('field_learning_goals', 'Learning Goal'),
          array('field_success_criteria', 'Success Criteria'),
          array('field_contexts', 'Context(s) Within Which the Resource Could be Used'),
          array('field_supporting_evidence', 'Supporting Evidence'),
          array('field_principles', 'Principles Literature or Research'),
          array('field_digital_media_type', 'Media Type(s)'),
          array('field_intended_student', 'Intended Student Population(s)'),
          array('field_geographical_settings', 'Geographic Setting(s)'),
          array('field_educational_use', 'Educational Use'),
          array('field_classroom_technologies', 'Technologies Required for Use in the Classroom'),
          array('field_smarter_balanced_keyword', 'Smarter Balanced Keyword(s)'),
          array('', 'Submission Date', 'function' => 'sbac_report_get_submission_date'),
          array('', 'Review Cycle Number', 'function' => 'sbac_report_get_review_cycle'),
          array('', 'Total Reviews Completed', 'function' => 'sbac_report_count_completed_reviews'),
          array('', 'GK Reviewer Name', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'reviewer_name', 'type' => 'gate_keeper'),
          array('', 'GK Reviewer Email Address', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'mail', 'type' => 'gate_keeper'),
          array('', 'GK Reviewer State', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'name', 'type' => 'gate_keeper'),
          array('', 'GK Completion Date', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'changed', 'type' => 'gate_keeper'),
          array('', 'GK Recommendation', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'met_criteria', 'type' => 'gate_keeper'),
          array('', 'QC 1: Reviewer Name', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'reviewer_name', 'type' => 'qc'),
          array('', 'QC 1: Reviewer Email Address', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'mail', 'type' => 'qc'),
          array('', 'QC 1: Reviewer State', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'name', 'type' => 'qc'),
          array('', 'QC 1: Completion Date', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'changed', 'type' => 'qc'),
          array('', 'QC 1: Recommendation', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_rec_options_value', 'type' => 'qc'),
          array('', 'QC 1: Recommendation Rationale', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_rec_rationale_value', 'type' => 'qc'),
          array('', 'QC 2: Reviewer Name', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 2, 'field' => 'reviewer_name', 'type' => 'qc'),
          array('', 'QC 2: Reviewer Email Address', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 2, 'field' => 'mail', 'type' => 'qc'),
          array('', 'QC 2: Reviewer State', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 2, 'field' => 'name', 'type' => 'qc'),
          array('', 'QC 2: Completion Date', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 2, 'field' => 'changed', 'type' => 'qc'),
          array('', 'QC 2: Recommendation', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 2, 'field' => 'field_rec_options_value', 'type' => 'qc'),
          array('', 'QC 2: Recommendation Rationale', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 2, 'field' => 'field_rec_rationale_value', 'type' => 'qc'),
          array('', 'QC 3: Reviewer Name', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 3, 'field' => 'reviewer_name', 'type' => 'qc'),
          array('', 'QC 3: Reviewer Email Address', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 3, 'field' => 'mail', 'type' => 'qc'),
          array('', 'QC 3: Reviewer State', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 3, 'field' => 'name', 'type' => 'qc'),
          array('', 'QC 3: Completion Date', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 3, 'field' => 'changed', 'type' => 'qc'),
          array('', 'QC 3: Recommendation', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 3, 'field' => 'field_rec_options_value', 'type' => 'qc'),
          array('', 'QC 3: Recommendation Rationale', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 3, 'field' => 'field_rec_rationale_value', 'type' => 'qc'),
          array('', 'QC Poster Name', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'reviewer_name', 'type' => 'post'),
          array('', 'QC Poster Email Address', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'mail', 'type' => 'post'),
          array('', 'QC Poster State', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'name', 'type' => 'post'),
          array('', 'QC Poster Completion Date', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'changed', 'type' => 'post'),
          array('', 'QC Poster Recommendation', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_post_options_value', 'type' => 'post'),
          array('', 'QC Poster Comment to Contributor', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_to_contributor_value', 'type' => 'post'),
          array('', 'QC Poster Comment to Reviewer 1', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_to_reviewer_1_value', 'type' => 'post'),
          array('', 'QC Poster Comment to Reviewer 2', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_to_reviewer_2_value', 'type' => 'post'),
          array('', 'QC Poster Comment to Reviewer 3', 'function' => 'sbac_report_get_qc_info', 'qc_number' => 1, 'field' => 'field_to_reviewer_3_value', 'type' => 'post'),
          array('stamp', 'Return Date', 'datasource' => 'return_date', 'fieldtype' => 'date', 'not_wrapper' => TRUE),
          array('', 'Post or Post With Distinction Date', 'function' => 'sbac_report_get_publish_date'),
          array('field_total_views', 'Views'),
          array('field_unique_views', 'Unique Views'),
          array('field_asset_downloads', 'Downloads'),
          array('field_unique_downloads', 'Unique Downloads'),
          array('permanent_link_type', 'Type of Permanent Link', 'function' => 'get_share_data', 'field' => 'share'),
          array('permanent_links_copied', 'Permanent Links Copied', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_link_status', 'Temporary Public Link Status', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_link_expiration', 'Temporary Public Link Expirartion', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_links_generated', 'Temporary Public Links Generated', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_link_accesses', 'Temporary Public Link Accesses', 'function' => 'get_share_data', 'field' => 'share'),
          array('', 'Current Student Learning Rating', 'function' => 'sbac_report_get_average_rating', 'type' => 'student_learning'),
          array('', 'Current Professional Development Rating', 'function' => 'sbac_report_get_average_rating', 'type' => 'professional_development'),
          array('', 'Current Ease of Use Rating', 'function' => 'sbac_report_get_average_rating', 'type' => 'ease_of_use'),
          array('top_three_appropriate_for_categories', 'Current Top Three "Appropriate For" Categories', 'function' => 'get_resource_review_data', 'field' => 'review'),
          array('', 'Total # of Ratings', 'function' => 'sbac_report_get_total_reviews'),
          array('', 'Number of Resource Flags', 'function' => 'sbac_report_get_total_resource_flags'),
          array('', 'First Resource Flag Date', 'function' => 'sbac_report_get_first_flag_date'),
          array('resource_flag_reasons', 'Resource Flag Reason', 'function' => 'get_eck_flag_data', 'field' => 'flag'),
          array('', 'Number of Resource User Ratings Flagged', 'function' => 'sbac_report_get_user_rating_flags'),
          array('', 'Date of Resource User Rating Flag', 'function' => 'sbac_report_get_user_rating_flag_date'),
          array('resource_review_flag_reasons', 'Resource Review Flag Reasons', 'function' => 'get_eck_flag_data', 'field' => 'flag'),
        ),
      ),
    );
}

