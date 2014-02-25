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
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Load More Forums';
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
  $handler->display->display_options['fields']['field_forum_topic_count']['alter']['text'] = '[field_forum_topic_count]<div class="forum-listing-suffix-label">Topics</div>';
  $handler->display->display_options['fields']['field_forum_topic_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_topic_count']['empty'] = '0<div class="forum-listing-suffix-label">Topics</div>';
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
  $handler->display->display_options['fields']['field_forum_member_count']['alter']['text'] = '[field_forum_member_count]<div class="forum-listing-suffix-label">Members</div>';
  $handler->display->display_options['fields']['field_forum_member_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_forum_member_count']['empty'] = '0<div class="forum-listing-suffix-label">Members</div>';
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
  /* Filter criterion: Field: Intended End User(s) (field_intended_end_user) */
  $handler->display->display_options['filters']['field_intended_end_user_tid']['id'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['table'] = 'field_data_field_intended_end_user';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['field'] = 'field_intended_end_user_tid';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['value'] = '';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['operator_id'] = 'field_intended_end_user_tid_op';
  $handler->display->display_options['filters']['field_intended_end_user_tid']['expose']['label'] = 'Intended End User(s) (field_intended_end_user)';
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

  /* Display: My Forums */
  $handler = $view->new_display('block', 'My Forums', 'block_1');
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
  $export['forum_list'] = $view;

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
  $handler->display->display_options['pager']['options']['items_per_page'] = '24';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '2';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Load More Members';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the Members (field_fc_forum_members) */
  $handler->display->display_options['relationships']['field_fc_forum_members_taxonomy_term']['id'] = 'field_fc_forum_members_taxonomy_term';
  $handler->display->display_options['relationships']['field_fc_forum_members_taxonomy_term']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_fc_forum_members_taxonomy_term']['field'] = 'field_fc_forum_members_taxonomy_term';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_fc_forum_member_target_id']['id'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['relationships']['field_fc_forum_member_target_id']['table'] = 'field_data_field_fc_forum_member';
  $handler->display->display_options['relationships']['field_fc_forum_member_target_id']['field'] = 'field_fc_forum_member_target_id';
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['link_photo_to_profile'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'small';
  /* Field: User: Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_first_name] [field_last_name]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Field: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['fields']['field_state']['label'] = '';
  $handler->display->display_options['fields']['field_state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_state']['delta_offset'] = '0';
  /* Field: Field collection item: Date Joined */
  $handler->display->display_options['fields']['field_fc_forum_member_joined']['id'] = 'field_fc_forum_member_joined';
  $handler->display->display_options['fields']['field_fc_forum_member_joined']['table'] = 'field_data_field_fc_forum_member_joined';
  $handler->display->display_options['fields']['field_fc_forum_member_joined']['field'] = 'field_fc_forum_member_joined';
  $handler->display->display_options['fields']['field_fc_forum_member_joined']['label'] = 'Joined';
  $handler->display->display_options['fields']['field_fc_forum_member_joined']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Sort criterion: Field collection item: Date Joined (field_fc_forum_member_joined) */
  $handler->display->display_options['sorts']['field_fc_forum_member_joined_value']['id'] = 'field_fc_forum_member_joined_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_joined_value']['table'] = 'field_data_field_fc_forum_member_joined';
  $handler->display->display_options['sorts']['field_fc_forum_member_joined_value']['field'] = 'field_fc_forum_member_joined_value';
  $handler->display->display_options['sorts']['field_fc_forum_member_joined_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_fc_forum_member_joined_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_fc_forum_member_joined_value']['expose']['label'] = 'Newest';
  /* Sort criterion: User: Name (field_first_name) */
  $handler->display->display_options['sorts']['field_first_name_value']['id'] = 'field_first_name_value';
  $handler->display->display_options['sorts']['field_first_name_value']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['sorts']['field_first_name_value']['field'] = 'field_first_name_value';
  $handler->display->display_options['sorts']['field_first_name_value']['relationship'] = 'field_fc_forum_member_target_id';
  $handler->display->display_options['sorts']['field_first_name_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_first_name_value']['expose']['label'] = 'Alphabetical';
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
  /* Filter criterion: Field collection item: Removed (field_fc_forum_member_is_removed) */
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['id'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['table'] = 'field_data_field_fc_forum_member_is_removed';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['field'] = 'field_fc_forum_member_is_removed_value';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_fc_forum_member_is_removed_value']['value'] = array(
    1 => '1',
  );

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
  $handler->display->display_options['pager']['options']['more_button_text'] = 'Load More Members';
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
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Started by';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_first_name] [field_last_name]';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = '';
  $handler->display->display_options['fields']['comment_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['comment_count']['suffix'] = ' Replies';
  /* Field: Content: Last comment author */
  $handler->display->display_options['fields']['last_comment_name']['id'] = 'last_comment_name';
  $handler->display->display_options['fields']['last_comment_name']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_name']['field'] = 'last_comment_name';
  $handler->display->display_options['fields']['last_comment_name']['label'] = 'Latest Reply';
  /* Field: Content: Last comment time */
  $handler->display->display_options['fields']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['label'] = '';
  $handler->display->display_options['fields']['last_comment_timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['last_comment_timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['last_comment_timestamp']['custom_date_format'] = 'M jS Y g:i a';
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
  $export['forum_topic_list'] = $view;

  return $export;
}
