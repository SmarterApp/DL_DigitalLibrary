<?php
/**
 * @file
 * sbac_collections.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function sbac_collections_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_f8ecfb3d-1ebf-4627-ab05-f9b1ad84b106';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Collection',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'node-type-collection-view',
    'css_id' => 'collection-list-region',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'User from Node (on node.node_author)',
        'keyword' => 'user',
        'name' => 'entity_from_schema:uid-node-user',
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
    ),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'collection' => 'collection',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'context_exists',
          'settings' => array(
            'exists' => '1',
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'foundation_2col_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title by %user:name';
  $display->uuid = '79b870db-a7c0-405b-afd9-54f44507226e';
  $display->storage_type = 'unknown';
  $display->storage_id = '';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-6d5bdbf1-53c8-4479-8fc5-280c28980f21';
  $pane->panel = 'bottom';
  $pane->type = 'views';
  $pane->subtype = 'collection';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 1,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'list_view',
    'context' => array(
      0 => '',
    ),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'digital-library page-my-resources list-view',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '6d5bdbf1-53c8-4479-8fc5-280c28980f21';
  $display->content['new-6d5bdbf1-53c8-4479-8fc5-280c28980f21'] = $pane;
  $display->panels['bottom'][0] = 'new-6d5bdbf1-53c8-4479-8fc5-280c28980f21';
  $pane = new stdClass();
  $pane->pid = 'new-cb8e4bd8-f690-41eb-90c5-34f276ef8e6b';
  $pane->panel = 'left';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_subject';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'taxonomy_term_reference_plain',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Subjects and Domains',
    'override_title_heading' => 'div',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'item-list item-list-field-pane',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'cb8e4bd8-f690-41eb-90c5-34f276ef8e6b';
  $display->content['new-cb8e4bd8-f690-41eb-90c5-34f276ef8e6b'] = $pane;
  $display->panels['left'][0] = 'new-cb8e4bd8-f690-41eb-90c5-34f276ef8e6b';
  $pane = new stdClass();
  $pane->pid = 'new-d8570e7d-f08b-4767-a748-177c8184ab2f';
  $pane->panel = 'right';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_grades';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'taxonomy_term_reference_plain',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Grades',
    'override_title_heading' => 'div',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'item-list item-list-field-pane',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'd8570e7d-f08b-4767-a748-177c8184ab2f';
  $display->content['new-d8570e7d-f08b-4767-a748-177c8184ab2f'] = $pane;
  $display->panels['right'][0] = 'new-d8570e7d-f08b-4767-a748-177c8184ab2f';
  $pane = new stdClass();
  $pane->pid = 'new-044edfb7-8adb-4eae-936d-a72104f842ca';
  $pane->panel = 'top';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => 'Title with by',
    'title' => '',
    'body' => '<h1 class="title">%node:title <span class="title-by">by %node:author</span></h1>',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '044edfb7-8adb-4eae-936d-a72104f842ca';
  $display->content['new-044edfb7-8adb-4eae-936d-a72104f842ca'] = $pane;
  $display->panels['top'][0] = 'new-044edfb7-8adb-4eae-936d-a72104f842ca';
  $pane = new stdClass();
  $pane->pid = 'new-a9229d48-48f9-4cbe-8e83-05766e96ab6b';
  $pane->panel = 'top';
  $pane->type = 'node_body';
  $pane->subtype = 'node_body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'div',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'a9229d48-48f9-4cbe-8e83-05766e96ab6b';
  $display->content['new-a9229d48-48f9-4cbe-8e83-05766e96ab6b'] = $pane;
  $display->panels['top'][1] = 'new-a9229d48-48f9-4cbe-8e83-05766e96ab6b';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-a9229d48-48f9-4cbe-8e83-05766e96ab6b';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_f8ecfb3d-1ebf-4627-ab05-f9b1ad84b106'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function sbac_collections_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'favorites_for_user';
  $page->task = 'page';
  $page->admin_title = 'Favorites for user';
  $page->admin_description = '';
  $page->path = 'favorites/%user';
  $page->access = array(
    'plugins' => array(),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'user' => array(
      'id' => 1,
      'identifier' => 'User: name',
      'name' => 'user_name',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_favorites_for_user__panel';
  $handler->task = 'page';
  $handler->subtask = 'favorites_for_user';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'User Collection',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'node-type-collection-view',
    'css_id' => 'collection-list-region',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'foundation_2col_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Favorites for %user:name';
  $display->uuid = 'ba847f8e-da37-4e83-a6b9-eb1596878320';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_favorites_for_user__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-3fd65c11-060c-43d1-a094-04e910baa59d';
  $pane->panel = 'bottom';
  $pane->type = 'views';
  $pane->subtype = 'collection';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 0,
    'nodes_per_page' => '0',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 1,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'user_list_view',
    'context' => array(
      0 => 'argument_user_name_1.uid',
    ),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '3fd65c11-060c-43d1-a094-04e910baa59d';
  $display->content['new-3fd65c11-060c-43d1-a094-04e910baa59d'] = $pane;
  $display->panels['bottom'][0] = 'new-3fd65c11-060c-43d1-a094-04e910baa59d';
  $pane = new stdClass();
  $pane->pid = 'new-e6d63f34-f8e8-4caa-9f7b-e0cf5c51f2ed';
  $pane->panel = 'top';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => 'Favorites by user',
    'title' => '',
    'body' => '<h1 class="title">Favorites <span class="title-by">by %user:name</span></h1>',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'e6d63f34-f8e8-4caa-9f7b-e0cf5c51f2ed';
  $display->content['new-e6d63f34-f8e8-4caa-9f7b-e0cf5c51f2ed'] = $pane;
  $display->panels['top'][0] = 'new-e6d63f34-f8e8-4caa-9f7b-e0cf5c51f2ed';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['favorites_for_user'] = $page;

  return $pages;

}
