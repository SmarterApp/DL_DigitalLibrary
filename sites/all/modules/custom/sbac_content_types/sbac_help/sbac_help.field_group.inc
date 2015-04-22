<?php
/**
 * @file
 * sbac_help.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sbac_help_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|help_page|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'help_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General',
    'weight' => '0',
    'children' => array(
      0 => 'field_help_icon',
      1 => 'field_summary',
      2 => 'body',
      3 => 'title',
      4 => 'path',
      5 => 'group_help_container',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_general|node|help_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_help_container|node|help_page|form';
  $field_group->group_name = 'group_help_container';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'help_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_general';
  $field_group->data = array(
    'label' => 'Help Container',
    'weight' => '7',
    'children' => array(
      0 => 'group_help_left',
      1 => 'group_help_right',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'element' => 'div',
        'classes' => '',
        'attributes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_help_container|node|help_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_help_left|node|help_page|form';
  $field_group->group_name = 'group_help_left';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'help_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_help_container';
  $field_group->data = array(
    'label' => 'Left Group',
    'weight' => '8',
    'children' => array(
      0 => 'field_help_page_topic',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'element' => 'div',
        'classes' => '',
        'attributes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_help_left|node|help_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_help_right|node|help_page|form';
  $field_group->group_name = 'group_help_right';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'help_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_help_container';
  $field_group->data = array(
    'label' => 'Right Group',
    'weight' => '9',
    'children' => array(
      0 => 'field_help_user_roles',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'element' => 'div',
        'classes' => '',
        'attributes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_help_right|node|help_page|form'] = $field_group;

  return $export;
}
