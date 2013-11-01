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
    function set_resource_filter(&$resource_filters, $key, $form_value, $vid, $all_values)
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

    set_resource_filter($resource_filters, 'types', $form_state['values']['resource_type_dropdown'], 14, sbac_report_resource_type_options());
    set_resource_filter($resource_filters, 'subject', $form_state['values']['resource_subject_dropdown'], 9, sbac_report_resource_subject_options());
    set_resource_filter($resource_filters, 'grade', $form_state['values']['resource_grade_dropdown'], 16, sbac_report_resource_grade_options());
    set_resource_filter($resource_filters, 'status', $form_state['values']['resource_status_dropdown'], 13, sbac_report_resource_status_options());
    set_resource_filter($resource_filters, 'attribute', $form_state['values']['resource_attribute_dropdown'], 28, sbac_report_resource_attribute_options());
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
  $sql = "SELECT * FROM taxonomy_term_data where vid = 14";
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
  $sql = "SELECT * FROM taxonomy_term_data where vid = 28";
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
  $sql = "SELECT * FROM taxonomy_term_data where vid = 9";

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
  $sql = "SELECT * FROM taxonomy_term_data where vid = 16";

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
  $sql = "SELECT * FROM taxonomy_term_data where vid = 13";
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
  //->fieldCondition('field_resource_state', 'tid', array_keys($resource_filters['status']))
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
  $wrappers = array();
  foreach ($nodes as $key => $value) {
    $wrappers[$key] = entity_metadata_wrapper('node', $value);
  }
  return $wrappers;
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
  foreach ($values as $key => $value) {
    $wrapper = entity_metadata_wrapper($entity_type, $value);
    if ($wrapper and $wrapper->node_id->value()) {
      if (!array_key_exists($wrapper->node_id->value(), $wrappers) or is_null($wrappers[$wrapper->node_id->value()])) {
        $wrappers[$wrapper->node_id->value()] = array();
      }
      $wrappers[$wrapper->node_id->value()][$value->id] = $wrapper; // by node id.
    }
  }
  return $wrappers;
}

