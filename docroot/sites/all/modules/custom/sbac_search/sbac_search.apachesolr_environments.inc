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
    'apachesolr_index_last' => array(
      'node' => array(
        'last_changed' => '1383148237',
        'last_entity_id' => '2586',
      ),
      'taxonomy_term' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'comment' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'feedback' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'review' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'media' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'flag' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'field_collection_item' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'file' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'taxonomy_vocabulary' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'user' => array(
        'last_changed' => '1383351799',
        'last_entity_id' => '1',
      ),
      'wysiwyg_profile' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
    ),
    'apachesolr_index_updated' => 1383593574,
    'apachesolr_last_optimize' => 1383582187,
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
    'apachesolr_index_last' => array(
      'node' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'taxonomy_term' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'comment' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'feedback' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'review' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'media' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'flag' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'field_collection_item' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'file' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'taxonomy_vocabulary' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'user' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'wysiwyg_profile' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
    ),
    'apachesolr_index_updated' => 0,
    'apachesolr_last_optimize' => 1383582187,
  );
  $environment->index_bundles = array();
  $export['amazon_apache_solr_environment_local'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_integration';
  $environment->name = 'Amazon Apache Solr - Integration';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/integration';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_direct_commit' => 0,
    'apachesolr_index_last' => array(
      'node' => array(
        'last_changed' => '1383148243',
        'last_entity_id' => '5311',
      ),
      'taxonomy_term' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'comment' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'feedback' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'review' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'media' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'flag' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'field_collection_item' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'file' => array(
        'last_changed' => '1383002115',
        'last_entity_id' => '2851',
      ),
      'taxonomy_vocabulary' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'user' => array(
        'last_changed' => '1383351799',
        'last_entity_id' => '1',
      ),
      'wysiwyg_profile' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
    ),
    'apachesolr_index_updated' => 1383593574,
    'apachesolr_last_optimize' => 1383582187,
    'apachesolr_read_only' => '0',
    'apachesolr_soft_commit' => 0,
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
  $export['amazon_apache_solr_integration'] = $environment;

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'amazon_apache_solr_prod';
  $environment->name = 'Amazon Apache Solr - Prod';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/production';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_index_last' => array(
      'node' => array(
        'last_changed' => '1383148237',
        'last_entity_id' => '2586',
      ),
      'taxonomy_term' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'comment' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'feedback' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'review' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'media' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'flag' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'field_collection_item' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'file' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'taxonomy_vocabulary' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'user' => array(
        'last_changed' => '1383351799',
        'last_entity_id' => '1',
      ),
      'wysiwyg_profile' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
    ),
    'apachesolr_index_updated' => 1383593574,
    'apachesolr_last_optimize' => 1383582187,
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
    'apachesolr_index_last' => array(
      'node' => array(
        'last_changed' => '1383148239',
        'last_entity_id' => '3336',
      ),
      'taxonomy_term' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'comment' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'feedback' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'review' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'media' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'flag' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'field_collection_item' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'file' => array(
        'last_changed' => '1383002115',
        'last_entity_id' => '2851',
      ),
      'taxonomy_vocabulary' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'user' => array(
        'last_changed' => '1383593596',
        'last_entity_id' => '1',
      ),
      'wysiwyg_profile' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
    ),
    'apachesolr_index_updated' => 1383593574,
    'apachesolr_last_optimize' => 1383582187,
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
  $environment->env_id = 'amazon_apache_solr_training';
  $environment->name = 'Amazon Apache Solr - Training';
  $environment->url = 'http://ec2-23-21-33-12.compute-1.amazonaws.com:8080/solr/training';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_index_last' => array(
      'node' => array(
        'last_changed' => '1383148239',
        'last_entity_id' => '3051',
      ),
      'taxonomy_term' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'comment' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'feedback' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'review' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'media' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'flag' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'field_collection_item' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'file' => array(
        'last_changed' => '1383002115',
        'last_entity_id' => '2851',
      ),
      'taxonomy_vocabulary' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
      'user' => array(
        'last_changed' => '1383593596',
        'last_entity_id' => '1',
      ),
      'wysiwyg_profile' => array(
        'last_changed' => 0,
        'last_entity_id' => 0,
      ),
    ),
    'apachesolr_index_updated' => 1383593574,
    'apachesolr_last_optimize' => 1383582187,
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
  $export['amazon_apache_solr_training'] = $environment;

  return $export;
}
