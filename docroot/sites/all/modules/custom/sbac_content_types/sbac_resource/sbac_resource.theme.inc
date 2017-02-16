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

  $items['sbac_resource_profile_print'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates/print',
    'template' => 'resource-profile-print',
    'variables' => array('node' => NULL),
    'preprocess functions' => array(
      'sbac_resource_profile_fields',
    ),
  );

  $items['sbac_resource_print'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates/print',
    'template' => 'resource-print',
    'variables' => array('print' => array(), 'type' => PRINT_HTML_FORMAT, 'node' => NULL),
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
      'pwd' => NULL,
      'pwd_highlights' => NULL,
      'pwd_hide' => NULL,
      'pwd_showmore' => NULL,
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
  drupal_add_css(drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css');
  $vars['exposed'] = '<div class="sbac-hide-exposed">' . $vars['exposed'] . '</div>';
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
  drupal_add_css(drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css');
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
  drupal_add_css(drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css');
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
  drupal_add_css(drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css');
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
    $variables = _sbac_resource_my_resources_links($vars['fields'], $vars['row']);
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
function sbac_resource_views_view_fields__my_resources__list_view__preprocess(&$vars) {
  global $user;
  $image_assets = _sbac_resource_grid_image($vars['fields'], 'list');
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  if (in_array('resource contributor', $user->roles) || in_array('DLRB Member', $user->roles)) {
    $variables = _sbac_resource_my_resources_links($vars['fields'], $vars['row']);
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
function sbac_resource_views_view__resource_review__grid_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css');
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
  drupal_add_css(drupal_get_path('module', 'sbac_resource') . '/css/sbac_resource.css');
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
  if (isset($variables['status_icons'])) {
    $vars['fields']['status_icons'] = $variables['status_icons'];
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
  if (isset($variables['status_icons'])) {
    $vars['fields']['status_icons'] = $variables['status_icons'];
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
 * @param $view_display
 *
 * @return string
 */
function _sbac_resource_grid_image($fields, $view_display = 'grid') {
  $variables = array();
  $thumbnail_pieces = array();
  if (isset($fields['nid']->raw)) {
    $class = 'grid-image lazy';
    if ($view_display == 'list') {
      $class = 'list-image lazy';
    }

    $default_file = 'no_img';
    $uri = NULL;
    $url = NULL;
    if (isset($fields['field_thumbnail_uri'])) {
      $thumbnail_uri = $fields['field_thumbnail_uri']->content;
      $thumbnail_uri = str_replace('<div class="field-content">', '', $thumbnail_uri);
      $thumbnail_uri = str_replace('</div>', '', $thumbnail_uri);
      $thumbnail_pieces = explode('::', $thumbnail_uri);
      $uri = $thumbnail_pieces[0];
      $url = $thumbnail_pieces[1];
      $ext = pathinfo($uri, PATHINFO_EXTENSION);
      $type = _sbac_resource_determine_extension($ext);
      $real_path = drupal_realpath($uri);
      if (!file_exists($real_path)) {
        $url = $default_file;
        $uri = $default_file;
      }

      if ($type != 'image') {
        $url = $default_file;
        $uri = $default_file;
      }
    }
    else {
      $url = $default_file;
      $uri = $default_file;
    }

    if ($uri != 'no_img' && $url != 'no_img') {
      $image_url = file_create_url($uri);
      $image_tag = '<img class="' . $class . '" typeof="foaf:Image" src="' . $image_url . '" width="268" height="138" alt="Resource thumbnail image" />';
      $variables['image'] = $image_tag;
      $variables['mime-type'] = file_get_mimetype($url);
      $variables['file-type-icon'] = 'document';
    }
  }
  if (count($thumbnail_pieces) && $uri != 'no_img' && $url != 'no_img') {
    return $variables;
  }
  else {
    return NULL;
  }
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

  $favorites = sbac_favorites_get_favorites($user->uid, $nid);
  if ($favorites) {
    $variables['favorites_link'] = t('Favorite');
  }

  if ($fields['state']->raw == 'published') {
    $variables['sticky'] = FALSE;
    if ($fields['sticky']->raw) {
      $variables['sticky'] = TRUE;
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

    $variables['rating'] = sbac_resource_display_fivestar_rating(sbac_resource_get_rating_average($fields['nid']->raw));
    $variables['rating_count'] = sbac_resource_get_rating_count($fields['nid']->raw);
  }
  else {
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
function _sbac_resource_my_resources_links($fields, $row) {
  $variables = array();
  global $user;
  if (isset($fields['state']->raw)) {
    $nid = $fields['nid']->raw;
    $state = $fields['state']->raw;
    $favorites = sbac_favorites_get_favorites($user->uid, $nid);
    if ($favorites) {
      $variables['favorites_link'] = t('Favorite');
    }
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
        $results = _sbac_resource_get_review_progress($nid);
        if ($results->rowCount()) {
          $result = $results->fetchAssoc();
         // they don't want the Quality Criteria Review 1,2,3 etc, so we'll remove the number at the end
          $variables['text'] = preg_replace('/\s\d$/ix', '', $result['state']);
        }
        else {
          $variables['text'] = t('In Review');
        }

        // if there is no active or completed gate keeper.
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
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $url = url('node/' . $nid . '/edit', array('absolute' => TRUE));
        $variables['buttons'][] = l('Edit & Resubmit', $url, array('absolute' => TRUE, 'attributes' => array('class' => array('medium', 'button'))));
        $variables['links'][] = l('Edit & Resubmit', $url, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['text'] = t('Returned');
        break;
      case 'approved':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['text'] = t('Arbitration Review');
        break;
      case 'published':
        $variables['sticky'] = FALSE;
        if ($fields['sticky']->raw) {
          $variables['sticky'] = TRUE;
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
 * Get the detailed review progress from the current state
 *
 * @param $nid
 * @param null $uid
 * @param $from_date
 * @param $to_date
 * @param null $order
 * @param string $order_direction
 * @param int $limit
 * @return \DatabaseStatementInterface|null
 */
function _sbac_resource_get_review_progress($nid = NULL, $uid = NULL, $from_date = NULL, $to_date = NULL, $limit = NULL, $order = NULL, $order_direction = 'ASC') {
  $query = db_select('node', 'n1');
  // get the history
  $query->innerJoin('workbench_moderation_node_history', 'h1', 'h1.nid = n1.nid');
  // get the feedback. Make sure we're only getting the completed feedback since the submission/resubmission
  $query->fields('n1', array('nid', 'title', 'created', 'sticky'));
  $query->addExpression("
  CASE
  WHEN h1.state = 'needs_review' THEN 'Submitted'
  WHEN h1.state = 'rejected' THEN 'Returned'
  WHEN h1.state = 'published' AND n1.sticky = 1 THEN 'Posted with Distinction'
  WHEN h1.state = 'published' AND n1.sticky = 0 THEN 'Posted'
  WHEN h1.state = 'approved' THEN 'Arbitration Review'
  WHEN h1.state = 'removed' THEN 'Removed'
  WHEN h1.state = 'being_reviewed' THEN (
    SELECT
      CASE
      WHEN count(*) = 0 THEN 'Gatekeeping Review'
      WHEN count(*) = 1 THEN 'Quality Criteria Review 1'
      WHEN count(*) = 2 THEN 'Quality Criteria Review 2'
      WHEN count(*) = 3 THEN 'Quality Criteria Review 3'
      END AS state
    FROM eck_feedback f3
    WHERE
      f3.created > IFNULL((
                            SELECT
                              max(h4.stamp)
                            FROM workbench_moderation_node_history h4
                            WHERE h4.nid = n1.nid
                            AND h4.from_state = 'draft'
                            AND h4.state = 'needs_review'
                            AND h4.stamp > (
                              SELECT
                                max(h5.stamp)
                              FROM workbench_moderation_node_history h5
                              WHERE h5.state = 'rejected' AND h5.nid = n1.nid
                            )), 0)
      AND f3.completed = 1
      AND f3.node_id = n1.nid)
  END", 'state');
  $query->condition('n1.type', 'resource');
  $query->condition('h1.state', array('draft'), 'NOT IN');
  $query->condition('h1.current', 1);
  if ($uid) {
    $query->condition('n1.uid', $uid);
  }
  if ($nid) {
    $query->condition('n1.nid', $nid);
  }
  $query->groupBy('n1.nid');
  if ($order && $order == 'state') {
    $query->orderBy('state', $order_direction);
  }
  else {
    $query->orderBy('n1.created', $order_direction);
  }
  if ($limit && $limit != -1) {
    $query->range(0, $limit);
  }
  if ($from_date && $to_date) {
    $query->where("DATE_FORMAT((DATE_ADD('19700101', INTERVAL n1.created SECOND) + INTERVAL -28800 SECOND), '%Y%m%d') BETWEEN :from_date AND :to_date", array(':from_date' => $from_date, ':to_date' => $to_date));
  }
//  dpq($query);
  return $query->execute();
}

/**
 * Resource Review Links.
 *
 * @param $fields
 * @return array
 */
function _sbac_resource_resource_review_links($fields, $row) {
  global $user;
  $variables = array('status_icons' => array(
    array('image' => 'grey.png',
      'hover' => 'Needs Review',
    ),
    array('image' => 'grey-2.png',
      'hover' => 'Needs Review',
    ),
    array('image' => 'grey-2.png',
      'hover' => 'Needs Review',
    ),
  ));
  $nid = $fields['nid']->raw;
  $feedback = $row->_field_data['nid']['entity']->feedback_status;
  $positionals = array('1st', '2nd', '3rd');
  if ($feedback->qc_count == 3) {
    $variables['status_icons'][3] =  array('image' => 'grey-2.png', 'hover' => 'Needs Review');
  }

  if (!$feedback->gatekeeper_started) {
    // Needs gatekeeper review.
    $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'gate_keeper', $fields['title']);
    $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
    $variables['links'][] = _sbac_resource_start_review_link($nid, 'gate_keeper', $fields['title'], 'link');
    $variables['text'] = t('Needs Gatekeeping Review');
  } elseif ($feedback->gatekeeper_started && !$feedback->gatekeeper_finished) {
    // Gatekeeper review in process.
    $url = url('node/' . $nid, array('absolute' => TRUE, 'fragment' => 'review-gk', 'query' => array('destination' => arg(0))));
    $variables['buttons'][] = l('Continue', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
    $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
    $variables['links'][] = l('Continue', $url, array('attributes' => array('query' => array('destination' => arg(0)))));
    $variables['text'] = t('Gatekeeping Review In Process');
    $variables['status_icons'][0] =  array('image' => 'yellow-pencil.png', 'hover' => 'In Gatekeeping Review');
  } elseif ($feedback->gatekeeper_finished) {
    $user_reviewing = FALSE;
    $variables['status_icons'][0] =  array('image' => 'green-g.png', 'hover' => 'Gatekeeping Passed');
    for ($x = 0; $x < $feedback->qc_count; $x++) {
      // Iterate through the QC reviews.
      if ($feedback->qc_status[$x]['uid'] == $user->uid) {
        $user_reviewing = TRUE;
      }
      if ($feedback->qc_status[$x]['started'] && !$feedback->qc_status[$x]['finished']) {
        // QC review is in process.
        $variables['status_icons'][$x+1] =  array('image' => 'yellow-pencil-2.png', 'hover' => 'In Quality Review');
      } elseif ($feedback->qc_status[$x]['finished']) {
        // QC review is finished.
        $y = $x + 1;
        // If all of the reviews are finished, and the current user is a resource publisher...
        if ($feedback->qc_count == $feedback->qc_num_finished && in_array('resource publisher', $user->roles)) {
          // Show the approval status by showing the green check or red x and set the hover accordingly.
          if ($feedback->qc_status[$x]['approved']) {
            $variables['status_icons'][$y] =  array('image' => 'green-check.png', 'hover' => 'Quality Review ' . $y . ' Passed');
          } else {
            $variables['status_icons'][$y] =  array('image' => 'red-x.png', 'hover' => 'Quality Review ' . $y . ' Failed');
          }
        // Otherwise we just want to stick with green checks and complete messages so reviewers don't know how others reviewed it.
        } else {
          $variables['status_icons'][$y] =  array('image' => 'green-check.png', 'hover' => 'Quality Review ' . $y . ' Complete');
        }
      }
    }
    if ($feedback->qc_count > $feedback->qc_num_finished) {
      if (!$user_reviewing) {
        // QC reviews aren't full yet.
        $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'qc', $fields['title']);
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = _sbac_resource_start_review_link($nid, 'qc', $fields['title'], 'link');
        $variables['text'] = t('Needs @pos Quality Review', array('@pos' => $positionals[$feedback->qc_num_finished + 1]));
      } else {
        $url = url('node/' . $nid, array('absolute' => TRUE, 'fragment' => 'review-qc'));
        $variables['buttons'][] = l('Continue', $url, array('attributes' => array('class' => array('medium', 'button'))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
        $variables['links'][] = l('Continue Review', $url);
        $variables['text'] = t('@pos Quality Review In Process', array('@pos' => $positionals[$x]));
      }
    }
  }
  if ($feedback->qc_count == $feedback->qc_num_finished) {
    // All the QC reviews are done, so on to Post review.
    if (!$feedback->post_started) {
      $variables['buttons'][] = _sbac_resource_start_review_link($nid, 'post', $fields['title']);
      $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
      $variables['links'][] = _sbac_resource_start_review_link($nid, 'post', $fields['title'], 'link');
      // If this was a resubmitted resource, change the wording.
      if ($feedback->post_resubmission) {
        $variables['text'] = t('Resubmitted Arbitration');
      } else {
        $variables['text'] = t('Needs Arbitration');
      }
    } elseif ($feedback->post_started && !$feedback->post_finished) {
      $url = url('node/' . $nid, array('absolute' => TRUE, 'fragment' => 'review-post', 'query' => array('destination' => arg(0))));
      $variables['buttons'][] = l('Continue', $url, array('attributes' => array('class' => array('medium', 'button'), 'query' => array('destination' => arg(0)))));
      $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE, 'query' => array('destination' => arg(0))));
      $variables['links'][] = l('Continue Review', $url, array('attributes' => array('query' => array('destination' => arg(0)))));
      $variables['text'] = t('Arbitration In Process');
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

  $variables['rating'] = sbac_resource_display_fivestar_rating(sbac_resource_get_rating_average($fields['nid']->raw));
  $variables['rating_count'] = sbac_resource_get_rating_count($fields['nid']->raw);

  return $variables;
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
 * @param $nid
 * @param $type
 * @param $title
 * @param string $style
 * @return string
 * @internal param $node
 */
function _sbac_resource_start_review_link($nid, $type, $title, $style = 'button') {
  // Add node title to button for behat tests
  $title = strtolower(str_replace(' ', '-', $title->raw));

  $link_text = t('Start Review');

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

  if ($style == 'button') {
    $content = l($link_text, 'node/' . $nid . '/feedback/' . $stub . '/start/' . $trigger_id, array(
        'attributes' => array(
          'class' => array(
            'use-ajax',
            'use-dialog',
            'medium',
            'button',
            $title,
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
    'subject' => t('Subjects'),
    'grades' => t('Grades'),
    'attributes' => t('Attributes of the Formative Assessment Process'),
    'digital_media_type' => t('Media Types'),
    'focus' => t('Resource Type'),
    'intended_end_user' => t('Intended End Users'),
    'intended_student_populations' => t('Intended Student Populations'),
    'educational_use' => t('Educational Use'),
    'smarter_balanced_keyword' => t('Module Type'),
    'education_alignment' => t('Common Core State Standards'),
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

  if (!empty($view_filters)) {
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
