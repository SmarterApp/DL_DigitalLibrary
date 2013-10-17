<?php
/**
 * @file
 * sbac_resource.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sbac_resource_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_advanced|node|resource|form';
  $field_group->group_name = 'group_advanced';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced',
    'weight' => '4',
    'children' => array(
      0 => 'field_view_permissions_per_state',
      1 => 'field_subscription_package_type',
      2 => 'field_view_permissions',
      3 => 'field_resource_actions',
      4 => 'field_posting_options',
      5 => 'field_posting_options_comment',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Advanced',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'sbac-resource-advanced',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_advanced|node|resource|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic|node|resource|form';
  $field_group->group_name = 'group_basic';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General',
    'weight' => '0',
    'children' => array(
      0 => 'field_document_id',
      1 => 'field_attributes',
      2 => 'field_focus',
      3 => 'field_student_agency',
      4 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'General',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'sbac-resource-general',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_basic|node|resource|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_materials|node|resource|form';
  $field_group->group_name = 'group_materials';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Materials',
    'weight' => '1',
    'children' => array(
      0 => 'field_file',
      1 => 'field_author',
      2 => 'field_license_information',
      3 => 'field_publisher',
      4 => 'field_license',
      5 => 'field_pii',
      6 => 'field_video',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Materials',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'sbac-resource-materials',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_materials|node|resource|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_summary|node|resource|form';
  $field_group->group_name = 'group_summary';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Summary',
    'weight' => '2',
    'children' => array(
      0 => 'field_alt_body',
      1 => 'field_connection_to_ccss',
      2 => 'field_connection_to_fap',
      3 => 'field_contexts',
      4 => 'field_learning_goals',
      5 => 'field_principles',
      6 => 'field_success_criteria',
      7 => 'field_supporting_evidence',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Summary',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-summary field-group-tab sbac-resource-summary',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_summary|node|resource|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tags|node|resource|form';
  $field_group->group_name = 'group_tags';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tags',
    'weight' => '3',
    'children' => array(
      0 => 'field_alignment_tags',
      1 => 'field_digital_media_type',
      2 => 'field_educational_use',
      3 => 'field_intended_end_user',
      4 => 'field_smarter_balanced_keyword',
      5 => 'field_subject',
      6 => 'field_geographical_settings',
      7 => 'field_grades',
      8 => 'field_intended_student',
      9 => 'field_classroom_technologies',
      10 => 'field_alignment_term',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Tags',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'sbac-resource-tags',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_tags|node|resource|form'] = $field_group;

  return $export;
}
