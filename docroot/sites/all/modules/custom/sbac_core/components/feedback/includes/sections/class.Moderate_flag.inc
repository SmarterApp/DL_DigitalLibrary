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
    $output = '';

    if ($_GET['flag'] == 'view-resource-review-flags' || $_GET['flag'] == 'resolve-resource-review-flags') {
      $review = TRUE;
      $flags = sbac_flag_get_all_flags_for_node($this->_node, 'review', $_GET['review']);
    }
    else {
      $review = FALSE;
      $flags = sbac_flag_get_all_flags_for_node($this->_node, 'resource');
    }

    if ($flags) {
      if ($review) {
        $output = sbac_flag_resource_review_profile_view($this->_node, $flags);
      }
      else {
        $output = sbac_flag_resource_profile_view($flags);
      }
    }

    return $output;
  }
}

