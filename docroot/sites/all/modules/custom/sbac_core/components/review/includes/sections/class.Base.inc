<?php
namespace sbac_core\components\review\sections;

abstract class Base extends \sbac_core\components\sections\Base {
  /**
   * Access check for entire Section.
   * @return [type] [description]
   */
  public function access() {
    if (parent::access()) {
      return TRUE;
    }

    return resource_access($this::permission, $this->_node, $this->_account);
  }
}

