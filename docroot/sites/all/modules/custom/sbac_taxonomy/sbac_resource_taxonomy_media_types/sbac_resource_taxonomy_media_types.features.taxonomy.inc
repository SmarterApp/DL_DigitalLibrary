<?php
/**
 * @file
 * sbac_resource_taxonomy_media_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_media_types_taxonomy_default_vocabularies() {
  return array(
    'digital_media_type' => array(
      'name' => 'Media Types',
      'machine_name' => 'digital_media_type',
      'description' => 'Media formats for materials in the resource',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 7,
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
