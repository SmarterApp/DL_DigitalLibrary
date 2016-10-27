<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class DeletedTopicNode extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum     = taxonomy_term_load(current($entities['taxonomy_term']));
    $topic_nid = current($entities['node']);
    $account   = user_load(current($accounts));

    if ($forum && $account) {
      $redirect_url = 'forums/term/' . $forum->tid;
      $this->setTaskUrl($redirect_url);

      $topic = sbac_forum__api__get_deleted_log_entry($topic_nid, 'node');
      $topic_title = ',';
      if (!empty($topic)) {
        $topic_title = ' ' . $topic['title'] . ',';
      }

      $output = array();
      $output[] = t('A facilitator for !forumname has deleted topic!title a topic you created.', array(
        '!forumname' => '<span class="taskit-title">' . $forum->name . '</span>',
        '!title' => '<span class="taskit-title">' . $topic_title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
