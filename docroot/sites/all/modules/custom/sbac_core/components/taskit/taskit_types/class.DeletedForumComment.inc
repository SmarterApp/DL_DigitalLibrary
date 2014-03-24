<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class DeletedForumComment extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $topic    = node_load(current($entities['node']));
    $account  = user_load(current($accounts));
    $forum_name = '';

    if ($topic && $account) {
      $redirect_url = 'node/' . $topic->nid;
      $this->setTaskUrl($redirect_url);

      $topic_title = $topic->title;

      $output = array();
      $output[] = t('A facilitator has deleted a forum reply in !title.', array(
        '!title' => '<span class="taskit-title">' . $topic_title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
