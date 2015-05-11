<?php
/**
 * @file
 * sbac_user.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function sbac_user_user_default_roles() {
  $roles = array();

  // Exported role: DLRB member.
  $roles['DLRB member'] = array(
    'name' => 'DLRB member',
    'weight' => 9,
  );

  // Exported role: advanced end user.
  $roles['advanced end user'] = array(
    'name' => 'advanced end user',
    'weight' => 3,
  );

  // Exported role: basic end user.
  $roles['basic end user'] = array(
    'name' => 'basic end user',
    'weight' => 2,
  );

  // Exported role: digital library administrator.
  $roles['digital library administrator'] = array(
    'name' => 'digital library administrator',
    'weight' => 11,
  );

  // Exported role: facilitator.
  $roles['facilitator'] = array(
    'name' => 'facilitator',
    'weight' => 7,
  );

  // Exported role: guest.
  $roles['guest'] = array(
    'name' => 'guest',
    'weight' => 15,
  );

  // Exported role: help desk.
  $roles['help desk'] = array(
    'name' => 'help desk',
    'weight' => 10,
  );

  // Exported role: moderator.
  $roles['moderator'] = array(
    'name' => 'moderator',
    'weight' => 8,
  );

  // Exported role: on-boarding.
  $roles['on-boarding'] = array(
    'name' => 'on-boarding',
    'weight' => 14,
  );

  // Exported role: reports administrator.
  $roles['reports administrator'] = array(
    'name' => 'reports administrator',
    'weight' => 16,
  );

  // Exported role: resource contributor.
  $roles['resource contributor'] = array(
    'name' => 'resource contributor',
    'weight' => 4,
  );

  // Exported role: resource publisher.
  $roles['resource publisher'] = array(
    'name' => 'resource publisher',
    'weight' => 6,
  );

  // Exported role: resource reviewer.
  $roles['resource reviewer'] = array(
    'name' => 'resource reviewer',
    'weight' => 5,
  );

  // Exported role: system administrator.
  $roles['system administrator'] = array(
    'name' => 'system administrator',
    'weight' => 12,
  );

  return $roles;
}
