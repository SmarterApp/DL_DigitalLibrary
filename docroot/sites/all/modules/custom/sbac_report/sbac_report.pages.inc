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
  $individual_form = drupal_get_form('sbac_report_individual_form');

  // Get SESSION values.
  $uid = sbac_report_get_session_value('sne', 'uid');
  $state_tid = sbac_report_get_session_value('state', 'tid');
  $date_range = sbac_report_get_session_value('date_range', 'range');

  $error_message = '';
  if (isset($_SESSION['sbac_report']['error_message'])) {
    $error_message = $_SESSION['sbac_report']['error_message'];
  }

  $sne_details = '';
  $contributed_summary = '';
  $contributed_details = '';
  $gate_keeping = '';
  $all_reviews = '';
  $summation = '';

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

  $individual_tab = theme('sbac_report_individual', array(
    'form' => $individual_form,
    'sne_details' => $sne_details,
    'contributed_summary' => $contributed_summary,
    'contributed_details' => $contributed_details,
    'gate_keeping' => $gate_keeping,
    'all_reviews' => $all_reviews,
    'summation' => $summation,
    'error_message' => $error_message,
  ));

  $csv_form1 = drupal_get_form('sbac_csv_report_user_activity_form');
  $csv_user_activity_tab = theme('sbac_csv_report_user_activity', array(
      'form' => $csv_form1,
    )
  );

  $csv_form2 = drupal_get_form('sbac_csv_report_resource_stats_form');
  $csv_resource_stats_tab = theme('sbac_csv_report_resource_stats', array(
      'form' => $csv_form2,
    )
  );

  $output = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'sbac_report') . '/js/sbac_report.default_tab.js',
      ),
    ),
  );

  $output[SBAC_REPORT_TAB_INDIVIDUAL] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Individual Contributor and Reviewer'),
    '#attributes' => array(
      'id' => SBAC_REPORT_TAB_INDIVIDUAL,
    ),
    'content' => array(
      '#markup' => $individual_tab,
    ),
  );
  
  if (sbac_report_user_access_all()) {
    $output[SBAC_REPORT_TAB_USER] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => t('User Activity (CSV Report)'),
      '#attributes' => array(
        'id' => SBAC_REPORT_TAB_USER,
      ),
      'content' => array(
        '#markup' => $csv_user_activity_tab,
      ),
    );

    $output[SBAC_REPORT_TAB_STATES] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => t('Detailed Resource Statistics Report (CSV Report)'),
      '#attributes' => array(
        'id' => SBAC_REPORT_TAB_STATES,
      ),
      'content' => array(
        '#markup' => $csv_resource_stats_tab,
      ),
    );
  }

  $default_tab = SBAC_REPORT_TAB_INDIVIDUAL;
  if (isset($_SESSION['sbac_report']['active_tab'])) {
    $default_tab = $_SESSION['sbac_report']['active_tab'];
  }

  $js = array(
    'sbac_report' => array(
      'tabs' => array(
        SBAC_REPORT_TAB_INDIVIDUAL,
        SBAC_REPORT_TAB_USER,
        SBAC_REPORT_TAB_STATES,
      ),
      'default_tab' => $default_tab,
    ),
  );

  drupal_add_js($js, 'setting');

  if ($error_message) {
    drupal_set_message($error_message, 'warning');
  }

  return drupal_render($output);
}

/**
 * Ajax for the autocomplete SNE textfield.
 */
