<?php
/**
 * CSV Report filter form.
 */
function sbac_csv_report_user_activity_form($form, &$form_state) {
  $form = array();

  // Make sure to load this after autocomplete.js
  // @see sbac_report.csv.js
//  $form['#attached']['js'] = array(
//    drupal_get_path('module', 'sbac_report') .
//    '/js/sbac_report.csv.js' => array('weight' => 99),
//  );

  $form['state'] = array(
    '#type' => 'select',
    '#title' => t('Choose a state'),
    '#options' => sbac_report_state_options(),
    '#multiple' => FALSE,
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

  $form['user_sne_slt_radio']['sne-slt-filter'] = array(
    '#type' => 'radios',
    '#title' => t('SNE/SLT Filter'),
    '#description' => t('Filter results by SNE/SLT'),
    '#default_value' => variable_get('sne-slt-filter', 2),
    '#options' => array(
      t('SNE'),
      t('SLT'),
      t('Both SNE and SLT'),
    ),

  );
//  $form['user_group_dropdown'] = array(
//    '#type' => 'markup',
//    '#markup' => theme('sbac_report_user_group_dropdown',
//      array('user_group_options' => $user_group_options,
//      )
//    ),
//  );
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
  );

  $form['#validate'][] = 'sbac_csv_report_user_activity_form_validate';

  return $form;
}

/**
 * CSV Report: form validate.
 */
function sbac_csv_report_user_activity_form_validate($form, &$form_state) {
  if (false) {
    // TODO: validate csv form
  }
}

/**
 * CSV Report: Form submit.
 * Store in SESSION:
 * $_SESSION['sbac_report'] = array(
 *   'state' => array('name' => 'California', 'tid' => 123),
 *   'date_range' => array('range' => '20130515--20140515'),
 * );
 */

function sbac_csv_report_user_activity_export_form_submit($form, &$form_state) {
  // State.
  if ($form_state) {

    $state_tid = $form_state['values']['state'];
    $_SESSION['sbac_report']['state']['tid'] = $state_tid;
    if (!is_numeric($state_tid) && $state_tid == 'all') {
      $_SESSION['sbac_report']['state']['name'] = 'all';
    }
    else {
      $state_options = $form['state']['#options'];
      $_SESSION['sbac_report']['state']['name'] = $state_options[$state_tid];
    }

    // Time range.
    $_SESSION['sbac_report']['date_range1']['range'] = $form_state['values']['date_range1'];

    // user groups.
    $_SESSION['sbac_report']['usergroups']['user_ids'] = $form_state['values']['user_group_dropdown'];
    $_SESSION['sbac_report']['sne-slt-filter']['filter'] = $form_state['values']['sne-slt-filter'];
  }
  # todo: set these above rather than retrieve them again.
  $state_tid1 = sbac_report_get_session_value('state', 'tid');
  $date_range1 = sbac_report_get_session_value('date_range1', 'range');
  $usergroups = sbac_report_get_session_value('usergroups', 'user_ids');
  $snefilter = sbac_report_get_session_value('sne-slt-filter', 'filter');

  // dump the csv file here:
  $csv_activity_report_result = build_activity_report_csv($state_tid1, $date_range1, $usergroups, $snefilter);
  // output the csv for download.

  if ($csv_activity_report_result == null) {
    $_SESSION['sbac_report']['error_message'] = "<div> No data exists for the filters you have selected.  Please choose a new combination of filters and attempt your export again. </div>";
    $_SESSION['sbac_report']['active_tab'] = 1;
    return; // report did not contain any data.
  }
  $_SESSION['sbac_report']['error_message'] = '';
  $_SESSION['sbac_report']['active_tab'] = 1;
  // _cex exits and does not return.
  _cex_download($csv_activity_report_result, 'output.csv');
  // _cex exits and does not return.
}

function get_users_for_user_groups($usergroups)
{
  $usergroups = implode(',',$usergroups);
// The below statement doesn't work, where usergroups is passed as a string or an array.
//  $sql = "select * from users as u join users_roles as ur on u.uid = ur.uid where ur.rid in :stuff";
//  $result = db_query($sql,
//    array(
//      ':stuff' => $usergroups,
//    )
//  );
  // done this way because the prepared statement didn't work:
  // todo make comma separated list work here or escape string.
  $sql = "select * from users as u join users_roles as ur on u.uid = ur.uid where ur.rid in ($usergroups)";
  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->uid] = $record;
  }

  return $values;
}

