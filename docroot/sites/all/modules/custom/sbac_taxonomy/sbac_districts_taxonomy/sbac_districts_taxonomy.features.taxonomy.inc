<?php
/**
 * @file
 * sbac_districts_taxonomy.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_districts_taxonomy_taxonomy_default_vocabularies() {
  return array(
    'districts' => array(
      'name' => 'Districts',
      'machine_name' => 'districts',
      'description' => 'The districts in the SBAC member states.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
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
