<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class RatingGoalComplete extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $account  = user_load(current($accounts));
    $rating_goal = $account->field_star_rating_goal['und'][0]['value'];
    if ($account) {
      $this->setTaskUrl('users/' . $account->uid . '#profile-goals');

      $output = array();
      $output[] = t('Congratulations: Your goal of !title resources rated has been met! !goal_page', array(
        '!title' => '<span class="taskit-title">' . $rating_goal . '</span>',
        '!goal_page' => '<span class="taskit-title">View your goals to increase your goal number.</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
