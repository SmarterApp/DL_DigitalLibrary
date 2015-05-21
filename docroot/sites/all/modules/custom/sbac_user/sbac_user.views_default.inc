<?php
/**
 * @file
 * sbac_user.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_user_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'sbac_staging_user_exporter';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'SBAC Staging User Exporter';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Staging User Profiles';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer users';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['label'] = 'First Name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = 'Last Name';
  /* Field: User: Title */
  $handler->display->display_options['fields']['field_position']['id'] = 'field_position';
  $handler->display->display_options['fields']['field_position']['table'] = 'field_data_field_position';
  $handler->display->display_options['fields']['field_position']['field'] = 'field_position';
  /* Field: User: Retired */
  $handler->display->display_options['fields']['field_retired']['id'] = 'field_retired';
  $handler->display->display_options['fields']['field_retired']['table'] = 'field_data_field_retired';
  $handler->display->display_options['fields']['field_retired']['field'] = 'field_retired';
  $handler->display->display_options['fields']['field_retired']['label'] = 'Retiree';
  $handler->display->display_options['fields']['field_retired']['delta_offset'] = '0';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = 'Primary Email';
  /* Field: User: Alternate email address */
  $handler->display->display_options['fields']['field_alternate_email_address']['id'] = 'field_alternate_email_address';
  $handler->display->display_options['fields']['field_alternate_email_address']['table'] = 'field_data_field_alternate_email_address';
  $handler->display->display_options['fields']['field_alternate_email_address']['field'] = 'field_alternate_email_address';
  $handler->display->display_options['fields']['field_alternate_email_address']['label'] = 'Secondary Email';
  /* Field: Field: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['delta_offset'] = '0';
  /* Field: User: District Name */
  $handler->display->display_options['fields']['field_district_name']['id'] = 'field_district_name';
  $handler->display->display_options['fields']['field_district_name']['table'] = 'field_data_field_district_name';
  $handler->display->display_options['fields']['field_district_name']['field'] = 'field_district_name';
  $handler->display->display_options['fields']['field_district_name']['label'] = 'District';
  /* Field: User: School Name */
  $handler->display->display_options['fields']['field_school_name']['id'] = 'field_school_name';
  $handler->display->display_options['fields']['field_school_name']['table'] = 'field_data_field_school_name';
  $handler->display->display_options['fields']['field_school_name']['field'] = 'field_school_name';
  $handler->display->display_options['fields']['field_school_name']['label'] = 'School';
  $handler->display->display_options['fields']['field_school_name']['delta_offset'] = '0';
  /* Field: User: SLT Member */
  $handler->display->display_options['fields']['field_slt_member']['id'] = 'field_slt_member';
  $handler->display->display_options['fields']['field_slt_member']['table'] = 'field_data_field_slt_member';
  $handler->display->display_options['fields']['field_slt_member']['field'] = 'field_slt_member';
  $handler->display->display_options['fields']['field_slt_member']['label'] = 'isSLT';
  /* Field: User: SNE Member */
  $handler->display->display_options['fields']['field_sne_member']['id'] = 'field_sne_member';
  $handler->display->display_options['fields']['field_sne_member']['table'] = 'field_data_field_sne_member';
  $handler->display->display_options['fields']['field_sne_member']['field'] = 'field_sne_member';
  $handler->display->display_options['fields']['field_sne_member']['label'] = 'isSNE';
  /* Field: User: Subject(s) */
  $handler->display->display_options['fields']['field_subject_s_']['id'] = 'field_subject_s_';
  $handler->display->display_options['fields']['field_subject_s_']['table'] = 'field_data_field_subject_s_';
  $handler->display->display_options['fields']['field_subject_s_']['field'] = 'field_subject_s_';
  $handler->display->display_options['fields']['field_subject_s_']['label'] = 'Subjects';
  $handler->display->display_options['fields']['field_subject_s_']['delta_offset'] = '0';
  /* Field: User: Grade(s) */
  $handler->display->display_options['fields']['field_grade_level_s_']['id'] = 'field_grade_level_s_';
  $handler->display->display_options['fields']['field_grade_level_s_']['table'] = 'field_data_field_grade_level_s_';
  $handler->display->display_options['fields']['field_grade_level_s_']['field'] = 'field_grade_level_s_';
  $handler->display->display_options['fields']['field_grade_level_s_']['label'] = 'Grades';
  $handler->display->display_options['fields']['field_grade_level_s_']['delta_offset'] = '0';
  /* Field: User: Student Population(s) */
  $handler->display->display_options['fields']['field_special_populations']['id'] = 'field_special_populations';
  $handler->display->display_options['fields']['field_special_populations']['table'] = 'field_data_field_special_populations';
  $handler->display->display_options['fields']['field_special_populations']['field'] = 'field_special_populations';
  $handler->display->display_options['fields']['field_special_populations']['label'] = 'Student Populations';
  $handler->display->display_options['fields']['field_special_populations']['delta_offset'] = '0';
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/reports/sbac_user/list';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'admin/reports/sbac_user/list/export';
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '25';
  $export['sbac_staging_user_exporter'] = $view;

  $view = new view();
  $view->name = 'users';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Mini Profile Dev';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: User: Content authored */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'users';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: HIDDEN - UID */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['ui_name'] = 'HIDDEN - UID';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: HIDDEN - First Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['ui_name'] = 'HIDDEN - First Name';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_first_name']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_first_name']['settings'] = array(
    'title_style' => '_none',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: HIDDEN - Last Name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['ui_name'] = 'HIDDEN - Last Name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: HIDDEN - Title */
  $handler->display->display_options['fields']['field_position']['id'] = 'field_position';
  $handler->display->display_options['fields']['field_position']['table'] = 'field_data_field_position';
  $handler->display->display_options['fields']['field_position']['field'] = 'field_position';
  $handler->display->display_options['fields']['field_position']['ui_name'] = 'HIDDEN - Title';
  $handler->display->display_options['fields']['field_position']['label'] = '';
  $handler->display->display_options['fields']['field_position']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_position']['type'] = 'taxonomy_term_reference_plain';
  /* Field: HIDDEN - State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['ui_name'] = 'HIDDEN - State';
  $handler->display->display_options['fields']['field_state']['label'] = '';
  $handler->display->display_options['fields']['field_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_state']['delta_offset'] = '0';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['link_photo_to_profile'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'forum_profile_image_60x60';
  /* Field: Full Name */
  $handler->display->display_options['fields']['fields_combine']['id'] = 'fields_combine';
  $handler->display->display_options['fields']['fields_combine']['table'] = 'views';
  $handler->display->display_options['fields']['fields_combine']['field'] = 'fields_combine';
  $handler->display->display_options['fields']['fields_combine']['ui_name'] = 'Full Name';
  $handler->display->display_options['fields']['fields_combine']['label'] = 'Contributed By';
  $handler->display->display_options['fields']['fields_combine']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['fields_combine']['alter']['path'] = 'users/[uid]';
  $handler->display->display_options['fields']['fields_combine']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['fields_combine']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fields_combine']['hide_empty'] = 1;
  $handler->display->display_options['fields']['fields_combine']['combined_fields'] = array(
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
    'uid' => 0,
    'picture' => 0,
    'field_state' => 0,
    'field_position' => 0,
    'fields_combine_1' => 0,
    'nid' => 0,
  );
  $handler->display->display_options['fields']['fields_combine']['separator'] = ' ';
  /* Field: Title, St */
  $handler->display->display_options['fields']['fields_combine_1']['id'] = 'fields_combine_1';
  $handler->display->display_options['fields']['fields_combine_1']['table'] = 'views';
  $handler->display->display_options['fields']['fields_combine_1']['field'] = 'fields_combine';
  $handler->display->display_options['fields']['fields_combine_1']['ui_name'] = 'Title, St';
  $handler->display->display_options['fields']['fields_combine_1']['label'] = '';
  $handler->display->display_options['fields']['fields_combine_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fields_combine_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fields_combine_1']['combined_fields'] = array(
    'field_state' => 'field_state',
    'field_position' => 'field_position',
    'uid' => 0,
    'field_first_name' => 0,
    'field_last_name' => 0,
    'picture' => 0,
    'fields_combine' => 0,
    'nid' => 0,
  );
  $handler->display->display_options['fields']['fields_combine_1']['separator'] = ', ';
  /* Field: COUNT(Resources) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['nid']['group_type'] = 'count';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Resources';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['path'] = 'digital-library-resources?contributor=[uid]';
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['suffix'] = ' Resources';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'uid';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource' => 'resource',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['relationship'] = 'uid';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  /* Filter criterion: Workbench Moderation: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['current']['value'] = '1';
  /* Filter criterion: Workbench Moderation: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'uid';
  $handler->display->display_options['filters']['state']['value'] = array(
    'published' => 'published',
  );

  /* Display: Author Mini Profile */
  $handler = $view->new_display('block', 'Author Mini Profile', 'mini_profile');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '<none>';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: HIDDEN - UID */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['ui_name'] = 'HIDDEN - UID';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: HIDDEN - Privacy */
  $handler->display->display_options['fields']['field_privacy']['id'] = 'field_privacy';
  $handler->display->display_options['fields']['field_privacy']['table'] = 'field_data_field_privacy';
  $handler->display->display_options['fields']['field_privacy']['field'] = 'field_privacy';
  $handler->display->display_options['fields']['field_privacy']['ui_name'] = 'HIDDEN - Privacy';
  $handler->display->display_options['fields']['field_privacy']['label'] = '';
  $handler->display->display_options['fields']['field_privacy']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_privacy']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_privacy']['type'] = 'list_key';
  $handler->display->display_options['fields']['field_privacy']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_privacy']['delta_offset'] = '0';
  /* Field: HIDDEN - First Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['ui_name'] = 'HIDDEN - First Name';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_first_name']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_first_name']['settings'] = array(
    'title_style' => '_none',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: HIDDEN - Last Name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['ui_name'] = 'HIDDEN - Last Name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: HIDDEN - Title */
  $handler->display->display_options['fields']['field_position']['id'] = 'field_position';
  $handler->display->display_options['fields']['field_position']['table'] = 'field_data_field_position';
  $handler->display->display_options['fields']['field_position']['field'] = 'field_position';
  $handler->display->display_options['fields']['field_position']['ui_name'] = 'HIDDEN - Title';
  $handler->display->display_options['fields']['field_position']['label'] = '';
  $handler->display->display_options['fields']['field_position']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_position']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_position']['type'] = 'taxonomy_term_reference_plain';
  /* Field: HIDDEN - State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['ui_name'] = 'HIDDEN - State';
  $handler->display->display_options['fields']['field_state']['label'] = '';
  $handler->display->display_options['fields']['field_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_state']['delta_offset'] = '0';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['link_photo_to_profile'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'forum_profile_image_60x60';
  /* Field: Full Name */
  $handler->display->display_options['fields']['fields_combine']['id'] = 'fields_combine';
  $handler->display->display_options['fields']['fields_combine']['table'] = 'views';
  $handler->display->display_options['fields']['fields_combine']['field'] = 'fields_combine';
  $handler->display->display_options['fields']['fields_combine']['ui_name'] = 'Full Name';
  $handler->display->display_options['fields']['fields_combine']['label'] = 'Contributed By';
  $handler->display->display_options['fields']['fields_combine']['alter']['path'] = 'users/[uid]';
  $handler->display->display_options['fields']['fields_combine']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['fields_combine']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fields_combine']['hide_empty'] = 1;
  $handler->display->display_options['fields']['fields_combine']['combined_fields'] = array(
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
    'uid' => 0,
    'field_position' => 0,
    'field_state' => 0,
    'picture' => 0,
    'fields_combine_1' => 0,
    'nid' => 0,
  );
  $handler->display->display_options['fields']['fields_combine']['separator'] = ' ';
  /* Field: Title, St */
  $handler->display->display_options['fields']['fields_combine_1']['id'] = 'fields_combine_1';
  $handler->display->display_options['fields']['fields_combine_1']['table'] = 'views';
  $handler->display->display_options['fields']['fields_combine_1']['field'] = 'fields_combine';
  $handler->display->display_options['fields']['fields_combine_1']['ui_name'] = 'Title, St';
  $handler->display->display_options['fields']['fields_combine_1']['label'] = '';
  $handler->display->display_options['fields']['fields_combine_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['fields_combine_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['fields_combine_1']['combined_fields'] = array(
    'field_state' => 'field_state',
    'field_position' => 'field_position',
    'uid' => 0,
    'field_first_name' => 0,
    'field_last_name' => 0,
    'picture' => 0,
    'fields_combine' => 0,
    'nid' => 0,
  );
  $handler->display->display_options['fields']['fields_combine_1']['separator'] = ', ';
  /* Field: COUNT(DISTINCT Resources) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['nid']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Resources';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['path'] = 'digital-library-resources?contributor=[uid]';
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['suffix'] = ' Resources';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $export['users'] = $view;

  return $export;
}
