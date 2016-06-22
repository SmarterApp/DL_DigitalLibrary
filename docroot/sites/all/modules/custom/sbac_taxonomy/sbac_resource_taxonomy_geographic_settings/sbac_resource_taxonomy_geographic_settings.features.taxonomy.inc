<?php
/**
 * @file
 * sbac_resource_taxonomy_geographic_settings.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_geographic_settings_taxonomy_default_vocabularies() {
  return array(
    'geographical_settings' => array(
      'name' => 'Geographic Settings',
      'machine_name' => 'geographical_settings',
      'description' => 'Geographic educational settings for which the resource is appropriate.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -2,
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
