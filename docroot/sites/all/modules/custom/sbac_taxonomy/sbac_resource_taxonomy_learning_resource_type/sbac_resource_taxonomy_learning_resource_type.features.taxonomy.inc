<?php
/**
 * @file
 * sbac_resource_taxonomy_learning_resource_type.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_learning_resource_type_taxonomy_default_vocabularies() {
  return array(
    'learning_resource_type' => array(
      'name' => 'Learning Resource Type',
      'machine_name' => 'learning_resource_type',
      'description' => 'The predominate type or kind characterizing the learning resource.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 5,
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
