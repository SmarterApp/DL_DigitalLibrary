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
  $environment->url = 'http://useast1-c1.acquia-search.com/solr/BVWZ-37038_sbacstg';
  $environment->service_class = 'AcquiaSearchService';
  $environment->conf = array(
    'acquia_override_auto_switch' => 1,
    'acquia_override_selector' => 'BVWZ-37038_sbacdev',
    'acquia_override_subscription_corename' => 'BVWZ-37038_sbacdev',
    'acquia_override_subscription_id' => 'BVWZ-37038',
    'acquia_override_subscription_key' => '9becc29baa4f91fac0900c6625c59534',
    'acquia_search_key' => 'fd919846b89046b75e2403a5a492b5e40f37124c',
    'apachesolr_access_always_add_grants' => 0,
    'apachesolr_direct_commit' => 0,
    'apachesolr_read_only' => '1',
    'apachesolr_soft_commit' => 0,
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'alignment',
      1 => 'help_page',
      2 => 'resource',
      3 => 'topic',
    ),
    'taxonomy_term' => array(
      0 => 'forum',
    ),
    'comment' => array(
      0 => 'comment_node_topic',
    ),
  );
  $export['acquia_search_server_1'] = $environment;

  return $export;
}
