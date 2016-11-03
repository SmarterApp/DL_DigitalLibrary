<?php
/**
 * @file
 * sbac_resource_taxonomy_license.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_resource_taxonomy_license_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Smarter Balanced Terms of Service (owned by the contributor)',
    'description' => NULL,
    'format' => NULL,
    'weight' => -6,
    'uuid' => '2f762934-b4d3-477d-8e6e-14a2ac6de637',
    'vocabulary_machine_name' => 'license',
  );
  $terms[] = array(
    'name' => 'Creative Commons Attribution',
    'description' => '',
    'format' => NULL,
    'weight' => -9,
    'uuid' => '785eed57-f602-41c9-ba83-b6554c8b6b7e',
    'vocabulary_machine_name' => 'license',
  );
  $terms[] = array(
    'name' => 'Creative Commons Attribution No Derivatives',
    'description' => '',
    'format' => NULL,
    'weight' => -8,
    'uuid' => 'b45f50ff-10aa-4103-9443-31e583fb3901',
    'vocabulary_machine_name' => 'license',
  );
  $terms[] = array(
    'name' => 'Smarter Balanced Copyright Clearance Form (signed by the owner)',
    'description' => '',
    'format' => NULL,
    'weight' => -10,
    'uuid' => 'b4edee0e-0bc4-475b-80df-49ac3636c46d',
    'vocabulary_machine_name' => 'license',
  );
  $terms[] = array(
    'name' => 'License Available at Approved Content Site (e.g., YouTube, Slideshare)',
    'description' => NULL,
    'format' => NULL,
    'weight' => -5,
    'uuid' => 'bb703dbb-e4f0-439e-b381-2b794906b8b6',
    'vocabulary_machine_name' => 'license',
  );
  $terms[] = array(
    'name' => 'Public Domain (free of copyright restrictions)',
    'description' => '',
    'format' => NULL,
    'weight' => -7,
    'uuid' => 'e85732d1-0afc-4a34-9d30-6013ef2b4882',
    'vocabulary_machine_name' => 'license',
  );
  return $terms;
}
