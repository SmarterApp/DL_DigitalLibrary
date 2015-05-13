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
    'alignment_type' => array(
      'name' => 'Alignment Type',
      'machine_name' => 'alignment_type',
      'description' => 'Alignment Type for Resources content.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 23,
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
    'education_alignment' => array(
      'name' => 'Education Alignment',
      'machine_name' => 'education_alignment',
      'description' => '',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => -1,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 11,
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
    'sbac_alignment' => array(
      'name' => 'SBAC Alignment',
      'machine_name' => 'sbac_alignment',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 20,
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
