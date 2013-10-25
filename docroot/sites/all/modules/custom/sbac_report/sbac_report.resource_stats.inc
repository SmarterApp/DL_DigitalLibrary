<?php
/**
 * CSV Report resource statistics form.
 */
function sbac_csv_report_resource_stats_form($form, &$form_state) {
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
    '#attributes' => array ('class' => array('chosen-widget')),
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
  );

  $form['#validate'][] = 'sbac_csv_report_resource_stats_form_validate';

  return $form;
}

/**
 * CSV Report: form validate.
 */
function sbac_csv_report_resource_stats_form_validate($form, &$form_state) {
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_STATES;

  if (false) {
    // TODO: validate csv form
  }
}
/*
 * Submit to do the export.
 */
function sbac_csv_report_resource_stats_export_form_submit($form, &$form_state)
{
  // State.
  $resource_filters = array();
  if ($form_state) {
    function set_resource_filter(&$resource_filters, $key, $form_value, $vid) {
      if (in_array('0', $form_value)) {
        $resource_filters[$key]="select tid from taxonomy_term_data where vid = $vid";
      }
      else if (in_array('1', $form_value)) { // attribute = "not yet assigned"

      }
      else if (in_array('2', $form_value)) { // attribute = "all"

      }
      else {
        $resource_filters[$key] = implode(',',$form_value);
      }
    }
    set_resource_filter($resource_filters, 'types', $form_state['values']['resource_type_dropdown'], 14);
    set_resource_filter($resource_filters, 'subject', $form_state['values']['resource_type_dropdown'], 9);
    set_resource_filter($resource_filters, 'grade', $form_state['values']['resource_type_dropdown'], 16);
    set_resource_filter($resource_filters, 'status', $form_state['values']['resource_type_dropdown'], 13);
    set_resource_filter($resource_filters, 'attribute', $form_state['values']['resource_type_dropdown'], 28);
  }
  $csv_resource_stats_result = build_resource_stats_csv($resource_filters);

  if ($csv_resource_stats_result == null) {
    $_SESSION['sbac_report']['error_message'] = SBAC_REPORT_FILTER_ERROR;
    return; // report did not contain any data.
  }
  $_SESSION['sbac_report']['error_message'] = '';
  // _cex exits and does not return.
  _cex_download($csv_resource_stats_result, 'output.csv');
  // can't get back to clear errors because fo the exit from _cex to force the
  // download of the csv file. drupal_goto('/reports');
  // _cex exits and does not return.
}

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
 * Resource Type
 */
function sbac_report_resource_type_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = 14";
  return query_taxonomy_term($sql);
}
function sbac_report_default_resource_type_option()
{
  return 0;
}
/*
 * Resource Status
 */
function sbac_report_resource_status_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = 13";
  return query_taxonomy_term($sql);
}
function sbac_report_default_resource_status_option()
{
  return 0;
}
/*
 * Resource Subject
 */
function sbac_report_resource_subject_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = 9";

  $values = query_taxonomy_term($sql);
  $values[1] = 'Not Yet Select';
  ksort($values);
  return $values;
}
function sbac_report_default_resource_subject_option()
{
  return 0;
}

/*
 * Resource Grade
 */
function sbac_report_resource_grade_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = 16";

  $values = query_taxonomy_term($sql);
  $values[1] = 'Not Yet Select';
  ksort($values);
  return $values;
}
function sbac_report_default_resource_grade_option()
{
  return 0;
}

/*
 * Resource Attribute
 */
function sbac_report_resource_attribute_options()
{
  $sql = "SELECT * FROM taxonomy_term_data where vid = 28";
  $values = query_taxonomy_term($sql);
  $values[1] = 'Not Yet Select';
  ksort($values);
  return $values;
}
function sbac_report_default_resource_attribute_option()
{
  return 0;
}

function build_resource_stats_csv($resource_filters)
{
  $resources = get_resources($resource_filters);

  $nodes = node_load_multiple(array_keys($resources));

  $file_data = create_resource_stats_from_data($nodes);

  return $file_data;
}

