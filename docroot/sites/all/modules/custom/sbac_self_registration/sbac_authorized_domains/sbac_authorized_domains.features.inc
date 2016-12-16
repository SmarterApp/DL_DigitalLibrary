<?php
/**
 * @file
 * sbac_authorized_domains.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_authorized_domains_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_authorized_domains_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function sbac_authorized_domains_eck_bundle_info() {
  $items = array(
  'authorized_domains_authorized_domains' => array(
  'machine_name' => 'authorized_domains_authorized_domains',
  'entity_type' => 'authorized_domains',
  'name' => 'authorized_domains',
  'label' => 'Authorized domains',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function sbac_authorized_domains_eck_entity_type_info() {
$items = array(
       'authorized_domains' => array(
  'name' => 'authorized_domains',
  'label' => 'Authorized domains',
  'properties' => array(
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'changed' => array(
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
  ),
),
  );
  return $items;
}
