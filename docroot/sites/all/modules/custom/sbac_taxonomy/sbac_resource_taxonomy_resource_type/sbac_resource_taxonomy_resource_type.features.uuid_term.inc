<?php
/**
 * @file
 * sbac_resource_taxonomy_resource_type.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_resource_type_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Professional Learning',
    'description' => '',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => '4cbc72a3-4ddd-4ef5-a06d-2750708deb59',
    'vocabulary_machine_name' => 'focus',
  );
  $terms[] = array(
    'name' => 'Instructional and Professional Learning',
    'description' => '',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => '549c0b03-4112-41ca-ba43-ab95cb5a108a',
    'vocabulary_machine_name' => 'focus',
  );
  $terms[] = array(
    'name' => 'Spotlight',
    'description' => '<p>Digital Library administrator designation only.</p>',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => 'a937dc6a-3172-4f83-93eb-66b5bcea3b84',
    'vocabulary_machine_name' => 'focus',
  );
  $terms[] = array(
    'name' => 'Playlist',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 3,
    'uuid' => 'b658e198-df9b-4653-83ee-b263a335b73d',
    'vocabulary_machine_name' => 'focus',
  );
  $terms[] = array(
    'name' => 'Instructional',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => 'facbb021-8739-4e09-ba41-f0a18ed607e5',
    'vocabulary_machine_name' => 'focus',
  );
  return $terms;
}
