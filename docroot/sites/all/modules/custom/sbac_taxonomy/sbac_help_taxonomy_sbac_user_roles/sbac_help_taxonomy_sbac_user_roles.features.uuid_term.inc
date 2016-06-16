<?php
/**
 * @file
 * sbac_help_taxonomy_sbac_user_roles.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_help_taxonomy_sbac_user_roles_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'All User Roles',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '01e036e3-fcaf-4eac-b37e-0d7762a871f4',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'digital library administrator',
    'description' => 8,
    'format' => NULL,
    'weight' => 12,
    'uuid' => '111d56ce-6338-4f60-9a87-dc9038a55a10',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'basic end user',
    'description' => 25,
    'format' => NULL,
    'weight' => 3,
    'uuid' => '2f6a2903-4be1-454c-9d1f-3ae43b8a0f24',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'resource contributor',
    'description' => 15,
    'format' => NULL,
    'weight' => 5,
    'uuid' => '3b2f2bd7-ec80-4cb0-b5c6-d0f065ee66e8',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'facilitator',
    'description' => 11,
    'format' => NULL,
    'weight' => 8,
    'uuid' => '5adf9273-f342-411f-9843-9e3a517d6f58',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'authenticated user',
    'description' => 2,
    'format' => NULL,
    'weight' => 2,
    'uuid' => '5ccfc000-2681-43d0-8852-f52bac9b8294',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'system administrator',
    'description' => 23,
    'format' => NULL,
    'weight' => 13,
    'uuid' => '6dc3ef3e-05e4-45d5-a81a-7244ca429abd',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'resource publisher',
    'description' => 16,
    'format' => NULL,
    'weight' => 7,
    'uuid' => '8645a211-36ac-46b2-a654-96586c72a46c',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'moderator',
    'description' => 13,
    'format' => NULL,
    'weight' => 9,
    'uuid' => '8ccaf7d5-d38c-4dbf-929a-f46556feb012',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'resource reviewer',
    'description' => 17,
    'format' => NULL,
    'weight' => 6,
    'uuid' => '98fd05ca-f9dd-48a0-acfa-304f6dbc61a5',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'DLRB member',
    'description' => 7,
    'format' => NULL,
    'weight' => 10,
    'uuid' => '9b6b3ac5-8b97-4dbb-82ab-9e84fe2f1d86',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'advanced end user',
    'description' => 24,
    'format' => NULL,
    'weight' => 4,
    'uuid' => 'ab332efa-6d09-4078-80b4-38388301160a',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'help desk',
    'description' => 22,
    'format' => NULL,
    'weight' => 11,
    'uuid' => 'b4f3345e-ef56-44bd-aa7a-2ecc951d868b',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'guest',
    'description' => 31,
    'format' => NULL,
    'weight' => 16,
    'uuid' => 'c0ca73f9-aec4-4c4e-bd13-363b1799e567',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'on-boarding',
    'description' => 26,
    'format' => NULL,
    'weight' => 15,
    'uuid' => 'd086f38a-0098-42be-a1c5-cf2acb1084e7',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'anonymous user',
    'description' => 1,
    'format' => NULL,
    'weight' => 1,
    'uuid' => 'ddd1cc17-e534-493a-a9be-62685de52da0',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  $terms[] = array(
    'name' => 'administrator',
    'description' => 3,
    'format' => NULL,
    'weight' => 3,
    'uuid' => 'e4220710-1526-46f8-ac87-410d2a4c38fd',
    'vocabulary_machine_name' => 'sbac_user_roles',
  );
  return $terms;
}
