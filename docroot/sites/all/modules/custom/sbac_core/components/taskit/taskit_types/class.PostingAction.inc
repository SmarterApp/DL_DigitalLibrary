<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class PostingAction extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      $viewing_account = current_user();

      $output = array();
      $details = '';
      if ($node->uid == $viewing_account->uid) {
        $output[] = t('!title was posted to the Digital Library', array(
          '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        ));
        
        $details = $this->contributorFeedback($node->nid, $viewing_account->uid);
      }
      else {
        $output[] = t('!title, a resource you reviewed, was posted to the Digital Library', array(
          '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        ));

        $details = $this->reviewerFeedback($node->nid, $viewing_account->uid);
      }

      $output[] = '<span class="taskit-timestamp">' . date($this->_date_format, $this->_created). '</span>';

      if ($details) {
        $output[] = '<div class="taskit-content-toggle">' . $details . '</div>';
      }

      return $this->linkDisplay($output);
    }

    return '';
  }
}