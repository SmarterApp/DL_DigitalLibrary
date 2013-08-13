<?php
/**
 * Implementation of hook_theme()
 *
 */
function sbac_alignment_theme($existing, $type, $theme, $path) {
  $items = array();

  $items['alignment_tags'] = array(
    'path' => drupal_get_path('module', 'sbac_alignment') . '/templates',
    'template' => 'alignment-tags',
    'variables' => array(
      'terms' => NULL,
      'level_title' => NULL,
    ),
  );
  $items['alignment_breadcrumbs'] = array(
    'path' => drupal_get_path('module', 'sbac_alignment') . '/templates',
    'template' => 'alignment-breadcrumbs',
    'variables' => array(
      'terms' => NULL,
    ),
  );
  $items['alignment_checkbox'] = array(
    'path' => drupal_get_path('module', 'sbac_alignment') . '/templates',
    'template' => 'alignment-checkbox',
    'variables' => array(
      'element' => NULL,
    ),
  );

  return $items;
}
