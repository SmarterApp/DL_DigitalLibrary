<?php
/**
 * CSV Report resource statistics form.
 */

function sbac_csv_report_resource_stats_form($form, &$form_state)
{
  $form = array();

  $form['resource_type_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose resource type:'),
    '#options' => sbac_report_resource_type_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_type_option(),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_status_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose resource status'),
    '#options' => sbac_report_resource_status_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_status_option(),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_subject_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose subject:'),
    '#options' => sbac_report_resource_subject_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_subject_option(),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_grade_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose grade:'),
    '#options' => sbac_report_resource_grade_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_grade_option(),
    '#required' => TRUE,
    '#attributes' => array('class' => array('chosen-widget')),
  );
  $form['resource_attribute_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose attribute of the formative assessment process:'),
    '#options' => sbac_report_resource_attribute_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_attribute_option(),
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
function sbac_csv_report_resource_stats_form_validate($form, &$form_state)
{
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_STATES;

  if (false) {
    // TODO: validate csv form
  }
}

/*
 * Submit to do the export for the detailed resource statistics csv report.
 */
function sbac_csv_report_resource_stats_export_form_submit($form, &$form_state)
{
  // State.
  $resource_filters = array();
  if ($form_state) {
    function set_resource_filter(&$resource_filters, $key, $form_value, $all_values)
    {
      if (in_array('0', $form_value)) { // all.
        $resource_filters[$key] = $all_values;
      } else if (in_array('1', $form_value)) { // not yet assigned
        $resource_filters[$key] = $all_values;
        unset($resource_filters[$key][0]); // remove 'All'.
      } else {
        $resource_filters[$key] = $form_value;
      }
    }

    set_resource_filter($resource_filters, 'types', $form_state['values']['resource_type_dropdown'], sbac_report_resource_type_options());
    set_resource_filter($resource_filters, 'subject', $form_state['values']['resource_subject_dropdown'], sbac_report_resource_subject_options());
    set_resource_filter($resource_filters, 'grade', $form_state['values']['resource_grade_dropdown'],  sbac_report_resource_grade_options());
    set_resource_filter($resource_filters, 'status', $form_state['values']['resource_status_dropdown'],  sbac_report_resource_status_options());
    set_resource_filter($resource_filters, 'attribute', $form_state['values']['resource_attribute_dropdown'],  sbac_report_resource_attribute_options());
  }

  $csv_resource_stats_result = build_resource_stats_csv($resource_filters);

  if ($csv_resource_stats_result == null) {
    $_SESSION['sbac_report']['error_message'] = SBAC_REPORT_FILTER_ERROR;
    $_SESSION['sbac_report']['first_time'] = 1;
    return; // report did not contain any data.
  }
  $_SESSION['sbac_report']['error_message'] = '';
  // _cex exits and does not return.
  _cex_download($csv_resource_stats_result, 'output.csv');
  // can't get back to clear errors because fo the exit from _cex to force the
  // download of the csv file. drupal_goto('/reports');
  // _cex exits and does not return.
}

/*
 * Query for a taxonomy term given an sql string, add 'All' to the query result.  Used for dropdowns on the
 * detailed resource stats csv report.
 */
function query_taxonomy_term($sql)
{
  $result = db_query($sql);
  $values = array();
  $values[0] = 'All';

  foreach ($result as $record) {
    $values[$record->tid] = $record->name;
  }
  return $values;
}

/*
 * Resource Type Dropdown options extracted from the taxonomy table.
 *
 * todo: remove hard coded number for the taxonomy term vocabulary set.
 */
function sbac_report_resource_type_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'focus')";

  return query_taxonomy_term($sql);
}

/*
 * Default options for the resource type option list
 */
function sbac_report_default_resource_type_option()
{
  return 0;
}

/*
 * Resource Status Dropdown options extracted from the taxonomy table.
 *
 * todo: remove hard coded number for the taxonomy term vocabulary set.
 */
function sbac_report_resource_status_options()
{
  // not a taxonomy term, these values come from the workbench moderation states.
  //$sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'resource_states')";
  $sql = "select name as tid, label as name from workbench_moderation_states";
  return query_taxonomy_term($sql);
}