function get_user_activity($users, $date_range)
{
  function count_with_users_query($sql_template, $users, $from_date=null, $to_date=null)//$parameters=null)
  {
    // done this way because the prepared statement didn't work passing array or comma separated string.
    // TODO: make prepared statement work here, or escape string???

    if ($from_date && $to_date) {
      $sql = sprintf($sql_template,$users,'%Y%m%d',$from_date,$to_date);
    }
    else {
      $sql = sprintf($sql_template,$users);
    }
    $result = db_query($sql);
    $values = array();
    foreach ($result as $record) {
      $values[$record->uid] = $record;
    }

    return $values;
  }

  $users = implode(',',$users);
  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  # resources viewed
  $sql = "select count(nid) as count, uid From node_user_paradata where uid in (%s) group by uid";
  $user_activity['resources_viewed'] = count_with_users_query($sql, $users);
  # resouces downloaded
  # not ready: select * from field_ass where uid = 372;

  # resources reviewed/rated
  $sql = "select count(id) as count, uid from eck_review where status = 1 and uid in (%s) group by uid";
  $user_activity['resources_reviewed'] = count_with_users_query($sql, $users);

  # resources contributed:
  $sql = "select count(nid) as count, uid from node where type = 'resource' and uid in (%s) group by uid";
  $user_activity['resources_contributed'] = count_with_users_query($sql, $users);

  # GC Review accepted on contributed resource:
  $sql = "select count(id) as count, uid from eck_feedback where
    type = 'gate_keeper' and status = 1 and completed = 1 and met_criteria = 1 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s') BETWEEN %s AND %s group by uid";


  $user_activity['resources_viewed'] = count_with_users_query($sql, $users, $from_date, $to_date);
  //  array(':from_date' => $from_date, ':to_date' => $to_date));

  # GC Review accepted on contributed resource:
  $sql = "select count(id) as count, uid from eck_feedback where type = 'gate_keeper' and status = 1 and completed = 1 and
    met_criteria = 0 and uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['gc_reviews_accepted_on_contributed_resources'] = count_with_users_query($sql, $users, $from_date, $to_date);
//    array(':from_date' => $from_date, ':to_date' => $to_date));

  # GC Reviews completed:
  $sql = "select count(id) as count, uid from eck_feedback where type = 'gate_keeper' and status = 1 and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['gc_reviews_completed'] = count_with_users_query($sql, $users, $from_date, $to_date);
//    array(':from_date' => $from_date, ':to_date' => $to_date));

  # QC Reviews completed:
  $sql = "select count(id) as count, uid from eck_feedback where type = 'qx' and status = 1 and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['qc_reviews_completed'] = count_with_users_query($sql, $users, $from_date, $to_date);
  //    array(':from_date' => $from_date, ':to_date' => $to_date));

  # Poster Reviews completed:
  $sql = "select count(id) as count, uid from eck_feedback where type = 'post' and status = 1 and completed = 1 and
    uid in (%s) and
    DATE_FORMAT((DATE_ADD('19700101', INTERVAL created SECOND) + INTERVAL -25200 SECOND), '%s')
    BETWEEN %s AND %s group by uid";
  $user_activity['poster_reviews_completed'] = count_with_users_query($sql, $users, $from_date, $to_date);
  //    array(':from_date' => $from_date, ':to_date' => $to_date));

  # Contributed resources posted
  $sql = "select count(nid) as count, uid from node where nid in(select nid from workbench_moderation_node_history where
    state = 'published') and uid in (%s) group by uid";
  $user_activity['contributed_resources_posted'] = count_with_users_query($sql, $users);

  # Contributed resources posted with distinction
  $sql = "select count(nid) as count, uid from node where sticky = 1 and nid in(select nid from workbench_moderation_node_history
    where state = 'published') and uid in (%s) group by uid";
  $user_activity['contributed_resources_posted_with_distinction'] = count_with_users_query($sql, $users);

  # Contributed resources reviewed and returned
  $sql = "select count(nid) as count, uid from node where nid in( select nid from workbench_moderation_node_history where
  state = 'rejected') and uid in (%s) group by uid";
  $user_activity['contributed_resources_reviewed_and_returned'] = count_with_users_query($sql, $users);

  # terms of service.
  $sql = "SELECT la.uid,la.accepted as 'tos-accepted',lc.version as 'tos-version',lc.revision as 'tos-revision',lc.date as 'tos-revision-date'
          FROM legal_conditions as lc join legal_accepted as la on lc.version=la.version
          WHERE uid in (%s)";
  $sql = sprintf($sql,$users);
  $result = db_query($sql);
  $values = array();
  foreach ($result as $record) {
    $values[$record->uid] = $record;
  }
  $user_activity['tos'] = $values;

  return $user_activity;
}

