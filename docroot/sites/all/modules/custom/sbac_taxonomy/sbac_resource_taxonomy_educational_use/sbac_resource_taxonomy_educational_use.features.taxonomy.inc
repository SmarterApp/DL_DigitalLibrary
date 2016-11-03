<?php
/**
 * @file
 * sbac_resource_taxonomy_educational_use.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_educational_use_taxonomy_default_vocabularies() {
  return array(
    'educational_use' => array(
      'name' => 'Educational Use',
      'machine_name' => 'educational_use',
      'description' => 'The purpose of the instructional resources in the context of a lesson.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -6,
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
