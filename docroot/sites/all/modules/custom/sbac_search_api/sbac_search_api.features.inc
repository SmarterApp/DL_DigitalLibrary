<?php
/**
 * @file
 * sbac_search_api.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_search_api_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "current_search" && $api == "current_search") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_search_api_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function sbac_search_api_default_search_api_index() {
  $items = array();
  $items['default_node_index'] = entity_import('search_api_index', '{
    "name" : "Default node index",
    "machine_name" : "default_node_index",
    "description" : "An automatically created search index for indexing node data. Might be configured to specific needs.",
    "server" : "local_solr",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "resource" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_access" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "field_digital_media_type:parents_all" : "field_digital_media_type:parents_all",
              "field_educational_use:parents_all" : "field_educational_use:parents_all",
              "field_intended_end_user:parents_all" : "field_intended_end_user:parents_all",
              "field_smarter_balanced_keyword:parents_all" : "field_smarter_balanced_keyword:parents_all",
              "field_subject:parents_all" : "field_subject:parents_all",
              "field_attributes:parents_all" : "field_attributes:parents_all",
              "field_grades:parents_all" : "field_grades:parents_all",
              "field_intended_student:parents_all" : "field_intended_student:parents_all",
              "field_alignment_term:parents_all" : "field_alignment_term:parents_all",
              "field_target_term:parents_all" : "field_target_term:parents_all"
            }
          }
        },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "field_summary" : true,
              "field_alt_body" : true,
              "field_author" : true,
              "body:value" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_summary" : true,
              "field_alt_body" : true,
              "field_author" : true,
              "body:value" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 0,
          "weight" : "15",
          "settings" : { "fields" : {
              "title" : true,
              "field_summary" : true,
              "field_alt_body" : true,
              "field_author" : true,
              "body:value" : true
            }
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_summary" : true,
              "field_alt_body" : true,
              "field_author" : true,
              "body:value" : true
            },
            "spaces" : "[^\\\\p{L}\\\\p{N}]",
            "ignorable" : "[-]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_summary" : true,
              "field_alt_body" : true,
              "field_author" : true,
              "body:value" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_porter_stemmer" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_summary" : true,
              "field_alt_body" : true,
              "field_author" : true,
              "body:value" : true
            },
            "exceptions" : "texan=texa"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "40",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always",
            "highlight_partial" : 0
          }
        }
      },
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "author:field_first_name" : { "type" : "text" },
        "author:field_last_name" : { "type" : "text" },
        "author:name" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "field_alignment_term" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_alt_body" : { "type" : "text" },
        "field_asset_downloads" : { "type" : "integer" },
        "field_attributes" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_author" : { "type" : "text" },
        "field_digital_media_type" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_educational_use" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_focus" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "field_grades" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_intended_student" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_node_avg_rating" : { "type" : "decimal" },
        "field_smarter_balanced_keyword" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_subject" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_summary" : { "type" : "text" },
        "field_target_term" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_topic_files:file:field_file_image_alt_text" : { "type" : "list\\u003Ctext\\u003E" },
        "field_topic_files:file:field_file_image_title_text" : { "type" : "list\\u003Ctext\\u003E" },
        "field_topic_files:file:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_unique_views" : { "type" : "integer" },
        "search_api_access_node" : { "type" : "list\\u003Cstring\\u003E" },
        "search_api_language" : { "type" : "string" },
        "search_api_url" : { "type" : "uri" },
        "status" : { "type" : "boolean" },
        "sticky" : { "type" : "boolean" },
        "title" : { "type" : "text", "boost" : "5.0" },
        "workbench_moderation_state" : { "type" : "string" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_sort().
 */
function sbac_search_api_default_search_api_sort() {
  $items = array();
  $items['default_node_index__created'] = entity_import('search_api_sort', '{
    "index_id" : "default_node_index",
    "field" : "created",
    "name" : "Newest",
    "enabled" : "1",
    "weight" : "-99",
    "identifier" : "default_node_index__created",
    "default_sort" : "0",
    "default_sort_no_terms" : "0",
    "default_order" : "desc",
    "options" : { "field_name" : "Date created" },
    "rdf_mapping" : []
  }');
  $items['default_node_index__field_asset_downloads'] = entity_import('search_api_sort', '{
    "index_id" : "default_node_index",
    "field" : "field_asset_downloads",
    "name" : "Most Downloaded",
    "enabled" : "1",
    "weight" : "-97",
    "identifier" : "default_node_index__field_asset_downloads",
    "default_sort" : "0",
    "default_sort_no_terms" : "0",
    "default_order" : "desc",
    "options" : { "field_name" : "Asset Downloads" },
    "rdf_mapping" : []
  }');
  $items['default_node_index__field_node_avg_rating'] = entity_import('search_api_sort', '{
    "index_id" : "default_node_index",
    "field" : "field_node_avg_rating",
    "name" : "Highest Rated",
    "enabled" : "1",
    "weight" : "-96",
    "identifier" : "default_node_index__field_node_avg_rating",
    "default_sort" : "0",
    "default_sort_no_terms" : "0",
    "default_order" : "desc",
    "options" : { "field_name" : "Node Avg Rating" },
    "rdf_mapping" : []
  }');
  $items['default_node_index__field_unique_views'] = entity_import('search_api_sort', '{
    "index_id" : "default_node_index",
    "field" : "field_unique_views",
    "name" : "Most Viewed",
    "enabled" : "1",
    "weight" : "-98",
    "identifier" : "default_node_index__field_unique_views",
    "default_sort" : "0",
    "default_sort_no_terms" : "0",
    "default_order" : "desc",
    "options" : { "field_name" : "Unique Views" },
    "rdf_mapping" : []
  }');
  $items['default_node_index__sticky'] = entity_import('search_api_sort', '{
    "index_id" : "default_node_index",
    "field" : "sticky",
    "name" : "Default",
    "enabled" : "1",
    "weight" : "-100",
    "identifier" : "default_node_index__sticky",
    "default_sort" : "1",
    "default_sort_no_terms" : "1",
    "default_order" : "desc",
    "options" : { "field_name" : "Sticky in lists" },
    "rdf_mapping" : []
  }');
  return $items;
}
