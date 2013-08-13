<?php
/**
 * @file
 * sbac_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['apachesolr_search-mlt-001'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'mlt-001',
    'module' => 'apachesolr_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['apachesolr_search-sort'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'sort',
    'module' => 'apachesolr_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-3oIJui0lmmBkAFFmcTEkVJot3eKv1taC'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '3oIJui0lmmBkAFFmcTEkVJot3eKv1taC',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-6hRwtQnh5QEQvA7ygy5VkqAykWm0TxHB'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '6hRwtQnh5QEQvA7ygy5VkqAykWm0TxHB',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-7Ukj7MKz3fVICF0GdXUztJSjQUICpvsL'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '7Ukj7MKz3fVICF0GdXUztJSjQUICpvsL',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-8zk7PLahZy4ZGK6It19dkxvvb4xoxujp'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '8zk7PLahZy4ZGK6It19dkxvvb4xoxujp',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-976qEsFqHaclWU8LQTmCSi0F8WA5qpGu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '976qEsFqHaclWU8LQTmCSi0F8WA5qpGu',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-TcaR6XlvhLY0ArO1gKJsskISp1lMfkY3'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'TcaR6XlvhLY0ArO1gKJsskISp1lMfkY3',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-cczDO6z8hf5wvf4VNdISsH7KcFbnBpr1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'cczDO6z8hf5wvf4VNdISsH7KcFbnBpr1',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-g2CQh9aZP2Bsz6S0fH0Smv5b30qSYu4i'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'g2CQh9aZP2Bsz6S0fH0Smv5b30qSYu4i',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-hJHWqf6WDVGSZ006BDwdCa7hyxEfaXE0'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'hJHWqf6WDVGSZ006BDwdCa7hyxEfaXE0',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-m8n3JxaLpTQBRCVL4jy2GhTO1TY7O9kV'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'm8n3JxaLpTQBRCVL4jy2GhTO1TY7O9kV',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-uRsGA4XzgGb87756vEgIy8KI3kWsqwW1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'uRsGA4XzgGb87756vEgIy8KI3kWsqwW1',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-uZb1gZf1RIvsYgKR55gy4pQdXYNbi27G'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'uZb1gZf1RIvsYgKR55gy4pQdXYNbi27G',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-wReCb900qa2SH47du0yj6MZVXPigCrhH'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'wReCb900qa2SH47du0yj6MZVXPigCrhH',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
