<?php
/**
 * @file
 * sbac_help_taxonomy_sbac_user_roles.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_help_taxonomy_sbac_user_roles_taxonomy_default_vocabularies() {
  return array(
    'sbac_user_roles' => array(
      'name' => 'SBAC User Roles',
      'machine_name' => 'sbac_user_roles',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 10,
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
