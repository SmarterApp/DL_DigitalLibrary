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