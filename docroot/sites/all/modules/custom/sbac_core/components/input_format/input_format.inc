<?php

/**
 * Process callback for form elements that have a text format selector attached.
 */
function input_format_force_full_html($element) {
  // restrict this code to certain pages
    $pages = array(
      'admin/sbac',
      'system/ajax',
    );

    if (!match_uri($pages)) {
      return $element;
    }

  // force full_html input format & get rid of the selector
    $text_format = 'full_html';

    $element['format']['format']['#access'] = FALSE;
    $element['format']['guidelines']['#access'] = FALSE;
    $element['format']['help']['#access'] = FALSE;
    $format = $element['format']['format']['#options'][$text_format];
    $element['format']['format']['#options'] = array();
    $element['format']['format']['#options'][$text_format] = $format;
    $element['format']['format']['#default_value'] = current(array_keys($element['format']['format']['#options']));
    
    // nuke the guidelines element portion to remove giant space gap
    unset($element['format']['guidelines']);
    unset($element['format']['help']);

    $element['format']['#attributes']['class'][] = 'no-format-selector';

    drupal_add_css(drupal_get_path('module', 'sbac_core') . '/components/input_format/css/input_format.css');

  return $element;
}
