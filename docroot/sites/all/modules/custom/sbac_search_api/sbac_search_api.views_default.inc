<?php
/**
 * @file
 * sbac_search_api.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_search_api_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'search_api_resource_views';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'Search API Resource Views';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Instructional Resources';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '@total Results';
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['label'] = '';
  $handler->display->display_options['fields']['field_asset_downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_asset_downloads']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 0,
  );
  /* Field: Indexed Node: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['label'] = '';
  $handler->display->display_options['fields']['field_alt_body']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: HTML5 */
  $handler->display->display_options['fields']['field_html5']['id'] = 'field_html5';
  $handler->display->display_options['fields']['field_html5']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_html5']['field'] = 'field_html5';
  $handler->display->display_options['fields']['field_html5']['label'] = '';
  $handler->display->display_options['fields']['field_html5']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Sticky in lists */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['type'] = 'boolean';
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  $handler->display->display_options['fields']['sticky']['link_to_entity'] = 0;
  /* Field: Indexed Node: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Indexed Node: Unique Views */
  $handler->display->display_options['fields']['field_unique_views']['id'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_unique_views']['field'] = 'field_unique_views';
  $handler->display->display_options['fields']['field_unique_views']['label'] = '';
  $handler->display->display_options['fields']['field_unique_views']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_unique_views']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 0,
  );
  /* Field: Indexed Node: Digital Media Type(s) */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_digital_media_type']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_digital_media_type']['bypass_access'] = 0;
  /* Field: Indexed Node: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_grades']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_grades']['bypass_access'] = 0;
  /* Field: Indexed Node: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['field_subject']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_subject']['bypass_access'] = 0;
  /* Field: Indexed Node: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['label'] = '';
  $handler->display->display_options['fields']['url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['url']['display_as_link'] = FALSE;
  $handler->display->display_options['fields']['url']['link_to_entity'] = 0;
  /* Sort criterion: Indexed Node: Sticky in lists */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Indexed Node: Date changed */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Filter criterion: Indexed Node: Workbench moderation state */
  $handler->display->display_options['filters']['workbench_moderation_state']['id'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['workbench_moderation_state']['field'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['value'] = 'Published';

  /* Display: Instructional Resources */
  $handler = $view->new_display('page', 'Instructional Resources', 'instructional');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Instructional';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indexed Node: Workbench moderation state */
  $handler->display->display_options['filters']['workbench_moderation_state']['id'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['workbench_moderation_state']['field'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['value'] = 'Published';
  /* Filter criterion: Indexed Node: Resource Type */
  $handler->display->display_options['filters']['field_focus']['id'] = 'field_focus';
  $handler->display->display_options['filters']['field_focus']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_focus']['field'] = 'field_focus';
  $handler->display->display_options['filters']['field_focus']['value'] = array(
    84 => '84',
    86 => '86',
  );
  $handler->display->display_options['path'] = 'instructional';

  /* Display: Professional Learning Resources */
  $handler = $view->new_display('page', 'Professional Learning Resources', 'professional_learning');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Professional Learning';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indexed Node: Workbench moderation state */
  $handler->display->display_options['filters']['workbench_moderation_state']['id'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['workbench_moderation_state']['field'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['value'] = 'Published';
  /* Filter criterion: Indexed Node: Resource Type */
  $handler->display->display_options['filters']['field_focus']['id'] = 'field_focus';
  $handler->display->display_options['filters']['field_focus']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_focus']['field'] = 'field_focus';
  $handler->display->display_options['filters']['field_focus']['value'] = array(
    86 => '86',
    85 => '85',
  );
  $handler->display->display_options['path'] = 'professional-learning';

  /* Display: Playlist Resources */
  $handler = $view->new_display('page', 'Playlist Resources', 'playlist');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Playlist';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indexed Node: Workbench moderation state */
  $handler->display->display_options['filters']['workbench_moderation_state']['id'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['workbench_moderation_state']['field'] = 'workbench_moderation_state';
  $handler->display->display_options['filters']['workbench_moderation_state']['value'] = 'Published';
  /* Filter criterion: Indexed Node: Resource Type */
  $handler->display->display_options['filters']['field_focus']['id'] = 'field_focus';
  $handler->display->display_options['filters']['field_focus']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_focus']['field'] = 'field_focus';
  $handler->display->display_options['filters']['field_focus']['value'] = array(
    78306 => '78306',
  );
  $handler->display->display_options['path'] = 'playlist';
  $export['search_api_resource_views'] = $view;

  return $export;
}
