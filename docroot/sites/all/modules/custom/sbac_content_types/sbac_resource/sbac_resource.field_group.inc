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
    'weight' => '5',
    'children' => array(
      0 => 'field_view_permissions_per_state',
      1 => 'field_posting_options',
      2 => 'field_posting_options_comment',
      3 => 'field_resource_actions',
      4 => 'field_subscription_package_type',
      5 => 'field_view_permissions',
      6 => 'field_permanent_link_settings',
      7 => 'field_temporary_public_link',
      8 => 'field_temporary_public_link_time',
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
    'weight' => '1',
    'children' => array(
      0 => 'field_document_id',
      1 => 'field_alt_body',
      2 => 'field_intended_end_user',
      3 => 'field_attributes',
      4 => 'field_connection_to_fap',
      5 => 'field_focus',
      6 => 'field_student_agency',
      7 => 'field_resource_thumbnail',
      8 => 'title',
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
  $field_group->identifier = 'group_flag|node|resource|form';
  $field_group->group_name = 'group_flag';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resource';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Flags',
    'weight' => '0',
    'children' => array(
      0 => 'field_temp',
      1 => 'field_asset_downloads',
      2 => 'field_total_views',
      3 => 'field_unique_views',
      4 => 'field_resource_state',
      5 => 'field_html5',
      6 => 'field_node_avg_rating',
      7 => 'field_recent_reviewers',
      8 => 'field_unique_downloads',
      9 => 'field_is_hidden',
      10 => 'field_recent_publishers',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Flag',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-flag field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_flag|node|resource|form'] = $field_group;

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
    'weight' => '2',
    'children' => array(
      0 => 'field_author',
      1 => 'field_license_information',
      2 => 'field_publisher',
      3 => 'field_license',
      4 => 'field_pii',
      5 => 'field_license_secondary',
      6 => 'field_copyright_clearace_forms',
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
    'label' => 'Details',
    'weight' => '3',
    'children' => array(
      0 => 'field_alignment_tags',
      1 => 'field_subject',
      2 => 'field_connection_to_ccss',
      3 => 'field_contexts',
      4 => 'field_grades',
      5 => 'field_learning_goals',
      6 => 'field_principles',
      7 => 'field_success_criteria',
      8 => 'field_supporting_evidence',
      9 => 'field_alignment_term',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Details',
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
    'weight' => '4',
    'children' => array(
      0 => 'field_digital_media_type',
      1 => 'field_educational_use',
      2 => 'field_smarter_balanced_keyword',
      3 => 'field_geographical_settings',
      4 => 'field_intended_student',
      5 => 'field_classroom_technologies',
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
