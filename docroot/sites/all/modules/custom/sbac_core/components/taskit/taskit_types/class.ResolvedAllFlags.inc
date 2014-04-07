<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ResolvedAllFlags extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);
      $output = array();
      $output[] = t('All flags have been resolved for the resource titled !title.', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
      ));
      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
      if (!empty($entities['feedback'])) {
        $feedback = entity_load_single('flag', current($entities['feedback']));
        $output[] = '<div class="taskit-content-toggle">' . $feedback->moderation_comment . '</div>';
      }
      $flags = sbac_flag_get_all_flags_for_node($node, 'resource');
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