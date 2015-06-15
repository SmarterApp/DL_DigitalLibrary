<?php
namespace taskit\sbac_core;

require_once('class.BaseTask.inc');

class RecommendedForumComment extends \taskit\sbac_core\BaseTask {
  public function display($entities, $accounts) {
    $topic = node_load(current($entities['node']));
    $comment = comment_load(current($entities['comment']));
    if ($comment) {
      $account = user_load(current($accounts));
      if ($topic && $account) {
        $topic_wrapper = entity_metadata_wrapper('node', $topic);
        try {
          $type = 'in forum';
          $forum_wrapper = $topic_wrapper->field_topic_forum_parent;
          $link = l($forum_wrapper->name->value(), 'forums/term/' . $forum_wrapper->tid->value());
          if ($resource = $forum_wrapper->field_forum_resource_ref->value()) {
            $type = 'on resource';
            $link = l($resource->title, 'node/' . $resource->nid, array('fragment' => 'review-collaboration'));
          }
          $output = t('Your !post in discussion topic !topic !type !forum has been recommended', array(
            '!post' => l('post', 'node/' . $topic->nid, array('fragment' => 'comment-' . $comment->cid)),
            '!topic' => '<span class="taskit-title">' . l($topic_wrapper->title->value(), 'node/' . $topic->nid) . '</span>',
            '!type' => $type,
            '!forum' => '<span class="taskit-title">' . $link . '</span>',
          ));
          $output .= '<span class="taskit-timestamp">' . format_date($this->_created, 'custom', $this->_date_format) . '</span> ';
          $output = '<div class="taskit-forum-cont">' . $output . '</div>';
          return $output;
        } catch (\EntityMetadataWrapperException $e) {
          return '';
        }
      }
    }
    return '';
  }
}
