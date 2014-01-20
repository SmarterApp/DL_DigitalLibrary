<?php
/**
 * @file
 * sbac_flag.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_flag_taxonomy_default_vocabularies() {
  return array(
    'resource_flags' => array(
      'name' => 'Resource Flags',
      'machine_name' => 'resource_flags',
      'description' => 'The flags that are available when a user wishes to flag a resource.',
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
