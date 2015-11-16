<?php
/**
 * @file
 * sbac_digital_library_resources.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_digital_library_resources_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'digital_library_resources';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'apachesolr__acquia_search_server_1';
  $view->human_name = 'Digital Library Resources';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Digital Library Resources';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Apache Solr: entity_id */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['label'] = '';
  $handler->display->display_options['fields']['entity_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['alter']['path'] = 'node/[entity_id]';
  $handler->display->display_options['fields']['entity_id']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['entity_id']['element_label_colon'] = FALSE;
  /* Sort criterion: Apache Solr: ds_created */
  $handler->display->display_options['sorts']['ds_created']['id'] = 'ds_created';
  $handler->display->display_options['sorts']['ds_created']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['sorts']['ds_created']['field'] = 'ds_created';
  $handler->display->display_options['sorts']['ds_created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['ds_created']['expose']['label'] = 'Newest';
  /* Sort criterion: Apache Solr: is_field_total_views */
  $handler->display->display_options['sorts']['is_field_total_views']['id'] = 'is_field_total_views';
  $handler->display->display_options['sorts']['is_field_total_views']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['sorts']['is_field_total_views']['field'] = 'is_field_total_views';
  $handler->display->display_options['sorts']['is_field_total_views']['order'] = 'DESC';
  $handler->display->display_options['sorts']['is_field_total_views']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['is_field_total_views']['expose']['label'] = 'Most Viewed';
  /* Sort criterion: Apache Solr: fs_field_node_avg_rating */
  $handler->display->display_options['sorts']['fs_field_node_avg_rating']['id'] = 'fs_field_node_avg_rating';
  $handler->display->display_options['sorts']['fs_field_node_avg_rating']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['sorts']['fs_field_node_avg_rating']['field'] = 'fs_field_node_avg_rating';
  $handler->display->display_options['sorts']['fs_field_node_avg_rating']['order'] = 'DESC';
  $handler->display->display_options['sorts']['fs_field_node_avg_rating']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['fs_field_node_avg_rating']['expose']['label'] = 'Highest Rated';
  /* Filter criterion: Full Text Search */
  $handler->display->display_options['filters']['keyword']['id'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['keyword']['field'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['ui_name'] = 'Full Text Search';
  $handler->display->display_options['filters']['keyword']['group'] = 1;
  $handler->display->display_options['filters']['keyword']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['keyword']['expose']['operator'] = 'keyword_op';
  $handler->display->display_options['filters']['keyword']['expose']['identifier'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['remember_roles'] = array(
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
    36 => 0,
  );
  /* Filter criterion: Apache Solr: entity_type */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['value'] = 'node';
  $handler->display->display_options['filters']['entity_type']['group'] = 1;
  /* Filter criterion: Apache Solr: bundle */
  $handler->display->display_options['filters']['bundle']['id'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['bundle']['field'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['value'] = 'resource';
  $handler->display->display_options['filters']['bundle']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '1';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: View area */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'digital_library_resources:attachment_1';
  $handler->display->display_options['path'] = 'digital-library-resources';

  /* Display: Atch. Posted w/Distinction */
  $handler = $view->new_display('attachment', 'Atch. Posted w/Distinction', 'attachment_1');
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'page';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Full Text Search */
  $handler->display->display_options['filters']['keyword']['id'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['keyword']['field'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['ui_name'] = 'Full Text Search';
  $handler->display->display_options['filters']['keyword']['group'] = 1;
  $handler->display->display_options['filters']['keyword']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['keyword']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['keyword']['expose']['operator'] = 'keyword_op';
  $handler->display->display_options['filters']['keyword']['expose']['identifier'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['remember_roles'] = array(
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
    36 => 0,
  );
  /* Filter criterion: Apache Solr: entity_type */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['value'] = 'node';
  $handler->display->display_options['filters']['entity_type']['group'] = 1;
  /* Filter criterion: Apache Solr: bundle */
  $handler->display->display_options['filters']['bundle']['id'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['bundle']['field'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['value'] = 'resource';
  $handler->display->display_options['filters']['bundle']['group'] = 1;
  /* Filter criterion: Apache Solr: is_field_posting_options */
  $handler->display->display_options['filters']['is_field_posting_options']['id'] = 'is_field_posting_options';
  $handler->display->display_options['filters']['is_field_posting_options']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['is_field_posting_options']['field'] = 'is_field_posting_options';
  $handler->display->display_options['filters']['is_field_posting_options']['value'] = '1';

  /* Display: Page Posted w/Distinction */
  $handler = $view->new_display('page', 'Page Posted w/Distinction', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '1';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Full Text Search */
  $handler->display->display_options['filters']['keyword']['id'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['keyword']['field'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['ui_name'] = 'Full Text Search';
  $handler->display->display_options['filters']['keyword']['group'] = 1;
  $handler->display->display_options['filters']['keyword']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['keyword']['expose']['operator'] = 'keyword_op';
  $handler->display->display_options['filters']['keyword']['expose']['identifier'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['remember_roles'] = array(
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
    36 => 0,
  );
  /* Filter criterion: Apache Solr: entity_type */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['value'] = 'node';
  $handler->display->display_options['filters']['entity_type']['group'] = 1;
  /* Filter criterion: Apache Solr: bundle */
  $handler->display->display_options['filters']['bundle']['id'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['bundle']['field'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['value'] = 'resource';
  $handler->display->display_options['filters']['bundle']['group'] = 1;
  /* Filter criterion: Apache Solr: is_field_posting_options */
  $handler->display->display_options['filters']['is_field_posting_options']['id'] = 'is_field_posting_options';
  $handler->display->display_options['filters']['is_field_posting_options']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['is_field_posting_options']['field'] = 'is_field_posting_options';
  $handler->display->display_options['filters']['is_field_posting_options']['value'] = '1';
  $handler->display->display_options['path'] = 'digital-library-resources/distinguished';
  $export['digital_library_resources'] = $view;

  return $export;
}
