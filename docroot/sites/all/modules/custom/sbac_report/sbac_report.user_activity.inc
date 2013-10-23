<?php

/**
 * CSV Report: Form submit.
 * Store in SESSION:
 * $_SESSION['sbac_report'] = array(
 *   'state' => array('name' => 'California', 'tid' => 123),
 *   'date_range' => array('range' => '20130515--20140515'),
 * );
 */

function sbac_report_csv_export_form_submit($form, &$form_state) {
  // State.
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

  # todo: set these above rather than retrieve them again.
  $state_tid1 = sbac_report_get_session_value('state', 'tid');
  $date_range1 = sbac_report_get_session_value('date_range1', 'range');
  $usergroups = sbac_report_get_session_value('usergroups', 'user_ids');
  $snefilter = sbac_report_get_session_value('sne-slt-filter', 'filter');

  // dump the csv file here:
  $csv_activity_report_result = build_activity_report_csv($state_tid1, $date_range1, $usergroups, $snefilter);
  // output the csv for download.
  _cex_download($csv_activity_report_result, 'output.csv');

  //echo $csv_activity_report_result;
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
  foreach ($fieldkeys as $fieldkey) { $titles .= $fieldkey.$separator; }
  foreach ($foreignidkeys as $foreignidkey) { $titles .= $foreignidkey.$separator; }
  foreach ($stringkeys as $stringkey) { $titles .= $stringkey.$separator; }
  foreach ($uidcountkeys as $uidcountkey) { $titles .= $uidcountkey.$separator; }
  foreach ($toskeys as $toskey) { $titles .= $toskey.$separator; }
  $titles = substr($titles, 0, -1);
  $titles .= "\r\n";

  $csv = $titles;
  $count = count($user_activity['user_profiles']); $ix = 0;

  foreach ($user_activity['user_profiles'] as $user_profile) {
    $uid = $user_profile->{'uid'};
    $row = '';
    foreach ($fieldkeys as $fieldkey) {
      format_value_field($row, $user_profile->{$fieldkey}, $separator, $subseparator, $quote_arrays, $subquote);
    }
    foreach ($foreignidkeys as $foreignidkey) {
      // tid is replaced by the actual value in the value field.
      format_value_field($row, $user_profile->{$foreignidkey}, $separator, $subseparator, $quote_arrays, $subquote);
    }
    foreach ($stringkeys as $stringkey) {
      $row .= $user_profile->{$stringkey} . $separator;
    }
    foreach ($uidcountkeys as $uidcountkey) {
      $row .= $user_activity[$uidcountkey][$uid]->count . $separator;
    }
    foreach ($toskeys as $toskey) {
      $row .=  $user_activity['tos'][$uid][$toskey] . $separator;
    }

    if (++$ix == $count) { $row = substr($row, 0, -1); } // reduce length by one removing the last separator

    $csv .= $row."\r\n";
  }
  return $csv;
}

function _cex_download( $output, $filename )
{
  header("Pragma: public");
  header("Expires: 0");
  header("Cache-Control: private");
  header("Content-type: application/octet-stream");
  header("Content-Disposition: attachment; filename=$filename");
  header("Accept-Ranges: bytes");
  echo $output;
  exit;
}

function validate_and_fill_out_user_activity(&$user_activity, &$fieldkeys, &$foreignidkeys, &$stringkeys, &$uidcountkeys, $toskeys)
{
  // loop through all values and make sure 0's and '' are used as placeholders for missing values.

  // todo: is terms of service, version of terms of service, date of version

//  $titles =  'first-name, last-name, state, district,school, grade,subject, school-population, email,'.
//    ' is-slt, is-sne, date-created, last-access, last-login, '.
//    ' date-of-terms-of-service, version-of-terms-of-service, date-of-service-version,'.
//    ' resources-viewed, resources-reviewed-rated, resources-contributed,'.
//    ' gk-reviews-accepted-on-contributed-resources, gk-reviews-returned-on-contributed-resources,'.
//    ' contributed-resources-posted, contributed-resources-posted-with-distinction, contributed-resources-reviewed-and-returned'.
//    ' gk-reviews-completed, qc-reviews-completed, posting-reviews-completed'
//    ."\r\n";

  array_push($fieldkeys, 'field_first_name');
  array_push($fieldkeys, 'field_last_name');
  array_push($fieldkeys, 'field_sne_member');
  array_push($fieldkeys, 'field_slt_member');
  array_push($fieldkeys, 'field_district_name');
  array_push($foreignidkeys, 'field_state');
  array_push($foreignidkeys, 'field_grade_level_s_');
  array_push($foreignidkeys, 'field_subject_s_');
  array_push($foreignidkeys, 'field_special_populations');

  array_push($stringkeys, 'mail');
  array_push($stringkeys, 'created');
  array_push($stringkeys, 'access');
  array_push($stringkeys, 'login');

  array_push($uidcountkeys, 'resources_viewed');
  array_push($uidcountkeys, 'resources_reviewed');
  array_push($uidcountkeys, 'resources_contributed');
  array_push($uidcountkeys, 'gc_reviews_accepted_on_contributed_resources');
  array_push($uidcountkeys, 'gc_reviews_completed');
  array_push($uidcountkeys, 'qc_reviews_completed');
  array_push($uidcountkeys, 'poster_reviews_completed');
  array_push($uidcountkeys, 'contributed_resources_posted');
  array_push($uidcountkeys, 'contributed_resources_posted_with_distinction');
  array_push($uidcountkeys, 'contributed_resources_reviewed_and_returned');

  array_push($toskeys, 'tos-accepted');
  array_push($toskeys, 'tos-version');
  array_push($toskeys, 'tos-revision');
  array_push($toskeys, 'tos-revision-date');

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
      format_value_property($user_profile, $fieldkey, $missing_string);
    }
    // build taxonomy index table while validating. grab all the ids then
    // load them all in one has table for quick reference.
    foreach ($foreignidkeys as $foreignidkey) {
      format_tid_property($user_profile, $foreignidkey, $missing_string, $used_tids);
    }

    foreach ($stringkeys as $stringkey) {
      if (!property_exists($user_profile,$stringkey)) {
        $user_profile->{$stringkey} = $missing_string;
      }
    }
    foreach ($uidcountkeys as $uidcountkey) {
      if (is_null($user_activity[$uidcountkey][$uid])) {
        $user_activity[$uidcountkey][$uid] = new stdClass();
        $user_activity[$uidcountkey][$uid]->count = $missing_integer;
        $user_activity[$uidcountkey][$uid]->uid = $uid;
      }
    }
    if (is_null($user_activity['tos'][$uid])) {
      $user_activity['tos'][$uid]['uid'] = $uid;
      foreach ($toskeys as $toskey) {
        $user_activity['tos'][$uid][$toskey] = "";
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
      set_tid_property($user_profile, $foreignidkey, $tid_terms);
    }
  }
}


function build_activity_report_csv($state_tid, $date_range, $usergroups, $sne_slt_filter)
{
  $users = get_users_for_user_groups($usergroups);

  $user_profiles = user_load_multiple(array_keys($users));
  $user_profiles = filter_users_by_sne_slt($user_profiles, $sne_slt_filter);
  $user_profiles = filter_users_by_state($user_profiles, $state_tid);

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
