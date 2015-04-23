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
    'forum_flags' => array(
      'name' => 'Forum Flags',
      'machine_name' => 'forum_flags',
      'description' => 'The flags that are available when a user wishes to flag a forum topic or comment.',
      'hierarchy' => 0,
      'module' => '',
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
    'glossary_terms' => array(
      'name' => 'Glossary Terms',
      'machine_name' => 'glossary_terms',
      'description' => 'Glossary Terms',
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
