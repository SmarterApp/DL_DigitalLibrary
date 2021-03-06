<?php
namespace taskit\sbac_core;
      
require_once('class.BaseTask.inc');

class RemovedResourceReview extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);
      $output = array();
      $output[] = t('!title was removed by :username ', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        ':username' => $account->name,
      ));
      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
      $flags = sbac_flag_get_all_flags_for_node($node, 'review');
      if ($flags) {
        $flag = array_shift($flags);
        $comment = $flag->moderation_comment;
        $output[] = '<div class="taskit-content-toggle">' . $comment . '</div>';
      }
      return $this->linkDisplay($output);
    }

    return '';
  }
}
