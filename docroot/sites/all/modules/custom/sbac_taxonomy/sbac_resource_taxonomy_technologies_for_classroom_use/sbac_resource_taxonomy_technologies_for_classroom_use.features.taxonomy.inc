<?php
/**
 * @file
 * sbac_resource_taxonomy_technologies_for_classroom_use.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_technologies_for_classroom_use_taxonomy_default_vocabularies() {
  return array(
    'technologies_for_classroom_use' => array(
      'name' => 'Technologies for Classroom Use',
      'machine_name' => 'technologies_for_classroom_use',
      'description' => '',
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
