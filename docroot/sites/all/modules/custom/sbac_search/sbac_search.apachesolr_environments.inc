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
  $environment->env_id = 'amazon_apache_solr_environment';
  $environment->name = 'Amazon Apache Solr Environment';
  $environment->url = 'http://ec2-54-242-95-39.compute-1.amazonaws.com:8080/solr/dev';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_search_facet_pages' => '',
  );
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
  $export['amazon_apache_solr_environment'] = $environment;

  return $export;
}
