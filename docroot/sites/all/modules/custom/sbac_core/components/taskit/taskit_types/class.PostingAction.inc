<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class PostingAction extends \taskit\sbac_core\BaseTask {
  // We're not using this anymore.  This notification has been broken up into individual notifications
  public function display($entities, $accounts) {
//    $node     = node_load(current($entities['node']));
//    $account  = user_load(current($accounts));

//    if ($node && $account) {
//      $this->setTaskUrl('node/' . $node->nid);
//      $output = array();
//
//      switch ($node->field_posting_options['und'][0]['value']) {
//        case 0: // Post without distinction
//          $output[] = t('!title was demoted (posted without distinction) by the :username', array(
//            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
//            ':username' => $account->name,
//          ));
//          break;
//        case 1: // Post with distinction
//          $output[] = t('!title was promoted (posted with distinction) by the :username', array(
//            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
//            ':username' => $account->name,
//          ));
//          break;
//        case 2:
//          $output[] = t('!title was removed by the :username', array(
//            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
//            ':username' => $account->name,
//          ));
//          break;
//        case 3:
//          // The UI does not provide a comment when 3 is selected.
//          break;
//      }
//
//
//      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
//      $details = $node->field_posting_options_comment['und'][0]['value'];
//      $output[] = '<div class="taskit-content-toggle">' . $details . '</div>';
//
//      return $this->linkDisplay($output);
//    }

    return '';
  }
}