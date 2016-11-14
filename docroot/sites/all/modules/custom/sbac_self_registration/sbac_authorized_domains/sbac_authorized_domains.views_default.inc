<?php
/**
 * @file
 * sbac_authorized_domains.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_authorized_domains_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'authorized_domains';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_authorized_domains';
  $view->human_name = 'Authorized domains';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Authorized Domains';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer authorized domains';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Filter';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'field_domain' => 'field_domain',
    'field_domain_state' => 'field_domain_state',
    'field_district' => 'field_district',
    'uid' => 'uid',
    'changed' => 'changed',
    'created' => 'created',
    'edit_link' => 'edit_link',
    'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_domain' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_domain_state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_district' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Authorized domains: Domain */
  $handler->display->display_options['fields']['field_domain']['id'] = 'field_domain';
  $handler->display->display_options['fields']['field_domain']['table'] = 'field_data_field_domain';
  $handler->display->display_options['fields']['field_domain']['field'] = 'field_domain';
  /* Field: Authorized domains: State */
  $handler->display->display_options['fields']['field_domain_state']['id'] = 'field_domain_state';
  $handler->display->display_options['fields']['field_domain_state']['table'] = 'field_data_field_domain_state';
  $handler->display->display_options['fields']['field_domain_state']['field'] = 'field_domain_state';
  /* Field: Authorized domains: District */
  $handler->display->display_options['fields']['field_district']['id'] = 'field_district';
  $handler->display->display_options['fields']['field_district']['table'] = 'field_data_field_district';
  $handler->display->display_options['fields']['field_district']['field'] = 'field_district';
  /* Field: Authorized domains: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_authorized_domains';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Operations';
  /* Field: Authorized domains: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_authorized_domains';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = '';
  $handler->display->display_options['fields']['delete_link']['element_label_colon'] = FALSE;
  /* Sort criterion: Authorized domains: State (field_domain_state) */
  $handler->display->display_options['sorts']['field_domain_state_tid']['id'] = 'field_domain_state_tid';
  $handler->display->display_options['sorts']['field_domain_state_tid']['table'] = 'field_data_field_domain_state';
  $handler->display->display_options['sorts']['field_domain_state_tid']['field'] = 'field_domain_state_tid';
  /* Sort criterion: Authorized domains: District (field_district) */
  $handler->display->display_options['sorts']['field_district_tid']['id'] = 'field_district_tid';
  $handler->display->display_options['sorts']['field_district_tid']['table'] = 'field_data_field_district';
  $handler->display->display_options['sorts']['field_district_tid']['field'] = 'field_district_tid';
  /* Sort criterion: Authorized domains: Domain (field_domain) */
  $handler->display->display_options['sorts']['field_domain_value']['id'] = 'field_domain_value';
  $handler->display->display_options['sorts']['field_domain_value']['table'] = 'field_data_field_domain';
  $handler->display->display_options['sorts']['field_domain_value']['field'] = 'field_domain_value';
  /* Filter criterion: Authorized domains: Domain (field_domain) */
  $handler->display->display_options['filters']['field_domain_value']['id'] = 'field_domain_value';
  $handler->display->display_options['filters']['field_domain_value']['table'] = 'field_data_field_domain';
  $handler->display->display_options['filters']['field_domain_value']['field'] = 'field_domain_value';
  $handler->display->display_options['filters']['field_domain_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_domain_value']['group'] = 1;
  $handler->display->display_options['filters']['field_domain_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_domain_value']['expose']['operator_id'] = 'field_domain_value_op';
  $handler->display->display_options['filters']['field_domain_value']['expose']['label'] = 'Domain includes';
  $handler->display->display_options['filters']['field_domain_value']['expose']['operator'] = 'field_domain_value_op';
  $handler->display->display_options['filters']['field_domain_value']['expose']['identifier'] = 'field_domain_value';
  $handler->display->display_options['filters']['field_domain_value']['expose']['remember_roles'] = array(
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
  /* Filter criterion: Authorized domains: State (field_domain_state) */
  $handler->display->display_options['filters']['field_domain_state_tid']['id'] = 'field_domain_state_tid';
  $handler->display->display_options['filters']['field_domain_state_tid']['table'] = 'field_data_field_domain_state';
  $handler->display->display_options['filters']['field_domain_state_tid']['field'] = 'field_domain_state_tid';
  $handler->display->display_options['filters']['field_domain_state_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_domain_state_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_domain_state_tid']['expose']['operator_id'] = 'field_domain_state_tid_op';
  $handler->display->display_options['filters']['field_domain_state_tid']['expose']['label'] = 'State is';
  $handler->display->display_options['filters']['field_domain_state_tid']['expose']['operator'] = 'field_domain_state_tid_op';
  $handler->display->display_options['filters']['field_domain_state_tid']['expose']['identifier'] = 'field_domain_state_tid';
  $handler->display->display_options['filters']['field_domain_state_tid']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_domain_state_tid']['group_info']['label'] = 'State (field_domain_state)';
  $handler->display->display_options['filters']['field_domain_state_tid']['group_info']['identifier'] = 'field_domain_state_tid';
  $handler->display->display_options['filters']['field_domain_state_tid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_domain_state_tid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_domain_state_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_domain_state_tid']['vocabulary'] = 'states';
  /* Filter criterion: Authorized domains: District (field_district) */
  $handler->display->display_options['filters']['field_district_tid']['id'] = 'field_district_tid';
  $handler->display->display_options['filters']['field_district_tid']['table'] = 'field_data_field_district';
  $handler->display->display_options['filters']['field_district_tid']['field'] = 'field_district_tid';
  $handler->display->display_options['filters']['field_district_tid']['value'] = '';
  $handler->display->display_options['filters']['field_district_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_district_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_district_tid']['expose']['operator_id'] = 'field_district_tid_op';
  $handler->display->display_options['filters']['field_district_tid']['expose']['label'] = 'District includes';
  $handler->display->display_options['filters']['field_district_tid']['expose']['operator'] = 'field_district_tid_op';
  $handler->display->display_options['filters']['field_district_tid']['expose']['identifier'] = 'field_district_tid';
  $handler->display->display_options['filters']['field_district_tid']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_district_tid']['vocabulary'] = 'districts';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '1';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['path'] = 'admin/sbac/authorized-domains/authorized';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Authorized Domains';
  $handler->display->display_options['menu']['weight'] = '-4';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Authorized Domains';
  $handler->display->display_options['tab_options']['weight'] = '1';
  $handler->display->display_options['tab_options']['name'] = 'management';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Block';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'authorized-domains-export-%timestamp-full.csv';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['newline_token'] = '1';
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['path'] = 'admin/sbac-authorized-domains/list/authorized-domains-export.csv';
  $export['authorized_domains'] = $view;

  return $export;
}
