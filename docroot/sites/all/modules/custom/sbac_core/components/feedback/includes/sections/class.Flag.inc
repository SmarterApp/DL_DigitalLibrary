<?php
namespace sbac_core\components\feedback\sections;

class Flag extends Base {
  const name = 'flag';
  const title = 'Flag';
  const permission = 'access flag';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    drupal_add_js(drupal_get_path('module', 'sbac_flag') . '/js/sbac_flag.js');
    drupal_add_css(drupal_get_path('module', 'sbac_core') . '/components/flag/css/flag.css');
    $output = sbac_flag_resource($this->_node);
    return $output;
  }
}

