<?php
namespace sbac_core\components\feedback\form_utility;

class GateKeeper extends Base {
  protected $_prefix = 'resource_gate_keeper_';
  protected $_bundle_friendly = 'gate-keeper';

  protected $_set_field = 'field_quality_set';
  protected $_radio_field = 'field_meets_criterion';

  protected $_edit_permission = 'edit gate keeper';

  /**
   * Loops through sets and creates data structure.
   * @return [type] [description]
   */
  public function process() {
    parent::process();
    
    $score = 0;
    $sets = $this->getCriteriaSets();
    foreach ($sets as &$item) {
      // log score (# of yes choices) for JS settings inclusion below
      if (isset($this->_form_state['values'][$this->_radio_field])) {
        $field_value = $this->_form_state['values'][$this->_radio_field];
      }
      else {
        $field_value = $item[$this->_radio_field][$this->_lang]['#default_value'];
      }

      if ($field_value == 1) {
        $score++;
      }
    }

    // log radio button names
    $this->_js_settings['feedback']['meet_radios'] = $this->_radios;

    // add action buttons
    $this->cancelButton();
    
    $this->saveButton();
    $this->notMeetButton();
    $this->meetButton();
    
    // default states for meet/not meet buttons
    // if all of the meets criterion radios are set to 'yes', then we need to disable 
    // the 'does not meet all' button, otherwise we disable the 'meets all' button
    if ($score == $this->_set_total) {
      $this->_form['actions']['not_meet_button']['#attributes']['disabled'] = TRUE;
    }
    else {
      $this->_form['actions']['meet_button']['#attributes']['disabled'] = TRUE;
    }
  }

  /**
   * Additional functionality outside of the criteria sets.
   * @return [type] [description]
   */
  function postProcess() {
    // set hidden select action options
    $this->_action_options += array(
      'cancel' => t('Cancel review'),
      'not_meet' => t('Does not meet all criteria'),
      'meet' => t('Meets all criteria'),
    );

    // add custom submit handler
    $this->_form['#submit'][] = 'feedback_eck_gate_keeper_form_submit';

    // only show field_contributor_comment to the resource author
    global $user;
    if ($this->_resource->uid != $user->uid) {
      if (!empty($this->_form['field_quality_set'][LANGUAGE_NONE])) {
        for ($i = 0; $i < $this->_form['field_quality_set'][LANGUAGE_NONE]['#cardinality']; $i++) {
          if (!empty($this->_form['field_quality_set']['und'][$i]['field_contributor_comment'])) {
            $this->_form['field_quality_set']['und'][$i]['field_contributor_comment']['#access'] = FALSE;
          }
          if (!empty($this->_form['field_quality_set']['und'][$i]['field_contributor_comment_date'])) {
            $this->_form['field_quality_set']['und'][$i]['field_contributor_comment_date']['#access'] = FALSE;
          }
        }
      }
    }
    parent::postProcess();
  }
}