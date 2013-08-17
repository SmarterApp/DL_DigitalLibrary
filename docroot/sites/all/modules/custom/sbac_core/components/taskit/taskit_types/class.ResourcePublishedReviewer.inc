<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ResourcePublishedReviewer extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      $output = array();
      $output[] = t('!title, a resource you reviewed, was posted to the Digital Library', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . date($this->_date_format, $this->_created). '</span>';

      return $this->linkDisplay($output);
    }

    return '';
  }
}