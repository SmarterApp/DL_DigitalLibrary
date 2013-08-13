<?php
/**
 * @file
 *  Provides the views plugin information.
 */

/**
 * Implements hook_views_plugin().
 */
function sbac_search_views_plugins() {
  return array(
    'module' => 'sbac_search',
    'pager' => array(
      'load_alot' => array(
        'title' => t('Search Pager'),
        'help' => t('sbac_search'),
        'handler' => 'views_plugin_pager_load_alot',
        'uses options' => TRUE,
        'parent' => 'full',
      ),
    ),
  );
}