/*
 * Default options for the resource status option list
 */
function sbac_report_default_resource_status_option()
{
  return 0;
}

/*
 * Resource Subject Dropdown options extracted from the taxonomy table.
 *
 * todo: remove hard coded number for the taxonomy term vocabulary set.
 */
function sbac_report_resource_subject_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'subject')";

  $values = query_taxonomy_term($sql);
  $values[1] = 'Not Yet Selected';
  ksort($values);
  return $values;
}

/*
 * Default options for the resource subject option list
 */
function sbac_report_default_resource_subject_option()
{
  return 0;
}

/*
 * Resource Grade Dropdown options extracted from the taxonomy table.
 *
 * todo: remove hard coded number for the taxonomy term vocabulary set.
 */
function sbac_report_resource_grade_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'grades')";

  $values = query_taxonomy_term($sql);
  $values[1] = 'Not Yet Selected';
  ksort($values);
  return $values;
}

/*
 * Default options for the resource grade option list
 */
function sbac_report_default_resource_grade_option()
{
  return 0;
}

/*
 * Resource Attribute Dropdown options extracted from the taxonomy table.
 *
 * todo: remove hard coded number for the taxonomy term vocabulary set.
 */
function sbac_report_resource_attribute_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = (SELECT vid FROM taxonomy_vocabulary where machine_name = 'attributes')";
  $values = query_taxonomy_term($sql);
  $values[1] = 'Not Yet Selected';
  ksort($values);
  return $values;
}

/*
 * Default options for the resource attributes option list
 */
function sbac_report_default_resource_attribute_option()
{
  return 0;
}

/*
 * This routine builds the detailed resource statistics csv report.  It uses other routines to get the data,
 * and format the report.  It returns the report as a string to the caller.  It takes as input the filters
 * from the front end form selector with five filter parameters: type, status, grade, attribute, and grade.
 */
function build_resource_stats_csv($resource_filters)
{
  $data = array();
  ini_set('memory_limit','512M');
  $resources = get_resources($resource_filters);
  $resource_feedback = get_entities_for_resources($resources, 'feedback');
  $workbench_moderation = get_workbench_moderation_history($resources);
  list($authors, $reviewers) = get_users_for_resources_stats_report($resources, $resource_feedback);

  ksort($resources);
  ksort($resource_feedback);
  ksort($workbench_moderation);

  $data['resource_nodes'] = $resources;
  $data['resource_feedback'] = $resource_feedback;
  $data['workbench_moderation'] = $workbench_moderation;
  $data['authors'] = $authors;
  $data['reviewers'] = $reviewers;

  get_counts_for_resource_stats($resources, $data); // already key sorted from here.

  // get the report configuration.
  $report_configuration = set_report_columns();
  $file_data = create_resource_stats_from_data($data, $report_configuration);

  return $file_data;
}

/*
 * Get the resources from the node table using five constraints: type, status, grade, attribute, and grade.
 * Returns an array of node ids to the resources.
 */
