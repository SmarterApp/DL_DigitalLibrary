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
  // Exported flag: "Discussion subscribe".
  $flags['subscribe_node'] = array(
    'entity_type' => 'node',
    'title' => 'Discussion subscribe',
    'global' => 0,
    'types' => array(
      0 => 'resource',
      1 => 'topic',
    ),
    'flag_short' => 'Subscribe',
    'flag_long' => '',
    'flag_message' => 'You are now subscribed to this item.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => '',
    'unflag_message' => 'You are no longer subscribed to this item.',
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
    'flag_short' => 'Subscribe',
    'flag_long' => '',
    'flag_message' => 'You are now subscribed to this item.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => '',
    'unflag_message' => 'You are no longer subscribed to this item.',
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
          "value" : "New discussion [message:field-node-ref:title] posted to [message:field-node-ref:field_topic_forum_parent]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003ENew discussion [message:field-node-ref:title] posted to [message:field-node-ref:field_topic_forum_parent]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\u003Cp\\u003EYou have subscribed to receive email notifications for new discussion threads posted to forum \\u0022[message:field-node-ref:field_topic_forum_parent].\\u0022\\u003C\\/p\\u003E\\u003Cp\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], [message:field-node-ref:author:field-first-name] [message:field-node-ref:author:field_last_name] wrote:\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; [message:field-node-ref:body]\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EView this discussion in the Digital Library: [message:field-node-ref:url]\\u003C\\/p\\u003E\\u003Cp\\u003EView this forum in the Digital Library: \\u003Ca href=\\u0022\\/forums\\/term\\/[message:field-node-ref:field-topic-forum-parent:tid]\\u0022\\u003E[message:field-node-ref:field_topic_forum_parent]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EUnsubscribe to this forum: \\u003Ca href=\\u0022\\/forums\\/term\\/[message:field-node-ref:field-topic-forum-parent:tid]\\u0022\\u003E[message:field-node-ref:field_topic_forum_parent]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003EOpt-out of all email notifications: [message:user:edit-url]",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYou have subscribed to receive email notifications for new discussion threads posted to forum \\u0022[message:field-node-ref:field_topic_forum_parent].\\u0022\\u003C\\/p\\u003E\\n\\u003Cp\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], [message:field-node-ref:author:field-first-name] [message:field-node-ref:author:field_last_name] wrote:\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; [message:field-node-ref:body]\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EView this discussion in the Digital Library: [message:field-node-ref:url]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EView this forum in the Digital Library: \\u003Ca href=\\u0022\\/forums\\/term\\/[message:field-node-ref:field-topic-forum-parent:tid]\\u0022\\u003E[message:field-node-ref:field_topic_forum_parent]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EUnsubscribe to this forum: \\u003Ca href=\\u0022\\/forums\\/term\\/[message:field-node-ref:field-topic-forum-parent:tid]\\u0022\\u003E[message:field-node-ref:field_topic_forum_parent]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003EOpt-out of all email notifications: [message:user:edit-url]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "entity_type" : "message_type",
    "entity_id" : "34",
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
          "value" : "New response posted to discussion [message:field-comment-ref:node:title] in forum [message:field-comment-ref:node:field_topic_forum_parent]",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003ENew response posted to discussion [message:field-comment-ref:node:title] in forum [message:field-comment-ref:node:field_topic_forum_parent]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp style=\\u0022font-family: \\u0027Open Sans\\u0027, sans-serif; font-size: 16px;\\u0022\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EYou have subscribed to receive email notifications for posts to the discussion thread\\u0026nbsp;\\u003C\\/span\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E\\u0026nbsp;\\u0022\\u003C\\/span\\u003E\\u003Ca style=\\u0022line-height: 19.2000007629395px;\\u0022 href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:title]\\u003C\\/a\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E\\u0022 in forum \\u0022\\u003C\\/span\\u003E[message:field-comment-ref:node:field_topic_forum_parent].\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E\\u0022\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], [message:field-comment-ref:author:field-first-name] [message:field-comment-ref:author:field_last_name] wrote:\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp;\\u0026nbsp;\\u003Cspan style=\\u0022font-family: inherit;\\u0022\\u003E\\u003Cspan style=\\u0022line-height: 1.2; font-size: 1em;\\u0022\\u003E[message:field-comment-ref:body]\\u003C\\/span\\u003E\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EView this discussion post int the Digital Library:\\u0026nbsp;\\u003C\\/span\\u003E\\u003Ca style=\\u0022line-height: 19.2000007629395px;\\u0022 href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:url]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EUnsubscribe to this discussion:\\u0026nbsp;\\u003C\\/span\\u003E\\u003Ca style=\\u0022line-height: 19.2000007629395px;\\u0022 href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:url]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOpt-out of all email notifications:\\u0026nbsp;\\u003C\\/span\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E[message:user:edit-url]\\u003C\\/span\\u003E\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp style=\\u0022font-family: \\u0027Open Sans\\u0027, sans-serif; font-size: 16px;\\u0022\\u003EDear Digital Library user:\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EYou have subscribed to receive email notifications for posts to the discussion thread\\u0026nbsp;\\u003C\\/span\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E\\u0026nbsp;\\u0022\\u003C\\/span\\u003E\\u003Ca style=\\u0022line-height: 19.2000007629395px;\\u0022 href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:title]\\u003C\\/a\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E\\u0022 in forum \\u0022\\u003C\\/span\\u003E[message:field-comment-ref:node:field_topic_forum_parent].\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E\\u0022\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOn [current-date:custom:F j \\\\a\\\\t g:i a], [message:field-comment-ref:author:field-first-name] [message:field-comment-ref:author:field_last_name] wrote:\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp; \\u0026nbsp;\\u0026nbsp;\\u003Cspan style=\\u0022font-family: inherit;\\u0022\\u003E\\u003Cspan style=\\u0022line-height: 1.2; font-size: 1em;\\u0022\\u003E[message:field-comment-ref:body]\\u003C\\/span\\u003E\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EView this discussion post int the Digital Library:\\u0026nbsp;\\u003C\\/span\\u003E\\u003Ca style=\\u0022line-height: 19.2000007629395px;\\u0022 href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:url]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EUnsubscribe to this discussion:\\u0026nbsp;\\u003C\\/span\\u003E\\u003Ca style=\\u0022line-height: 19.2000007629395px;\\u0022 href=\\u0022[message:field-comment-ref:node:url]\\u0022\\u003E[message:field-comment-ref:node:url]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003EOpt-out of all email notifications:\\u0026nbsp;\\u003C\\/span\\u003E\\u003Cspan style=\\u0022font-family: inherit; font-size: 1em; line-height: 1.2;\\u0022\\u003E[message:user:edit-url]\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "entity_type" : "message_type",
    "entity_id" : "35",
    "rdf_mapping" : []
  }');
  return $items;
}
