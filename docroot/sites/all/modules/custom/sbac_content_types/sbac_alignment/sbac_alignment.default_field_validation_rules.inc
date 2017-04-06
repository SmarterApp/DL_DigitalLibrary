<?php
/**
 * @file
 * sbac_alignment.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function sbac_alignment_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'Unique Alignment Key';
  $rule->name = 'unique_alignment_key';
  $rule->field_name = 'field_alignment_key';
  $rule->col = 'value';
  $rule->entity_type = 'taxonomy_term';
  $rule->bundle = 'education_alignment';
  $rule->validator = 'field_validation_unique_validator';
  $rule->settings = array(
    'data' => 'global',
    'per_user' => 0,
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      25 => 0,
      24 => 0,
      15 => 0,
      17 => 0,
      16 => 0,
      11 => 0,
      13 => 0,
      7 => 0,
      22 => 0,
      8 => 0,
      23 => 0,
      26 => 0,
      31 => 0,
      36 => 0,
    ),
    'errors' => 0,
    'condition' => 0,
    'condition_wrapper' => array(
      'condition_field' => '',
      'condition_operator' => 'equals',
      'condition_value' => '',
    ),
  );
  $rule->error_message = 'Alignment Key "[value]" already exists. This field must be unique.';
  $export['unique_alignment_key'] = $rule;

  return $export;
}
