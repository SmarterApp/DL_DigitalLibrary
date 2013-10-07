<?php

/**
 * AJAX callback for /node/###/review/*
 * @param  [type] $bundle     [description]
 * @param  [type] $node       [description]
 * @param  [type] $state      [description]
 * @param  [type] $trigger_id [description]
 * @param  [type] $id         [description]
 * @return [type]             [description]
 */
function resource_review_ajax_page($bundle, $node, $state, $trigger_id, $id = NULL) {
  $commands = dialog_show_form('review_' . $bundle . '_form', $node, $state, $trigger_id, $id);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
}

