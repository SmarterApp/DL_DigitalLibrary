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
    $forum_id = sbac_forum_get_resource_forum($this->_node->nid);
    $output = views_embed_view('forum_topic_list', 'collaboration', $forum_id);
    return $output;
  }
}

