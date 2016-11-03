<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class PostRemovedCreator extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {

    $node = node_load(current($entities['node']));
    $comment = comment_load(current($entities['comment']));
    $account = user_load(current($accounts));
    if ($node && $accounts) {

      $query = db_select('eck_flag', 'ef');
      $query->fields('ef', array('moderation_comment'));
      $query->distinct();
      $query->condition('nid', $node->nid, '=');
      $query->condition('target_id', $comment->cid, '=');
      $query->orderBy('created', 'DESC');
      $results = $query->execute();
      $message = $results->fetchAssoc();
      $message = array_pop($message);

      $triggering_users = $this->getTriggeringUsers();
      $output = t('Your post in !title has been removed by !moderator', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        '!moderator' => '<span class="taskit-moderator">' . sbac_forum__api__get_authpane_hoverover(current($triggering_users)) . '</span>',
      ));

      $output .= ' <span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
      $output .= '<div class="taskit-topic-removed-message">' . $message . '</div>';
      $output = '<div class="taskit-forum-cont">' . $output . '</div>';
      return $output;
    }

    return '';
  }

}