function sbac_report_sne_autocomplete($string = '') {
  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_INDIVIDUAL;

  $args = array(
    ':str' => '%' . $string . '%',
  );

  // Get the selected state if there's any.
  $matches = array();

  $state_condition = '';
  $state_tid = sbac_report_get_default_state_tid();

  if ($state_tid == 'all') {
    $state_condition = '';
  }
  elseif (!empty($state_tid)) {
    $state_condition = "AND (field_state.field_state_tid = :state_tid)";
    $args[':state_tid'] = $state_tid;
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

  INNER JOIN {field_data_field_state} AS field_state
    ON users.uid = field_state.entity_id AND field_state.entity_type = 'user' AND field_state.deleted = 0

  LEFT JOIN {field_data_field_last_name} AS field_last_name
    ON users.uid = field_last_name.entity_id AND field_last_name.entity_type = 'user' AND field_last_name.deleted = 0

  LEFT JOIN {field_data_field_first_name} AS field_first_name
    ON users.uid = field_first_name.entity_id AND field_first_name.entity_type = 'user' AND field_first_name.deleted = 0

  LEFT JOIN {field_data_field_sne_member} AS field_sne_member
    ON users.uid = field_sne_member.entity_id AND field_sne_member.entity_type = 'user' AND field_sne_member.deleted = 0

  WHERE (
    CONCAT_WS(' ', field_first_name.field_first_name_value, field_last_name.field_last_name_value) LIKE :str
    AND (users.status <> 0)
    AND (field_sne_member.field_sne_member_value = 1)
    $state_condition
  )

  GROUP BY uid

  LIMIT 10 OFFSET 0

SQL;

  $result = db_query($sql, $args);

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

  $gk_ind_accepted_percentage = 0;
  $gk_ind_returned_percentage = 0;

  if ($gk_ind_total) {
    $gk_ind_accepted_percentage = round($gk_ind_accepted_count / $gk_ind_total, 2) * 100;
    $gk_ind_returned_percentage = round($gk_ind_returned_count / $gk_ind_total, 2) * 100;
  }

  // All.
  $gk_all_accepted_count = count($gk_all_accepted);
  $gk_all_returned_count = count($gk_all_returned);
  $gk_all_total = $gk_all_accepted_count + $gk_all_returned_count;
  if ($gk_all_total != 0) {
    $gk_all_accepted_percentage = round($gk_all_accepted_count / $gk_all_total, 2) * 100;
    $gk_all_returned_percentage = round($gk_all_returned_count / $gk_all_total, 2) * 100;
  }
  else {
    $gk_all_accepted_percentage = 0;
    $gk_all_returned_percentage = 0;
  }
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
        'class' => array('large-12 report-gk')
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
    array('data' => (round($average_consistency_rate, 2) * 100) . '%'),
  );

  return theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'class' => array('large-12 report-ar')
      ),
    )
  );
}

/**
 * Builds the overall resource qc review summation table.
 * @param  [type]  $uid        [description]
 * @param  [type]  $date_range [description]
 * @param  integer $display    [description]
 * @return [type]              [description]
 */
