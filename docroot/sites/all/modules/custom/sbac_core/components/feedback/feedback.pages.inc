<?php

/*----------------------------------------------------------------------------
      CALLBACKS
----------------------------------------------------------------------------*/

/**
 * Callback for /node/###/feedback.
 */
function resource_feedback_page($node) {
  $output = '';

  $path = drupal_get_path('module', 'sbac_core') . '/components/feedback';
  drupal_add_css($path . '/css/feedback.css');
  drupal_add_js($path . '/js/feedback.js');

  module_load_include('inc', 'sbac_core', '/components/sections/includes/class.Factory');

  try {
    $factory = new \sbac_core\components\sections\Factory($node);

    if ($node->workbench_moderation['current']->state == 'published') {
      $tabs = array(
        'access about process' => array(
          'feedback' => array(
            'about' => TRUE,
            'collaboration' => FALSE,
          ),
        ),
        'access review process' => array(
          'review' => array(
            'reviews' => FALSE,
          ),
        ),
        'access share process' => array(
          'feedback' => array(
            'share' => FALSE,
          )
        ),
        'access related resources' => array(
          'feedback' => array(
            'related_resources' => FALSE,
          ),
        ),
        'access flag' => array(
          'feedback' => array(
            'flag' => FALSE,
          ),
        ),
        'access moderate flag' => array(
          'feedback' => array(
            'moderate_flag' => TRUE,
          )
        ),
      );

    }
    else {
      $tabs = array(
        'access about process' => array(
          'feedback' => array(
            'about' => TRUE,
            'collaboration' => FALSE,
          ),
        ),
        'access gk review comments' => array(
          'feedback' => array(
            'gk_comments' => TRUE,
          ),
        ),
        'access qc review comments' => array(
          'feedback' => array(
            'qc_comments' => TRUE,
          ),
        ),
        'access review process' => array(
          'review' => array(
            'reviews' => FALSE,
          ),
        ),
        'access quality criteria process' => array(
          'feedback' => array(
            'revisions' => TRUE,
            'gk' => TRUE,
            'qc' => TRUE,
          ),
        ),
        'access post process' => array(
          'feedback' => array(
            'tags' => TRUE,
            'post' => TRUE,
          ),
        ),
        'access share process' => array(
          'feedback' => array(
            'share' => FALSE,
          )
        ),
        'access related resources' => array(
          'feedback' => array(
            'related_resources' => FALSE,
          ),
        ),
        'access flag' => array(
          'feedback' => array(
            'flag' => FALSE,
          ),
        ),
        'access moderate flag' => array(
          'feedback' => array(
            'moderate_flag' => TRUE,
          )
        ),
      );
    }

    foreach ($tabs as $permission => $sources) {
      if ($factory->access($permission)) {
        foreach ($sources as $source => $items) {
          foreach ($items as $tab => $visible) {
            $section = $factory->get($source, $tab);
            if ($section && ($section->access() || $section->show_disabled())) {
              $factory->add($section, $source, $tab, $visible);
            }
          }
        }
      }
    }

    // on click, send source and tab ('feedback', 'about')
    // to ajax callback, render factory using source and tab
    // place into content div for that tab....
    if ($sections = $factory->getSections()) {
      // we don't want to display the Edit Resource Tags section if the
      // Publisher doesn't have access to the Post process
      if (!isset($sections['post']) || $sections['post']['disabled']) {
        unset($sections['tags']);
      }

      $output = theme('sections', array(
        'sections' => $sections,
        'name' => 'review',
      ));
    }
  }
  catch (\Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
  }

  return $output;
}

/**
 * AJAX callback for /node/###/feedback/*
 * @param  [type] $node           [description]
 * @param  [type] $state          [description]
 * @param  [type] $trigger_id     [description]
 * @param  [type] $entity_id      [description]
 * @return [type]                 [description]
 */
function resource_feedback_ajax_page($bundle, $node, $state, $trigger_id, $entity_id = NULL) {
  $commands = dialog_show_form('feedback_' . $bundle . '_form', $node, $state, $trigger_id, $entity_id);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
}

/**
 * Callback for /node/###/feedback/redirect/ABC
 *
 * Browsers can be a pain when doing JS redirects of  pages pointing to hash fragments, so it's
 * simpler to do a back-end redirect.
 *
 * @param  [type] $node [description]
 * @param  [type] $tab  [description]
 * @return [type]       [description]
 */
function resource_redirect_page($node, $tab) {
  drupal_goto('node/' . $node->nid, array(
    'fragment' => $tab,
  ));
}

/*----------------------------------------------------------------------------
      HELPERS / INTERNAL
----------------------------------------------------------------------------*/

/**
 * Generates a modal-triggering "start review" link.
 * @param  [type] $node [description]
 * @param  [type] $type [description]
 * @return [type]       [description]
 */
function _feedback_start_review_link($node, $type) {
  if ($type == 'gate_keeper') {
    $stub = 'gate-keeper';

    if (!resource_access('start gate keeper', $node)) {
      return '';
    }
  }
  elseif ($type == 'post') {
    $stub = 'post';

    if (!resource_access('start post', $node)) {
      return '';
    }
  }
  else {
    return '';
  }


  static $count;
  if (is_null($count)) {
    $count = 1;
  }
  else {
    $count++;
  }

  $trigger_id = $stub . '-trigger-' . $count;

  drupal_add_library('dialog', 'dialog');
  $link_text = t('Start Review (!hours hrs)', array('!hours' => FEEDBACK_REVIEW_TIMEOUT));
  $content = l($link_text, 'node/' . $node->nid . '/feedback/' . $stub . '/start/' . $trigger_id, array(
    'attributes' => array(
      'class' => array(
        'use-ajax',
        'use-dialog',
      ),
      'id' => $trigger_id,
    ),
   ));

  return $content;
}











