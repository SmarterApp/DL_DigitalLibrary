<?php
namespace sbac_core\components\feedback\sections;

class Collaboration extends Base {
  const name = 'collaboration';
  const title = 'Collaboration';
  const permission = 'view collaboration';

  /**
   * Builds and returns the content for current section.
   * @return string [type] [description]
   */
  public function getContent() {
    $output = '';
    drupal_add_css(drupal_get_path('module', 'sbac_forum') . '/css/sbac_forum.css');
    $forum_id = sbac_forum_get_resource_forum_id($this->_node->nid);
    if ($forum_id) {
      $output = views_embed_view('forum_topic_list', 'collaboration', $forum_id);
    }
    return $output;
  }
}

