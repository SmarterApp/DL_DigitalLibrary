<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ResourceRated extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);
      $review_type = '';

      $output = array();

      $output[] = t('A !reviewtype for !title was posted', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        '!reviewtype' => '<span class="taskit-title">New Review</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
      return $this->linkDisplay($output);
    }
    else {
      return '';
    }
  }
}
