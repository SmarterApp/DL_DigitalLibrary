<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class DeletedTopicNode extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $topic    = taxonomy_term_load(current($entities['node']));
    $account  = user_load(current($accounts));


    if ($forum && $account) {
      $redirect_url = 'forums/term/' . $forum->tid;
      $this->setTaskUrl($redirect_url);

      $output = array();
      $output[] = t('A Facilitator for !forumname has deleted a discussion topic !title, a topic you created.', array(
        '!forumname' => '<span class="taskit-title">' . $forum->name . '</span>',
        '!title' => '<span class="taskit-title">' . $topic->title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
