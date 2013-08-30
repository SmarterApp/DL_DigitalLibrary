<?php
/**
 * @file
 * Views related code for the SBAC resource feature.
 */

/**
 * Implements hook_views_query_alter().
 *
 * @param $view
 * @param $query
 */
function sbac_resource_views_query_alter(&$view, &$query) {
  if ($view->name == 'resources' || $view->name == 'all_resources') {
    global $user;
    if (in_array('resource contributor', $user->roles)) {
      // Can't see "being reviewed" state. Anything less
      // would be uncivilized. Gilette! The best a man can get.
      //unset($query->where[1]['conditions'][3]['value'][2]);
    }
    if (in_array('resource reviewer', $user->roles)) {
      // Can see needs review, being reviewed and published.
      unset($query->where[1]['conditions'][3]['value'][0]);
      unset($query->where[1]['conditions'][3]['value'][3]);
      unset($query->where[1]['conditions'][3]['value'][4]);
      unset($query->where[1]['conditions'][4]);
    }
    if (in_array('resource publisher', $user->roles)) {
      // Can see approved, published
      unset($query->where[1]['conditions'][3]['value'][0]);
      unset($query->where[1]['conditions'][3]['value'][1]);
      unset($query->where[1]['conditions'][3]['value'][2]);
      unset($query->where[1]['conditions'][3]['value'][3]);
      unset($query->where[1]['conditions'][4]);
    }
  }
}

/**
 * Implements hook_views_pre_render().
 *
 * @param $view
 */
function sbac_resource_views_pre_render(&$view) {
  if ($view->name == 'resources' || $view->name == 'all_resources') {
    global $user;
    if (in_array('resource reviewer', $user->roles)) {
      foreach ($view->result as $key => $result) {
        if (isset($result->workbench_moderation_node_history_state) && $result->workbench_moderation_node_history_state == 'being_reviewed') {
          // Do not show nodes to resource reviewer when the node is in the process of the gate keeper review.
          $gate_keeper = _sbac_resource_determine_feedback($result->nid, 'gate_keeper', $user->uid, 1, 0, 1, 'set', TRUE);
          if ($gate_keeper) {
            unset($view->result[$key]);
          }
          // Do not show nodes to resource reviewers when the node is being reviewed by 3 people.
          $feedback = _sbac_resource_determine_feedback($result->nid, 'review', $user->uid, 1, FALSE, 1, 'set', TRUE);
          if (count($feedback) == 3) {
            unset($view->result[$key]);
          }
          // Do not show nodes to the resource reviewers when the node has been reviewed by this person and is complete.
          $feedback = _sbac_resource_determine_feedback($result->nid, 'review', $user->uid, 1, 1, FALSE, 'single');
          if ($feedback) {
            unset($view->result[$key]);
          }
        }
      }
    }
    if (in_array('resource publisher', $user->roles)) {
      foreach ($view->result as $key => $result) {
        if (isset($result->workbench_moderation_node_history_state) && $result->workbench_moderation_node_history_state == 'approved') {
          // Do not show nodes to the resource publishers when the node has been reviewed by another resource publisher
          $feedback = _sbac_resource_determine_feedback($result->nid, 'post', $user->uid, 1, 0, 1, 'set', TRUE);
          if ($feedback) {
            unset($view->result[$key]);
          }
        }
      }
    }
  }
}

/**
 * Implements hook_views_default_views_alter().
 *
 * @param $views
 */
function sbac_resource_views_default_views_alter(&$views) {
  if (isset($views['help_topics'])) {
    $welcome_tutorial = taxonomy_get_term_by_name('Welcome Tutorial', 'help_page_topic');
    if ($welcome_tutorial) {
      $welcome_tutorial = array_shift($welcome_tutorial);
      $views['help_topics']->display['default']->display_options['filters']['field_help_page_topic_tid']['value'][$welcome_tutorial->tid] = $welcome_tutorial->tid;
      $views['help_topics']->display['block']->display_options['filters']['field_help_page_topic_tid']['value'][$welcome_tutorial->tid] = $welcome_tutorial->tid;
    }
  }

  if (isset($views['resource_tutorial'])) {
    $resource_tutorial = taxonomy_get_term_by_name('Resource Tutorial', 'help_page_topic');
    if ($resource_tutorial) {
      $resource_tutorial = array_shift($resource_tutorial);
      $views['resource_tutorial']->display['default']->display_options['filters']['field_help_page_topic_tid']['value'][$resource_tutorial->tid] = $resource_tutorial->tid;
      $views['help_topics']->display['page_1']->display_options['filters']['field_help_page_topic_tid']['value'][$resource_tutorial->tid] = $resource_tutorial->tid;
    }
  }
}