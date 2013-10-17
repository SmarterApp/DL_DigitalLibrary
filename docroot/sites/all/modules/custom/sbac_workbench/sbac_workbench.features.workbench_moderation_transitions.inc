<?php
/**
 * @file
 * sbac_workbench.features.workbench_moderation_transitions.inc
 */

/**
 * Implements hook_workbench_moderation_export_transitions().
 */
function sbac_workbench_workbench_moderation_export_transitions() {
  $items = array(
    'approved:needs_review' => array(
      'from_name' => 'approved',
      'to_name' => 'needs_review',
    ),
    'approved:published' => array(
      'from_name' => 'approved',
      'to_name' => 'published',
    ),
    'being_reviewed:approved' => array(
      'from_name' => 'being_reviewed',
      'to_name' => 'approved',
    ),
    'being_reviewed:needs_review' => array(
      'from_name' => 'being_reviewed',
      'to_name' => 'needs_review',
    ),
    'being_reviewed:rejected' => array(
      'from_name' => 'being_reviewed',
      'to_name' => 'rejected',
    ),
    'creation:draft' => array(
      'from_name' => 'creation',
      'to_name' => 'draft',
    ),
    'draft:needs_review' => array(
      'from_name' => 'draft',
      'to_name' => 'needs_review',
    ),
    'needs_review:being_reviewed' => array(
      'from_name' => 'needs_review',
      'to_name' => 'being_reviewed',
    ),
    'published:removed' => array(
      'from_name' => 'published',
      'to_name' => 'removed',
    ),
    'rejected:needs_review' => array(
      'from_name' => 'rejected',
      'to_name' => 'needs_review',
    ),
  );
  return $items;
}
