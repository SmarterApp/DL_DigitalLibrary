<?php
/**
 * @file
 * sbac_resource.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sbac_resource_taxonomy_default_vocabularies() {
  return array(
    'age_range' => array(
      'name' => 'Age Range',
      'machine_name' => 'age_range',
      'description' => 'The typical age range of the resource\'s intended end user.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -4,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 1,
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
    'attributes' => array(
      'name' => 'Attributes',
      'machine_name' => 'attributes',
      'description' => 'Attributes of Formative Assessment Process',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 13,
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
    'digital_media_type' => array(
      'name' => 'Digital Media Type',
      'machine_name' => 'digital_media_type',
      'description' => 'Type of media in which the resource is provided.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -9,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 2,
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
    'educational_use' => array(
      'name' => 'Educational Use',
      'machine_name' => 'educational_use',
      'description' => 'The purpose of the instructional resources in the context of a lesson.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -8,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 3,
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
    'focus' => array(
      'name' => 'Focus',
      'machine_name' => 'focus',
      'description' => 'The focus of the resource',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 14,
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
    'geographical_settings' => array(
      'name' => 'Geographical Setting(s)',
      'machine_name' => 'geographical_settings',
      'description' => 'Setting(s) for which the resource is appropriate.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 15,
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
    'grades' => array(
      'name' => 'Grades',
      'machine_name' => 'grades',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 16,
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
    'intended_end_user' => array(
      'name' => 'Intended End User',
      'machine_name' => 'intended_end_user',
      'description' => 'Individual or group for which the resource was produced.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -10,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 4,
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
    'intended_student_populations' => array(
      'name' => 'Intended Student Population(s)',
      'machine_name' => 'intended_student_populations',
      'description' => 'Student populations with which the resource can be used.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 17,
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
    'interactivity_type' => array(
      'name' => 'Interactivity Type',
      'machine_name' => 'interactivity_type',
      'description' => 'The predominate mode of learning supported by the learning resource.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -3,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 5,
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
    'learning_resource_type' => array(
      'name' => 'Learning Resource Type',
      'machine_name' => 'learning_resource_type',
      'description' => 'The predominate type or kind characterizing the learning resource.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -6,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 6,
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
    'license' => array(
      'name' => 'License',
      'machine_name' => 'license',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 19,
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
    'resource_states' => array(
      'name' => 'Resource States',
      'machine_name' => 'resource_states',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 31,
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
    'smarter_balanced_keyword' => array(
      'name' => 'Smarter Balanced Keyword',
      'machine_name' => 'smarter_balanced_keyword',
      'description' => 'Identifiers aligned to Smarter Balanced topics.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -5,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 7,
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
    'states' => array(
      'name' => 'States',
      'machine_name' => 'states',
      'description' => 'List of States.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 8,
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
    'subject' => array(
      'name' => 'Subject',
      'machine_name' => 'subject',
      'description' => 'The subject area to which the resource applies.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -7,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 9,
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
    'technologies_for_classroom_use' => array(
      'name' => 'Technologies for Classroom Use',
      'machine_name' => 'technologies_for_classroom_use',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'entity_type' => 'taxonomy_vocabulary',
      'entity_id' => 21,
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
