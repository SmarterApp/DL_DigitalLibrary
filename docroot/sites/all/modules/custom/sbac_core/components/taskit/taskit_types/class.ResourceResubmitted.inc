<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ResourceResubmitted extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node = node_load(current($entities['node']));
    $account = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      global $user;

      $output = array();
      if ($node->uid == $user->uid) {
        $output[] = t('You re-submitted !title.', array(
          '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        ));
      }
      else {
        $output[] = t('!title, a resource you reviewed, was re-submitted.', array(
          '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        ));
      }
      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format) . '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}