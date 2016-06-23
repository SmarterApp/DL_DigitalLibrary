<?php
/**
 * Implementation of hook_theme()
 *
 */
function sbac_alignment_theme($existing, $type, $theme, $path) {
  $items = array();

  $items['alignment_tags'] = array(
    'path' => drupal_get_path('theme', 'SBAC') . '/templates/sbac_alignment',
    'template' => 'alignment-tags',
    'variables' => array(
      'terms' => NULL,
      'level_title' => NULL,
    ),
  );
  $items['alignment_breadcrumbs'] = array(
    'path' => drupal_get_path('theme', 'SBAC') . '/templates/sbac_alignment',
    'template' => 'alignment-breadcrumbs',
    'variables' => array(
      'terms' => NULL,
    ),
  );
  $items['alignment_checkbox'] = array(
    'path' => drupal_get_path('theme', 'SBAC') . '/templates/sbac_alignment',
    'template' => 'alignment-checkbox',
    'variables' => array(
      'element' => NULL,
    ),
  );
  $items['alignment_modal_confirm'] = array(
    'path' => drupal_get_path('theme', 'SBAC') . '/templates/sbac_alignment',
    'template' => 'alignment-modal-confirm',
    'variables' => array(
      'term' => NULL,
    ),
  );

  $items['sbac_alignment_alignment_form'] = array(
    'path' => drupal_get_path('theme', 'SBAC') . '/templates/sbac_alignment',
    'template' => 'alignment-form',
    'render element' => 'form',
  );
  $items['sbac_alignment_filter_alignment_form'] = array(
    'path' => drupal_get_path('theme', 'SBAC') . '/templates/sbac_alignment',
    'template' => 'alignment-form',
    'render element' => 'form',
  );

  $items['views_view_table__alignment__resource_admin_view'] = array(
    'template' => 'templates/sbac_alignment/alignment/resource_admin_view/views-view-table--alignment--resource-admin-view',
    'arguments' => array('variables' => NULL),
    'original hook' => 'views_view_table',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_table',
    ),
    'path' => drupal_get_path('theme', 'SBAC')
  );

  return $items;
}
