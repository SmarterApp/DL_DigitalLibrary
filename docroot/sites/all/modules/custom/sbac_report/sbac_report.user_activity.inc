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
  $user_group_options = sbac_report_user_group_options();

  $form['user_group_dropdown'] = array(
    '#type' => 'select',
    '#title' => t('Choose User Groups'),
    '#options' => $user_group_options,
    '#attributes' => array('class' => array('chosen-widget')),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_get_default_usergroup(),
    '#required' => TRUE,
  );

  $sne_slt_options = sbac_report_sne_slt_options();

  $form['sne_slt_filter'] = array(
    '#type' => 'select',
    '#title' => t('Filter for SNE or SLT Members'),
    '#options' => $sne_slt_options,
    '#attributes' => array('class' => array('chosen-widget')),
    '#multiple' => TRUE,
    '#default_value' => sbac_report_get_default_sne_slt(),
    '#required' => TRUE,
  );

  $date_options = sbac_report_date_range_options();
  $session_date_range = sbac_report_get_session_value('date_range', 'range');

  // If there was no date range stored in SESSION.
  // Default to the "Last 30 Days".
  if (empty($session_date_range)) {
    $session_date_range = $date_options['Last 30 Days'];
    $date_display = t('Last 30 Days');
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

  if (FALSE) {
    // TODO: validate csv form
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
  ini_set('memory_limit', '512M');
  // State.
  if ($form_state) {

    $state_tid = $form_state['values']['state'];
    $_SESSION['sbac_report']['state']['tid'] = $state_tid;
//    if (!is_numeric($state_tid) && !is_array($state_tid) && $state_tid == 'all') {
//      $_SESSION['sbac_report']['state']['name'] = 'all';
//    }
//    else {
//      $state_options = $form['state']['#options'];
//      $_SESSION['sbac_report']['state']['name'] = $state_options[$state_tid];
//    }

    // Time range.
    $_SESSION['sbac_report']['date_range1']['range'] = $form_state['values']['date_range1'];

    // user groups.
    $_SESSION['sbac_report']['usergroups']['user_ids'] = $form_state['values']['user_group_dropdown'];
    $_SESSION['sbac_report']['sne-slt-filter']['filter'] = $form_state['values']['sne_slt_filter'];
  }
  # todo: set these above rather than retrieve them again.
  $state_tid1 = sbac_report_get_session_value('state', 'tid');
  $date_range1 = sbac_report_get_session_value('date_range1', 'range');
  $usergroups = sbac_report_get_session_value('usergroups', 'user_ids');
  $snefilter = sbac_report_get_session_value('sne-slt-filter', 'filter');

  if (count($usergroups) == 0) {
    $_SESSION['sbac_report']['error_message'] = SBAC_REPORT_FILTER_ERROR;
    $_SESSION['sbac_report']['active_tab'] = 1;
    return; // report did not contain any data.
  }
  // dump the csv file here:
  $csv_activity_report_result = build_activity_report_csv($state_tid1, $date_range1, $usergroups, $snefilter);
  // output the csv for download.
  $state_tid1 = NULL;
  unset($state_tid1); //memory management
  $date_range1 = NULL;
  unset($date_range1); //memory management
  $usergroups = NULL;
  unset($usergroups); //memory management
  $snefilter = NULL;
  unset($snefilter); //memory management

  if ($csv_activity_report_result == NULL) {
    $_SESSION['sbac_report']['error_message'] = SBAC_REPORT_FILTER_ERROR;
    $_SESSION['sbac_report']['first_time'] = 1;
    return; // report did not contain any data.
  }
  $_SESSION['sbac_report']['error_message'] = '';
  $_SESSION['sbac_report']['first_time'] = 0;
  gc_enable();
  gc_collect_cycles();
  gc_disable();
  // _cex exits and does not return in order to force a download by the browser.
  _cex_download($csv_activity_report_result, 'output.csv');
  // _cex exits and does not return.
}

/*
 * Get the user groups for a given user group.  Note that a query with 'in (%s)' in the string doesn't work
 * properly with Drupals perpared statement support.
 *
 */
function get_users_for_user_groups(&$usergroups_ids) {
  // look for the aggregated admins option "admins"
  if (array_key_exists(1, $usergroups_ids)) {
    // get the admins:
    $admins = sbac_report_user_group_admins();
    unset($usergroups_ids[1]);
    foreach ($admins as $key => $value) {
      $usergroups_ids[$key] = $key;
    }
  }
  // look for the 'all' option being set:
  else {
    if (array_key_exists(0, $usergroups_ids)) {
      $admins = sbac_report_user_group_admins();
      foreach ($admins as $key => $value) {
        $usergroups_ids[$key] = $key;
      }
      $all = sbac_report_user_group_options();
      foreach ($all as $key => $value) {
        $usergroups_ids[$key] = $key;
      }
    }
  }

  $usergroups = implode(',', $usergroups_ids);

// todo: get prepared statement to work with 'in (%s)'.

// The below statement doesn't work, where usergroups is passed as a string or an array.
//  $sql = "select * from users as u join users_roles as ur on u.uid = ur.uid where ur.rid in :stuff";
//  $result = db_query($sql,
//    array(
//      ':stuff' => $usergroups,
//    )
//  );
  // done this way because the prepared statement didn't work:
  $sql = "select * from users as u join users_roles as ur on u.uid = ur.uid where ur.rid in ($usergroups)";
  $usergroups = NULL;
  unset($usergroups); //memory management

  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->uid] = $record;
  }

  return $values;
}

