<?php

/*----------------------------------------------------------------------------
      CALLBACKS
----------------------------------------------------------------------------*/

/**
 * Callback for admin/sbac and other generic 'landing' pages
 */
function sbac_core_index_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  return theme('node_add_list', array('content' => $content));
}

/**
 * Returns the list of options in State vocabulary.
 * @return [type] [description]
 */
function sbac_state_options() {
  $options = array(
    '[any]' => t('any'),
  );

  $vid = db_query("SELECT vid FROM taxonomy_vocabulary WHERE machine_name = 'states'")->fetchField();
  if ($vid) {
    $result = db_query("SELECT name, tid FROM taxonomy_term_data WHERE vid = :vid ORDER BY weight ASC", array(
      ':vid' => $vid,
    ));

    foreach ($result as $row) {
      $options[$row->tid] = $row->name;
    }
  } 

  return $options;
}