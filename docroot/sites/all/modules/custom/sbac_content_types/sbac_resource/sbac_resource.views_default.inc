<?php
/**
 * @file
 * sbac_resource.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_resource_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'my_resources';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'My Resources';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Digital Library Resources';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Post date (Newest)';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created_1']['id'] = 'created_1';
  $handler->display->display_options['sorts']['created_1']['table'] = 'node';
  $handler->display->display_options['sorts']['created_1']['field'] = 'created';
  $handler->display->display_options['sorts']['created_1']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created_1']['expose']['label'] = 'Post date (Oldest)';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title (Alphabetical)';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  $handler->display->display_options['filters']['current']['group'] = 1;
  /* Filter criterion: Field: Grades (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_grades_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grades';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_grades_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['label'] = 'Subjects';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['identifier'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_subject_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';
  /* Filter criterion: Field: Resource Type (field_focus) */
  $handler->display->display_options['filters']['field_focus_tid']['id'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['table'] = 'field_data_field_focus';
  $handler->display->display_options['filters']['field_focus_tid']['field'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_focus_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator_id'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['label'] = 'Resource Type';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['identifier'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_focus_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_focus_tid']['vocabulary'] = 'focus';
  /* Filter criterion: Content: Author uid */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'node';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  /* Filter criterion: Content: Is hidden (field_is_hidden) */
  $handler->display->display_options['filters']['field_is_hidden_value']['id'] = 'field_is_hidden_value';
  $handler->display->display_options['filters']['field_is_hidden_value']['table'] = 'field_data_field_is_hidden';
  $handler->display->display_options['filters']['field_is_hidden_value']['field'] = 'field_is_hidden_value';
  $handler->display->display_options['filters']['field_is_hidden_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_is_hidden_value']['value'] = array(
    1 => '1',
  );

  /* Display: Grid View */
  $handler = $view->new_display('block', 'Grid View', 'grid_view');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'grid-library';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['type'] = 'text_plain';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'boolean';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grades */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['text'] = '[field_asset_downloads]';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['alter']['text'] = '[field_unique_views-value]';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: HTML5 */
  $handler->display->display_options['fields']['field_html5']['id'] = 'field_html5';
  $handler->display->display_options['fields']['field_html5']['table'] = 'field_data_field_html5';
  $handler->display->display_options['fields']['field_html5']['field'] = 'field_html5';
  $handler->display->display_options['fields']['field_html5']['label'] = '';
  $handler->display->display_options['fields']['field_html5']['element_label_colon'] = FALSE;
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;

  /* Display: List View */
  $handler = $view->new_display('block', 'List View', 'list_view');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['type'] = 'text_plain';
  /* Field: Content revision: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node_revision';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grades */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['text'] = '[field_asset_downloads]';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['alter']['text'] = '[field_unique_views]';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: HTML5 */
  $handler->display->display_options['fields']['field_html5']['id'] = 'field_html5';
  $handler->display->display_options['fields']['field_html5']['table'] = 'field_data_field_html5';
  $handler->display->display_options['fields']['field_html5']['field'] = 'field_html5';
  $handler->display->display_options['fields']['field_html5']['label'] = '';
  $handler->display->display_options['fields']['field_html5']['element_label_colon'] = FALSE;
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $export['my_resources'] = $view;

  $view = new view();
  $view->name = 'resource_review';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Resource Review';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Digital Library Resources';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  /* Filter criterion: Workbench Moderation: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    'needs_review' => 'needs_review',
    'being_reviewed' => 'being_reviewed',
    'approved' => 'approved',
  );
  $handler->display->display_options['filters']['state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['label'] = 'Resource States';
  $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
  $handler->display->display_options['filters']['state']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  /* Filter criterion: Field: Grades (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grades';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_grades_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['label'] = 'Subjects';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['identifier'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_subject_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';
  /* Filter criterion: Field: Intended Participants (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['label'] = 'Intended End Users';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['identifier'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_intended_end_user_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['vocabulary'] = 'intended_end_user';
  /* Filter criterion: Field: Resource Type (field_focus) */
  $handler->display->display_options['filters']['field_focus_tid']['id'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['table'] = 'field_data_field_focus';
  $handler->display->display_options['filters']['field_focus_tid']['field'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator_id'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['label'] = 'Resource Type';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['identifier'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_focus_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_focus_tid']['vocabulary'] = 'focus';

  /* Display: Grid View */
  $handler = $view->new_display('block', 'Grid View', 'grid_view');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'grid-library';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['type'] = 'text_plain';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'boolean';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grades */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['text'] = '[field_asset_downloads] Downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['alter']['text'] = '[field_unique_views-value] Views';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;

  /* Display: List View */
  $handler = $view->new_display('block', 'List View', 'list_view');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['type'] = 'text_plain';
  /* Field: Content revision: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node_revision';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grades */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['alter']['text'] = '[field_asset_downloads] Downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['alter']['text'] = '[field_unique_views] Views';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $export['resource_review'] = $view;

  $view = new view();
  $view->name = 'resources';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Resources';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Digital Library Resources';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  /* Sort criterion: Content revision: Updated date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  $handler->display->display_options['sorts']['timestamp']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['timestamp']['expose']['label'] = 'Updated date';
  /* Sort criterion: Content: Unique Views (field_unique_views) */
  $handler->display->display_options['sorts']['field_unique_views_value']['id'] = 'field_unique_views_value';
  $handler->display->display_options['sorts']['field_unique_views_value']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['sorts']['field_unique_views_value']['field'] = 'field_unique_views_value';
  $handler->display->display_options['sorts']['field_unique_views_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_unique_views_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_unique_views_value']['expose']['label'] = 'Number of Views';
  /* Sort criterion: Content: Node Avg Rating (field_node_avg_rating) */
  $handler->display->display_options['sorts']['field_node_avg_rating_value']['id'] = 'field_node_avg_rating_value';
  $handler->display->display_options['sorts']['field_node_avg_rating_value']['table'] = 'field_data_field_node_avg_rating';
  $handler->display->display_options['sorts']['field_node_avg_rating_value']['field'] = 'field_node_avg_rating_value';
  $handler->display->display_options['sorts']['field_node_avg_rating_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_node_avg_rating_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_node_avg_rating_value']['expose']['label'] = 'Node Avg Rating (field_node_avg_rating)';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tid']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  $handler->display->display_options['filters']['current']['group'] = 1;
  /* Filter criterion: Workbench Moderation: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    'published' => 'published',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
  /* Filter criterion: Field: Grades (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_grades_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_grades_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grade';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_grades_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Student Populations (field_intended_student) */
  $handler->display->display_options['filters']['field_intended_student_tid']['id'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['table'] = 'field_data_field_intended_student';
  $handler->display->display_options['filters']['field_intended_student_tid']['field'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_intended_student_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_student_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator_id'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['label'] = 'Student Population';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['identifier'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_intended_student_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_student_tid']['vocabulary'] = 'intended_student_populations';
  /* Filter criterion: Field: Media Types (field_digital_media_type) */
  $handler->display->display_options['filters']['field_digital_media_type_tid']['id'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['field'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['operator_id'] = 'field_digital_media_type_tid_op';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['label'] = 'Digital Media Type';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['operator'] = 'field_digital_media_type_tid_op';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['identifier'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_digital_media_type_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['vocabulary'] = 'digital_media_type';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['label'] = 'Subject';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['identifier'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_subject_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';
  /* Filter criterion: Field: Geographic Settings (field_geographical_settings) */
  $handler->display->display_options['filters']['field_geographical_settings_tid']['id'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['table'] = 'field_data_field_geographical_settings';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['field'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['operator_id'] = 'field_geographical_settings_tid_op';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['label'] = 'Geographical Settings';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['operator'] = 'field_geographical_settings_tid_op';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['identifier'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_geographical_settings_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['vocabulary'] = 'geographical_settings';
  /* Filter criterion: Field: Educational Use (field_educational_use) */
  $handler->display->display_options['filters']['field_educational_use_tid']['id'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['table'] = 'field_data_field_educational_use';
  $handler->display->display_options['filters']['field_educational_use_tid']['field'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_educational_use_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_educational_use_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['operator_id'] = 'field_educational_use_tid_op';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['label'] = 'Educational Use';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['operator'] = 'field_educational_use_tid_op';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['identifier'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_educational_use_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_educational_use_tid']['vocabulary'] = 'educational_use';
  /* Filter criterion: Field: Intended Participants (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['label'] = 'Intended End User';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['identifier'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_intended_end_user_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['vocabulary'] = 'intended_end_user';
  /* Filter criterion: Field: Module Type (field_smarter_balanced_keyword) */
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['id'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['table'] = 'field_data_field_smarter_balanced_keyword';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['field'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['operator_id'] = 'field_smarter_balanced_keyword_tid_op';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['label'] = 'Smarter Balanced Keyword';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['operator'] = 'field_smarter_balanced_keyword_tid_op';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['identifier'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['vocabulary'] = 'smarter_balanced_keyword';
  /* Filter criterion: Field: Resource Type (field_focus) */
  $handler->display->display_options['filters']['field_focus_tid']['id'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['table'] = 'field_data_field_focus';
  $handler->display->display_options['filters']['field_focus_tid']['field'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_focus_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_focus_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator_id'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['label'] = 'Focus';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['identifier'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_focus_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_focus_tid']['vocabulary'] = 'focus';
  /* Filter criterion: Field: Attributes of the Formative Assessment Process (field_attributes) */
  $handler->display->display_options['filters']['field_attributes_tid']['id'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['table'] = 'field_data_field_attributes';
  $handler->display->display_options['filters']['field_attributes_tid']['field'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['operator'] = 'and';
  $handler->display->display_options['filters']['field_attributes_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_attributes_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['operator_id'] = 'field_attributes_tid_op';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['label'] = 'Attributes';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['operator'] = 'field_attributes_tid_op';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['identifier'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  $handler->display->display_options['filters']['field_attributes_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_attributes_tid']['vocabulary'] = 'attributes';
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['group'] = 1;
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['keys']['expose']['operator'] = 'keys_op';
  $handler->display->display_options['filters']['keys']['expose']['identifier'] = 'keys';
  $handler->display->display_options['filters']['keys']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    27 => 0,
  );
  $handler->display->display_options['filters']['keys']['remove_score'] = TRUE;
  /* Filter criterion: Content: Sticky */
  $handler->display->display_options['filters']['sticky']['id'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['table'] = 'node';
  $handler->display->display_options['filters']['sticky']['field'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['value'] = 'All';
  $handler->display->display_options['filters']['sticky']['group'] = 1;
  $handler->display->display_options['filters']['sticky']['exposed'] = TRUE;
  $handler->display->display_options['filters']['sticky']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['sticky']['expose']['label'] = 'Sticky';
  $handler->display->display_options['filters']['sticky']['expose']['operator'] = 'sticky_op';
  $handler->display->display_options['filters']['sticky']['expose']['identifier'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
  );
  /* Filter criterion: User: The user ID */
  $handler->display->display_options['filters']['uid_raw']['id'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['table'] = 'users';
  $handler->display->display_options['filters']['uid_raw']['field'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_raw']['group'] = 1;
  $handler->display->display_options['filters']['uid_raw']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid_raw']['expose']['operator_id'] = 'uid_raw_op';
  $handler->display->display_options['filters']['uid_raw']['expose']['label'] = 'The user ID';
  $handler->display->display_options['filters']['uid_raw']['expose']['operator'] = 'uid_raw_op';
  $handler->display->display_options['filters']['uid_raw']['expose']['identifier'] = 'contributor';
  $handler->display->display_options['filters']['uid_raw']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
    32 => 0,
  );
  /* Filter criterion: Content: Owner (field_publisher) */
  $handler->display->display_options['filters']['field_publisher_value']['id'] = 'field_publisher_value';
  $handler->display->display_options['filters']['field_publisher_value']['table'] = 'field_data_field_publisher';
  $handler->display->display_options['filters']['field_publisher_value']['field'] = 'field_publisher_value';
  $handler->display->display_options['filters']['field_publisher_value']['group'] = 2;
  $handler->display->display_options['filters']['field_publisher_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_publisher_value']['expose']['operator_id'] = 'field_publisher_value_op';
  $handler->display->display_options['filters']['field_publisher_value']['expose']['label'] = 'Owner';
  $handler->display->display_options['filters']['field_publisher_value']['expose']['operator'] = 'field_publisher_value_op';
  $handler->display->display_options['filters']['field_publisher_value']['expose']['identifier'] = 'owner';
  $handler->display->display_options['filters']['field_publisher_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
    32 => 0,
  );
  /* Filter criterion: Content: Author (field_author) */
  $handler->display->display_options['filters']['field_author_value']['id'] = 'field_author_value';
  $handler->display->display_options['filters']['field_author_value']['table'] = 'field_data_field_author';
  $handler->display->display_options['filters']['field_author_value']['field'] = 'field_author_value';
  $handler->display->display_options['filters']['field_author_value']['group'] = 2;
  $handler->display->display_options['filters']['field_author_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_author_value']['expose']['operator_id'] = 'field_author_value_op';
  $handler->display->display_options['filters']['field_author_value']['expose']['label'] = 'author';
  $handler->display->display_options['filters']['field_author_value']['expose']['operator'] = 'field_author_value_op';
  $handler->display->display_options['filters']['field_author_value']['expose']['identifier'] = 'author';
  $handler->display->display_options['filters']['field_author_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    25 => 0,
    24 => 0,
    15 => 0,
    17 => 0,
    16 => 0,
    11 => 0,
    13 => 0,
    7 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    26 => 0,
    31 => 0,
    32 => 0,
  );

  /* Display: Grid View */
  $handler = $view->new_display('block', 'Grid View', 'grid_view');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'grid-library';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['type'] = 'text_plain';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'boolean';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grades */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['block_caching'] = '6';

  /* Display: List View */
  $handler = $view->new_display('block', 'List View', 'list_view');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_type'] = 'p';
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_alt_body']['type'] = 'text_plain';
  /* Field: Content revision: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node_revision';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grades */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'field_data_field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['block_caching'] = '6';
  $export['resources'] = $view;

  return $export;
}