function get_resources($resource_filters)
{
  function set_field_condition_niether_filter(&$entities, $resource_filter, $field)
  {
    if ($resource_filter[1]) {
      unset($resource_filter[1]); //remove niether option so that the other half of the query is correct below
      $entities->fieldCondition($field, 'tid', array_keys($resource_filter), 'NOT IN');
    }
  }

  function set_field_condition_filter(&$entities, $resource_filter, $field)
  {
    if (!$resource_filter[0] && $resource_filter[1]) {
      unset($resource_filter[1]); //remove niether option so that the other half of the query is correct below
      $entities->fieldCondition($field, 'tid', array_keys($resource_filter));
    }
  }

  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'resource')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_focus', 'tid', array_keys($resource_filters['types']));
  // this field doesn't work:
  //   ->fieldCondition('field_resource_state', 'tid', array_keys($resource_filters['status']));
  //set_field_condition_filter($entities, $resource_filters['status'], 'field_resource_state');
  set_field_condition_filter($entities, $resource_filters['subject'], 'field_subject');
  set_field_condition_filter($entities, $resource_filters['grade'], 'field_grades');
  set_field_condition_filter($entities, $resource_filters['attribute'], 'field_attributes');
  $entities = $entities->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
    ->execute();
  if (array_key_exists('node', $entities) and $entities['node']) {
    $nids = array_keys($entities['node']);
  }
  // grade, subject, and attribute, have "not yet assgined", need to query separately for each of these.
  if ($resource_filters['subject'][1] || $resource_filters['grade'][1] || $resource_filters['attribute'][1]) {
    $entities = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'resource')
      ->propertyCondition('status', 1);
    set_field_condition_niether_filter($entities, $resource_filters['subject'], 'field_subject');
    set_field_condition_niether_filter($entities, $resource_filters['grade'], 'field_grades');
    set_field_condition_niether_filter($entities, $resource_filters['attribute'], 'field_attributes');

    $entities = $entities->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();
    if (array_key_exists('node', $entities) and $entities['node']) {
      $nids = array_merge($nids, $entities['node']);
    }
  }
  $nodes = node_load_multiple($nids);
  $nodes = fitler_resource_status($nodes, $resource_filters['status']);

  $wrappers = array();
  foreach ($nodes as $key => $value) {
    $wrappers[$key] = entity_metadata_wrapper('node', $value);
  }
  return $wrappers;
}

function fitler_resource_status($nodes, $statuses) {

  if (array_key_exists(0,$statuses)) {
    return $nodes;
  }
  $filtered_nodes = array();
  foreach ($nodes as $key => $node) {
    if (in_array($node->workbench_moderation['current']->state, $statuses)) {
      $filtered_nodes[$key] = $node;
    }
  }
  return $filtered_nodes;
}

/*
 * Get the entities related to resource nodes (review, feedback, etc).
 */
function get_entities_for_resources($resources, $entity_type)
{
  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', $entity_type)
    ->propertyCondition('node_id', array_keys($resources))
    ->execute();

  $eids = array_keys($entities[$entity_type]);
  $values = entity_load($entity_type, $eids);
  $wrappers = array();
  foreach ($values as $value) {
    $wrapper = entity_metadata_wrapper($entity_type, $value);
    $node_id = $wrapper->node_id->value();
    if ($wrapper and $node_id) {
      if (!array_key_exists($node_id, $wrappers) or
          is_null($wrappers[$node_id])) {
        $wrappers[$node_id] = array();
      }
      if ($value->type=='qc') {
        if (!array_key_exists('qc1', $wrappers[$node_id])) {
          $wrappers[$node_id]['qc1'] = $wrapper;
        }
        else if (!array_key_exists('qc2',$wrappers[$node_id])) {
          $wrappers[$node_id]['qc2'] = $wrapper;
        }
        else {
          $wrappers[$node_id]['qc3'] = $wrapper;
        }
      }
      else if ($value->type=='post') {
        $wrappers[$node_id][$value->type] = $wrapper; 
      }
      else if ($value->type=='gate_keeper') {
        $wrappers[$node_id][$value->type] = $wrapper;
      }
    }
  }
  return $wrappers;
}

function get_workbench_moderation_history($resources)
{
  $query = <<<SQL
    select * from workbench_moderation_states;
SQL;
  $result = db_query($query);
  $lookup = array();
  foreach ($result as $record) {
    $lookup[$record->name] = $record->label;
  }

  $sql = <<<SQL
    select * from workbench_moderation_node_history where nid in (%s) and current = 1
SQL;
  $query = sprintf($sql, implode(',', array_keys($resources)));
  $result = db_query($query);
  $values = array();
  foreach ($result as $record) {
    if (array_key_exists($record->state, $lookup)) {
      $record->state = $lookup[$record->state];
    }
    $values[$record->nid] = $record;
  }
  return $values;
}

/*
 *  get_users_for_resources_stats_report($resources)
 *
 *  Get the four different users involved in creating and reviewing a resource:
 *   Author/Contributor
 *   Reviewer 1
 *   Reviewer 2
 *   Reviewer 3
 *   Poster
 */
