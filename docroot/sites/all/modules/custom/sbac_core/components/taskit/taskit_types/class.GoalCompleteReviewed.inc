<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class GoalCompleteReviewed extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $account  = user_load(current($accounts));
    $rating_goal = $account->field_resources_reviewed_goal['und'][0]['value'];
    if ($account) {
      $url = url('user/' . $account->uid, array('fragment' => 'profile-goals'));
      $this->setTaskUrl($url);

      $output = array();
      $output[] = t('Congratulations: You have reached your goal for resources reviewed! !goal_page', array(
        '!goal_page' => '<span class="taskit-title">View your goals to increase your goal number.</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
