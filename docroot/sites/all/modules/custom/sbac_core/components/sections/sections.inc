<?php

/**
 * Template preprocessing function for Sections theme invocation.
 * @param  [type] $vars [description]
 * @return [type]       [description]
 */
function sections_preprocess(&$vars) {
  $path = drupal_get_path('module', 'sbac_core') . '/components/sections/';
  if (strpos($_GET['q'], 'user') !== FALSE || strpos($_GET['q'], 'node') !== FALSE) {
    drupal_add_js($path . 'js/sections.js');
  }
  drupal_add_css($path . 'css/sections.css');

  foreach ($vars['sections'] as $key => &$section) {
    $section['use-ajax'] = 'use-ajax';
    if ((isset($section['title']) && $section['title'] == 'About This Resource') || (isset($section['no-ajax']) && $section['no-ajax'] == TRUE)) {
      $section['use-ajax'] = '';
    }

    if (!isset($section['source'])) {
      $section['source'] = NULL;
    }
    if (!isset($section['tab'])) {
      $section['tab'] = NULL;
    }
    if (!isset($section['nid'])) {
      $section['nid'] = NULL;
    }

    // remove properties
    if ($key{0} == '#') {
      unset($vars['sections'][$key]);
      continue;
    }

    $class = '';
    $class .= 'section-' . strtolower(str_replace(' ', '-', $section['title']));
    if (isset($section['class'])) {
      $class .= ' ' . $section['class'];
    }
    if (isset($section['content']) && $section['content'] != NULL) {
      $class .= ' section-loaded';
    }
    if (isset($section['disabled']) && $section['disabled']) {
      $class .= ' disabled';
    }
    $section['class'] = $class;
    $section['id'] = 'section-' . strtolower(str_replace(' ', '-', $section['title']));
  }
}

/**
 * Returns the sections content via ajax.
 */
function section_get_content() {
  $output = array();
  $content = null;
  if (!isset($_GET['source']) || !isset($_GET['tab']) || !isset($_GET['nid']) || !isset($_GET['section_id'])) {
    print ajax_render($output);
  }

  $source = $_GET['source'];
  $tab = $_GET['tab'];
  $user_uid = $_GET['uid'];
  if ($source == 'people') {
    if ($tab == 'notifications') {
      global $user;
      //$content = views_embed_view('sbac_email_message');
      $content = sbac_core_notifications_get_html_content();

      // taskit_mark_all_read($user);
    }
    elseif ($tab == 'favorites') {
      $content = sbac_favorites_get_html_content();
      $commands = array();
      $commands[] = ajax_command_invoke('#' . $_GET['section_id'], 'empty');
      $commands[] = ajax_command_append('#' . $_GET['section_id'], $content);
      $page = array('#type' => 'ajax', '#commands' => $commands);
      ajax_deliver($page);
      exit();
    }
    elseif ($tab == 'goals') {
      $content = sbac_goals_get_html_content($user_uid);
      $commands = array();
      $commands[] = ajax_command_invoke('#' . $_GET['section_id'], 'empty');
      $commands[] = ajax_command_append('#' . $_GET['section_id'], $content);
      $page = array('#type' => 'ajax', '#commands' => $commands);
      ajax_deliver($page);
      exit();
    }
  }
  else {
    $node = node_load($_GET['nid']);
    module_load_include('inc', 'sbac_core', '/components/sections/includes/class.Factory');
    $factory = new \sbac_core\components\sections\Factory($node);
    $section = $factory->get($source, $tab);
    if ($section && $section->access()) {
      $content = $section->getContent();
    }
  }

  $output[] = ajax_command_invoke('#' . $_GET['section_id'], 'empty');
  $output[] = ajax_command_append('#' . $_GET['section_id'], $content);
  print ajax_render($output);
  exit();
}