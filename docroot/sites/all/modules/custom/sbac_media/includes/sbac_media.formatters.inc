<?php

/**
 * @file sbac_media/includes/sbac_media.formatters.inc
 *
 * Formatters.
 */

/**
 * Implements hook_file_formatter_info().
 */
function sbac_media_file_formatter_info() {
  $formatters['sbac_media_schooltube'] = array(
    'label' => t('SchoolTube Video'),
    'file types' => array('video'),
    'default settings' => array(
      'width' => 500,
      'height' => 375,
    ),
    'view callback' => 'sbac_media_file_formatter_schooltube_video_view',
    'settings callback' => 'sbac_media_file_formatter_schooltube_video_settings',
  );

  $formatters['sbac_media_teachertube'] = array(
    'label' => t('TeacherTube Video'),
    'file types' => array('video'),
    'default settings' => array(
      'width' => 560,
      'height' => 315,
    ),
    'view callback' => 'sbac_media_file_formatter_teachertube_video_view',
    'settings callback' => 'sbac_media_file_formatter_teachertube_video_settings',
  );

  $formatters['sbac_media_slideshare'] = array(
    'label' => t('SlideShare Presentation'),
    'file types' => array('video'),
    'default settings' => array(
      'width' => 427,
      'height' => 356,
    ),
    'view callback' => 'sbac_media_file_formatter_slideshare_video_view',
    'settings callback' => 'sbac_media_file_formatter_slideshare_video_settings',
  );  

  $formatters['sbac_media_image'] = array(
    'label' => t('SBAC Media Preview Image'),
    'file types' => array('video'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'sbac_media_file_formatter_image_view',
    'settings callback' => 'sbac_media_file_formatter_image_settings',
  );

  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function sbac_media_file_formatter_schooltube_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'schooltube' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'sbac_media_schooltube_video',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height') as $setting) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function sbac_media_file_formatter_teachertube_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'teachertube' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'sbac_media_teachertube_video',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height') as $setting) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function sbac_media_file_formatter_slideshare_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'slideshare' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'sbac_media_slidleshare_presentation',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height') as $setting) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function sbac_media_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'schooltube') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    // @TODO: If autosubmit is removed and we allow view modes that insert
    // images in the WYSIWYG, add file->overrides handling.
    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getOriginalThumbnailPath(),
        '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
        '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
      );
    }

    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function sbac_media_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}

function sbac_media_variable_default() {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'width' => 500,
      'height' => 375,
    );
  }
  return $defaults;
}