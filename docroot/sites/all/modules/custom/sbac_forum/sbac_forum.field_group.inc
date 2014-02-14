<?php
/**
 * @file
 * sbac_forum.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sbac_forum_field_group_info() {
  $export = array();

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
    'label' => 'Who Can View and Join This Forum?',
    'weight' => '7',
    'children' => array(
      0 => 'field_state',
      1 => 'field_forum_access_states',
      2 => 'field_forum_access_user_roles',
      3 => 'field_forum_access_role_list',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Who Can View and Join This Forum?',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => '',
        'description' => 'By default, a forum is visible to all Digital Library members and any member can choose to join',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_forum_access|taxonomy_term|forum|form'] = $field_group;

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
    'weight' => '9',
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
  $export['group_forum_hidden1|taxonomy_term|forum|form'] = $field_group;

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
    'weight' => '8',
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
  $export['group_forum_hidden|taxonomy_term|forum|form'] = $field_group;

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
    'weight' => '16',
    'children' => array(
      0 => 'field_forum_topic_count',
      1 => 'field_forum_topic_comment_count',
      2 => 'field_forum_member_count',
      3 => 'field_forum_last_activity',
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
  $export['group_forum_stats|taxonomy_term|forum|form'] = $field_group;

  return $export;
}
