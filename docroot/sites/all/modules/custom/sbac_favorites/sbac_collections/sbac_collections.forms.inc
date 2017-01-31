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
  if ($form_id !== 'collection_node_form') {
    return;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function sbac_collections_form_collection_node_form_alter(&$form, &$form_state, $form_id) {
  _sbac_resource_form_flatten_term_tree($form, $form_state);

  $form['additional_settings']['#access'] = false;

  $form['tags'] = array(
    '#type' => 'markup',
    '#markup' => '<h2>Add Tags</h2>',
    '#weight' => 10,
  );
  $form['field_subject']['#weight'] = 20;
  $form['field_grades']['#weight'] = 30;

  if ($form['actions']['delete']) {
    $form['actions']['delete']['#attributes'] = array(
      'class' => array(
        'delete-btn',
        'red',
        'button',
      ),
    );
    $form['actions']['delete']['#weight'] = -100;
  }

  if (!empty($form_state['ajax']) && $form_state['ajax']) {
    $form['actions']['close'] = array(
      '#type' => 'button',
      '#button_type' => 'no-submit',
      '#access' => true,
      '#value' => t('Close'),
      '#attributes' => array(
        'class' => array(
          'close-btn',
          'blue',
          'button',
        ),
        'onclick' => 'Drupal.CTools.Modal.dismiss();',
      ),
      '#weight' => 1,
    );
  }

//  $form['actions']['continue'] = array(
//    '#type' => 'button',
//    '#access' => true,
//    '#value' => t('Continue'),
//    '#attributes' => array(
//      'class' => array(
//        'continue-btn',
//        'green',
//        'button',
//      ),
//    ),
//    '#weight' => 100,
//  );

  if ($form['actions']['submit']) {
    $form['actions']['submit']['#attributes'] = array(
      'class' => array(
        'continue-btn',
        'green',
        'button',
      ),
      'data-edit' => 'testing',
    );
    $form['actions']['submit']['#value'] = 'Continue';
    $form['actions']['submit']['#weight'] = 100;
  }
}
