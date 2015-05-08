<?php

/**
 * Preprocess function for theme('sbac_media_schooltube_video').
 */
function sbac_media_preprocess_media_schooltube_video(&$variables) {

  // Build the URI.
  $wrapper = file_stream_wrapper_get_instance_by_uri($variables['uri']);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = check_plain($parts['v']);

  // Make the file object available.
  $file_object = file_uri_to_object($variables['uri']);

  // Add some options as their own template variables.
  foreach (array('width', 'height') as $theme_var) {
    $variables[$theme_var] = $variables['options'][$theme_var];
  }

  // Do something useful with the overridden attributes from the file
  // object. We ignore alt and style for now.
  if (isset($variables['options']['attributes']['class'])) {
    if (is_array($variables['options']['attributes']['class'])) {
      $variables['classes_array'] = array_merge($variables['classes_array'], $variables['options']['attributes']['class']);
    }
  }

  // Add template variables for accessibility.
  $variables['title'] = check_plain($file_object->filename);
  // @TODO: Find an easy/ not too expensive way to get the YouTube description
  // to use for the alternative content.
  $variables['alternative_content'] = t('Video of @title', array('@title' => $variables['title']));

  // Build the iframe URL with options query string.
  // Example: http://www.schooltube.com/embed_force/224405d2718114d93738/
  // $variables['url'] = url($protocol . '//www.' . $url_base . '/embed/' . $variables['video_id'], array('query' => $query, 'external' => TRUE));
  $variables['url'] = url('http://www.schooltube.com/embed_force/' . $variables['video_id'], array('external' => TRUE));  
}

/**
 * NOT IMPLEMENTED: See schooltube function above for example implementation
 * Preprocess function for theme('sbac_media_teachertube_video').
 */
function sbac_media_preprocess_media_teachertube_video(&$variables) {
  $variables = array();
}

/**
 * NOT IMPLEMENTED: See schooltube function above for example implementation
 * Preprocess function for theme('sbac_media_slideshare_video').
 */
function sbac_media_preprocess_media_slideshare_video(&$variables) {
  $variables = array();
}