function get_resources($resource_filters) {

  $sql = <<<SQL
    select * from node where nid in
    (
    select distinct(ti1.nid) from
    taxonomy_index as ti1 join
    taxonomy_index as ti2 join
    taxonomy_index as ti3 join
    taxonomy_index as ti4
    on ti1.nid = ti2.nid and ti2.nid = ti3.nid and ti3.nid = ti4.nid
    where
    ti1.tid in (%s)
    and
    ti2.tid in (%s)
    and
    ti3.tid in (%s)
    and
    ti4.tid in (%s)

    order by ti1.nid
    );
SQL;
  $sql = sprintf($sql, $resource_filters['types'], $resource_filters['subject'],
    $resource_filters['grade'],$resource_filters['status']);
  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->nid] = $record;
  }
  // todo: filter on attribute: $resource_filters['attribute']
  return $values;
}

function create_resource_stats_from_data($nodes)
{
  $separator = ',';
  $encloseer = '"';
  $quote_arrays = true;
  $subseparator = ';';
  $subquote = "'";
  $line_ending = "\r\n";

  ksort($nodes);

  $fieldkeys = array();
  $foreignidkeys = array();
  $stringkeys = array();
  validate_and_fill_out_resource_stats($nodes, $fieldkeys, $foreignidkeys, $stringkeys);

  $titles = '';
  foreach ($fieldkeys as $fieldkey) { $titles .= $fieldkey[1].$separator; }
  foreach ($foreignidkeys as $foreignidkey) { $titles .= $foreignidkey[1].$separator; }
  foreach ($stringkeys as $stringkey) { $titles .= $stringkey[1].$separator; }

  $titles = substr($titles, 0, -1);
  $titles .= $line_ending;

  $csv = $titles;
  $count = count($nodes); $ix = 0;

  foreach ($nodes as $resource) {
    $nid = $resource->{'nid'};
    $row = '';
    foreach ($fieldkeys as $fieldkey) {
      format_value_field($row, $resource->{$fieldkey[0]}, $separator, $encloseer,
        $subseparator, $quote_arrays, $subquote, $fieldkey[2]=='date');
    }
    foreach ($foreignidkeys as $foreignidkey) {
      // tid is replaced by the actual value in the value field.
      format_value_field($row, $resource->{$foreignidkey[0]}, $separator, $encloseer,
        $subseparator, $quote_arrays, $subquote, $foreignidkey[2]=='date');
    }
    foreach ($stringkeys as $stringkey) {
      if ($stringkey[2]=='date') {
        $value = date('Y-m-d',$resource->{$stringkey[0]});
      }
      else {
        $value = $resource->{$stringkey[0]};
      }
      $row .= $value . $separator;
    }

    if (++$ix == $count) { $row = substr($row, 0, -1); } // reduce length by one removing the last separator

    $csv .= $row.$line_ending;
  }
  return $csv;
}



