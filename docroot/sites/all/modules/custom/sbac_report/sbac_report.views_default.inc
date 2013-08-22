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
  $view->name = 'contributed_resources';
  $view->description = 'For the SNE report';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Contributed Resources';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contributed Resources';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: COUNT(Content: Nid) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['group_type'] = 'count';
  $handler->display->display_options['fields']['nid']['label'] = 'Resources Contributed';
  $handler->display->display_options['fields']['nid']['empty'] = '0';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Created date */
  $handler->display->display_options['arguments']['created_fulldate']['id'] = 'created_fulldate';
  $handler->display->display_options['arguments']['created_fulldate']['table'] = 'node';
  $handler->display->display_options['arguments']['created_fulldate']['field'] = 'created_fulldate';
  $handler->display->display_options['arguments']['created_fulldate']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['created_fulldate']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['created_fulldate']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['created_fulldate']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );

  /* Display: Resources Summary */
  $handler = $view->new_display('block', 'Resources Summary', 'resources_summary');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: COUNT(Content: Nid) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['group_type'] = 'count';
  $handler->display->display_options['fields']['nid']['label'] = 'Resources Contributed';
  $handler->display->display_options['fields']['nid']['empty'] = '0';
  /* Field: SUM(Content: Published) */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['group_type'] = 'sum';
  $handler->display->display_options['fields']['status']['label'] = 'Contributed Resources Posted';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: SUM(Content: Sticky) */
  $handler->display->display_options['fields']['sticky']['id'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['table'] = 'node';
  $handler->display->display_options['fields']['sticky']['field'] = 'sticky';
  $handler->display->display_options['fields']['sticky']['group_type'] = 'sum';
  $handler->display->display_options['fields']['sticky']['label'] = 'Contributed Resources Posted with Distinction';
  $handler->display->display_options['fields']['sticky']['type'] = 'boolean';
  $handler->display->display_options['fields']['sticky']['not'] = 0;

  /* Display: Resources Details */
  $handler = $view->new_display('block', 'Resources Details', 'resources_details');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Display';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '5, 10, 15';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = 'All';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'created' => 'created',
    'state' => 'state',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Resource Title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Contribution Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/y h:m a';
  /* Field: Workbench Moderation: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['label'] = 'Post Status';
  $handler->display->display_options['fields']['state']['machine_name'] = 0;
  $export['contributed_resources'] = $view;

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

  $view = new view();
  $view->name = 'sne_details';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'SNE Details';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'SNE Details';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_type'] = 'div';
  $handler->display->display_options['fields']['picture']['element_class'] = 'column large-3 profile-pic';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = FALSE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['alter']['text'] = '[field_first_name] [field_last_name]';
  $handler->display->display_options['fields']['field_first_name']['element_type'] = 'h2';
  $handler->display->display_options['fields']['field_first_name']['element_class'] = 'name clearfix';
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: User: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['label'] = '';
  $handler->display->display_options['fields']['field_state']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_state']['alter']['text'] = 'SNE from [field_state]';
  $handler->display->display_options['fields']['field_state']['element_label_colon'] = FALSE;
  /* Field: User: District Name */
  $handler->display->display_options['fields']['field_district_name']['id'] = 'field_district_name';
  $handler->display->display_options['fields']['field_district_name']['table'] = 'field_data_field_district_name';
  $handler->display->display_options['fields']['field_district_name']['field'] = 'field_district_name';
  $handler->display->display_options['fields']['field_district_name']['label'] = '';
  $handler->display->display_options['fields']['field_district_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_district_name']['element_label_colon'] = FALSE;
  /* Field: User: School Name */
  $handler->display->display_options['fields']['field_school_name']['id'] = 'field_school_name';
  $handler->display->display_options['fields']['field_school_name']['table'] = 'field_data_field_school_name';
  $handler->display->display_options['fields']['field_school_name']['field'] = 'field_school_name';
  $handler->display->display_options['fields']['field_school_name']['label'] = '';
  $handler->display->display_options['fields']['field_school_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_school_name']['alter']['text'] = '[field_school_name] in [field_district_name]';
  $handler->display->display_options['fields']['field_school_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_school_name']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_school_name']['element_wrapper_class'] = 'profile-school';
  $handler->display->display_options['fields']['field_school_name']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_school_name']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_school_name']['delta_offset'] = '0';
  /* Field: User: Grade(s) */
  $handler->display->display_options['fields']['field_grade_level_s_']['id'] = 'field_grade_level_s_';
  $handler->display->display_options['fields']['field_grade_level_s_']['table'] = 'field_data_field_grade_level_s_';
  $handler->display->display_options['fields']['field_grade_level_s_']['field'] = 'field_grade_level_s_';
  $handler->display->display_options['fields']['field_grade_level_s_']['label'] = '';
  $handler->display->display_options['fields']['field_grade_level_s_']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_grade_level_s_']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_grade_level_s_']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_grade_level_s_']['delta_offset'] = '0';
  /* Field: Grades */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Grades';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div><span class="title">Grades: </span>[field_grade_level_s_]</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: User: Subject(s) */
  $handler->display->display_options['fields']['field_subject_s_']['id'] = 'field_subject_s_';
  $handler->display->display_options['fields']['field_subject_s_']['table'] = 'field_data_field_subject_s_';
  $handler->display->display_options['fields']['field_subject_s_']['field'] = 'field_subject_s_';
  $handler->display->display_options['fields']['field_subject_s_']['label'] = '';
  $handler->display->display_options['fields']['field_subject_s_']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_subject_s_']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_subject_s_']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_subject_s_']['delta_offset'] = '0';
  /* Field: Subjects */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Subjects';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<div><span class="title">Subjects: </span>[field_subject_s_]</div>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: User: Student Population(s) */
  $handler->display->display_options['fields']['field_special_populations']['id'] = 'field_special_populations';
  $handler->display->display_options['fields']['field_special_populations']['table'] = 'field_data_field_special_populations';
  $handler->display->display_options['fields']['field_special_populations']['field'] = 'field_special_populations';
  $handler->display->display_options['fields']['field_special_populations']['label'] = '';
  $handler->display->display_options['fields']['field_special_populations']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_special_populations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_special_populations']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_special_populations']['delta_offset'] = '0';
  /* Field: Student Populations */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['ui_name'] = 'Student Populations';
  $handler->display->display_options['fields']['nothing_2']['label'] = '';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = '<div><span class="title">Student Populations: </span>[field_special_populations]</div>';
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: User: State (field_state) */
  $handler->display->display_options['arguments']['field_state_value']['id'] = 'field_state_value';
  $handler->display->display_options['arguments']['field_state_value']['table'] = 'field_data_field_state';
  $handler->display->display_options['arguments']['field_state_value']['field'] = 'field_state_value';
  $handler->display->display_options['arguments']['field_state_value']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_state_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_state_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_state_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_state_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_state_value']['limit'] = '0';
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    15 => '15',
    17 => '17',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'sne_details');
  $handler->display->display_options['block_description'] = 'SNE Details';
  $export['sne_details'] = $view;

  return $export;
}
