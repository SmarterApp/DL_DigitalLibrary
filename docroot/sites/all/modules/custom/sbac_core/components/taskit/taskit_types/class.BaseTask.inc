<?php
namespace taskit\sbac_core;

class BaseTask extends \taskit\Task {
  protected $_task_url = '';

  /**
   * Sets the task's URL.
   * @param [type] $url [description]
   */
  public function setTaskUrl($url) {
    $this->_task_url = $url;
  }

  /**
   * Wraps output in anchor tag.
   * @param  [type] $output [description]
   * @return [type]         [description]
   */
  public function linkDisplay($output) {
    $output = implode(' ', $output);

    return l($output, $this->_task_url, array(
      'html' => TRUE, 
      'attributes' => array(
        'class' => array(
          'taskit-content',
        ),
      ),
    ));
  }

  public function contributorFeedback($resource_nid, $viewing_uid) {
    $posts = entity_load('feedback', FALSE, array(
      'node_id' => $resource_nid,
      'type' => 'post',
      'completed' => 1,
      'status' => 1,
    ));

    $post = array_shift($posts);

    return field_get_value($post, 'field_to_contributor');
  }

  public function reviewerFeedback($resource_nid, $viewing_uid) {
    $posts = entity_load('feedback', FALSE, array(
      'node_id' => $resource_nid,
      'type' => 'post',
      'completed' => 1,
      'status' => 1,
    ));

    $post = array_shift($posts);

    $reviews = entity_load('feedback', FALSE, array(
      'node_id' => $resource_nid,
      'type' => 'review',
      'completed' => 1,
      'status' => 1,
    ));

    $i = 0;
    foreach ($reviews as $review) {
      $i++;

      if ($viewing_uid == $review->uid) {
        break;
      }
    }

    $content = '';
    if ($i) {
      $content = field_get_value($post, 'field_to_reviewer_' . $i);
    }

    return $content;
  }
}
