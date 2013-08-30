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
  $view->name = 'all_resources';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'All Resources';
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
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_file']['id'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['table'] = 'field_data_field_file';
  $handler->display->display_options['fields']['field_file']['field'] = 'field_file';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  /* Filter criterion: Content: Temp (field_temp) */
  $handler->display->display_options['filters']['field_temp_value']['id'] = 'field_temp_value';
  $handler->display->display_options['filters']['field_temp_value']['table'] = 'field_data_field_temp';
  $handler->display->display_options['filters']['field_temp_value']['field'] = 'field_temp_value';
  $handler->display->display_options['filters']['field_temp_value']['value'] = array(
    0 => '0',
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
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'being_reviewed' => 'being_reviewed',
    'rejected' => 'rejected',
    'approved' => 'approved',
    'published' => 'published',
  );
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';

  /* Display: Digital Library Resources Grid View */
  $handler = $view->new_display('block', 'Digital Library Resources Grid View', 'grid_view');
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
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_file']['id'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['table'] = 'field_data_field_file';
  $handler->display->display_options['fields']['field_file']['field'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['label'] = '';
  $handler->display->display_options['fields']['field_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_file']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_file']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_file']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_file']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_file']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
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
  /* Field: Content: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Content: Digital Media Type(s) */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Content: Subjects and Domains */
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

  /* Display: Digital Library Resource List View */
  $handler = $view->new_display('block', 'Digital Library Resource List View', 'list_view');
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
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_file']['id'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['table'] = 'field_data_field_file';
  $handler->display->display_options['fields']['field_file']['field'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['label'] = '';
  $handler->display->display_options['fields']['field_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_file']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_file']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_file']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_file']['delta_offset'] = '0';
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
  /* Field: Content: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Content: Digital Media Type(s) */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Content: Subjects and Domains */
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
  $export['all_resources'] = $view;

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
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_file']['id'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['table'] = 'field_data_field_file';
  $handler->display->display_options['fields']['field_file']['field'] = 'field_file';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  /* Filter criterion: Content: Temp (field_temp) */
  $handler->display->display_options['filters']['field_temp_value']['id'] = 'field_temp_value';
  $handler->display->display_options['filters']['field_temp_value']['table'] = 'field_data_field_temp';
  $handler->display->display_options['filters']['field_temp_value']['field'] = 'field_temp_value';
  $handler->display->display_options['filters']['field_temp_value']['value'] = array(
    0 => '0',
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
    'draft' => 'draft',
    'needs_review' => 'needs_review',
    'being_reviewed' => 'being_reviewed',
    'rejected' => 'rejected',
    'approved' => 'approved',
    'published' => 'published',
  );
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  /* Filter criterion: Search: Search Terms */
  $handler->display->display_options['filters']['keys']['id'] = 'keys';
  $handler->display->display_options['filters']['keys']['table'] = 'search_index';
  $handler->display->display_options['filters']['keys']['field'] = 'keys';
  $handler->display->display_options['filters']['keys']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keys']['expose']['operator_id'] = 'keys_op';
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
  );
  /* Filter criterion: Content: Grade(s) (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
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
  );
  $handler->display->display_options['filters']['field_grades_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Content: Intended Student Population(s) (field_intended_student) */
  $handler->display->display_options['filters']['field_intended_student_tid']['id'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['table'] = 'field_data_field_intended_student';
  $handler->display->display_options['filters']['field_intended_student_tid']['field'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator_id'] = 'field_intended_student_tid_op';
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
  );
  $handler->display->display_options['filters']['field_intended_student_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_student_tid']['vocabulary'] = 'intended_student_populations';
  /* Filter criterion: Content: Digital Media Type(s) (field_digital_media_type) */
  $handler->display->display_options['filters']['field_digital_media_type_tid']['id'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['field'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['operator_id'] = 'field_digital_media_type_tid_op';
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
  );
  $handler->display->display_options['filters']['field_digital_media_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['vocabulary'] = 'digital_media_type';
  /* Filter criterion: Content: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
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
  );
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';
  /* Filter criterion: Content: Geographical Setting(s) (field_geographical_settings) */
  $handler->display->display_options['filters']['field_geographical_settings_tid']['id'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['table'] = 'field_data_field_geographical_settings';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['field'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['operator_id'] = 'field_geographical_settings_tid_op';
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
  );
  $handler->display->display_options['filters']['field_geographical_settings_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['vocabulary'] = 'geographical_settings';
  /* Filter criterion: Content: Educational Use (field_educational_use) */
  $handler->display->display_options['filters']['field_educational_use_tid']['id'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['table'] = 'field_data_field_educational_use';
  $handler->display->display_options['filters']['field_educational_use_tid']['field'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['operator_id'] = 'field_educational_use_tid_op';
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
  );
  $handler->display->display_options['filters']['field_educational_use_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_educational_use_tid']['vocabulary'] = 'educational_use';
  /* Filter criterion: Content: Intended End User(s) (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
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
  );
  $handler->display->display_options['filters']['field_intended_end_user_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['vocabulary'] = 'intended_end_user';
  /* Filter criterion: Content: Smarter Balanced Keyword(s) (field_smarter_balanced_keyword) */
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['id'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['table'] = 'field_data_field_smarter_balanced_keyword';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['field'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['operator_id'] = 'field_smarter_balanced_keyword_tid_op';
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
  );
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['vocabulary'] = 'smarter_balanced_keyword';
  /* Filter criterion: Content: Resource Type (field_focus) */
  $handler->display->display_options['filters']['field_focus_tid']['id'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['table'] = 'field_data_field_focus';
  $handler->display->display_options['filters']['field_focus_tid']['field'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator_id'] = 'field_focus_tid_op';
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
  );
  $handler->display->display_options['filters']['field_focus_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_focus_tid']['vocabulary'] = 'focus';
  /* Filter criterion: Content: Attributes (field_attributes) */
  $handler->display->display_options['filters']['field_attributes_tid']['id'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['table'] = 'field_data_field_attributes';
  $handler->display->display_options['filters']['field_attributes_tid']['field'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['operator_id'] = 'field_attributes_tid_op';
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
  );
  $handler->display->display_options['filters']['field_attributes_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_attributes_tid']['vocabulary'] = 'attributes';

  /* Display: Digital Library Resources Grid View */
  $handler = $view->new_display('block', 'Digital Library Resources Grid View', 'grid_view');
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
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_file']['id'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['table'] = 'field_data_field_file';
  $handler->display->display_options['fields']['field_file']['field'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['label'] = '';
  $handler->display->display_options['fields']['field_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_file']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_file']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_file']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_file']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_file']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['alter']['max_length'] = '140';
  $handler->display->display_options['fields']['field_alt_body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
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
  /* Field: Content: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Content: Digital Media Type(s) */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Content: Subjects and Domains */
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

  /* Display: Digital Library Resource List View */
  $handler = $view->new_display('block', 'Digital Library Resource List View', 'list_view');
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
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_file']['id'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['table'] = 'field_data_field_file';
  $handler->display->display_options['fields']['field_file']['field'] = 'field_file';
  $handler->display->display_options['fields']['field_file']['label'] = '';
  $handler->display->display_options['fields']['field_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_file']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_file']['type'] = 'file_url_plain';
  $handler->display->display_options['fields']['field_file']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_file']['delta_offset'] = '0';
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
  /* Field: Content: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Content: Digital Media Type(s) */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Content: Subjects and Domains */
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
  $export['resources'] = $view;

  return $export;
}
