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
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Show More Forums';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'forum_page_card';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Taxonomy term: Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['id'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['table'] = 'field_data_field_fc_forum_members';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['field'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['delta'] = '-1';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Forum resource ref */
  $handler->display->display_options['fields']['field_forum_resource_ref']['id'] = 'field_forum_resource_ref';
  $handler->display->display_options['fields']['field_forum_resource_ref']['table'] = 'field_data_field_forum_resource_ref';
  $handler->display->display_options['fields']['field_forum_resource_ref']['field'] = 'field_forum_resource_ref';
  $handler->display->display_options['fields']['field_forum_resource_ref']['label'] = '';
  $handler->display->display_options['fields']['field_forum_resource_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_forum_resource_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_resource_ref']['settings'] = array(
    'link' => 0,
  );
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
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Replace Text';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['fields']['field_forum_last_activity']['empty'] = 'None';
  $handler->display->display_options['fields']['field_forum_last_activity']['settings'] = array(
    'format_type' => 'forum_listing',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Topic Count */
  $handler->display->display_options['fields']['field_forum_topic_count']['id'] = 'field_forum_topic_count';
  $handler->display->display_options['fields']['field_forum_topic_count']['table'] = 'field_data_field_forum_topic_count';
  $handler->display->display_options['fields']['field_forum_topic_count']['field'] = 'field_forum_topic_count';
  $handler->display->display_options['fields']['field_forum_topic_count']['label'] = '';
  $handler->display->display_options['fields']['field_forum_topic_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_forum_topic_count']['alter']['text'] = '[field_forum_topic_count]<div class="forum-listing-suffix-label">Discussions</div>';
  $handler->display->display_options['fields']['field_forum_topic_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_count']['empty'] = '0<div class="forum-listing-suffix-label">Discussions</div>';
  $handler->display->display_options['fields']['field_forum_topic_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Reply (comment) Count */
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['id'] = 'field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['field'] = 'field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['label'] = '';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['alter']['text'] = '[field_forum_topic_comment_count]<div class="forum-listing-suffix-label">Posts</div>';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['empty'] = '0<div class="forum-listing-suffix-label">Replies</div>';
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
  $handler->display->display_options['fields']['field_forum_member_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_forum_member_count']['alter']['text'] = '[field_forum_member_count]<div class="forum-listing-suffix-label">Participants</div>';
  $handler->display->display_options['fields']['field_forum_member_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_member_count']['empty'] = '0<div class="forum-listing-suffix-label">Participants</div>';
  $handler->display->display_options['fields']['field_forum_member_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Taxonomy term: Reply (comment) Count (field_forum_topic_comment_count) */
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['id'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['field'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Created (field_forum_created) */
  $handler->display->display_options['sorts']['field_forum_created_value']['id'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['table'] = 'field_data_field_forum_created';
  $handler->display->display_options['sorts']['field_forum_created_value']['field'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Member Count (field_forum_member_count) */
  $handler->display->display_options['sorts']['field_forum_member_count_value']['id'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['table'] = 'field_data_field_forum_member_count';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['field'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['order'] = 'DESC';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['machine_name']['group'] = 1;
  /* Filter criterion: Field: Grade(s) (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['value'] = '';
  $handler->display->display_options['filters']['field_grades_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grade(s) (field_grades)';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
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
    27 => 0,
  );
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Intended End User(s) (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['value'] = '';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['label'] = 'Intended Forum Participants (field_intended_end_user)';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['identifier'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['remember_roles'] = array(
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
    27 => 0,
  );
  $handler->display->display_options['filters']['field_intended_end_user_tid']['vocabulary'] = 'intended_end_user';
  /* Filter criterion: Field: Intended Student Population(s) (field_intended_student) */
  $handler->display->display_options['filters']['field_intended_student_tid']['id'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['table'] = 'field_data_field_intended_student';
  $handler->display->display_options['filters']['field_intended_student_tid']['field'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['value'] = '';
  $handler->display->display_options['filters']['field_intended_student_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator_id'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['label'] = 'Intended Student Population(s) (field_intended_student)';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['identifier'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['vocabulary'] = 'intended_student_populations';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['value'] = '';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';

  /* Display: All Forums */
  $handler = $view->new_display('block', 'All Forums', 'block');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['block_caching'] = '-1';

  /* Display: My Forums */
  $handler = $view->new_display('block', 'My Forums', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<div class="my-forum-empty-text"><h2>You Are Not A Member Of Any Forums Yet</h2>
<a href="forums-main-page/reset/my-forums/default">Find a forum </a>to participate in our vibrant community.</div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Taxonomy term: Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['id'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['table'] = 'field_data_field_fc_forum_members';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['field'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Last Activity (field_forum_last_activity) */
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['id'] = 'field_forum_last_activity_value';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['table'] = 'field_data_field_forum_last_activity';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['field'] = 'field_forum_last_activity_value';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Reply (comment) Count (field_forum_topic_comment_count) */
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['id'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['field'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Created (field_forum_created) */
  $handler->display->display_options['sorts']['field_forum_created_value']['id'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['table'] = 'field_data_field_forum_created';
  $handler->display->display_options['sorts']['field_forum_created_value']['field'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Member Count (field_forum_member_count) */
  $handler->display->display_options['sorts']['field_forum_member_count_value']['id'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['table'] = 'field_data_field_forum_member_count';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['field'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field collection item: Member (field_fc_forum_member) */
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['id'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['table'] = 'field_data_field_fc_forum_member';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['field'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['relationship'] = 'field_fc_forum_members_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field collection item: Removed (field_fc_forum_member_is_removed) */
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['id'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['table'] = 'field_data_field_fc_forum_member_is_removed';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['field'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['relationship'] = 'field_fc_forum_members_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['default_argument_options']['argument'] = '0';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['summary_options']['items_per_page'] = '25';

  /* Display: Resource Forums */
  $handler = $view->new_display('block', 'Resource Forums', 'block_2');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<div class="my-forum-empty-text"><h2>You Are Not A Member Of Any Forums Yet</h2>
<a href="forums-main-page/reset/my-forums/default">Find a forum </a>to participate in our vibrant community.</div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Taxonomy term: Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['id'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['table'] = 'field_data_field_fc_forum_members';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['field'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Last Activity (field_forum_last_activity) */
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['id'] = 'field_forum_last_activity_value';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['table'] = 'field_data_field_forum_last_activity';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['field'] = 'field_forum_last_activity_value';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Reply (comment) Count (field_forum_topic_comment_count) */
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['id'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['field'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Created (field_forum_created) */
  $handler->display->display_options['sorts']['field_forum_created_value']['id'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['table'] = 'field_data_field_forum_created';
  $handler->display->display_options['sorts']['field_forum_created_value']['field'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Member Count (field_forum_member_count) */
  $handler->display->display_options['sorts']['field_forum_member_count_value']['id'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['table'] = 'field_data_field_forum_member_count';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['field'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['machine_name']['group'] = 1;
  /* Filter criterion: Field: Grade(s) (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_grades_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grades (field_grades)';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_grades_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Intended End User(s) (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['label'] = 'Intended Participants (field_intended_end_user)';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['identifier'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_intended_end_user_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['vocabulary'] = 'intended_end_user';
  /* Filter criterion: Field: Intended Student Population(s) (field_intended_student) */
  $handler->display->display_options['filters']['field_intended_student_tid']['id'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['table'] = 'field_data_field_intended_student';
  $handler->display->display_options['filters']['field_intended_student_tid']['field'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_student_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator_id'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['label'] = 'Student Populations (field_intended_student)';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['identifier'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_intended_student_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_student_tid']['vocabulary'] = 'intended_student_populations';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['label'] = 'Subjects and Domains (field_subject)';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['identifier'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_subject_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';
  /* Filter criterion: Taxonomy term: Forum resource ref (field_forum_resource_ref) */
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['id'] = 'field_forum_resource_ref_target_id';
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['table'] = 'field_data_field_forum_resource_ref';
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['field'] = 'field_forum_resource_ref_target_id';
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['operator'] = 'not empty';
  /* Filter criterion: Field: Attributes (field_attributes) */
  $handler->display->display_options['filters']['field_attributes_tid']['id'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['table'] = 'field_data_field_attributes';
  $handler->display->display_options['filters']['field_attributes_tid']['field'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['operator_id'] = 'field_attributes_tid_op';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['label'] = 'Attributes of the Formative Assessment Process (field_attributes)';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['operator'] = 'field_attributes_tid_op';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['identifier'] = 'field_attributes_tid';
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_attributes_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_attributes_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_attributes_tid']['vocabulary'] = 'attributes';
  /* Filter criterion: Field: Geographical Setting(s) (field_geographical_settings) */
  $handler->display->display_options['filters']['field_geographical_settings_tid']['id'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['table'] = 'field_data_field_geographical_settings';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['field'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['operator_id'] = 'field_geographical_settings_tid_op';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['label'] = 'Geographic Settings (field_geographical_settings)';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['operator'] = 'field_geographical_settings_tid_op';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['identifier'] = 'field_geographical_settings_tid';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_geographical_settings_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_geographical_settings_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_geographical_settings_tid']['vocabulary'] = 'geographical_settings';
  /* Filter criterion: Field: Digital Media Type(s) (field_digital_media_type) */
  $handler->display->display_options['filters']['field_digital_media_type_tid']['id'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['table'] = 'field_data_field_digital_media_type';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['field'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['operator_id'] = 'field_digital_media_type_tid_op';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['label'] = 'Media Types (field_digital_media_type)';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['operator'] = 'field_digital_media_type_tid_op';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['identifier'] = 'field_digital_media_type_tid';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_digital_media_type_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_digital_media_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_digital_media_type_tid']['vocabulary'] = 'digital_media_type';
  /* Filter criterion: Field: Resource Type (field_focus) */
  $handler->display->display_options['filters']['field_focus_tid']['id'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['table'] = 'field_data_field_focus';
  $handler->display->display_options['filters']['field_focus_tid']['field'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator_id'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['label'] = 'Resource Type (field_focus)';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['operator'] = 'field_focus_tid_op';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['identifier'] = 'field_focus_tid';
  $handler->display->display_options['filters']['field_focus_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_focus_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_focus_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_focus_tid']['vocabulary'] = 'focus';
  /* Filter criterion: Field: Educational Use (field_educational_use) */
  $handler->display->display_options['filters']['field_educational_use_tid']['id'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['table'] = 'field_data_field_educational_use';
  $handler->display->display_options['filters']['field_educational_use_tid']['field'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['operator_id'] = 'field_educational_use_tid_op';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['label'] = 'Educational Use (field_educational_use)';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['operator'] = 'field_educational_use_tid_op';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['identifier'] = 'field_educational_use_tid';
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_educational_use_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_educational_use_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_educational_use_tid']['vocabulary'] = 'educational_use';
  /* Filter criterion: Field: Module Type (field_smarter_balanced_keyword) */
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['id'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['table'] = 'field_data_field_smarter_balanced_keyword';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['field'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['operator_id'] = 'field_smarter_balanced_keyword_tid_op';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['label'] = 'Smarter Balanced Keyword(s) (field_smarter_balanced_keyword)';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['operator'] = 'field_smarter_balanced_keyword_tid_op';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['identifier'] = 'field_smarter_balanced_keyword_tid';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_smarter_balanced_keyword_tid']['vocabulary'] = 'smarter_balanced_keyword';
  $handler->display->display_options['block_caching'] = '-1';

  /* Display: Topic Forums */
  $handler = $view->new_display('block', 'Topic Forums', 'block_3');
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Reply (comment) Count (field_forum_topic_comment_count) */
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['id'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['field'] = 'field_forum_topic_comment_count_value';
  $handler->display->display_options['sorts']['field_forum_topic_comment_count_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Created (field_forum_created) */
  $handler->display->display_options['sorts']['field_forum_created_value']['id'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['table'] = 'field_data_field_forum_created';
  $handler->display->display_options['sorts']['field_forum_created_value']['field'] = 'field_forum_created_value';
  $handler->display->display_options['sorts']['field_forum_created_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Member Count (field_forum_member_count) */
  $handler->display->display_options['sorts']['field_forum_member_count_value']['id'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['table'] = 'field_data_field_forum_member_count';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['field'] = 'field_forum_member_count_value';
  $handler->display->display_options['sorts']['field_forum_member_count_value']['order'] = 'DESC';
  /* Sort criterion: Taxonomy term: Last Activity (field_forum_last_activity) */
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['id'] = 'field_forum_last_activity_value';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['table'] = 'field_data_field_forum_last_activity';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['field'] = 'field_forum_last_activity_value';
  $handler->display->display_options['sorts']['field_forum_last_activity_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['machine_name']['group'] = 1;
  /* Filter criterion: Field: Grade(s) (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_grades_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grades (field_grades)';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_grades_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_grades_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Intended End User(s) (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['label'] = 'Intended Participants (field_intended_end_user)';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['identifier'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_intended_end_user_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['vocabulary'] = 'intended_end_user';
  /* Filter criterion: Field: Intended Student Population(s) (field_intended_student) */
  $handler->display->display_options['filters']['field_intended_student_tid']['id'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['table'] = 'field_data_field_intended_student';
  $handler->display->display_options['filters']['field_intended_student_tid']['field'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_student_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator_id'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['label'] = 'Student Populations (field_intended_student)';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['operator'] = 'field_intended_student_tid_op';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['identifier'] = 'field_intended_student_tid';
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_intended_student_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_intended_student_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_intended_student_tid']['vocabulary'] = 'intended_student_populations';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator_id'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['label'] = 'Subjects and Domains (field_subject)';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['operator'] = 'field_subject_tid_op';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['identifier'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['expose']['remember_roles'] = array(
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
  );
  $handler->display->display_options['filters']['field_subject_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_subject_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';
  /* Filter criterion: Taxonomy term: Forum resource ref (field_forum_resource_ref) */
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['id'] = 'field_forum_resource_ref_target_id';
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['table'] = 'field_data_field_forum_resource_ref';
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['field'] = 'field_forum_resource_ref_target_id';
  $handler->display->display_options['filters']['field_forum_resource_ref_target_id']['operator'] = 'empty';
  $handler->display->display_options['block_caching'] = '-1';
  $export['forum_list'] = $view;

  $view = new view();
  $view->name = 'forum_list_empty';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Forum List - Empty';
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
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Show More Forums';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Taxonomy term: Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['id'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['table'] = 'field_data_field_fc_forum_members';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['field'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['delta'] = '-1';
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
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Replace Text';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['fields']['field_forum_last_activity']['empty'] = 'None';
  $handler->display->display_options['fields']['field_forum_last_activity']['settings'] = array(
    'format_type' => 'forum_listing',
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
  $handler->display->display_options['fields']['field_forum_topic_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_forum_topic_count']['alter']['text'] = '[field_forum_topic_count]<div class="forum-listing-suffix-label">Discussions</div>';
  $handler->display->display_options['fields']['field_forum_topic_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_count']['empty'] = '0<div class="forum-listing-suffix-label">Discussions</div>';
  $handler->display->display_options['fields']['field_forum_topic_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Field: Taxonomy term: Reply (comment) Count */
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['id'] = 'field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['table'] = 'field_data_field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['field'] = 'field_forum_topic_comment_count';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['label'] = '';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['alter']['text'] = '[field_forum_topic_comment_count]<div class="forum-listing-suffix-label">Replies</div>';
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_comment_count']['empty'] = '0<div class="forum-listing-suffix-label">Replies</div>';
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
  $handler->display->display_options['fields']['field_forum_member_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_forum_member_count']['alter']['text'] = '[field_forum_member_count]<div class="forum-listing-suffix-label">Participants</div>';
  $handler->display->display_options['fields']['field_forum_member_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_member_count']['empty'] = '0<div class="forum-listing-suffix-label">Participants</div>';
  $handler->display->display_options['fields']['field_forum_member_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['machine_name']['group'] = 1;
  /* Filter criterion: Field: Grade(s) (field_grades) */
  $handler->display->display_options['filters']['field_grades_tid']['id'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['table'] = 'field_data_field_grades';
  $handler->display->display_options['filters']['field_grades_tid']['field'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['value'] = '';
  $handler->display->display_options['filters']['field_grades_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator_id'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['label'] = 'Grade(s) (field_grades)';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['operator'] = 'field_grades_tid_op';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['identifier'] = 'field_grades_tid';
  $handler->display->display_options['filters']['field_grades_tid']['expose']['remember_roles'] = array(
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
    27 => 0,
  );
  $handler->display->display_options['filters']['field_grades_tid']['vocabulary'] = 'grades';
  /* Filter criterion: Field: Subjects and Domains (field_subject) */
  $handler->display->display_options['filters']['field_subject_tid']['id'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['table'] = 'field_data_field_subject';
  $handler->display->display_options['filters']['field_subject_tid']['field'] = 'field_subject_tid';
  $handler->display->display_options['filters']['field_subject_tid']['value'] = '';
  $handler->display->display_options['filters']['field_subject_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_subject_tid']['vocabulary'] = 'subject';

  /* Display: All Forums */
  $handler = $view->new_display('block', 'All Forums', 'block');

  /* Display: My Forums */
  $handler = $view->new_display('block', 'My Forums', 'block_1');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Taxonomy term: Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['id'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['table'] = 'field_data_field_fc_forum_members';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['field'] = 'field_fc_forum_members_value';
  $handler->display->display_options['relationships']['field_fc_forum_members_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field collection item: Member (field_fc_forum_member) */
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['id'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['table'] = 'field_data_field_fc_forum_member';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['field'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['relationship'] = 'field_fc_forum_members_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_fc_forum_member_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field collection item: Removed (field_fc_forum_member_is_removed) */
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['id'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['table'] = 'field_data_field_fc_forum_member_is_removed';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['field'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['relationship'] = 'field_fc_forum_members_value';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['default_argument_options']['argument'] = '0';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_fc_forum_member_is_removed_value']['summary_options']['items_per_page'] = '25';
  $export['forum_list_empty'] = $view;

  $view = new view();
  $view->name = 'forum_member_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'Forum - Member List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Forum - Member List';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '2';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Show More Members';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<div class="forum-members-empty-message">There are no participants yet</div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Field collection item: Entity with the Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_taxonomy_term']['id'] = 'field_fc_forum_members_taxonomy_term';
  $handler->display->display_options['relationships']['field_fc_forum_members_taxonomy_term']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_fc_forum_members_taxonomy_term']['field'] = 'field_fc_forum_members_taxonomy_term';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_fc_forum_member_target_id']['id'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['relationships']['field_fc_forum_member_target_id']['table'] = 'field_data_field_fc_forum_member';
  $handler->display->display_options['relationships']['field_fc_forum_member_target_id']['field'] = 'field_fc_forum_member_target_id';
  /* Relationship: User: Title (field_position) */
  $handler->display->display_options['relationships']['field_position_tid']['id'] = 'field_position_tid';
  $handler->display->display_options['relationships']['field_position_tid']['table'] = 'field_data_field_position';
  $handler->display->display_options['relationships']['field_position_tid']['field'] = 'field_position_tid';
  $handler->display->display_options['relationships']['field_position_tid']['relationship'] = 'field_fc_forum_member_target_id';
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  /* Field: User: Privacy */
  $handler->display->display_options['fields']['field_privacy']['id'] = 'field_privacy';
  $handler->display->display_options['fields']['field_privacy']['table'] = 'field_data_field_privacy';
  $handler->display->display_options['fields']['field_privacy']['field'] = 'field_privacy';
  $handler->display->display_options['fields']['field_privacy']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['field_privacy']['label'] = '';
  $handler->display->display_options['fields']['field_privacy']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_privacy']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_privacy']['delta_offset'] = '0';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['link_photo_to_profile'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'forum_profile_image_60x60';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_type'] = 'div';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Field: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['field_state']['label'] = '';
  $handler->display->display_options['fields']['field_state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_state']['delta_offset'] = '0';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_position_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Recommendation Count */
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['id'] = 'field_fc_forum_member_reco_count';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['table'] = 'field_data_field_fc_forum_member_reco_count';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['field'] = 'field_fc_forum_member_reco_count';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['label'] = '';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['alter']['text'] = '[field_fc_forum_member_reco_count] <div class="forum-member-recommendation-count">Recommendations</div>';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['empty'] = '0<div class="forum-member-recommendation-count">Recommendations</div>';
  $handler->display->display_options['fields']['field_fc_forum_member_reco_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 0,
  );
  /* Field: Field collection item: Topics Count */
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['id'] = 'field_fc_forum_member_tpic_count';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['table'] = 'field_data_field_fc_forum_member_tpic_count';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['field'] = 'field_fc_forum_member_tpic_count';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['label'] = '';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['alter']['text'] = '[field_fc_forum_member_tpic_count] <div class="forum-member-topic-count">Discussions</div>';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['empty'] = '0<div class="forum-member-topic-count">Discussions</div>';
  $handler->display->display_options['fields']['field_fc_forum_member_tpic_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 0,
  );
  /* Field: Field collection item: Post Count */
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['id'] = 'field_fc_forum_member_post_count';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['table'] = 'field_data_field_fc_forum_member_post_count';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['field'] = 'field_fc_forum_member_post_count';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['label'] = '';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['alter']['text'] = '[field_fc_forum_member_post_count] <div class="forum-member-post-count">Posts</div>';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['empty'] = '0<div class="forum-member-post-count">Posts</div>';
  $handler->display->display_options['fields']['field_fc_forum_member_post_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 0,
  );
  /* Sort criterion: Field collection item: Participation score (field_fc_forum_member_partip_scr) */
  $handler->display->display_options['sorts']['field_fc_forum_member_partip_scr_value']['id'] = 'field_fc_forum_member_partip_scr_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_partip_scr_value']['table'] = 'field_data_field_fc_forum_member_partip_scr';
  $handler->display->display_options['sorts']['field_fc_forum_member_partip_scr_value']['field'] = 'field_fc_forum_member_partip_scr_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_partip_scr_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_fc_forum_member_partip_scr_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_fc_forum_member_partip_scr_value']['expose']['label'] = 'Participation';
  /* Sort criterion: Field collection item: Recommendation Count (field_fc_forum_member_reco_count) */
  $handler->display->display_options['sorts']['field_fc_forum_member_reco_count_value']['id'] = 'field_fc_forum_member_reco_count_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_reco_count_value']['table'] = 'field_data_field_fc_forum_member_reco_count';
  $handler->display->display_options['sorts']['field_fc_forum_member_reco_count_value']['field'] = 'field_fc_forum_member_reco_count_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_reco_count_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_fc_forum_member_reco_count_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_fc_forum_member_reco_count_value']['expose']['label'] = 'Most Recommended';
  /* Sort criterion: Field collection item: Recent activity (field_fc_forum_member_rcnt_actvt) */
  $handler->display->display_options['sorts']['field_fc_forum_member_rcnt_actvt_value']['id'] = 'field_fc_forum_member_rcnt_actvt_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_rcnt_actvt_value']['table'] = 'field_data_field_fc_forum_member_rcnt_actvt';
  $handler->display->display_options['sorts']['field_fc_forum_member_rcnt_actvt_value']['field'] = 'field_fc_forum_member_rcnt_actvt_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_rcnt_actvt_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_fc_forum_member_rcnt_actvt_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_fc_forum_member_rcnt_actvt_value']['expose']['label'] = 'Most Recent Activity';
  /* Contextual filter: Taxonomy term: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['relationship'] = 'field_fc_forum_members_taxonomy_term';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: User: The user ID */
  $handler->display->display_options['filters']['uid_raw']['id'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['table'] = 'users';
  $handler->display->display_options['filters']['uid_raw']['field'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['filters']['uid_raw']['operator'] = 'not empty';

  /* Display: Members */
  $handler = $view->new_display('block', 'Members', 'block');

  /* Display: Removed Members */
  $handler = $view->new_display('block', 'Removed Members', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '24';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '4';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Show More Members';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<div class="forum-removed-members-empty-message">There are no removed participants for this forum</div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Field collection item: Removed (field_fc_forum_member_is_removed) */
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['id'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['table'] = 'field_data_field_fc_forum_member_is_removed';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['field'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['value'] = array(
    1 => '1',
  );
  $export['forum_member_list'] = $view;

  $view = new view();
  $view->name = 'forum_topic_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Forum - Topic List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Forum - Topic List';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '1';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Show More Topics';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<div class="sbac-forum-filter-no-topics-wrapper">There are no discussion topics yet</div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Author uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_type'] = 'div';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Content: Last comment uid */
  $handler->display->display_options['fields']['last_comment_uid']['id'] = 'last_comment_uid';
  $handler->display->display_options['fields']['last_comment_uid']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_uid']['field'] = 'last_comment_uid';
  $handler->display->display_options['fields']['last_comment_uid']['label'] = 'Latest Reply';
  $handler->display->display_options['fields']['last_comment_uid']['element_type'] = 'div';
  $handler->display->display_options['fields']['last_comment_uid']['separator'] = '';
  /* Field: Content: Last comment time */
  $handler->display->display_options['fields']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['label'] = '';
  $handler->display->display_options['fields']['last_comment_timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['last_comment_timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['last_comment_timestamp']['custom_date_format'] = 'M jS Y g:i a';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = '';
  $handler->display->display_options['fields']['comment_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['comment_count']['alter']['text'] = '[comment_count] <div class="topic-listing-suffix-label">Posts</div>';
  $handler->display->display_options['fields']['comment_count']['element_type'] = 'div';
  $handler->display->display_options['fields']['comment_count']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Last comment time */
  $handler->display->display_options['sorts']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['sorts']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['sorts']['last_comment_timestamp']['order'] = 'DESC';
  $handler->display->display_options['sorts']['last_comment_timestamp']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['last_comment_timestamp']['expose']['label'] = 'Most Recent Activity';
  /* Sort criterion: Content: Comment count */
  $handler->display->display_options['sorts']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['sorts']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['sorts']['comment_count']['order'] = 'DESC';
  $handler->display->display_options['sorts']['comment_count']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['comment_count']['expose']['label'] = 'Most Posts';
  /* Contextual filter: Content: Forum (field_topic_forum_parent) */
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['id'] = 'field_topic_forum_parent_tid';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['table'] = 'field_data_field_topic_forum_parent';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['field'] = 'field_topic_forum_parent_tid';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_topic_forum_parent_tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'topic' => 'topic',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  /* Display: Collaboration */
  $handler = $view->new_display('block', 'Collaboration', 'collaboration');
  $export['forum_topic_list'] = $view;

  $view = new view();
  $view->name = 'forums_keyword_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'apachesolr__acquia_search_server_1';
  $view->human_name = 'Forum - Keyword Search';
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
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'full_html';
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'More Matches';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '@total matches';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Empty';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['fields']['entity_type']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['bundle_name']['id'] = 'bundle_name';
  $handler->display->display_options['fields']['bundle_name']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['fields']['bundle_name']['field'] = 'bundle_name';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['fields']['entity_id']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['fields']['entity_id']['field'] = 'entity_id';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['content']['id'] = 'content';
  $handler->display->display_options['fields']['content']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['fields']['content']['field'] = 'content';
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['operator'] = 'word';
  $handler->display->display_options['filters']['entity_type']['value'] = 'node taxonomy_term comment';
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['bundle']['id'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['bundle']['field'] = 'bundle';
  $handler->display->display_options['filters']['bundle']['operator'] = 'word';
  $handler->display->display_options['filters']['bundle']['value'] = 'topic forum Topic comment';
  /* Filter criterion: Apache Solr: Search */
  $handler->display->display_options['filters']['keyword']['id'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['table'] = 'apachesolr__acquia_search_server_1';
  $handler->display->display_options['filters']['keyword']['field'] = 'keyword';
  $handler->display->display_options['filters']['keyword']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keyword']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['keyword']['expose']['operator'] = 'keyword_op';
  $handler->display->display_options['filters']['keyword']['expose']['identifier'] = 'keyword';
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
    27 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'forums-search';
  $export['forums_keyword_search'] = $view;

  return $export;
}
