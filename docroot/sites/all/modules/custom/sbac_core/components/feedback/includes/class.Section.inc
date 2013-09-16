<?php
namespace sbac_core\components\feedback;

class Section {
  protected $_process = '';
  protected $_machine_name = '';
  protected $_control = NULL;
  protected $_access_override = NULL;

  /**
   * Constructor
   * @param [type] $process      [description]
   * @param [type] $machine_name [description]
   * @param [type] $control      [description]
   */
  public function __construct($process, $machine_name, $control) {
    // sanity checks
    if (empty($process)) {
      throw new \Exception(t('Process cannot be empty.'));
    }

    if (empty($machine_name)) {
      throw new \Exception(t('Machine name cannot be empty.'));
    }

    if (!is_object($control)) {
      throw new \Exception(t('Control must be a valid object.'));
    }

    $this->_process = $process;
    $this->_machine_name = $machine_name;
    $this->_control = $control;

    module_load_include('inc', 'sbac_core', '/components/feedback/includes/sections/class.Base');
  }

  /**
   * Checks access to current section.
   * @return [type] [description]
   */
  public function access() {
    $permission = '';

    if (isset($this->_access_override) && !is_null($this->_access_override)) {
      return $this->_access_override;
    }

    switch ($this->_machine_name) {
      case 'about':
        $permission = 'view about';
        break;

      case 'reviews':
        return TRUE;
        break;

      case 'gk':
        $permission = 'view gate keeper';
        break;

      case 'qc':
        $permission = 'view quality criteria';
        break;

      case 'tags':
        $permission = 'view tags';
        break;

      case 'post':
        $permission = 'view post';
        break;
    }

    if ($permission) {
      return resource_access($permission, $this->_control->getNode(), $this->_control->getAccount());
    }

    return FALSE;
  }

  /**
   * Returns content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    $class_name = preg_replace('/[^a-zA-Z0-9]/', '', $this->_machine_name);
    $class_name{0} = strtoupper($class_name{0});
    $class_name = 'Section' . $class_name;

    module_load_include('inc', 'sbac_core', '/components/feedback/includes/sections/class.' . $class_name);

    $class_name = '\\sbac_core\\components\\feedback\\section\\' . $class_name;;

    if (class_exists($class_name)) {
      static $count;
      if (is_null($count)) {
        $count = 0;
      }
      else {
        $count++;
      }

      $tab = new $class_name($this);
      $tab->setCounter($count);
      
      return $tab->getContent();
    }
    else {
      throw new \Exception(t('Missing class %class.', array('%class' => $class_name)));
    }
  }

  /**
   * Returns machine name.
   * @return [type] [description]
   */
  public function getMachineName() {
    return $this->_machine_name;
  }

  /**
   * Returns the Control object.
   * @return [type] [description]
   */
  public function getControl() {
    return $this->_control;
  }

  /**
   * Sets permission flag to selectively override access to section.
   * @param  [type] $access [description]
   * @return [type]         [description]
   */
  public function overrideAccess($access) {
    $this->_access_override = $access;
  }
}