/*
 * Local function that handles all the query logic for the count queries.  It injects the user list and optionally
 * a from/to date into the query.  It then performs the query and returns the resulting records in a hash by user
 * id (uid).
*/
function count_with_users_query($sql_template, $users, $from_date = NULL, $to_date = NULL) {
  // done this way because the prepared statement didn't work passing array or comma separated string.
  // TODO: make prepared statement work here, or escape string???

  if ($from_date && $to_date) {
    $sql = sprintf($sql_template, $users, '%Y%m%d', $from_date, $to_date);
  }
  else {
    $sql = sprintf($sql_template, $users);
  }
  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->uid] = $record;
  }

  return $values;
}

/*
 * Get the user activity on resources and reviews.  There are 12 different statistics that are retrieved by this
 * routine, each one a count of something.  This routine also gets the terms of service legal information.
 */
function get_user_activity($users, $date_range) {
  $users = implode(',', $users); // make the users a comma separated list.
  // extract the date range into a from and to date
  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  // Count queries:
  # resources viewed
  $sql = "select count(nid) as count, uid From node_user_paradata where uid in (%s) group by uid";
  $user_activity['resources_viewed'] = count_with_users_query($sql, $users);
  # resouces downloaded
  # not ready: select * from field_ass where uid = 372;

  # resources reviewed/rated
  $sql = "select count(id) as count, uid,created from eck_review where status = 1 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['resources_reviewed'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # resources contributed:
  $sql = "select count(distinct(n.nid)) as count, n.uid, n.created from node as n join workbench_moderation_node_history as wmnh on n.nid = wmnh.nid
    where n.type = 'resource' and n.uid in (%s) and wmnh.state!='draft' and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL n.created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by n.uid";
  $user_activity['resources_contributed'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Resources Viewed:
  $sql = "select count(id) as count, uid,created from eck_feedback where
    type = 'gate_keeper' and status = 1 and completed = 1 and met_criteria = 1 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['resources_viewed'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # GK Reviews completed:
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'gate_keeper' and status = 1 and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['gc_reviews_completed'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # QC Reviews completed:
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'qc' and status = 1 and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['qc_reviews_completed'] = count_with_users_query($sql, $users, $from_date, $to_date);
  //    array(':from_date' => $from_date, ':to_date' => $to_date));

  # Poster Reviews completed:
  $sql = "select count(id) as count, uid,created from eck_feedback where type = 'post' and status = 1 and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['poster_reviews_completed'] = count_with_users_query($sql, $users, $from_date, $to_date);
  //    array(':from_date' => $from_date, ':to_date' => $to_date));

  # Resources with GK Review accepted on contributed resource:
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and nid in (
    select node_id from eck_feedback where type = 'gate_keeper' and status = 1 and completed = 1 and
    met_criteria = 1  and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid)";
  $user_activity['gc_reviews_accepted_on_contributed_resources'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Resources with GK Review returned on contributed resource:
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and nid in (
    select node_id from eck_feedback where type = 'gate_keeper' and status = 1 and completed = 1 and
    met_criteria = 0 and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid)";
  $user_activity['gc_reviews_returned_on_contributed_resources'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Contributed resources posted
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and nid in (select nid from workbench_moderation_node_history where
    state = 'published') and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['contributed_resources_posted'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Contributed resources posted with distinction
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and type = 'resource' and sticky = 1 and nid in (select nid from workbench_moderation_node_history
    where state = 'published') and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['contributed_resources_posted_with_distinction'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Contributed resources reviewed and returned
  $sql = "select count(nid) as count, uid, created from node where uid in (%s) and nid in (select nid from workbench_moderation_node_history where
  state = 'rejected')  and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['contributed_resources_reviewed_and_returned'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # terms of service.
  $sql = "SELECT la.uid,la.accepted as 'tos_accepted',lc.version as 'tos_version',lc.revision as 'tos_revision',lc.date as 'tos_revision_date'
          FROM legal_conditions as lc join legal_accepted as la on lc.version=la.version
          WHERE uid in (%s)";
  $sql = sprintf($sql, $users);
  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->uid] = $record;
  }
  $user_activity['tos'] = $values;

  # Unique Permanent Links Copied
  $sql = "SELECT count(nid) AS count, uid FROM {sbac_share_link_copy_count} WHERE uid IN (%s)
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['unique_permanent_links_copied'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Temporary Links Generated
  $sql = "SELECT count(nid) AS count, uid FROM {sbac_share} WHERE uid IN (%s)
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL create_datetime SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";
  $user_activity['temporary_link_generated'] = count_with_users_query($sql, $users, $from_date, $to_date);

  # Unique Temporary Links Generated
  $sql = "SELECT nid, uid FROM {sbac_share} WHERE uid IN (%s)
          AND DATE_FORMAT((DATE_ADD('19700101', INTERVAL create_datetime SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by nid, uid";
  $user_activity['unique_temporary_link_generated'] = count_with_users_query($sql, $users, $from_date, $to_date);

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
function create_user_activity_from_data($user_activity) {
  $separator = ',';
  $encloseer = '"';
  $quote_arrays = TRUE;
  $subseparator = ';';
  $subquote = "";
  $line_ending = "\r\n";

  ksort($user_activity['user_profiles']);

  $fieldkeys = array();
  $foreignidkeys = array();
  $stringkeys = array();
  $uidcountkeys = array();
  $toskeys = array();

  // get the fields for the report and clean up the data.
  validate_and_fill_out_user_activity($user_activity, $fieldkeys, $foreignidkeys, $stringkeys, $uidcountkeys, $toskeys);

  $titles = '';
  foreach ($fieldkeys as $fieldkey) {
    $titles .= $fieldkey[1] . $separator;
  }
  foreach ($foreignidkeys as $foreignidkey) {
    $titles .= $foreignidkey[1] . $separator;
  }
  foreach ($stringkeys as $stringkey) {
    $titles .= $stringkey[1] . $separator;
  }
  foreach ($uidcountkeys as $uidcountkey) {
    $titles .= $uidcountkey[1] . $separator;
  }
  foreach ($toskeys as $toskey) {
    $titles .= $toskey[1] . $separator;
  }
  $titles = substr($titles, 0, -1);
  $titles .= $line_ending;

  $csv = $titles;
  $titles = NULL;
  unset($titles); //memory management
  $count = count($user_activity['user_profiles']);
  $ix = 0;

  foreach ($user_activity['user_profiles'] as $user_profile) {
    $uid = $user_profile->{'uid'};
    $row = '';
    foreach ($fieldkeys as $fieldkey) {
      $is_date = (array_key_exists(2, $fieldkey) ? $fieldkey[2] == 'date' : FALSE);
      format_value_field($row, $user_profile->{$fieldkey[0]}, $separator, $encloseer,
        $subseparator, $quote_arrays, $subquote, $is_date);
    }
    foreach ($foreignidkeys as $foreignidkey) {
      $is_date = (array_key_exists(2, $foreignidkey) ? $foreignidkey[2] == 'date' : FALSE);
      // tid is replaced by the actual value in the value field.
      format_value_field($row, $user_profile->{$foreignidkey[0]}, $separator, $encloseer,
        $subseparator, $quote_arrays, $subquote, $is_date);
    }

    foreach ($stringkeys as $stringkey) {
      $is_date = (array_key_exists(2, $stringkey) ? $stringkey[2] == 'date' : FALSE);
      if (is_null($user_profile->{$stringkey[0]})) {
        $value = '';
      }
      else {
        if ($is_date) {
          $value = format_date($user_profile->{$stringkey[0]}, 'custom', 'Y-m-d');
        }
        else {
          $value = $user_profile->{$stringkey[0]};
        }
      }
      $row .= $value . $separator;
      $value = NULL;
      unset($value); // memory management
    }
    foreach ($uidcountkeys as $uidcountkey) {
      $row .= $user_activity[$uidcountkey[0]][$uid]->count . $separator;
    }
    $param = array();
    $param['und'] = array();
    $param['und'][0] = array();
    foreach ($toskeys as $toskey) {
      $is_date = (array_key_exists(2, $toskey) ? $toskey[2] == 'date' : FALSE);
      $param['und'][0]['value'] = $user_activity['tos'][$uid]->{$toskey[0]};
      format_value_field($row, $param, $separator, $encloseer,
        $subseparator, $quote_arrays, $subquote, $is_date);
    }

    if (++$ix == $count) {
      $row = substr($row, 0, -1);
    } // reduce length by one removing the last separator

    $csv .= $row . $line_ending;

    $row = NULL;
    unset($row); //memory mangement
  }
  return $csv;
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
function validate_and_fill_out_user_activity(&$user_activity, &$fieldkeys, &$foreignidkeys, &$stringkeys, &$uidcountkeys, &$toskeys) {
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
  array_push($stringkeys, array('created', 'Date Created', 'date'));
  array_push($stringkeys, array('access', 'Last Access', 'date'));
  array_push($stringkeys, array('login', 'Last Login', 'date'));

  array_push($uidcountkeys, array('resources_viewed', 'Resources Viewed'));
  array_push($uidcountkeys, array('resources_reviewed', 'Resources Reviewed/Rated'));
  array_push($uidcountkeys, array('resources_contributed', 'Resources Contributed'));
  array_push($uidcountkeys, array(
    'gc_reviews_accepted_on_contributed_resources',
    'GK Reviews Accepted on Contributed Resources'
  ));
  array_push($uidcountkeys, array(
    'gc_reviews_returned_on_contributed_resources',
    'GK Reviews Returned on Contributed Resources'
  ));
  array_push($uidcountkeys, array('gc_reviews_completed', 'GK Reviews Completed'));
  array_push($uidcountkeys, array('qc_reviews_completed', 'QC Reviews Completed'));
  array_push($uidcountkeys, array('poster_reviews_completed', 'Posting Reviews Completed'));
  array_push($uidcountkeys, array('contributed_resources_posted', 'Contributed Resources Posted'));
  array_push($uidcountkeys, array(
    'contributed_resources_posted_with_distinction',
    'Contributed Resources Posted with Distinction'
  ));
  array_push($uidcountkeys, array(
    'contributed_resources_reviewed_and_returned',
    'Contributed Resources Reviewed and Returned'
  ));

  array_push($toskeys, array('tos_accepted', 'Date of Terms of Service', 'date'));
  array_push($toskeys, array('tos_version', 'Version of Terms of Service Accepted'));
  //array_push($toskeys, array('tos_revision', 'Terms of Service Version'));
  array_push($toskeys, array('tos_revision_date', 'Date of Terms of Service Version', 'date'));

  // replace missing values with ' ' or 0
  $missing_string = ' ';
  $missing_integer = 0;

  $used_tids = array();
  foreach ($user_activity['user_profiles'] as $user_profile) {
    $uid = $user_profile->{'uid'};
    foreach ($fieldkeys as $fieldkey) {
      format_value_property($user_profile, $fieldkey[0], $missing_string);
    }
    // build taxonomy index table while validating. grab all the ids then
    // load them all in one has table for quick reference.
    foreach ($foreignidkeys as $foreignidkey) {
      format_tid_property($user_profile, $foreignidkey[0], $missing_string, $used_tids);
    }

    foreach ($stringkeys as $stringkey) {
      if (!property_exists($user_profile, $stringkey[0])) {
        $user_profile->{$stringkey[0]} = $missing_string;
      }
    }
    foreach ($uidcountkeys as $uidcountkey) {
      if (!array_key_exists($uidcountkey[0], $user_activity) or
        !array_key_exists($uid, $user_activity[$uidcountkey[0]]) or
        is_null($user_activity[$uidcountkey[0]][$uid])
      ) {
        if (!array_key_exists($uidcountkey[0], $user_activity)) {
          $user_activity[$uidcountkey[0]] = array();
        }
        $user_activity[$uidcountkey[0]][$uid] = new stdClass();
        $user_activity[$uidcountkey[0]][$uid]->count = $missing_integer;
        $user_activity[$uidcountkey[0]][$uid]->uid = $uid;
      }
    }

    foreach ($toskeys as $toskey) {
      if (!array_key_exists('tos', $user_activity)) {
        $user_activity['tos'] = array();
      }
      if (!array_key_exists($uid, $user_activity['tos']) or
        is_null($user_activity['tos'][$uid])
      ) {

        $user_activity['tos'][$uid] = new stdClass();
        $user_activity['tos'][$uid]->tos_accepted = '';
        $user_activity['tos'][$uid]->tos_version = '';
        $user_activity['tos'][$uid]->tos_revision = '';
        $user_activity['tos'][$uid]->tos_revision_date = '';
        $user_activity['tos'][$uid]->uid = $uid;
      }
      if (is_null($user_activity['tos'][$uid]->{$toskey[0]})) {
        $user_activity['tos'][$uid]->{$toskey[0]} = '';
      }
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

    foreach ($user_activity['user_profiles'] as $user_profile) {
      foreach ($foreignidkeys as $foreignidkey) {
        set_tid_property($user_profile, $foreignidkey[0], $tid_terms);
      }
    }
  }
}

/*
 * Build an User Activity CSV report.  Gets the users, loads the profiles, filters them by the SNE/SLT dropdown,
 * and by state, then gets the user activty statistics and legal terms of service data, then calls the routine
 * to create the report from the data.
 */
function build_activity_report_csv($state_tid, $date_range, &$usergroups, $sne_slt_filter) {
  $users = get_users_for_user_groups($usergroups);

  $user_profiles = user_load_multiple(array_keys($users));
  $user_profiles = filter_users_by_sne_slt($user_profiles, $sne_slt_filter);
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

/*
 * Fitler the users by the sne/slt value in the dropdown menu.
 */
function filter_users_by_sne_slt($user_profiles, $sne_slt_filter) {
  // sne filter: 0=>neither, 1=>sne, 2=>slt, 2=>both
  $filtered_user_profiles = array();
// the all condition if it ever gets requested:
//  if (in_array(4, $sne_slt_filter)) { // both, nothing to filter.
//    return $user_profiles;
//  }
  $look_for_both_sne_and_slt = in_array(3, $sne_slt_filter);
  $look_for_slt = in_array(2, $sne_slt_filter);
  $look_for_sne = in_array(1, $sne_slt_filter);
  $look_for_neither = in_array(0, $sne_slt_filter);

  foreach ($user_profiles as $user_profile) {
    if ($look_for_both_sne_and_slt &&
      ($user_profile->field_sne_member && $user_profile->field_sne_member['und'][0]['value'] == '1') &&
      ($user_profile->field_slt_member && $user_profile->field_slt_member['und'][0]['value'] == '1')
    ) { // both
      $filtered_user_profiles[$user_profile->uid] = $user_profile;
    }
    else {
      if ($look_for_slt &&
        ($user_profile->field_sne_member && $user_profile->field_sne_member['und'][0]['value'] == '0') &&
        ($user_profile->field_slt_member && $user_profile->field_slt_member['und'][0]['value'] == '1')
      ) { // slt only.
        $filtered_user_profiles[$user_profile->uid] = $user_profile;
      }
      else {
        if ($look_for_sne &&
          ($user_profile->field_sne_member && $user_profile->field_sne_member['und'][0]['value'] == '1') &&
          ($user_profile->field_slt_member && $user_profile->field_slt_member['und'][0]['value'] == '0')
        ) { // sne only.
          $filtered_user_profiles[$user_profile->uid] = $user_profile;
        }
        else {
          if ($look_for_neither &&
            ((bool) !$user_profile->field_sne_member || $user_profile->field_sne_member['und'][0]['value'] == '0') &&
            ((bool) !$user_profile->field_slt_member || $user_profile->field_slt_member['und'][0]['value'] == '0')
          ) { // niether.
            $filtered_user_profiles[$user_profile->uid] = $user_profile;
          }
        }
      }
    }
  }
  return $filtered_user_profiles;
}

/*
 * Filter out users by states.
 */
function filter_users_by_state($user_profiles, $state_tid) {
  // sne filter: 0=>sne, 1=>slt, 2=> both
  $filtered_user_profiles = array();
  if ($state_tid['all']) { // both, nothing to filter.
    return $user_profiles;
  }
  foreach ($user_profiles as $user_profile) {
    if ($user_profile->field_state['und'] &&
      in_array($user_profile->field_state['und'][0]['tid'], $state_tid)
    ) {
      $filtered_user_profiles[$user_profile->uid] = $user_profile;
    }
  }
  return $filtered_user_profiles;
}
