<?php
/**
 * @file
 * Views related code for the SBAC alignment feature.
 */

/**
 * Implements hook_views_query_alter().
 *
 * @param $view
 * @param $query
 */
function sbac_alignment_views_query_alter(&$view, &$query) {
  if ($view->name == 'alignment') {
    sbac_alignment_alignment_views_query_alter($view, $query);
  }
}

/**
 * Adds the extra delete param to the join to ensure
 * we get back permanent and temp ccss objects.
 *
 * @param $view
 * @param $query
 */
function sbac_alignment_alignment_views_query_alter(&$view, &$query) {
  $query->table_queue['field_data_field_resource_reference']['join']->extra[1]['value'] = array(0, 1);
}