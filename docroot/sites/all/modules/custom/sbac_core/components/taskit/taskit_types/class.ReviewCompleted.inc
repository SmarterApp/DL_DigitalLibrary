<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ReviewCompleted extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));
    if (isset($entities['feedback'])) {
      $feedback_id = $entities['feedback'];
      $feedback_raw = entity_load('feedback', $feedback_id);
      if (!empty($feedback_raw)) {
        $feedback = array_shift($feedback_raw);
      }

      if ($node && $account && $feedback) {
        $this->setTaskUrl('node/' . $node->nid);
        $review_type = '';
        switch($feedback->type) {
          case 'gate_keeper':
            $review_type = 'Gate-Keeping Review';
            break;
          case 'qc':
            $review_type = 'Quality Criteria Review';
            break;
          case 'post':
            $review_type = 'Posting Review';
            break;
        }
        global $user;
        $output = array();
        if ($user->uid == $node->uid) {
          $output[] = t('A !reviewtype for !title was completed', array(
            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
            '!reviewtype' => '<span class="taskit-title">' . $review_type . '</span>',
          ));
        }
        else {
          $output[] = t('You completed a !reviewtype for !title', array(
            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
            '!reviewtype' => '<span class="taskit-title">' . $review_type . '</span>',
          ));
        }
        $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
        return $this->linkDisplay($output);
      }
    }

    return '';
  }
}
