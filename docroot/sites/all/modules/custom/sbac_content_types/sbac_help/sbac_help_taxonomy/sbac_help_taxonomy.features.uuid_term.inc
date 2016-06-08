<?php
/**
 * @file
 * sbac_help_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_help_taxonomy_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'authenticated user',
    'description' => 2,
    'format' => NULL,
    'weight' => 2,
    'uuid' => '01be4138-57a6-4fa7-8202-7f680cf0dbe0',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60546,
  );
  $terms[] = array(
    'name' => 'advanced end user',
    'description' => 24,
    'format' => NULL,
    'weight' => 4,
    'uuid' => '1a4aacea-0175-4d97-ad2f-2a5f2347cd17',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60561,
  );
  $terms[] = array(
    'name' => 'resource reviewer',
    'description' => 17,
    'format' => NULL,
    'weight' => 6,
    'uuid' => '30252a3c-6bdb-4cb7-8ac2-beba513ebf18',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60571,
  );
  $terms[] = array(
    'name' => 'Resource Tutorial',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '4877fa29-1bf2-4952-9088-9db3c57c6dea',
    'vocabulary_machine_name' => 'help_page_topic',
  );
  $terms[] = array(
    'name' => 'help desk',
    'description' => 22,
    'format' => NULL,
    'weight' => 11,
    'uuid' => '4ea2ed12-efa8-46a5-8754-9809c903ed3e',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60596,
  );
  $terms[] = array(
    'name' => 'administrator',
    'description' => 3,
    'format' => NULL,
    'weight' => 3,
    'uuid' => '4f7ad123-5b88-418f-b7b9-4df029ea7e8c',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60551,
  );
  $terms[] = array(
    'name' => 'anonymous user',
    'description' => 1,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '55d24be2-5396-44bf-86f3-169383e6dca4',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60541,
  );
  $terms[] = array(
    'name' => 'facilitator',
    'description' => 11,
    'format' => NULL,
    'weight' => 8,
    'uuid' => '632c99f7-5806-4537-a5f7-c01e8ca466f3',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60581,
  );
  $terms[] = array(
    'name' => 'digital library administrator',
    'description' => 8,
    'format' => NULL,
    'weight' => 12,
    'uuid' => '6b26c506-047f-4109-9c60-cee1d5439bce',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60601,
  );
  $terms[] = array(
    'name' => 'resource contributor',
    'description' => 15,
    'format' => NULL,
    'weight' => 5,
    'uuid' => '843aff48-16ac-409b-a7da-670460c97709',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60566,
  );
  $terms[] = array(
    'name' => 'All User Roles',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'a221e140-2cc1-4792-9927-a2b37c5efd60',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60536,
  );
  $terms[] = array(
    'name' => 'basic end user',
    'description' => 25,
    'format' => NULL,
    'weight' => 3,
    'uuid' => 'a60a0903-732f-4466-8284-f607423eaa62',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60556,
  );
  $terms[] = array(
    'name' => 'Welcome Tutorial',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'cd3ccb4a-bdc2-43f2-8a6c-13fe297c4bf5',
    'vocabulary_machine_name' => 'help_page_topic',
  );
  $terms[] = array(
    'name' => 'DLRB member',
    'description' => 7,
    'format' => NULL,
    'weight' => 10,
    'uuid' => 'd043a948-7341-491a-9c34-34bdd257a162',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60591,
  );
  $terms[] = array(
    'name' => 'moderator',
    'description' => 13,
    'format' => NULL,
    'weight' => 9,
    'uuid' => 'dc038b2e-79af-46aa-b473-047473387383',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60586,
  );
  $terms[] = array(
    'name' => 'system administrator',
    'description' => 23,
    'format' => NULL,
    'weight' => 13,
    'uuid' => 'debd60d5-2029-42af-88d3-675e129fbeff',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60606,
  );
  $terms[] = array(
    'name' => 'Help Desk Contacts',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'e7eba79f-7b9e-4705-836c-3f9bf6d7d7c2',
    'vocabulary_machine_name' => 'help_page_topic',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 78701,
  );
  $terms[] = array(
    'name' => 'on-boarding',
    'description' => 26,
    'format' => NULL,
    'weight' => 15,
    'uuid' => 'ed2da7bc-f9e4-434e-8964-e096a927a42e',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60611,
  );
  $terms[] = array(
    'name' => 'resource publisher',
    'description' => 16,
    'format' => NULL,
    'weight' => 7,
    'uuid' => 'fc89d37a-bd68-4f0f-ae27-d59bffd97161',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60576,
  );
  $terms[] = array(
    'name' => 'guest',
    'description' => 31,
    'format' => NULL,
    'weight' => 16,
    'uuid' => 'ff43c214-7469-4f84-bd61-beeccde08e5d',
    'vocabulary_machine_name' => 'sbac_user_roles',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60616,
  );
  return $terms;
}
