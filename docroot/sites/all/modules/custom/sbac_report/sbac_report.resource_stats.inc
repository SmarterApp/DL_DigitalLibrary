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
/*
 * Resource Type
 */
function sbac_report_resource_type_options()
{
  return array(0=>"type",1=>"two",2=>"three");
}
function sbac_report_default_resource_type_option()
{
  return "two";
}

/*
 * Resource Subject
 */
function sbac_report_resource_subject_options()
{
  return array(0=>"subject",1=>"two",2=>"three");
}
function sbac_report_default_resource_subject_option()
{
  return "two";
}

/*
 * Resource Grade
 */
function sbac_report_resource_grade_options()
{
  return array(0=>"grade",1=>"two",2=>"three");
}
function sbac_report_default_resource_grade_option()
{
  return "two";
}

/*
 * Resource Attribute
 */
function sbac_report_resource_attribute_options()
{
  return array(0=>"attribute",1=>"two",2=>"three");
}
function sbac_report_default_resource_attribute_option()
{
  return "two";
}

/*
 * Resource Status
 */
function sbac_report_resource_status_options()
{
  return array(0=>"status",1=>"two",2=>"three");
}
function sbac_report_default_resource_status_option()
{
  return "two";
}