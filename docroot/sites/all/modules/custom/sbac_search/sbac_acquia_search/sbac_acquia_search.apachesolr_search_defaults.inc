<?php
/**
 * @file
 * sbac_search.apachesolr_search_defaults.inc
 */

/**
 * Implements hook_apachesolr_search_default_searchers().
 */
function sbac_search_apachesolr_search_default_searchers() {
  $export = array();

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'core_search';
  $searcher->label = 'Digital Library Search';
  $searcher->description = 'Searches the digital library resources';
  $searcher->search_path = 'search/digital-library';
  $searcher->page_title = 'Digital Library Search';
  $searcher->env_id = 'acquia_search_server_1';
  $searcher->settings = array(
    'fq' => array(
      0 => 'entity_type:node',
      1 => 'bundle:resource',
    ),
    'apachesolr_search_custom_enable' => 1,
    'apachesolr_search_search_type' => 'custom',
    'apachesolr_search_per_page' => 10,
    'apachesolr_search_spellcheck' => 1,
    'apachesolr_search_search_box' => 1,
    'apachesolr_search_allow_user_input' => 0,
    'apachesolr_search_browse' => 'blocks',
  );
  $export['core_search'] = $searcher;

  return $export;
}
