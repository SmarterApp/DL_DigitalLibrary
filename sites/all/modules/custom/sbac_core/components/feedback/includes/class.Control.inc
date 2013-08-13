<?php
namespace sbac_core\components\feedback;

class Control {
  protected $_node = NULL;
  protected $_account = NULL;
  protected $_sections = array();

  /**
   * Constructor.
   * @param [type] $node [description]
   */
  public function __construct($node) {
    if (!is_object($node)) {
      throw new \Exception(t('Node must be a valid object.'));
    }

    $this->_node = $node;

    global $user;
    $this->_account = $user;
  }

  /**
   * Adds new section.
   * @param [type]  $process       [description]
   * @param [type]  $machine_name  [description]
   * @param [type]  $title         [description]
   * @param boolean $show_disabled [description]
   */
  public function addSection($process, $machine_name, $title, $show_disabled = FALSE) {
    // sanity checks  
      if (empty($process)) {
        throw new \Exception(t('Process cannot be empty.'));
      }

      if (empty($machine_name)) {
        throw new \Exception(t('Machine name cannot be empty.'));
      }

    // restrict machine names to not conflict with internal classes
      $reserved = array('');
      if (in_array($machine_name, $reserved)) {
        throw new \Exception(t('Cannot add section with the machine name %name.', array('%name' => $machine_name)));
      }

    // check general permissions to this process
      $permission = 'access ' . $process . ' process';
      if (!resource_access($permission, $this->_node, $this->_account)) {
        return;
      }

    // create individual section
      $section = new Section($process, $machine_name, $this);
 
      if ($show_disabled || $section->access()) {
        $this->_sections[$machine_name] = array(
          'title'     => $title,
          'content'   => $section->getContent(),
          'disabled'  => !($section->access()),
        );
      }
  }

  /**
   * Returns all sections.
   * @return [type] [description]
   */
  public function getSections() {
    return $this->_sections;
  }

  /**
   * Returns the node.
   * @return [type] [description]
   */
  public function getNode() {
    return $this->_node;
  }

  /**
   * Returns the user account.
   * @return [type] [description]
   */
  public function getAccount() {
    return $this->_account;
  }
}