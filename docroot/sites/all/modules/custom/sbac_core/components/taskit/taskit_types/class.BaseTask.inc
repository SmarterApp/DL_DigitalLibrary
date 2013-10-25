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

  public function contributorFeedback($resource_nid, $viewing_uid, $feedback) {
    $post = FALSE;
    foreach (entity_load('feedback', array_values($feedback)) as $entity) {
      if ($entity->type == 'post') {
        $post = $entity;
      }
    }

    if (!$post) {
      return '';
    }

    return field_get_value($post, 'field_to_contributor');
  }

  public function reviewerFeedback($resource_nid, $viewing_uid, $feedback) {
    $post = FALSE;
    foreach (entity_load('feedback', array_values($feedback)) as $entity) {
      if ($entity->type == 'post') {
        $post = $entity;
      }
    }

    if (!$post) {
      return '';
    }

    $i = 0;
    foreach (entity_load('feedback', array_values($feedback)) as $entity) {
      $i++;

      if ($entity->type == 'qc' && $viewing_uid == $entity->uid) {
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
