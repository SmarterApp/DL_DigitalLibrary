<?php
namespace sbac_core\components\input_format;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_element_info_alter().
   *
   * Adds new filter process callback to text areas with input selector to
   * selectively force Full HTML format.
   */
  function hook_element_info_alter(&$type) {
    if (!isset($type['text_format']['#process'])) {
      return;
    }

    // our process callback must run immediately after filter_process_format().
    $filter_process_format_location = array_search('filter_process_format', $type['text_format']['#process']);
    
    $replacement = array(
      'filter_process_format',
      'input_format_force_full_html'
    );

    array_splice($type['text_format']['#process'], $filter_process_format_location, 1, $replacement);
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}