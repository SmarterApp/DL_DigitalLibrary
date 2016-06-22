<?php
/**
 * @file
 * sbac_alignment_taxonomy_alignment_type.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_alignment_taxonomy_alignment_type_taxonomy_default_vocabularies() {
  return array(
    'alignment_type' => array(
      'name' => 'Alignment Type',
      'machine_name' => 'alignment_type',
      'description' => 'Alignment Type for Resources content.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -9,
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
