<?php
/**
 * @file
 * sbac_featured_content.features.inc
 */

/**
 * Implements hook_views_api().
 */
function sbac_featured_content_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function sbac_featured_content_flag_default_flags() {
  $flags = array();
  // Exported flag: "Featured".
  $flags['featured_node'] = array(
    'entity_type' => 'node',
    'title' => 'Featured',
    'global' => 0,
    'types' => array(
      0 => 'resource',
    ),
    'flag_short' => 'Feature this [node:content-type:name]',
    'flag_long' => '',
    'flag_message' => '[node:title] is now featured',
    'unflag_short' => 'Un-Feature this Resource',
    'unflag_long' => '',
    'unflag_message' => '[node:title] is no longer featured',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'diff_standard' => 0,
      'print' => 0,
      'token' => 0,
      'secondary_teaser' => 0,
      'revision' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 1,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'sbac_featured_content',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
