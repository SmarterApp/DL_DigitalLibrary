<?php
/**
 * @file
 * sbac_workbench.features.workbench_moderation_states.inc
 */

/**
 * Implements hook_workbench_moderation_export_states().
 */
function sbac_workbench_workbench_moderation_export_states() {
  $items = array(
    'approved' => array(
      'name' => 'approved',
      'label' => 'Approved',
      'description' => 'Ready for publishing',
      'weight' => -5,
    ),
    'being_reviewed' => array(
      'name' => 'being_reviewed',
      'label' => 'Being Reviewed',
      'description' => 'Resource is under review',
      'weight' => -7,
    ),
    'creation' => array(
      'name' => 'creation',
      'label' => 'Creation',
      'description' => 'Initial creation',
      'weight' => -10,
    ),
    'draft' => array(
      'name' => 'draft',
      'label' => 'Draft',
      'description' => 'Work in progress',
      'weight' => -9,
    ),
    'needs_review' => array(
      'name' => 'needs_review',
      'label' => 'Needs Review',
      'description' => 'Ready for moderation',
      'weight' => -8,
    ),
    'published' => array(
      'name' => 'published',
      'label' => 'Published',
      'description' => 'Make this version live',
      'weight' => -4,
    ),
    'rejected' => array(
      'name' => 'rejected',
      'label' => 'Rejected',
      'description' => 'Did not pass reviewer',
      'weight' => -6,
    ),
    'removed' => array(
      'name' => 'removed',
      'label' => 'Removed',
      'description' => 'Removes the resource.',
      'weight' => 0,
    ),
  );
  return $items;
}
