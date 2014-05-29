<?php

// Used for implementing Features overrides via component alter hooks.

/**
 * Implements hook_field_default_field_bases_alter
 *   - provided by features component alter
 */
function sbac_forum_field_default_field_bases_alter(&$field_bases) {
  if (isset($field_bases['field_forum_access_role_list'])) {
    $field_bases['field_forum_access_role_list']['settings']['allowed_values'] = array();
    $field_bases['field_forum_access_role_list']['settings']['allowed_values_function'] = '_sbac_forum_field_forum_access_role_list_get_roles';
  }
}

/**
 * Helper function that gets list of roles and sets them as the allowed values
 *
 * @return Array List of roles that can be selected.
 */
function _sbac_forum_field_forum_access_role_list_get_roles() {
  // For now use the default function. Can filter this list further if requirements change.
  $items = user_roles(TRUE);
  // Does not filter by roles, should have used Title Vocabulary.
//  $vocab = taxonomy_vocabulary_machine_name_load('title');
//  $tree = taxonomy_get_tree($vocab->vid);
//  $items = array();
//  foreach ($tree as $term) {
//    $items[$term->tid] = $term->name;
//  }
  return $items;
}
