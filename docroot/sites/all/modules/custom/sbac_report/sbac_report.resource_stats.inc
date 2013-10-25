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
    $_SESSION['sbac_report']['error_message'] = "<div> No data exists for the filters you have selected.  Please choose a new combination of filters and attempt your export again. </div>";
    $_SESSION['sbac_report']['active_tab'] = 2;
    return; // report did not contain any data.
  }
  $_SESSION['sbac_report']['error_message'] = '';
  $_SESSION['sbac_report']['active_tab'] = 2;
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
  return query_taxonomy_term($sql);
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
  return query_taxonomy_term($sql);
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
  unset($values[0]);
  $values[1] = 'Not Yet Assigned an Attribute';
  $values[2] = 'Assigned Any Attribute';
  ksort($values);
  return $values;
}
function sbac_report_default_resource_attribute_option()
{
  return 1;
}

function build_resource_stats_csv($resource_filters)
{
  $resources = get_resources($resource_filters);

  $nodes = node_load_multiple(array_keys($resources));

  $file_data = create_resource_stats_from_data($nodes);

  return $resources;
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
  function format_value_field(&$row, $field, $separator, $subseparator, $quote_arrays, $subquote)
  {
    //reset($array); $first =  key($array);
    $count = count($field['und']); $ix = 0;
    if ($count > 1 and $quote_arrays)  { $row .= $subquote; }
    foreach ($field['und'] as $array_value) {
      $value = $array_value['value'];
      $row .= $value . $subseparator;
      $ix++;
      if ($ix == $count) {
        $row = substr($row, 0, -1);
      } // reduce length by one removing the last sub-separator
    }
    if ($count > 1 and $quote_arrays)  { $row .= $subquote; }
    $row .= $separator;
  }

  $separator = ', ';
  $quote_arrays = true;
  $subseparator = ';';
  $subquote = "'";

  ksort($node);

  $fieldkeys = array();
  $foreignidkeys = array();
  $stringkeys = array();
  validate_and_fill_out_resource_stats($node, $fieldkeys, $foreignidkeys, $stringkeys);

  $titles = '';
  foreach ($fieldkeys as $fieldkey) { $titles .= $fieldkey.$separator; }
  foreach ($foreignidkeys as $foreignidkey) { $titles .= $foreignidkey.$separator; }
  foreach ($stringkeys as $stringkey) { $titles .= $stringkey.$separator; }

  $titles = substr($titles, 0, -1);
  $titles .= "\r\n";

  $csv = $titles;
  $count = count($nodes); $ix = 0;

  foreach ($nodes as $resource) {
    $nid = $resource->{'nid'};
    $row = '';
    foreach ($fieldkeys as $fieldkey) {
      format_value_field($row, $resource->{$fieldkey}, $separator, $subseparator, $quote_arrays, $subquote);
    }
    foreach ($foreignidkeys as $foreignidkey) {
      // tid is replaced by the actual value in the value field.
      format_value_field($row, $resource->{$foreignidkey}, $separator, $subseparator, $quote_arrays, $subquote);
    }
    foreach ($stringkeys as $stringkey) {
      $row .= $resource->{$stringkey} . $separator;
    }

    if (++$ix == $count) { $row = substr($row, 0, -1); } // reduce length by one removing the last separator

    $csv .= $row."\r\n";
  }
  return $csv;
}



function validate_and_fill_out_resource_stats(&$resource_nodes, &$fieldkeys, &$foreignidkeys, &$stringkeysb)
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

  array_push($fieldkeys, 'field_first_name');
  array_push($foreignidkeys, 'field_attribute'); //attributes of formative assessment process??
  array_push($strixngkeys, 'title'); //title
  array_push($stringkeys, 'field_student_agency'); //student engagement in the formative proceess
  array_push($workbench_moderation, array('current','state')); //status


  function format_value_property(&$resource_node, $fieldkey, $missing_string) {
    if (!property_exists($resource_node,$fieldkey)) {
      $resource_node->{$fieldkey} = array();
    }
    if (is_null($resource_node->{$fieldkey}['und'])) {
      $resource_node->{$fieldkey}['und'] = array();
      $resource_node->{$fieldkey}['und'][0] = array();
      $resource_node->{$fieldkey}['und'][0]['value'] = $missing_string;
    }
    $ix = 0;
    foreach ($resource_node->{$fieldkey}['und'] as $field) {
      if (is_null($resource_node->{$fieldkey}['und'][0]['value'])) {
        $resource_node->{$fieldkey}['und'][$ix]['value'] = $missing_string;
      }
      $ix++;
    }
  }
  function format_tid_property(&$resource_node, $fieldkey, $missing_string, &$used_tids) {
    // todo: look up the actual value in the foreign table, replace the tid with the actual value in the value field.
    if (!property_exists($resource_node,$fieldkey)) {
      $resource_node->{$fieldkey} = array();
    }
    if (is_null($resource_node->{$fieldkey}['und'])) {
      $resource_node->{$fieldkey}['und'] = array();
      $resource_node->{$fieldkey}['und'][0] = array();
      $resource_node->{$fieldkey}['und'][0]['tid'] = $missing_string;
      $resource_node->{$fieldkey}['und'][0]['value'] = $missing_string;
    }
    $ix = 0;
    foreach ($resource_node->{$fieldkey}['und'] as &$field) {
      if (is_null($field['tid'])) {
        $field['tid'] = $missing_string;
        $field['value'] = $missing_string;
      }
      // look up the value in the foreign table.
      if ($field['tid'] != $missing_string) {
        $used_tids[$field['tid']] = $field['tid'];
      }
      $ix++;
    }
  }
  function set_tid_property(&$resource_node, $fieldkey, &$tid_terms) {
    // todo: look up the actual value in the foreign table, replace the tid with the actual value in the value field.

    $ix = 0;
    foreach ($resource_node->{$fieldkey}['und'] as &$field) {
      // look up the value in the foreign table.
      if ($field['tid'] != 0) {
        $field['value'] = $tid_terms[$field['tid']]->name;
      }
      $ix++;
    }
  }
  // replace missing values with ' ' or 0
  $missing_string = ' ';

  $used_tids = array();
  foreach ($resource_nodes['resource_nodes'] as $resource_node) {
    $uid = $resource_node->{'uid'};
    foreach ($fieldkeys as $fieldkey) {
      format_value_property($resource_node, $fieldkey, $missing_string);
    }
    // build taxonomy index table while validating. grab all the ids then
    // load them all in one has table for quick reference.
    foreach ($foreignidkeys as $foreignidkey) {
      format_tid_property($resource_node, $foreignidkey, $missing_string, $used_tids);
    }

    foreach ($stringkeys as $stringkey) {
      if (!property_exists($resource_node,$stringkey)) {
        $resource_node->{$stringkey} = $missing_string;
      }
    }
  }
}


