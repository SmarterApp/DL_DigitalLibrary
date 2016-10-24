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
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'flagging_form' => array(
      'weight' => '10',
      'label' => 'hidden',
      'format' => 'flagging_form',
    ),
    'review_author' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'review_author',
    ),
    'review_helpfulness' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'review_helpfulness',
    ),
    'review_vote' => array(
      'weight' => '8',
      'label' => 'hidden',
      'format' => 'review_vote',
    ),
    'review_delete' => array(
      'weight' => '9',
      'label' => 'hidden',
      'format' => 'review_delete',
    ),
  );
  $export['review|end_use|default'] = $ds_fieldsetting;

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
        1 => 'review_helpfulness',
      ),
      'left' => array(
        2 => 'field_student_learning',
      ),
      'middle' => array(
        3 => 'field_pro_dev',
      ),
      'right' => array(
        4 => 'field_ease_use',
      ),
      'footer' => array(
        5 => 'field_appropriate_for',
        6 => 'title',
        7 => 'field_details',
        8 => 'review_vote',
        9 => 'review_delete',
        10 => 'flagging_form',
      ),
    ),
    'fields' => array(
      'review_author' => 'header',
      'review_helpfulness' => 'header',
      'field_student_learning' => 'left',
      'field_pro_dev' => 'middle',
      'field_ease_use' => 'right',
      'field_appropriate_for' => 'footer',
      'title' => 'footer',
      'field_details' => 'footer',
      'review_vote' => 'footer',
      'review_delete' => 'footer',
      'flagging_form' => 'footer',
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