function create_user_activity_from_data($user_activity)
{
  function format_value_field(&$row, $field, $separator, $subseparator, $quote_arrays, $subquote)
  {
    //reset($array); $first =  key($array);
    $count = count($field['und']); $ix = 0;
    if ($count > 1 and $quote_arrays)  { $row .= $subquote; }
    foreach ($field['und'] as $array_value) {
      $value = $array_value['value'];
      $row .= $value . $subseparator;
      $ix++;
      if ($ix == $count) {
        $row = substr($row, 0, -1);
      } // reduce length by one removing the last sub-separator
    }
    if ($count > 1 and $quote_arrays)  { $row .= $subquote; }
    $row .= $separator;
  }

  $separator = ', ';
  $quote_arrays = true;
  $subseparator = ';';
  $subquote = "'";

  ksort($user_activity['user_profiles']);

  $fieldkeys = array();
  $foreignidkeys = array();
  $stringkeys = array();
  $uidcountkeys = array();
  $toskeys = array();
  validate_and_fill_out_user_activity($user_activity, $fieldkeys, $foreignidkeys, $stringkeys, $uidcountkeys, $toskeys);

  $titles = '';
  foreach ($fieldkeys as $fieldkey) { $titles .= $fieldkey[1].$separator; }
  foreach ($foreignidkeys as $foreignidkey) { $titles .= $foreignidkey[1].$separator; }
  foreach ($stringkeys as $stringkey) { $titles .= $stringkey[1].$separator; }
  foreach ($uidcountkeys as $uidcountkey) { $titles .= $uidcountkey[1].$separator; }
  foreach ($toskeys as $toskey) { $titles .= $toskey[1].$separator; }
  $titles = substr($titles, 0, -1);
  $titles .= "\r\n";

  $csv = $titles;
  $count = count($user_activity['user_profiles']); $ix = 0;

  foreach ($user_activity['user_profiles'] as $user_profile) {
    $uid = $user_profile->{'uid'};
    $row = '';
    foreach ($fieldkeys as $fieldkey) {
      format_value_field($row, $user_profile->{$fieldkey[0]}, $separator, $subseparator, $quote_arrays, $subquote);
    }
    foreach ($foreignidkeys as $foreignidkey) {
      // tid is replaced by the actual value in the value field.
      format_value_field($row, $user_profile->{$foreignidkey[0]}, $separator, $subseparator, $quote_arrays, $subquote);
    }
    foreach ($stringkeys as $stringkey) {
      $row .= $user_profile->{$stringkey[0]} . $separator;
    }
    foreach ($uidcountkeys as $uidcountkey) {
      $row .= $user_activity[$uidcountkey[0]][$uid]->count . $separator;
    }
    foreach ($toskeys as $toskey) {
      $row .=  $user_activity['tos'][$uid][$toskey[0]] . $separator;
    }

    if (++$ix == $count) { $row = substr($row, 0, -1); } // reduce length by one removing the last separator

    $csv .= $row."\r\n";
  }
  return $csv;
}

