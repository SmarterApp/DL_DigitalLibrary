<?php
/**
 * @file
 * sbac_lexicon.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_lexicon_taxonomy_default_vocabularies() {
  return array(
    'glossary_terms' => array(
      'name' => 'Glossary Terms',
      'machine_name' => 'glossary_terms',
      'description' => 'Glossary Terms',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 22,
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
