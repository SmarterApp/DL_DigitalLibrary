<?php


function sbac_forum_main_landing_page() {
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  $output = '';
  $current_filters = '';
  if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
    $current_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
  }

  if (!empty($current_filters)) {
    $output = 'THERE ARE FILTERS!! ';
  }

  $output .= 'Forum contents';

  return $output;
}
