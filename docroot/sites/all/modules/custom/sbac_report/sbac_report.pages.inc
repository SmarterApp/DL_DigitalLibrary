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
  $state_tid = sbac_report_get_session_value('state', 'tid');
  $date_range = sbac_report_get_session_value('date_range', 'range');

  if (!empty($uid) && !empty($date_range) && !empty($state_tid)) {
    $sne_details = sbac_report_embed_view('sne_details', 'sne_details', $uid, $state_tid);
    // If there are no SNE with the selected state and uid. Display none.
    // @todo: custom message if there's no result.
    if (!empty($sne_details)) {
      $contributed_summary = views_embed_view('contributed_resources', 'resources_summary', $uid, $date_range);
      $contributed_details = views_embed_view('contributed_resources', 'resources_details', $uid, $date_range);

      /* Uncomment for Phase 2 of the report
      // Gate-Keeping Reviews.
      $name = sbac_report_get_session_value('sne', 'name');
      $gk_indv_rate = sbac_report_gate_keeping_reviews_rate($uid, $date_range);
      $gk_all_rate = sbac_report_gate_keeping_reviews_rate('all', $date_range);
      $gate_keeping = sbac_report_build_gk_table($name, $gk_indv_rate, $gk_all_rate);
      */
    }
  }

  return theme('sbac_report_individual', array(
      'form' => $form,
      'sne_details' => $sne_details,
      'contributed_summary' => $contributed_summary,
      'contributed_details' => $contributed_details,
      // 'gate_keeping' => $gate_keeping,
    )
  );
}

/**
 * Ajax for the autocomplete SNE textfield.
 */
function sbac_report_sne_autocomplete($string = '') {
  // Get the selected state if there's any.
  $matches = array();

  $state_tid = sbac_report_get_default_state_tid();
  if ($state_tid == 'all') {
    $state_condition = '';
  }
  elseif (!empty($state_tid)) {
    $state_condition = "AND (field_state.field_state_tid = '$state_tid')";
  }
  else {
    $matches['none'] = t('Please select a state');
    print drupal_json_encode($matches);
    exit;
  }

  $sql = <<<SQL

  SELECT users.uid AS uid,
    users.name AS name,
    field_last_name.field_last_name_value AS 'last_name',
    field_first_name.field_first_name_value AS 'first_name'
  FROM {users} users

  LEFT JOIN {field_data_field_last_name} AS field_last_name
    ON users.uid = field_last_name.entity_id AND (field_last_name.entity_type = 'user' AND field_last_name.deleted = '0')

  LEFT JOIN {field_data_field_first_name} AS field_first_name
    ON users.uid = field_first_name.entity_id AND (field_first_name.entity_type = 'user' AND field_first_name.deleted = '0')

  LEFT JOIN {field_data_field_state} AS field_state
    ON users.uid = field_state.entity_id AND (field_state.entity_type = 'user' AND field_state.deleted = '0')

  LEFT JOIN {field_data_field_sne_member} AS field_sne_member
    ON users.uid = field_sne_member.entity_id AND (field_sne_member.entity_type = 'user' AND field_sne_member.deleted = '0')

  WHERE (
    (
      (field_first_name.field_first_name_value LIKE :str)
      OR (field_last_name.field_last_name_value LIKE :str)
      OR (CONCAT_WS(' ', field_first_name.field_first_name_value, field_last_name.field_last_name_value) LIKE :str)
    )
    AND (users.status <> '0')
    AND (field_sne_member.field_sne_member_value = 1)
    $state_condition
  )

  GROUP BY uid

  LIMIT 10 OFFSET 0

SQL;

  $result = db_query($sql,
    array(
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
      $user_name = ' (' . $record->name . ')';
      $matches[$full_name . $user_name] = '<span class="autocomplete-suggestion" data-uid="' . $uid . '">' . check_plain($full_name) . $user_name . '</span>';
    }
  }
  print drupal_json_encode($matches);
}


/**
 * Helper function to build the Gate Keeping Reviews table.
 *
 * @param string $name
 *   The SNE name.
 * @param array $indv_rate
 *   The rate for the SNE returned by function sbac_report_gate_keeping_reviews_rate().
 * @param array $all_rate
 *   The rate for all SNEs returned by function sbac_report_gate_keeping_reviews_rate().
 *
 * @return string
 *   HTML.
 */
function sbac_report_build_gk_table($name, $indv_rate, $all_rate) {
  $header = array(
    '',
    t('Number of Gate-Keeping Reviews'),
    t('Acceptance Rate'),
    t('Return Rate'),
  );

  $rows = array();

  // First row.
  $indv_acceptance = ($indv_rate['acceptance'] / $indv_rate['total']) * 100;
  $indv_return = ($indv_rate['return'] / $indv_rate['total']) * 100;
  $rows[] = array(
    array('data' => $name),
    array('data' => $indv_rate['total']),
    array('data' => $indv_rate['acceptance'] . ' (' . round($indv_acceptance, 0) . '%)'),
    array('data' => $indv_rate['return'] . ' (' . round($indv_return, 0) . '%)'),
  );

  // Second row.
  $all_acceptance = ($all_rate['acceptance'] / $all_rate['total']) * 100;
  $all_return = ($all_rate['return'] / $all_rate['total']) * 100;
  $rows[] = array(
    array('data' => t('All SNEs')),
    array('data' => $all_rate['total']),
    array('data' => $all_rate['acceptance'] . ' (' . round($all_acceptance, 0) . '%)'),
    array('data' => $all_rate['return'] . ' (' . round($all_return, 0) . '%)'),
  );

  return theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'class' => array('large-12')
      ),
    )
  );
}
