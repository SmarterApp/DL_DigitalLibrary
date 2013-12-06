<?php
namespace sbac_core\components\feedback\sections;

class Related_Resources extends Base {
  const name = 'related_resources';
  const title = 'Related Resources';
  const permission = 'access related resources';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $output = sbac_resource_related_resources($this->_node->nid);
    return $output;
  }
}

