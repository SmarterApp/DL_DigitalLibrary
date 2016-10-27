<?php
/**
 * @file
 * sbac_resource_taxonomy_interactivity_type.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_interactivity_type_taxonomy_default_vocabularies() {
  return array(
    'interactivity_type' => array(
      'name' => 'Interactivity Type',
      'machine_name' => 'interactivity_type',
      'description' => 'The predominate mode of learning supported by the learning resource.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 4,
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
