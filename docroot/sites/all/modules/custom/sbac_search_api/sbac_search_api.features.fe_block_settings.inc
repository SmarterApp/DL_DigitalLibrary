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

  $export['current_search-standard'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'standard',
    'module' => 'current_search',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
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

  $export['facetapi-7ERviPJtMLm6XXzQWWpYSLto72jI1HhP'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '7ERviPJtMLm6XXzQWWpYSLto72jI1HhP',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -40,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -36,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -39,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -41,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -34,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -33,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -35,
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
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -37,
      ),
    ),
    'title' => 'Media Type',
    'visibility' => 1,
  );

  $export['facetapi-yNElAjJhESbU04dGEzguUfiDWud0Zqlh'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'yNElAjJhESbU04dGEzguUfiDWud0Zqlh',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => 'instructional
professional-learning
playlist
instructional/*
professional-learning/*
playlist/*',
    'roles' => array(),
    'themes' => array(
      'SBAC' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'SBAC',
        'weight' => -38,
      ),
    ),
    'title' => 'Common Core State Standard',
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
playlist/*',
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
playlist/*',
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
instructional/*',
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
professional-learning/*',
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
