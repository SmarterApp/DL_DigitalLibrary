<?php
/**
 * @file
 * sbac_search_api.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sbac_search_api_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-cc_placeholder'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'cc_placeholder',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*
search-resources
search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => -47,
      ),
    ),
    'title' => 'Common Core State Standard',
    'visibility' => 1,
  );

  $export['block-filters_loading'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'filters_loading',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*
search-resources
search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -53,
      ),
    ),
    'title' => 'Filters',
    'visibility' => 1,
  );

  $export['block-target_placeholder'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'target_placeholder',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*
search-resources
search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => -49,
      ),
    ),
    'title' => 'Target Alignment',
    'visibility' => 1,
  );

  $export['current_search-main_search'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main_search',
    'module' => 'current_search',
    'node_types' => array(),
    'pages' => 'search-resources
search-resources/*
ajax/search-resources
ajax/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -43,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['current_search-search_sections'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'search_sections',
    'module' => 'current_search',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*
ajax/instructional
ajax/professional-learning
ajax/playlist
ajax/instructional/*
ajax/professional-learning/*
ajax/playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -44,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['facetapi-7ERviPJtMLm6XXzQWWpYSLto72jI1HhP'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '7ERviPJtMLm6XXzQWWpYSLto72jI1HhP',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -51,
      ),
    ),
    'title' => 'Grade',
    'visibility' => 1,
  );

  $export['facetapi-9IXECKP1g9XgZkpivQrvFAjmjoVe947l'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '9IXECKP1g9XgZkpivQrvFAjmjoVe947l',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -45,
      ),
    ),
    'title' => 'Educational Use',
    'visibility' => 1,
  );

  $export['facetapi-CAR5oQ63BgUNqWF0g1XH5K6fcI7P504o'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'CAR5oQ63BgUNqWF0g1XH5K6fcI7P504o',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -50,
      ),
    ),
    'title' => 'Target Alignment',
    'visibility' => 1,
  );

  $export['facetapi-HqaeQBI5mLDpJpXNDoVO6Qz1I014gYWt'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'HqaeQBI5mLDpJpXNDoVO6Qz1I014gYWt',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -52,
      ),
    ),
    'title' => 'Subject',
    'visibility' => 1,
  );

  $export['facetapi-NtPguqUCF0EUTwpi0v0Mnz1KbNyj9UNx'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'NtPguqUCF0EUTwpi0v0Mnz1KbNyj9UNx',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -42,
      ),
    ),
    'title' => 'Module Type',
    'visibility' => 1,
  );

  $export['facetapi-P8B9X4Dq1ud5HdIIwhUGtI1AmWVE0QXu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'P8B9X4Dq1ud5HdIIwhUGtI1AmWVE0QXu',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -41,
      ),
    ),
    'title' => 'Formative Assessment Attributes',
    'visibility' => 1,
  );

  $export['facetapi-SRzTQ59mFwugFsX5pvlijAz0PEacAZ6N'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'SRzTQ59mFwugFsX5pvlijAz0PEacAZ6N',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -43,
      ),
    ),
    'title' => 'Intended Student Population',
    'visibility' => 1,
  );

  $export['facetapi-X36xv2RuY1Ot0DpUulF6YvxmwbYZqp5f'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'X36xv2RuY1Ot0DpUulF6YvxmwbYZqp5f',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -46,
      ),
    ),
    'title' => 'Media Type',
    'visibility' => 1,
  );

  $export['facetapi-covvO8Y5vniTt3pqlpKW11qLdeZ3fwyE'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'covvO8Y5vniTt3pqlpKW11qLdeZ3fwyE',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -44,
      ),
    ),
    'title' => 'Intended End User',
    'visibility' => 1,
  );

  $export['facetapi-pgz5u51jQRXW3ctNMkTXIAFqugHgiXFl'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'pgz5u51jQRXW3ctNMkTXIAFqugHgiXFl',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*
search-resources
search-resources/*',
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
    'visibility' => 1,
  );

  $export['facetapi-yNElAjJhESbU04dGEzguUfiDWud0Zqlh'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'yNElAjJhESbU04dGEzguUfiDWud0Zqlh',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'cct/instructional
cct/professional-learning
cct/playlist
cct/instructional/*
cct/professional-learning/*
cct/playlist/*
cct/search-resources
cct/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -48,
      ),
    ),
    'title' => 'Common Core State Standard',
    'visibility' => 1,
  );

  $export['search-form'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'form',
    'module' => 'search',
    'node_types' => array(),
    'pages' => 'digital-library-resources*
content*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'SBAC',
        'weight' => 2,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['search_api_sorts-search-sorts'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'search-sorts',
    'module' => 'search_api_sorts',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*
search-resources
search-resources/*
ajax/instructional
ajax/professional-learning
ajax/playlist
ajax/instructional/*
ajax/professional-learning/*
ajax/playlist/*
ajax/search-resources
ajax/search-resources/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -39,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['views-1c6be29a0a3259ae3fecbb8a244460d3'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '1c6be29a0a3259ae3fecbb8a244460d3',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'playlist
playlist/*
ajax/playlist
ajax/playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -40,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['views-5ec5640b3bdae5495e8c1150e2ed9abc'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '5ec5640b3bdae5495e8c1150e2ed9abc',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'instructional
instructional/*
ajax/instructional
ajax/instructional/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -42,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['views-93f31ff576fc1070e47dee2149aae935'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '93f31ff576fc1070e47dee2149aae935',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'professional-learning
professional-learning/*
ajax/professional-learning
ajax/professional-learning/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -41,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  return $export;
}
