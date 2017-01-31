<?php
/**
 * @file
 * sbac_forum.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_forum_taxonomy_default_vocabularies() {
  return array(
    'forum' => array(
      'name' => 'Forum',
      'machine_name' => 'forum',
      'description' => 'Handles collaboration functionality',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -4,
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
