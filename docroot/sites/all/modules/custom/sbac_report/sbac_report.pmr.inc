<?php

/**
 * Generates the Primary Material Report.
 */
function sbac_report_pmr_report() {
  $sql = "SELECT nid FROM {node} WHERE type = 'resource'";
  $result = db_query($sql);

  $nids = array();
  foreach ($result as $row) {
    $nids[] = $row->nid;
  }

  if ($nids) {
    batch_set(array(
        'title' => t('Primary Material Report'),
        'operations' => array(
          array('sbac_report_pmr_batch_process', array($nids)),
        ),
        'finished' => 'sbac_report_pmr_batch_finished', // Finished batch callback.
        'file' => drupal_get_path('module', 'sbac_report') . '/sbac_report.pmr.inc',
      )
    );
    batch_process('reports');
  }
}

/**
 * Generates the report into a CSV.
 *
 * @param $csv_info
 */
function sbac_report_pmr_batch_process($nids, &$context) {
  $context['sandbox']['finished'] = 0;
  $limit = 200;

  if (!isset($context['sandbox']['file'])) {
    $column_titles = array(
      'Reviewer Title',
      'Document Name',
      'File Extension or Embedded File Type',
      'Direct URL',
    );
    $context['sandbox']['report_configuration'] = $column_titles;

    // Create the file and print the labels in the header row.
    $directory = "private://sbac_media_report/";
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'sbac_report_primary_material_report_' . date('M_d_Y_g_i_s') . '.csv';
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
      $context['sandbox']['nodes'] = $nids;
      $context['sandbox']['node_count'] = count($nids);
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
    if ($context['sandbox']['nodes']) {
      $nid = array_shift($context['sandbox']['nodes']);
      $csv_info = array();
      $material = sbac_report_get_primary_material($nid, $csv_info);
      if (!$material || $nid == 1419) {
        continue;
      }
      sbac_report_get_node_title($nid, $csv_info);
      sbac_report_get_direct_url($nid, $csv_info);

      // initialize
      $csv_column = array();
      $csv_column[] = $csv_info[$nid]['title'];
      $csv_column[] = $csv_info[$nid]['media']['document_name'];
      $csv_column[] = $csv_info[$nid]['media']['file_extension'];
      $csv_column[] = $csv_info[$nid]['url'];

      // write the record to csv.
      fputcsv($handle, $csv_column);
      $context['results']['count']++;
      $context['finished'] = $context['results']['count'] / $context['sandbox']['node_count'];
    }
  }

  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total materials.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['node_count'],
  ));
}

/**
 * Get the node title.
 *
 * @param $nid
 * @param $csv_info
 */
function sbac_report_get_node_title($nid, &$csv_info) {
  $query = "SELECT title FROM {node} WHERE nid = :nid";
  $title = db_query($query, array(':nid' => $nid))->fetchField();
  if ($title) {
    $csv_info[$nid]['title'] = $title;
  }
}

/**
 * Get primary material associated to resource.
 *
 * Primary Material (document name with extensions to determine
 * file type .docx, .mp4, etc, and what embedded video (youtube,
 * fileshare, etc.)  I need to be able to differentiate between
 * the types identified in the table here
 *
 * @param $nid
 * @param $csv_info
 */
function sbac_report_get_primary_material($nid, &$csv_info) {
  $media = db_query("SELECT * FROM {eck_media} WHERE nid = :nid AND type <> :type AND status <> :status ORDER BY weight LIMIT 1", array(':nid' => $nid, ':type' => 'html5', ':status' => 2))->fetchObject();
  if ($media) {
    $csv_info[$nid]['media']['document_name'] = $media->filename;
    if (!empty($media->embed_url)) {
      if (strpos($media->embed_url, 'youtube') !== FALSE) {
        $ext = 'Youtube';
      }
      if (strpos($media->embed_url, 'vimeo') !== FALSE) {
        $ext = 'Vimeo';
      }
      if (strpos($media->embed_url, 'teachertube') !== FALSE) {
        $ext = 'TeacherTube';
      }
      if (strpos($media->embed_url, 'schooltube') !== FALSE) {
        $ext = 'SchoolTube';
      }
      if (strpos($media->embed_url, 'slideshare') !== FALSE) {
        $ext = 'SlideShare';
      }
      $csv_info[$nid]['media']['file_extension'] = $ext;
    }
    else {
      $ext = substr(strrchr($media->filename,'.'), 1);
      $csv_info[$nid]['media']['file_extension'] = $ext;
    }
    return TRUE;
  }
  return FALSE;
}

/**
 * Returns the node URL.
 *
 * @param $nid
 * @param $csv_info
 */
function sbac_report_get_direct_url($nid, &$csv_info) {
  global $base_url;
  $csv_info[$nid]['url'] = $base_url . '/node/' . $nid;
}

/**
 * When the batch finishes, I move the file and show it to the user.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_pmr_batch_finished($success, $results, $operations) {
  if ($success) {
    $directory = "private://sbac_media_report/";
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
    $download_link = l(t('click here to download the file'), $web_url, array('attributes' => array('class' => array('sbac-media-download-link'))));
    $message = '<span class="sbac-report-download">' . t('The SBAC Media Primary Material CSV file is now ready for download. Please !download_link.', array('!download_link' => $download_link)) . '</span>';

    gc_enable();
    gc_collect_cycles();
    gc_disable();
  }
  else {
    $message = t('Finished with an error. Please try again.');
  }
  drupal_set_message($message);
}
