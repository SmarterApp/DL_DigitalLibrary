<?php

/**
 * @file
 * Forms for Domains admin screens
 */

/**
 * Settings form for domains
 */
function sbac_authorized_domains_configuration()
{
  $form['authorized_domains'] = array(
    '#title' => t('Authorized Domains'),
    '#suffix' => '<a href="/admin/sbac_authorized_domains/authorized" style="font-weight:bold;">' . t('Authorized Domains') . '</a><Br><Br>'
  );

  $form['add_domain'] = array(
    '#title' => t('Add Domain'),
    '#suffix' => '<a href="/admin/sbac_authorized_domains/adddomain" style="font-weight:bold;">' . t('Add Domain') . '</a><Br><Br>'
  );

  $form['import_domains'] = array(
    '#title' => t('Import Domains'),
    '#suffix' => '<a href="/admin/sbac_authorized_domains/importdomains" style="font-weight:bold;">' . t('Import Domains') . '</a><Br><Br>'
  );

  $form['unauthorized_domain_audit_log'] = array(
    '#title' => t('Unauthorized Domain Audit Log'),
    '#suffix' => '<a href="/admin/sbac_authorized_domains/domainlog" style="font-weight:bold;">' . t('Unauthorized Domain Audit Log') . '</a>'
  );

  return $form;
}

function sbac_authorized_domains_import_domains_form()
{
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import Domains'),
    '#collapsible' => TRUE
  );

  if (function_exists('file_upload_max_size')) {
    $file_size = t('Maximum file size: @size.', array(
      '@size' => format_size(file_upload_max_size())
    ));
  }

  $form['browser']['file_upload'] = array(
    '#type' => 'file',
    '#title' => '',
    '#size' => 40,
    '#description' => '' . '<p>' . check_plain(t('Select the CSV file to be imported.') . ' ' . $file_size) . '<br/>' . t('Allowed file types: CSV') . '</p><p>' . t('The CSV file must include 1 domain per line, in the format: domain,state,district.')
  );

  $form['browser']['scan'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

function sbac_authorized_domains_import_domains_form_validate(&$form, &$form_state) {
  $validators = array(
    'file_validate_extensions' => array( 'csv CSV' ),
  ) ;
  if ($file = file_save_upload('file_upload', $validators, 'temporary://') ) {
    // The file was saved using file_save_upload() and was added to
    // the files table as a temporary file. We'll make a copy and let
    // the garbage collector delete the original upload.
    $csv_dir = 'temporary://csvfile';
    $directory_exists = file_prepare_directory($csv_dir, FILE_CREATE_DIRECTORY);
    if ($directory_exists) {
      $destination = $csv_dir . '/' . $file->filename;
      if (file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
        $form_state['values']['file_upload'] = $destination;
      }
      else {
        form_set_error('file_upload', t('You must select a CSV file to upload'));
      }
    }
  }
  if (isset($form_state['values']['file_upload']) && $form_state['values']['file_upload']) {
    //dpm($form_state);
    if ($handle = fopen($form_state['values']['file_upload'], 'r')) {
      if (!$line = fgetcsv($handle, 4096)) {
        form_set_error('file_upload', t('This file is empty.'));
      }
      fclose($handle);
    } else {
      form_set_error('file_upload', t('Unable to read uploaded file.'));
    }
  } else {
    form_set_error('file_upload', t('File missing.'));
  }
}

function sbac_authorized_domains_import_domains_form_submit(&$form, &$form_state) {
  $batch = array(
    'title' => t('Importing CSV...'),
    'operations' => array(),
    'init_message' => t('Starting'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('An error occurred during processing'),
    'finished' => 'sbac_authorized_domains_import_finished',
  ) ;
  if (isset($form_state['values']['file_upload'])) {
    if ($handle = fopen($form_state['values']['file_upload'], 'r')) {
      while ($line = fgetcsv($handle, 4096)) {
        /**
         * we use base64_encode to ensure we don't overload the batch
         * processor by stuffing complex objects into it
         */
        $batch['operations'][] = array('_sbac_authorized_domains_import_line', array(array_map('base64_encode', $line)));
      }
      fclose($handle);
    }
  }
  batch_set($batch);
}

function sbac_authorized_domains_log_form($form, & $form_state)
{
  $form = array();

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Download Log'),
    '#validate' => array(
      'sbac_authorized_domains_log_validate'
    )
  );

  $form['color'] = array(
    '#title' => t('Color'),
    '#suffix' => '<br>' . t('Click the link above to download the Unauthorized Domain Audit Log as a CSV file.')
  );

  // sbac_authorized_domains_log_submit();
  return $form;
}

function sbac_authorized_domains_log_validate($form, &$form_state)
{

  // Using $form_state to receive the form passed values. Write the database, or other operations
  // $result = db_query('SELECT * FROM {unauthorized_domain_audit}');
  $query = db_select('unauthorized_domain_audit', 'c')->fields('c')->execute();

  $str = "Domain,AccessCount\n";
  $str = iconv('utf-8', 'gb2312', $str);

  while ($result = $query->fetchAssoc()) {
    $domain = iconv('utf-8', 'gb2312', $result['domain']);
    $accesscount = iconv('utf-8', 'gb2312', $result['accesscount']);
    $str .= $domain . "," . $accesscount . "\n"; // Use a citation comma separated
  }

  $filename = 'SBAC_Unauthorized_Domain_Audit_Log_' . date('Ymdhms') . '.csv'; // Set the file name
  export_csv($filename, $str); // export
  form_set_error('', '');
  exit();
}

function sbac_authorized_domains_json_output()
{
  // We are returning JSON, so tell the browser.
  $stateId = $_POST['stateId'];
  drupal_add_http_header('Content-Type', 'application/json');

  $result = get_state_district($stateId);

  echo drupal_json_encode(array('data' => $result));
}

function get_state_district($stateId) {
  $output = array();
  $district_vocab = taxonomy_vocabulary_machine_name_load('districts');

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $district_vocab->vid, '=')
    ->fieldCondition('field_domain_state', 'tid', $stateId, '=');
  $result = $query->execute();

  if (isset($result['taxonomy_term']) && count($result['taxonomy_term']) > 0) {
    $entity_ids = array_keys($result['taxonomy_term']);
    $entities = entity_load('taxonomy_term', $entity_ids);
    foreach ($entities as $entity) {
      $output[] = array('name' => $entity->name, 'tid' => $entity->tid);
    }
  }
  return $output;
}

function export_csv($filename, $data)
{
  header("Content-type:text/csv");
  header("Content-Disposition:attachment;filename=" . $filename);
  header('Cache-Control:must-revalidate,post-check=0,pre-check=0');
  header('Expires:0');
  header('Pragma:public');
  echo $data;
}

