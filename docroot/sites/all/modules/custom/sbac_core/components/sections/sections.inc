<?php

/**
 * Template preprocessing function for Sections theme invocation.
 * @param  [type] $vars [description]
 * @return [type]       [description]
 */
function sections_preprocess(&$vars) {
  $path = drupal_get_path('module', 'sbac_core') . '/components/sections/';

  drupal_add_js($path . 'js/sections.js');
  drupal_add_css($path . 'css/sections.css');

  foreach ($vars['sections'] as $key => &$section) {
    // remove properties
    if ($key{0} == '#') {
      unset($vars['sections'][$key]);
      continue;
    }

    $class = '';
    $class .= 'section-' . strtolower(str_replace(' ', '-', $section['title']));
    if (isset($section['class'])) {
      $class = $section['class'];
    }

    if (isset($section['disabled']) && $section['disabled']) {
      $class .= ' disabled';
    }

    $section['class'] = $class;
  }
}