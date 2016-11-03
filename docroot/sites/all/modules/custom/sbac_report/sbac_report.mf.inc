<?php

/**
 * Script to flag the new archive
 */
function sbac_report_mf_report() {
  // gets all eck_media that doesn't exist in file managed table
  $missing_files = array();
  $sql = "select e.* from eck_media e LEFT JOIN file_managed f ON e.fid = f.fid WHERE e.fid > 0 AND f.fid IS NULL";
  $results = db_query($sql);
  foreach ($results as $row) {
    $missing_files[$row->fid] = $row;
  }

  if ($missing_files) {
    batch_set(array(
        'title' => t('Missing Files Report'),
        'operations' => array(
          array('sbac_report_mf_batch_process', array($missing_files)),
        ),
        'finished' => 'sbac_report_mf_batch_finished', // Finished batch callback.
        'file' => drupal_get_path('module', 'sbac_report') . '/sbac_report.mf.inc',
      )
    );
    batch_process('reports');
  }
}

/**
 * Batch job to create the csv.
 *
 * @param $missing_files
 * @param $context
 */
function sbac_report_mf_batch_process($missing_files, &$context) {
  module_load_include('inc', 'sbac_report', 'sbac_report.pages');
  $context['sandbox']['finished'] = 0;
  $limit = 200;
  $gcs = sbac_media_get_google_cloud_storage();
  $bucket = variable_get('oscaddie_gcs_bucket_name');
  $folder = 'production';

  if (!isset($context['sandbox']['file'])) {
    $column_titles = array(
      'URL of Resource',
      'Contributor Name',
      'Contributor State',
      'Contributor Email Address',
      'Resource Contributed Date',
      'Material Missing',
      'ECK Record',
      'File Managed Record',
      'Exists On Google',
    );
    $context['sandbox']['report_configuration'] = $column_titles;

    // Create the file and print the labels in the header row.
    $directory = "private://mf_reports/";
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'MF_Report_' . date('M_d_Y_g_i_s') . '.csv';
    $directory .= $filename;
    $directory_real_path = drupal_realpath($directory);
    $handle = fopen($directory_real_path, 'w'); // Create the file.
    fputcsv($handle, $column_titles); // Write the labels to the header row
    fclose($handle);

    // Store info in sandbox during processing.
    $context['sandbox']['file'] = $directory_real_path;
    // Store some values in the results array for processing when finshed.
    $context['results']['filename'] = $filename;
    $context['results']['file'] = $directory_real_path;

    if (file_exists($directory_real_path)) {
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['missing_files'] = $missing_files;
      $context['sandbox']['missing_files_count'] = count($missing_files);
    }
  }

  // Open the file for writing ('a' puts pointer at end of file).
  $handle = fopen($context['sandbox']['file'], 'a');

  // Accounting.
  if (!isset($context['results']['count'])) {
    $context['results']['count'] = 0;
  }

  // Loop until we hit the batch limit.
  for ($i = 0; $i < $limit; $i++) {
    $csv_column = array();
    if ($context['sandbox']['missing_files']) {
      $media = array_shift($context['sandbox']['missing_files']);
      if (isset($media->id)) { // eck media row
        $node = node_load($media->nid);
        $account = user_load($node->uid);
        if ($account && $node) {
          global $base_url;
          $csv_column[] = $base_url . '/node/' . $media->nid;
          $csv_column[] = $account->field_first_name['und'][0]['value'] . ' ' . $account->field_last_name['und'][0]['value'];
          $state = taxonomy_term_load($account->field_state['und'][0]['tid']);
          $csv_column[] = $state->name;
          $csv_column[] = $account->mail;
          $csv_column[] = date('M d, Y - g:i a', $node->created);
          $csv_column[] = $media->filename;
          $csv_column[] = 'Yes';
          $csv_column[] = 'No';
          try {
            $target =  "resources/" . floor($media->nid/32000) . '/' . $media->nid . '/' . $media->filename;
            $response = $gcs['service']->objects->get($bucket, $folder . '/' . $target);
            if ($response) {
              $csv_column[] = 'Yes';
            }
          }
          catch (Exception $e) {
            $csv_column[] = 'No';
          }
        }
      }
    }

    if ($csv_column) {
      // write the record to csv.
      fputcsv($handle, $csv_column);
      $context['results']['count']++;
      $context['finished'] = $context['results']['count'] / $context['sandbox']['missing_files_total'];
    }
  }

  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total missing files.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['missing_files_total'],
  ));
}

/**
 * When the batch finishes, I move the file and show it to the user.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_mf_batch_finished($success, $results, $operations) {
  if ($success) {
    $directory = "private://mf_reports/";
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
    $message = '<span class="sbac-report-download">' . t('The RR Report CSV file is now ready for download. Please !download_link.', array('!download_link' => $download_link)) . '</span>';

    gc_enable();
    gc_collect_cycles();
    gc_disable();
  }
  else {
    $message = t('Finished with an error. Please try again.');
  }
  drupal_set_message($message);
}
