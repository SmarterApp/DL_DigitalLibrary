<?php

/**
 * Returns the specified text truncated to given length and adds the 
 * "read more" and "read less" functionality.
 * 
 * @param  [type]  $text      [description]
 * @param  integer $length    [description]
 * @param  boolean $show_open [description]
 * @return [type]             [description]
 */
function more_less_text($text, $length = 300, $show_open = FALSE) {
  $text = trim($text);

  if (strlen($text) <= $length) {
    return $text;
  }

  $ellipsis = '';

  // use Views when available
  if (function_exists('views_trim_text')) {
    $alter = array(
      'max_length' => $length,
      'word_boundary' => TRUE,
      'ellipsis' => $ellipsis,
      'html' => TRUE,
    );

    $summary = views_trim_text($alter, $text);
  }
  // otherwise default to the DevTools version
  else {
    $text_format = 'full_html';

    $options = array(
      'ellipsis' => $ellipsis,
      'format' => $text_format,
    );

    // truncate text on word boundary and then fix any broken markup
    $summary = truncate($text, $length, $options);
    $summary = check_markup($summary, $text_format);
  }

  // add "read more" and "read less" links to summary & full text, respectively;
  // con't get an <a href="#"> through l(), so use raw HTML
  $read_more = ' <a href="#" class="more-less-text-trigger-more">' . t('read more') . '</a>';
  $read_less = ' <a href="#" class="more-less-text-trigger-less">' . t('read less') . '</a>';

  $summary = (substr($summary, -4) == '</p>') ? (substr($summary, 0, -4) . $read_more . '</p>') : ($summary . $read_more);
  $text    = (substr($text, -4) == '</p>')    ? (substr($text, 0, -4) . $read_less . '</p>')    : ($text . $read_less);

  $output = theme('more_less_text', array(
    'summary' => $summary,
    'full' => $text,
    'show_open' => $show_open,
  ));

  $path = drupal_get_path('module', 'sbac_core') . '/components/more_less_text';

  drupal_add_js($path . '/js/more_less_text.js');
  drupal_add_css($path . '/css/more_less_text.css');

  return $output;
}