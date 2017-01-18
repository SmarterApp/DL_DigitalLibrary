<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class NewSneReauest extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $webform  = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($webform && $account) {
      $this->setTaskUrl('node/' . $webform->nid . '/webform-results');

      $output = array();
      $output[] = t('A new SNE request has been submitted, click !here to review', array(
        '!here' => '<span class="taskit-title">here</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      return $this->linkDisplay($output);
    }

    return '';
  }
}