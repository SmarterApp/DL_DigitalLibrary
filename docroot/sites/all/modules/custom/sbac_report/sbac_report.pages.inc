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
  global $user;
  $account = user_load($user->uid);
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
  $resource_statistics = '';
  $contributed_details = '';
  $gate_keeping = '';
  $all_reviews = '';
  $summation = '';

  $view_own_report = array(
    'resource contributor',
    'resource reviewer',
  );

  if (!empty($uid) && !empty($date_range) && !empty($state_tid)) {
    $sne_details = sbac_report_build_sne_details($uid, $state_tid);
  }
  elseif (!sbac_report_select_other_users($account) && array_intersect($user->roles, $view_own_report)) {
    $uid = $user->uid;
    $state_tid = $account->field_state['und'][0]['tid'];
    $name = $account->field_first_name['und'][0]['safe_value'] . ' ' . $account->field_last_name['und'][0]['safe_value'];
    $date_range = format_date(0, 'custom', 'Ymd') . '--' . format_date(time(), 'custom', 'Ymd');
    $_SESSION['sbac_report']['sne']['uid'] = $uid;
    $_SESSION['sbac_report']['sne']['name'] = $name;

    $sne_details = sbac_report_build_sne_details($uid, $state_tid);
  }
  if (!empty($sne_details)) {
    // Pass -1 as limit, summary should be "number of items per page" independent.
    $contributed_summary = sbac_report_build_resource_summary($uid, $date_range, -1);
    if (sbac_report_select_other_users($account) || array_intersect($user->roles, $view_own_report)) {
      $resource_statistics = sbac_report_build_resource_statistics($uid, $date_range);
    }
    $contributed_details = sbac_report_build_resource_details($uid, $date_range);

    // Gate-Keeping Reviews.
    $name = sbac_report_get_session_value('sne', 'name');
    $gk_ind_accepted = sbac_report_get_ind_accepted_gate_keeper($uid, $date_range);
    $gk_ind_returned = sbac_report_get_ind_returned_gate_keeper($uid, $date_range);
    $gk_all_accepted = sbac_report_get_all_accepted_gate_keeper($date_range);
    $gk_all_returned = sbac_report_get_all_returned_gate_keeper($date_range);
    $gate_keeping = sbac_report_build_gk_table($name, $gk_ind_accepted, $gk_ind_returned, $gk_all_accepted, $gk_all_returned);

    // All Reviews.
    $reviews_in_progress = sbac_report_get_in_reviews($uid, $date_range);
    $all_completed_reviews = sbac_report_get_completed_reviews($uid, $date_range);
    $all_current_completed_reviews = sbac_report_get_current_completed_reviews($uid, $date_range);
    $average_consistency_rate = sbac_report_get_average_consistency_rate_acr($uid, $all_current_completed_reviews);
    $all_reviews = sbac_report_build_ar_table($reviews_in_progress, $all_completed_reviews, $average_consistency_rate);

    // The big 'summation' table.
    $summation = sbac_report_build_summation_table($uid, $date_range);
  }

  $individual_tab = theme('sbac_report_individual', array(
    'form' => $individual_form,
    'sne_details' => $sne_details,
    'contributed_summary' => $contributed_summary,
    'resource_statistics' => $resource_statistics,
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

  $csv_form3 = drupal_get_form('sbac_csv_report_forum_stats_form');
  $csv_forum_stats_tab = theme('sbac_csv_report_forum_stats', array(
      'form' => $csv_form3,
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
      '#title' => 'User Activity <span> (CSV Report) </span>',
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
      '#title' => t('Detailed Resource Statistics Report CSV Report)'),
      '#attributes' => array(
        'id' => SBAC_REPORT_TAB_STATES,
      ),
      'content' => array(
        '#markup' => $csv_resource_stats_tab,
      ),
    );

    $output[SBAC_REPORT_TAB_FORUM] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => t('Forum Statistics Report (CSV Report)'),
      '#attributes' => array(
        'id' => SBAC_REPORT_TAB_FORUM,
      ),
      'content' => array(
        '#markup' => $csv_forum_stats_tab,
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
        SBAC_REPORT_TAB_FORUM,
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
 * @param $uid
 * @param $date_range
 */
function sbac_report_build_resource_summary($uid, $date_range, $limit = 5) {
  $query = "SELECT node.nid AS nid,
            workbench_moderation_node_history.published AS workbench_moderation_node_history_published,
            node.sticky AS node_sticky
            FROM
            {node} node
            JOIN {workbench_moderation_node_history} workbench_moderation_node_history ON node.nid = workbench_moderation_node_history.nid AND node.vid = workbench_moderation_node_history.vid
            WHERE (((node.uid = :uid ))
            AND (((node.type IN ('resource'))
            AND (workbench_moderation_node_history.current <> '0')
            AND (workbench_moderation_node_history.state NOT IN  ('draft')))
            AND ((DATE_FORMAT((DATE_ADD('19700101', INTERVAL node.created SECOND) + INTERVAL -28800 SECOND), '%Y%m%d') BETWEEN :from_date AND :to_date))))";

  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  if ($limit == -1) {
    $results = db_query($query, array(':uid' => $uid, ':from_date' => $from_date, ':to_date' => $to_date));
  }
  else {
    $results = db_query_range($query, 0, $limit, array(':uid' => $uid, ':from_date' => $from_date, ':to_date' => $to_date));
  }

  $data = array('one' => 0, 'two' => 0, 'three' => 0);
  foreach ($results as $row) {
    $data['one']++;
    if ($row->workbench_moderation_node_history_published == 1 && $row->node_sticky == 0) {
      $data['two'] += $row->workbench_moderation_node_history_published;
    }
    if ($row->workbench_moderation_node_history_published == 1 && $row->node_sticky == 1) {
      $data['three'] += $row->node_sticky;
    }
  }

  $rows = array(array(0, 0, 0));
  if ($data) {
    $rows = array(array($data['one'], $data['two'], $data['three']));
  }

  return theme('sbac_report_resource_summary', array('rows' => $rows));
}

function sbac_report_build_resource_statistics($uid, $date_range, $limit = 5) {
  $sort = 'desc';
  $order = 'title';
  if (isset($_GET['order_rs'])) {
    $order = $_GET['order_rs'];
  }
  if (isset($_GET['sort_rs'])) {
    $sort = $_GET['sort_rs'];
  }
  if (isset($_SESSION['sbac_report_posted_rs'])) {
    $limit = $_SESSION['sbac_report_posted_rs'];
  }
  $opp_sort = ($sort == 'asc' ? 'desc' : 'asc');
  $url = '/reports?items_per_page_rs=';
  $data['table_title_query'] = $url . $limit . '&order_rs=title&sort_rs=' . $opp_sort;
  $data['table_posted_query'] = $url . $limit . '&order_rs=posted&sort_rs=' . $opp_sort;
  $data['table_rating_query'] = $url . $limit . '&order_rs=rating&sort_rs=' . $opp_sort;
  $data['table_reviewers_query'] = $url . $limit . '&order_rs=reviewers&sort_rs=' . $opp_sort;
  $data['table_topics_query'] = $url . $limit . '&order_rs=topics&sort_rs=' . $opp_sort;
  $data['table_posts_query'] = $url . $limit . '&order_rs=posts&sort_rs=' . $opp_sort;
  $data['table_downloads_query'] = $url . $limit . '&order_rs=downloads&sort_rs=' . $opp_sort;
  $data['table_views_query'] = $url . $limit . '&order_rs=views&sort_rs=' . $opp_sort;

  $src = '/misc/arrow-' . $sort . '.png';
  $data[$order . '_image'] = '<img typeof="foaf:Image" src="' . $src . '" width="13" height="13" alt="sort ascending" title="sort ascending">';

  $query = "SELECT  node.title AS node_title,
                    node.nid AS nid,
                    node.created AS node_created,
                    field_data_field_node_avg_rating.field_node_avg_rating_value AS field_data_field_node_avg_rating_field_node_avg_rating_value,
                    (SELECT COUNT(*) FROM eck_review WHERE node_id = node.nid) AS number_reviewers,
                    field_data_field_unique_downloads.field_unique_downloads_value AS field_data_field_unique_downloads_field_unique_downloads_val,
                    field_data_field_unique_views.field_unique_views_value AS field_data_field_unique_views_field_unique_views_value,
                    field_data_field_forum_topic_count.field_forum_topic_count_value AS field_forum_topic_count_value,
                    field_data_field_forum_topic_comment_count.field_forum_topic_comment_count_value AS field_forum_topic_comment_count_value,
                    MIN(node.nid) AS nid_1,
                    'node' AS field_data_field_node_avg_rating_node_entity_type,
                    COUNT(field_data_field_recent_reviewers.field_recent_reviewers_target_id) AS field_data_field_recent_reviewers_field_recent_reviewers_tar,
                    COUNT(field_data_field_recent_reviewers.delta) AS field_data_field_recent_reviewers_delta,
                    COUNT(field_data_field_recent_reviewers.language) AS field_data_field_recent_reviewers_language,
                    COUNT(field_data_field_recent_reviewers.bundle) AS field_data_field_recent_reviewers_bundle,
                    'node' AS field_data_field_unique_downloads_node_entity_type,
                    'node' AS field_data_field_unique_views_node_entity_type
            FROM        {node} node
            LEFT JOIN   {node_revision} node_revision
              ON node.vid = node_revision.vid
            INNER JOIN  {workbench_moderation_node_history} workbench_moderation_node_history
              ON node_revision.vid = workbench_moderation_node_history.vid
            LEFT JOIN   {field_data_field_node_avg_rating} field_data_field_node_avg_rating
              ON node.nid = field_data_field_node_avg_rating.entity_id
                AND (field_data_field_node_avg_rating.entity_type = 'node'
                  AND field_data_field_node_avg_rating.deleted = '0')
            LEFT JOIN   {field_data_field_recent_reviewers} field_data_field_recent_reviewers
              ON node.nid = field_data_field_recent_reviewers.entity_id
              AND (field_data_field_recent_reviewers.entity_type = 'node'
                AND field_data_field_recent_reviewers.deleted = '0')
            LEFT JOIN {taxonomy_term_data} taxonomy_term_data
              ON node.title = taxonomy_term_data.name
            LEFT JOIN {field_data_field_forum_topic_count} field_data_field_forum_topic_count
              ON taxonomy_term_data.tid = field_data_field_forum_topic_count.entity_id
            LEFT JOIN {field_data_field_forum_topic_comment_count} field_data_field_forum_topic_comment_count
              ON taxonomy_term_data.tid = field_data_field_forum_topic_comment_count.entity_id
            LEFT JOIN   {field_data_field_unique_downloads} field_data_field_unique_downloads
              ON node.nid = field_data_field_unique_downloads.entity_id
              AND (field_data_field_unique_downloads.entity_type = 'node'
                AND field_data_field_unique_downloads.deleted = '0')
            LEFT JOIN   {field_data_field_unique_views} field_data_field_unique_views
              ON node.nid = field_data_field_unique_views.entity_id
              AND (field_data_field_unique_views.entity_type = 'node'
                AND field_data_field_unique_views.deleted = '0')
            WHERE ((node.uid = :uid))
              AND ((  (node.status = '1')
                AND   (node.type IN ('resource'))
                AND   (workbench_moderation_node_history.current = 1)
                AND   (workbench_moderation_node_history.state IN ('published')) ))
              AND ((DATE_FORMAT((DATE_ADD('19700101', INTERVAL node.created SECOND) + INTERVAL -28800 SECOND), '%Y%m%d') BETWEEN :from_date AND :to_date))
            GROUP BY  node_title,
                      nid,
                      node_created,
                      field_data_field_node_avg_rating_node_entity_type,
                      field_data_field_node_avg_rating_field_node_avg_rating_value,
                      field_data_field_unique_downloads_node_entity_type,
                      field_data_field_unique_downloads_field_unique_downloads_val,
                      field_data_field_unique_views_node_entity_type,
                      field_data_field_unique_views_field_unique_views_value
            ";

  switch ($order) {
    case 'title':
      $query .= "ORDER BY node_title " . $sort;
      break;
    case 'posted':
      $query .= "ORDER BY node_created " . $sort;
      break;
    case 'rating':
      $query .= "ORDER BY field_data_field_node_avg_rating_field_node_avg_rating_value " . $sort;
      break;
    case 'reviewers':
      $query .= "ORDER BY number_reviewers " . $sort;
      break;
    case 'topics':
      $query .= "ORDER BY field_forum_topic_count_value " . $sort;
      break;
    case 'posts':
      $query .= "ORDER BY field_forum_topic_comment_count_value " . $sort;
      break;
    case 'downloads':
      $query .= "ORDER BY field_data_field_unique_downloads_field_unique_downloads_val " . $sort;
      break;
    case 'views':
      $query .= "ORDER BY field_data_field_unique_views_field_unique_views_value " . $sort;
      break;
  }

  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  if ($limit == -1) {
    $results = db_query($query, array(':uid' => $uid, ':from_date' => $from_date, ':to_date' => $to_date));
  }
  else {
    $results = db_query_range($query, 0, $limit, array(':uid' => $uid, ':from_date' => $from_date, ':to_date' => $to_date));
  }

  $rows = array();
  foreach ($results as $row) {
    $title = truncate($row->node_title, 55, array('check_markup' => FALSE));
    $row->title = l($title, 'node/' . $row->nid, array('attributes' => array('target' => '_blank')));
    $rows[] = array(
      'title' => $row->title,
      'posted' => date('m/d/y', $row->node_created),
      'rating' => ($row->field_data_field_node_avg_rating_field_node_avg_rating_value
 ? sbac_resource_display_fivestar_rating($row->field_data_field_node_avg_rating_field_node_avg_rating_value) : 'No reviews'),
      'reviewers' => l(($row->number_reviewers ? $row->number_reviewers : '0'), 'node/' . $row->nid, array('fragment' => 'review-reviews')),
      'topics' => l(($row->field_forum_topic_count_value ? $row->field_forum_topic_count_value : '0'), 'node/' . $row->nid, array('fragment' => 'review-collaboration')),
      'posts' => ($row->field_forum_topic_comment_count_value? $row->field_forum_topic_comment_count_value : '0'),
      'views' => $row->field_data_field_unique_views_field_unique_views_value ? $row->field_data_field_unique_views_field_unique_views_value : '0',
      'downloads' => $row->field_data_field_unique_downloads_field_unique_downloads_val ? $row->field_data_field_unique_downloads_field_unique_downloads_val : '0',
    );
  }

  $form = drupal_get_form('sbac_report_posted_resource_stats_pager_form', array(
    'uid' => $uid,
    'date_range' => $date_range,
    'limit' => $limit,
  ));
  $form_output = drupal_render($form);

  if (!$rows) {
    return '';
  }
  return theme(
    'sbac_report_posted_resource_stats',
    array(
      'rows' => $rows,
      'form' => $form_output,
      'data' => $data,
    )
  );

}


/**
 * @param $uid
 * @param $date_range
 */
function sbac_report_build_resource_details($uid, $date_range, $limit = 5) {
  global $user;
  // Deal with the sort options on the "Contributed resources details" table.
  $sort = 'desc';
  $order = 'created';
  if (!empty($_SESSION[SBAC_REPORT_RESOURCE_DETAILS_PAGER])) {
    $limit = $_SESSION[SBAC_REPORT_RESOURCE_DETAILS_PAGER];
  }
  if (isset($_GET['order'])) {
    $order = $_GET['order'];
  }
  if (isset($_GET['sort'])) {
    $sort = $_GET['sort'];
  }
  ($sort == 'asc' ? $opp_sort = 'desc' : $opp_sort = 'asc');
  $data['table_state_query'] = '/reports?items_per_page=' . $limit . '&order=state&sort=' . $opp_sort;
  $data['table_created_query'] = '/reports?items_per_page=' . $limit . '&order=created&sort=' . $opp_sort;
  $src = '/misc/arrow-' . $sort . '.png'; // up / down image.
  $data[$order . '_image'] = '<img typeof="foaf:Image" src="' . $src . '" width="13" height="13" alt="sort ascending" title="sort ascending">';

  $dates = explode('--', $date_range);
  $from_date = $dates[0];
  $to_date = $dates[1];

  $results = _sbac_resource_get_review_progress(NULL, $uid, $from_date, $to_date, $limit, $order, $sort)->fetchAll();
  $rows = array();
  foreach ($results as $row) {
    $resource = node_load($row->nid);
    $title = truncate($row->title, 55, array('check_markup' => FALSE));
    if (_resource_access_node_has_state($resource, array('rejected', 'published')) && sbac_central_user_has_role(array('reports administrator', 'resource publisher'))) {
      $query = array();
    }
    elseif ($resource->uid == $user->uid) {
      $query = array();
    }
    else {
      $query = array('sec' => '1');
    }
    $row->title = l($title, $resource->path['alias'], array('attributes' => array('target' => '_blank'), 'query' => $query));
    $row->contribution_date = date('m/d/Y h:i a', $row->created);
    $rows[] = $row;
  }

  $form = drupal_get_form('sbac_report_resource_details_pager_form', array(
    'uid' => $uid,
    'date_range' => $date_range,
    'limit' => $limit,
  ));
  $form_output = drupal_render($form);

  if ($rows) {
    return theme('sbac_report_resource_details', array('rows' => $rows, 'form' => $form_output, 'data' => $data));
  }
  return '';
}

/**
 * Form to change the number of items displayed in the summation table.
 *
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @param  [type] $data       [description]
 * @return [type]             [description]
 */
function sbac_report_posted_resource_stats_pager_form($form, &$form_state, $data) {
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $data['uid'],
  );

  $form['date_range'] = array(
    '#type' => 'hidden',
    '#value' => $data['date_range'],
  );

  $form['limit_2'] = array(
    '#title' => t('Display'),
    '#title_display' => 'before',
    '#attributes' => array('class' => array('form-items-per-page')),
    '#type' => 'select',
    '#options' => array(
      5 => t('Up to 5'),
      10 => t('Up to 10'),
      15 => t('Up to 15'),
      -1 => t('All'),
    ),
    '#default_value' => isset($_SESSION['sbac_report_posted_rs']) ? $_SESSION['sbac_report_posted_rs'] : 5,
    '#ajax' => array(
      'callback' => 'sbac_report_posted_resource_stats_pager_form_ajax',
      'wrapper' => 'posted-resources-stats',
      'method' => 'replace',
    ),
  );

  return $form;
}

/**
 * AJAX submit handler for sbac_report_build_gk_table_display_form
 *
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_report_posted_resource_stats_pager_form_ajax($form, &$form_state) {
  $values = $form_state['values'];
  $_SESSION['sbac_report_posted_rs'] = $values['limit_2'];
  $output = '<div id="posted-resources-stats">';
  $output .= sbac_report_build_resource_statistics($values['uid'], $values['date_range'], $values['limit_2']);
  $output .= '</div>';
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
function sbac_report_resource_details_pager_form($form, &$form_state, $data) {
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $data['uid'],
  );

  $form['date_range'] = array(
    '#type' => 'hidden',
    '#value' => $data['date_range'],
  );

  $form['limit'] = array(
    '#title' => t('Display'),
    '#title_display' => 'before',
    '#attributes' => array('class' => array('form-items-per-page')),
    '#type' => 'select',
    '#options' => array(
      5 => t('Up to 5'),
      10 => t('Up to 10'),
      15 => t('Up to 15'),
      -1 => t('All'),
    ),
    '#default_value' => isset($_SESSION[SBAC_REPORT_RESOURCE_DETAILS_PAGER]) ? $_SESSION[SBAC_REPORT_RESOURCE_DETAILS_PAGER] : 5,
    '#ajax' => array(
      'callback' => 'sbac_report_resource_details_pager_form_ajax',
      'wrapper' => 'contriubted-resource-details',
      'method' => 'replace',
    ),
  );

  return $form;
}

/**
 * AJAX submit handler for sbac_report_build_gk_table_display_form
 *
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_report_resource_details_pager_form_ajax($form, &$form_state) {
  $values = $form_state['values'];
  $_SESSION[SBAC_REPORT_RESOURCE_DETAILS_PAGER] = $values['limit'];
  $output = '<div id="contriubted-resource-details">';
  // Pass -1 as limit, summary should be "number of items per page" independent.
  $output .= sbac_report_build_resource_details($values['uid'], $values['date_range'], $values['limit']);
  $output .= '</div>';
  return $output;
}

/**
 * Selects the user information for the details card.
 *
 * @param $uid
 * @param $state
 * @return string
 */
function sbac_report_build_sne_details($uid, $state) {
  $output = '';

  $args = array();
  $sql = "SELECT u.uid FROM {users} u ";
  if ($state != 'all') {
    $sql .= "
      JOIN {field_data_field_state} fdfs
      ON u.uid = fdfs.entity_id
      AND fdfs.entity_type = 'user'
      AND fdfs.deleted = 0 ";
  }
  $sql .= "WHERE u.uid = :uid ";
  $args[':uid'] = $uid;
  if ($state != 'all') {
    $sql .= "AND fdfs.field_state_tid = :state";
    $args[':state'] = $state;
  }

  $result = db_query($sql, $args)->fetchField();
  if ($result) {
    $user = user_load($uid);
    if ($user) {
      $user_output = sbac_report_build_sne_output($user);
      $output = theme('sbac_report_output_sne', array('user_output' => $user_output));
    }
  }

  return $output;
}

/**
 * Checks user privacy options and outputs.
 *
 * @param $user
 * @return array
 */
function sbac_report_build_sne_output($user) {
  $user_output = array();
  $always_show[] = array('value' => 'field_first_name');
  $always_show[] = array('value' => 'field_position');
  $always_show[] = array('value' => 'field-state');
  $always_show[] = array('value' => 'field-grade-level-s-');
  $always_show[] = array('value' => 'field-subject-s-');
  $always_show[] = array('value' => 'special-populations');
  $privacy_list = array_merge($user->field_privacy['und'], $always_show);
  // Privacy is set all the time.
  if ($privacy_list) {
    foreach ($privacy_list as $key => $privacy) {
      switch ($privacy['value']) {
        case 'picture':
          if (isset($user->picture->uri)) {
            $picture = theme('image_style', array(
              'style_name' => 'profile_image',
              'path' => $user->picture->uri,
              'attributes' => array('class' => 'profile-img')
            ));
            $user_output['picture'] = '<a href="/user/' . $user->uid . '">' . $picture . '</a>';
          }
          break;
        case 'field_first_name':
          if (isset($user->field_first_name['und'][0]['value'])) {
            $user_output['first_name'] = $user->field_first_name['und'][0]['value'];
          }
          break;
        case 'field_last_name':
          if (isset($user->field_last_name['und'][0]['value'])) {
            $user_output['last_name'] = $user->field_last_name['und'][0]['value'];
          }
          break;
        case 'field_position':
          if (isset($user->field_position['und'][0]['tid'])) {
            $term = taxonomy_term_load($user->field_position['und'][0]['tid']);
            $user_output['position'] = $term->name;
          }
          break;
        case 'field-state':
          if (isset($user->field_state['und'][0]['tid'])) {
            $term = taxonomy_term_load($user->field_state['und'][0]['tid']);
            $user_output['state'] = $term->name;
          }
          break;
        case 'field-grade-level-s-':
          if (isset($user->field_grade_level_s_['und'][0])) {
            foreach ($user->field_grade_level_s_['und'] as $key => $term) {
              $term = taxonomy_term_load($term['tid']);
              $user_output['grade_level'][$term->tid] = $term->name;
            }
          }
          break;
        case 'field-subject-s-':
          if (isset($user->field_subject_s_['und'][0])) {
            foreach ($user->field_subject_s_['und'] as $key => $term) {
              $term = taxonomy_term_load($term['tid']);
              $user_output['subjects'][$term->tid] = $term->name;
            }
          }
          break;
        case 'special-populations':
          if (isset($user->field_special_populations['und'][0])) {
            foreach ($user->field_special_populations['und'] as $key => $term) {
              $term = taxonomy_term_load($term['tid']);
              $user_output['populations'][$term->tid] = $term->name;
            }
          }
          break;
        case 'mail':
          $user_output['email'] = $user->mail;
          break;
        case 'field_school_name':
          if (isset($user->field_school_name['und'][0])) {
            $user_output['school_name'] = $user->field_school_name['und'][0]['value'];
          }
          break;
        case 'field_district_name':
          if (isset($user->field_district_name['und'][0])) {
            $user_output['district_name'] = $user->field_district_name['und'][0]['value'];
          }
          break;
        case 'field_introduction':
          if (isset($user->field_introduction['und'][0])) {
            $user_output['introduction'] = $user->field_introduction['und'][0]['value'];
          }
          break;
      }
    }
  }

  return $user_output;
}

/**
 * Ajax for the autocomplete SNE textfield.
 */
function sbac_report_sne_autocomplete($string = '') {
  global $user;
  // Individual report hides the autocomplete to some users, check if this
  // user can see more users or not.
  $see_others = sbac_report_select_other_users($user);
  if (!$see_others) {
    print drupal_json_encode(array());
    exit;
  }

  $_SESSION['sbac_report']['active_tab'] = SBAC_REPORT_TAB_INDIVIDUAL;

  $query = db_select('users', 'u');
  $query->innerJoin('field_data_field_state', 's', 'u.uid = s.entity_id AND s.entity_type = \'user\' AND s.deleted = 0');
  $query->leftJoin('field_data_field_last_name', 'l', 'u.uid = l.entity_id AND l.entity_type = \'user\' AND l.deleted = 0');
  $query->leftJoin('field_data_field_first_name', 'f', 'u.uid = f.entity_id AND f.entity_type = \'user\' AND f.deleted = 0');
  $query->condition('u.status', 0, '<>');
  $query->where("CONCAT_WS(' ', f.field_first_name_value, l.field_last_name_value) LIKE :str", array(':str' => '%' . $string . '%'));
  $query->fields('u', array('uid', 'name'));
  $query->addField('f', 'field_first_name_value', 'first_name');
  $query->addField('l','field_last_name_value', 'last_name');
  $query->groupBy('u.uid');
  $query->range(0, 10);

  // Get the selected state if there's any.
  $matches = array();

  $state_tid = sbac_report_get_default_state_tid();

  if ($state_tid == 'all' || (isset($state_tid['all']) && ($state_tid['all'] == 'all' || $state_tid == 'all'))) {
    // Do nothing
  }
  elseif (!empty($state_tid)) {
    $query->condition('s.field_state_tid', $state_tid);
  }
  else {
    $matches['none'] = t('Please select a state');
    print drupal_json_encode($matches);
    exit;
  }

  // Reports administrators are only allowed to view resource contributors/reviewers
  if (sbac_central_user_has_role(array('reports administrator'))) {
    $query->leftJoin('users_roles', 'ur', 'ur.uid = u.uid');
    $query->leftJoin('role', 'r', 'r.rid = ur.rid');
    $query->condition('r.name', array('resource contributor', 'resource reviewer'), 'IN');
  }

  $result = $query->execute()->fetchAll();

  foreach ($result as $record) {
    $first_name = $record->first_name;
    $last_name = $record->last_name;
    $full_name = trim($first_name) . ' ' . trim($last_name);
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
 * @param  integer $display [description]
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
      $desc = variable_get('qc_' . $focus_data['tid'] . '_criteria_' . $i . '_description');

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

    $resource = node_load($row->nid);

    // resource title
    $item[] = array(
      'data' => '<div class="cell-scroll">' . l($row->node_title, $resource->path['alias'], array('attributes' => array('target' => '_blank'), 'query' => array('sec' => '1'))) . '</div>',
      'class' => 'cell title',
    );

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


    /**
     * PivotalTracker: 66993298 - Replaced dialog modal with ctools modal to fix
     * scroll issue.
     */
    $url = 'reports/info/nojs/' . $resource->nid . '/' . $uid;
    $trigger_id = 'sbac-report-ct-individual-modal-form-' . $resource->nid;

    $options = array(
      'attributes' => array(
        'class' => 'ctools-use-modal use-ajax ctools-modal-sbac-report-ct-individual-modal-form',
        'id' => $trigger_id,
      ),
      'html' => TRUE,
    );

    $info_link = l('<i class="icon-info">Info</i>', $url, $options);

    $modal_settings = array(
      'sbac-report-ct-individual-modal-form' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 700,
          'height' => 625,
        ),
        'modalTheme' => 'CtoolSbacReportModal',
      ),
    );
    drupal_add_js($modal_settings, 'setting');
    drupal_add_js(drupal_get_path('module', 'sbac_report') . '/js/sbac_report.ctools.js');
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
 * Menu callback for individual report.
 * @param  [type] $js   [description]
 * @param  [type] $node [description]
 * @param  [type] $user [description]
 * @return [type]       [description]
 */
function sbac_report_ct_individual_modal_callback($js = NULL, $node, $user) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();

    $form_state = array(
      'ajax' => TRUE,
      'title' => t($node->title),
      'report' => array(
        'node' => $node,
        'user' => $user,
      ),
    );

    $output = ctools_modal_form_wrapper('sbac_report_ct_individual_modal_form', $form_state);

    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
    }

    print ajax_render($output);
    drupal_exit();

  }
}