function sbac_report_build_summation_table($uid, $date_range, $display = 5) {
  $subheader = array(
    array(
      'data' => t('Resource Title'),
      'class' => 'subheader',
    ),
    array(
      'data' => t('Review Date'),
      'class' => 'subheader',
    ),
    array(
      'data' => t('Recc.'),
      'class' => 'subheader',
    ),
    array(
      'data' => t('Recc. Cons.'),
      'class' => 'subheader',
    ),
    array(
      'data' => t('GK'),
      'class' => 'subheader',
    ),
  );

  $core_column_count = sizeof($subheader);

  $focus_map = array(
    array(
      'tid' => 85,
      'title' => t('Professional Learning Quality Criteria Consistency Rates'),
      'count' => variable_get('qc_85_criteria_num', 0),
    ),
    array(
      'tid' => 84,
      'title' => t('Instructional Quality Criteria Consistency Rates'),
      'count' => variable_get('qc_84_criteria_num', 0),
    ),
    array(
      'tid' => 86,
      'title' => t('Combination of Instructional and Professional Learning Quality Criteria Consistency Rates'),
      'count' => variable_get('qc_86_criteria_num', 0),
    )
  );

  $header = array(
    array(
      'data' => '&nbsp;',
      'colspan' => $core_column_count,
      'class' => 'empty',
    ),
  ); 

  foreach ($focus_map as $focus_data) {
    if ($focus_data['tid'] == 86) {
      continue;
    }

    $header[] = array(
      'data' => $focus_data['title'],
      'colspan' => $focus_data['count'],
      'class' => 'header header-' . $focus_data['tid'],
    );

    for ($i = 1; $i <= $focus_data['count']; $i++) {
      $title = variable_get('qc_' . $focus_data['tid'] . '_criteria_' . $i . '_title');
      $desc  = variable_get('qc_' . $focus_data['tid'] . '_criteria_' . $i . '_description');

      $cell = ' 
                <span class="devtools-tooltip report-qc-tooltip">
                  <a href="#" class="devtools-tooltip-trigger">' . $i . '</a>
                  <div class="devtools-tooltip-body">
                    <span class="title">' . filter_text($title) . '</span>
                    <span class="desc">' . filter_text($desc) . '</span>
                  </div>
                </span>
              ';

      $subheader[] = array(
        'data' => $cell,
        'class' => 'subheader',
      );
    }
  }

  $subheader[] = $header[] = array(
    'data' => '&nbsp;',
    'class' => 'subheader empty',
  );

  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  $query = "  SELECT      DISTINCT gk.id AS gk_id,
                          gk.met_criteria AS met_criteria,
                          gk.uid AS gk_uid,
                          gk.node_id AS nid,
                          qc.id AS qc_id,
                          qc.uid AS qc_uid,
                          n.title AS node_title,

                          IF(qc.created IS NULL, gk.created, qc.created) AS review_date

              FROM        eck_feedback gk
              
              INNER JOIN  node n
                ON        n.nid = gk.node_id
              
              LEFT JOIN   eck_feedback qc
                ON        qc.type = 'qc'
                AND       qc.node_id = gk.node_id
                AND       qc.status = 1
                AND       qc.completed = 1
                AND       qc.current = 1

              WHERE       gk.type = 'gate_keeper'
              AND         gk.status = 1
              AND         gk.completed = 1
              AND         gk.current = 1

              AND         :uid IN (gk.uid, qc.uid)

              AND         DATE_FORMAT(
                            (
                              DATE_ADD('19700101', INTERVAL IF(qc.created IS NULL, gk.created, qc.created) SECOND)
                               + 
                              INTERVAL -25200 SECOND
                            ),
                            '%Y%m%d'
                          ) BETWEEN :from_date AND :to_date

              AND         IF ((gk.uid = :uid AND qc.uid != :uid), qc.id = NULL, 1)

              ORDER BY    review_date DESC
           ";

//  if ($display != -1) {
//    $query .= ' LIMIT ' . (int) $display;
//  }

  $result = db_query($query, array(
    ':uid' => (int) $uid,
    ':from_date' => $from_date,
    ':to_date' => $to_date,
  ));

  $rows = array(
    $subheader,
  );

  $count = 0;
  foreach ($result as $row) {
    $item = array();

    $count_items = _sbac_resource_determine_feedback($row->nid, 'qc', $uid, 1, FALSE, 1, 'set', TRUE);
    if (count($count_items) != 2) { // two other reviewers
      continue;
    }

    // resource title
    $item[] = array(
      'data' => '<div class="cell-scroll">' . $row->node_title . '</div>',
      'class' => 'cell title',
    );
    
    $resource = node_load($row->nid);

    // review date
    $item[] = array(
      'data' => format_date($row->review_date, 'custom', 'm/d/y'),
      'class' => 'cell date',
    );
    
    // gate keeper decision
    if ($row->gk_uid == $uid) {
      $gk_decision = $row->met_criteria ? 'Y' : 'N';
    }
    else {
      $gk_decision = '-';
    }

    $fill = array(
      'data' => t('-'),
      'class' => 'cell fill',
    );

    $empty = array(
      'data' => '&nbsp;',
      'class' => 'cell empty',
    );

    if ($gk_decision == 'N' || is_null($row->qc_id)) {
      // recommendation decision
      $item[] = $fill;

      // recommendation consistency
      $item[] = $fill;

      // gate keeper decision
      $item[] = array(
        'data' => t($gk_decision),
        'class' => 'cell gk-decision',
      );

      $current_size = sizeof($item);
      $max = sizeof($subheader);

      $item += array_fill($current_size - 1, $max - $current_size, $fill);
    }
    else {
      // recommendation decision
      $qc = entity_load_single('feedback', $row->qc_id);
      $focus = field_get_value($resource, 'field_focus', 'tid');

      $item[] = array(
        'data' => rec_friendly_name($qc),
        'class' => 'cell rec-dec',
      );

      // recommendation consistency
      $entities = entity_load('feedback', FALSE, array(
        'node_id' => $resource->nid,
        'type' => 'qc',
        'status' => 1,
        'current' => 1,
        'completed' => 1,
      ));

      $current_qc = $entities[$row->qc_id];
      unset($entities[$row->qc_id]);

      $item[] = array(
        'data' => rec_consistency_rate($entities, $current_qc),
        'class' => 'cell gk-con',
      );

      // gate keeper decision
      $item[] = array(
        'data' => t($gk_decision),
        'class' => 'cell gk-decision',
      );

      if ($focus != 86) {
        if (count($focus_map) == 3) {
          array_pop($focus_map);
        }
      }
      else {
        if (count($focus_map) == 2) {
          $focus_map[] = array(
            'tid' => 86,
            'title' => t('Combination of Instructional and Professional Learning Quality Criteria Consistency Rates'),
            'count' => variable_get('qc_86_criteria_num', 0),
          );
        }
      }

      foreach ($focus_map as $focus_data) {
        for ($i = 0; $i < $focus_data['count']; $i++) {
          if ($focus == 86 && $focus_data['tid'] != $focus) {
            continue;
          }

          if ($focus_data['tid'] == $focus) {
            $current_qc_questions = field_entity_value($current_qc, 'field_review_set');

            if (!isset($current_qc_questions[$i])) {
              $item[] = $empty;
              continue;
            }
            
            $current_value = field_entity_value($current_qc_questions[$i], 'field_level');

            if (sizeof($entities) == 2) {
              $consistency = 0;

              foreach ($entities as $other_qc) {
                $other_questions = field_entity_value($other_qc, 'field_review_set');
                $other_value = field_entity_value($other_questions[$i], 'field_level');

                $consistency += abs($current_value - $other_value);
              }

              $consistency /= 8;
              $consistency = round((1 - $consistency) * 100) . '%';

              $item[] = array(
                'data' => $consistency,
                'class' => 'cell qc-con',
              );
            }
            // other reviews aren't completed, so we don't show consistency percentages
            else {
              $item[] = $fill;
            } 
          }
          else {
            $item[] = $fill;
          }
        }
      }
    }

    drupal_add_library('dialog', 'dialog');
    $trigger_id = 'report-' . $resource->nid;
    $url = 'reports/' . $resource->nid . '/info/default/' . $trigger_id . '/' . $uid;

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
        ),
        'id' => $trigger_id,
      ),
      'html'=> true,
    );

    $info_link = l('<i class="icon-info">Info</i>', $url, $options);

    // info tooltip
    $item[] = array(
      'data' => $info_link,
      'class' => 'cell info',
    );

    $rows[] = $item;
    $count++;
    if ($count == $display) {
      break;
    }
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'class' => array('large-12 report-summation no-sticky')
    ),
    'sticky' => FALSE,
  ));

  $form = drupal_get_form('sbac_report_build_gk_table_display_form', array(
    'uid' => $uid,
    'date_range' => $date_range,
  ));

  $output .= drupal_render($form);

  $output = '<div id="summation-table">' . $output . '</div>';

  return $output;
}

