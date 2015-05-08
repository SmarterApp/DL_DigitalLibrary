<?php
/**
 * @file
 * sbac_media.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sbac_media_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'media-media-field_file_hash'
  $field_instances['media-media-field_file_hash'] = array(
    'bundle' => 'media',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'media',
    'field_name' => 'field_file_hash',
    'label' => 'File Hash',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => '',
        'maxlength_js_enforce' => 0,
        'maxlength_js_label' => '',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 4,
    ),
    'xss' => 0,
  );

  // Exported field_instance: 'media-media-field_file_id'
  $field_instances['media-media-field_file_id'] = array(
    'bundle' => 'media',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'media',
    'field_name' => 'field_file_id',
    'label' => 'File ID',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => 0,
        'maxlength_js_label' => '',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
    'xss' => 0,
  );

  // Exported field_instance: 'media-media-field_file_name'
  $field_instances['media-media-field_file_name'] = array(
    'bundle' => 'media',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'media',
    'field_name' => 'field_file_name',
    'label' => 'File Name',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => 0,
        'maxlength_js_label' => '',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
    'xss' => 0,
  );

  // Exported field_instance: 'media-media-field_file_size'
  $field_instances['media-media-field_file_size'] = array(
    'bundle' => 'media',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'media',
    'field_name' => 'field_file_size',
    'label' => 'File Size',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => 0,
        'maxlength_js_label' => '',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 3,
    ),
    'xss' => 0,
  );

  // Exported field_instance: 'media-media-field_nid'
  $field_instances['media-media-field_nid'] = array(
    'bundle' => 'media',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'media',
    'field_name' => 'field_nid',
    'label' => 'Node ID',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => 0,
        'maxlength_js_label' => '',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
    'xss' => 0,
  );

  // Exported field_instance: 'media-media-field_weight'
  $field_instances['media-media-field_weight'] = array(
    'bundle' => 'media',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'media',
    'field_name' => 'field_weight',
    'label' => 'File Weight',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js_label' => '',
      ),
      'type' => 'number',
      'weight' => 5,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('File Hash');
  t('File ID');
  t('File Name');
  t('File Size');
  t('File Weight');
  t('Node ID');

  return $field_instances;
}
