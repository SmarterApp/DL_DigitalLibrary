<?php
/**
 * @file
 * sbac_help.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_help_taxonomy_default_vocabularies() {
  return array(
    'help_topic_category' => array(
      'name' => 'Help Topic Category',
      'machine_name' => 'help_topic_category',
      'description' => '',
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
