<?php
namespace taskit\sbac_core;

class ResourcePublishedReviewer extends \taskit\Task {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $path = 'node/' . $node->nid;

      $output = array();
      $output[] = t('!title, a resource you reviewed, was posted to the Digital Library', array(
        '!title' => '<span class="taskit-title">' .l( $node->title, 'node/' . $node->nid) . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . date($this->_date_format, $this->_created). '</span>';

      return '<div class="taskit-content">' . implode(' ', $output) . '</div>';
    }

    return '';
  }
}