function get_workbench_moderation_history($resources)
{
  $sql = <<<SQL
    select * from workbench_moderation_node_history where nid in (%s) and current = 1
SQL;
  $query = sprintf($sql, implode(',', array_keys($resources)));
  $result = db_query($query);
  $values = array();
  foreach ($result as $record) {
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

//  foreach ($feedback_reviews as $reviews) {
//    foreach ($reviews as $review) {
//      try {
//        $value = $review->uid->value(); /// get's the actual user.
//        $value = entity_metadata_wrapper('user', $value);
//        $reviewers[$value] = $value;
//      } catch (EntityMetadataWrapperException $e) {
//        print $e->getMessage();
//      }
//    }
//  }

  return array($authors, $reviewers);
}

/*
 * Creates the resource report given a list of node ids.
 *
 * @param $data: queried data for the report.  Values will be pulled from this array based on the configured columns.
 *
 */
function create_resource_stats_from_data($data, $report_configuration)
{
  $csv_configuration = array();

  $csv_configuration['separator'] = ',';
  $csv_configuration['encloseer'] = '"';
  $csv_configuration['quote_arrays'] = true;
  $csv_configuration['subseparator'] = ';';
  $csv_configuration['subquote'] = "'";
  $csv_configuration['line_ending'] = "\r\n";

  ksort($data);

  // set the title
  $titles = '';
  foreach ($report_configuration as $configuration) {
    foreach ($configuration['fieldkeys'] as $fieldkey) {
      $titles .= $fieldkey[1] . $csv_configuration['separator'];
    }
  }
  $titles = substr($titles, 0, -1) . $csv_configuration['line_ending'];

  $csv = $titles;
  $resources = $data['resource_nodes'];
  $schema = $report_configuration['node_schema'];
  $count = count($resources);
  $ix = 0;
  foreach ($resources as $resource) {
    $row = '';
    // go through the configuration array returned by set_report_columns() and create each line of the report.
    //foreach ($schema as $row_schema) {
    // go through each data source line item. (rows)
    foreach ($schema['fieldkeys'] as $fieldkey) { // (columns)
      $value = get_field_value_using_schema($fieldkey, $data, $resource, $is_date);
      format_metadata_value_field($row, $value, $csv_configuration, $is_date);
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

  return
    array(
      'node_schema' => array( // sheet 1
        'fieldkeys' => array( // row schema definition of the fields.
//          array('field_publisher', 'Owner'),
          array('field_author', 'Author'),
//          array('field_alt_body', 'Resource Summary'),
//          array('field_connection_to_ccss', 'Specific Connection to the Common Core State Standards'),
//          array('field_connection_to_fap', 'Specific Connection to the Formative Assessment Process'),
//          array('field_contexts', 'Context(s) Within Which the Resource Could be Used'),
//          array('field_learning_goals', 'Learning Goals'),
//          array('field_success_criteria', 'Success Criteria'),
//          array('field_supporting_evidence', 'Supporting Evidence'),
//          array('field_principles', 'Principles Literature or Research'),
//          array('field_license_information', 'License?'),
//          array('field_student_agency', 'Student Engagement in the Formative Process'),
//          array('field_total_views', 'Views'),
//          array('field_unique_views', 'Unique Views'),
//          array('field_publisher', 'Owner'),
//          array('field_author', 'Author'),
//          array('field_alt_body', 'Resource Summary'),
//          array('field_connection_to_ccss', 'Specific Connection to the Common Core State Standards'),
//          array('field_connection_to_fap', 'Specific Connection to the Formative Assessment Process'),
//          array('field_contexts', 'Context(s) Within Which the Resource Could be Used'),
//          array('field_learning_goals', 'Learning Goals'),
//          array('field_success_criteria', 'Success Criteria'),
//          array('field_supporting_evidence', 'Supporting Evidence'),
//          array('field_principles', 'Principles Literature or Research'),
//          array('field_license_information', 'License?'),
//          array('field_student_agency', 'Student Engagement in the Formative Process'),
//          array('field_total_views', 'Views'),
//          array('field_unique_views', 'Unique Views'),
//          // property keys:
//          array('title', 'Title'), //title
//          array('created', 'Contribution Date', 'fieldtype' => 'date'), //todo: not showing up
//          // foreign keys:
//          array('field_attributes', 'Attribute of Formative Assessment Process'),
//          array('field_focus', 'Resource Type'),
//          array('field_grades', 'Grade(s)'),
//          array('field_intended_end_user', 'Intended End User(s)'),
//          array('field_geographical_settings', 'Geographic Setting(s)'),
//          array('field_smarter_balanced_keyword', 'Smarter Balanced Keyword(s)'),
//          array('field_digital_media_type', 'Media Type(s)'),
//          array('field_educational_use', 'Educational Use'),
//          array('field_alignment_tags', 'Common Core State Standards?'),
//          array('field_subject', 'Subjects and Domains'),
//          array('field_intended_student', 'Intended Student Population(s)'),
          array('field_classroom_technologies', 'Technologies Required for Use in the Classroom'),
          // non-wrapper fields:
          array('state', 'Status', 'datasource' => 'workbench_moderation', 'path' => array('state' => 'class',)),
          // entity relationship fields

          // Gate Keeper
          array('type', 'Feedback Type', 'datasource' => 'resource_feedback', 'index' => 0), // gk
          // todo:  array('type', 'Gate-Keeper Approval Date', 'datasource' => 'resource_feedback', 'index' => 0), // gk
          // todo: array('type', 'Return Date', 'datasource' => 'resource_feedback', 'index' => 0), // gk

          // QC 1, 2,3
          array('type', 'Feedback Type', 'datasource' => 'resource_feedback', 'index' => 1), // qc 1
          array('created', 'QC Review 1 Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 1),
          // todo: array('', 'QC Review 1 Recommendation', 'datasource' => 'resource_feedback', 'index' => 1),
          array('field_rec_rationale', 'QC Review 1 Recommendation Rationale', 'datasource' => 'resource_feedback', 'index' => 1),
          array('type', 'Feedback Type', 'datasource' => 'resource_feedback', 'index' => 2), // qc 2
          array('created', 'QC Review 2 Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 2),
          // todo: array('', 'QC Review 2 Recommendation', 'datasource' => 'resource_feedback', 'index' => 2),
          array('field_rec_rationale', 'QC Review 2 Recommendation Rationale', 'datasource' => 'resource_feedback', 'index' => 2),
          array('type', 'Feedback Type', 'datasource' => 'resource_feedback', 'index' => 3), // qc 3
          array('created', 'QC Review 3 Submission Date', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 3),
          // todo: array('', 'QC Review 3 Recommendation', 'datasource' => 'resource_feedback', 'index' => 3),
          array('field_rec_rationale', 'QC Review 3 Recommendation Rationale', 'datasource' => 'resource_feedback', 'index' => 3),

          // poster
          array('type', 'Feedback Type', 'datasource' => 'resource_feedback', 'index' => 4), // post
          array('created', 'Poster Review Submission Date (created)', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 4),
          array('changed', 'Poster Review Submission Date (changed)', 'fieldtype' => 'date', 'datasource' => 'resource_feedback', 'index' => 4),
          array('field_to_reviewer_1', 'Poster Comment to Reviewer 1', 'datasource' => 'resource_feedback', 'index' => 4),
          array('field_to_reviewer_2', 'Poster Comment to Reviewer 2', 'datasource' => 'resource_feedback', 'index' => 4),
          array('field_to_reviewer_3', 'Poster Comment to Reviewer 3', 'datasource' => 'resource_feedback', 'index' => 4),
          array('field_to_contributor', 'Poster Comment to Contributor', 'datasource' => 'resource_feedback', 'index' => 4),

          // users info
          array('uid', 'Reviewer 1', 'datasource' => 'resource_feedback', 'index' => 1),
          array('uid', 'Reviewer 2', 'datasource' => 'resource_feedback', 'index' => 2),
          array('uid', 'Reviewer 3', 'datasource' => 'resource_feedback', 'index' => 3),
          array('uid', 'Poster Id', 'datasource' => 'resource_feedback', 'index' => 4),
          array('author', 'Author Id'),

          array(
            'key' => array('uid', 'name' => 'user_id', 'datasource' => 'resource_nodes'),
            'data' => array('key' => 'user_id', 'datasource' => 'authors'),
          ),
          // test case for functional access:
          array('type', 'Feedback custom', 'datasource' => 'resource_feedback', 'function' => 'get_custom_feedback'),
        ),
      ),
    );
}

