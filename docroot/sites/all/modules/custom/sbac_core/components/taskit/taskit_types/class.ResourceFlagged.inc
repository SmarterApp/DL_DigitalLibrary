<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ResourceFlagged extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      $output = array();
      $output[] = t('The resource !title has been flagged as urgent and needs moderation.', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
      ));

//      $flag = sbac_flag_get_user_flag($node->nid, $account->uid);
      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
//      if ($flag) {
//        $output[] = '<div class="taskit-content-toggle">Comment provided by user who flagged: ' . $flag['flag_comment'] . '</div>';
//      }

      return $this->linkDisplay($output);
    }

    return '';
  }
}