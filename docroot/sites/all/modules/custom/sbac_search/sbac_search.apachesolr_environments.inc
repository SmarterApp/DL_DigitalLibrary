<?php
/**
 * @file
 * sbac_search.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 */
function sbac_search_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'acquia_search_server_1';
  $environment->name = 'Acquia Search';
  $environment->url = 'http://useast1-c1.acquia-search.com/solr/KQRU-38122';
  $environment->service_class = 'AcquiaSearchService';
  $environment->conf = array();
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
    ),
    'file' => array(
      0 => 'file',
    ),
    'user' => array(
      0 => 'user',
    ),
  );
  $export['acquia_search_server_1'] = $environment;

  return $export;
}
