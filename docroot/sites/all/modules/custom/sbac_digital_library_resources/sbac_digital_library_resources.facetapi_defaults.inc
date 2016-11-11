<?php
/**
 * @file
 * sbac_digital_library_resources.facetapi_defaults.inc
 */

/**
 * Implements hook_facetapi_default_facet_settings().
 */
function sbac_digital_library_resources_facetapi_default_facet_settings() {
  $export = array();

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_alignment_term';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_alignment_term';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '30',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '1',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_alignment_term'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_attributes';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_attributes';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_attributes'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_digital_media_type';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_digital_media_type';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_digital_media_type'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_educational_use';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_educational_use';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_educational_use'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_focus';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_focus';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_focus'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_grades';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_grades';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_grades'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_intended_end_user';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_intended_end_user';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_intended_end_user'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_intended_student';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_intended_student';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_intended_student'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_smarter_balanced_keywor';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_smarter_balanced_keywor';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_smarter_balanced_keywor'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@acquia_search_server_1::im_field_subject';
  $facet->searcher = 'apachesolr@acquia_search_server_1';
  $facet->realm = '';
  $facet->facet = 'im_field_subject';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '-1',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '0',
    'facet_missing' => 0,
    'flatten' => '0',
    'individual_parent' => '0',
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@acquia_search_server_1::im_field_subject'] = $facet;

  return $export;
}