function validate_and_fill_out_user_activity(&$user_activity, &$fieldkeys, &$foreignidkeys, &$stringkeys, &$uidcountkeys, $toskeys)
{
  // loop through all values and make sure 0's and '' are used as placeholders for missing values.
//  $titles =  'first-name, last-name, state, district,school, grade,subject, school-population, email,'.
//    ' is-slt, is-sne, date-created, last-access, last-login, '.
//    ' date-of-terms-of-service, version-of-terms-of-service, date-of-service-version,'.
//    ' resources-viewed, resources-reviewed-rated, resources-contributed,'.
//    ' gk-reviews-accepted-on-contributed-resources, gk-reviews-returned-on-contributed-resources,'.
//    ' contributed-resources-posted, contributed-resources-posted-with-distinction, contributed-resources-reviewed-and-returned'.
//    ' gk-reviews-completed, qc-reviews-completed, posting-reviews-completed'
//    ."\r\n";

  array_push($fieldkeys, array('field_first_name', 'First Name'));
  array_push($fieldkeys, array('field_last_name', 'Last Name'));
  array_push($fieldkeys, array('field_sne_member', 'Is SNE Member'));
  array_push($fieldkeys, array('field_slt_member', 'Is SLT Member'));
  array_push($fieldkeys, array('field_district_name', 'District'));
  array_push($foreignidkeys, array('field_state', 'State'));
  array_push($foreignidkeys, array('field_grade_level_s_', 'Grade(s)'));
  array_push($foreignidkeys, array('field_subject_s_', 'Subject(s)'));
  array_push($foreignidkeys, array('field_special_populations', 'School Population(s)'));

  array_push($stringkeys, array('mail', 'Email'));
  array_push($stringkeys, array('created','Date Created'));
  array_push($stringkeys, array('access','Last Access'));
  array_push($stringkeys, array('login','Last Login'));

  array_push($uidcountkeys, array('resources_viewed','Resources Viewed'));
  array_push($uidcountkeys, array('resources_reviewed', 'Resources Reviewed'));
  array_push($uidcountkeys, array('resources_contributed', 'Resources Contributed'));
  array_push($uidcountkeys, array('gc_reviews_accepted_on_contributed_resources', 'GK Reviews Accepted on Contriubted Resources'));
  array_push($uidcountkeys, array('gc_reviews_completed', 'GK Reviews Completed'));
  array_push($uidcountkeys, array('qc_reviews_completed', 'QC Reviews Completed'));
  array_push($uidcountkeys, array('poster_reviews_completed', 'Poster Reviews Completed'));
  array_push($uidcountkeys, array('contributed_resources_posted', 'Contributed Resources Posted'));
  array_push($uidcountkeys, array('contributed_resources_posted_with_distinction', 'Contributed Resources Posted with Distinction'));
  array_push($uidcountkeys, array('contributed_resources_reviewed_and_returned', 'Contributed Resources Reviewed and Returned'));

  array_push($toskeys, array('tos-accepted', 'Date TOS Accepted'));
  array_push($toskeys, array('tos-version', 'TOS Version'));
  array_push($toskeys, array('tos-revision', 'TOS Revision'));
  array_push($toskeys, array('tos-revision-date', 'Date of TOS Revision'));

  function format_value_property(&$user_profile, $fieldkey, $missing_string) {
    if (!property_exists($user_profile,$fieldkey)) {
      $user_profile->{$fieldkey} = array();
    }
    if (is_null($user_profile->{$fieldkey}['und'])) {
      $user_profile->{$fieldkey}['und'] = array();
      $user_profile->{$fieldkey}['und'][0] = array();
      $user_profile->{$fieldkey}['und'][0]['value'] = $missing_string;
    }
    $ix = 0;
    foreach ($user_profile->{$fieldkey}['und'] as $field) {
      if (is_null($user_profile->{$fieldkey}['und'][0]['value'])) {
        $user_profile->{$fieldkey}['und'][$ix]['value'] = $missing_string;
      }
      $ix++;
    }
  }
  function format_tid_property(&$user_profile, $fieldkey, $missing_string, &$used_tids) {
    // todo: look up the actual value in the foreign table, replace the tid with the actual value in the value field.
    if (!property_exists($user_profile,$fieldkey)) {
      $user_profile->{$fieldkey} = array();
    }
    if (is_null($user_profile->{$fieldkey}['und'])) {
      $user_profile->{$fieldkey}['und'] = array();
      $user_profile->{$fieldkey}['und'][0] = array();
      $user_profile->{$fieldkey}['und'][0]['tid'] = $missing_string;
      $user_profile->{$fieldkey}['und'][0]['value'] = $missing_string;
    }
    $ix = 0;
    foreach ($user_profile->{$fieldkey}['und'] as &$field) {
      if (is_null($field['tid'])) {
        $field['tid'] = $missing_string;
        $field['value'] = $missing_string;
      }
      // look up the value in the foreign table.
      if ($field['tid'] != $missing_string) {
        $used_tids[$field['tid']] = $field['tid'];
      }
      $ix++;
    }
  }
  function set_tid_property(&$user_profile, $fieldkey, &$tid_terms) {
    // todo: look up the actual value in the foreign table, replace the tid with the actual value in the value field.

    $ix = 0;
    foreach ($user_profile->{$fieldkey}['und'] as &$field) {
      // look up the value in the foreign table.
      if ($field['tid'] != 0) {
        $field['value'] = $tid_terms[$field['tid']]->name;
      }
      $ix++;
    }
  }
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
      if (!property_exists($user_profile,$stringkey[0])) {
        $user_profile->{$stringkey[0]} = $missing_string;
      }
    }
    foreach ($uidcountkeys as $uidcountkey) {
      if (is_null($user_activity[$uidcountkey[0]][$uid])) {
        $user_activity[$uidcountkey[0]][$uid] = new stdClass();
        $user_activity[$uidcountkey[0]][$uid]->count = $missing_integer;
        $user_activity[$uidcountkey[0]][$uid]->uid = $uid;
      }
    }
    if (is_null($user_activity['tos'][$uid])) {
      $user_activity['tos'][$uid]['uid'] = $uid;
      foreach ($toskeys as $toskey) {
        $user_activity['tos'][$uid][$toskey[0]] = "";
      }
    }
  }

  // have all the tids, now get the term data and set the report values:
  # terms of service.
  $sql = sprintf ("SELECT tid,name from taxonomy_term_data where tid in (%s)",
    $usergroups = implode(',',array_keys($used_tids)));
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


