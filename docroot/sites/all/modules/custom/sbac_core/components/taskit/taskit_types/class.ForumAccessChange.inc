<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ForumAccessChange extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));

    if ($forum && $account) {
      $this->setTaskUrl('forums');
      $message = 'You have been removed and no longer have access to this forum.';

      $output = array();
      $output[] = t('A Facilitator has changed the access criteria for this forum: !title', array(
        '!title' => '<span class="taskit-title">' . $forum->name . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      $output[] = '<div class="taskit-content-toggle">' . $message . '</div>';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
