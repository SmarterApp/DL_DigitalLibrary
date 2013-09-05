<?php
/**
 * @file
 * sbac_paradata.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function sbac_paradata_field_group_info() {
  $export = array();

//  $field_group = new stdClass();
//  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
//  $field_group->api_version = 1;
//  $field_group->identifier = 'group_paradata|node|resource|form';
//  $field_group->group_name = 'group_paradata';
//  $field_group->entity_type = 'node';
//  $field_group->bundle = 'resource';
//  $field_group->mode = 'form';
//  $field_group->parent_name = '';
//  $field_group->data = array(
//    'label' => 'Paradata',
//    'weight' => '40',
//    'children' => array(
//      0 => 'field_unique_views',
//      1 => 'field_total_views',
//      2 => 'field_asset_downloads',
//    ),
//    'format_type' => 'tab',
//    'format_settings' => array(
//      'formatter' => 'closed',
//      'instance_settings' => array(
//        'description' => '',
//        'classes' => '',
//        'required_fields' => 1,
//      ),
//    ),
//  );
//  $export['group_paradata|node|resource|form'] = $field_group;

  return $export;
}
