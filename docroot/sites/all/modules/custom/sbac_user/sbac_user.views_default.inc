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

  return $export;
}
