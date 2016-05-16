<?php
/**
 * @file
 * sbac_digital_library_resources.current_search.inc
 */

/**
 * Implements hook_current_search_default_items().
 */
function sbac_digital_library_resources_current_search_default_items() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'resource_results';
  $item->label = 'Resource Results';
  $item->settings = array(
    'items' => array(
      'results' => array(
        'id' => 'text',
        'label' => 'Results',
        'text' => '[facetapi_results:result-count] Resource:',
        'plural' => 1,
        'text_plural' => '[facetapi_results:result-count] Resources:',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 0,
        'element' => '0',
        'css' => 0,
        'classes' => '',
        'weight' => '0',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '1',
    ),
  );
  $export['resource_results'] = $item;

  return $export;
}
