<?php
namespace sbac_core\components\feedback\section;

class SectionReviews extends Base {
  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    drupal_add_js(drupal_get_path('module', 'sbac_core') . '/components/feedback/js/feedback_reviews.js');

    $output = '';
    $output .= '<div class="section-title">' . t('Tell us what you think of this resource') . '</div>';
    $output .= '<a href="#" class="button medium review-form-trigger">' . t('Write your review') . '</a>';

    $output .= $this->getNewEntityForm('review', 'end_use');

    $output = '<div class="user-review-wrap" id="user-review-wrap-enduse">' . $output . '</div>';

    return $output; 
  }
}

