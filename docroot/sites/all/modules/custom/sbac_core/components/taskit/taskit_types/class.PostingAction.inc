<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class PostingAction extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);
      $output = array();

      $original_posting_option = $_SESSION['sbac-original-posting-option'];
      $posting_option = $_SESSION['sbac-posting-option'];
      $chosen_option = $posting_option;
      if ($original_posting_option == $posting_option) {
        $chosen_option = 3;
      }

      switch ($chosen_option) {
        case 0: // Post without distinction
          $output[] = t('!title was demoted (posted without distinction) by the :username', array(
            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
            ':username' => $account->name,
          ));
          break;
        case 1: // Post with distinction
          $output[] = t('!title was promoted (posted with distinction) by the :username', array(
            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
            ':username' => $account->name,
          ));
          break;
        case 2:
          $output[] = t('!title was removed by the :username', array(
            '!title' => '<span class="taskit-title">' . $node->title . '</span>',
            ':username' => $account->name,
          ));
          break;
        case 3:
          // The UI does not provide a comment when 3 is selected.
          break;
      }


      $output[] = '<span class="taskit-timestamp">' . date($this->_date_format, $this->_created). '</span>';
      $details = $_SESSION['sbac-posting-option-comment'];
      $output[] = '<div class="taskit-content-toggle">' . $details . '</div>';

      return $this->linkDisplay($output);
    }

    return '';
  }
}