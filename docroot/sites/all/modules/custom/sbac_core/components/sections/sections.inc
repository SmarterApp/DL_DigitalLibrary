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

function section_get_content() {
  $output = array();
  $content = null;
  if (!isset($_GET['source']) || !isset($_GET['tab']) || !isset($_GET['nid'])) {
    $output['response'] = null;
  }

  $node = node_load($_GET['nid']);
  module_load_include('inc', 'sbac_core', '/components/sections/includes/class.Factory');
  $factory = new \sbac_core\components\sections\Factory($node);
  $source = $_GET['source'];
  $tab = $_GET['tab'];
  $section = $factory->get($source, $tab);
  if ($section && $section->access()) {
    $content = $section->getContent();
  }

  if ($content) {
    $output['response'] = $content;
  }
  else {
    $output['response'] = null;
  }
  print drupal_json_encode($output);
  exit;
}