/**
 * Form to change the number of items displayed in the summation table.
 * 
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @param  [type] $data       [description]
 * @return [type]             [description]
 */
function sbac_report_build_gk_table_display_form($form, &$form_state, $data) {
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $data['uid'],
  );

  $form['date_range'] = array(
    '#type' => 'hidden',
    '#value' => $data['date_range'],
  );

  $form['display'] = array(
    '#title' => t('Display'),
    '#type' => 'select',
    '#options' => array(
      5 => t('Up to 5'),
      10 => t('Up to 10'),
      15 => t('Up to 15'),
      -1 => t('All'),
    ),
    '#ajax' => array(
      'callback' => 'sbac_report_build_gk_table_display_form_ajax',
      'wrapper' => 'summation-table',
    ),
  );

  return $form;
}

/**
 * AJAX submit handler for sbac_report_build_gk_table_display_form
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_report_build_gk_table_display_form_ajax($form, &$form_state) {
  $values = $form_state['values'];

  $output = sbac_report_build_summation_table($values['uid'], $values['date_range'], $values['display']);

  return $output;
}

/**
 * Callback for /reports/%node/info/
 * @return [type] [description]
 */
function sbac_report_individual_modal($node, $state, $trigger_id, $uid) {
  $commands = dialog_show_form('sbac_report_individual_modal_form', $node, $state, $trigger_id, $uid);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
}

/**
 * The form to initialize Resource Report Info Modal.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @param  [type] $node       [description]
 * @param  [type] $state      [description]
 * @param  [type] $trigger_id [description]
 * @param  [type] $uid        [description]
 * @return [type]             [description]
 */
