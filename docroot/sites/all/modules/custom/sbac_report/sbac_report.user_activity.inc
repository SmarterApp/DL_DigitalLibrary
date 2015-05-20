<?php
/**
 * CSV Report filter form.
 */
function sbac_csv_report_user_activity_form($form, &$form_state) {
  $form = array();

  // Make sure to load this after autocomplete.js
  // @see sbac_report.csv.js
  if (match_uri('reports')) {
    $form['#attached']['js'] = array(
      drupal_get_path('module', 'sbac_report') .
      '/js/sbac_report.csv.js' => array('weight' => 99),
    );
  }

  $form['state'] = array(
    '#type' => 'select',
    '#title' => t('Choose a state'),
    '#options' => sbac_report_state_options(),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_get_default_state_tid(),
    '#attributes' => array('class' => array('chosen-widget')),
    '#ajax' => array(
      'callback' => 'sbac_report_state_ajax',
    ),
    '#required' => TRUE,
  );

  /* if (sbac_central_user_has_role(array('reports administrator'))) {
    $form['state'] = array_merge($form['state'], array(
      '#multiple' => FALSE,
      '#attributes' => array('class' => array()),
      '#disabled' => TRUE,
    ));
  }
  */
  $user_group_options = sbac_report_user_group_options();
  array_push($user_group_options, 'SNE Members');
  array_push($user_group_options, 'SLT Members');
  /* if (sbac_central_user_has_role(array('reports administrator'))) {
    foreach($user_group_options as $index => $option){
      if(!in_array($option, array('resource contributor', 'resource reviewer', 'all'))){
        unset($user_group_options[$index]);
      }
    }
  }
  */
  sbac_csv_report_prettify($user_group_options);

  $form['user_group_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose User Groups'),
    '#options' => $user_group_options,
    '#attributes' => array('class' => array('chosen-widget')),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_get_default_usergroup(),
    '#required' => TRUE,
  );

  $date_options = sbac_report_date_range_options();
  $session_date_range = sbac_report_get_session_value('date_range', 'range');

  // If there was no date range stored in SESSION.
  // Default to the "Last 30 Days".
  if (empty($session_date_range) || $session_date_range = $date_options['Cumulative to date']) {
    $session_date_range = $date_options['Cumulative to date'];
    $date_display = t('Cumulative to date');
  }
  // If there is, we get the display text "Last 60 Days", "Last 90 Days", etc.
  elseif ($key = array_search($session_date_range, $date_options)) {
    $date_display = t($key);
  }
  // If it was a custom selection, format the string.
  else {
    $date_display = sbac_report_format_date_range($session_date_range);
  }

  sbac_report_build_date_range_dropdown($form, $session_date_range, $date_display, $date_options, '1');

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
    '#submit' => array('sbac_csv_report_user_activity_export_form_submit'),
//    '#attributes' => array('OnSubmit' => 'closeSecondaryAlert();'),
  );

  $form['#validate'][] = 'sbac_csv_report_user_activity_form_validate';

  return $form;
}

/**
 * CSV Report: form validate. This routine also sets the user activity report as the active tab
 */
function sbac_csv_report_user_activity_form_validate($form, &$form_state) {
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_USER;

  if (empty($form_state['values']['date_range1'])) {
    form_set_error('date_range', t('Choose a time period field is required.'));
  }

  if (sbac_central_user_has_role(array('reports administrator'))) {
    if ($form_state['values']['state'] != sbac_report_get_default_state_tid()) {
      form_set_error('state', t('You\'re only allowed to select your own state'));
    }
  }
}

/**
 * CSV Report: Form submit.
 *
 * If there are values in the session, grab them, then build the report and send it to the
 * browser.
 *
 * Note: This routine calls "exit" in order to force the browser to download the csv file.
 */

function sbac_csv_report_user_activity_export_form_submit($form, &$form_state) {
  if ($form_state) {
    $_SESSION['sbac_report']['state']['tid'] = $form_state['values']['state'];
    $_SESSION['sbac_report']['date_range1']['range'] = $form_state['values']['date_range1'];
    $_SESSION['sbac_report']['usergroups']['user_ids'] = $form_state['values']['user_group_dropdown'];
  }
  $state_tid = sbac_report_get_session_value('state', 'tid');
  $date_range = sbac_report_get_session_value('date_range1', 'range');
  $user_groups = sbac_report_get_session_value('usergroups', 'user_ids');

  if (count($user_groups) == 0) {
    $_SESSION['sbac_report']['error_message'] = SBAC_REPORT_FILTER_ERROR;
    $_SESSION['sbac_report']['active_tab'] = 1;
    return; // report did not contain any data.
  }

  $users = get_users_for_user_groups($state_tid, $user_groups);
  if ($users) {
    batch_set(array(
        'title' => t('User Activity Report'),
        'operations' => array(
          array('sbac_report_user_activity_batch', array($users, $date_range)),
        ),
        'finished' => 'sbac_report_user_activity_finished_batch', // Finished batch callback.
      )
    );
    batch_process('reports');
  }
  else {
    if (count($users) == 0) {
      drupal_set_message(SBAC_REPORT_FILTER_ERROR, 'error');
      $_SESSION['sbac_report']['error_message'] = SBAC_REPORT_FILTER_ERROR;
      return;
    }
  }
}

/**
 * Batch process the users.
 *
 * @param $users
 * @param $context
 * @return null|string
 */
