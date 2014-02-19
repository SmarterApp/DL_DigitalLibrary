<?php
/**
 * @file
 * sbac_forum.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sbac_forum_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'forum_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Forum List';
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
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Load More Forums';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'forums/term/[tid]';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Facilitators */
  $handler->display->display_options['fields']['field_forum_facilitators']['id'] = 'field_forum_facilitators';
  $handler->display->display_options['fields']['field_forum_facilitators']['table'] = 'field_data_field_forum_facilitators';
  $handler->display->display_options['fields']['field_forum_facilitators']['field'] = 'field_forum_facilitators';
  $handler->display->display_options['fields']['field_forum_facilitators']['label'] = '';
  $handler->display->display_options['fields']['field_forum_facilitators']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_forum_facilitators']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_facilitators']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_forum_facilitators']['delta_offset'] = '0';
  /* Field: Taxonomy term: Members */
  $handler->display->display_options['fields']['field_fc_forum_members']['id'] = 'field_fc_forum_members';
  $handler->display->display_options['fields']['field_fc_forum_members']['table'] = 'field_data_field_fc_forum_members';
  $handler->display->display_options['fields']['field_fc_forum_members']['field'] = 'field_fc_forum_members';
  $handler->display->display_options['fields']['field_fc_forum_members']['label'] = '';
  $handler->display->display_options['fields']['field_fc_forum_members']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_fc_forum_members']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fc_forum_members']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_fc_forum_members']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_fc_forum_members']['delta_offset'] = '0';
  /* Field: Taxonomy term: Last Activity */
  $handler->display->display_options['fields']['field_forum_last_activity']['id'] = 'field_forum_last_activity';
  $handler->display->display_options['fields']['field_forum_last_activity']['table'] = 'field_data_field_forum_last_activity';
  $handler->display->display_options['fields']['field_forum_last_activity']['field'] = 'field_forum_last_activity';
  $handler->display->display_options['fields']['field_forum_last_activity']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Taxonomy term: Topic Count */
  $handler->display->display_options['fields']['field_forum_topic_count']['id'] = 'field_forum_topic_count';
  $handler->display->display_options['fields']['field_forum_topic_count']['table'] = 'field_data_field_forum_topic_count';
  $handler->display->display_options['fields']['field_forum_topic_count']['field'] = 'field_forum_topic_count';
  $handler->display->display_options['fields']['field_forum_topic_count']['label'] = '';
  $handler->display->display_options['fields']['field_forum_topic_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Reply (comment) Count */
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['id'] = 'field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['field'] = 'field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['label'] = '';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Member Count */
  $handler->display->display_options['fields']['field_forum_member_count']['id'] = 'field_forum_member_count';
  $handler->display->display_options['fields']['field_forum_member_count']['table'] = 'field_data_field_forum_member_count';
  $handler->display->display_options['fields']['field_forum_member_count']['field'] = 'field_forum_member_count';
  $handler->display->display_options['fields']['field_forum_member_count']['label'] = '';
  $handler->display->display_options['fields']['field_forum_member_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_member_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Contextual filter: Field: Grade(s) (field_grades) */
  $handler->display->display_options['arguments']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['arguments']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['arguments']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['arguments']['field_grades_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_grades_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_grades_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_grades_tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field: Intended End User(s) (field_intended_end_user) */
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_intended_end_user_tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field: Intended Student Population(s) (field_intended_student) */
  $handler->display->display_options['arguments']['field_intended_student_tid']['id'] = 'field_intended_student_tid';
  $handler->display->display_options['arguments']['field_intended_student_tid']['table'] = 'field_data_field_intended_student';
  $handler->display->display_options['arguments']['field_intended_student_tid']['field'] = 'field_intended_student_tid';
  $handler->display->display_options['arguments']['field_intended_student_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_intended_student_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_intended_student_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_intended_student_tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['arguments']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['arguments']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['arguments']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['arguments']['field_subject_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_subject_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_subject_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_subject_tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'forum' => 'forum',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['forum_list'] = $view;

  return $export;
}
