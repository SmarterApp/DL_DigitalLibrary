<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class ForumFlagged extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $this->setTaskUrl('node/' . $node->nid);

      $forum = entity_load_single('taxonomy_term', $node->field_topic_forum_parent[LANGUAGE_NONE][0]['tid']);

      $output = array();
      $output[] = t('A post in discussion topic !title in Forum !forum was flagged and needs moderation.', array(
        '!title' => '<span class="taskit-title">' . $node->title . '</span>',
        '!forum' => '<span class="taskit-title">' . $forum->name . '</span>',
      ));

//      $flag = sbac_flag_get_user_flag($node->nid, $account->uid);
      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';
//      if ($flag) {
//        $output[] = '<div class="taskit-content-toggle">Comment provided by user who flagged: ' . $flag['flag_comment'] . '</div>';
//      }

      return $this->linkDisplay($output);
    }

    return '';
  }
}