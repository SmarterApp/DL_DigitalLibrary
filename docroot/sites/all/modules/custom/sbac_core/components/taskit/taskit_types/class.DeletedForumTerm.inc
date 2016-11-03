<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class DeletedForumTerm extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));

    if ($account) {
      $this->setTaskUrl('forums');

      $output = array();
      $output[] = t('A facilitator has deleted this forum: !title', array(
        '!title' => '<span class="taskit-title">' . $forum->name . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
