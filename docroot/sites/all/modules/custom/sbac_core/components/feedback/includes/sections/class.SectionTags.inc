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
      $form_state = array();
      $form_state['build_info']['args'][] = $this->_node;
      $form_state += form_state_defaults();

      $node_form = drupal_retrieve_form('resource_node_form', $form_state);

    // move all elements from the Tags group into our new form
      $form = array();
      $fields = array();
      foreach ($node_form['#group_children'] as $field_name => $tab) {
        if ($tab == 'group_tags') {
          $form[$field_name] = $node_form[$field_name];
        }
      }

      /*
      if (isset($form['field_alignment_term']) && !isset($form['field_alignment_term']['#attributes']['id'])) {
        $form['field_alignment_term']['#id'] = 'field-alignment-term';
        $form['field_alignment_term']['#attributes']['id'] = 'field-alignment-term';
      }
      */

    // add buttons
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 99,
      );

    $output = drupal_render($form);

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


