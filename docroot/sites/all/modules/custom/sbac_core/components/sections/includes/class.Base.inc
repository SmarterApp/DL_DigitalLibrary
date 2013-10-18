<?php
namespace sbac_core\components\sections;

abstract class Base implements iSection {
  protected $_node = NULL;
  protected $_node_state = NULL;
  protected $_account = NULL;

  protected $_show_disabled = FALSE;
  protected $_access_override = NULL;

  /**
   * Constructor
   * @param [type] $node    [description]
   * @param [type] $account [description]
   */
  public function __construct($node, $account) {
    $this->_node = $node;
    $this->_account = $account;

    if (isset($node->workbench_moderation['current']->state)) {
      $this->_node_state = $node->workbench_moderation['current']->state;
    }

    $this->init();
  }

  /**
   * Post-constructor initialization/setup
   * @return [type] [description]
   */
  protected function init() {

  }

  /**
   * Access check for entire Section.
   * @return [type] [description]
   */
  public function access() {
    if (isset($this->_access_override) && !is_null($this->_access_override)) {
      return $this->_access_override;
    }

    return FALSE;
  }

  /**
   * Flag to show the Section as disabled when access is denied.
   * @return [type] [description]
   */
  public function show_disabled() {
    return $this->_show_disabled;
  }

  /**
   * Returns a rendered entity-edit form.
   * @param  [type] $type   [description]
   * @param  [type] $bundle [description]
   * @return [type]         [description]
   */
  public function getNewEntityForm($type, $bundle) {
    $output = '';

    $form = eck__entity__add($type, $bundle);
    $output = drupal_render($form);

    return $output;
  }

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  abstract public function getContent();
}