function get_users_for_resources_stats_report($resources, $feedback_reviews)
{
  // authors
  $authors = array();
  foreach ($resources as $resource) {
    try {
      $value = $resource->field_author->value();
      if (!is_null($value)) {
        $authors[$value] = $value;
      }
    } catch (EntityMetadataWrapperException $e) {
      print $e->getMessage();
    }
  }
  $sql = <<<SQL
    select * from users where name in (%s)
SQL;
  $query = sprintf($sql, "'" . implode("','", array_keys($authors)) . "'");
  $result = db_query($query);
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
        $value = $review->uid->value(); /// get's the actual user.
        $value = entity_metadata_wrapper('user', $value);
        $reviewers[$value->uid->value()] = $value;
      } catch (EntityMetadataWrapperException $e) {
        print $e->getMessage();
      }
    }
  }
  return array($authors, $reviewers);
}
/*
 * Takes a list of node ids.
 */
function get_counts_for_resource_stats($nodes, &$data)
{
  function count_with_nodes_query($sql_template, $nodes, $merge_necessary=true)//$parameters=null)
  {
    // done this way because the prepared statement didn't work passing array or comma separated string.
    // TODO: make prepared statement work here, or escape string???
    if ($merge_necessary) {
      $sql = sprintf($sql_template, $nodes);
    }
    else {
      $sql = $sql_template;
    }
    $result = db_query($sql);
    $values = array();
    foreach ($result as $record) {
      $values[$record->nid] = $record;
    }
    ksort($values);
    return $values;
  }

  $nodes = implode(',',array_keys($nodes));

  # Number of Uploaded Materials
  $sql = "SELECT nid, count(id) as number_uploaded FROM eck_media where nid in (%s) group by nid";
  $data['count_uploaded_materials'] = count_with_nodes_query($sql, $nodes);

  # Return date
  $sql = "SELECT nid, stamp FROM workbench_moderation_node_history where state = 'rejected' and
          nid not in (SELECT nid FROM workbench_moderation_node_history where state = 'approved')";
  $data['return_date'] = count_with_nodes_query($sql, $nodes, false);

  # Review cycle number
  $sql = "SELECT nid, count(nid) as review_cycle FROM sbacdev.workbench_moderation_node_history where state = 'rejected' group by nid";
  $data['review_cycle'] = count_with_nodes_query($sql, $nodes, false);

  # Current student learning rating (average)
  $sql = "select n.nid, AVG(sl.field_student_learning_rating) as average from
            eck_review as er
            join field_data_field_student_learning as sl
            join node as n
            on er.node_id = n.nid
            and sl.entity_id = er.id group by n.nid";

  $data['student_learning_rating_average'] = count_with_nodes_query($sql, $nodes, false);

  # Current professional development rating (average)
  $sql = "select n.nid, AVG(sl.field_pro_dev_rating) as average from
            eck_review as er
            join field_data_field_pro_dev as sl
            join node as n
            on er.node_id = n.nid
            and sl.entity_id = er.id group by n.nid";

  $data['pro_dev_rating_average'] = count_with_nodes_query($sql, $nodes, false);

  # Current ease of use rating (average)
  $sql = "select n.nid, AVG(sl.field_ease_use_rating) as average from
            eck_review as er
            join field_data_field_ease_use as sl
            join node as n
            on er.node_id = n.nid
            and sl.entity_id = er.id group by n.nid";

  $data['ease_use_rating_average'] = count_with_nodes_query($sql, $nodes, false);

}

/*
 * Creates the resource report given a list of node ids.
 *
 * @param $data: queried data for the report.  Values will be pulled from this array based on the configured columns.
 *
 */
