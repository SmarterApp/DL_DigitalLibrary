<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class GoalCompleteContributed extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $account  = user_load(current($accounts));
    $rating_goal = $account->field_resources_posted_goal['und'][0]['value'];
    if ($account) {
      $user_name = str_replace(' ', '-', strtolower(sbac_user_format_username($account)));
      $user_name_clean = str_replace('.', '', $user_name);
      $this->setTaskUrl(check_plain('users/' . $user_name_clean . '#profile-goals'));

      $output = array();
      $output[] = t('Congratulations: You have reached your goal for resources contributed! !goal_page', array(
        '!goal_page' => '<span class="taskit-title">View your goals to increase your goal number.</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