function sbac_report_individual_modal_form($form, &$form_state, $node, $state, $trigger_id, $uid) {
  $form = array();

  // default state
    $output = '';

    // load all reviews
    $gk_entities = entity_load('feedback', FALSE, array(
      'node_id' => $node->nid,
      'type' => 'gate_keeper',
      'status' => 1,
      'current' => 1,
      'completed' => 1,
    ));

    $gk = current($gk_entities);

    $qc_entities = entity_load('feedback', FALSE, array(
      'node_id' => $node->nid,
      'type' => 'qc',
      'status' => 1,
      'current' => 1,
      'completed' => 1,
    ));

    $post_entities = entity_load('feedback', FALSE, array(
      'node_id' => $node->nid,
      'type' => 'post',
      'status' => 1,
      'current' => 1,
      'completed' => 1,
    ));

    $post = FALSE;
    if ($post_entities) {
      $post = current($post_entities);
    }

    $user_review = FALSE;
    $recommendation = '';

    // try to find the QC created by the user we're looking at
    foreach ($qc_entities as $qc) {
      if ($qc->uid == $uid) {
        $user_review = $qc;
      }
    }

    // if we still didn't find a QC, then the user must have a GK, and it'll be the one we 
    // already loaded
    if (!$user_review) {
      $user_review = $gk;
    }

    $date = '';
    if ($user_review) {
      $date = t('Review Date: !date', array('!date' => format_date($user_review->created, 'custom', 'm/d/y')));

      if ($user_review->type == 'qc') {
        $rec = rec_friendly_name($user_review);
        $recommendation = t('Recommendation: !val', array('!val' => $rec));
      }
    }

    // prepare header/intro
      $output .=  '  
                    <div class="intro">
                      <div class="review-date">
                        ' . $date . '
                      </div>
                      <div class="recommendation">
                        ' . $recommendation . '
                      </div>
                      <div class="clear"></div>
                    </div>
                  ';

    // add GK summary slide
      $items = array();

      $gk_slide = '<div class="slide-title">' . t('Gate-Keeping Criteria') . '</div>';

      $focus = field_entity_value($node, 'field_focus');

      $gk_slide = '<div class="resource-type">' . t('Resource Type: !type', array('!type' => $focus->name)) . '</div>';

      foreach (field_entity_value($gk, 'field_quality_set') as $count => $question) {
        $comments = field_entity_value($question, 'field_comments');
        $decision = field_entity_value($question, 'field_meets_criterion');

        $gk_slide .= '
                        <div class="gk-item">
                          <span class="item-num">' . ($count + 1) . '</span>
                          <span class="item-decision">' . ($decision ? t('Y') : t('N')) . '</span>
                          <span class="item-comments">' . $comments . '</span>
                        </div>
                     ';
      }

      $items[] = $gk_slide;

    // add QC recommendations slide
      if ($qc_entities) {
        $qc_rec_slide = '';
        $qc_count = 1;
        foreach ($qc_entities as $qc) {
          $qc_rec_slide .= '<div class="slide-title">' . t('Reviewer !count', array('!count' => $qc_count)) . '</div>';
          $qc_account = user_load($qc->uid);

          $location = l(full_name($qc_account), 'user/' . $qc_account->uid);

          if ($states = field_entity_value($qc_account, 'field_state')) {
            $term = current($states);
            $location .= t(', State of !state', array(
              '!state' => $term->name
            ));
          }
          
          $qc_rec_slide .= '
                            <div class="qc-item">
                              <div class="qc-rec-name">
                                ' . $location . '
                              </div>
                              
                              <div class="qc-rec-value">
                               <span>' . t('Recommendation:') . '</span> ' . rec_friendly_name($qc) . '
                              </div>

                              <div class="qc-rec-con">
                                <span>' . t('Resource Consistency Rate:') . '</span> ' .
                                rec_consistency_rate($qc_entities, $qc) . '
                              </div>

                              <div class="qc-rec-rationale">
                                <span>' . t('Rationale:') . '</span> ' . 
                                field_entity_value($qc, 'field_rec_rationale') . '
                              </div>
                            </div>
                           ';

          $qc_count++;
        }

        $items[] = $qc_rec_slide;
      }

    // add Poster comments recommendations slide
      if ($post) {
        $post_options = field_allowed_values('field_post_options');
        $post_value = field_entity_value($post, 'field_post_options');

        $post_slide = '
                        <div class="slide-title">' . t('SLT') . '</div>
                        <div class="post-decision">' . t('Posting decision: !dec', array('!dec' => $post_options[$post_value])) . '</div>
                      ';

        $fields = array(
          'field_to_contributor' => t('Comment to Contributor'),
          'field_to_reviewer_1' => t('Comment to Reviewer 1'),
          'field_to_reviewer_2' => t('Comment to Reviewer 2'),
          'field_to_reviewer_3' => t('Comment to Reviewer 3'),
        );

        foreach ($fields as $field_name => $title) {
          $post_slide .=  '
                            <div class="post-item">
                              <span class="inline-title">' . $title . ': </span>
                              ' . field_entity_value($post, $field_name) . '
                            </div>
                          ';
        }

        $items[] = $post_slide;
      }

    // add Quality Criteria question slides
      if ($qc_entities) {
        $questions = field_entity_value(reset($qc_entities), 'field_review_set');
        $questions_count = sizeof($questions);
        
        for ($i = 0; $i < $questions_count; $i++) {
          $qc_title = variable_get('qc_' . field_entity_value($node, 'field_focus')->tid . '_criteria_' . ($i + 1) . '_title', '');

          $slide = '<div class="slide-title">' . filter_text($qc_title) . '</div>';

          $levels = array();
          $comments = '';

          $j = 1;
          foreach ($qc_entities as $qc) {
            $questions = field_entity_value($qc, 'field_review_set');

            $level = field_entity_value($questions[$i], 'field_level');

            if ($qc->uid == $uid) {
              array_unshift($levels, '<strong>' . $level . '</strong>');
            }
            else {
              $levels[] = $level;
            }

            $comments .= '
                        <div class="qc-question-item">
                          <span class="inline-title">' . t('Reviewer !count Comment', array('!count' => $j)) . ': </span>
                          ' . field_entity_value($questions[$i], 'field_comments') . '
                        </div>
                      ';

            $j++;
          }

          $slide .= '<div class="qc-question-levels">' . t('- Level: ') . implode(' / ', $levels) . '</div>';
          $slide .= $comments;
          
          $items[] = $slide;
        }
      }

    // render slides
      $item_list = theme('item_list', array(
        'items' => $items,
        'attributes' => array(
          'class' => array(
            'slides',
          ),
        ),
      ));

      $output .= '
                  <div class="flexslider item-list">
                    <div class="flex-viewport">
                      ' . $item_list . '
                    </div>
                  </div>
                ';

    // add content to form structure
      $form['state_default']['content'] = array(
        '#markup' => $output,
      );

      $form['state_default']['continue'] = array(
        '#type' => 'button',
        '#value' => t('Continue'),
        '#attributes' => array(
          'class' => array(
            'flexslider-continue',
          ),
        ),
      );

  // dialog configuration
    $dialog_common_options = array(
      'width' => '700px',
      'position' => 'center',
    );

  // state configuration
    $state_common_options = array(
      'close_link' => TRUE,
      'close_link_text' => t('Cancel'),
      'close_link_class' => array(
        'button',
        'radius',
      ),
    );

    $form_state['dialog_settings'] = array(
      'current_state' => $state,
      'trigger_id' => $trigger_id,
      'states' => array(

        'default' => array(
          'dialog' => array('title' => $node->title) + $dialog_common_options,
          'close_link' => TRUE,
          'close_link_text' => t('Cancel'),
          'close_link_class' => array(
            'button',
            'radius',
          ),
        ),
      ),
    );

  dialog_form_prepare($form, $form_state);

  return $form;
}

