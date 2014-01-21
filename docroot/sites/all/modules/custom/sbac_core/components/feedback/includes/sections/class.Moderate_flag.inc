<?php
namespace sbac_core\components\feedback\sections;

class Moderate_flag extends Base {
  const name = 'Moderate_flag';
  const title = 'Resource Flags';
  const permission = 'access moderate flag';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $flags = sbac_flag_get_all_flags_for_node($this->_node, 'resource');
    $output = '';
    if ($flags) {
      $output = sbac_flag_resource_profile_view($flags);
    }
    return $output;
  }
}

