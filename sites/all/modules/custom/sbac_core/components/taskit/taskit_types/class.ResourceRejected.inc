<?php
namespace taskit\sbac_core;

class ResourceRejected extends \taskit\Task {
  public function display($entities, $accounts) {
    $node     = node_load(current($entities['node']));
    $account  = user_load(current($accounts));

    if ($node && $account) {
      $path     = 'node/' . $node->nid;

      $viewing_account = current_user();

      $output = array();
      if ($node->uid == $viewing_account->uid) {
        $output[] = t('!title was returned to you for revision', array(
          '!title' => '<span class="taskit-title">' .l($node->title, 'node/' . $node->nid) . '</span>',
        ));
      }
      else {
        $output[] = t('!title, a resource you reviewed, was returned to the reviewer', array(
          '!title' => '<span class="taskit-title">' .l($node->title, 'node/' . $node->nid) . '</span>',
        ));
      }

      // $this->addClass('taskit-collapsed');

      drupal_add_library('system', 'drupal.ajax');
      $trigger = l('', '', array('attributes' => array(
        'class' => array(
          'taskit-expand-trigger',
          'use-ajax',
        ),
      )));

      $output[] = '<span class="taskit-timestamp">' . date($this->_date_format, $this->_created). '</span>';
      // $output[] = '<span class="taskit-expand">' . $trigger . '</span>';
      // $output[] = '<div class="taskit-content-toggle">- comments from the three reviewers, or a link to the summary tab? - </div>';

      return '<div class="taskit-content">' . implode(' ', $output) . '</div>';
    }

    return '';
  }
}
