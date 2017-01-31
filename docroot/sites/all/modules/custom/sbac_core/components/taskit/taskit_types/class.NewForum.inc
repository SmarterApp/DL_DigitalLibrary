<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class NewForum extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));

    if ($forum && $account) {
      $this->setTaskUrl('forums/term/' . $forum->tid);

      $output = array();
      $output[] = t('You have created a new forum !title! You will be responsible for moderating its content.', array(
        '!title' => '<span class="taskit-title">' . $forum->name . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}