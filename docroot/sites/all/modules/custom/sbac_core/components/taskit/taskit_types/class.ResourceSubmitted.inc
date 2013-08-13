<?php
namespace taskit\sbac_core;

class ResourceSubmitted extends \taskit\Task {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $path     = 'node/' . $node->nid;

      $output = array();
      $output[] = t('You submitted !title.', array(
        '!title' => '<span class="taskit-title">' .l( $node->title, 'node/' . $node->nid) . '</span>',
      ));

      $output[] = '<span class="taskit-timestamp">' . date($this->_date_format, $this->_created). '</span> ';

      return '<div class="taskit-content">' . implode(' ', $output) . '</div>';
    }

    return '';
  }
}