<?php

/**
 * Script to flag the new archive
 */
function sbac_report_gk_report() {
  $resource_nodes = array();
  $sql = "SELECT n.*
          FROM {node} n
          JOIN {workbench_moderation_node_history} w
            ON n.nid = w.nid
          WHERE n.type = 'resource'
            AND w.state <> 'creation'";
  $result = db_query($sql);
  foreach ($result as $row) {
    $resource_nodes[$row->nid] = $row;
  }

  if ($resource_nodes) {
    batch_set(array(
        'title' => t('GK Report'),
        'operations' => array(
          array('sbac_report_gk_batch_process', array($resource_nodes)),
        ),
        'finished' => 'sbac_report_gk_batch_finished', // Finished batch callback.
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
function sbac_report_gk_batch_process($resource_nodes, &$context) {
  $limit = 500;
  $context['sandbox']['finished'] = 0;

  if (!isset($context['sandbox']['file'])) {
    $column_titles = array(
      'Title',
      'Return Date',
      'GK Reviewer Name',
      'GK Reviewer State',
      'GK 1 Quality Criteria Level',
      'GK 1 Quality Criteria Rationale',
      'GK 2 Quality Criteria Level',
      'GK 2 Quality Criteria Rationale',
      'GK 3 Quality Criteria Level',
      'GK 3 Quality Criteria Rationale',
      'GK 4 Quality Criteria Level',
      'GK 4 Quality Criteria Rationale',
      'GK 5 Quality Criteria Level',
      'GK 5 Quality Criteria Rationale',
      'GK 6 Quality Criteria Level',
      'GK 6 Quality Criteria Rationale',
      'GK 7 Quality Criteria Level',
      'GK 7 Quality Criteria Rationale'
    );
    $context['sandbox']['report_configuration'] = $column_titles;

    // Create the file and print the labels in the header row.
    $directory = "private://gk_reports/";
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'GK_Report_' . date('M_d_Y_g_i_s') . '.csv';
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
      $context['sandbox']['resources'] = $resource_nodes;
      $context['sandbox']['resources_total'] = 804;
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
    if ($context['sandbox']['resources']) {
      $node = array_shift($context['sandbox']['resources']);
      //get all the states for this node, it may have been rejected at some point.
      $sql = "SELECT * FROM {workbench_moderation_node_history} WHERE nid = :nid";
      $records = db_query($sql, array(':nid' => $node->nid));
      $all_node_states = array();
      $possible = FALSE;
      $current = FALSE;
      foreach ($records as $record) {
        $all_node_states[$record->hid] = $record;
        if ($record->state == 'rejected') {
          $possible = TRUE;
        }
        if ($record->current == 1 && $record->state != 'creation') {
          $current = TRUE;
          $node->w_state = $record->state;
        }
      }

      // Its possible that this record has multiple GK feedback that interests this
      // report, check them all and if so, load up that specific feedback results
      // and spit those back to the user.
      if ($possible) {
        $all_node_states = array_reverse($all_node_states);
        $count = 0;
        foreach ($all_node_states as $node_state) {
          if ($node_state->state == 'rejected') {
            // load all eck_feedback for this node and this user id.
            // the user could have more then one review, how to determine your setting the right one?????
            // no relationship between the two.
            $stamp = $node_state->stamp;
            $start = $stamp - 10;
            $end = $stamp + 10;
            $query = "SELECT * FROM {eck_feedback} WHERE node_id = :nid AND uid = :uid AND type = :type AND completed = 1 AND changed BETWEEN :start AND :end LIMIT 1";
            $eck_row = db_query($query, array(':nid' => $node_state->nid, ':uid' => $node_state->uid, ':type' => 'gate_keeper', ':start' => $start, ':end' => $end))->fetchObject();
            if ($eck_row) {
              $eck_feedback_entity = entity_load_single('feedback', $eck_row->id);
              if ($eck_feedback_entity) {
                $count++;
                $csv_column = array();
                // title
                $title = $node->title;
                if ($count > 1) {
                  $title .= " ***** " . $count;
                }
                $csv_column[] = $title;
                // returned
                if ($node_state->state == 'rejected') {
                  $csv_column[] = date('M d, Y - g:i', $eck_feedback_entity->changed);
                }
                else {
                  $csv_column[] = '';
                }
                // gk reviewer name
                $gk_reviewer = user_load($eck_feedback_entity->uid);
                $csv_column[] = $gk_reviewer->field_first_name['und'][0]['value'] . ' ' . $gk_reviewer->field_last_name['und'][0]['value'];
                // gk reviewer state
                $state = taxonomy_term_load($gk_reviewer->field_state['und'][0]['tid']);
                if ($state) {
                  $csv_column[] = $state->name;
                }
                else {
                  $csv_column[] = 'State not found';
                }
                foreach (field_entity_value($eck_feedback_entity, 'field_quality_set') as $question) {
                  $level = field_entity_value($question, 'field_meets_criterion');
                  $level = $level ? t('Yes') : t('No');
                  $comment = field_entity_value($question, 'field_comments');
                  $csv_column[] = $level;
                  $csv_column[] = $comment;
                }

                fputcsv($handle, $csv_column);
                $context['results']['count']++;
                $context['finished'] = $context['results']['count'] / $context['sandbox']['resources_total'];
              }
            }
          }
        }
      }
      else if ($current) {
        $eck_query = "SELECT f.* FROM {eck_feedback} f WHERE f.node_id = :nid AND f.type = :type AND f.completed = 1 AND f.met_criteria = 1";
        $eck_results = db_query($eck_query, array(':nid' => $node->nid, ':type' => 'gate_keeper'));
        if ($eck_results) {
          foreach ($eck_results as $eck_row) {
            $eck_feedback_entity = entity_load_single('feedback', $eck_row->id);
            if ($eck_feedback_entity) {
              $csv_column = array();
              // title
              $csv_column[] = $node->title;
              // returned
              if ($node->w_state == 'rejected') {
                $csv_column[] = date('M d, Y - g:i', $eck_feedback_entity->changed);
              }
              else {
                $csv_column[] = '';
              }
              // gk reviewer name
              $gk_reviewer = user_load($eck_feedback_entity->uid);
              $csv_column[] = $gk_reviewer->field_first_name['und'][0]['value'] . ' ' . $gk_reviewer->field_last_name['und'][0]['value'];
              // gk reviewer state
              $state = taxonomy_term_load($gk_reviewer->field_state['und'][0]['tid']);
              if ($state) {
                $csv_column[] = $state->name;
              }
              else {
                $csv_column[] = 'State not found';
              }
              foreach (field_entity_value($eck_feedback_entity, 'field_quality_set') as $question) {
                $level = field_entity_value($question, 'field_meets_criterion');
                $level = $level ? t('Yes') : t('No');
                $comment = field_entity_value($question, 'field_comments');
                $csv_column[] = $level;
                $csv_column[] = $comment;
              }
              fputcsv($handle, $csv_column);
              $context['results']['count']++;
              $context['finished'] = $context['results']['count'] / $context['sandbox']['resources_total'];
            }
          }
        }
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
    $directory = "private://gk_reports/";
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
    $message = '<span class="sbac-report-download">' . t('The GK Report CSV file is now ready for download. Please !download_link.', array('!download_link' => $download_link)) . '</span>';

    gc_enable();
    gc_collect_cycles();
    gc_disable();
  }
  else {
    $message = t('Finished with an error. Please try again.');
  }
  drupal_set_message($message);
}