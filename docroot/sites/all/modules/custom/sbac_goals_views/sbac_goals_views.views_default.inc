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
<p>Start <a href="my-resources">Start submitting resources</a> to get the list started.</p>
<p>Learn about contributing and reviewing resources <a href=\'\'>here</a></p>';
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

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['contributed_resources_rankings'] = $view;

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
<p>Start <a href="sbac-digital-library">browsing and rating resources</a> to get the list started.</p>';
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
<p>Start <a href="resource-review">Start reviewing  resources</a> to get the list started.</p>
<p>Learn about contributing and reviewing resources <a href=\'\'>here</a></p>';
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

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['reviewed_resources_rankings'] = $view;

  return $export;
}
