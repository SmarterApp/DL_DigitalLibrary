<?php
/**
 * @file
 * sbac_lexicon_taxonomy_glossary_terms.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_lexicon_taxonomy_glossary_terms_taxonomy_default_vocabularies() {
  return array(
    'glossary_terms' => array(
      'name' => 'Glossary Terms',
      'machine_name' => 'glossary_terms',
      'description' => 'Glossary Terms',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -1,
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
