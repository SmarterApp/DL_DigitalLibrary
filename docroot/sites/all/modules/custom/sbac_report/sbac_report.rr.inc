<?php

/**
 * Script to flag the new archive
 */
function sbac_report_rr_report() {
  $resource_reviewers = array();
  $sql = "SELECT u.* FROM {users} u
          JOIN {users_roles} ur ON u.uid = ur.uid
          JOIN {eck_feedback} f ON u.uid = f.uid
          WHERE ur.rid = :rid AND u.uid > 1
          GROUP BY u.uid";
  $role = user_role_load_by_name('resource reviewer');
  $result = db_query($sql, array(':rid' => $role->rid));
  foreach ($result as $row) {
    $resource_reviewers[$row->uid] = $row;
  }

  if ($resource_reviewers) {
    batch_set(array(
        'title' => t('RR Report'),
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
  module_load_include('inc', 'sbac_report', 'sbac_report.pages');
  $context['sandbox']['finished'] = 0;
  $limit = 200;

  if (!isset($context['sandbox']['file'])) {
    $column_titles = array(
      'Reviewer Name',
      'Reviewer State',
      'Resource Title',
      'Rec.Consistency Rate',
    );
    $context['sandbox']['report_configuration'] = $column_titles;

    // Create the file and print the labels in the header row.
    $directory = "private://rr_reports/";
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'RR_Report_' . date('M_d_Y_g_i_s') . '.csv';
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
      $context['sandbox']['reviewers'] = $resource_reviewers;
      $context['sandbox']['reviewers_total'] = 315;
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
    if ($context['sandbox']['reviewers']) {
      // initialize
      $csv_column = array();
      $review_columns = array();
      // get account
      $account = array_shift($context['sandbox']['reviewers']);
      $account = user_load($account->uid);
      // get feedback
      $sql = "SELECT f.* FROM {eck_feedback} f
              WHERE f.uid = :uid AND f.type = 'qc'
              AND f.completed = 1
              AND f.status = 1";
      $eck_results = db_query($sql, array(':uid' => $account->uid));
      foreach ($eck_results as $eck_record) {
        $eck_entity = entity_load_single('feedback', $eck_record->id);
        if ($eck_entity) {
          $node = node_load($eck_record->node_id);
          if ($node) {
            $other_qc_sql = "SELECT id FROM {eck_feedback} WHERE node_id = :nid AND type = 'qc' AND status = 1 AND completed = 1 AND uid <> :uid";
            $other_qc_results = db_query($other_qc_sql, array(':nid' => $eck_record->node_id, ':uid' => $account->uid));
            $other_qcs = array();
            foreach ($other_qc_results as $qc_result) {
              $qc_entity = entity_load_single('feedback', $qc_result->id);
              if ($qc_entity) {
                $other_qcs[] = $qc_entity;
              }
            }

            $consistency_rate = NULL;
            if (count($other_qcs) == 2) {
              $consistency_rate = rec_consistency_rate($other_qcs, $eck_entity);
            }

            // think i have to loop around all and call this function. rec_consistency_rate($all, $current);
            $title = db_query("SELECT title FROM {node} WHERE nid = :nid", array(':nid' => $eck_record->node_id))->fetchField();
            if ($title && $consistency_rate) {
              // resource title
              $review_columns[] = $title;
              // consistency rate
              $review_columns[] = $consistency_rate;
            }
          }
        }
      }

      if ($review_columns) {
        // first / last name
        $csv_column[] = $account->field_first_name['und'][0]['value'] . ' ' . $account->field_last_name['und'][0]['value'];
        // state
        $state = taxonomy_term_load($account->field_state['und'][0]['tid']);
        if ($state) {
          $csv_column[] = $state->name;
        }
        else {
          $csv_column[] = 'State not found';
        }
        $csv_column = array_merge($csv_column, $review_columns);

        // write the record to csv.
        fputcsv($handle, $csv_column);
        $context['results']['count']++;
        $context['finished'] = $context['results']['count'] / $context['sandbox']['reviewers_total'];
      }
    }
  }

  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total resource reviewers.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['reviewers_total'],
  ));
}

/**
 * When the batch finishes, I move the file and show it to the user.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_rr_batch_finished($success, $results, $operations) {
  if ($success) {
    $directory = "private://rr_reports/";
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
