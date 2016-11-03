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
    'field' => 'id', // This is the identifier field for the view.
    'title' => t('SBAC Favorites'),
    'help' => t('Custom data for user favorites.'),
    'weight' => -10,
  );
  // Join.
  $data['sbac_favorites']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );


  // Entity ID table field.
  $data['sbac_favorites']['id'] = array(
    'title' => t('Entity ID'),
    'help' => t('The entity id.'),
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
