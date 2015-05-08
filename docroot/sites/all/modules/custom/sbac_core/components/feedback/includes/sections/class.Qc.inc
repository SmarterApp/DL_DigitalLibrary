<?php
namespace sbac_core\components\feedback\sections;

class Qc extends Base {
  const name = 'qc';
  const title = 'Quality Criteria Review';
  const permission = 'view quality criteria';

  /**
   * Returns a modal-triggering "start review" link.
   * @return [type]       [description]
   */
  public function getStartLink($stub = '', $machine_name = '') {
    return parent::getStartLink('qc', 'qc');
  }

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