function sbac_report_user_activity_batch($users, $date_range, &$context) {
  $limit = 50;
  $context['sandbox']['finished'] = 0;
  ini_set('memory_limit', '512M');

  // First time through.
  if (!isset($context['sandbox']['file'])) {
    $column_titles = set_user_activity_report_columns();
    $context['sandbox']['report_configuration'] = $column_titles;
    $directory = "private://user_activity_stats_csv/";
    file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    $filename = 'User_Activity_' . date('M_d_Y_g_i_s') . '.csv';
    $directory .= $filename;
    $directory_real_path = drupal_realpath($directory);
    $handle = fopen($directory_real_path, 'w'); // Create the file.
    fputcsv($handle, $column_titles); // Write the labels to the header row.
    fclose($handle);

    // Store info in sandbox during processing.
    $context['sandbox']['file'] = $directory_real_path;
    // Store some values in the results array for processing when finshed.
    $context['results']['filename'] = $filename;
    $context['results']['file'] = $directory_real_path;
    if (file_exists($directory_real_path)) {
      $context['sandbox']['progress'] = 0;
      $context['sandbox']['users'] = $users;
      $context['sandbox']['date_range'] = $date_range;
      $context['sandbox']['user_total'] = count($context['sandbox']['users']);
    }
    unset($column_titles);
    unset($directory);
    unset($directory_real_path);
    unset($filename);
  }
  unset($users);

  // Open the file for writing ('a' puts pointer at end of file).
  $handle = fopen($context['sandbox']['file'], 'a');
  if (!isset($context['results']['count'])) {
    $context['results']['count'] = 0;
  }

  // Loop until we hit the batch limit.
  for ($i = 0; $i < $limit; $i++) {
    if ($context['sandbox']['users']) {
      $user = array_shift($context['sandbox']['users']);
      $user_activity = get_user_activity($user, $context['sandbox']['date_range']);
      $row = create_user_activity_from_data($user, $user_activity);
      sbac_report_user_activity_organize_columns($row, $context['sandbox']['report_configuration']);
      fputcsv($handle, $row);

      unset($row);
      unset($user);
      unset($user_activity);

      $context['results']['count']++;
      $context['finished'] = $context['results']['count'] / $context['sandbox']['user_total'];
    }
  }

  fclose($handle);
  unset($handle);
  // Show message updating user on how many subscribers have been exported.
  $context['message'] = t('Exported @count of @total users.', array(
    '@count' => $context['results']['count'],
    '@total' => $context['sandbox']['user_total'],
  ));
}

/**
 * Organize a row according to the columns specified
 */
function sbac_report_user_activity_organize_columns(&$row, $columns){
  $temp_row = array();
  foreach($columns as $index => $column_name){
    $temp_row[] = $row[$column_name];
  }
  $row = $temp_row;
}

/**
 * Once finished, allow the user to download the csv.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function sbac_report_user_activity_finished_batch($success, $results, $operations) {
  if ($success) {
    $directory = "private://user_activity_stats_csv/";
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
    $message = '<span class="sbac-report-download">' . t('The User Activity Report file is now ready for download. Please !download_link.', array('!download_link' => $download_link)) . '</span>';

    gc_enable();
    gc_collect_cycles();
    gc_disable();
    //_cex_download($csv_resource_stats_result, 'output.csv');
    $_SESSION['sbac_report']['error_message'] = '';
    $_SESSION['sbac_report']['first_time'] = 0;
  }
  else {
    $message = t('Finished with an error. Please try again.');
  }
  drupal_set_message($message);
}

/**
 * Prettify the drop down options.
 *
 * @param $user_group_options
 */
function sbac_csv_report_prettify(&$user_group_options) {
  foreach ($user_group_options as $key => $value) {
    switch ($value) {
      case 'all':
        $user_group_options[$key] = t('All Users');
        break;
      case 'basic end user':
        unset($user_group_options[$key]);
        break;
      case 'advanced end user':
        $user_group_options[$key] = t('End Users');
        break;
      case 'resource contributor':
        $user_group_options[$key] = t('Contributors');
        break;
      case 'resource reviewer':
        $user_group_options[$key] = t('Reviewers');
        break;
      case 'resource publisher':
        $user_group_options[$key] = t('Posters');
        break;
      case 'facilitator':
        $user_group_options[$key] = t('Facilitators');
        break;
      case 'moderator':
        $user_group_options[$key] = t('Moderators');
        break;
      case 'DLRB member':
        $user_group_options[$key] = t('DLRB Members');
        break;
      case 'guest':
        unset($user_group_options[$key]);
        break;
      case 'admins':
        $user_group_options[$key] = t('Admins');
        break;
    }
  }
  /* if (!sbac_central_user_has_role(array('reports administrator'))) {
    $res = $user_group_options;
    $user_group_options = array_slice($res, 0, 5, TRUE) + array(32 => "SNE Members") + array(33 => "SLT Members") + array(13 => "Moderators") + array(11 => "Facilitators") + array_slice($res, 3, count($res) - 3, TRUE);
    if (isset($user_group_options[37]) && $user_group_options[37] == 'SNE Members') {
      unset($user_group_options[37]);
    }
    if (isset($user_group_options[38]) && $user_group_options[38] == 'SLT Members') {
      unset($user_group_options[38]);
    }
    }*/
}

/*
 * Get the user groups for a given user group.  Note that a query with 'in (%s)' in the string doesn't work
 * properly with Drupals perpared statement support.
 *
 */
function get_users_for_user_groups($state_tid, &$user_groups_ids) {
  // look for the aggregated admins option "admins"
  if (array_key_exists(1, $user_groups_ids)) {
    // get the admins:
    $admins = sbac_report_user_group_admins();
    unset($user_groups_ids[1]);
    foreach ($admins as $key => $value) {
      $user_groups_ids[$key] = $key;
    }
  }
  // look for the 'all' option being set:
  else {
    if (array_key_exists(0, $user_groups_ids)) {

      $admins = sbac_report_user_group_admins();
      foreach ($admins as $key => $value) {
        $user_groups_ids[$key] = $key;
      }
      $all = sbac_report_user_group_options();
      foreach ($all as $key => $value) {
        $user_groups_ids[$key] = $key;
        
      }
    }
  }

  $slt_filter = FALSE;
  $sne_filter = FALSE;
  if (in_array(32, $user_groups_ids)) { // 32 is SNE
    $sne_filter = $user_groups_ids[32];
    unset($user_groups_ids[32]);
  }
  if (in_array(33, $user_groups_ids)) { // 33 is SLT
    $slt_filter = $user_groups_ids[33];
    unset($user_groups_ids[33]);
  }

  $query = db_select('users', 'u');
  $query->fields('u', array('uid'));
  if ($user_groups_ids) {
    $query->join('users_roles', 'ur', 'u.uid = ur.uid');
    $query->condition('ur.rid', $user_groups_ids, 'IN');
  }
  if ($sne_filter && $slt_filter) {
    $query->join('field_data_field_sne_member', 'sne', 'u.uid = sne.entity_id');
    $query->join('field_data_field_slt_member', 'slt', 'u.uid = slt.entity_id');
    $or = db_or()->condition('sne.field_sne_member_value', 1)->condition('slt.field_slt_member_value', 1);
    $query->condition($or);
  }
  else if ($sne_filter) {
    $query->join('field_data_field_sne_member', 'sne', 'u.uid = sne.entity_id');
    $query->condition('sne.field_sne_member_value', 1);
  }
  else if ($slt_filter) {
    $query->join('field_data_field_slt_member', 'slt', 'u.uid = slt.entity_id');
    $query->condition('slt.field_slt_member_value', 1);
  }
  if (in_array('all', $state_tid)) {
    // nothing, they want all users.
  }
  else {
    $query->join('field_data_field_state', 'state', 'u.uid = state.entity_id');
    if (is_array($state_tid)) {
      $query->condition('state.field_state_tid', $state_tid, 'IN');
    } else {
      $query->condition('state.field_state_tid', $state_tid);
    }
  }

  $result = $query->execute();
  $users = array();
  foreach ($result as $record) {
    $users[$record->uid] = $record;
  }
  return $users;
}

