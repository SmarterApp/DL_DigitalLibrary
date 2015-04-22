<?php
/**
 * @file
 * sbac_report.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_report_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'gate_keeping_reviews';
  $view->description = 'For the SNE report';
  $view->tag = 'default';
  $view->base_table = 'eck_feedback';
  $view->human_name = 'Gate-Keeping Reviews';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Gate-Keeping Reviews';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Feedback: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'eck_feedback';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: COUNT(Feedback: Id) */
  $handler->display->display_options['fields']['id_1']['id'] = 'id_1';
  $handler->display->display_options['fields']['id_1']['table'] = 'eck_feedback';
  $handler->display->display_options['fields']['id_1']['field'] = 'id';
  $handler->display->display_options['fields']['id_1']['group_type'] = 'count';
  $handler->display->display_options['fields']['id_1']['label'] = 'Number of Gate-Keeping Reviews';
  /* Field: SUM(Feedback: Meets Criteria) */
  $handler->display->display_options['fields']['met_criteria']['id'] = 'met_criteria';
  $handler->display->display_options['fields']['met_criteria']['table'] = 'eck_feedback';
  $handler->display->display_options['fields']['met_criteria']['field'] = 'met_criteria';
  $handler->display->display_options['fields']['met_criteria']['group_type'] = 'sum';
  $handler->display->display_options['fields']['met_criteria']['exclude'] = TRUE;
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Acceptance Rate';
  $handler->display->display_options['fields']['expression']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['expression']['alter']['text'] = '[met_criteria] ([expression])';
  $handler->display->display_options['fields']['expression']['empty'] = '0';
  $handler->display->display_options['fields']['expression']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['suffix'] = '%';
  $handler->display->display_options['fields']['expression']['expression'] = '([met_criteria]/[id_1])*100';
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression_1']['id'] = 'expression_1';
  $handler->display->display_options['fields']['expression_1']['table'] = 'views';
  $handler->display->display_options['fields']['expression_1']['field'] = 'expression';
  $handler->display->display_options['fields']['expression_1']['label'] = 'Return Count';
  $handler->display->display_options['fields']['expression_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['expression_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['expression_1']['precision'] = '0';
  $handler->display->display_options['fields']['expression_1']['expression'] = '[id_1]-[met_criteria]';
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression_2']['id'] = 'expression_2';
  $handler->display->display_options['fields']['expression_2']['table'] = 'views';
  $handler->display->display_options['fields']['expression_2']['field'] = 'expression';
  $handler->display->display_options['fields']['expression_2']['label'] = 'Return Rate';
  $handler->display->display_options['fields']['expression_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['expression_2']['alter']['text'] = '[expression_1] ([expression_2])';
  $handler->display->display_options['fields']['expression_2']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression_2']['precision'] = '0';
  $handler->display->display_options['fields']['expression_2']['suffix'] = '%';
  $handler->display->display_options['fields']['expression_2']['expression'] = '([expression_1]/[id_1])*100';
  /* Contextual filter: Feedback: Author */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'eck_feedback';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Feedback: Created */
  $handler->display->display_options['arguments']['created']['id'] = 'created';
  $handler->display->display_options['arguments']['created']['table'] = 'eck_feedback';
  $handler->display->display_options['arguments']['created']['field'] = 'created';
  $handler->display->display_options['arguments']['created']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['created']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['created']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['created']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['created']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['created']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['created']['not'] = 0;
  /* Filter criterion: Feedback: feedback type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_feedback';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gate_keeper' => 'gate_keeper',
  );
  /* Filter criterion: Feedback: Completed */
  $handler->display->display_options['filters']['completed']['id'] = 'completed';
  $handler->display->display_options['filters']['completed']['table'] = 'eck_feedback';
  $handler->display->display_options['filters']['completed']['field'] = 'completed';
  $handler->display->display_options['filters']['completed']['value']['value'] = '1';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['gate_keeping_reviews'] = $view;

  return $export;
}
