<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ResourceRejectedReviewer extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      $output = array();
      $output[] = t('!title, a resource you reviewed, was returned to the submitter', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
      $output[] = '<div class="taskit-content-toggle">details...</div>';

      return $this->linkDisplay($output);
    }

    return '';
  }
}