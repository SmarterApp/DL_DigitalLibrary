<?php
namespace sbac_core\components\feedback\section;

class SectionTags extends Base {
  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    return $this->_node->nid;
  }
}

