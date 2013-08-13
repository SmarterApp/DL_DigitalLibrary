<?php
namespace sbac_core\components\feedback\section;

class SectionAbout extends Base {
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

