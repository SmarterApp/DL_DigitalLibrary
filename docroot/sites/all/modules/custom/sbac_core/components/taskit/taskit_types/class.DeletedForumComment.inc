<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class DeletedForumComment extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    // $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));
    $forum_name = '';

    if ($account) {
      $this->setTaskUrl('forums');

      $output = array();
      $output[] = t('A Facilitator has deleted a forum reply.', array(
        '!title' => '<span class="taskit-title">' . $forum_name . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
