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
    $output = 'Brandilly';
    return $output;
  }
}

