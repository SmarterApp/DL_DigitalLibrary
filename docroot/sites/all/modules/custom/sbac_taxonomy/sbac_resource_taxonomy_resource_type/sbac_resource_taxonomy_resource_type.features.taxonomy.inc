<?php
/**
 * @file
 * sbac_resource_taxonomy_resource_type.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_resource_type_taxonomy_default_vocabularies() {
  return array(
    'focus' => array(
      'name' => 'Resource Type',
      'machine_name' => 'focus',
      'description' => 'The type of resource',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 10,
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
