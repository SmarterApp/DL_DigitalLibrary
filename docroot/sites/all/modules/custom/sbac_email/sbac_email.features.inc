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
 * Implements hook_flag_default_flags().
 */
function sbac_email_flag_default_flags() {
  $flags = array();
  // Exported flag: "Email receive".
  $flags['email'] = array(
    'entity_type' => 'flag',
    'title' => 'Email receive',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Turn on email notices',
    'flag_long' => 'Turn on email notices',
    'flag_message' => '',
    'unflag_short' => 'Turn off Email notices',
    'unflag_long' => 'Turn off email notices',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'teaser' => 'teaser',
      'diff_standard' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'module' => 'sbac_email',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

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
    "entity_id" : "18",
    "rdf_mapping" : []
  }');
  return $items;
}
