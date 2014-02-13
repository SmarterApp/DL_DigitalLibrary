<?php


function sbac_forum_main_landing_page() {
  drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
  $output = '';

  $output = 'Forum contents';

  return $output;
}
