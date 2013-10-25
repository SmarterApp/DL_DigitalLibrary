<?php
/**
 * @file
 * sbac_alignment.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_alignment_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'alignment';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Alignment';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Alignment';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Select your Common Core Standard(s) */
  $handler->display->display_options['fields']['field_education_alignment']['id'] = 'field_education_alignment';
  $handler->display->display_options['fields']['field_education_alignment']['table'] = 'field_data_field_education_alignment';
  $handler->display->display_options['fields']['field_education_alignment']['field'] = 'field_education_alignment';
  $handler->display->display_options['fields']['field_education_alignment']['label'] = 'Alignment';
  $handler->display->display_options['fields']['field_education_alignment']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_education_alignment']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_education_alignment']['delta_offset'] = '0';
  /* Field: Content: Alignment Type */
  $handler->display->display_options['fields']['field_alignment_type']['id'] = 'field_alignment_type';
  $handler->display->display_options['fields']['field_alignment_type']['table'] = 'field_data_field_alignment_type';
  $handler->display->display_options['fields']['field_alignment_type']['field'] = 'field_alignment_type';
  $handler->display->display_options['fields']['field_alignment_type']['label'] = 'Alignment';
  $handler->display->display_options['fields']['field_alignment_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_alignment_type']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'View Link';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<i class="accessibility foundicon-eyeball"></i>';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '<i class="gen-enclosed foundicon-edit"></i>';
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_wrapper_class'] = 'alignment-tag-edit';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['alter']['text'] = '<i class="gen-enclosed foundicon-remove"></i>';
  $handler->display->display_options['fields']['delete_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_node']['element_wrapper_class'] = 'alignment-tag-delete';
  $handler->display->display_options['fields']['delete_node']['text'] = 'Delete';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Resource Reference (field_resource_reference) */
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['id'] = 'field_resource_reference_target_id';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['table'] = 'field_data_field_resource_reference';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['field'] = 'field_resource_reference_target_id';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_resource_reference_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'alignment' => 'alignment',
  );

  /* Display: Alignment Tags */
  $handler = $view->new_display('block', 'Alignment Tags', 'resource_admin_view');
  $export['alignment'] = $view;

  return $export;
}
