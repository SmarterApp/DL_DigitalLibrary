<?php
/**
 * @file
 * sbac_search.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 * 
 * Variables are set in the ENV_settings.inc file.
 * @TODO Add an admin interface to set variables.
 * 
 */
function sbac_search_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = variable_get('sbac_search_env_env_id');
  $environment->name = variable_get('sbac_search_env_name');
  $environment->url = variable_get('sbac_search_env_url');
  $environment->service_class = variable_get('sbac_search_env_service_class');
  $environment->conf = variable_get('sbac_search_env_conf');
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
