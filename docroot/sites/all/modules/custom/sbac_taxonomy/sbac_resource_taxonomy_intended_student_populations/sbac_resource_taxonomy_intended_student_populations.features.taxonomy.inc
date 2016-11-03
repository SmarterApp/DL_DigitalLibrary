<?php
/**
 * @file
 * sbac_resource_taxonomy_intended_student_populations.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_intended_student_populations_taxonomy_default_vocabularies() {
  return array(
    'intended_student_populations' => array(
      'name' => 'Intended Student Populations',
      'machine_name' => 'intended_student_populations',
      'description' => 'Student populations with whom the resource can be used.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 3,
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
