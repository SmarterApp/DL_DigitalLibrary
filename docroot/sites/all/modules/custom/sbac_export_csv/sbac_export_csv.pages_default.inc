<?php
/**
 * @file
 * sbac_export_csv.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function sbac_export_csv_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'sbac_exports';
  $page->task = 'page';
  $page->admin_title = 'SBAC Exports';
  $page->admin_description = 'List of exportable items';
  $page->path = 'exports';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access content',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_sbac_exports__panel';
  $handler->task = 'page';
  $handler->subtask = 'sbac_exports';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'b647181c-e9ad-4c4c-8301-af32ce01f058';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_sbac_exports__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-db314c56-7f38-4b45-8bac-3709df45b2fd';
  $pane->panel = 'center';
  $pane->type = 'custom';
  $pane->subtype = 'custom';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => 'SBAC Exports List',
    'title' => '',
    'body' => '<table><tbody><tr><td><a href="./ccss-export.csv">Common Core Standards</a></td></tr></tbody></table>',
    'format' => 'full_html',
    'substitute' => TRUE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'db314c56-7f38-4b45-8bac-3709df45b2fd';
  $display->content['new-db314c56-7f38-4b45-8bac-3709df45b2fd'] = $pane;
  $display->panels['center'][0] = 'new-db314c56-7f38-4b45-8bac-3709df45b2fd';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-db314c56-7f38-4b45-8bac-3709df45b2fd';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['sbac_exports'] = $page;

  return $pages;

}
