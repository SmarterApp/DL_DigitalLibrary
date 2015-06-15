<?php
namespace sbac_core\components\sections;

class Factory {
  protected $_node = NULL;
  protected $_account = NULL;
  protected $_sections = array();
  protected $_components_path = '';

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

    $this->_components_path = drupal_get_path('module', 'sbac_core') . '/components/';
  }

  /**
   * Access control for entire flow.
   * @param  [type] $permission [description]
   * @return [type]             [description]
   */
  function access($permission) {
    return resource_access($permission, $this->_node, $this->_account);
  }

  /**
   * Loads required files.
   * @param  [type] $source [description]
   * @param  [type] $name   [description]
   * @return [type]         [description]
   */
  public function loadPrereqs($source, $name) {
    $files = array(
      'components/sections/includes/interface.iSection',
      'components/sections/includes/class.Base',
      'components/' . $source . '/includes/sections/class.Base',
      'components/' . $source . '/includes/sections/class.' . $name,
    );

    foreach ($files as $file) {
      if (!module_load_include('inc', 'sbac_core', $file)) {
        throw new \Exception(t('Could not load !file', array('!file' => $file)));
      }
    }
  }

  /**
   * Builds & returns the requested Section Object.
   * @param  [type] $source [description]
   * @param  [type] $name   [description]
   * @return [type]         [description]
   */
  public function get($source, $name) {
    $name = ucfirst($name);

    try {
      $this->loadPrereqs($source, $name);

      $path = array(
        'sbac_core',
        'components',
        $source,
        'sections',
        $name,
      );

      $fqp = implode('\\', $path);

      global $user;
      $account = $user;

      return new $fqp($this->_node, $account);
    }
    catch(\Exception $e) {
      throw new \Exception($e->getMessage());
    } 

    return FALSE;
  }

  /**
   * Logs new section.
   *
   * @param [type] $section [description]
   */
  public function add(iSection $section, $source = NULL, $tab = NULL, $visible = TRUE) {
    if (($access = $section->access()) || $section->show_disabled()) {
      $add = array(
        'title'     => t($section::title),
        'content'   => '',
        'disabled'  => !$access,
        'source' => $source,
        'tab' => $tab,
        'nid' => $this->_node->nid,
        'section_loaded' => ($visible ? 'section-loaded' : ''),
      );

      // don't generate content if the user doesn't have access to the tab
      if ($access && $visible) {
        $add['content'] = $section->getContent();
      }

      $this->_sections[$section::name] = $add;
    }
  }

  /**
   * Returns all sections.
   * @return [type] [description]
   */
  public function getSections() {
    return $this->_sections;
  }
}