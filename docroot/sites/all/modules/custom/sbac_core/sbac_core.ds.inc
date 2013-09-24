<?php
/**
 * @file
 * sbac_core.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function sbac_core_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|resource|secondary_teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'resource';
  $ds_fieldsetting->view_mode = 'secondary_teaser';
  $ds_fieldsetting->settings = array(
    'resource_slideshow' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'resource_slideshow',
    ),
  );
  $export['node|resource|secondary_teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'review|end_use|default';
  $ds_fieldsetting->entity_type = 'review';
  $ds_fieldsetting->bundle = 'end_use';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'review_author' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'review_author',
    ),
  );
  $export['review|end_use|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'user|user|tooltip';
  $ds_fieldsetting->entity_type = 'user';
  $ds_fieldsetting->bundle = 'user';
  $ds_fieldsetting->view_mode = 'tooltip';
  $ds_fieldsetting->settings = array(
    'ds_user_picture' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_picture_small',
    ),
  );
  $export['user|user|tooltip'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function sbac_core_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resource|secondary_teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resource';
  $ds_layout->view_mode = 'secondary_teaser';
  $ds_layout->layout = 'ds_3col_stacked_equal_width';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'resource_slideshow',
      ),
      'left' => array(
        1 => 'field_intended_end_user',
        2 => 'field_subject',
        3 => 'field_grades',
        4 => 'field_alignment_term',
      ),
      'middle' => array(
        5 => 'field_digital_media_type',
        6 => 'field_smarter_balanced_keyword',
        7 => 'field_intended_student',
        8 => 'field_classroom_technologies',
      ),
      'right' => array(
        9 => 'field_alignment_tags',
        10 => 'field_educational_use',
        11 => 'field_geographical_settings',
      ),
    ),
    'fields' => array(
      'resource_slideshow' => 'header',
      'field_intended_end_user' => 'left',
      'field_subject' => 'left',
      'field_grades' => 'left',
      'field_alignment_term' => 'left',
      'field_digital_media_type' => 'middle',
      'field_smarter_balanced_keyword' => 'middle',
      'field_intended_student' => 'middle',
      'field_classroom_technologies' => 'middle',
      'field_alignment_tags' => 'right',
      'field_educational_use' => 'right',
      'field_geographical_settings' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'middle' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['node|resource|secondary_teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'review|end_use|default';
  $ds_layout->entity_type = 'review';
  $ds_layout->bundle = 'end_use';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_3col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'review_author',
      ),
      'left' => array(
        1 => 'field_student_learning',
      ),
      'middle' => array(
        2 => 'field_pro_dev',
      ),
      'right' => array(
        3 => 'field_ease_use',
      ),
      'footer' => array(
        4 => 'field_appropriate_for',
        5 => 'title',
        6 => 'field_details',
      ),
    ),
    'fields' => array(
      'review_author' => 'header',
      'field_student_learning' => 'left',
      'field_pro_dev' => 'middle',
      'field_ease_use' => 'right',
      'field_appropriate_for' => 'footer',
      'title' => 'footer',
      'field_details' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'middle' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['review|end_use|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|tooltip';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'tooltip';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'ds_user_picture',
      ),
      'right' => array(
        1 => 'field_first_name',
        2 => 'field_position',
        3 => 'field_state',
        4 => 'field_school_name',
        5 => 'field_district_name',
      ),
      'footer' => array(
        6 => 'field_grade_level_s_',
        7 => 'field_subject_s_',
        8 => 'field_special_populations',
      ),
    ),
    'fields' => array(
      'ds_user_picture' => 'left',
      'field_first_name' => 'right',
      'field_position' => 'right',
      'field_state' => 'right',
      'field_school_name' => 'right',
      'field_district_name' => 'right',
      'field_grade_level_s_' => 'footer',
      'field_subject_s_' => 'footer',
      'field_special_populations' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['user|user|tooltip'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function sbac_core_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'secondary_teaser';
  $ds_view_mode->label = 'Secondary Teaser';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['secondary_teaser'] = $ds_view_mode;

  return $export;
}
