<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class RemovedForumMember extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $forum    = taxonomy_term_load(current($entities['taxonomy_term']));
    $account  = user_load(current($accounts));
    $removed_member = field_collection_item_load(current($entities['field_collection_item']));

    if ($forum && $account) {
      $this->setTaskUrl('forums');
      $message = '';

      if ($removed_member) {
        $removed_member_wrapper = entity_metadata_wrapper('field_collection_item', $removed_member);
        if (isset($removed_member_wrapper->field_fc_forum_member_removedmsg)) {
          $message = $removed_member_wrapper->field_fc_forum_member_removedmsg->value();
        }
      }

      $output = array();
      $output[] = t('A facilitator has removed you from this forum: !title', array(
        '!title' => '<span class="taskit-title">' . $forum->name . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format). '</span> ';

      $output[] = '<div class="taskit-content-toggle">' . $message . '</div>';

      return $this->linkDisplay($output);
    }

    return '';
  }
}
