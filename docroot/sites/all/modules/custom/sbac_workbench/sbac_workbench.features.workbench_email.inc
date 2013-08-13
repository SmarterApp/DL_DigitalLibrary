<?php
/**
 * @file
 * sbac_workbench.features.workbench_email.inc
 */

/**
 * Implements hook_workbench_email_export().
 */
function sbac_workbench_workbench_email_export() {
  $items = array(
    'approved:needs_review:resource contributor' => array(
      'from_name' => 'approved',
      'to_name' => 'needs_review',
      'role' => 'resource contributor',
    ),
    'approved:needs_review:resource reviewer' => array(
      'from_name' => 'approved',
      'to_name' => 'needs_review',
      'role' => 'resource reviewer',
    ),
    'needs_review:draft:resource contributor' => array(
      'from_name' => 'needs_review',
      'to_name' => 'draft',
      'role' => 'resource contributor',
    ),
  );
  return $items;
}
