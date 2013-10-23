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
  );
  $form['resource_status_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose resource status'),
    '#options' => sbac_report_resource_status_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_status_option(),
    '#required' => TRUE,
  );
  $form['resource_subject_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose subject:'),
    '#options' => sbac_report_resource_subject_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_subject_option(),
    '#required' => TRUE,
  );
  $form['resource_grade_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose grade:'),
    '#options' => sbac_report_resource_grade_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_grade_option(),
    '#required' => TRUE,
  );
  $form['resource_attribute_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose attribute of the formative assessment process:'),
    '#options' => sbac_report_resource_attribute_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_default_resource_attribute_option(),
    '#required' => TRUE,
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
function sbac_csv_report_resource_stats_export_form_submit()
{
  echo "done";
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
  $sql = "SELECT * FROM sbac.taxonomy_term_data where vid = 14";
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
  $sql = "SELECT * FROM sbac.taxonomy_term_data where vid = 13";
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
  $sql = "SELECT * FROM sbac.taxonomy_term_data where vid = 9";
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
  $sql = "SELECT * FROM sbac.taxonomy_term_data where vid = 16";
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
  $sql = "SELECT * FROM sbac.taxonomy_term_data where vid = 28";
  return query_taxonomy_term($sql);
}
function sbac_report_default_resource_attribute_option()
{
  return 0;
}

