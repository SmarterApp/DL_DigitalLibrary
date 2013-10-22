<?php
/**
 * @file
 * sbac_resource.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sbac_resource_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-resource-field_alignment_tags'
  $field_instances['node-resource-field_alignment_tags'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_alignment_tags',
    'label' => 'Alignment Tags',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 29,
    ),
  );

  // Exported field_instance: 'node-resource-field_alignment_term'
  $field_instances['node-resource-field_alignment_term'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 35,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 42,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'tooltip',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_alignment_term',
    'label' => 'Common Core Standard(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'label_help_description' => '',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 30,
    ),
  );

  // Exported field_instance: 'node-resource-field_alt_body'
  $field_instances['node-resource-field_alt_body'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Enter a user-friendly summary of the resource that includes the topics covered by the resource and how the resource should be used (e.g., PLCs, individual, ongoing learning, etc.).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_alt_body',
    'label' => 'Body',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Enter a user-friendly summary of the resource that includes the topics covered by the resource and how the resource should be used (e.g., PLCs, individual, ongoing learning, etc.).',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-resource-field_asset_downloads'
  $field_instances['node-resource-field_asset_downloads'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 33,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_asset_downloads',
    'label' => 'Asset Downloads',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'number',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-resource-field_attributes'
  $field_instances['node-resource-field_attributes'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Which attributes of the formative assessment process does this resource include? Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 16,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 21,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 35,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_attributes',
    'label' => 'Attributes',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'Which attributes of the formative assessment process does this resource include? Select all that apply.',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_buttons',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-resource-field_author'
  $field_instances['node-resource-field_author'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The name(s) of the person/people who wrote or developed the resource:',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 9,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 10,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 29,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_author',
    'label' => 'Author',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'The name(s) of the person/people who wrote or developed the resource:',
        'maxlength_js' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'size' => 75,
      ),
      'type' => 'text_textfield',
      'weight' => 34,
    ),
  );

  // Exported field_instance: 'node-resource-field_classroom_technologies'
  $field_instances['node-resource-field_classroom_technologies'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The technologies required to use this resource in the classroom. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 29,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 35,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_classroom_technologies',
    'label' => 'Technologies Required for Use in Classroom',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'The technologies required to use this resource in the classroom. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 28,
    ),
  );

  // Exported field_instance: 'node-resource-field_connection_to_ccss'
  $field_instances['node-resource-field_connection_to_ccss'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Identify how this resource addresses the Common Core State Standards (e.g., how it addresses particular claims, clusters, targets, and/or “standards”). Pay special attention to the interconnectedness of claims.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 20,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 25,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 39,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_connection_to_ccss',
    'label' => 'Connection to CCSS',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Identify how this resource addresses the Common Core State Standards (e.g., how it addresses particular claims, clusters, targets, and/or “standards”). Pay special attention to the interconnectedness of claims.',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-resource-field_connection_to_fap'
  $field_instances['node-resource-field_connection_to_fap'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Identify how this includes, reflects, and addresses the formative assessment process.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 21,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 26,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 40,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_connection_to_fap',
    'label' => 'Connection to FAP',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Identify how this includes, reflects, and addresses the formative assessment process.',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-resource-field_contexts'
  $field_instances['node-resource-field_contexts'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Describe the likely context(s) in which the resource could be used (e.g. PLCs, individual, ongoing learning, small group, whole class).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 19,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 24,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 38,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_contexts',
    'label' => 'Contexts',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Describe the likely context(s) in which the resource could be used (e.g. PLCs, individual, ongoing learning, small group, whole class).',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-resource-field_digital_media_type'
  $field_instances['node-resource-field_digital_media_type'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The type(s) of media included in the resource. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 5,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 7,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_digital_media_type',
    'label' => 'Digital Media Type(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'The type(s) of media included in the resource. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 26,
    ),
  );

  // Exported field_instance: 'node-resource-field_document_id'
  $field_instances['node-resource-field_document_id'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
      ),
      'search_index' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'secondary_teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_document_id',
    'label' => 'Document ID',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-resource-field_educational_use'
  $field_instances['node-resource-field_educational_use'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The purpose of the instructional resources in the context of a lesson. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 6,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 8,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_educational_use',
    'label' => 'Educational Use',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'The purpose of the instructional resources in the context of a lesson. Select all that apply.',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_select',
      'weight' => 27,
    ),
  );

  // Exported field_instance: 'node-resource-field_file'
  $field_instances['node-resource-field_file'] = array(
    'bundle' => 'resource',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 0,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 1,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_file',
    'label' => 'Materials',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'resource',
      'file_extensions' => 'doc docx odt pdf xls xlsx ods ppt pptx odp txt jpg png jpeg mp4 mpg mov avi mp3 aac',
      'max_filesize' => '100 MB',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
          'schooltube' => 'schooltube',
          'slideshare' => 'slideshare',
          'teachertube' => 'teachertube',
          'vimeo' => 'vimeo',
          'youtube' => 'youtube',
        ),
        'allowed_types' => array(
          'audio' => 'audio',
          'document' => 'document',
          'image' => 'image',
          'video' => 'video',
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 'media_internet',
          'upload' => 'upload',
          'youtube' => 0,
        ),
        'label_help_description' => 'You can add videos, images and documents to this resource. This resource must contain at least one (1) material.',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 31,
    ),
  );

  // Exported field_instance: 'node-resource-field_focus'
  $field_instances['node-resource-field_focus'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'From the list, select the one choice that most closely describes the type of resource.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 18,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 23,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 37,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_focus',
    'label' => 'Resource Type',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'From the list, select the one choice that most closely describes the type of resource.',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_buttons',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-resource-field_geographical_settings'
  $field_instances['node-resource-field_geographical_settings'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Setting(s) for which this resource is appropriate. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 28,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 34,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_geographical_settings',
    'label' => 'Geographical Setting(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'Setting(s) for which this resource is appropriate. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 24,
    ),
  );

  // Exported field_instance: 'node-resource-field_grades'
  $field_instances['node-resource-field_grades'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The Grade(s) in which the resource might be used, regardless of curriculum alignment. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 26,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 32,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_grades',
    'label' => 'Grade(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'The Grade(s) in which the resource might be used, regardless of curriculum alignment. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'node-resource-field_intended_end_user'
  $field_instances['node-resource-field_intended_end_user'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Individual(s) or group(s) for whom the resource was produced. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 4,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 6,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_intended_end_user',
    'label' => 'Intended End User(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'Individual(s) or group(s) for whom the resource was produced. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 22,
    ),
  );

  // Exported field_instance: 'node-resource-field_intended_student'
  $field_instances['node-resource-field_intended_student'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Student population(s) for which the resource is best suited. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 27,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 33,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_intended_student',
    'label' => 'Intended Student Population(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'Student population(s) for which the resource is best suited. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'node-resource-field_learning_goals'
  $field_instances['node-resource-field_learning_goals'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Identify the learning targets associated with this resource. Learning targets can be for students and/or educators depending upon whether a resource is a professional learning resource or an instructional resource.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 22,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 28,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 41,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_learning_goals',
    'label' => 'Learning Targets',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Identify the learning targets associated with this resource. Learning targets can be for students and/or educators depending upon whether a resource is a professional learning resource or an instructional resource.',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-resource-field_license'
  $field_instances['node-resource-field_license'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The license under which all the uploaded materials in this resource can be used in the Digital Library.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 15,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 20,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 34,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_license',
    'label' => 'Specific License',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
        'label_help_description' => 'The license under which all the uploaded materials in this resource can be used in the Digital Library.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 36,
    ),
  );

  // Exported field_instance: 'node-resource-field_license_information'
  $field_instances['node-resource-field_license_information'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 9,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_license_information',
    'label' => 'License Information',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'Select one choice. Any materials submitted to the Library through a link to YouTube, Vimeo, SchoolTube, TeacherTube, or SlideShare are made available under the terms that govern the embedding functions of that service.',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_buttons',
      'weight' => 33,
    ),
  );

  // Exported field_instance: 'node-resource-field_pii'
  $field_instances['node-resource-field_pii'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Per FERPA regulations, resources in the Digital Library cannot contain student records and other information that identify to specific students.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 30,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 36,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_pii',
    'label' => 'Personally Identifiable Student Information',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'Per FERPA regulations, resources in the Digital Library cannot contain student records and other information that identify to specific students.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_buttons',
      'weight' => 37,
    ),
  );

  // Exported field_instance: 'node-resource-field_posting_options'
  $field_instances['node-resource-field_posting_options'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 40,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_posting_options',
    'label' => 'Posting Options',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'The last saved posting determination.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_buttons',
      'weight' => 42,
    ),
  );

  // Exported field_instance: 'node-resource-field_posting_options_comment'
  $field_instances['node-resource-field_posting_options_comment'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 41,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_posting_options_comment',
    'label' => 'To contributor',
    'profanity' => 1,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js' => 300,
        'maxlength_js_enforce' => 0,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 43,
    ),
    'xss' => 1,
  );

  // Exported field_instance: 'node-resource-field_principles'
  $field_instances['node-resource-field_principles'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'List either:
<ol type=\'A\'><li>the principles of adult learning or professional development reflected in the resource; and/or</li>
<li>the literature, research, or widely accepted practices used to inform the content in the resource. </li>
</ol>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 25,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 31,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 44,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_principles',
    'label' => 'Principles',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'List either:
<ol type=\'A\'><li>the principles of adult learning or professional development reflected in the resource; and/or</li>
<li>the literature, research, or widely accepted practices used to inform the content in the resource.</li>
</ol>',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-resource-field_publisher'
  $field_instances['node-resource-field_publisher'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The name(s) of the person/people/entities/publishers who own the copyright for the resource:',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 30,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_publisher',
    'label' => 'Owner',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'The name(s) of the person/people/entities/publishers who own the copyright for the resource:',
        'maxlength_js' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'size' => 75,
      ),
      'type' => 'text_textfield',
      'weight' => 35,
    ),
  );

  // Exported field_instance: 'node-resource-field_resource_actions'
  $field_instances['node-resource-field_resource_actions'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
      1 => array(
        'value' => 1,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 39,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_resource_actions',
    'label' => 'What can people do with this resource?',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'By default, resources are only accessible by authenticating into the Digital Library',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_buttons',
      'weight' => 41,
    ),
  );

  // Exported field_instance: 'node-resource-field_resource_state'
  $field_instances['node-resource-field_resource_state'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 'creation',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 42,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_resource_state',
    'label' => 'Resource State',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 0,
        'label_help_description' => '',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 44,
    ),
  );

  // Exported field_instance: 'node-resource-field_smarter_balanced_keyword'
  $field_instances['node-resource-field_smarter_balanced_keyword'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Identifiers aligned to Smarter Balanced topics. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 10,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 11,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_smarter_balanced_keyword',
    'label' => 'Smarter Balanced Keyword(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'Identifiers aligned to Smarter Balanced topics. Select all that apply.',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_select',
      'weight' => 25,
    ),
  );

  // Exported field_instance: 'node-resource-field_student_agency'
  $field_instances['node-resource-field_student_agency'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Describe how this resource enables students to actively engage in the formative assessment process, if applicable.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 17,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 22,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 36,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_student_agency',
    'label' => 'Student Engagement in the Formative Assesment Process',
    'profanity' => 0,
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Describe how this resource enables students to actively engage in the formative assessment process, if applicable.',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-resource-field_subject'
  $field_instances['node-resource-field_subject'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The Subject area(s) and domain(s) to which the learning resource applies. Select all that apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 7,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 9,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_subject',
    'label' => 'Subjects and Domains',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'label_help_description' => 'The Subject area(s) and domain(s) to which the learning resource applies. Select all that apply.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_select',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-resource-field_subscription_package_type'
  $field_instances['node-resource-field_subscription_package_type'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 37,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_subscription_package_type',
    'label' => 'Subscription Package Type',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'Identify the subscription package to which this resource is aligned',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_buttons',
      'weight' => 38,
    ),
  );

  // Exported field_instance: 'node-resource-field_success_criteria'
  $field_instances['node-resource-field_success_criteria'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Identify the Success Criteria that describe what success looks like from a learner’s perspective when the learning target is reached. The learner can be a student and/or educator depending on whether a resource is a professional learning resource or an instructional resource.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 23,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 29,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 42,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_success_criteria',
    'label' => 'Success Criteria',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Identify the Success Criteria that describe what success looks like from a learner’s perspective when the learning target is reached. The learner can be a student and/or educator depending on whether a resource is a professional learning resource or an instructional resource.',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-resource-field_supporting_evidence'
  $field_instances['node-resource-field_supporting_evidence'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Include evidence that the resource has been tried successfully with educators (or students) and has resulted in a positive impact on educator practices (or student outcomes)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 24,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 30,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 43,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_supporting_evidence',
    'label' => 'Supporting Evidence',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'label_help_description' => 'Include evidence that the resource has been tried successfully with educators (or students) and has resulted in a positive impact on educator practices (or student outcomes)',
        'maxlength_js' => 600,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Character count: @remaining',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-resource-field_temp'
  $field_instances['node-resource-field_temp'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 14,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 18,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 33,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_temp',
    'label' => 'Temp',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
        'label_help_description' => '',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_onoff',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-resource-field_total_views'
  $field_instances['node-resource-field_total_views'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 32,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_total_views',
    'label' => 'Total Views',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'number',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-resource-field_unique_views'
  $field_instances['node-resource-field_unique_views'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 31,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_unique_views',
    'label' => 'Unique Views',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'number',
      'weight' => 12,
    ),
  );

  // Exported field_instance: 'node-resource-field_video'
  $field_instances['node-resource-field_video'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 34,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 41,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_video',
    'label' => 'Embedded Video',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'txt',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'emfield',
      'settings' => array(
        'label_help_description' => '',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'enfield_widget',
      'weight' => 32,
    ),
  );

  // Exported field_instance: 'node-resource-field_view_permissions'
  $field_instances['node-resource-field_view_permissions'] = array(
    'bundle' => 'resource',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 38,
      ),
      'search_index' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_view_permissions',
    'label' => 'View Permissions',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'label_help_description' => 'By default, a resource entered via the posting workflow is visible to all Smarter Balanced member states.',
        'maxlength_js_label' => '',
      ),
      'type' => 'options_buttons',
      'weight' => 39,
    ),
  );

  // Exported field_instance: 'node-resource-field_view_permissions_per_state'
  $field_instances['node-resource-field_view_permissions_per_state'] = array(
    'bundle' => 'resource',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 13,
      ),
      'search_index' => array(
        'label' => 'above',
        'module' => 'ds',
        'settings' => array(
          'taxonomy_term_reference_view_mode' => 'full',
        ),
        'type' => 'ds_taxonomy_view_mode',
        'weight' => 17,
      ),
      'secondary_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 32,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_view_permissions_per_state',
    'label' => 'View Permissions Per State',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
      ),
      'type' => 'options_select',
      'weight' => 40,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Alignment Tags');
  t('Asset Downloads');
  t('Attributes');
  t('Author');
  t('Body');
  t('Common Core Standard(s)');
  t('Connection to CCSS');
  t('Connection to FAP');
  t('Contexts');
  t('Describe how this resource enables students to actively engage in the formative assessment process, if applicable.');
  t('Describe the likely context(s) in which the resource could be used (e.g. PLCs, individual, ongoing learning, small group, whole class).');
  t('Digital Media Type(s)');
  t('Document ID');
  t('Educational Use');
  t('Embedded Video');
  t('Enter a user-friendly summary of the resource that includes the topics covered by the resource and how the resource should be used (e.g., PLCs, individual, ongoing learning, etc.).');
  t('From the list, select the one choice that most closely describes the type of resource.');
  t('Geographical Setting(s)');
  t('Grade(s)');
  t('Identifiers aligned to Smarter Balanced topics. Select all that apply.');
  t('Identify how this includes, reflects, and addresses the formative assessment process.');
  t('Identify how this resource addresses the Common Core State Standards (e.g., how it addresses particular claims, clusters, targets, and/or “standards”). Pay special attention to the interconnectedness of claims.');
  t('Identify the Success Criteria that describe what success looks like from a learner’s perspective when the learning target is reached. The learner can be a student and/or educator depending on whether a resource is a professional learning resource or an instructional resource.');
  t('Identify the learning targets associated with this resource. Learning targets can be for students and/or educators depending upon whether a resource is a professional learning resource or an instructional resource.');
  t('Include evidence that the resource has been tried successfully with educators (or students) and has resulted in a positive impact on educator practices (or student outcomes)');
  t('Individual(s) or group(s) for whom the resource was produced. Select all that apply.');
  t('Intended End User(s)');
  t('Intended Student Population(s)');
  t('Learning Targets');
  t('License Information');
  t('List either:
<ol type=\'A\'><li>the principles of adult learning or professional development reflected in the resource; and/or</li>
<li>the literature, research, or widely accepted practices used to inform the content in the resource. </li>
</ol>');
  t('Materials');
  t('Owner');
  t('Per FERPA regulations, resources in the Digital Library cannot contain student records and other information that identify to specific students.');
  t('Personally Identifiable Student Information');
  t('Posting Options');
  t('Principles');
  t('Resource State');
  t('Resource Type');
  t('Setting(s) for which this resource is appropriate. Select all that apply.');
  t('Smarter Balanced Keyword(s)');
  t('Specific License');
  t('Student Engagement in the Formative Assesment Process');
  t('Student population(s) for which the resource is best suited. Select all that apply.');
  t('Subjects and Domains');
  t('Subscription Package Type');
  t('Success Criteria');
  t('Supporting Evidence');
  t('Technologies Required for Use in Classroom');
  t('Temp');
  t('The Grade(s) in which the resource might be used, regardless of curriculum alignment. Select all that apply.');
  t('The Subject area(s) and domain(s) to which the learning resource applies. Select all that apply.');
  t('The license under which all the uploaded materials in this resource can be used in the Digital Library.');
  t('The name(s) of the person/people who wrote or developed the resource:');
  t('The name(s) of the person/people/entities/publishers who own the copyright for the resource:');
  t('The purpose of the instructional resources in the context of a lesson. Select all that apply.');
  t('The technologies required to use this resource in the classroom. Select all that apply.');
  t('The type(s) of media included in the resource. Select all that apply.');
  t('To contributor');
  t('Total Views');
  t('Unique Views');
  t('View Permissions');
  t('View Permissions Per State');
  t('What can people do with this resource?');
  t('Which attributes of the formative assessment process does this resource include? Select all that apply.');

  return $field_instances;
}
