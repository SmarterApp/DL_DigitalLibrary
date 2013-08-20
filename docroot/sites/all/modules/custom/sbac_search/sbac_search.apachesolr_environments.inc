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
  $environment->env_id = 'amazon_apache_solr_dev';
  $environment->name = 'Amazon Apache Solr - Dev';
  $environment->url = 'http://ec2-54-242-95-39.compute-1.amazonaws.com:8080/solr/dev';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array();
  $export['amazon_apache_solr_dev'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_environment_local';
  $environment->name = 'Amazon Apache Solr - Local';
  $environment->url = 'http://ec2-54-242-95-39.compute-1.amazonaws.com:8080/solr/dev';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '1',
  );
  $environment->index_bundles = array();
  $export['amazon_apache_solr_environment_local'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_prod';
  $environment->name = 'Amazon Apache Solr - Prod';
  $environment->url = 'http://ec2-54-242-95-39.compute-1.amazonaws.com:8080/solr/production';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array();
  $export['amazon_apache_solr_prod'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_test';
  $environment->name = 'Amazon Apache Solr - Test';
  $environment->url = 'http://ec2-54-242-95-39.compute-1.amazonaws.com:8080/solr/staging';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array();
  $export['amazon_apache_solr_test'] = $environment;

  return $export;
}