/**
 * Implements hook_form().
 * Makes form for report modal popup.
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 * @return [type]             [description]
 */
function sbac_report_ct_individual_modal_form($form, &$form_state) {
  $form = array();
  $slides = array();
  $node = $form_state['report']['node'];
  $uid = $form_state['report']['user']->uid;

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

  $form['intro']['review_date'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="intro"><div class="review-date">',
    '#suffix' => '</div>',
    '#markup' => 'Review Date: ' . format_date($user_review->created, 'custom', 'm/d/y'),
  );

  $form['intro']['user_recommendation'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="recommendation">',
    '#suffix' => '</div><div class="clear"></div></div>',
    '#markup' => 'Recommendation: ' . rec_friendly_name($user_review),
  );

  // Add GK slide
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

  $slides[] = $gk_slide;

  // Add QC slide
  if ($qc_entities) {
    $qc_rec_slide = '';
    $qc_count = 1;
    foreach ($qc_entities as $qc) {
      $qc_account = user_load($qc->uid);

      if ($states = field_entity_value($qc_account, 'field_state')) {
        $term = current($states);
        $location = t('State of !state', array(
          '!state' => $term->name
        ));
      }

      $qc_rec_slide .= '
                        <div class="qc-item">
                          <div class="slide-title">' . t('Reviewer !count', array('!count' => $qc_count)) . ', ' . $location .'</div>
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

    $slides[] = $qc_rec_slide;
  }

  // Add Poster comments and recommendations.
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
      $post_slide .= '
                        <div class="post-item">
                          <span class="inline-title">' . $title . ': </span>
                          ' . field_entity_value($post, $field_name) . '
                        </div>
                      ';
    }

    $slides[] = $post_slide;
  }

  // Add Quality Criteria question slides.
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

      $slides[] = $slide;
    }
  }

  // render slides
  $slide_list = theme('item_list', array(
    'items' => $slides,
    'attributes' => array(
      'class' => array(
        'slides',
      ),
    ),
  ));

  $content = '
              <div class="flexslider item-list">
                ' . $slide_list . '
              </div>
            ';
  $form['report']['content'] = array(
    '#markup' => $content,
  );

  $form['report']['continue'] = array(
    '#type' => 'button',
    '#value' => t('Continue'),
    '#attributes' => array(
      'class' => array(
        'flexslider-continue',
      ),
    ),
  );

  $form['report']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );

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
    case 0:
      $rec = 'NR';
      break;
    case 1:
      $rec = 'R-';
      break;
    case 2:
      $rec = 'R';
      break;
    case 3:
      $rec = 'R+';
      break;
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
