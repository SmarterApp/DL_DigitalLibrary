<?php
/**
 * @file
 * sbac_forum.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sbac_forum_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_forum_access|taxonomy_term|forum|form';
  $field_group->group_name = 'group_forum_access';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Who Can Participate?',
    'weight' => '5',
    'children' => array(
      0 => 'field_forum_access_role_list',
      1 => 'field_forum_access_states',
      2 => 'field_forum_access_user_roles',
      3 => 'field_state',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Who Can Participate?',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => '',
        'description' => 'By default, a forum is visible to all Digital Library members and any member can participate.',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_forum_access|taxonomy_term|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_forum_hidden1|taxonomy_term|forum|form';
  $field_group->group_name = 'group_forum_hidden1';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Members',
    'weight' => '7',
    'children' => array(
      0 => 'field_fc_forum_members',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-forum-hidden1 field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_forum_hidden1|taxonomy_term|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_forum_hidden|taxonomy_term|forum|form';
  $field_group->group_name = 'group_forum_hidden';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Facilitators',
    'weight' => '6',
    'children' => array(
      0 => 'field_forum_facilitators',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Facilitators',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-forum-hidden field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_forum_hidden|taxonomy_term|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_forum_stats|taxonomy_term|forum|form';
  $field_group->group_name = 'group_forum_stats';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Administrative (hidden)',
    'weight' => '9',
    'children' => array(
      0 => 'field_forum_created',
      1 => 'field_forum_last_activity',
      2 => 'field_forum_member_count',
      3 => 'field_forum_removed_member_count',
      4 => 'field_forum_topic_comment_count',
      5 => 'field_forum_topic_count',
      6 => 'field_forum_resource_ref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-forum-stats field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_forum_stats|taxonomy_term|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_forum_tags|taxonomy_term|forum|form';
  $field_group->group_name = 'group_forum_tags';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Add Tags',
    'weight' => '3',
    'children' => array(
      0 => 'field_grades',
      1 => 'field_intended_end_user',
      2 => 'field_intended_student',
      3 => 'field_subject',
      4 => 'field_attributes',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Add Tags',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-forum-tags field-group-div',
        'description' => 'Add tags that best describe the purpose of your forum and make it easily discoverable',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_forum_tags|taxonomy_term|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_collection|comment|comment_node_topic|form';
  $field_group->group_name = 'group_topic_collection';
  $field_group->entity_type = 'comment';
  $field_group->bundle = 'comment_node_topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach Collection',
    'weight' => '3',
    'children' => array(
      0 => 'field_topic_comment_collection',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attach Collection',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-topic-collection field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_topic_collection|comment|comment_node_topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_comments_links|comment|comment_node_topic|form';
  $field_group->group_name = 'group_topic_comments_links';
  $field_group->entity_type = 'comment';
  $field_group->bundle = 'comment_node_topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach link(s)',
    'weight' => '2',
    'children' => array(
      0 => 'field_topic_comment_links',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attach link(s)',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-topic-comments-links field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_topic_comments_links|comment|comment_node_topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_comments_materials|comment|comment_node_topic|form';
  $field_group->group_name = 'group_topic_comments_materials';
  $field_group->entity_type = 'comment';
  $field_group->bundle = 'comment_node_topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach file(s)',
    'weight' => '1',
    'children' => array(
      0 => 'field_topic_comment_files',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attach file(s)',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-topic-comments-materials field-group-fieldset',
        'description' => 'Please be sure attachments meet all policies related to copyright and Personally Identifiable Information (PII). <a href="/help-topics"> Click for more information.</a>',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_topic_comments_materials|comment|comment_node_topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_links|node|topic|form';
  $field_group->group_name = 'group_topic_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach link(s)',
    'weight' => '3',
    'children' => array(
      0 => 'field_topic_links',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attach link(s)',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-topic-links field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_topic_links|node|topic|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_topic_materials|node|topic|form';
  $field_group->group_name = 'group_topic_materials';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'topic';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach file(s)',
    'weight' => '2',
    'children' => array(
      0 => 'field_topic_files',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Attach file(s)',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'Please be sure attachments meet all policies related to copyright and Personally Identifiable Information (PII). <a href="/help-topics"> Click for more information.</a>',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_topic_materials|node|topic|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add Tags');
  t('Administrative (hidden)');
  t('Attach Collection');
  t('Attach file(s)');
  t('Attach link(s)');
  t('Facilitators');
  t('Members');
  t('Who Can Participate?');

  return $field_groups;
}
