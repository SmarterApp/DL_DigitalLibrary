<?php

/**
 * Implementation of hook_theme()
 *
 */
function sbac_resource_theme($existing, $type, $theme, $path) {
  $items['node__resource'] = array(
    'render element' => 'elements',
    'path' => $path . '/templates',
    'template' => 'node--resource',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_node',
    ),
  );

  $items['sbac_resource_profile'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates',
    'template' => 'resource-profile',
    'variables' => array('node' => NULL),
    'preprocess functions' => array(
      'sbac_resource_profile_fields',
    ),
  );

  $items['sbac_resource_related_resources_header'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates/related_resources',
    'template' => 'related-resources-header',
  );

  $items['sbac_resource_card'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates/related_resources',
    'template' => 'resource-card',
    'variables' => array('fields' => NULL),
  );

  $items['sbac_resource_no_related_resources'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates/related_resources',
    'template' => 'no-related-resources',
  );

  $items['resource_node_form'] = array(
    'file' => 'sbac_resource.forms.inc',
    'render element' => 'form',
  );

  $items['resource_alignment_item'] = array(
    'variables' => array('title' => NULL, 'tags' => array()),
    'template' => 'alignment-item',
  );

  $items['digital_library'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates',
    'template' => 'digital-library',
    'variables' => array(
      'digital_library_output' => NULL,
      'no_results' => NULL,
      'smart_search_welcome' => NULL,
    )
  );

  $items['smart_search_welcome'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates',
    'template' => 'smart-search-welcome',
    'variables' => array(
      'current_filters' => NULL,
      'kw' => NULL,
    ),
    'preprocess functions' => array(
      'sbac_resource_smart_search_welcome__preprocess',
    ),
  );

  $items['my_resources'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates',
    'template' => 'my-resources',
    'variables' => array(
      'my_resources_output' => NULL,
      'no_results' => NULL,
    )
  );

  $items['resource_review'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates',
    'template' => 'resource-review',
    'variables' => array(
      'resource_review_output' => NULL,
      'no_results' => NULL,
    )
  );

  // Resources - Grid View
  $items['views_view_fields__resources__grid_view'] = array(
    'template' => 'templates/resources/grid_view/views-view-fields--resources--grid-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resources - Grid View
  $items['views_view__resources__grid_view'] = array(
    'template' => 'templates/resources/grid_view/views-view--resources--grid-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resources - List View
  $items['views_view_fields__resources__list_view'] = array(
    'template' => 'templates/resources/list_view/views-view-fields--resources--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resources__list_view__preprocess'
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resources - List View
  $items['views_view__resources__list_view'] = array(
    'template' => 'templates/resources/list_view/views-view--resources--list-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resources__list_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // My Resources - Grid View
  $items['views_view_fields__my_resources__grid_view'] = array(
    'template' => 'templates/my_resources/grid_view/views-view-fields--my-resources--grid-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__my_resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // My Resources - Grid View
  $items['views_view__my_resources__grid_view'] = array(
    'template' => 'templates/my_resources/grid_view/views-view--my-resources--grid-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__my_resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // My Resources - List View
  $items['views_view_fields__my_resources__list_view'] = array(
    'template' => 'templates/my_resources/list_view/views-view-fields--my-resources--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__my_resources__list_view__preprocess'
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // My Resources - List View
  $items['views_view__my_resources__list_view'] = array(
    'template' => 'templates/my_resources/list_view/views-view--my-resources--list-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__my_resources__list_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resource Review - Grid View
  $items['views_view_fields__resource_review__grid_view'] = array(
    'template' => 'templates/resource_review/grid_view/views-view-fields--resource-review--grid-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resource_review__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resource Review - Grid View
  $items['views_view__resource_review__grid_view'] = array(
    'template' => 'templates/resource_review/grid_view/views-view--resource-review--grid-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resource_review__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resource Review - List View
  $items['views_view_fields__resource_review__list_view'] = array(
    'template' => 'templates/resource_review/list_view/views-view-fields--resource-review--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resource_review__list_view__preprocess'
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resource Review - List View
  $items['views_view__resource_review__list_view'] = array(
    'template' => 'templates/resource_review/list_view/views-view--resource-review--list-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resource_review__list_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  return $items;
}

/**
 * Extract the title from the alignment
 *
 * @param array $alignment
 *  The alignment array element.
 * @return string
 *   The themed output.
 */
function sbac_resource__alignment_extract($alignment) {
  $title = check_plain($alignment['#title']);
  $tags = array();
  foreach ($alignment['#items'] as $item) {
    $tags[] = $item['taxonomy_term']->name;
  }
  return theme('resource_alignment_item', array('title' => $title, 'tags' => $tags));
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view__resources__grid_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view__resources__list_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__resources__grid_view__preprocess(&$vars) {
  $vars['fields']['state_button'] = NULL;
  $image_assets = _sbac_resource_grid_image($vars['fields']);
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  $variables = _sbac_resource_digital_library_links($vars['fields']);
  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grades'])) {
    $vars['fields']['grades'] = $variables['grades'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
  if (isset($variables['favorites_link'])) {
    $vars['fields']['favorites_link'] = $variables['favorites_link'];
  }
  if (isset($variables['favorites_tooltip'])) {
    $vars['fields']['favorites_tooltip'] = $variables['favorites_tooltip'];
  }
  if (isset($variables['rating'])) {
    $vars['fields']['rating'] = $variables['rating'];
  }
  if (isset($variables['rating_count'])) {
    $vars['fields']['rating_count'] = $variables['rating_count'];
  }
  global $base_url;
  $path = $vars['fields']['path']->content;
  $path = str_replace('<span class="field-content">', '', $path);
  $path = str_replace('</span>', '', $path);
  $vars['fields']['path']->content = $base_url . $path;
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__resources__list_view__preprocess(&$vars) {
  $image_assets = _sbac_resource_grid_image($vars['fields'], 'list');
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  $variables = _sbac_resource_digital_library_links($vars['fields']);
  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grade'])) {
    $vars['fields']['grade'] = $variables['grade'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
  if (isset($variables['favorites_link'])) {
    $vars['fields']['favorites_link'] = $variables['favorites_link'];
  }
  if (isset($variables['favorites_tooltip'])) {
    $vars['fields']['favorites_tooltip'] = $variables['favorites_tooltip'];
  }
  if (isset($variables['rating'])) {
    $vars['fields']['rating'] = $variables['rating'];
  }
  if (isset($variables['rating_count'])) {
    $vars['fields']['rating_count'] = $variables['rating_count'];
  }
  global $base_url;
  $path = $vars['fields']['path']->content;
  $path = str_replace('<span class="field-content">', '', $path);
  $path = str_replace('</span>', '', $path);
  $vars['fields']['path']->content = $base_url . $path;
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view__my_resources__grid_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view__my_resources__list_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__my_resources__grid_view__preprocess(&$vars) {
  global $user;
  $vars['fields']['state_button'] = NULL;
  $image_assets = _sbac_resource_grid_image($vars['fields']);
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  if (in_array('resource contributor', $user->roles) || in_array('DLRB Member', $user->roles)) {
    $variables = _sbac_resource_my_resources_links($vars['fields']);
  }
  if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
    $variables = _sbac_resource_my_resources_admin_links($vars['fields']);
  }
  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grades'])) {
    $vars['fields']['grades'] = $variables['grades'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
  if (isset($variables['favorites_link'])) {
    $vars['fields']['favorites_link'] = $variables['favorites_link'];
  }
  if (isset($variables['favorites_tooltip'])) {
    $vars['fields']['favorites_tooltip'] = $variables['favorites_tooltip'];
  }
  global $base_url;
  $path = $vars['fields']['path']->content;
  $path = str_replace('<span class="field-content">', '', $path);
  $path = str_replace('</span>', '', $path);
  $vars['fields']['path']->content = $base_url . $path;
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__my_resources__list_view__preprocess(&$vars) {
  global $user;
  $image_assets = _sbac_resource_grid_image($vars['fields'], 'list');
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  if (in_array('resource contributor', $user->roles) || in_array('DLRB Member', $user->roles)) {
    $variables = _sbac_resource_my_resources_links($vars['fields']);
  }
  if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
    $variables = _sbac_resource_my_resources_admin_links($vars['fields']);
  }
  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grade'])) {
    $vars['fields']['grade'] = $variables['grade'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
  if (isset($variables['favorites_link'])) {
    $vars['fields']['favorites_link'] = $variables['favorites_link'];
  }
  if (isset($variables['favorites_tooltip'])) {
    $vars['fields']['favorites_tooltip'] = $variables['favorites_tooltip'];
  }
  global $base_url;
  $path = $vars['fields']['path']->content;
  $path = str_replace('<span class="field-content">', '', $path);
  $path = str_replace('</span>', '', $path);
  $vars['fields']['path']->content = $base_url . $path;
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view__resource_review__grid_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view__resource_review__list_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__resource_review__grid_view__preprocess(&$vars) {
  $vars['fields']['state_button'] = NULL;
  $image_assets = _sbac_resource_grid_image($vars['fields']);
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  $variables = _sbac_resource_resource_review_links($vars['fields'], $vars['row']);
  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grades'])) {
    $vars['fields']['grades'] = $variables['grades'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
  global $base_url;
  $path = $vars['fields']['path']->content;
  $path = str_replace('<span class="field-content">', '', $path);
  $path = str_replace('</span>', '', $path);
  $vars['fields']['path']->content = $base_url . $path;
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__resource_review__list_view__preprocess(&$vars) {
  $image_assets = _sbac_resource_grid_image($vars['fields'], 'list');
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  $variables = _sbac_resource_resource_review_links($vars['fields'], $vars['row']);
  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grade'])) {
    $vars['fields']['grade'] = $variables['grade'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
  global $base_url;
  $path = $vars['fields']['path']->content;
  $path = str_replace('<span class="field-content">', '', $path);
  $path = str_replace('</span>', '', $path);
  $vars['fields']['path']->content = $base_url . $path;
}

/**
 * Returns the image icon.
 *
 * @param $fields
 */
function _sbac_resource_grid_image($fields, $view_display = 'grid') {
  $variables = array();
  if (isset($fields['nid']->raw)) {
    $class = 'grid-image lazy';
    if ($view_display == 'list') {
      $class = 'list-image lazy';
    }

    $default_file = 'public://file.png';

    $thumbnail_uri = $fields['field_thumbnail_uri']->content;
    $thumbnail_uri  = str_replace('<div class="field-content">', '', $thumbnail_uri);
    $thumbnail_uri  = str_replace('</div>', '', $thumbnail_uri);
    $thumbnail_pieces = explode('::', $thumbnail_uri);
    $uri = $thumbnail_pieces[0];
    $url = $thumbnail_pieces[1];

    $ext = pathinfo($uri, PATHINFO_EXTENSION);
    $type = _sbac_resource_determine_extension($ext);
    if ($type != 'image') {
      $url = $default_file;
      $uri = $default_file;
    }

    $variables['image'] = theme('image_style', array(
      'style_name' => 'resource_image_grid',
      'path' => $uri,
      'attributes' => array('class' => $class),
      'alt'=>'Resource thumbnail image'
    ));
    $variables['mime-type'] = file_get_mimetype($url);
    $variables['file-type-icon'] = _sbac_resource_determine_file_type_icon($ext);
  }
  return $variables;
}

/**
 * Creates the admin links (only edit)
 *
 * @param $fields
 * @return array
 */
function _sbac_resource_my_resources_admin_links($fields) {
  $variables = array();
  global $user;
  $nid = $fields['nid']->raw;

  if ($fields['state']->raw == 'published') {
    $variables['sticky'] = FALSE;
    if ($fields['sticky']->raw) {
      $variables['sticky'] = TRUE;
    }

    $favorites = sbac_favorites_get_favorites($user->uid, $nid);
    if ($favorites) {
      $variables['favorites_link'] = t('Favorite');
    }

    $variables['views'] = '0';
    if (isset($fields['field_unique_views'])) {
      $variables['views'] = $fields['field_unique_views']->content;
    }
    $variables['downloads'] = '0';
    if (isset($fields['field_asset_downloads'])) {
      $variables['downloads'] = $fields['field_asset_downloads']->content;
    }
    $variables['collaborators'] = 'N Collaborations';
    $variables['subject'] = $fields['field_subject']->content;
    $variables['grades'] = $fields['field_grades']->content;
    $variables['media_types'] = $fields['field_digital_media_type']->content;
  }
  else {
    $url = url('node/' . $nid, array('absolute' => TRUE));
    $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
    $url = url('node/' . $nid . '/edit', array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
    $variables['buttons'][] = l('Edit', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
    $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
    $variables['links'][] = l('Edit', 'node/' . $nid . '/edit', array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
    $html5 = db_query("SELECT field_html5_value FROM {field_data_field_html5} WHERE entity_id = :entity_id", array(':entity_id' => $nid))->fetchField();
    if ($html5) {
      $variables['text'] = t('Draft Content Module');
    }
    else {
      $variables['text'] = t('Draft Resource');
    }
  }

  return $variables;
}

/**
 * Creates the links and buttons for the resource contributor
 *
 * @param $fields
 * @param $links
 * @param $buttons
 * @param $text
 */
function _sbac_resource_my_resources_links($fields) {
  $variables = array();
  global $user;
  if (isset($fields['state']->raw)) {
    $nid = $fields['nid']->raw;
    $state = $fields['state']->raw;
    switch ($state) {
      case 'draft':
        $url = url('node/' . $nid . '/edit', array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['buttons'][] = l('Edit', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['buttons'][] = l(t('Delete'), 'sbac_resource/nojs/delete-resource', array(
          'html' => TRUE,
          'attributes' => array(
            'class' => 'use-ajax medium red button ctools-modal-sbac-resource-modal-delete-resource-button-' . $nid,
            'id' => 'sbac-resource-modal-delete-resource-button-' . $nid,
          ),
          'query' => array('nid' => $nid),
        ));

        // JS to properly size the modal when submit resource is clicked.
        $js_settings = array(
          'sbac-resource-modal-delete-resource-button-' . $nid => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 600,
              'height' => 160,
            ),
          ),
        );
        drupal_add_js($js_settings, 'setting');

        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = l('Edit', 'node/' . $nid . '/edit', array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = l(t('Delete'), 'sbac_resource/nojs/delete-resource', array(
          'html' => TRUE,
          'query' => array(
            'nid' => $nid
          ),
          'attributes' => array(
            'class' => 'use-ajax ctools-modal-sbac-resource-modal-delete-resource-link-' . $nid,
            'id' => 'sbac-resource-modal-delete-resource-link-' . $nid,
          )
        ));

        // JS to properly size the modal when submit resource is clicked.
        $js_settings = array(
          'sbac-resource-modal-delete-resource-link-' . $nid => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 600,
              'height' => 160,
            ),
          ),
        );
        drupal_add_js($js_settings, 'setting');

        $variables['text'] = t('Saved as Draft');
        break;
      case 'needs_review':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['buttons'][] = l(t('Un-submit'), 'sbac-resource/nojs/unsubmit-resource-modal', array(
          'html' => TRUE,
          'query' => array(
            'nid' => $nid
          ),
          'attributes' => array(
            'class' => 'use-ajax button blue ctools-modal-sbac-resource-modal-unsubmit-resource-button-' . $nid,
            'id' => 'sbac-resource-modal-unsubmit-resource-button-' . $nid,
          )
        ));

        // JS to properly size the modal when submit resource is clicked.
        $js_settings = array(
          'sbac-resource-modal-unsubmit-resource-button-' . $nid => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 600,
              'height' => 160,
            ),
          ),
        );
        drupal_add_js($js_settings, 'setting');

        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = l(t('Un-submit'), 'sbac-resource/nojs/unsubmit-resource-modal', array(
          'html' => TRUE,
          'query' => array(
            'nid' => $nid
          ),
          'attributes' => array(
            'class' => 'use-ajax ctools-modal-sbac-resource-modal-unsubmit-resource-link-' . $nid,
            'id' => 'sbac-resource-modal-unsubmit-resource-link-' . $nid,
          )
        ));

        // JS to properly size the modal when submit resource is clicked.
        $js_settings = array(
          'sbac-resource-modal-unsubmit-resource-link-' . $nid => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 600,
              'height' => 160,
            ),
          ),
        );
        drupal_add_js($js_settings, 'setting');

        $variables['text'] = t('Submitted');
        break;
      case 'being_reviewed':
        $url = url('node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['text'] = t('In Review');

        $gate_keeper = _sbac_resource_determine_feedback($nid, 'gate_keeper', FALSE, 1, 0, 1, 'single');
        $completed_gate_keeper = _sbac_resource_determine_feedback($nid, 'gate_keeper', FALSE, 1, 1, 1, 'single');
        if (!$gate_keeper && !$completed_gate_keeper) {
          $variables['buttons'][] = l(t('Un-submit'), 'sbac-resource/nojs/unsubmit-resource-modal', array(
            'html' => TRUE,
            'query' => array(
              'nid' => $nid
            ),
            'attributes' => array(
              'class' => 'use-ajax button blue ctools-modal-sbac-resource-modal-unsubmit-resource-button-' . $nid,
              'id' => 'sbac-resource-modal-unsubmit-resource-button-' . $nid,
            )
          ));

          // JS to properly size the modal when submit resource is clicked.
          $js_settings = array(
            'sbac-resource-modal-unsubmit-resource-button-' . $nid => array(
              'modalSize' => array(
                'type' => 'fixed',
                'width' => 600,
                'height' => 160,
              ),
            ),
          );
          drupal_add_js($js_settings, 'setting');

          $variables['links'][] = l(t('Un-submit'), 'sbac-resource/nojs/unsubmit-resource-modal', array(
            'html' => TRUE,
            'query' => array(
              'nid' => $nid
            ),
            'attributes' => array(
              'class' => 'use-ajax ctools-modal-sbac-resource-modal-unsubmit-resource-link-' . $nid,
              'id' => 'sbac-resource-modal-unsubmit-resource-link-' . $nid,
            )
          ));

          // JS to properly size the modal when submit resource is clicked.
          $js_settings = array(
            'sbac-resource-modal-unsubmit-resource-link-' . $nid => array(
              'modalSize' => array(
                'type' => 'fixed',
                'width' => 600,
                'height' => 160,
              ),
            ),
          );
          drupal_add_js($js_settings, 'setting');
        }

        break;
      case 'rejected':
        $variables['buttons'][] = l('View Notification', 'user', array('absolute' => TRUE, 'fragment' => 'profile-notifications', 'attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = l('View Notification', 'user', array('absolute' => TRUE, 'fragment' => 'profile-notifications', 'query' => array('destination' => arg(0))));
        $url = url('node/' . $nid . '/edit', array('absolute' => TRUE));
        $variables['links'][] = l('Edit & Resubmit', $url, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['text'] = t('Returned');
        break;
      case 'approved':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['text'] = t('In Review');
        break;
      case 'published':
        $variables['sticky'] = FALSE;
        if ($fields['sticky']->raw) {
          $variables['sticky'] = TRUE;
        }

        $favorites_class = 'sbac-favorites-link-no';
        $variables['favorites_tooltip'] = '<div class="sbac-favorites-tooltip f-dropdown right" style="display:none;">Add to Favorites</div>';
        $favorites = sbac_favorites_get_favorites($user->uid, $nid);
        if ($favorites) {
          $favorites_class = 'sbac-favorites-link-yes';
          $variables['favorites_tooltip'] = '<div class="sbac-favorites-tooltip f-dropdown right" style="display:none;">Added to Favorites</div>';
        }
        $variables['favorites_link'] = l('Favorites', $_GET['q'], array('attributes' => array('class' => array('sbac-favorites-link', $favorites_class), 'nid' => $nid, 'uid' => $user->uid)));

        $variables['views'] = '0';
        if (isset($fields['field_unique_views'])) {
          $variables['views'] = $fields['field_unique_views']->content;
        }
        $variables['downloads'] = '0';
        if (isset($fields['field_asset_downloads'])) {
          $variables['downloads'] = $fields['field_asset_downloads']->content;
        }
        $variables['collaborators'] = 'N Collaborations';
        $variables['subject'] = $fields['field_subject']->content;
        $variables['grades'] = $fields['field_grades']->content;
        $variables['media_types'] = $fields['field_digital_media_type']->content;
        break;
      case 'removed':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['buttons'][] = l(t('Delete'), 'sbac_resource/nojs/delete-resource', array(
          'html' => TRUE,
          'attributes' => array(
            'class' => 'use-ajax medium red button ctools-modal-sbac-resource-modal-delete-resource-button-' . $nid,
            'id' => 'sbac-resource-modal-delete-resource-button-' . $nid,
          ),
          'query' => array('nid' => $nid),
        ));

        // JS to properly size the modal when submit resource is clicked.
        $js_settings = array(
          'sbac-resource-modal-delete-resource-button-' . $nid => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 600,
              'height' => 160,
            ),
          ),
        );
        drupal_add_js($js_settings, 'setting');

        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = l(t('Delete'), 'sbac_resource/nojs/delete-resource', array(
          'html' => TRUE,
          'query' => array(
            'nid' => $nid
          ),
          'attributes' => array(
            'class' => 'use-ajax ctools-modal-sbac-resource-modal-delete-resource-link-' . $nid,
            'id' => 'sbac-resource-modal-delete-resource-link-' . $nid,
          )
        ));

        // JS to properly size the modal when submit resource is clicked.
        $js_settings = array(
          'sbac-resource-modal-delete-resource-link-' . $nid => array(
            'modalSize' => array(
              'type' => 'fixed',
              'width' => 600,
              'height' => 160,
            ),
          ),
        );
        drupal_add_js($js_settings, 'setting');

        $variables['text'] = t('Removed');
        break;
    }
  }
  return $variables;
}


/**
 * Resource Review Links.
 *
 * @param $fields
 * @return array
 */
function _sbac_resource_resource_review_links($fields) {
  $variables = array();
  if (isset($fields['state']->raw)) {
    $nid = $fields['nid']->raw;
    $state = $fields['state']->raw;
    switch ($state) {
      case 'needs_review':
        $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'gate_keeper');
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = _sbac_resource_start_review_link($nid, 'gate_keeper', 'link');
        $variables['text'] = t('Needs Review');
        break;
      case 'being_reviewed':
        global $user;
        // check for a completed GK by any user and then init the review process
        if ($completed = _sbac_resource_determine_feedback($nid, 'gate_keeper', FALSE, 1, 1, 1, 'single')) {
          // check for an active Review by the current user to continue review
          if ($active = _sbac_resource_determine_feedback($nid, 'qc', $user->uid, 1, 0, 1, 'single')) {
            $url = url('node/' . $nid, array('absolute' => TRUE, 'fragment' => 'review-qc', 'query' => array('destination' => arg(0))));
            $variables['buttons'][] = l('Continue Review', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
            $variables['links'][] = l('Continue Review', $url, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
            $variables['text'] = t('Being Reviewed');
          }
          // start review
          else {
            $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'qc');
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
            $variables['links'][] = _sbac_resource_start_review_link($nid, 'qc', 'link');
            $variables['text'] = t('Needs Review');
          }
        }
        // no completed GK, so start or continue
        else {
          // check for an active GK by the current user to continue review
          if ($active = _sbac_resource_determine_feedback($nid, 'gate_keeper', $user->uid, 1, 0, 1, 'single')) {
            $url = url('node/' . $nid, array('absolute' => TRUE, 'fragment' => 'review-gk', 'query' => array('destination' => arg(0))));
            $variables['buttons'][] = l('Continue Review', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
            $variables['links'][] = l('Continue Review', $url, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
            $variables['text'] = t('Being Reviewed');
          }
          // start review
          else {
            $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'gate_keeper');
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
            $variables['links'][] = _sbac_resource_start_review_link($nid, 'gate_keeper', 'link');
            $variables['text'] = t('Needs Review');
          }
        }
        break;
      case 'approved':
        global $user;
        $feedback = _sbac_resource_determine_feedback($nid, 'post', $user->uid, 1, 0, 1, 'single');
        if ($feedback) {
          $url = url('node/' . $nid, array('absolute' => TRUE, 'fragment' => 'review-post', 'query' => array('destination' => arg(0))));
          $link = l('Continue Review', $url);
          $variables['buttons'][] = l('Continue Review', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
          $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
          $variables['links'][] = $link;
          $variables['text'] = t('Being Reviewed');
        }
        else {
          $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'post');
          $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
          $variables['links'][] = _sbac_resource_start_review_link($nid, 'post', 'link');
          $variables['text'] = t('Needs Posting');
        }
        break;
    }
  }
  return $variables;
}

/**
 * Creates the links and buttons for the digital library page.
 *
 * Role is not taken into consideration since all roles only
 * see published nodes at this point.
 *
 * @param $fields
 * @return array
 */
function _sbac_resource_digital_library_links($fields) {
  $variables = array();
  global $user;

  $nid = $fields['nid']->raw;
  if ($user->uid == 1 || in_array('DLRB member', $user->roles) || in_array('digital library administrator', $user->roles) || in_array('system administrator', $user->roles)) {
    $url = url('node/' . $nid . '/edit', array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
    $variables['buttons'][] = l('Edit', $url, array(
      'attributes' => array(
        'class' => array('medium', 'button'),
        'query' => array('destination' => arg(0))
      )
    ));
  }

  $variables['sticky'] = FALSE;
  if ($fields['sticky']->raw) {
    $variables['sticky'] = TRUE;
  }

  $favorites = sbac_favorites_get_favorites($user->uid, $nid);
  if ($favorites) {
    $variables['favorites_link'] = t('Favorite');
  }

  $variables['views'] = '0';
  if (isset($fields['field_unique_views'])) {
    $variables['views'] = $fields['field_unique_views']->content;
  }
  $variables['downloads'] = '0';
  if (isset($fields['field_asset_downloads'])) {
    $variables['downloads'] = $fields['field_asset_downloads']->content;
  }
  $variables['collaborators'] = 'N Collaborations';
  $variables['subject'] = $fields['field_subject']->content;
  $variables['grades'] = $fields['field_grades']->content;
  $variables['media_types'] = $fields['field_digital_media_type']->content;

  // Get the resource rating.
  $count_query = "  SELECT    COUNT(id)
                    FROM      {eck_review}
                    WHERE     type = 'end_use'
                    AND       node_id = :node_id
                    AND       status = 1
                 ";
  $review_count = db_query($count_query, array(':node_id' => $fields['nid']->raw))->fetchField();
  $average_query = "
    SELECT
      (avg(student.field_student_learning_rating) +
       avg(dev.field_pro_dev_rating) +
       avg(ease.field_ease_use_rating)) / 3
    FROM {field_data_field_student_learning} student
      INNER JOIN {eck_review} review
        ON review.id = student.entity_id
      LEFT JOIN {field_data_field_pro_dev} dev
        ON dev.entity_id = review.id
      LEFT JOIN {field_data_field_ease_use} ease
        ON ease.entity_id = review.id
    WHERE student.bundle = 'end_use'
          AND review.node_id = :nid";
  $average = db_query($average_query, array(':nid'=>$fields['nid']->raw))->fetchField();
  $fivestar = theme('fivestar_formatter_default', array(
    'element' => array(
      '#theme' => 'fivestar_formatter_default',
      '#rating' => $average,
      '#instance_settings' => array(
        'stars' => 4,
        'allow_clear' => 0,
        'target' => 'none',
        'user_register_form' => '',
      ),
      '#display_settings' => array(
        'widget' => array(
          'fivestar_widget' => '',
        ),
        'style' => 'average',
        'text' => 'average',
        'expose' => 1,
      ),
      '#widget' => array(
        'name' => 'oxygen',
        'css' => drupal_get_path('module', 'fivestar') . '/widgets/oxygen/oxygen.css',
      ),
      '#description' => '',
      '#children' => '',
    ),
  ));

  $variables['rating'] = $fivestar;
  $variables['rating_count'] = $review_count;

  return $variables;
}

/**
 * Selects the number of feedback review items from the table for
 * the given nid / uid.
 *
 * @param $uid
 * @param $nid
 */
function _sbac_resource_determine_feedback($nid, $type = 'qc', $uid = FALSE, $status = FALSE, $completed = FALSE, $current = FALSE, $return_type = 'set', $uid_not = FALSE, $archived = FALSE) {
  $feedback = array();
  if ($nid) {
    $query = db_select('eck_feedback', 'f');
    $query->fields('f', array('id', 'uid', 'node_id', 'created', 'changed', 'title', 'status', 'completed', 'met_criteria', 'current'));
    $query->condition('f.node_id', $nid);
    $query->condition('f.type', $type);
    if ($uid !== FALSE) {
      if ($uid_not) {
        $query->condition('f.uid', array($uid), 'NOT IN');
      }
      else{
        $query->condition('f.uid', $uid);
      }
    }
    if ($status !== FALSE) {
      if ($archived == FALSE) {
        $query->condition('f.status', $status);
      }
      else {
        $condition1 = db_and()->condition('f.status', 1);
        $condition2 = db_and()->condition('f.status', 0)->condition('f.archived', 1);
        $query->condition(db_or()->condition($condition1)->condition($condition2));
        unset($condition1);
        unset($condition2);
      }
    }
    if ($completed !== FALSE) {
      $query->condition('f.completed', $completed);
    }
    if ($current !== FALSE) {
      $query->condition('f.current', $current);
    }

    if ($return_type == 'single') { // get the latest result.
      $query->orderBy('f.id', 'DESC');
      $query->range(0, 1);
      $single = $query->execute()->fetchAssoc();

      unset($query);
      return $single;
    }
    else {
      $result = $query->execute();
      foreach ($result as $record) {
        $feedback[] = $record;
      }

      unset($query);
      unset($result);
      unset($record);
    }
  }
  return $feedback;
}

/**
 * Selects the number of feedback review items from the table for
 * the given nid / uid.
 *
 * @param $uid
 * @param $nid
 */
function _sbac_resource_determine_gate_keeper($nid, $uid = FALSE) {
  if ($nid) {
    $query = db_select('eck_feedback', 'f');
    $query->fields('f', array('id', 'uid', 'node_id', 'created', 'changed', 'title', 'status', 'completed', 'met_criteria', 'current'));
    $query->condition('f.node_id', $nid);
    $query->condition('f.type', 'gate_keeper');
    if ($uid) {
      $query->condition('f.uid', $uid);
    }
    $query->orderBy('f.id', 'DESC');
    $query->range(0, 1);
    return $query->execute()->fetchAssoc();
  }
  return FALSE;
}

/**
 * Pulled from sbac_core/components/feedback/feedback.page.inc
 * _feedback_start_review_link
 * Updated to take more control over the link attributes.
 *
 * @param $node
 * @param $type
 * @return string
 */
function _sbac_resource_start_review_link($nid, $type, $style = 'button') {
  if ($type == 'gate_keeper') {
    $stub = 'gate-keeper';
  }
  elseif ($type == 'qc') {
    $stub = 'qc';
  }
  elseif ($type == 'post') {
    $stub = 'post';
  }
  else {
    return '';
  }

  static $count;
  if (is_null($count)) {
    $count = 1;
  }
  else {
    $count++;
  }
  $trigger_id = $stub . '-trigger-' . $count;
  drupal_add_library('dialog', 'dialog');

  $link_text = t('Start Review');
  if ($style == 'button') {
    $content = l($link_text, 'node/' . $nid . '/feedback/' . $stub . '/start/' . $trigger_id, array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'medium',
          'button',
          'start-review-trigger',
        ),
        'id' => $trigger_id,
      ),
    ));
  }
  else {
    $content = l($link_text, 'node/' . $nid . '/feedback/' . $stub . '/start/' . $trigger_id, array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'start-review-trigger',
        ),
        'id' => $trigger_id,
      ),
    ));
  }
  return $content;
}

function sbac_resource_smart_search_welcome__preprocess(&$vars) {
  drupal_add_js(drupal_get_path('module', 'sbac_resource') . '/js/sbac_resource.smart_search.js');
  $search_filters_output = '';
  $edit_link = '';

  $vocab_labels = array(
    'subject'                      => t('Subjects'),
    'grades'                       => t('Grades'),
    'attributes'                   => t('Attributes of the Formative Assessment Process'),
    'digital_media_type'           => t('Media Types'),
    'focus'                        => t('Resource Type'),
    'intended_end_user'            => t('Intended End Users'),
    'intended_student_populations' => t('Intended Student Populations'),
    'educational_use'              => t('Educational Use'),
    'smarter_balanced_keyword'     => t('Smarter Balanced Keywords'),
    'geographical_settings'        => t('Geographic Settings'),
    'education_alignment'          => t('Common Core State Standards'),
  );

  $view_filters = array();
  $current_filters = $vars['current_filters'];
  $kw = $vars['kw'];

  if (!empty($kw)) {
    $view_filters[] = 'Keywords: ' . $kw;
  }

  $filters = explode('::', $current_filters);
  $vocab_listing = array();
  $preformatted_filters = array();
  if ($filters) {
    foreach ($filters as $filter) {
      $filter_info = explode(':', $filter);
      if ($filter_info && sizeof($filter_info) == 2) {
        $vid = $filter_info[0];
        $tid = $filter_info[1];
        if ($vid && $tid) {
          $vocabulary = taxonomy_vocabulary_load($vid);
          $term = taxonomy_term_load($tid);
          if ($vocabulary && $term) {
            $term_label = $term->name;
            if (isset($term->field_alignment_shortname)) {
              $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
              $term_label = $term_wrapper->field_alignment_shortname->value();
            }
            $vocab_listing[$vocabulary->vid] = $vocab_labels[$vocabulary->machine_name];
            $preformatted_filters[$vocabulary->vid][] = $term_label;
          }
        }
      }
    }
  }
  if (!empty($preformatted_filters)) {
    foreach ($preformatted_filters as $vid_key => $value) {
      $target_terms_text = $vocab_listing[$vid_key] . ': ' . implode(', ', $value);
      $view_filters[] = $target_terms_text;
    }
  }

  if (!empty($view_filters) ){
    $item_list_params = array(
      'items' => $view_filters,
      'type' => 'ul',
    );
    $search_filters_output = theme('item_list', $item_list_params);
  }
  $edit_link = l('Edit Filters', '#', array('attributes' => array('class' => 'button ssw-edit-link')));
  $vars['search_filters'] = $search_filters_output;
  $vars['edit_filters_link'] = $edit_link;
}
