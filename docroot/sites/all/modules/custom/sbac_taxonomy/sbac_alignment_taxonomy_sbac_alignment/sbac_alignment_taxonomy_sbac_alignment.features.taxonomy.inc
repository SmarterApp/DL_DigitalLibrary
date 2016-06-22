<?php
/**
 * @file
 * sbac_alignment_taxonomy_sbac_alignment.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_alignment_taxonomy_sbac_alignment_taxonomy_default_vocabularies() {
  return array(
    'sbac_alignment' => array(
      'name' => 'SBAC Alignment',
      'machine_name' => 'sbac_alignment',
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
