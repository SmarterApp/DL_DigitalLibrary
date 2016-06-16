<?php
/**
 * @file
 * sbac_resource_taxonomy_formative_assesment.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_formative_assesment_taxonomy_default_vocabularies() {
  return array(
    'attributes' => array(
      'name' => 'Formative Assessment Attributes',
      'machine_name' => 'attributes',
      'description' => 'Attributes of Formative Assessment Process',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -5,
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
