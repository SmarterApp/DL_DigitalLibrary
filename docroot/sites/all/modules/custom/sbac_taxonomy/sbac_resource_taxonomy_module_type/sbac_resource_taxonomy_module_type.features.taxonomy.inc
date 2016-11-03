<?php
/**
 * @file
 * sbac_resource_taxonomy_module_type.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_module_type_taxonomy_default_vocabularies() {
  return array(
    'smarter_balanced_keyword' => array(
      'name' => 'Module Type',
      'machine_name' => 'smarter_balanced_keyword',
      'description' => 'Identifiers aligned to Smarter Balanced commissioned modules.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 8,
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
