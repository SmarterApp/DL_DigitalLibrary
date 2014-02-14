<?php


function sbac_forum_main_landing_page() {
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  $output = '';
  $current_filters = '';

  // Get correct set of category filters based on subnav.
  if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
    $current_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
  }

  $active_tab = sbac_forum__api__get_active_subnav();
  if (empty($active_tab)) {
    sbac_forum__api__set_active_subnav(SBAC_FORUM_SUBNAV_ALL);
  }
  module_load_include('inc', 'sbac_forum', 'includes/sbac_forum.forms');
  $subnav = drupal_get_form('sbac_forum_sub_nav_form');
  $output .= drupal_render($subnav);


  if (!empty($current_filters)) {
    $output = 'THERE ARE FILTERS!! ';
  }


  $output .= '<div class="sbac-forum-main-container">';
  $output .= 'Forum contents';
  $output .= '</div>';

  return $output;
}
