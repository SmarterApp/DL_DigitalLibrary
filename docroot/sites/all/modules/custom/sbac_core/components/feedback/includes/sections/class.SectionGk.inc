<?php
namespace sbac_core\components\feedback\section;

class SectionGk extends Base {
  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $output = '';

    drupal_add_js(drupal_get_path('module', 'sbac_core') . '/components/feedback/js/feedback_gate_keeper.js');

    // TODO: permission 'gate keeper readonly' doesn't exist
    if (!$output = $this->getEntityForm('gate_keeper', 'gate keeper readonly')) {
      if ($intro = variable_get('resource_gate_keeper_help', '')) {
        $output .= '<div class="gate-keeper-intro">' . filter_text($intro) . '</div>';
      }
      
      $output .= $this->getStartLink();
    }

    $output = '<div class="feedback-wrap" id="feedback-wrap-gk">' . $output . '</div>';

    return $output;
  }
}

