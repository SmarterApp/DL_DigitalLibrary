<?php
/**
 * @file
 * sbac_resource_taxonomy_license.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_license_taxonomy_default_vocabularies() {
  return array(
    'license' => array(
      'name' => 'License',
      'machine_name' => 'license',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 6,
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
