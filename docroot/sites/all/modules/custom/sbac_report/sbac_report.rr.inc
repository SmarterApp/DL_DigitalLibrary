<?php

/**
 * Script to flag the new archive
 */
function sbac_report_rr_report() {
  $resource_reviewers = array();
  $sql = "SELECT u.* FROM {users} u
          JOIN {users_roles} ur ON u.uid = ur.uid
          WHERE ur.rid = :rid";
  $rid = user_role_load_by_name('resource reviewer');
  $result = db_query($sql, array(':rid' => $rid));
  foreach ($result as $row) {
    $resource_reviewers[$row->uid] = $row;
  }

  if ($resource_reviewers) {
    batch_set(array(
        'title' => t('GK Report'),
        'operations' => array(
          array('sbac_report_rr_batch_process', array($resource_reviewers)),
        ),
        'finished' => 'sbac_report_rr_batch_finished', // Finished batch callback.
      )
    );
    batch_process('reports');
  }
}

/**
 * Batch job to create csv.
 *
 * @param $resource_nodes
 */
function sbac_report_rr_batch_process($resource_reviewers, &$context) {
  $limit = 200;
  $context['sandbox']['finished'] = 0;
  ini_set('max_execution_time', 60);

  if (!isset($context['sandbox']['file'])) {
    $column_titles = array(
      'Title',
      'Return Date',
      'GK Reviewer Name',
      'GK Reviewer State',
      'GK 1 Quality Criteria Level',
    );
    $context['sandbox']['report_configuration'] = $column_titles;

    // Create the file and print the labels in the header row.
    $filename = 'RR_Report_' . date('M_d_Y_g_i_s') . '.csv';
    $file_path = file_directory_temp() . '/' . $filename;
    $handle = fopen($file_path, 'w'); // Create the file.
    fputcsv($handle, $column_titles); // Write the labels to the header row
    fclose($handle);

    // Store info in sandbox during processing.
    $context['sandbox']['file'] = $file_path;

    // Store some values in the results array for processing when finshed.
    $context['results']['filename'] = $filename;
    $context['results']['file'] = $file_path;

    if (file_exists($file_path)) {
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['reviewers'] = $resource_reviewers;
      $context['sandbox']['reviewers_total'] = count($resource_reviewers);
    }
  }

  // Accounting.
  if (!isset($context['results']['count'])) {
    $context['results']['count'] = 0;
  }

  // Open the file for writing ('a' puts pointer at end of file).
  $handle = fopen($context['sandbox']['file'], 'a');

  // Loop until we hit the batch limit.
  for ($i = 0; $i < $limit; $i++) {
    if ($context['sandbox']['resources']) {
      $account = array_shift($context['sandbox']['resources']);
      $account = user_load($account->uid);
      $csv_column[] = $account->field_first_name['und'][0]['value'] . ' ' . $account->field_last_name['und'][0]['value'];
      // gk reviewer state
      $state = taxonomy_term_load($account->field_state['und'][0]['tid']);
      if ($state) {
        $csv_column[] = $state->name;
      }
      else {
        $csv_column[] = 'State not found';
      }
      // get all feedback for this user
      // loop around them,
      $sql = "SELECT f.* FROM {eck_feedback} f WHERE f.uid = :uid AND f.type = 'qc' AND f.completed = 1 AND ((f.status = 1) OR (f.status = 0 AND f.archived = 1))";
      $eck_results = db_query($sql, array(':uid' => $account->uid));
      foreach ($eck_results as $$eck_record) {
        $other_sql = "SELECT f.* FROM {eck_feedback} f WHERE f.uid <> :uid AND f.type = 'qc' AND f.completed = 1 AND ((f.status = 1) OR (f.status = 0 AND f.archived = 1))";
        $other_eck_results = db_query($other_sql, array(':uid' => $account->uid));

      }
    }
  }

  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total resources.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['resources_total'],
  ));
}

/**
 * When the batch finishes, I move the file and show it to the user.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_gk_batch_finished($success, $results, $operations) {
  if ($success) {
    $directory = "private://rr_reports/";
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $directory .= $results['filename'];
    $directory_real_path = drupal_realpath($directory);
    copy($results['file'], $directory_real_path);
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