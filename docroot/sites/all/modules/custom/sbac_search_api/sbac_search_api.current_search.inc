<?php
/**
 * @file
 * sbac_search_api.current_search.inc
 */

/**
 * Implements hook_current_search_default_items().
 */
function sbac_search_api_current_search_default_items() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'main_search';
  $item->label = 'Main Search';
  $item->settings = array(
    'items' => array(
      'search_results' => array(
        'id' => 'text',
        'label' => 'Search Results',
        'text' => '[facetapi_results:result-count] Result for "[facetapi_results:keys]"',
        'plural' => 1,
        'text_plural' => '[facetapi_results:result-count] Results for "[facetapi_results:keys]"',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 0,
        'element' => '0',
        'css' => 0,
        'classes' => '',
        'weight' => '0',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '0',
    ),
  );
  $export['main_search'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'search_sections';
  $item->label = 'Search Sections';
  $item->settings = array(
    'items' => array(
      'results' => array(
        'id' => 'text',
        'label' => 'Results',
        'text' => '[facetapi_results:result-count] Result',
        'plural' => 1,
        'text_plural' => '[facetapi_results:result-count] Results',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 1,
        'element' => 'div',
        'css' => 1,
        'classes' => 'search-results',
        'weight' => '-50',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '1',
    ),
  );
  $export['search_sections'] = $item;

  return $export;
}
