<?php
namespace sbac_core\components\feedback\sections;

class About extends Base {
  const name = 'about';
  const title = 'About This Resource';
  const permission = 'view about';

  /**
   * Returns a modal-triggering "start review" link.
   * @return [type]       [description]
   */
  public function getStartLink($stub, $machine_name) {
    if (!resource_access('start gate keeper', $this->_node)) {
      return '';
    }

    return parent::getStartLink('gate-keeper', 'about');
  }

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    drupal_add_js(drupal_get_path('module', 'sbac_core') . '/components/feedback/js/feedback_about.js');

    $output = '';
    $teaser = node_view($this->_node, 'secondary_teaser');
    $output .= drupal_render($teaser);

    return $output;
  }
}

