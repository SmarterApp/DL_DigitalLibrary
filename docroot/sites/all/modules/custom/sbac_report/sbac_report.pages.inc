<?php
/**
 * @file
 * Page callbacks for SBAC Report.
 */

/**
 * Page callback for the report.
 */
function sbac_report_individual() {
  drupal_set_title(t('Usage and Activity Reports'));
  $form = drupal_get_form('sbac_report_individual_form');
  $sne_details = '';
  $contributed_summary = '';
  $contributed_details = '';

  // unset($_SESSION['sbac_report']);
  // Get SESSION values.
  $uid = sbac_report_get_session_value('sne', 'uid');
  $state = sbac_report_get_session_value('state', 'name');
  $date_range = sbac_report_get_session_value('date_range', 'range');

  if (!empty($uid) && !empty($date_range) && !empty($state)) {
    $sne_details = sbac_report_embed_view('sne_details', 'sne_details', $uid, $state);
    // If there are no SNE with the selected state and uid. Display none.
    // @todo: custom message if there's no result.
    if (!empty($sne_details)) {
      $contributed_summary = views_embed_view('contributed_resources', 'resources_summary', $uid, $date_range);
      $contributed_details = views_embed_view('contributed_resources', 'resources_details', $uid, $date_range);
    }
  }

  return theme('sbac_report_individual', array(
      'form' => $form,
      'sne_details' => $sne_details,
      'contributed_summary' => $contributed_summary,
      'contributed_details' => $contributed_details,
    )
  );
}

/**
 * Ajax for the autocomplete SNE textfield.
 */
function sbac_report_sne_autocomplete($string = '') {
  // Get the selected state if there's any.
  $matches = array();

  $rc_role = user_role_load_by_name('resource contributor');
  $rv_role = user_role_load_by_name('resource reviewer');
  $rids = array($rv_role->rid, $rc_role->rid);

  $state = sbac_report_get_session_value('state', 'name');
  if ($state == 'all') {
    $state_condition = '';
  }
  elseif (!empty($state)) {
    $state_condition = "AND (field_data_field_state.field_state_value = '$state')";
  }
  else {
    $matches['none'] = t('Please select a state');
    print drupal_json_encode($matches);
    exit;
  }

  $sql = <<<SQL

  SELECT users.uid AS uid,
    field_data_field_last_name.field_last_name_value as 'last_name',
    field_data_field_first_name.field_first_name_value as 'first_name',
    field_data_field_state.field_state_value as 'state'
  FROM {users} users
  INNER JOIN {users_roles} users_roles ON users.uid = users_roles.uid
  LEFT JOIN {field_data_field_last_name} field_data_field_last_name
    ON users.uid = field_data_field_last_name.entity_id AND (field_data_field_last_name.entity_type = 'user' AND field_data_field_last_name.deleted = '0')
  LEFT JOIN {field_data_field_first_name} field_data_field_first_name
    ON users.uid = field_data_field_first_name.entity_id AND (field_data_field_first_name.entity_type = 'user' AND field_data_field_first_name.deleted = '0')
  LEFT JOIN {field_data_field_state} field_data_field_state
    ON users.uid = field_data_field_state.entity_id AND (field_data_field_state.entity_type = 'user' AND field_data_field_state.deleted = '0')
  LEFT JOIN {field_data_field_sne_member} field_data_field_sne_member
    ON users.uid = field_data_field_sne_member.entity_id AND (field_data_field_sne_member.entity_type = 'user' AND field_data_field_sne_member.deleted = '0')
  WHERE (
    ((field_data_field_first_name.field_first_name_value LIKE :str) OR (field_data_field_last_name.field_last_name_value LIKE :str))
    AND (users.status <> '0')
    AND (users_roles.rid IN (:rids))
    AND (field_data_field_sne_member.field_sne_member_value = 1)
    $state_condition
  )
  LIMIT 10 OFFSET 0

SQL;

  $result = db_query($sql,
    array(
      ':rids' => $rids,
      ':str' => '%' . $string . '%',
    )
  );

  foreach ($result as $record) {
    $first_name = $record->first_name;
    $last_name = $record->last_name;
    $full_name = $first_name . ' ' . $last_name;
    $uid = $record->uid;
    if (!isset($matches[$full_name])) {
      $matches[$full_name] = '<span class="autocomplete-suggestion" data-uid="' . $uid . '">' . check_plain($full_name) . '</span>';
    }
    // Prevent overriding, if some matches have the same full name.
    else {
      $id = ' [id:' . $uid . ']';
      $matches[$full_name . $id] = '<span class="autocomplete-suggestion" data-uid="' . $uid . '">' . check_plain($full_name) . $id . '</span>';
    }
  }
  print drupal_json_encode($matches);
}
