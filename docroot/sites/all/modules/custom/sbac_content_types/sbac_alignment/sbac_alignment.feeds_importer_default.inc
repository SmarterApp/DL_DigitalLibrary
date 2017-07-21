<?php
/**
 * @file
 * sbac_alignment.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function sbac_alignment_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'cc_tags';
  $feeds_importer->config = array(
    'name' => 'CC Tags',
    'description' => 'Imports the crosswalk data to the CC taxonomy.',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'delete_uploaded_file' => 0,
        'direct' => 0,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          'gs' => 'gs',
          'public' => 'public',
          'private' => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'encoding' => 'UTF-8',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'id',
            'target' => 'field_alignment_key',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'crosswalk',
            'target' => 'field_alignment_crosswalk',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'insert_new' => '0',
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'education_alignment',
        'language' => 'und',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['cc_tags'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'target_tags';
  $feeds_importer->config = array(
    'name' => 'Target Tags',
    'description' => 'Imports the Target tags',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'delete_uploaded_file' => 0,
        'direct' => 0,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          'gs' => 'gs',
          'public' => 'public',
          'private' => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'encoding' => 'UTF-8',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsTermProcessor',
      'config' => array(
        'vocabulary' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'name',
            'target' => 'name',
            'unique' => FALSE,
            'language' => 'und',
          ),
          1 => array(
            'source' => 'fullDescription',
            'target' => 'description',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'uuid',
            'target' => 'guid',
            'unique' => 1,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'parentUuid',
            'target' => 'parentguid',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'shortName',
            'target' => 'field_alignment_shortname',
            'unique' => FALSE,
            'language' => 'und',
          ),
          5 => array(
            'source' => 'publication',
            'target' => 'field_alignment_publication',
            'unique' => FALSE,
            'language' => 'und',
          ),
          6 => array(
            'source' => 'grade',
            'target' => 'field_alignment_grade',
            'unique' => FALSE,
            'language' => 'und',
          ),
          7 => array(
            'source' => 'name',
            'target' => 'field_alignment_key',
            'unique' => FALSE,
            'language' => 'und',
          ),
          8 => array(
            'source' => 'crosswalk',
            'target' => 'field_alignment_crosswalk',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '0',
        'update_non_existent' => 'skip',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'target_alignment',
        'language' => 'und',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['target_tags'] = $feeds_importer;

  return $export;
}
