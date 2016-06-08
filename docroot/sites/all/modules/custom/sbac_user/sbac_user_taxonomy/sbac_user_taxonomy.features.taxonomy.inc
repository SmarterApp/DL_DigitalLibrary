<?php
/**
 * @file
 * sbac_user_taxonomy.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_user_taxonomy_taxonomy_default_vocabularies() {
  return array(
    'title' => array(
      'name' => 'Title',
      'machine_name' => 'title',
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
