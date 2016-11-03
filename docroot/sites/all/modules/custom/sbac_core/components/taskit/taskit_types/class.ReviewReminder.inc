<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ReviewReminder extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      $viewing_account = current_user();

      $feedback = entity_load('feedback', FALSE, array(
        'node_id' => $node->nid,
        'type' => 'post',
      ));

      $output = array();
      $output[] = t('You have !hours hours left to complete the review for !title', array(
        '!hours' => FEEDBACK_REVIEW_REMINDER,
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}