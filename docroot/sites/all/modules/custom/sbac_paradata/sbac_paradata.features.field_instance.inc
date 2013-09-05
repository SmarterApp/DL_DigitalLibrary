<?php
/**
 * @file
 * sbac_paradata.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sbac_paradata_field_default_field_instances() {
  $field_instances = array();

//  // Exported field_instance: 'node-resource-field_asset_downloads'
//  $field_instances['node-resource-field_asset_downloads'] = array(
//    'bundle' => 'resource',
//    'default_value' => NULL,
//    'deleted' => 0,
//    'description' => '',
//    'display' => array(
//      'default' => array(
//        'label' => 'above',
//        'module' => 'number',
//        'settings' => array(
//          'decimal_separator' => '.',
//          'prefix_suffix' => TRUE,
//          'scale' => 0,
//          'thousand_separator' => ' ',
//        ),
//        'type' => 'number_integer',
//        'weight' => 40,
//      ),
//      'search_index' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//      'secondary_teaser' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//      'teaser' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//    ),
//    'ds_extras_field_template' => '',
//    'entity_type' => 'node',
//    'field_name' => 'field_asset_downloads',
//    'label' => 'Asset Downloads',
//    'required' => 0,
//    'settings' => array(
//      'max' => '',
//      'min' => '',
//      'prefix' => '',
//      'suffix' => '',
//      'user_register_form' => FALSE,
//    ),
//    'widget' => array(
//      'active' => 0,
//      'module' => 'number',
//      'settings' => array(
//        'label_help_description' => '',
//        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
//      ),
//      'type' => 'number',
//      'weight' => 11,
//    ),
//  );
//
//  // Exported field_instance: 'node-resource-field_total_views'
//  $field_instances['node-resource-field_total_views'] = array(
//    'bundle' => 'resource',
//    'default_value' => array(
//      0 => array(
//        'value' => 0,
//      ),
//    ),
//    'deleted' => 0,
//    'description' => '',
//    'display' => array(
//      'default' => array(
//        'label' => 'above',
//        'module' => 'number',
//        'settings' => array(
//          'decimal_separator' => '.',
//          'prefix_suffix' => TRUE,
//          'scale' => 0,
//          'thousand_separator' => ' ',
//        ),
//        'type' => 'number_integer',
//        'weight' => 39,
//      ),
//      'search_index' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//      'secondary_teaser' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//      'teaser' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//    ),
//    'ds_extras_field_template' => '',
//    'entity_type' => 'node',
//    'field_name' => 'field_total_views',
//    'label' => 'Total Views',
//    'required' => 0,
//    'settings' => array(
//      'max' => '',
//      'min' => '',
//      'prefix' => '',
//      'suffix' => '',
//      'user_register_form' => FALSE,
//    ),
//    'widget' => array(
//      'active' => 0,
//      'module' => 'number',
//      'settings' => array(
//        'label_help_description' => '',
//        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
//      ),
//      'type' => 'number',
//      'weight' => 13,
//    ),
//  );
//
//  // Exported field_instance: 'node-resource-field_unique_views'
//  $field_instances['node-resource-field_unique_views'] = array(
//    'bundle' => 'resource',
//    'default_value' => array(
//      0 => array(
//        'value' => 0,
//      ),
//    ),
//    'deleted' => 0,
//    'description' => '',
//    'display' => array(
//      'default' => array(
//        'label' => 'above',
//        'module' => 'number',
//        'settings' => array(
//          'decimal_separator' => '.',
//          'prefix_suffix' => TRUE,
//          'scale' => 0,
//          'thousand_separator' => ' ',
//        ),
//        'type' => 'number_integer',
//        'weight' => 38,
//      ),
//      'search_index' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//      'secondary_teaser' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//      'teaser' => array(
//        'label' => 'above',
//        'settings' => array(),
//        'type' => 'hidden',
//        'weight' => 0,
//      ),
//    ),
//    'ds_extras_field_template' => '',
//    'entity_type' => 'node',
//    'field_name' => 'field_unique_views',
//    'label' => 'Unique Views',
//    'required' => 0,
//    'settings' => array(
//      'max' => '',
//      'min' => '',
//      'prefix' => '',
//      'suffix' => '',
//      'user_register_form' => FALSE,
//    ),
//    'widget' => array(
//      'active' => 0,
//      'module' => 'number',
//      'settings' => array(
//        'label_help_description' => '',
//        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
//      ),
//      'type' => 'number',
//      'weight' => 12,
//    ),
//  );
//
//  // Translatables
//  // Included for use with string extractors like potx.
//  t('Asset Downloads');
//  t('Total Views');
//  t('Unique Views');

  return $field_instances;
}
