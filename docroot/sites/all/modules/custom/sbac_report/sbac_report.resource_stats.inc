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

  if (FALSE) {
    // TODO: validate csv form
  }
}

/**
 * Submit to do the export for the detailed resource statistics csv report.
 */
function sbac_csv_report_resource_stats_export_form_submit($form, &$form_state) {
  // State.
  $resource_filters = array();
  if ($form_state) {
    /**
     * Local function to filter out resources that don't match a criteria
     */
    function set_resource_filter(&$resource_filters, $key, $form_value, $all_values) {
      if (isset($all_values['published'])) {
        $all_values['published'] = 'Published';
      }
      if (isset($all_values['rejected'])) {
        $all_values['rejected'] = 'Rejected';
      }
      if (isset($all_values['approved'])) {
        $all_values['approved'] = 'Approved';
      }
      if (in_array('0', $form_value)) { // all.
        $resource_filters[$key] = $all_values;
      }
      else {
        if (in_array('1', $form_value)) { // not yet assigned
          $resource_filters[$key] = $all_values;
          unset($resource_filters[$key][0]); // remove 'All'.
        }
        else {
          $resource_filters[$key] = $form_value;
        }
      }
    }

    set_resource_filter($resource_filters, 'types', $form_state['values']['resource_type_dropdown'], sbac_report_resource_type_options());
    set_resource_filter($resource_filters, 'subject', $form_state['values']['resource_subject_dropdown'], sbac_report_resource_subject_options());
    set_resource_filter($resource_filters, 'grade', $form_state['values']['resource_grade_dropdown'], sbac_report_resource_grade_options());
    set_resource_filter($resource_filters, 'status', $form_state['values']['resource_status_dropdown'], sbac_report_resource_status_options());
    set_resource_filter($resource_filters, 'attribute', $form_state['values']['resource_attribute_dropdown'], sbac_report_resource_attribute_options());
  }

  $_SESSION['report_chosen_filters'] = $resource_filters;
  $resources = get_resources($resource_filters);
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
 * @param $resource_filters
 * @param $context
 */
function sbac_report_resource_statistics_batch($resources, $resource_filters, &$context) {
  $limit = 100;

  // First time through.
  if (!isset($context['sandbox']['file'])) {
    $context['sandbox']['finished'] = 0;
    $context['results']['count'] = 0;
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
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
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
  }
  
  // Open the file for writing ('a' puts pointer at end of file).
  $handle = fopen($context['sandbox']['file'], 'a');

  // Loop until we hit the batch limit.
  for ($i = 0; $i < $limit; $i++) {
    if ($context['sandbox']['resources']) {
      $nid = array_shift($context['sandbox']['resources']);
      $node = node_load($nid);
      if ($node) {
        $entity_node = entity_metadata_wrapper('node', $node);
        if ($entity_node) {
          $resource_feedback = get_entities_for_resources($entity_node, 'feedback');
          $workbench_moderation = get_workbench_moderation_history($entity_node);
          $share_data = get_share_data_for_resource($entity_node);
          $authors = NULL;
          $reviewers = NULL;
          list($authors, $reviewers) = get_users_for_resources_stats_report($entity_node, $resource_feedback);

          ksort($resource_feedback);
          ksort($workbench_moderation);

          $data = array();
          $data['resource_node'] = $entity_node;
          $data['resource_feedback'] = $resource_feedback;
          $data['workbench_moderation'] = $workbench_moderation;
          $data['authors'] = $authors;
          $data['reviewers'] = $reviewers;
          $data['share'] = $share_data;
          get_counts_for_resource_stats($entity_node, $data);
          get_counts_for_flags($entity_node, $data);

          $report_configuration = $context['sandbox']['report_configuration'];
          $schema = $report_configuration['node_schema'];
          $row = array();
          foreach ($schema['fieldkeys'] as $field_key) { // (columns)
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
          }

          fputcsv($handle, $row);
          $context['results']['count']++;
          $context['finished'] = $context['results']['count'] / $context['sandbox']['resources_total'];
        }
      }
    }
  }

  fclose($handle);

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
    $values[$record->tid] = $record->name;
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
  // not a taxonomy term, these values come from the workbench moderation states.
  //$sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'resource_states')";
  $sql = "SELECT name AS tid, label AS name FROM workbench_moderation_states WHERE name <> 'creation'";
  $options = query_taxonomy_term($sql);
  if (isset($options['published'])) {
    $options['published'] = 'Posted';
  }
  if (isset($options['rejected'])) {
    $options['rejected'] = 'Returned';
  }
  if (isset($options['approved'])) {
    $options['approved'] = 'Needs Posting';
  }
  $options['posted_distinction'] = 'Posted with Distinction';
  asort($options);
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
 * This routine builds the detailed resource statistics csv report.  It uses other routines to get the data,
 * and format the report.  It returns the report as a string to the caller.  It takes as input the filters
 * from the front end form selector with five filter parameters: type, status, grade, attribute, and grade.
 */
function build_resource_stats_csv($resource_filters) {
  $data = array();
  $resource_feedback = NULL;
  $workbench_moderation = NULL;
  $authors = NULL;
  $reviewers = NULL;

  ini_set('memory_limit', '1024M');
  ini_set('max_execution_time', 600);

  $resources = get_resources($resource_filters);
  if ($resources) {
    $resource_feedback = get_entities_for_resources($resources, 'feedback');
    $workbench_moderation = get_workbench_moderation_history($resources);
    list($authors, $reviewers) = get_users_for_resources_stats_report($resources, $resource_feedback);

    ksort($resources);
    ksort($resource_feedback);
    ksort($workbench_moderation);
  }

  $data['resource_nodes'] = $resources;
  $data['resource_feedback'] = $resource_feedback;
  $data['workbench_moderation'] = $workbench_moderation;
  $data['authors'] = $authors;
  $data['reviewers'] = $reviewers;

  if ($resources) {
    get_counts_for_resource_stats($resources, $data); // already key sorted from here.
  }
  else {
    $data['count_uploaded_materials'] = 0;
    $data['return_date'] = 0;
    $data['review_cycle'] = 0;
    $data['student_learning_rating_average'] = 0;
    $data['pro_dev_rating_average'] = 0;
    $data['ease_use_rating_average'] = 0;
    $data['total_reviews_per_node'] = 0;
  }

  $file_data = NULL;
  if ($resources) {
    // get the report configuration.
    $report_configuration = set_report_columns();
    $file_data = create_resource_stats_from_data($data, $report_configuration);
  }

  $data = NULL;
  unset($data); //memory management
  return $file_data;
}

/**
 * Get the resources from the node table using five constraints: type, status, grade, attribute, and grade.
 * Returns an array of node ids to the resources.
 */
function get_resources($resource_filters) {
  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->join('field_data_field_focus', 'f', 'n.nid = f.entity_id AND n.vid = f.revision_id');
  $query->join('field_data_field_grades', 'g', 'n.nid = g.entity_id AND n.vid = g.revision_id');
  $query->join('field_data_field_subject', 's', 'n.nid = s.entity_id AND n.vid = s.revision_id');
  $query->join('field_data_field_attributes', 'a', 'n.nid = a.entity_id AND n.vid = a.revision_id');
  if (!isset($resource_filters['status'][0])) {
    $query->join('workbench_moderation_node_history', 'w', 'n.nid = w.nid AND n.vid = w.vid');
  }
  $query->condition('n.type', 'resource');
  $query->condition('n.status', 1);
  $query->condition('f.field_focus_tid', array_keys($resource_filters['types']));
  if (!isset($resource_filters['status'][0])) {
    if (in_array('posted_distinction', $resource_filters['status'])) {
      // ensure published is brought back, since posted with distinction is a published state with sticky = 1;
      // $resource_filters['status']['published'] = 'Published';
      // remove the option that does not exist in the DB.
      // unset($resource_filters['status']['posted_distinction']);
      $query->condition(db_and()->condition('w.state', array('published'), 'IN')->condition('n.sticky', 1));
    }
    else {
      $query->condition('w.state', array_keys($resource_filters['status']), 'IN');
    }
    $query->condition('w.current', 1);
  }
  set_field_condition_filter_restrictive($query, $resource_filters['subject'], 's.field_subject_tid');
  set_field_condition_filter_restrictive($query, $resource_filters['grade'], 'g.field_grades_tid');
  set_field_condition_filter_restrictive($query, $resource_filters['attribute'], 'a.field_attributes_tid');
  $query->groupBy('n.nid');
  $query->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');
  $result = $query->execute();
  $nids = array();
  foreach ($result as $row) {
    $nids[] = $row->nid;
  }

  // grade, subject, and attribute, have "not yet assgined", need to query separately for each of these.
  if (isset($resource_filters['subject'][1]) || isset($resource_filters['grade'][1]) || isset($resource_filters['attribute'][1])) {
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'));
    $query->join('field_data_field_grades', 'g', 'n.nid = g.entity_id AND n.vid = g.revision_id');
    $query->join('field_data_field_subject', 's', 'n.nid = s.entity_id AND n.vid = s.revision_id');
    $query->join('field_data_field_attributes', 'a', 'n.nid = a.entity_id AND n.vid = a.revision_id');
    $query->condition('n.type', 'resource');
    $query->condition('n.status', 1);
    set_field_condition_niether_filter($query, $resource_filters['subject'], 's.field_subject_tid');
    set_field_condition_niether_filter($query, $resource_filters['grade'], 'g.field_grades_tid');
    set_field_condition_niether_filter($query, $resource_filters['attribute'], 'a.field_attributes_tid');
    $query->groupBy('n.nid');
    $query->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');

    $result = $query->execute();
    $separate_nids = array();
    foreach ($result as $row) {
      $separate_nids[] = $row->nid;
    }
    $nids = array_merge($nids, $separate_nids);
  }

  return $nids;
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
 * @param $resources
 * @param $entity_type
 * @return array
 */
function get_entities_for_resources($resource, $entity_type) {
  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', $entity_type)
    ->propertyCondition('node_id', $resource->nid->value())
    ->execute();

  $wrappers = array();
  if ($entities) {
    $eids = array_keys($entities[$entity_type]);
    $values = entity_load($entity_type, $eids);
    foreach ($values as $value) {
      if ($value->status === '0') {
        continue;
      }
      $wrapper = entity_metadata_wrapper($entity_type, $value);
      $node_id = $wrapper->node_id->value();
      if ($wrapper and $node_id) {
        if (!array_key_exists($node_id, $wrappers) or
          is_null($wrappers[$node_id])
        ) {
          $wrappers[$node_id] = array();
        }
        if ($value->type == 'qc') {
          if (!array_key_exists('qc1', $wrappers[$node_id])) {
            $wrappers[$node_id]['qc1'] = $wrapper;
          }
          else {
            if (!array_key_exists('qc2', $wrappers[$node_id])) {
              $wrappers[$node_id]['qc2'] = $wrapper;
            }
            else {
              $wrappers[$node_id]['qc3'] = $wrapper;
            }
          }
        }
        else {
          if ($value->type == 'post') {
            $wrappers[$node_id][$value->type] = $wrapper;
          }
          else {
            if ($value->type == 'gate_keeper') {
              $wrappers[$node_id][$value->type] = $wrapper;
            }
          }
        }
      }
    }
  }
  return $wrappers;
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
    select * from workbench_moderation_node_history where nid = :nid and current = 1
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
  try {
    $value = $resource->field_author->value();
    if (!is_null($value)) {
      $authors[$value] = $value;
    }
  } catch (EntityMetadataWrapperException $e) {
    print $e->getMessage();
  }
  $sql = <<<SQL
    select * from users where name in (:authors)
SQL;
  // $query = sprintf($sql, "'" . implode("','", array_keys($authors)) . "'");

  $result = db_query($sql, array(':authors' => array_keys($authors)));
  $query = NULL;
  unset($query); //memory management

  $sql = NULL;
  unset($sql); //memory management

  $authors = array();
  foreach ($result as $record) {
    $authors[$record->uid] = entity_metadata_wrapper('user', $record);
  }
  // posters
  // reviewers
  $reviewers = array();
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
  $sql = "SELECT nid, stamp FROM workbench_moderation_node_history where state = 'rejected' and
          nid not in (SELECT nid FROM workbench_moderation_node_history where state = 'approved')";
  $data['return_date'] = count_with_nodes_query($sql, $node, FALSE);

  # Review cycle number
  $sql = "SELECT nid, count(nid) as review_cycle FROM workbench_moderation_node_history where state = 'rejected' group by nid";
  $data['review_cycle'] = count_with_nodes_query($sql, $node, FALSE);

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
  $sql = "SELECT ef.id FROM {eck_flag} ef WHERE ef.type = 'resource' AND ef.nid = :nid";
  $data['is_flagged'] = count_with_nodes_query($sql, $node, TRUE);

  # Resource Flag Reason(s)
  $sql = "SELECT ef.* FROM {eck_flag} ef WHERE ef.type = 'resource' AND ef.nid = :nid";
  $data['resource_flag_reasons'] = count_with_nodes_query($sql, $node, TRUE, TRUE);

  # Has Flagged Reviews
  $sql = "SELECT ef.* FROM {eck_flag} ef WHERE ef.type = 'review_end_use' AND ef.nid = :nid";
  $data['has_flagged_reviews'] = count_with_nodes_query($sql, $node, TRUE);

  # Resource Review Flag Reason(s)
  $sql = "SELECT ef.* FROM {eck_flag} ef WHERE ef.type = 'review_end_use' AND ef.nid = :nid";
  $data['resource_review_flag_reasons'] = count_with_nodes_query($sql, $node, TRUE, TRUE);
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
          array('field_publisher', 'Owner'),
          array('field_author', 'Author'),
          array('field_alt_body', 'Resource Summary'),
          array('field_connection_to_ccss', 'Specific Connection to the Common Core State Standards'),
          array('field_connection_to_fap', 'Specific Connection to the Formative Assessment Process'),
          array('field_contexts', 'Context(s) Within Which the Resource Could be Used'),
          array('field_learning_goals', 'Learning Goal'),
          array('field_success_criteria', 'Success Criteria'),
          array('field_supporting_evidence', 'Supporting Evidence'),
          array('field_principles', 'Principles Literature or Research'),
          array('field_license', 'Specific License', 'accessor' => 'label'),
          array('field_license_secondary', 'Secondary License', 'accessor' => 'label'),
          array(
            'foreign',
            'License URL',
            'field' => 'description',
            'foreignkey' => array('field_license', '', 'accessor' => 'value'),
          ),
          array('field_student_agency', 'Student Engagement in the Formative Process'),
          // property keys:
          array('title', 'Title'),
          //title
          array('created', 'Contribution Date', 'fieldtype' => 'date'),
          // foreign keys:
          array('field_attributes', 'Attribute of Formative Assessment Process'),
          array('field_focus', 'Resource Type'),
          array(
            'number_uploaded',
            'Number of Uploaded Materials',
            'datasource' => 'count_uploaded_materials',
            'not_wrapper' => TRUE
          ),
          // gk

          array('field_grades', 'Grade(s)'),
          array('field_subject', 'Subjects and Domains'),
          array('field_intended_end_user', 'Intended End User(s)'),
          array('field_intended_student', 'Intended Student Population(s)'),
          array('field_geographical_settings', 'Geographic Setting(s)'),
          array('field_smarter_balanced_keyword', 'Smarter Balanced Keyword(s)'),
          array('field_digital_media_type', 'Media Type(s)'),
          array('field_educational_use', 'Educational Use'),
          array('field_classroom_technologies', 'Technologies Required for Use in the Classroom'),
          array('field_alignment_term', 'Common Core State Standards', 'accessor' => 'label'),
          // non-wrapper fields:
          array('state', 'Status', 'datasource' => 'workbench_moderation', 'path' => array('state' => 'class',),),
          // Gate Keeper
          array(
            'created',
            'Gate-Keeper Approval Date',
            'datasource' => 'resource_feedback',
            'index' => 'gate_keeper',
            'fieldtype' => 'date',
          ),
          // gk
          array('stamp', 'Return Date', 'datasource' => 'return_date', 'fieldtype' => 'date', 'not_wrapper' => TRUE),
          // gk
          // QC 1, 2,3
          array(
            'created',
            'QC Review 1 Submission Date',
            'fieldtype' => 'date',
            'datasource' => 'resource_feedback',
            'index' => 'qc1'
          ),
          array(
            'field_rec_options',
            'QC Review 1 Recommendation',
            'datasource' => 'resource_feedback',
            'index' => 'qc1',
            'accessor' => 'label'
          ),
          array(
            'field_rec_rationale',
            'QC Review 1 Recommendation Rationale',
            'datasource' => 'resource_feedback',
            'index' => 'qc1'
          ),
          array(
            'created',
            'QC Review 2 Submission Date',
            'fieldtype' => 'date',
            'datasource' => 'resource_feedback',
            'index' => 'qc2'
          ),
          array(
            'field_rec_options',
            'QC Review 2 Recommendation',
            'datasource' => 'resource_feedback',
            'index' => 'qc2',
            'accessor' => 'label'
          ),
          array(
            'field_rec_rationale',
            'QC Review 2 Recommendation Rationale',
            'datasource' => 'resource_feedback',
            'index' => 'qc2'
          ),
          array(
            'created',
            'QC Review 3 Submission Date',
            'fieldtype' => 'date',
            'datasource' => 'resource_feedback',
            'index' => 'qc3'
          ),
          array(
            'field_rec_options',
            'QC Review 3 Recommendation',
            'datasource' => 'resource_feedback',
            'index' => 'qc3',
            'accessor' => 'label'
          ),
          array(
            'field_rec_rationale',
            'QC Review 3 Recommendation Rationale',
            'datasource' => 'resource_feedback',
            'index' => 'qc3'
          ),
          // poster
          array(
            'created',
            'Poster Review Submission Date',
            'fieldtype' => 'date',
            'datasource' => 'resource_feedback',
            'index' => 'post'
          ),
          array(
            'field_to_reviewer_1',
            'Poster Comment to Reviewer 1',
            'datasource' => 'resource_feedback',
            'index' => 'post'
          ),
          array(
            'field_to_reviewer_2',
            'Poster Comment to Reviewer 2',
            'datasource' => 'resource_feedback',
            'index' => 'post'
          ),
          array(
            'field_to_reviewer_3',
            'Poster Comment to Reviewer 3',
            'datasource' => 'resource_feedback',
            'index' => 'post'
          ),
          array(
            'field_to_contributor',
            'Poster Comment to Contributor',
            'datasource' => 'resource_feedback',
            'index' => 'post'
          ),
          array('changed', 'Post Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 'post'),
          // total reivews.
          array('total_reviews', 'Total Reviews', 'datasource' => 'total_reviews_per_node', 'not_wrapper' => TRUE),
          // gk

          // users info
          array(
            'foreign',
            'Reviewer 1 Name',
            'field' => array(
              array('field_first_name', 'und', 0, 'value',),
              array('field_last_name', 'und', 0, 'value',),
            ),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc1',),
          ),
          array(
            'foreign',
            'Reviewer 1 State',
            'field' => 'name',
            'foreignkey' => array(
              'uid',
              '',
              'datasource' => 'resource_feedback',
              'index' => 'qc1',
              'wrapper' => 'user'
            ),
            'foreigndata' => array('field_state'),
          ),
          array(
            'foreign',
            'Reviewer 2 Name',
            'field' => array(
              array('field_first_name', 'und', 0, 'value',),
              array('field_last_name', 'und', 0, 'value',),
            ),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc2',),
          ),
          array(
            'foreign',
            'Reviewer 2 State',
            'field' => 'name',
            'foreignkey' => array(
              'uid',
              '',
              'datasource' => 'resource_feedback',
              'index' => 'qc2',
              'wrapper' => 'user'
            ),
            'foreigndata' => array('field_state'),
          ),
          array(
            'foreign',
            'Reviewer 3 Name',
            'field' => array(
              array('field_first_name', 'und', 0, 'value',),
              array('field_last_name', 'und', 0, 'value',),
            ),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc3',),
          ),
          array(
            'foreign',
            'Reviewer 3 State',
            'field' => 'name',
            'foreignkey' => array(
              'uid',
              '',
              'datasource' => 'resource_feedback',
              'index' => 'qc3',
              'wrapper' => 'user'
            ),
            'foreigndata' => array('field_state'),
          ),
          array(
            'foreign',
            'Poster Name',
            'field' => array(
              array('field_first_name', 'und', 0, 'value',),
              array('field_last_name', 'und', 0, 'value',),
            ),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'post',),
          ),
          array(
            'foreign',
            'Poster State',
            'field' => 'name',
            'foreignkey' => array(
              'uid',
              '',
              'datasource' => 'resource_feedback',
              'index' => 'post',
              'wrapper' => 'user'
            ),
            'foreigndata' => array('field_state'),
          ),
          array(
            'author',
            'Contributor Name',
            'field' => array(
              array('field_first_name', 'und', 0, 'value',),
              array('field_last_name', 'und', 0, 'value',),
            ),
          ),
          array(
            'field_state',
            'Contributor State',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'roles',
            'Contributor Roles',
            'accessor' => 'label',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array(
            'field_position',
            'Contributor Title',
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
          array('review_cycle', 'Review Cycle Number', 'datasource' => 'review_cycle', 'not_wrapper' => TRUE),
          // gk
          array(
            'average',
            'Current Student Learning Rating',
            'datasource' => 'student_learning_rating_average',
            'not_wrapper' => TRUE
          ),
          // gk
          array(
            'average',
            'Current Professional Development Rating',
            'datasource' => 'pro_dev_rating_average',
            'not_wrapper' => TRUE
          ),
          // gk
          array(
            'average',
            'Current Ease of Use Rating',
            'datasource' => 'ease_use_rating_average',
            'not_wrapper' => TRUE
          ),
          // gk
          array('field_total_views', 'Views'),
          array('field_unique_views', 'Unique Views'),
          array(
            '',
            'Total Number of Tag(s)',
            'function' => 'get_total_tags'
          ),
          array('permanent_link_type', 'Type of Permanent Link', 'function' => 'get_share_data', 'field' => 'share'),
          array('permanent_links_copied', 'Permanent Links Copied', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_link_status', 'Temporary Public Link Status', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_link_expiration', 'Temporary Public Link Expirartion', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_links_generated', 'Temporary Public Links Generated', 'function' => 'get_share_data', 'field' => 'share'),
          array('temp_public_link_accesses', 'Temporary Public Link Accesses', 'function' => 'get_share_data', 'field' => 'share'),
          array('is_flagged', 'Is Flagged', 'function' => 'get_eck_flag_data', 'field' => 'flag'),
          array('resource_flag_reasons', 'Resource Flag Reason', 'function' => 'get_eck_flag_data', 'field' => 'flag'),
          array('has_flagged_reviews', 'Has Flagged Reviews', 'function' => 'get_eck_flag_data', 'field' => 'flag'),
          array('resource_review_flag_reasons', 'Resource Review Flag Reasons', 'function' => 'get_eck_flag_data', 'field' => 'flag'),
        ),
      ),
    );
}

