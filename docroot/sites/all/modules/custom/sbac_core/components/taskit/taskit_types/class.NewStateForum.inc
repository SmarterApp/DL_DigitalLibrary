<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class NewStateForum extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('forums/term/' . $forum->tid);

      $output = array();
      $output[] = t('A new State forum for your state has been created', array(
        '!title' => '<span class="taskit-title">' . $forum->title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}