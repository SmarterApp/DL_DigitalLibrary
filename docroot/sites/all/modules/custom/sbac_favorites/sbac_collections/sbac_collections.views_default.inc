<?php
/**
 * @file
 * sbac_collections.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_collections_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'collection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Collection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: SBAC Favorites: Favorite */
  $handler->display->display_options['relationships']['id']['id'] = 'id';
  $handler->display->display_options['relationships']['id']['table'] = 'sbac_favorites';
  $handler->display->display_options['relationships']['id']['field'] = 'id';
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
  /* Sort criterion: SBAC Favorites: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'sbac_favorites';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'id';
  /* Sort criterion: SBAC Favorites: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'sbac_favorites';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'id';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: SBAC Favorites: Collection ID */
  $handler->display->display_options['arguments']['cid']['id'] = 'cid';
  $handler->display->display_options['arguments']['cid']['table'] = 'sbac_favorites';
  $handler->display->display_options['arguments']['cid']['field'] = 'cid';
  $handler->display->display_options['arguments']['cid']['relationship'] = 'id';
  $handler->display->display_options['arguments']['cid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['cid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['cid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['cid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['cid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'id';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['relationship'] = 'id';
  $handler->display->display_options['filters']['current']['value'] = '1';
  $handler->display->display_options['filters']['current']['group'] = 1;
  /* Filter criterion: Content: Is hidden (field_is_hidden) */
  $handler->display->display_options['filters']['field_is_hidden_value']['id'] = 'field_is_hidden_value';
  $handler->display->display_options['filters']['field_is_hidden_value']['table'] = 'field_data_field_is_hidden';
  $handler->display->display_options['filters']['field_is_hidden_value']['field'] = 'field_is_hidden_value';
  $handler->display->display_options['filters']['field_is_hidden_value']['relationship'] = 'id';
  $handler->display->display_options['filters']['field_is_hidden_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_is_hidden_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Workbench Moderation: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'id';
  $handler->display->display_options['filters']['state']['value'] = array(
    'published' => 'published',
  );
  /* Filter criterion: SBAC Favorites: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'sbac_favorites';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'id';
  $handler->display->display_options['filters']['type_1']['value'] = 'node';

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
  $handler->display->display_options['fields']['title']['relationship'] = 'id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['relationship'] = 'id';
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
  $handler->display->display_options['fields']['nid']['relationship'] = 'id';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['relationship'] = 'id';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['relationship'] = 'id';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['relationship'] = 'id';
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
  $handler->display->display_options['fields']['field_unique_views']['relationship'] = 'id';
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
  $handler->display->display_options['fields']['field_html5']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_html5']['label'] = '';
  $handler->display->display_options['fields']['field_html5']['element_label_colon'] = FALSE;
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'id';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;

  /* Display: User List View */
  $handler = $view->new_display('block', 'User List View', 'user_list_view');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'view-display-id-list_view';
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
  $handler->display->display_options['fields']['title']['relationship'] = 'id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_alt_body']['id'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['table'] = 'field_data_field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['field'] = 'field_alt_body';
  $handler->display->display_options['fields']['field_alt_body']['relationship'] = 'id';
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
  $handler->display->display_options['fields']['nid']['relationship'] = 'id';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['relationship'] = 'id';
  $handler->display->display_options['fields']['state']['label'] = '';
  $handler->display->display_options['fields']['state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  /* Field: Content: Sticky */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['relationship'] = 'id';
  $handler->display->display_options['fields']['sticky']['label'] = '';
  $handler->display->display_options['fields']['sticky']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['sticky']['not'] = 0;
  /* Field: Field: Grade(s) */
  $handler->display->display_options['fields']['field_grades']['id'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['table'] = 'field_data_field_grades';
  $handler->display->display_options['fields']['field_grades']['field'] = 'field_grades';
  $handler->display->display_options['fields']['field_grades']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_grades']['label'] = '';
  $handler->display->display_options['fields']['field_grades']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grades']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grades']['delta_offset'] = '0';
  /* Field: Field: Media Types */
  $handler->display->display_options['fields']['field_digital_media_type']['id'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['field'] = 'field_digital_media_type';
  $handler->display->display_options['fields']['field_digital_media_type']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_digital_media_type']['label'] = '';
  $handler->display->display_options['fields']['field_digital_media_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_digital_media_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_digital_media_type']['delta_offset'] = '0';
  /* Field: Field: Subjects and Domains */
  $handler->display->display_options['fields']['field_subject']['id'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['table'] = 'field_data_field_subject';
  $handler->display->display_options['fields']['field_subject']['field'] = 'field_subject';
  $handler->display->display_options['fields']['field_subject']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_subject']['label'] = '';
  $handler->display->display_options['fields']['field_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject']['delta_offset'] = '0';
  /* Field: Content: Asset Downloads */
  $handler->display->display_options['fields']['field_asset_downloads']['id'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['table'] = 'field_data_field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['field'] = 'field_asset_downloads';
  $handler->display->display_options['fields']['field_asset_downloads']['relationship'] = 'id';
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
  $handler->display->display_options['fields']['field_unique_views']['relationship'] = 'id';
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
  $handler->display->display_options['fields']['field_html5']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_html5']['label'] = '';
  $handler->display->display_options['fields']['field_html5']['element_label_colon'] = FALSE;
  /* Field: Content: Thumbnail URI */
  $handler->display->display_options['fields']['field_thumbnail_uri']['id'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['table'] = 'field_data_field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['field'] = 'field_thumbnail_uri';
  $handler->display->display_options['fields']['field_thumbnail_uri']['relationship'] = 'id';
  $handler->display->display_options['fields']['field_thumbnail_uri']['label'] = '';
  $handler->display->display_options['fields']['field_thumbnail_uri']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_thumbnail_uri']['type'] = 'text_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'id';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: SBAC Favorites: User ID */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'sbac_favorites';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'id';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'id';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['relationship'] = 'id';
  $handler->display->display_options['filters']['current']['value'] = '1';
  $handler->display->display_options['filters']['current']['group'] = 1;
  /* Filter criterion: Content: Is hidden (field_is_hidden) */
  $handler->display->display_options['filters']['field_is_hidden_value']['id'] = 'field_is_hidden_value';
  $handler->display->display_options['filters']['field_is_hidden_value']['table'] = 'field_data_field_is_hidden';
  $handler->display->display_options['filters']['field_is_hidden_value']['field'] = 'field_is_hidden_value';
  $handler->display->display_options['filters']['field_is_hidden_value']['relationship'] = 'id';
  $handler->display->display_options['filters']['field_is_hidden_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_is_hidden_value']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Workbench Moderation: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'id';
  $handler->display->display_options['filters']['state']['value'] = array(
    'published' => 'published',
  );
  /* Filter criterion: SBAC Favorites: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'sbac_favorites';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'id';
  $handler->display->display_options['filters']['type_1']['value'] = 'node';
  /* Filter criterion: SBAC Favorites: Collection ID */
  $handler->display->display_options['filters']['cid']['id'] = 'cid';
  $handler->display->display_options['filters']['cid']['table'] = 'sbac_favorites';
  $handler->display->display_options['filters']['cid']['field'] = 'cid';
  $handler->display->display_options['filters']['cid']['relationship'] = 'id';
  $handler->display->display_options['filters']['cid']['value']['value'] = '0';
  $export['collection'] = $view;

  $view = new view();
  $view->name = 'my_collections';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'My Collections';
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
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: SBAC Favorites: Favoritor */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'sbac_favorites';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: SBAC Favorites: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'sbac_favorites';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Sort criterion: SBAC Favorites: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'sbac_favorites';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'collection' => 'collection',
  );
  /* Filter criterion: SBAC Favorites: Collection ID */
  $handler->display->display_options['filters']['cid']['id'] = 'cid';
  $handler->display->display_options['filters']['cid']['table'] = 'sbac_favorites';
  $handler->display->display_options['filters']['cid']['field'] = 'cid';
  $handler->display->display_options['filters']['cid']['value']['value'] = '0';
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['my_collections'] = $view;

  return $export;
}
