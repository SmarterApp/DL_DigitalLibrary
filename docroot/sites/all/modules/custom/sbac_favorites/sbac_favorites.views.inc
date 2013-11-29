<?php

/**
 * Implements hook_views_data().
 *
 * @return mixed
 */
function sbac_favorites_views_data() {
  $data['sbac_favorites']['table']['group'] = t('SBAC Favorites');
  // Base table.
  $data['sbac_favorites']['table']['base'] = array(
    'field' => 'nid', // This is the identifier field for the view.
    'title' => t('SBAC Favorites'),
    'help' => t('Custom data for user favorites.'),
    'weight' => -10,
  );
  // Join.
  $data['sbac_favorites']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );


  // Node ID table field.
  $data['sbac_favorites']['nid'] = array(
    'title' => t('Resource NID'),
    'help' => t('The resource nid.'),
    'relationship' => array(
      'base' => 'node', // The name of the table to join with.
      'base field' => 'nid', // The name of the field on the joined table.
      'handler' => 'views_handler_relationship',
      'label' => t('Default label for the relationship'),
      'title' => t('Title shown when adding the relationship'),
      'help' => t('More information on this relationship'),
    ),
  );

  // User ID field.
  $data['sbac_favorites']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('User ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Weight fields
  $data['sbac_favorites']['weight'] = array(
    'title' => t('Weight'),
    'help' => t('Weight'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
