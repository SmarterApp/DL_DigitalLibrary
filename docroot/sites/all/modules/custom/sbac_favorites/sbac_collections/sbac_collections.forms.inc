<?php
/**
 * @file
 * Code for the SBAC collection feature.
 */

/**
 * Implements hook_form_alter().
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function sbac_collections_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id === 'collection_node_form') {
        _sbac_resource_form_flatten_term_tree($form, $form_state);
    }
}