function build_activity_report_csv($state_tid, $date_range, $usergroups, $sne_slt_filter)
{
  $users = get_users_for_user_groups($usergroups);

  $user_profiles = user_load_multiple(array_keys($users));
  $user_profiles = filter_users_by_sne_slt($user_profiles, $sne_slt_filter);
  $user_profiles = filter_users_by_state($user_profiles, $state_tid);
  if (count($user_profiles) == 0) {
    return null;
  }

  $user_activity = get_user_activity(array_keys($users), $date_range);
  $user_activity['user_profiles']=$user_profiles;
  $file_data = create_user_activity_from_data($user_activity);

  return $file_data;
}

function filter_users_by_sne_slt($user_profiles, $sne_slt_filter)
{
  // sne filter: 0=>sne, 1=>slt, 2=> both
  $filtered_user_profiles = array();
  if ($sne_slt_filter == 2) { // both, nothing to filter.
    return $user_profiles;
  }
  foreach ($user_profiles as $user_profile) {
    if (($sne_slt_filter == 0 && $user_profile->field_sne_member && $user_profile->field_sne_member['und'][0]['value'] == '1') ||
      ($sne_slt_filter == 1 && $user_profile->field_slt_member && $user_profile->field_slt_member['und'][0]['value'] == '1')) {
      $filtered_user_profiles[$user_profile->uid] = $user_profile;
    }
  }
  return $filtered_user_profiles;
}

function filter_users_by_state($user_profiles, $state_tid)
{
  // sne filter: 0=>sne, 1=>slt, 2=> both
  $filtered_user_profiles = array();
  if ($state_tid == 'all') { // both, nothing to filter.
    return $user_profiles;
  }
  foreach ($user_profiles as $user_profile) {
    if ($user_profile->field_state['und'] &&
      $user_profile->field_state['und'][0]['value'] == $state_tid) {
      $filtered_user_profiles[$user_profile->uid] = $user_profile;
    }
  }
  return $filtered_user_profiles;
}
