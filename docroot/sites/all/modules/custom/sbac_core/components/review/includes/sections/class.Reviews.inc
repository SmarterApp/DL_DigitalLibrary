<?php
namespace sbac_core\components\review\sections;

class Reviews extends Base {
  const name = 'reviews';
  const title = 'Reviews';
  const permission = 'view reviews';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $output = '';

    $output .= '
                  <div class="review-form-header">
                    <div class="section-title">' . t('Tell us what you think of this resource') . '</div>
                    <a href="#" class="review-form-trigger button medium">' . t('Write your review') . '</a>
                    <div class="clear"></div>
                  </div>
               ';

    $output .= $this->getNewEntityForm('review', 'end_use');

    $output = '<div class="review-wrap" id="review-wrap-reviews">' . $output . '</div>';

    return $output;
  }
}

