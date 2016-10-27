<?php
namespace sbac_core\components\feedback\sections;

class Gk extends Base {
  const name = 'gk';
  const title = 'Gate-Keeping Criteria Review';
  const permission = 'view gate keeper';

  /**
   * Returns a modal-triggering "start review" link.
   * @return [type]       [description]
   */
  public function getStartLink($stub = '', $machine_name = '') {
    if (!resource_access('start gate keeper', $this->_node)) {
      return '';
    }

    return parent::getStartLink('gate-keeper', 'gk');
  }

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $output = '';

    drupal_add_js(drupal_get_path('module', 'sbac_core') . '/components/feedback/js/feedback_gate_keeper.js');

    if (!$output = $this->getEntityForm('gate_keeper')) {
      if ($intro = variable_get('resource_gate_keeper_help', '')) {
        $output .= '<div class="gate-keeper-intro">' . filter_text($intro) . '</div>';
      }

      $output .= $this->getStartLink();
    }

    $output = '<div class="feedback-wrap" id="feedback-wrap-gk">' . $output . '</div>';

    return $output;
  }
}

