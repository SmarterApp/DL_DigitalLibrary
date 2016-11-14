<?php
/**
 * @file
 * sbac_districts_taxonomy.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sbac_districts_taxonomy_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-districts-field_district_id'.
  $field_instances['taxonomy_term-districts-field_district_id'] = array(
    'bundle' => 'districts',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The ID for the district in ART',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_district_id',
    'label' => 'District ID',
    'profanity' => 0,
    'required' => 1,
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
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 31,
    ),
    'xss' => 0,
  );

  // Exported field_instance: 'taxonomy_term-districts-field_domain_state'.
  $field_instances['taxonomy_term-districts-field_domain_state'] = array(
    'bundle' => 'districts',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_domain_state',
    'label' => 'State',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
        'label_help_description' => '',
      ),
      'type' => 'options_select',
      'weight' => 33,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('District ID');
  t('State');
  t('The ID for the district in ART');

  return $field_instances;
}
