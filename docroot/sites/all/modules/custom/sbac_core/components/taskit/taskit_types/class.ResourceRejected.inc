<?php
namespace taskit\sbac_core;
      
require_once('class.BaseTask.inc');

class ResourceRejected extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));
    if (isset($entities['feedback'])) {
      $feedback = $entities['feedback'];
      if ($node && $account) {
        $this->setTaskUrl('node/' . $node->nid);

        global $user;
        $output = array();
        if ($node->uid == $user->uid) {
          $output[] = t('!title was returned to you for revision', array(
            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
          ));

          $details = $this->contributorFeedback($node->nid, $user->uid, $feedback);
        }
        else {
          $output[] = t('!title, a resource you reviewed, was returned to the submitter', array(
            '!title' => '<span class="taskit-title">' . $node->title. '</span>',
          ));

          $details = $this->reviewerFeedback($node->nid, $user->uid, $feedback);
        }

        // $this->addClass('taskit-collapsed');

        drupal_add_library('system', 'drupal.ajax');
        $trigger = l('', '', array('attributes' => array(
          'class' => array(
            'taskit-expand-trigger',
            'use-ajax',
          ),
        )));

        $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
        if ($details) {
          $output[] = '<div class="taskit-content-toggle">' . $details . '</div>';
        }
        return $this->linkDisplay($output);
      }
    }

    return '';
  }
}
