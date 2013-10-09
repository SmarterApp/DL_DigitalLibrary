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
  $gate_keeping = '';
  $all_reviews = '';
  $summation = '';

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

      // Gate-Keeping Reviews.
      $name = sbac_report_get_session_value('sne', 'name');
      $gk_ind_accepted = sbac_report_get_ind_accepted_gate_keeper($uid, $date_range);
      $gk_ind_returned = sbac_report_get_ind_returned_gate_keeper($uid, $date_range);
      $gk_all_accepted = sbac_report_get_all_accepted_gate_keeper($date_range);
      $gk_all_returned = sbac_report_get_all_returned_gate_keeper($date_range);
      $gate_keeping = sbac_report_build_gk_table($name, $gk_ind_accepted, $gk_ind_returned, $gk_all_accepted, $gk_all_returned);

      // All Reviews.
      $reviews_in_progress = sbac_report_get_in_reviews($uid, $date_range);
      $completed_reviews = sbac_report_get_completed_reviews($uid, $date_range);
      // $reviews = array_merge($reviews_in_progress, $completed_reviews);
      $average_consistency_rate = sbac_report_get_average_consistency_rate_acr($uid, $completed_reviews);
      $all_reviews = sbac_report_build_ar_table($reviews_in_progress, $completed_reviews, $average_consistency_rate);

      // The big 'summation' table.
      $summation = sbac_report_build_summation_table($uid, $date_range);
    }
  }

  return theme('sbac_report_individual', array(
      'form' => $form,
      'sne_details' => $sne_details,
      'contributed_summary' => $contributed_summary,
      'contributed_details' => $contributed_details,
      'gate_keeping' => $gate_keeping,
      'all_reviews' => $all_reviews,
      'summation' => $summation,
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
function sbac_report_build_gk_table($name, $gk_ind_accepted, $gk_ind_returned, $gk_all_accepted, $gk_all_returned) {
  $header = array(
    '',
    t('Accepted Reviews'),
    t('Returned Reviews'),
    t('Total Reviews'),
  );

  $rows = array();
  // Individual.
  $gk_ind_accepted_count = count($gk_ind_accepted);
  $gk_ind_returned_count = count($gk_ind_returned);
  $gk_ind_total = $gk_ind_accepted_count + $gk_ind_returned_count;
  $gk_ind_accepted_percentage = round($gk_ind_accepted_count / $gk_ind_total, 1) * 100;
  $gk_ind_returned_percentage = round($gk_ind_returned_count / $gk_ind_total, 1) * 100;

    // All.
  $gk_all_accepted_count = count($gk_all_accepted);
  $gk_all_returned_count = count($gk_all_returned);
  $gk_all_total = $gk_all_accepted_count + $gk_all_returned_count;
  $gk_all_accepted_percentage = round($gk_all_accepted_count / $gk_all_total, 1) * 100;
  $gk_all_returned_percentage = round($gk_all_returned_count / $gk_all_total, 1) * 100;

  // First Row.
  $rows[] = array(
    array('data' => $name),
    array('data' => $gk_ind_accepted_count . ' (' . $gk_ind_accepted_percentage . '%)'),
    array('data' => $gk_ind_returned_count . ' (' . $gk_ind_returned_percentage . '%)'),
    array('data' => $gk_ind_total),
  );

  // Second row.
  $rows[] = array(
    array('data' => t('All SNE Members')),
    array('data' => $gk_all_accepted_count . ' (' . $gk_all_accepted_percentage . '%)'),
    array('data' => $gk_all_returned_count . ' (' . $gk_all_returned_percentage . '%)'),
    array('data' => $gk_all_total),
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

/**
 * Returns the HTML for the table output.
 *
 * @param $reviews_in_progress
 * @param $completed_reviews
 * @param $average_consistency_rate
 * @return string
 */
function sbac_report_build_ar_table($reviews_in_progress, $completed_reviews, $average_consistency_rate) {
  $header = array(
    t('Reviews in Progress'),
    t('Completed Reviews'),
    t('Average Consistency Rate for All Completed Reviews'),
  );

  $rows = array();

  // First row.
  $rows[] = array(
    array('data' => count($reviews_in_progress)),
    array('data' => count($completed_reviews)),
    array('data' => (round($average_consistency_rate, 1) * 100) . '%'),
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

function sbac_report_build_summation_table($uid, $date_range) {
  $header = array(
    t('Resource Title'),
    t('Review Date'),
    t('Recc.'),
    t('Recc. Consistency'),
    t('GK'),
  );

  // $types = field_info_field_map();
  // $types = field_info_instances('feedback', 'qc');
  // print_rr($types);exit();

  $query = "  SELECT      gk.id AS gk_id,
                          gk.met_criteria AS met_criteria,
                          gk.uid AS gk_uid,
                          gk.node_id AS nid,
                          qc.id AS qc_id,
                          qc.created AS qc_created

              FROM        eck_feedback gk
              LEFT JOIN   eck_feedback qc
                ON        qc.type = 'qc'
                AND       qc.node_id = gk.node_id
                AND       qc.status = 1
                AND       qc.completed = 1
                AND       qc.current = 1
                AND       qc.uid = :uid

              WHERE       gk.status = 1
              AND         gk.completed = 1
              AND         gk.current = 1
           ";

  $result = db_query($query, array(
    ':uid' => (int) $uid,
  ));

  foreach ($result as $row) {
    dsmm($row);
  }

  $rows = array();

  for ($i = 0; $i < 10; $i++) {
    $rows[] = array(
      array(
        'data' => 'test',
      ),
      array(
        'data' => 'test1',
      ),
      array(
        'data' => 'test2',
      ),
      array(
        'data' => 'test3',
      ),
      array(
        'data' => 'test4',
      ),
    );
  }

  return theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'class' => array('large-12')
      ),
    )
  );
}