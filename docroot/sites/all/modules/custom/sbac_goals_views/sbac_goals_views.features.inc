<?php
/**
 * @file
 * sbac_goals_views.features.inc
 */

/**
 * Implements hook_views_api().
 */
function sbac_goals_views_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function sbac_goals_views_image_default_styles() {
  $styles = array();

  // Exported image style: leaderboard_30x33.
  $styles['leaderboard_30x33'] = array(
    'label' => 'leaderboard_30x33',
    'effects' => array(
      7 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 30,
          'height' => 33,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
