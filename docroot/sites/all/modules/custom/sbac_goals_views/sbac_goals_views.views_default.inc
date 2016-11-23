<?php
/**
 * @file
 * sbac_goals_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_goals_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'contributed_resources_rankings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Contributed resources rankings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Resource Reviewer';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p><strong>No activity yet!</strong></p>
<!-- <p>Start <a href="my-resources">Start submitting resources</a> to get the list started.</p>
<p>Learn about contributing and reviewing resources <a href=\'\'>here</a></p> -->';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: User: Resources Contributed */
  $handler->display->display_options['fields']['field_resources_contributed']['id'] = 'field_resources_contributed';
  $handler->display->display_options['fields']['field_resources_contributed']['table'] = 'field_data_field_resources_contributed';
  $handler->display->display_options['fields']['field_resources_contributed']['field'] = 'field_resources_contributed';
  $handler->display->display_options['fields']['field_resources_contributed']['label'] = '';
  $handler->display->display_options['fields']['field_resources_contributed']['element_class'] = 'contributed-goal-completed';
  $handler->display->display_options['fields']['field_resources_contributed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_resources_contributed']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: User: Resources Posted Goal */
  $handler->display->display_options['fields']['field_resources_posted_goal']['id'] = 'field_resources_posted_goal';
  $handler->display->display_options['fields']['field_resources_posted_goal']['table'] = 'field_data_field_resources_posted_goal';
  $handler->display->display_options['fields']['field_resources_posted_goal']['field'] = 'field_resources_posted_goal';
  $handler->display->display_options['fields']['field_resources_posted_goal']['label'] = '';
  $handler->display->display_options['fields']['field_resources_posted_goal']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_resources_posted_goal']['alter']['text'] = 'of [field_resources_posted_goal]';
  $handler->display->display_options['fields']['field_resources_posted_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_resources_posted_goal']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = '';
  $handler->display->display_options['fields']['login']['exclude'] = TRUE;
  $handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['login']['date_format'] = 'forum_listing';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'forum_listing';
  /* Sort criterion: User: Resources Contributed (field_resources_contributed) */
  $handler->display->display_options['sorts']['field_resources_contributed_value']['id'] = 'field_resources_contributed_value';
  $handler->display->display_options['sorts']['field_resources_contributed_value']['table'] = 'field_data_field_resources_contributed';
  $handler->display->display_options['sorts']['field_resources_contributed_value']['field'] = 'field_resources_contributed_value';
  $handler->display->display_options['sorts']['field_resources_contributed_value']['order'] = 'DESC';
  /* Sort criterion: User: Last name (field_last_name) */
  $handler->display->display_options['sorts']['field_last_name_value']['id'] = 'field_last_name_value';
  $handler->display->display_options['sorts']['field_last_name_value']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['sorts']['field_last_name_value']['field'] = 'field_last_name_value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Hide From Leaderboards (field_hide_from_leaderboards) */
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['id'] = 'field_hide_from_leaderboards_value';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['table'] = 'field_data_field_hide_from_leaderboards';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['field'] = 'field_hide_from_leaderboards_value';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: User: Resources Posted Goal (field_resources_posted_goal) */
  $handler->display->display_options['filters']['field_resources_posted_goal_value']['id'] = 'field_resources_posted_goal_value';
  $handler->display->display_options['filters']['field_resources_posted_goal_value']['table'] = 'field_data_field_resources_posted_goal';
  $handler->display->display_options['filters']['field_resources_posted_goal_value']['field'] = 'field_resources_posted_goal_value';
  $handler->display->display_options['filters']['field_resources_posted_goal_value']['operator'] = '!=';
  $handler->display->display_options['filters']['field_resources_posted_goal_value']['value']['value'] = '0';
  /* Filter criterion: User: Resources Contributed (field_resources_contributed) */
  $handler->display->display_options['filters']['field_resources_contributed_value']['id'] = 'field_resources_contributed_value';
  $handler->display->display_options['filters']['field_resources_contributed_value']['table'] = 'field_data_field_resources_contributed';
  $handler->display->display_options['filters']['field_resources_contributed_value']['field'] = 'field_resources_contributed_value';
  $handler->display->display_options['filters']['field_resources_contributed_value']['operator'] = 'not empty';
  /* Filter criterion: User: Resources Contributed (field_resources_contributed) */
  $handler->display->display_options['filters']['field_resources_contributed_value_1']['id'] = 'field_resources_contributed_value_1';
  $handler->display->display_options['filters']['field_resources_contributed_value_1']['table'] = 'field_data_field_resources_contributed';
  $handler->display->display_options['filters']['field_resources_contributed_value_1']['field'] = 'field_resources_contributed_value';
  $handler->display->display_options['filters']['field_resources_contributed_value_1']['operator'] = '>';
  $handler->display->display_options['filters']['field_resources_contributed_value_1']['value']['value'] = '0';
  /* Filter criterion: Global: Field against variable comparison */
  $handler->display->display_options['filters']['variable_compare']['id'] = 'variable_compare';
  $handler->display->display_options['filters']['variable_compare']['table'] = 'views';
  $handler->display->display_options['filters']['variable_compare']['field'] = 'variable_compare';
  $handler->display->display_options['filters']['variable_compare']['operator'] = '>=';
  $handler->display->display_options['filters']['variable_compare']['variable'] = 'goals_start_date_timestamp';
  $handler->display->display_options['filters']['variable_compare']['left_field'] = 'login';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['contributed_resources_rankings'] = $view;

  $view = new view();
  $view->name = 'forum_rankings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Forum Rankings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p><strong>No activity yet!</strong></p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Taxonomy term: Add Forum Cover Image */
  $handler->display->display_options['fields']['field_state_or_district_image']['id'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['table'] = 'field_data_field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['field'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['label'] = '';
  $handler->display->display_options['fields']['field_state_or_district_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state_or_district_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_state_or_district_image']['settings'] = array(
    'image_style' => 'forum_profile_image_60x60',
    'image_link' => '',
  );
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'forum' => 'forum',
  );
  /* Filter criterion: Taxonomy term: Add to leaderboard (field_add_to_leaderboard) */
  $handler->display->display_options['filters']['field_add_to_leaderboard_value']['id'] = 'field_add_to_leaderboard_value';
  $handler->display->display_options['filters']['field_add_to_leaderboard_value']['table'] = 'field_data_field_add_to_leaderboard';
  $handler->display->display_options['filters']['field_add_to_leaderboard_value']['field'] = 'field_add_to_leaderboard_value';
  $handler->display->display_options['filters']['field_add_to_leaderboard_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Taxonomy term: States (field_forum_access_states) */
  $handler->display->display_options['filters']['field_forum_access_states_value']['id'] = 'field_forum_access_states_value';
  $handler->display->display_options['filters']['field_forum_access_states_value']['table'] = 'field_data_field_forum_access_states';
  $handler->display->display_options['filters']['field_forum_access_states_value']['field'] = 'field_forum_access_states_value';
  $handler->display->display_options['filters']['field_forum_access_states_value']['value'] = array(
    0 => '0',
  );

  /* Display: Rating Leaderboard */
  $handler = $view->new_display('block', 'Rating Leaderboard', 'rating_leaderboard');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Add Forum Cover Image */
  $handler->display->display_options['fields']['field_state_or_district_image']['id'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['table'] = 'field_data_field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['field'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['label'] = '';
  $handler->display->display_options['fields']['field_state_or_district_image']['alter']['text'] = '<img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/user-default-image.png" width="30px" height="30px" alt="Anonymous\'s picture" title="Anonymous\'s picture">';
  $handler->display->display_options['fields']['field_state_or_district_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state_or_district_image']['empty'] = '<img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/state-forum-default.png" width="30px" height="30px" alt="Forum picture" title="Forum picture">';
  $handler->display->display_options['fields']['field_state_or_district_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_state_or_district_image']['settings'] = array(
    'image_style' => 'leaderboard_30x33',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Educator Goal Complete */
  $handler->display->display_options['fields']['field_educator_goal_complete']['id'] = 'field_educator_goal_complete';
  $handler->display->display_options['fields']['field_educator_goal_complete']['table'] = 'field_data_field_educator_goal_complete';
  $handler->display->display_options['fields']['field_educator_goal_complete']['field'] = 'field_educator_goal_complete';
  $handler->display->display_options['fields']['field_educator_goal_complete']['label'] = '';
  $handler->display->display_options['fields']['field_educator_goal_complete']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_educator_goal_complete']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Educator Goal */
  $handler->display->display_options['fields']['field_educator_goal']['id'] = 'field_educator_goal';
  $handler->display->display_options['fields']['field_educator_goal']['table'] = 'field_data_field_educator_goal';
  $handler->display->display_options['fields']['field_educator_goal']['field'] = 'field_educator_goal';
  $handler->display->display_options['fields']['field_educator_goal']['label'] = '';
  $handler->display->display_options['fields']['field_educator_goal']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_educator_goal']['alter']['text'] = 'of [field_educator_goal]';
  $handler->display->display_options['fields']['field_educator_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_educator_goal']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Educator Goal Complete (field_educator_goal_complete) */
  $handler->display->display_options['sorts']['field_educator_goal_complete_value']['id'] = 'field_educator_goal_complete_value';
  $handler->display->display_options['sorts']['field_educator_goal_complete_value']['table'] = 'field_data_field_educator_goal_complete';
  $handler->display->display_options['sorts']['field_educator_goal_complete_value']['field'] = 'field_educator_goal_complete_value';
  $handler->display->display_options['sorts']['field_educator_goal_complete_value']['order'] = 'DESC';

  /* Display: Reviewed Leaderboard */
  $handler = $view->new_display('block', 'Reviewed Leaderboard', 'reviewed_leaderboard');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Add Forum Cover Image */
  $handler->display->display_options['fields']['field_state_or_district_image']['id'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['table'] = 'field_data_field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['field'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['label'] = '';
  $handler->display->display_options['fields']['field_state_or_district_image']['alter']['text'] = '<img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/user-default-image.png" width="30px" height="30px" alt="Anonymous\'s picture" title="Anonymous\'s picture">';
  $handler->display->display_options['fields']['field_state_or_district_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state_or_district_image']['empty'] = '<img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/state-forum-default.png" width="30px" height="30px" alt="Forum picture" title="Forum picture">';
  $handler->display->display_options['fields']['field_state_or_district_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_state_or_district_image']['settings'] = array(
    'image_style' => 'leaderboard_30x33',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Reviewer Goal Complete */
  $handler->display->display_options['fields']['field_reviewer_goal_complete']['id'] = 'field_reviewer_goal_complete';
  $handler->display->display_options['fields']['field_reviewer_goal_complete']['table'] = 'field_data_field_reviewer_goal_complete';
  $handler->display->display_options['fields']['field_reviewer_goal_complete']['field'] = 'field_reviewer_goal_complete';
  $handler->display->display_options['fields']['field_reviewer_goal_complete']['label'] = '';
  $handler->display->display_options['fields']['field_reviewer_goal_complete']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_reviewer_goal_complete']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Reviewer Goal */
  $handler->display->display_options['fields']['field_reviewer_goal']['id'] = 'field_reviewer_goal';
  $handler->display->display_options['fields']['field_reviewer_goal']['table'] = 'field_data_field_reviewer_goal';
  $handler->display->display_options['fields']['field_reviewer_goal']['field'] = 'field_reviewer_goal';
  $handler->display->display_options['fields']['field_reviewer_goal']['label'] = '';
  $handler->display->display_options['fields']['field_reviewer_goal']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_reviewer_goal']['alter']['text'] = 'of [field_reviewer_goal]';
  $handler->display->display_options['fields']['field_reviewer_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_reviewer_goal']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Reviewer Goal Complete (field_reviewer_goal_complete) */
  $handler->display->display_options['sorts']['field_reviewer_goal_complete_value']['id'] = 'field_reviewer_goal_complete_value';
  $handler->display->display_options['sorts']['field_reviewer_goal_complete_value']['table'] = 'field_data_field_reviewer_goal_complete';
  $handler->display->display_options['sorts']['field_reviewer_goal_complete_value']['field'] = 'field_reviewer_goal_complete_value';
  $handler->display->display_options['sorts']['field_reviewer_goal_complete_value']['order'] = 'DESC';

  /* Display: Contributed Leaderboard */
  $handler = $view->new_display('block', 'Contributed Leaderboard', 'contributed_leaderboard');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Add Forum Cover Image */
  $handler->display->display_options['fields']['field_state_or_district_image']['id'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['table'] = 'field_data_field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['field'] = 'field_state_or_district_image';
  $handler->display->display_options['fields']['field_state_or_district_image']['label'] = '';
  $handler->display->display_options['fields']['field_state_or_district_image']['alter']['text'] = '<img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/user-default-image.png" width="30px" height="30px" alt="Anonymous\'s picture" title="Anonymous\'s picture">';
  $handler->display->display_options['fields']['field_state_or_district_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state_or_district_image']['empty'] = '<img typeof="foaf:Image" src="/sites/all/themes/custom/SBAC/images/state-forum-default.png" width="30px" height="30px" alt="Forum picture" title="Forum picture">';
  $handler->display->display_options['fields']['field_state_or_district_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_state_or_district_image']['settings'] = array(
    'image_style' => 'leaderboard_30x33',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Contributor Goal Complete */
  $handler->display->display_options['fields']['field_contributor_goal_complete']['id'] = 'field_contributor_goal_complete';
  $handler->display->display_options['fields']['field_contributor_goal_complete']['table'] = 'field_data_field_contributor_goal_complete';
  $handler->display->display_options['fields']['field_contributor_goal_complete']['field'] = 'field_contributor_goal_complete';
  $handler->display->display_options['fields']['field_contributor_goal_complete']['label'] = '';
  $handler->display->display_options['fields']['field_contributor_goal_complete']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contributor_goal_complete']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Contributor Goal */
  $handler->display->display_options['fields']['field_contributor_goal']['id'] = 'field_contributor_goal';
  $handler->display->display_options['fields']['field_contributor_goal']['table'] = 'field_data_field_contributor_goal';
  $handler->display->display_options['fields']['field_contributor_goal']['field'] = 'field_contributor_goal';
  $handler->display->display_options['fields']['field_contributor_goal']['label'] = '';
  $handler->display->display_options['fields']['field_contributor_goal']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_contributor_goal']['alter']['text'] = 'of [field_contributor_goal]';
  $handler->display->display_options['fields']['field_contributor_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contributor_goal']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Contributor Goal Complete (field_contributor_goal_complete) */
  $handler->display->display_options['sorts']['field_contributor_goal_complete_value']['id'] = 'field_contributor_goal_complete_value';
  $handler->display->display_options['sorts']['field_contributor_goal_complete_value']['table'] = 'field_data_field_contributor_goal_complete';
  $handler->display->display_options['sorts']['field_contributor_goal_complete_value']['field'] = 'field_contributor_goal_complete_value';
  $handler->display->display_options['sorts']['field_contributor_goal_complete_value']['order'] = 'DESC';
  $export['forum_rankings'] = $view;

  $view = new view();
  $view->name = 'rated_resources_rankings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Rated resources rankings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Educator';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p><strong>No activity yet!</strong></p>
<!--<p>Start <a href="sbac-digital-library">browsing and rating resources</a> to get the list started.</p>-->';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: User: Resources Rated */
  $handler->display->display_options['fields']['field_resources_rated']['id'] = 'field_resources_rated';
  $handler->display->display_options['fields']['field_resources_rated']['table'] = 'field_data_field_resources_rated';
  $handler->display->display_options['fields']['field_resources_rated']['field'] = 'field_resources_rated';
  $handler->display->display_options['fields']['field_resources_rated']['label'] = '';
  $handler->display->display_options['fields']['field_resources_rated']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_resources_rated']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: User: Star Rating Goal */
  $handler->display->display_options['fields']['field_star_rating_goal']['id'] = 'field_star_rating_goal';
  $handler->display->display_options['fields']['field_star_rating_goal']['table'] = 'field_data_field_star_rating_goal';
  $handler->display->display_options['fields']['field_star_rating_goal']['field'] = 'field_star_rating_goal';
  $handler->display->display_options['fields']['field_star_rating_goal']['label'] = '';
  $handler->display->display_options['fields']['field_star_rating_goal']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_star_rating_goal']['alter']['text'] = 'of [field_star_rating_goal]';
  $handler->display->display_options['fields']['field_star_rating_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_star_rating_goal']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = '';
  $handler->display->display_options['fields']['login']['exclude'] = TRUE;
  $handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['login']['date_format'] = 'forum_listing';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'forum_listing';
  /* Sort criterion: User: Resources Rated (field_resources_rated) */
  $handler->display->display_options['sorts']['field_resources_rated_value']['id'] = 'field_resources_rated_value';
  $handler->display->display_options['sorts']['field_resources_rated_value']['table'] = 'field_data_field_resources_rated';
  $handler->display->display_options['sorts']['field_resources_rated_value']['field'] = 'field_resources_rated_value';
  $handler->display->display_options['sorts']['field_resources_rated_value']['order'] = 'DESC';
  /* Sort criterion: User: Last name (field_last_name) */
  $handler->display->display_options['sorts']['field_last_name_value']['id'] = 'field_last_name_value';
  $handler->display->display_options['sorts']['field_last_name_value']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['sorts']['field_last_name_value']['field'] = 'field_last_name_value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Hide From Leaderboards (field_hide_from_leaderboards) */
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['id'] = 'field_hide_from_leaderboards_value';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['table'] = 'field_data_field_hide_from_leaderboards';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['field'] = 'field_hide_from_leaderboards_value';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: User: Resources Rated (field_resources_rated) */
  $handler->display->display_options['filters']['field_resources_rated_value']['id'] = 'field_resources_rated_value';
  $handler->display->display_options['filters']['field_resources_rated_value']['table'] = 'field_data_field_resources_rated';
  $handler->display->display_options['filters']['field_resources_rated_value']['field'] = 'field_resources_rated_value';
  $handler->display->display_options['filters']['field_resources_rated_value']['operator'] = 'not empty';
  /* Filter criterion: User: Resources Rated (field_resources_rated) */
  $handler->display->display_options['filters']['field_resources_rated_value_1']['id'] = 'field_resources_rated_value_1';
  $handler->display->display_options['filters']['field_resources_rated_value_1']['table'] = 'field_data_field_resources_rated';
  $handler->display->display_options['filters']['field_resources_rated_value_1']['field'] = 'field_resources_rated_value';
  $handler->display->display_options['filters']['field_resources_rated_value_1']['operator'] = '>';
  $handler->display->display_options['filters']['field_resources_rated_value_1']['value']['value'] = '0';
  /* Filter criterion: User: Star Rating Goal (field_star_rating_goal) */
  $handler->display->display_options['filters']['field_star_rating_goal_value']['id'] = 'field_star_rating_goal_value';
  $handler->display->display_options['filters']['field_star_rating_goal_value']['table'] = 'field_data_field_star_rating_goal';
  $handler->display->display_options['filters']['field_star_rating_goal_value']['field'] = 'field_star_rating_goal_value';
  $handler->display->display_options['filters']['field_star_rating_goal_value']['operator'] = '!=';
  $handler->display->display_options['filters']['field_star_rating_goal_value']['value']['value'] = '0';
  /* Filter criterion: Global: Field against variable comparison */
  $handler->display->display_options['filters']['variable_compare']['id'] = 'variable_compare';
  $handler->display->display_options['filters']['variable_compare']['table'] = 'views';
  $handler->display->display_options['filters']['variable_compare']['field'] = 'variable_compare';
  $handler->display->display_options['filters']['variable_compare']['operator'] = '>=';
  $handler->display->display_options['filters']['variable_compare']['variable'] = 'goals_start_date_timestamp';
  $handler->display->display_options['filters']['variable_compare']['left_field'] = 'login';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['rated_resources_rankings'] = $view;

  $view = new view();
  $view->name = 'reviewed_resources_rankings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Reviewed resources rankings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Resource Reviewer';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p><strong>No activity yet!</strong></p>
<!--<p>Start <a href="resource-review">Start reviewing  resources</a> to get the list started.</p>
<p>Learn about contributing and reviewing resources <a href=\'\'>here</a></p>-->';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: User: Resources Reviewed */
  $handler->display->display_options['fields']['field_resources_reviewed']['id'] = 'field_resources_reviewed';
  $handler->display->display_options['fields']['field_resources_reviewed']['table'] = 'field_data_field_resources_reviewed';
  $handler->display->display_options['fields']['field_resources_reviewed']['field'] = 'field_resources_reviewed';
  $handler->display->display_options['fields']['field_resources_reviewed']['label'] = '';
  $handler->display->display_options['fields']['field_resources_reviewed']['element_class'] = 'reviewed-goal-completed';
  $handler->display->display_options['fields']['field_resources_reviewed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_resources_reviewed']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: User: Resources Reviewed Goal */
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['id'] = 'field_resources_reviewed_goal';
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['table'] = 'field_data_field_resources_reviewed_goal';
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['field'] = 'field_resources_reviewed_goal';
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['label'] = '';
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['alter']['text'] = 'of [field_resources_reviewed_goal]';
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_resources_reviewed_goal']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = '';
  $handler->display->display_options['fields']['login']['exclude'] = TRUE;
  $handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['login']['date_format'] = 'forum_listing';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'forum_listing';
  /* Sort criterion: User: Resources Reviewed (field_resources_reviewed) */
  $handler->display->display_options['sorts']['field_resources_reviewed_value']['id'] = 'field_resources_reviewed_value';
  $handler->display->display_options['sorts']['field_resources_reviewed_value']['table'] = 'field_data_field_resources_reviewed';
  $handler->display->display_options['sorts']['field_resources_reviewed_value']['field'] = 'field_resources_reviewed_value';
  $handler->display->display_options['sorts']['field_resources_reviewed_value']['order'] = 'DESC';
  /* Sort criterion: User: Last name (field_last_name) */
  $handler->display->display_options['sorts']['field_last_name_value']['id'] = 'field_last_name_value';
  $handler->display->display_options['sorts']['field_last_name_value']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['sorts']['field_last_name_value']['field'] = 'field_last_name_value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Hide From Leaderboards (field_hide_from_leaderboards) */
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['id'] = 'field_hide_from_leaderboards_value';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['table'] = 'field_data_field_hide_from_leaderboards';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['field'] = 'field_hide_from_leaderboards_value';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_hide_from_leaderboards_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: User: Resources Reviewed (field_resources_reviewed) */
  $handler->display->display_options['filters']['field_resources_reviewed_value']['id'] = 'field_resources_reviewed_value';
  $handler->display->display_options['filters']['field_resources_reviewed_value']['table'] = 'field_data_field_resources_reviewed';
  $handler->display->display_options['filters']['field_resources_reviewed_value']['field'] = 'field_resources_reviewed_value';
  $handler->display->display_options['filters']['field_resources_reviewed_value']['operator'] = 'not empty';
  /* Filter criterion: User: Resources Reviewed Goal (field_resources_reviewed_goal) */
  $handler->display->display_options['filters']['field_resources_reviewed_goal_value']['id'] = 'field_resources_reviewed_goal_value';
  $handler->display->display_options['filters']['field_resources_reviewed_goal_value']['table'] = 'field_data_field_resources_reviewed_goal';
  $handler->display->display_options['filters']['field_resources_reviewed_goal_value']['field'] = 'field_resources_reviewed_goal_value';
  $handler->display->display_options['filters']['field_resources_reviewed_goal_value']['operator'] = '!=';
  $handler->display->display_options['filters']['field_resources_reviewed_goal_value']['value']['value'] = '0';
  /* Filter criterion: User: Resources Reviewed (field_resources_reviewed) */
  $handler->display->display_options['filters']['field_resources_reviewed_value_1']['id'] = 'field_resources_reviewed_value_1';
  $handler->display->display_options['filters']['field_resources_reviewed_value_1']['table'] = 'field_data_field_resources_reviewed';
  $handler->display->display_options['filters']['field_resources_reviewed_value_1']['field'] = 'field_resources_reviewed_value';
  $handler->display->display_options['filters']['field_resources_reviewed_value_1']['operator'] = '>';
  $handler->display->display_options['filters']['field_resources_reviewed_value_1']['value']['value'] = '0';
  /* Filter criterion: Global: Field against variable comparison */
  $handler->display->display_options['filters']['variable_compare']['id'] = 'variable_compare';
  $handler->display->display_options['filters']['variable_compare']['table'] = 'views';
  $handler->display->display_options['filters']['variable_compare']['field'] = 'variable_compare';
  $handler->display->display_options['filters']['variable_compare']['operator'] = '>=';
  $handler->display->display_options['filters']['variable_compare']['variable'] = 'goals_start_date_timestamp';
  $handler->display->display_options['filters']['variable_compare']['left_field'] = 'login';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['reviewed_resources_rankings'] = $view;

  return $export;
}