/*
 * Local function that handles all the query logic for the count queries.  It injects the user list and optionally
 * a from/to date into the query.  It then performs the query and returns the resulting records in a hash by user
 * id (uid).
*/
function count_with_users_query($sql_template, $user, $from_date = NULL, $to_date = NULL, $special_case = NULL) {
  // done this way because the prepared statement didn't work passing array or comma separated string.
  // TODO: make prepared statement work here, or escape string???

  if ($from_date && $to_date) {
    $sql = sprintf($sql_template, $user->uid, '%Y%m%d', $from_date, $to_date);
  }
  else {
    $sql = sprintf($sql_template, $user->uid);
  }
  $result = db_query($sql);
  if ($special_case) {
    $values = array();
    foreach ($result as $record) {
      if (!isset($values[$record->uid])) {
        $values[$record->uid] = 1;
      }
      else {
        $values[$record->uid]++;
      }
    }
  }
  else {
    $values = array();
    foreach ($result as $record) {
      $values[$record->uid] = $record;
    }
  }

  return $values;
}

/*
 * Get the user activity on resources and reviews.  There are 12 different statistics that are retrieved by this
 * routine, each one a count of something.  This routine also gets the terms of service legal information.
 */
function get_user_activity($user, $date_range) {
  // extract the date range into a from and to date
  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  // Count queries:
  # resources viewed
  $sql = "select count(nid) as count, uid From node_user_paradata where uid in (%s) group by uid";
  $user_activity['resources_viewed'] = count_with_users_query($sql, $user);

  # resources downloaded
  $sql = "select count(nid) as count, uid from sbac_resource_download_stats where uid in (%s) group by uid";
  $user_activity['resources_downloaded'] = count_with_users_query($sql, $user);

  # resources favorited
  $sql = "select count(s.id) as count, s.uid from sbac_favorites s where s.uid in (%s) and s.type = 'node' and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL s.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by s.uid";
  $user_activity['resources_favorited'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # helpful reviews
  $sql = "select count(distinct r.node_id) as count, r.uid from eck_review r left join votingapi_vote v on v.entity_id = r.id and v.entity_type = 'review' where v.value
 > 0 and r.uid in (%s) and DATE_FORMAT((DATE_ADD('19700101', INTERVAL r.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by r.uid";
  $user_activity['resources_helpful'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # resources reviewed/rated
  $sql = "select count(id) as count, uid,created from eck_review where status = 1 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['resources_reviewed'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # resources contributed:
  $sql = "select count(distinct(n.nid)) as count, n.uid, n.created from node as n
    join workbench_moderation_node_history as wmnh on n.nid = wmnh.nid AND n.vid = wmnh.vid
    where n.type = 'resource' and n.uid in (%s) and wmnh.state!='draft' and wmnh.current <> '0' and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL n.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by n.uid";
  $user_activity['resources_contributed'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # topic forum views
  $sql = "select count(distinct v.tid) as count, v.uid from sbac_forum_views v left join field_data_field_forum_resource_ref r on v.tid = r.entity_id where v.uid in (%s) and r.field_forum_resource_ref_target_id is null group by v.uid";
  $user_activity['forum_views'] = count_with_users_query($sql, $user);

  # resource forum participated
  $sql = "select count(distinct s.resource_id) as count, s.uid from
	(select r.field_forum_resource_ref_target_id as resource_id, n.uid, n.created from node n left join field_data_field_topic_forum_parent p on n.nid = p.entity_id left join field_data_field_forum_resource_ref r on p.field_topic_forum_parent_tid = r.entity_id  where n.type = 'topic' and r.field_forum_resource_ref_target_id is not null
UNION
select r.field_forum_resource_ref_target_id as resource_id, c.uid, c.created from comment c left join node n on c.nid = n.nid left join field_data_field_topic_forum_parent p on n.nid = p.entity_id left join field_data_field_forum_resource_ref r on p.field_topic_forum_parent_tid = r.entity_id where r.field_forum_resource_ref_target_id is not null) s
where s.uid in (%s) and DATE_FORMAT((DATE_ADD('19700101', INTERVAL s.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
group by s.uid";
  $user_activity['resource_forum_participated'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # resource forum posts created
  $sql = "select count(c.cid) as count, c.uid from comment c left join node n on c.nid = n.nid left join field_data_field_topic_forum_parent p on n.nid = p.entity_id
left join field_data_field_forum_resource_ref r on p.field_topic_forum_parent_tid = r.entity_id where c.uid in (%s) and r.field_forum_resource_ref_target_id
 is not null and DATE_FORMAT((DATE_ADD('19700101', INTERVAL c.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by c.uid";
  $user_activity['resource_forum_posts_created'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # topic forum posts created
  $sql = "select count(c.cid) as count, c.uid from comment c left join node n on c.nid = n.nid left join field_data_field_topic_forum_parent p on n.nid = p.entity_id
left join field_data_field_forum_resource_ref r on p.field_topic_forum_parent_tid = r.entity_id where c.uid in (%s) and r.field_forum_resource_ref_target_id
 is null and DATE_FORMAT((DATE_ADD('19700101', INTERVAL c.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by c.uid";
  $user_activity['topic_forum_posts_created'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # posts recommended by others
  $sql = "select count(distinct c.cid) as count, c.uid from comment c left join field_data_field_topic_comment_recommended r on c.cid = r.entity_id where r
.field_topic_comment_recommended_target_id is not null and c.uid in (%s) and DATE_FORMAT((DATE_ADD('19700101', INTERVAL c.created SECOND) + INTERVAL -25200
SECOND), '%s') BETWEEN %s AND %s group by c.uid";
  $user_activity['posts_recommended_by_others'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # posts recommend by user
  $sql = "
SELECT
	count(DISTINCT c.cid) AS count,
	r.field_topic_comment_recommended_target_id as uid
FROM comment c
	LEFT JOIN field_data_field_topic_comment_recommended r
		ON c.cid = r.entity_id
WHERE
	r.field_topic_comment_recommended_target_id IN (%s)
GROUP BY r.field_topic_comment_recommended_target_id";
  $user_activity['posts_recommended_by_user'] = count_with_users_query($sql, $user);

  # flag resources removed by user
  $sql = "
SELECT
	count(DISTINCT f.target_id) AS count,
	f.being_moderated                       AS uid
FROM eck_flag f
WHERE f.target_type = 'resource'
      AND f.being_moderated in (%s)
      AND f.resolved = 2
      AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
	group by f.being_moderated";
  $user_activity['flag_resources_removed_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flag resources resolved by user
  $sql = "
SELECT
	count(DISTINCT f.target_id) AS count,
	f.being_moderated                       AS uid
FROM eck_flag f
WHERE f.target_type = 'resource'
      AND f.being_moderated in (%s)
      AND f.resolved = 1
      AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
	group by f.being_moderated";
  $user_activity['flag_resources_resolved_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flag reviews removed by user
  $sql = "
SELECT
	count(DISTINCT f.target_id)       AS count,
	f.being_moderated AS uid
FROM eck_flag f
	LEFT JOIN eck_review r
		ON r.id = f.target_id
WHERE
	f.target_type = 'review'
	AND f.being_moderated IN (%s)
	AND f.resolved = 1
	AND r.status = 0
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.changed SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY f.being_moderated";
  $user_activity['flag_reviews_removed_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flag reviews resolved by user
  $sql = "
SELECT
	count(DISTINCT f.target_id)       AS count,
	f.being_moderated AS uid
FROM eck_flag f
	LEFT JOIN eck_review r
		ON r.id = f.target_id
WHERE
	f.target_type = 'review'
	AND f.being_moderated IN (%s)
	AND f.resolved = 1
	AND r.status = 1
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.changed SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY f.being_moderated";
  $user_activity['flag_reviews_resolved_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flag discussion removed by user
  $sql = "
SELECT
	count(f.target_id) AS count,
	f.being_moderated  AS uid
FROM eck_flag f
WHERE
	f.target_type = 'topic'
	AND f.being_moderated IN (%s)
	AND f.resolved = 2
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.changed SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY f.being_moderated";
  $user_activity['flag_discussion_removed_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flag posts removed by user
  $sql = "
SELECT
	count(DISTINCT f.target_id) AS count,
	f.being_moderated           AS uid
FROM eck_flag f
WHERE
	f.target_type = 'comment'
	AND f.being_moderated in (%s)
	AND f.resolved = 2
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.changed SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY f.being_moderated";
  $user_activity['flag_posts_removed_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # topic discussion deleted by user
  $sql = "
SELECT
	count(l.entity_id) AS count,
	l.uid              AS uid
FROM sbac_forum_deleted_log l
WHERE
	l.uid IN (%s)
	AND l.entity_type = 'node'
	AND l.forum_type = 'topic'
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL l.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY l.uid";
  $user_activity['topic_discussions_deleted_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # resource discussion deleted by user
  $sql = "
SELECT
	count(l.entity_id) AS count,
	l.uid              AS uid
FROM sbac_forum_deleted_log l
WHERE
	l.uid IN (%s)
	AND l.entity_type = 'node'
	AND l.forum_type = 'resource'
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL l.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY l.uid";
  $user_activity['resource_discussions_deleted_by_user'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flagged reviews
  $sql = "select count(distinct r.id) as count, r.uid from eck_review r left join eck_flag f on f.target_id = r.id and f.target_type = 'review' where r.uid in (%s) and f
.id is not null and DATE_FORMAT((DATE_ADD('19700101',
 INTERVAL r.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by r.uid ;";
  $user_activity['flagged_rating'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flagged discussions
  $sql = "
SELECT
	count(DISTINCT n.nid) AS count,
	n.uid
FROM node n LEFT JOIN eck_flag f
		ON f.target_id = n.nid AND f.target_type = 'topic'
WHERE
	n.type = 'topic'
	AND n.uid in (%s)
	AND f.id IS NOT NULL
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL n.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY n.uid;";
  $user_activity['flagged_discussions'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # flagged posts
  $sql = "
SELECT
	count(c.cid) AS count,
	c.uid
FROM comment c LEFT JOIN eck_flag f
		ON f.target_id = c.cid AND f.target_type = 'comment'
WHERE
	f.id IS NOT NULL
	AND c.uid in (%s)
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL c.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY c.uid";
  $user_activity['flagged_posts'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # posts flagged by user
  $sql = "
SELECT
	count(f.id) AS count,
	f.uid
FROM eck_flag f
WHERE
	f.target_type IN ('comment', 'topic')
	AND f.uid IN (%s)
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL f.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY f.uid";
  $user_activity['posts_flagged'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # resources flagged by others
  $sql = "
SELECT
	count(n.nid) as count,
	n.uid
FROM node n
	LEFT JOIN eck_flag f
		ON f.target_id = n.nid AND f.target_type = 'resource'
WHERE
	n.type = 'resource'
	AND n.uid IN (%s)
	AND f.id IS NOT NULL
	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL n.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY n.uid";
  $user_activity['resources_flagged_by_others'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # topic forum participated
  $sql = "
SELECT
	count(DISTINCT s.forum_id) AS count,
	s.uid
FROM
	(SELECT
		 p.field_topic_forum_parent_tid AS forum_id,
		 n.uid,
		 n.created
	 FROM node n LEFT JOIN field_data_field_topic_forum_parent p
			 ON n.nid = p.entity_id
		 LEFT JOIN field_data_field_forum_resource_ref r
			 ON p.field_topic_forum_parent_tid = r.entity_id
	 WHERE n.type = 'topic' AND r.field_forum_resource_ref_target_id IS NULL
	 UNION
	 SELECT
		 p.field_topic_forum_parent_tid AS forum_id,
		 c.uid,
		 c.created
	 FROM comment c LEFT JOIN node n
			 ON c.nid = n.nid
		 LEFT JOIN field_data_field_topic_forum_parent p
			 ON n.nid = p.entity_id
		 LEFT JOIN field_data_field_forum_resource_ref r
			 ON p.field_topic_forum_parent_tid = r.entity_id
	 WHERE r.field_forum_resource_ref_target_id IS NULL) s
WHERE
	s.uid IN (%s)
 	AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL s.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s
GROUP BY s.uid;
";
  $user_activity['topic_forum_participated'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # resource forum discussion created
  $sql = "select count(distinct n.nid) as count, n.uid from node n left join field_data_field_topic_forum_parent p on n.nid = p.entity_id left join
field_data_field_forum_resource_ref r on p.field_topic_forum_parent_tid = r.entity_id where n.uid in (%s) and  n.type = 'topic' and r
.field_forum_resource_ref_target_id is not null and DATE_FORMAT((DATE_ADD('19700101', INTERVAL n.created SECOND) + INTERVAL -25200 SECOND),
'%s') BETWEEN %s AND %s group by n.uid";
  $user_activity['resource_forum_discussion_created'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # topic forum discussion created
  $sql = "select count(distinct n.nid) as count, n.uid from node n left join field_data_field_topic_forum_parent p on n.nid = p.entity_id left join
field_data_field_forum_resource_ref r on p.field_topic_forum_parent_tid = r.entity_id where n.uid in (%s) and  n.type = 'topic' and r
.field_forum_resource_ref_target_id is null and DATE_FORMAT((DATE_ADD('19700101', INTERVAL n.created SECOND) + INTERVAL -25200 SECOND),
'%s') BETWEEN %s AND %s group by n.uid";
  $user_activity['topic_forum_discussion_created'] = count_with_users_query($sql, $user, $from_date, $to_date);


  # Resources Viewed:
  $sql = "select count(n.nid) as count, n.uid from node_user_paradata n where n.uid in (%s) group by n.uid";
  $user_activity['resources_viewed'] = count_with_users_query($sql, $user);

  # GK Reviews completed:
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'gate_keeper' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['gc_reviews_completed'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # QC Reviews completed:
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'qc' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['qc_reviews_completed'] = count_with_users_query($sql, $user, $from_date, $to_date);
  //    array(':from_date' => $from_date, ':to_date' => $to_date));

  # Poster Reviews completed:
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'post' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['poster_reviews_completed'] = count_with_users_query($sql, $user, $from_date, $to_date);
  //    array(':from_date' => $from_date, ':to_date' => $to_date));

  # Resources with GK Review accepted on contributed resource:
//  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and nid in (
//    select node_id from eck_feedback where type = 'gate_keeper' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and met_criteria = 1 and
//    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
//    BETWEEN %s AND %s) group by uid";
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'gate_keeper' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and
    met_criteria = 1 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['gc_reviews_accepted_on_contributed_resources'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # Resources with GK Review returned on contributed resource:
//  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and nid in (
//    select node_id from eck_feedback where type = 'gate_keeper' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and met_criteria = 0 and
//    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
//    BETWEEN %s AND %s) group by uid";
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'gate_keeper' and ((status = 1) OR (status = 0 AND archived = 1)) and completed = 1 and
    met_criteria = 0 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['gc_reviews_returned_on_contributed_resources'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # Contributed resources posted
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and sticky = 0 and nid in (select nid from workbench_moderation_node_history where
    state = 'published' AND published = 1 AND current = 1) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['contributed_resources_posted'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # Contributed resources posted with distinction
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and sticky = 1 and nid in (select nid from workbench_moderation_node_history
    where state = 'published' AND published = 1 AND current = 1) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['contributed_resources_posted_with_distinction'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # Contributed resources reviewed and returned
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and nid in (select nid from workbench_moderation_node_history where
  state = 'rejected')  and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['contributed_resources_reviewed_and_returned'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # terms of service.
  $sql = "SELECT la.uid,la.accepted as 'tos_accepted',lc.version as 'tos_version',lc.revision as 'tos_revision',lc.date as 'tos_revision_date'
          FROM legal_conditions as lc join legal_accepted as la on lc.version=la.version
          WHERE uid in (%s)";
  $sql = sprintf($sql, $user->uid);
  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->uid] = $record;
  }
  $user_activity['tos'] = $values;

  # Temporary Links Generated
  $sql = "SELECT count(nid) AS count, uid FROM {sbac_share} WHERE uid IN (%s)
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL create_datetime SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['temporary_link_generated'] = count_with_users_query($sql, $user, $from_date, $to_date);

  # Unique Temporary Links Generated
  $sql = "SELECT count(nid) as count, uid FROM {sbac_share} WHERE uid IN (%s)
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL create_datetime SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by nid, uid";
  $user_activity['unique_temporary_link_generated'] = count_with_users_query($sql, $user, $from_date, $to_date, TRUE);

  if ($user->uid == 144) {
    $var = '';
  }

  # Resource reviews with Pending Flags
  $sql = "SELECT count(er.node_id) AS count, er.uid FROM {eck_flag} ef JOIN {eck_review} er ON ef.target_id = er.id
          WHERE er.uid IN (%s) AND ef.type = 'review_end_use' AND ef.being_moderated = 0 AND ef.resolved = 0
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL ef.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by er.node_id, er.uid";
  $user_activity['resource_reviews_with_pending_flags'] = count_with_users_query($sql, $user, $from_date, $to_date, TRUE);

  # Resource reviews with Resolved Flags
  $sql = "SELECT count(er.node_id) AS count, er.uid FROM {eck_flag} ef JOIN {eck_review} er ON ef.target_id = er.id
          WHERE er.uid IN (%s) AND ef.type = 'review_end_use' AND ef.being_moderated > 0 AND ef.resolved = 1
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL ef.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by er.node_id, er.uid";
  $user_activity['resource_reviews_with_resolved_flags'] = count_with_users_query($sql, $user, $from_date, $to_date, TRUE);

  # Resources Flagged
  $sql = "SELECT count(nid) as count, uid FROM {eck_flag} WHERE uid IN (%s) AND type = 'resource'
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by nid, uid";
  $user_activity['resources_flagged'] = count_with_users_query($sql, $user, $from_date, $to_date, TRUE);

  # Resource Reviews Flagged
  $sql = "SELECT count(nid) as count, uid FROM {eck_flag} WHERE uid IN (%s) AND type = 'review_end_use'
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by nid, uid";
  $user_activity['resource_reviews_flagged'] = count_with_users_query($sql, $user, $from_date, $to_date, TRUE);

  return $user_activity;
}

/*
 * Create the User Activity CSV report.  This routine uses 'validate_and_fill_out_user_activity_report to specify
 * the columns of the report and to fill out the missing values in the queried data set.  Once it has the columns of
 * the report and the cleaned up data, it formats the CSV report as a string and returns it.
 *
 * @param $user_activity contains all the data for the report, basically, a list of users with various statistics
 * counted.  See 'get_user_activity()' for the queries to retreive this data.
 */
function create_user_activity_from_data($user, $user_activity) {
  $separator = '';
  $encloseer = '';
  $quote_arrays = TRUE;
  $subseparator = ',';
  $subquote = "";
  $fieldkeys = array();
  $foreignidkeys = array();
  $stringkeys = array();
  $uidcountkeys = array();
  $toskeys = array();
  $countkeys = array();
  $flagkeys = array();

  // get the fields for the report and clean up the data.
  $account = validate_and_fill_out_user_activity($user, $user_activity, $fieldkeys, $foreignidkeys, $stringkeys, $uidcountkeys, $toskeys, $countkeys, $flagkeys);

  $row = array();
  foreach ($fieldkeys as $fieldkey) {
    $is_date = (array_key_exists(2, $fieldkey) ? $fieldkey[2] == 'date' : FALSE);
    $string = '';
    format_value_field($string, $account->{$fieldkey[0]}, $separator, $encloseer, $subseparator, $quote_arrays, $subquote, $is_date);
    $row[$fieldkey[1]] = $string;
  }

  foreach ($foreignidkeys as $foreignidkey) {
    $is_date = (array_key_exists(2, $foreignidkey) ? $foreignidkey[2] == 'date' : FALSE);
    // tid is replaced by the actual value in the value field.
    $string = '';
    format_value_field($string, $account->{$foreignidkey[0]}, $separator, $encloseer, $subseparator, $quote_arrays, $subquote, $is_date);
    $row[$foreignidkey[1]] = $string;
  }

  foreach ($stringkeys as $stringkey) {
    $is_date = (array_key_exists(2, $stringkey) ? $stringkey[2] == 'date' : FALSE);
    if (is_null($account->{$stringkey[0]})) {
      $value = '';
    }
    else {
      if ($is_date) {
        $value = format_date($account->{$stringkey[0]}, 'custom', 'Y-m-d');
      }
      else {
        $value = $account->{$stringkey[0]};
      }
    }
    if($stringkey[1] == 'Role' && is_array($value)){
      unset($value[2]); // authenticated user role
      $value = ucwords(implode(', ', $value));
    }
    $row[$stringkey[1]] = $value;
    $value = NULL;
  }

  foreach ($uidcountkeys as $uidcountkey) {
    $row[$uidcountkey[1]] = $user_activity[$uidcountkey[0]][$user->uid]->count;
  }

  $param = array();
  $param['und'] = array();
  $param['und'][0] = array();
  foreach ($toskeys as $toskey) {
    $is_date = (array_key_exists(2, $toskey) ? $toskey[2] == 'date' : FALSE);
    $param['und'][0]['value'] = $user_activity['tos'][$user->uid]->{$toskey[0]};
    $string = '';
    format_value_field($string, $param, $separator, $encloseer, $subseparator, $quote_arrays, $subquote, $is_date);
    $row[$toskey[1]] = $string;
  }

  foreach ($countkeys as $countkey) {
    if (isset($user_activity[$countkey[0]][$user->uid]->count) && !is_null($user_activity[$countkey[0]][$user->uid]->count)) {
      $value = $user_activity[$countkey[0]][$user->uid]->count;
    }
    else {
      if (isset($user_activity[$countkey[0]][$user->uid]) && !is_null($user_activity[$countkey[0]][$user->uid])) {
        $value = $user_activity[$countkey[0]][$user->uid];
      }
      else {
        $value = 0;
      }
    }
    $row[$countkey[1]] = $value;
  }

  foreach ($flagkeys as $flagkey) {
    if (isset($user_activity[$flagkey[0]][$user->uid]->count) && !is_null($user_activity[$flagkey[0]][$user->uid]->count)) {
      $value = $user_activity[$flagkey[0]][$user->uid]->count;
    }
    else {
      if (isset($user_activity[$flagkey[0]][$user->uid]) && !is_null($user_activity[$flagkey[0]][$user->uid])) {
        $value = $user_activity[$flagkey[0]][$user->uid];
      }
      else {
        $value = 0;
      }
    }
    $row[$flagkey[1]] = $value;
  }

  return $row;
}

/*
 * This routine defines the columns of the user activity report and also validates and pads out the query data.
 *
 * An array is created that defines the columns of the report.  Each entry in the array contains an index into the data
 * set, the human readable title, and a flag for wether the field is a date.
 *
 * There are five types of locations where the data for fields can be found.
 *
 * stringkey: from the user profile as a direct value
 * fieldkey: from the user profile drupal field data as a direct value
 * foreignidkey: from the user profile field data, but as a foreign key to the taxonomy table.
 * uidcountkey: from the 12 specialized statistic queries
 * toskey: the terms of service queries.
 *
 */
function validate_and_fill_out_user_activity($user, &$user_activity, &$fieldkeys, &$foreignidkeys, &$stringkeys, &$uidcountkeys, &$toskeys, &$countkeys, &$flagkeys) {
  array_push($fieldkeys, array('field_first_name', 'First Name'));
  array_push($fieldkeys, array('field_last_name', 'Last Name'));
  array_push($fieldkeys, array('field_sne_member', 'Is SNE Member'));
  array_push($fieldkeys, array('field_slt_member', 'Is SLT Member'));
  array_push($fieldkeys, array('field_school_name', 'School'));
  array_push($fieldkeys, array('field_district_name', 'District'));
  array_push($foreignidkeys, array('field_position', 'Title'));
  array_push($foreignidkeys, array('field_state', 'State'));
  array_push($foreignidkeys, array('field_grade_level_s_', 'Grade(s)'));
  array_push($foreignidkeys, array('field_subject_s_', 'Subject(s)'));
  array_push($foreignidkeys, array('field_special_populations', 'School Population(s)'));

  array_push($stringkeys, array('mail', 'Email'));
  array_push($stringkeys, array('roles', 'Role'));
  array_push($stringkeys, array('created', 'Date Created', 'date'));
  array_push($stringkeys, array('access', 'Last Access', 'date'));
  array_push($stringkeys, array('login', 'Last Login', 'date'));

  array_push($uidcountkeys, array('resources_viewed', '# of Resources Viewed by User'));
  array_push($uidcountkeys, array('resources_downloaded', '# of Resources Downloaded by User'));
  array_push($uidcountkeys, array('resources_favorited', '# of Resources Favorited by User'));
  array_push($uidcountkeys, array('resources_reviewed', '# of Resources Rated by User'));
  array_push($uidcountkeys, array('resources_helpful', '# of User\'s Ratings Marked Helpful by Others'));
  array_push($uidcountkeys, array('resources_contributed', '# of Resources Contributed by User'));
  array_push($uidcountkeys, array('forum_views', '# of Topic Forums Viewed by User'));
  array_push($uidcountkeys, array('resource_forum_participated', '# of Resource Forums Participated by User'));
  array_push($uidcountkeys, array('topic_forum_participated', '# of Topic Forums Participated by User'));
  array_push($uidcountkeys, array('resource_forum_discussion_created', '# of Resource Forum Discussions Created by User'));
  array_push($uidcountkeys, array('topic_forum_discussion_created', '# of Topic Forum Discussions Created by User'));
  array_push($uidcountkeys, array('resource_forum_posts_created', '# of Resource Forum Posts Created by User'));
  array_push($uidcountkeys, array('topic_forum_posts_created', '# of Topic Forum Posts Created by User'));
  array_push($uidcountkeys, array('posts_recommended_by_others', '# of User\'s Forum Posts Recommended by Others'));
  array_push($uidcountkeys, array('posts_recommended_by_user', '# of Others\' Forum Posts Recommended by User'));
  array_push($uidcountkeys, array('flag_resources_removed_by_user', '# of Flagged Resources Removed by User through Moderation'));
  array_push($uidcountkeys, array('flag_resources_resolved_by_user', '# of Flagged Resources Resolved by User through Moderation'));
  array_push($uidcountkeys, array('flag_reviews_removed_by_user', '# of Flagged Resource Reviews Removed by User through moderation'));
  array_push($uidcountkeys, array('flag_reviews_resolved_by_user', '# of Flagged Resource Reviews Resolved by User through moderation'));
  array_push($uidcountkeys, array('flag_discussion_removed_by_user', '# of Flagged Forum Discussions Removed by User through moderation'));
  array_push($uidcountkeys, array('flag_posts_removed_by_user', '# of Flagged Forum Posts Removed by User through moderation'));
  array_push($uidcountkeys, array('flagged_rating', '# of Resource Ratings Created by User that were Flagged'));
  array_push($uidcountkeys, array('flagged_discussions', '# of Forum discussions created by User that were Flagged'));
  array_push($uidcountkeys, array('flagged_posts', '# of Forum Posts created by User that were Flagged'));
  array_push($uidcountkeys, array('posts_flagged', '# of Forum Posts and Discussions Flagged by User'));
  array_push($uidcountkeys, array('gc_reviews_completed', '# of GK Reviews Completed by User'));
  array_push($uidcountkeys, array('qc_reviews_completed', '# of QC Reviews Completed by User'));
  array_push($uidcountkeys, array('poster_reviews_completed', '# of Arbitration Reviews Completed by User'));
  array_push($uidcountkeys, array('contributed_resources_posted', '# of Resources Contributed by User that are Posted'));
  array_push($uidcountkeys, array('contributed_resources_posted_with_distinction', '# of Resources Contributed by User that are Posted with Distinction'));
  array_push($uidcountkeys, array('resources_flagged_by_others', '# of  Resources Contributed by User that were Flagged'));
  array_push($uidcountkeys, array('topic_forums_created', '# of Topic Forums Created by User'));
  array_push($uidcountkeys, array('topic_discussions_deleted_by_user', '# of Topic Forum Discussions Deleted by User'));
  array_push($uidcountkeys, array('resource_discussions_deleted_by_user', '# of Resource Forum Discussions Deleted by User'));

  array_push($toskeys, array('tos_accepted', 'Date of Terms of Service', 'date'));
  array_push($toskeys, array('tos_version', 'Version of Terms of Service Accepted'));
  array_push($toskeys, array('tos_revision_date', 'Date of Terms of Service Version', 'date'));

  array_push($countkeys, array('temporary_link_generated', '# of Temporary Public Links Generated by User'));
  array_push($countkeys, array('unique_temporary_link_generated', '# of Resources For Which User Generated Temporary Public Links'));

  array_push($flagkeys, array('resources_flagged', '# of Resources Flagged by User'));
  array_push($flagkeys, array('resource_reviews_flagged', '# of Resource Reviews Flagged by User'));

  // replace missing values with ' ' or 0
  $missing_string = ' ';
  $missing_integer = 0;

  $used_tids = array();
  $account = user_load($user->uid);
  foreach ($fieldkeys as $fieldkey) {
    format_value_property($account, $fieldkey[0], $missing_string);
  }
  // build taxonomy index table while validating. grab all the ids then
  // load them all in one has table for quick reference.
  foreach ($foreignidkeys as $foreignidkey) {
    format_tid_property($account, $foreignidkey[0], $missing_string, $used_tids);
  }
  foreach ($stringkeys as $stringkey) {
    if (!property_exists($account, $stringkey[0])) {
      $account->{$stringkey[0]} = $missing_string;
    }
  }
  foreach ($uidcountkeys as $uidcountkey) {
    if (!array_key_exists($uidcountkey[0], $user_activity) or
      !array_key_exists($user->uid, $user_activity[$uidcountkey[0]]) or
      is_null($user_activity[$uidcountkey[0]][$user->uid])
    ) {
      if (!array_key_exists($uidcountkey[0], $user_activity)) {
        $user_activity[$uidcountkey[0]] = array();
      }
      $user_activity[$uidcountkey[0]][$user->uid] = new stdClass();
      $user_activity[$uidcountkey[0]][$user->uid]->count = $missing_integer;
      $user_activity[$uidcountkey[0]][$user->uid]->uid = $user->uid;
    }
  }

  foreach ($toskeys as $toskey) {
    if (!array_key_exists('tos', $user_activity)) {
      $user_activity['tos'] = array();
    }
    if (!array_key_exists($user->uid, $user_activity['tos']) or
      is_null($user_activity['tos'][$user->uid])
    ) {

      $user_activity['tos'][$user->uid] = new stdClass();
      $user_activity['tos'][$user->uid]->tos_accepted = '';
      $user_activity['tos'][$user->uid]->tos_version = '';
      $user_activity['tos'][$user->uid]->tos_revision = '';
      $user_activity['tos'][$user->uid]->tos_revision_date = '';
      $user_activity['tos'][$user->uid]->uid = $user->uid;
    }
    if (is_null($user_activity['tos'][$user->uid]->{$toskey[0]})) {
      $user_activity['tos'][$user->uid]->{$toskey[0]} = '';
    }
  }

  // have all the tids, now get the term data and set the report values:
  # terms of service.
  if (count($used_tids) > 0) {
    $sql = sprintf("SELECT tid,name from taxonomy_term_data where tid in (%s)",
      implode(',', array_keys($used_tids)));
    $result = db_query($sql);
    $values = array();
    foreach ($result as $record) {
      $values[$record->tid] = $record;
    }
    $tid_terms = $values;
    foreach ($foreignidkeys as $foreignidkey) {
      set_tid_property($account, $foreignidkey[0], $tid_terms);
    }
  }
  return $account;
}

/*
 * Build an User Activity CSV report.  Gets the users, loads the profiles, filters them by the SNE/SLT dropdown,
 * and by state, then gets the user activty statistics and legal terms of service data, then calls the routine
 * to create the report from the data.
 */
function build_activity_report_csv($state_tid, $date_range, &$usergroups) {
  $users = get_users_for_user_groups($usergroups);

  $user_profiles = user_load_multiple(array_keys($users));
  $user_profiles = filter_users_by_state($user_profiles, $state_tid);
  if (count($user_profiles) == 0) {
    return NULL;
  }

  $user_activity = get_user_activity(array_keys($users), $date_range);
  $user_activity['user_profiles'] = $user_profiles;
  if (count($user_activity) == 0) {
    return NULL;
  }
  $user_profiles = NULL;
  unset($user_profiles); //memory management

  $file_data = create_user_activity_from_data($user_activity);
  $user_activity = NULL;
  unset($user_activity); //memory management

  return $file_data;
}

/**
 * Returns the report headers.
 *
 * @return array
 */
function set_user_activity_report_columns() {
  $csv_header = array(
    "First Name",
    "Last Name",
    "Email",
    "Title",
    "State",
    "District",
    "School",
    "Grade(s)",
    "Subject(s)",
    "School Population(s)",
    "Is SLT Member",
    "Is SNE Member",
    "Role",
    "Date Created",
    "Last Login",
    "Date of Terms of Service",
    "Version of Terms of Service Accepted",
    "Date of Terms of Service Version",
    "# of Resources Viewed by User",
    "# of Resources Downloaded by User",
    "# of Resources Favorited by User",
    "# of Resources Rated by User",
    '# of User\'s Ratings Marked Helpful by Others',
    '# of Topic Forums Viewed by User',
    '# of Resource Forums Participated by User',
    '# of Topic Forums Participated by User',
    '# of Resource Forum Discussions Created by User',
    '# of Topic Forum Discussions Created by User',
    '# of Resource Forum Posts Created by User',
    '# of Topic Forum Posts Created by User',
    '# of Topic Forum Discussions Deleted by User',
    '# of Resource Forum Discussions Deleted by User',
    '# of User\'s Forum Posts Recommended by Others',
    '# of Others\' Forum Posts Recommended by User',
    '# of Temporary Public Links Generated by User',
    '# of Resources For Which User Generated Temporary Public Links',
    '# of GK Reviews Completed by User',
    '# of QC Reviews Completed by User',
    '# of Arbitration Reviews Completed by User',
    '# of Resources Contributed by User',
    '# of Resources Contributed by User that are Posted',
    '# of Resources Contributed by User that are Posted with Distinction',
    '# of Flagged Resources Removed by User through Moderation',
    '# of Flagged Resources Resolved by User through Moderation',
    '# of Flagged Resource Reviews Removed by User through moderation',
    '# of Flagged Resource Reviews Resolved by User through moderation',
    '# of Flagged Forum Discussions Removed by User through moderation',
    '# of Flagged Forum Posts Removed by User through moderation',
    '# of Resource Ratings Created by User that were Flagged',
    '# of Forum discussions created by User that were Flagged',
    '# of Forum Posts created by User that were Flagged',
    '# of Resources Flagged by User',
    "# of Resource Reviews Flagged by User",
    '# of Forum Posts and Discussions Flagged by User',
    '# of  Resources Contributed by User that were Flagged',
  );
  return $csv_header;
}