/**
 * Returns the friendly recommendation value name from given entity.
 * @param  [type] $entity [description]
 * @return [type]         [description]
 */
function rec_friendly_name($entity) {
  $rec_value = field_entity_value($entity, 'field_rec_options');
  $rec = '';

  switch ($rec_value) {
    case 0: $rec = 'NR';  break;
    case 1: $rec = 'R-';  break;
    case 2: $rec = 'R';   break;
    case 3: $rec = 'R+';  break;
  }

  return $rec;
}

/**
 * Calculates recommendation consistency between the $current entity
 * and $all entities.
 * @param  [type] $all     [description]
 * @param  [type] $current [description]
 * @return [type]          [description]
 */
function rec_consistency_rate($all, $current) {
  $current_rec_value = field_entity_value($current, 'field_rec_options') + 1;

  $consistency = 0;
  foreach ($all as $other) {
    if ($other->id == $current->id) {
      continue;
    }

    $other_rec_value = field_entity_value($other, 'field_rec_options') + 1;
    $consistency += abs($current_rec_value - $other_rec_value);
  }

  $consistency /= 6;
  $consistency = round((1 - $consistency) * 100) . '%';

  return $consistency;
}

/**
 * Updates the active tab.
 * @param  [type] $tab [description]
 * @return [type]      [description]
 */
function sbac_reports_set_tab_ajax($tab) {
  $_SESSION['sbac_report']['active_tab'] = $tab;
}
