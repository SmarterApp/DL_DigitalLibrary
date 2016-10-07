<?php

function sbac_collections_theme($existing, $type, $theme, $path) {
  $items = array();
  $items['views_view_fields__collection__list_view'] = array(
    'template' => 'templates/views-view-fields--collection--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_collections_views_view_fields__collection__list_view__preprocess'
    ),
    'path' => drupal_get_path('module', 'sbac_collections')
  );
  $items['views_view__collection__list_view'] = array(
    'template' => 'templates/views-view--collection--list-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_collections_views_view__collection__list_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_collections')
  );

  return $items;
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_collections_views_view__collection__list_view__preprocess(&$vars) {
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
function sbac_collections_views_view_fields__collection__list_view__preprocess(&$vars) {
  global $user;
  $image_assets = _sbac_resource_grid_image($vars['fields'], 'list');
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }

  $variables = _sbac_resource_my_resources_links($vars['fields'], $vars['row']);

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
