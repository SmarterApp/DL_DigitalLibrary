<?php
namespace sbac_core\components\feedback\section;

class SectionQc extends Base {
  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $output = '';

    drupal_add_js(drupal_get_path('module', 'sbac_core') . '/components/feedback/js/feedback_qc.js');

    if (!$output = $this->getEntityForm('qc', 'quality review readonly')) {
      if ($intro = variable_get('resource_review_intro', '')) {
        $output .= '<div class="gate-keeper-intro">' . filter_text($intro) . '</div>';
      }
      
      $output .= $this->getStartLink();
    }

    $output = '<div class="feedback-wrap" id="feedback-wrap-qcr">' . $output . '</div>';

    return $output;
  }
}

