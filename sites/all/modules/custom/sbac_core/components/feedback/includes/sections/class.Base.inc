<?php
namespace sbac_core\components\feedback\section;

class Base {
  protected $_section = NULL;
  protected $_machine_name = NULL;
  protected $_node = NULL;
  protected $_account = NULL;
  protected $_counter = 0;

  /**
   * Constructor.
   * @param [type] $node    [description]
   * @param [type] $account [description]
   */
  public function __construct($section) {
    // sanity checks
    if (!is_object($section)) {
      throw new \Exception(t('Section must be a valid object.'));
    }

    $this->_section      = $section;
    $this->_machine_name = $section->getMachineName();
    $this->_node         = $section->getControl()->getNode();
    $this->_account      = $section->getControl()->getAccount();
  }

  /**
   * Sets the counter.
   * @param [type] $counter [description]
   */
  public function setCounter($counter) {
    $this->_counter = $counter;
  }

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent () {
    return '';
  }

  /**
   * Returns a modal-triggering "start review" link.
   * @return [type]       [description]
   */
  public function getStartLink() {
    switch ($this->_machine_name) {
      case 'about':
      case 'gk':
        $stub  = 'gate-keeper';
        
        if (!resource_access('start gate keeper', $this->_node)) {
          return '';
        }

        break;

      case 'qc':
        $stub  = 'review';

        break;

      case 'post':
        $stub  = 'post';
        
        if (!resource_access('start post', $this->_node)) {
          return '';
        }

        break;

      default:
        return '';
    }

    $trigger_id = $stub . '-trigger-' . $this->_counter;

    drupal_add_library('dialog', 'dialog');
    $link_text = t('Start Review (!hours hrs)', array('!hours' => FEEDBACK_REVIEW_TIMEOUT));
    $content = l($link_text, 'node/' . $this->_node->nid . '/review/' . $stub . '/start/' . $trigger_id, array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'dialog-trigger-' . $this->_machine_name,
        ),
        'id' => $trigger_id,
      ),
     ));

    return $content;
  }

  /**
   * Returns a rendered entity-edit form if there is an existing entity.
   * @param  [type] $type          [description]
   * @param  [type] $readonly_perm [description]
   * @return [type]                [description]
   */
  public function getEntityForm($type, $readonly_perm = NULL) {
    $output = '';

    $id = db_select('eck_feedback', 'eckf')
            ->fields('eckf', array('id'))
            ->condition('type', $type)
            ->condition('node_id', $this->_node->nid)
            ->condition('status', 1)
            ->condition('uid', $this->_account->uid)
            ->execute()
            ->fetchField();

    if ($id) {
      $entity = entity_load_single('feedback', $id);

      // we may want to override access with a readonly permission
      if ($entity->completed && !$this->_section->access()) {
        // $this->_section->overrideAccess(resource_access($readonly_perm, $this->_node, $this->_account));
        
        // TODO: check this works as expected, then get rid of $readonly_perm
        $this->_section->overrideAccess(1);
      }

      $form = eck__entity__edit('feedback', $type, $id);
      $output = drupal_render($form);
    }

    return $output;
  }
}

