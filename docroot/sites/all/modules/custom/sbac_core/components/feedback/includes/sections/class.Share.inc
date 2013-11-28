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
    $output = sbac_share_resource_node_view($this->_node);
    return $output;
  }
}

