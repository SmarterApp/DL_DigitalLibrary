<?php
/**
 * @file
 * sbac_learning_registry.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_learning_registry_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_node_types';
  $strongarm->value = array(
    'resource' => 'resource',
    'alignment' => 0,
    'topic' => 0,
    'help_page' => 0,
  );
  $export['learning_registry_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_node_url';
  $strongarm->value = 'http://sandbox.learningregistry.org';
  $export['learning_registry_node_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_oauth_salt';
  $strongarm->value = 'KrP7FgnpjK4hXfVDIAwC';
  $export['learning_registry_oauth_salt'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_queuing';
  $strongarm->value = '0';
  $export['learning_registry_queuing'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_schema_type';
  $strongarm->value = array(
    'name' => 'LRMI',
    'resource_data_callback' => 'learning_resource_metadata_initiative_create_lrmi_payload',
    'payload_schema' => array(
      0 => 'schema.org',
      1 => 'LRMI',
      2 => 'application/microdata+json',
    ),
    'slice_callback' => 'learning_resource_metadata_initiative_slice',
  );
  $export['learning_registry_schema_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_schema_type_default_value';
  $strongarm->value = 'lrmi';
  $export['learning_registry_schema_type_default_value'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_signing_method';
  $strongarm->value = 'LR-PGP.1.0';
  $export['learning_registry_signing_method'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_submitter';
  $strongarm->value = 'Smarter Ballanced Beta';
  $export['learning_registry_submitter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_tos';
  $strongarm->value = 'http://creativecommons.org/choose/';
  $export['learning_registry_tos'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'learning_registry_url_type';
  $strongarm->value = '0';
  $export['learning_registry_url_type'] = $strongarm;

  return $export;
}
