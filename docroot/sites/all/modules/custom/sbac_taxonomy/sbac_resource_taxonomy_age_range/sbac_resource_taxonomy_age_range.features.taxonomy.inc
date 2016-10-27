<?php
/**
 * @file
 * sbac_resource_taxonomy_age_range.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_age_range_taxonomy_default_vocabularies() {
  return array(
    'age_range' => array(
      'name' => 'Age Range',
      'machine_name' => 'age_range',
      'description' => 'The typical age range of the resource\'s intended end user.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -10,
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
