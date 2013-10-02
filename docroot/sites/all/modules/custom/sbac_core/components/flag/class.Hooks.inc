<?php
namespace sbac_core\components\flag;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'eck__entity__form_add_flag_review_end_use') {
      $form['#attached']['css'][] = $this->_path . '/css/flag.css';
      $form['#attached']['js'][] = $this->_path . '/js/flag.js';

      $form['#prefix'] = '<div class="flag-review-end-use-wrap">';
      $form['#suffix'] = '</div>';

      if ($node = current_node()) {
        $form['node_id']['#value'] = $node->nid;
        $form['node_id']['#access'] = FALSE;

        // print_rr($form);
        // exit();
      }
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /*----------------------------------------------------------------------------
      INTERNAL / HELPERS
  ----------------------------------------------------------------------------*/
}



