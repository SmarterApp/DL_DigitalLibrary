<?php
/**
 * @file
 * sbac_email.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_email_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_email_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function sbac_email_default_message_type() {
  $items = array();
  $items['node_insert'] = entity_import('message_type', '{
    "name" : "node_insert",
    "description" : "Node insert",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[message:field-node-ref:author:field_first_name] [message:field-node-ref:author:field_last_name] posted new discussion [message:field-node-ref:title] for [message:field-node-ref:field_topic_forum_parent]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-node-ref:author:field_first_name] [message:field-node-ref:author:field_last_name] posted new discussion [message:field-node-ref:title] for [message:field-node-ref:field_topic_forum_parent]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003E[message:field-node-ref:author:field-first-name] [message:field-node-ref:author:field_last_name] posted new discussion \\u0022\\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E\\u0022 for \\u003Ca href=\\u0022[message:field-node-ref:field-topic-forum-parent:url]\\u0022\\u003E[message:field-node-ref:field_topic_forum_parent]:\\u003C\\/a\\u003E \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:body]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-node-ref:author:field-first-name] [message:field-node-ref:author:field_last_name] posted new discussion \\u0022\\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:title]\\u003C\\/a\\u003E\\u0022 for \\u003Ca href=\\u0022[message:field-node-ref:field-topic-forum-parent:url]\\u0022\\u003E[message:field-node-ref:field_topic_forum_parent]:\\u003C\\/a\\u003E \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003E[message:field-node-ref:body]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "entity_type" : "message_type",
    "entity_id" : "15",
    "rdf_mapping" : []
  }');
  return $items;
}
