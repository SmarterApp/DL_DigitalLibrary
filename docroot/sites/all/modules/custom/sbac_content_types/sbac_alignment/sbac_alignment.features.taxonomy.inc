<?php
/**
 * @file
 * sbac_alignment.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_alignment_taxonomy_default_vocabularies() {
  return array(
    'education_alignment' => array(
      'name' => 'Education Alignment',
      'machine_name' => 'education_alignment',
      'description' => '',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => -7,
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
    'target_alignment' => array(
      'name' => 'Target Alignment',
      'machine_name' => 'target_alignment',
      'description' => 'Target Alignment Tags',
      'hierarchy' => 1,
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
