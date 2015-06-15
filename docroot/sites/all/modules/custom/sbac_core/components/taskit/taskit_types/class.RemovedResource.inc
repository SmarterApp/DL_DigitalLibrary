<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class RemovedResource extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node = node_load(current($entities['node']));
    $account = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);
      $output = array();
      $output[] = t('!title was removed by :username ', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        ':username' => $account->name,
      ));
      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format) . '</span> ';
      if (!empty($entities['feedback'])) {
        $feedback = entity_load_single('flag', current($entities['feedback']));
        $output[] = '<div class="taskit-content-toggle">' . $feedback->moderation_comment . '</div>';
      }
      elseif (!empty($node->field_posting_options_comment[LANGUAGE_NONE])) {
        // TODO: This is a known bug as field_posting_options_comment is always the current value. We want the revision value at the time of removal. We'll revisit this later
        $details = $node->field_posting_options_comment['und'][0]['value'];
        $output[] = '<div class="taskit-content-toggle">' . $details . '</div>';
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
