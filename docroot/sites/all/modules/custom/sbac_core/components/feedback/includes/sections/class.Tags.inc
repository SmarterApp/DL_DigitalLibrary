<?php
namespace sbac_core\components\feedback\sections;

class Tags extends Base {
  const name = 'tags';
  const title = 'Edit Resource Tags';
  const permission = 'view tags';

  protected $_show_disabled = TRUE;

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    module_load_include('inc', 'node', 'node.pages');
    
    // bring in the node form; the last argument ensures it gets modified in hook_form_alter()
    // for this page's needs
      $form = drupal_get_form('resource_node_form', $this->_node, 'edit_tags');

    // wrap output
      $output = '<div class="feedback-wrap" id="feedback-wrap-edit-tags">' . drupal_render($form) . '</div>';
  
    return $output;
  }
}















