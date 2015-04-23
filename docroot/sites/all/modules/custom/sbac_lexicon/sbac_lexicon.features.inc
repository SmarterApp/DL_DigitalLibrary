<?php
/**
 * @file
 * sbac_lexicon.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_lexicon_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "elysia_cron" && $api == "default_elysia_cron_rules") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sbac_lexicon_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function sbac_lexicon_default_message_type() {
  $items = array();
  $items['comment_insert'] = entity_import('message_type', '{
    "name" : "comment_insert",
    "description" : "Comment insert",
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
          "value" : "\\u003Cp\\u003E[message:field-comment-ref:author] commented on [message:field-comment-ref:node:title]\\u003C\\/p\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-comment-ref:author] commented on [message:field-comment-ref:node:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EHello [message:field-comment-ref:node:author], \\u003Ca href=\\u0022[message:field-comment-ref:author:url]\\u0022\\u003E[message:field-comment-ref:author:name]\\u003C\\/a\\u003E has commented on your post \\u003Ca href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:title]\\u003C\\/a\\u003E. Here\\u0027s what they had to say:\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026gt;\\u0026gt;\\u0026gt;\\u0026gt;[message:field-comment-ref:body]\\u003C\\/p\\u003E\\u003Cp\\u003ECheers,\\u0026nbsp;SmarterBalanced Reply Bot\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EHello [message:field-comment-ref:node:author], \\u003Ca href=\\u0022[message:field-comment-ref:author:url]\\u0022\\u003E[message:field-comment-ref:author:name]\\u003C\\/a\\u003E has commented on your post \\u003Ca href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:title]\\u003C\\/a\\u003E. Here\\u0027s what they had to say:\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026gt;\\u0026gt;\\u0026gt;\\u0026gt;[message:field-comment-ref:body]\\u003C\\/p\\u003E\\n\\u003Cp\\u003ECheers,\\u00a0SmarterBalanced Reply Bot\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "entity_type" : "message_type",
    "entity_id" : "4",
    "rdf_mapping" : []
  }');
  return $items;
}
