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
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/dev';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
    ),
    'file' => array(
      0 => 'audio',
      1 => 'document',
      2 => 'image',
      3 => 'video',
    ),
    'user' => array(
      0 => 'user',
    ),
  );
  $export['amazon_apache_solr_dev'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_environment_local';
  $environment->name = 'Amazon Apache Solr - Local';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/dev';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '1',
  );
  $export['amazon_apache_solr_environment_local'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_prod';
  $environment->name = 'Amazon Apache Solr - Prod';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/production';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
    ),
    'file' => array(
      0 => 'audio',
      1 => 'document',
      2 => 'image',
      3 => 'video',
    ),
    'user' => array(
      0 => 'user',
    ),
  );
  $export['amazon_apache_solr_prod'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_test';
  $environment->name = 'Amazon Apache Solr - Test';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/staging';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
    ),
    'file' => array(
      0 => 'audio',
      1 => 'document',
      2 => 'image',
      3 => 'video',
    ),
    'user' => array(
      0 => 'user',
    ),
  );
  $export['amazon_apache_solr_test'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_integration';
  $environment->name = 'Amazon Apache Solr - Integration';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/integration';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
    ),
    'file' => array(
      0 => 'audio',
      1 => 'document',
      2 => 'image',
      3 => 'video',
    ),
    'user' => array(
      0 => 'user',
    ),
  );
  $export['amazon_apache_solr_integ'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_training';
  $environment->name = 'Amazon Apache Solr - Training';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/training';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_read_only' => '0',
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
    ),
    'file' => array(
      0 => 'audio',
      1 => 'document',
      2 => 'image',
      3 => 'video',
    ),
    'user' => array(
      0 => 'user',
    ),
  );
  $export['amazon_apache_solr_train'] = $environment;

  return $export;
}