function validate_and_fill_out_resource_stats(&$resource_nodes, &$fieldkeys, &$foreignidkeys, &$stringkeys)
{
  // loop through all values and make sure 0's and '' are used as placeholders for missing values.
//  $titles =  'first-name, last-name, state, district,school, grade,subject, school-population, email,'.
//    ' is-slt, is-sne, date-created, last-access, last-login, '.
//    ' date-of-terms-of-service, version-of-terms-of-service, date-of-service-version,'.
//    ' resources-viewed, resources-reviewed-rated, resources-contributed,'.
//    ' gk-reviews-accepted-on-contributed-resources, gk-reviews-returned-on-contributed-resources,'.
//    ' contributed-resources-posted, contributed-resources-posted-with-distinction, contributed-resources-reviewed-and-returned'.
//    ' gk-reviews-completed, qc-reviews-completed, posting-reviews-completed'
//    ."\r\n";

  array_push($fieldkeys, array('field_publisher', 'Owner'));
  array_push($fieldkeys, array('field_author', 'Author'));
  array_push($fieldkeys, array('field_alt_body', 'Resource Summary'));
  array_push($fieldkeys, array('field_connection_to_ccss', 'Specific Connection to the Common Core State Standards'));
  array_push($fieldkeys, array('field_connection_to_fap', 'Specific Connection to the Formative Assessment Process'));
  array_push($fieldkeys, array('field_contexts', 'Context(s) Within Which the Resource Could be Used'));
  array_push($fieldkeys, array('field_learning_goals', 'Learning Targets'));
  array_push($fieldkeys, array('field_success_criteria', 'Success Criteria'));
  array_push($fieldkeys, array('field_supporting_evidence', 'Supporting Evidence'));
  array_push($fieldkeys, array('field_principles', 'Principles Literature or Research'));
  array_push($fieldkeys, array('field_license_information', 'License?'));
  array_push($fieldkeys, array('field_student_agency', 'Student Engagement in the Formative Process')); //
  array_push($fieldkeys, array('field_total_views', 'Views'));
  array_push($fieldkeys, array('field_unique_views', 'Unique Views'));

  array_push($foreignidkeys, array('field_attributes', 'Attribute of Formative Assessment Process')); //
  array_push($foreignidkeys, array('field_focus', 'Resource Type')); //
  array_push($foreignidkeys, array('field_grades', 'Grade(s)')); //
  array_push($foreignidkeys, array('field_intended_end_user', 'Intended End User(s)')); //
  array_push($foreignidkeys, array('field_graphical_settings', 'Geographic Setting(s)')); //
  array_push($foreignidkeys, array('field_smarter_balanced_keyword', 'Smarter Balanced Keyword(s)')); //
  array_push($foreignidkeys, array('field_digital_media_type', 'Media Type(s)')); //
  array_push($foreignidkeys, array('field_educational_use', 'Educational Use')); //
  array_push($foreignidkeys, array('field_alignment_tags', 'Common Core State Standards?')); //
  array_push($foreignidkeys, array('field_subject', 'Subjects and Domains')); //
  array_push($foreignidkeys, array('field_intended_student', 'Intended Student Population(s)')); //
  array_push($foreignidkeys, array('field_classroom_technologies', 'Technologies Required for Use in the Classroom')); //

  array_push($stringkeys, array('title', 'Title')); //title
  //todo: not showing up
  array_push($stringkeys, array('created', 'Contribution Date','date'));

  array_push($workbench_moderation, array(array('current','state'), 'Status')); //status

  // replace missing values with ' ' or 0
  $missing_string = ' ';

  $used_tids = array();
  foreach ($resource_nodes as $resource_node) {
    $nid = $resource_node->{'nid'};
    foreach ($fieldkeys as $fieldkey) {
      format_value_property($resource_node, $fieldkey[0], $missing_string);
    }
    // build taxonomy index table while validating. grab all the ids then
    // load them all in one has table for quick reference.
    foreach ($foreignidkeys as $foreignidkey) {
      format_tid_property($resource_node, $foreignidkey[0], $missing_string, $used_tids);
    }

    foreach ($stringkeys as $stringkey) {
      if (!property_exists($resource_node,$stringkey[0])) {
        $resource_node->{$stringkey[0]} = $missing_string;
      }
    }
  }
  // have all the tids, now get the term data and set the report values:
  # terms of service.
  if (count($used_tids)>0) {
    $sql = sprintf ("SELECT tid,name from taxonomy_term_data where tid in (%s)",
      implode(',',array_keys($used_tids)));
    $result = db_query($sql);
    $values = array();
    foreach ($result as $record) {
      $values[$record->tid] = $record;
    }
    $tid_terms = $values;

    foreach ($resource_nodes as $resource_node) {
      foreach ($foreignidkeys as $foreignidkey) {
        set_tid_property($resource_node, $foreignidkey[0], $tid_terms);
      }
    }
  }
}


