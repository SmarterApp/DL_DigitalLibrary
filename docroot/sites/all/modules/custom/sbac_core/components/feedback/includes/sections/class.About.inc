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
  public function getStartLink($stub = '', $machine_name = '') {
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
    $output = '<div class="glossary-link-container"><a href="/glossary" class="glossary-link" target="_blank">Glossary Of Terms</a></div>';
    $output .= theme('sbac_resource_profile', array('node' => $this->_node));
    return $output;
  }
}

