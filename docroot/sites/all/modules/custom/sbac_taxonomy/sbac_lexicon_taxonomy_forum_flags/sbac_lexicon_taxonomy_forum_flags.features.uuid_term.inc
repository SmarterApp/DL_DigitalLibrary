<?php
/**
 * @file
 * sbac_lexicon_taxonomy_forum_flags.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_lexicon_taxonomy_forum_flags_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Biased and objectionable or culturally insensitive. <span>(e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)</span>',
    'description' => NULL,
    'format' => NULL,
    'weight' => -3,
    'uuid' => '32be672b-7a18-418b-aa78-d4e44563d85a',
    'vocabulary_machine_name' => 'forum_flags',
  );
  $terms[] = array(
    'name' => 'Outdated or inactive',
    'description' => NULL,
    'format' => NULL,
    'weight' => -6,
    'uuid' => '5b0740a8-c16f-422b-8937-578e232c095f',
    'vocabulary_machine_name' => 'forum_flags',
  );
  $terms[] = array(
    'name' => 'Unintelligible',
    'description' => NULL,
    'format' => NULL,
    'weight' => -4,
    'uuid' => '9af886bb-fdf9-4831-8651-87cfbe6180b5',
    'vocabulary_machine_name' => 'forum_flags',
  );
  $terms[] = array(
    'name' => 'Inaccurate / misleading',
    'description' => NULL,
    'format' => NULL,
    'weight' => -5,
    'uuid' => 'ab267575-eb99-43d7-a883-06d0188befd7',
    'vocabulary_machine_name' => 'forum_flags',
  );
  $terms[] = array(
    'name' => 'Contains personally identifiable information (PII)',
    'description' => NULL,
    'format' => NULL,
    'weight' => -2,
    'uuid' => 'e92b20f7-5bed-45e0-b67b-544b76fed7df',
    'vocabulary_machine_name' => 'forum_flags',
  );
  $terms[] = array(
    'name' => 'Appears to be spam',
    'description' => NULL,
    'format' => NULL,
    'weight' => -1,
    'uuid' => 'edacd1d0-6ede-4c9f-b64a-605adba3402e',
    'vocabulary_machine_name' => 'forum_flags',
  );
  return $terms;
}
