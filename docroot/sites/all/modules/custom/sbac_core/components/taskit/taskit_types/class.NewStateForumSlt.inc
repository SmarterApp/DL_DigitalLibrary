<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class NewStateForumSlt extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));

    if ($forum && $account) {
      $this->setTaskUrl('forums/term/' . $forum->tid);

      $output = array();
      $output[] = t('A forum !title was created by a user in your state. You will have moderation rights to this forum. Join group !here.', array(
        '!title' => '<span class="taskit-title">' . $forum->name . '</span>',
        '!here' => '<span class="taskit-title">here</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}