<?php
namespace sbac_core\components\feedback\sections;

class Share extends Base {
  const name = 'share';
  const title = 'Share';
  const permission = 'view share';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $form = drupal_get_form('sbac_share_resource_form', $this->_node);
    $output = drupal_render($form);
    return $output;
  }
}

