<?php
namespace sbac_core\components\feedback\section;

class SectionTags extends Base {
  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    // pull up the existing node form
      module_load_include('inc', 'node', 'node.pages');
      
    // bring in the node form; the last argument ensures it gets modified in hook_form_alter()
    // for this page's needs
      $form = drupal_get_form('resource_node_form', $this->_node, 'edit_tags');

    // wrap output
      $output = '<div id="edit-tags">' . drupal_render($form) . '</div>';
  
    return $output;
  }
}


/*
    $type_name = node_type_get_name($this->_node);

    
    $form = drupal_get_form($this->_node->type . '_node_form', $this->_node);

    $remove = array(
      'group_basic',
      'group_materials',
      'group_summary',
      'group_advanced',
      'group_paradata'
    );

    foreach ($remove as $group) {
      unset($form['#groups'][$group], $form['#fieldgroups'][$group]);
    }

    // $form['actions'] = array(
    //   '#type' => 'actions',
    //   'submit' => array(
    //     '#type' => 'submit',
    //     '#value' => t('Save'),
    //   ),
    // );

    // print_rr($form);exit();

    // $form['#groups']['group_basic']->format_settings['instance_settings']['classes'] .= ' element-invisible ';
    // $form['#fieldgroups']['group_basic']->format_settings['instance_settings']['classes'] .= ' element-invisible ';

    // print_rr($form['resource_basic_container_open']);

    // exit();
*/


