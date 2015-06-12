<?php
/**
 * @file
 * sbac_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_user_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_user_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function sbac_user_image_default_styles() {
  $styles = array();

  // Exported image style: profile_image.
  $styles['profile_image'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 180,
          'height' => 230,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'profile_image',
  );

  // Exported image style: small.
  $styles['small'] = array(
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 25,
          'height' => 25,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'small',
  );

  return $styles;
}