function create_resource_stats_from_data($data, $report_configuration, $primary_data_source='resource_nodes', $primary_data_key='nid')
{
  $csv_configuration = array();

  $csv_configuration['separator'] = ',';
  $csv_configuration['encloseer'] = '"';
  $csv_configuration['quote_arrays'] = true;
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
    // go through the configuration array returned by set_report_columns() and create each line of the report.
    //foreach ($schema as $row_schema) {
    // go through each data source line item. (rows)
    foreach ($schema['fieldkeys'] as $fieldkey) { // (columns)
      $primarykey = $primary_data_key;
      if (array_key_exists('primarykey',$fieldkey)) {
        $primarykey = $fieldkey['primarykey'];
      }
      $value = get_field_value_using_schema($fieldkey, $data, $resource, $primarykey, $is_date);
      if (array_key_exists('field', $fieldkey)) {
        format_metadata_value_field($row, $value, $csv_configuration, $is_date, $fieldkey['field']);
      }
      else {
        format_metadata_value_field($row, $value, $csv_configuration, $is_date);
      }
    }
    if (++$ix == $count) {
      $row = substr($row, 0, -1);
    } // reduce length by one removing the last separator
    //}
    $csv .= $row . $csv_configuration['line_ending'];
  }
  return $csv;
}

