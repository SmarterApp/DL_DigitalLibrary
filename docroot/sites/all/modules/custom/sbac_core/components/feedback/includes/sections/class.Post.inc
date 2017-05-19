<?php
namespace sbac_core\components\feedback\sections;

class Post extends Base {
  const name = 'post';
  const title = 'Arbitration Review';
  const permission = 'view post';

  /**
   * Returns a modal-triggering "start review" link.
   * @return [type]       [description]
   */
  public function getStartLink($stub = '', $machine_name = '') {
    return parent::getStartLink('post', 'post');
  }

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $output = '';

    drupal_add_js(drupal_get_path('module', 'sbac_core') . '/components/feedback/js/feedback_post.js');

    if (!$output = $this->getEntityForm('post')) {
      if ($intro = variable_get('resource_post_help', '')) {
        $output .= '<div class="gate-keeper-intro">' . filter_text($intro) . '</div>';
      }

      $output .= $this->getStartLink();
    }

    $output = '<div class="feedback-wrap" id="feedback-wrap-post">' . $output . '</div>';

    return $output;
  }
}

