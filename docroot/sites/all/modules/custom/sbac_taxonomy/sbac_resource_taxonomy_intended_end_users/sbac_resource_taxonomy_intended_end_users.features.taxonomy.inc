<?php
/**
 * @file
 * sbac_resource_taxonomy_intended_end_users.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_intended_end_users_taxonomy_default_vocabularies() {
  return array(
    'intended_end_user' => array(
      'name' => 'Intended End Users',
      'machine_name' => 'intended_end_user',
      'description' => 'Individual or group for which the resource was produced.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 2,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