function set_report_columns()
{
  function get_custom_feedback($fieldkey, $data)
  {
    return 'Hi';
  }
  function get_total_tags($fieldkey, $data)
  {
    // count of these fields:

    $count = count($data->field_grades->value());
    $count += count($data->field_subject->value());
    $count += count($data->field_intended_end_user->value());
    $count += count($data->field_intended_student->value());
    $count += count($data->field_geographical_settings->value());
    $count += count($data->field_smarter_balanced_keyword->value());
    $count += count($data->field_digital_media_type->value());
    $count += count($data->field_educational_use->value());
    $count += count($data->field_classroom_technologies->value());
    $count += count($data->field_alignment_tags->value());

    return "$count";
  }
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
          array('field_license', 'Specific License'),

          array('field_student_agency', 'Student Engagement in the Formative Process'),


          // property keys:
          array('title', 'Title'), //title
          array('created', 'Contribution Date', 'fieldtype' => 'date'),
          // foreign keys:
          array('field_attributes', 'Attribute of Formative Assessment Process'),
          array('field_focus', 'Resource Type'),

          array('number_uploaded', 'Number of Uploaded Materials', 'datasource' => 'count_uploaded_materials', 'not_wrapper' => true), // gk

          array('field_grades', 'Grade(s)'),
          array('field_subject', 'Subjects and Domains'),
          array('field_intended_end_user', 'Intended End User(s)'),
          array('field_intended_student', 'Intended Student Population(s)'),
          array('field_geographical_settings', 'Geographic Setting(s)'),
          array('field_smarter_balanced_keyword', 'Smarter Balanced Keyword(s)'),
          array('field_digital_media_type', 'Media Type(s)'),
          array('field_educational_use', 'Educational Use'),
          array('field_classroom_technologies', 'Technologies Required for Use in the Classroom'),
          array('field_alignment_tags', 'Common Core State Standards?'),
          // non-wrapper fields:
          array('state', 'Status', 'datasource' => 'workbench_moderation', 'path' => array('state' => 'class',)),
          // Gate Keeper
          array('created', 'Gate-Keeper Approval Date', 'datasource' => 'resource_feedback', 'index' => 'gate_keeper', 'fieldtype' => 'date',), // gk
          array('stamp', 'Return Date', 'datasource' => 'return_date', 'fieldtype' => 'date','not_wrapper' => true), // gk
          // QC 1, 2,3
          array('created', 'QC Review 1 Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 'qc1'),
          array('field_rec_options', 'QC Review 1 Recommendation', 'datasource' => 'resource_feedback', 'index' => 'qc1', 'accessor'=>'label'),
          array('field_rec_rationale', 'QC Review 1 Recommendation Rationale', 'datasource' => 'resource_feedback', 'index' => 'qc1'),

          array('created', 'QC Review 2 Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 'qc2'),
          array('field_rec_options', 'QC Review 2 Recommendation', 'datasource' => 'resource_feedback', 'index' => 'qc2', 'accessor'=>'label'),
          array('field_rec_rationale', 'QC Review 2 Recommendation Rationale', 'datasource' => 'resource_feedback', 'index' => 'qc2'),

          array('created', 'QC Review 3 Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 'qc3'),
          array('field_rec_options', 'QC Review 3 Recommendation', 'datasource' => 'resource_feedback', 'index' => 'qc3', 'accessor'=>'label'),
          array('field_rec_rationale', 'QC Review 3 Recommendation Rationale', 'datasource' => 'resource_feedback', 'index' => 'qc3'),

          // poster
          array('created', 'Poster Review Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 'post'),
          array('field_to_reviewer_1', 'Poster Comment to Reviewer 1', 'datasource' => 'resource_feedback', 'index' => 'post'),
          array('field_to_reviewer_2', 'Poster Comment to Reviewer 2', 'datasource' => 'resource_feedback', 'index' => 'post'),
          array('field_to_reviewer_3', 'Poster Comment to Reviewer 3', 'datasource' => 'resource_feedback', 'index' => 'post'),
          array('field_to_contributor', 'Poster Comment to Contributor', 'datasource' => 'resource_feedback', 'index' => 'post'),
          array('changed', 'Post Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 'post'),

          // users info
          array('foreign', 'Reviewer 1 Name', 'field' => array(array('field_last_name', 'und', 0, 'value',), 'separator' => ',', array('field_first_name', 'und', 0, 'value',),),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc1',  ),),
          array('foreign', 'Reviewer 1 State', 'field' => 'name',
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc1', 'wrapper'=>'user'),
            'foreigndata' => array('field_state'),
          ),
          array('foreign', 'Reviewer 2 Name', 'field' => array(array('field_last_name', 'und', 0, 'value',), 'separator' => ',', array('field_first_name', 'und', 0, 'value',),),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc2',  ),),
          array('foreign', 'Reviewer 2 State', 'field' => 'name',
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc2', 'wrapper'=>'user'),
            'foreigndata' => array('field_state'),
          ),

          array('foreign', 'Reviewer 3 Name', 'field' => array(array('field_last_name', 'und', 0, 'value',), 'separator' => ',', array('field_first_name', 'und', 0, 'value',),),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc3',  ),),
          array('foreign', 'Reviewer 3 State', 'field' => 'name',
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'qc3', 'wrapper'=>'user'),
            'foreigndata' => array('field_state'),
          ),

          array('foreign', 'Poster Name', 'field' => array(array('field_last_name', 'und', 0, 'value',), 'separator' => ',', array('field_first_name', 'und', 0, 'value',),),
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'post',  ),),
          array('foreign', 'Poster State', 'field' => 'name',
            'foreignkey' => array('uid', '', 'datasource' => 'resource_feedback', 'index' => 'post', 'wrapper'=>'user'),
            'foreigndata' => array('field_state'),
          ),
          array('author', 'Contributor Name', 'field' => array(array('field_last_name', 'und', 0, 'value',), 'separator' => ',', array('field_first_name', 'und', 0, 'value',),),),
          array('field_state', 'Contributor State',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),

          array('roles', 'Contributor Roles', 'accessor' => 'label',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),

          array('field_position', 'Contributor Title',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array('field_district_name', 'Contributor School District',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array('field_grade_level_s_', 'Contributor Grade(s)',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array('field_subject_s_', 'Contributor Subject(s)',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),
          array('field_special_populations', 'Contributor Student Population(s)',
            'foreignkey' => array('author', 'wrapper' => 'user',),
          ),

          array('review_cycle', 'Review Cycle Number', 'datasource' => 'review_cycle', 'not_wrapper' => true), // gk
          array('average', 'Current Student Learning Rating', 'datasource' => 'student_learning_rating_average', 'not_wrapper' => true), // gk
          array('average', 'Current Professional Development Rating', 'datasource' => 'pro_dev_rating_average', 'not_wrapper' => true), // gk
          array('average', 'Current Ease of Use Rating', 'datasource' => 'ease_use_rating_average', 'not_wrapper' => true), // gk


          array('field_total_views', 'Views'),
          array('field_unique_views', 'Unique Views'),
          array('', 'Total Number of Tag(s)',
            'function' => 'get_total_tags'),

        ),
      ),
    );
}

