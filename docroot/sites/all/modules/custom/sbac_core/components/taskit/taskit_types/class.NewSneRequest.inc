<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class NewSneRequest extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $webform  = node_load(current($entities['node']));
    $account  = user_load(current($accounts));
    $triggering_users = $this->getTriggeringUsers();

    if ($webform && $account) {
      $sid = sbac_sne_webform_get_submission_id(current($triggering_users));
      $this->setTaskUrl('node/' . $webform->nid . '/submission/' . $sid->sid);

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