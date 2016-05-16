<?php
namespace sbac_core\components\feedback\sections;

abstract class Base extends \sbac_core\components\sections\Base {
  /**
   * Access check for entire Section.
   * @return [type] [description]
   */
  public function access() {
    if (parent::access()) {
      return TRUE;
    }

    return resource_access($this::permission, $this->_node, $this->_account);
  }

  /**
   * Returns a modal-triggering "start review" link.
   * @return [type]       [description]
   */
  public function getStartLink($stub = '', $machine_name = '') {
    $counter = &drupal_static(__FUNCTION__);

    if (is_null($counter)) {
      $counter = 0;
    }

    $trigger_id = $stub . '-trigger-' . $counter++;

    drupal_add_library('dialog', 'dialog');
    $link_text = t('Start Review (!hours hours)', array('!hours' => FEEDBACK_REVIEW_TIMEOUT));
    $content = l($link_text, 'node/' . $this->_node->nid . '/feedback/' . $stub . '/start/' . $trigger_id, array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'dialog-trigger-' . $machine_name,
          'button',
          'medium',
        ),
        'id' => $trigger_id,
      ),
    ));

    return $content;
  }

  /**
   * Returns a rendered entity-edit form if there is an existing entity.
   * @param  [type] $bundle        [description]
   * @return [type]                [description]
   */
  public function getEntityForm($bundle) {
    $output = '';

    $id = db_select('eck_feedback', 'eckf')
        ->fields('eckf', array('id'))
        ->condition('type', $bundle)
        ->condition('node_id', $this->_node->nid)
        ->condition('status', 1)
        ->condition('uid', $this->_account->uid)
        ->execute()
        ->fetchField();

    if ($id) {
      $entity = entity_load_single('feedback', $id);

      // we may want to override access with a readonly permission
      if ($entity->completed && !$this->access()) {
        $this->_access_override = TRUE;
      }

      $form = eck__entity__edit('feedback', $bundle, $id);
      $output = drupal_render($form);
    }

    return $output;
  }
}

