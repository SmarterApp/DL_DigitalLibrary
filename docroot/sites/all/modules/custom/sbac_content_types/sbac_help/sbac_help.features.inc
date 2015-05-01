<?php
/**
 * @file
 * sbac_help.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_help_ctools_plugin_api($module = NULL, $api = NULL) {
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
function sbac_help_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function sbac_help_flag_default_flags() {
  $flags = array();
  // Exported flag: "Welcome Help Topic".
  $flags['welcome_help_topic'] = array(
    'entity_type' => 'node',
    'title' => 'Welcome Help Topic',
    'global' => 0,
    'types' => array(
      0 => 'help_page',
    ),
    'flag_short' => 'Display on Landing Page',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Remove from Landing Page',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'diff_standard' => 0,
      'print' => 0,
      'token' => 0,
      'node_term_user' => 0,
      'secondary_teaser' => 0,
      'revision' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 1,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'sbac_help',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_image_default_styles().
 */
function sbac_help_image_default_styles() {
  $styles = array();

  // Exported image style: help_icon.
  $styles['help_icon'] = array(
    'name' => 'help_icon',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 160,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'help_icon',
  );

  // Exported image style: help_topics_modal_image.
  $styles['help_topics_modal_image'] = array(
    'name' => 'help_topics_modal_image',
    'label' => 'Help Topics Modal Image',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 260,
          'height' => 138,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: landing_page_help_topic.
  $styles['landing_page_help_topic'] = array(
    'name' => 'landing_page_help_topic',
    'label' => 'Landing Page Help Topic',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 120,
          'height' => 64,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: welcome_tutorial.
  $styles['welcome_tutorial'] = array(
    'name' => 'welcome_tutorial',
    'label' => 'welcome_tutorial',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function sbac_help_node_info() {
  $items = array(
    'help_page' => array(
      'name' => t('Help Page'),
      'base' => 'node_content',
      'description' => t('Creates help pages that get listed on the help modal.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
