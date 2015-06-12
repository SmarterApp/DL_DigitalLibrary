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
    'flag_short' => 'Email Notification is OFF - Click to turn on email notices',
    'flag_long' => 'Turn on email notices',
    'flag_message' => '',
    'unflag_short' => 'Email Notification is ON - Click to turn off email notices',
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
  // Exported flag: "Discussion subscribe".
  $flags['subscribe_node'] = array(
    'entity_type' => 'node',
    'title' => 'Discussion subscribe',
    'global' => 0,
    'types' => array(
      0 => 'resource',
      1 => 'topic',
    ),
    'flag_short' => 'Subscribe to Discussion',
    'flag_long' => 'Receive notifications of new posts in this discussion',
    'flag_message' => '',
    'unflag_short' => 'Unsubscribe from Discussion',
    'unflag_long' => 'Don\'t receive notifications of new posts in this discussion',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => -9,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'diff_standard' => 0,
      'print' => 0,
      'token' => 0,
      'secondary_teaser' => 0,
      'revision' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'sbac_email',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Forum Subscribe".
  $flags['subscribe_term'] = array(
    'entity_type' => 'taxonomy_term',
    'title' => 'Forum Subscribe',
    'global' => 0,
    'types' => array(
      0 => 'forum',
    ),
    'flag_short' => 'Subscribe to Forum',
    'flag_long' => 'Receive notifications of new discussions in this forum',
    'flag_message' => '',
    'unflag_short' => 'Unsubscribe from Forum',
    'unflag_long' => 'Don\'t receive notifications of new discussions in this forum',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => -8,
    'show_in_links' => array(
      'full' => 0,
      'diff_standard' => 0,
      'token' => 0,
      'tooltip' => 0,
      'forum_page_card' => 0,
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
          "value" : "\\u003Cp\\u003ENew discussion \\u0022[message:field-node-ref:title]\\u0022 Posted to Forum \\u0022[message:field-node-ref:field_topic_forum_parent]\\u0022\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003ENew discussion \\u0022[message:field-node-ref:title]\\u0022 Posted to Forum \\u0022[message:field-node-ref:field_topic_forum_parent]\\u0022\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], the discussion thread,\\u0026nbsp;\\u003C\\/span\\u003E[message:field-node-ref:title], was added.\\u0026nbsp;\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E[message:field-node-ref:author:field-first-name] [message:field-node-ref:author:field_last_name] wrote:\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; [message:field-node-ref:body]\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EView this discussion in the Digital Library by clicking \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:mail].\\u003C\\/a\\u003E You are receiving this email because you are subscribed to this forum and your email notification setting is \\u0022On.\\u0022 Click \\u003Ca href=\\u0022\\/forums\\/term\\/[message:field-node-ref:field-topic-forum-parent:tid]\\u0022\\u003Ehere\\u003C\\/a\\u003E and select the \\u0022Unsubscribe\\u0022 link to unsubscribe to this forum. Change your email notification settings by clicking \\u003Ca href=\\u0022[message:user:url:absolute]#edit-sbac-user-email-options\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], the discussion thread,\\u0026nbsp;\\u003C\\/span\\u003E[message:field-node-ref:title], was added.\\u0026nbsp;\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E[message:field-node-ref:author:field-first-name] [message:field-node-ref:author:field_last_name] wrote:\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; [message:field-node-ref:body]\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EView this discussion in the Digital Library by clicking \\u003Ca href=\\u0022[message:field-node-ref:url]\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:mail].\\u003C\\/a\\u003E You are receiving this email because you are subscribed to this forum and your email notification setting is \\u0022On.\\u0022 Click \\u003Ca href=\\u0022\\/forums\\/term\\/[message:field-node-ref:field-topic-forum-parent:tid]\\u0022\\u003Ehere\\u003C\\/a\\u003E and select the \\u0022Unsubscribe\\u0022 link to unsubscribe to this forum. Change your email notification settings by clicking \\u003Ca href=\\u0022[message:user:url:absolute]#edit-sbac-user-email-options\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "entity_type" : "message_type",
    "entity_id" : "308",
    "rdf_mapping" : []
  }');
  $items['sbac_email_comment_insert'] = entity_import('message_type', '{
    "name" : "sbac_email_comment_insert",
    "description" : "SBAC Email Comment Insert",
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
          "value" : "New response posted to discussion \\u0022[message:field-comment-ref:node:title]\\u0022 in forum \\u0022[message:field-comment-ref:node:field_topic_forum_parent]\\u0022",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003ENew response posted to discussion \\u0022[message:field-comment-ref:node:title]\\u0022 in forum \\u0022[message:field-comment-ref:node:field_topic_forum_parent]\\u0022\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], [message:field-comment-ref:author:field-first-name] [message:field-comment-ref:author:field_last_name] wrote:\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; [message:field-comment-ref:body]\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EView this discussion post in the Digital Library by clicking \\u003Ca href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:mail].\\u003C\\/a\\u003E You are receiving this email because you are subscribed to the discussion [message:field-comment-ref:node:title]\\u0026nbsp;and your email notification setting is \\u0022On.\\u0022 Click \\u003Ca href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003Ehere\\u003C\\/a\\u003E and select the \\u0022Unsubscribe\\u0022 link to unsubscribe to this discussion. Change your email notification settings by clicking \\u003Ca href=\\u0022[message:user:url:absolute]#edit-sbac-user-email-options\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], [message:field-comment-ref:author:field-first-name] [message:field-comment-ref:author:field_last_name] wrote:\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; [message:field-comment-ref:body]\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EView this discussion post in the Digital Library by clicking \\u003Ca href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for \\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:mail].\\u003C\\/a\\u003E You are receiving this email because you are subscribed to the discussion [message:field-comment-ref:node:title]\\u0026nbsp;and your email notification setting is \\u0022On.\\u0022 Click \\u003Ca href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003Ehere\\u003C\\/a\\u003E and select the \\u0022Unsubscribe\\u0022 link to unsubscribe to this discussion. Change your email notification settings by clicking \\u003Ca href=\\u0022[message:user:url:absolute]#edit-sbac-user-email-options\\u0022\\u003Ehere.\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "entity_type" : "message_type",
    "entity_id" : "310",
    "rdf_mapping" : []
  }');
  return $items;
}
