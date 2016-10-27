<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class MostActiveMembersContributed extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $account = user_load(current($accounts));
    if ($account) {
      $homepage = variable_get('site_frontpage');
      $this->setTaskUrl(check_plain($homepage));

      $output = array();
      $output[] = t('Congratulations! You have been added to the !title for your number of resources contributed. Keep up the good work.', array(
        '!title' => '<span class="taskit-title">Most Active Members Board</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }
    return '';
  }
}
