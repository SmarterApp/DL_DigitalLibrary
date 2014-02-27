<?php
/**
 * @file
 * sbac_forum.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function sbac_forum_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'forum_main_page';
  $context->description = 'used for forum filter page';
  $context->tag = 'forum';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'forums' => 'forums',
      ),
    ),
  );
  $context->reactions = array(
    'theme_html' => array(
      'class' => 'sbac-forum-browse-page',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('forum');
  t('used for forum filter page');
  $export['forum_main_page'] = $context;

  return $export;
}
