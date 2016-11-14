<?php
/**
 * @file
 * sbac_authorized_domains.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_authorized_domains_taxonomy_default_vocabularies() {
  return array(
    'districts' => array(
      'name' => 'Districts',
      'machine_name' => 'districts',
      'description' => 'sbac_districts_taxonomy',
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
    'states' => array(
      'name' => 'States',
      'machine_name' => 'states',
      'description' => 'List of States.',
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
