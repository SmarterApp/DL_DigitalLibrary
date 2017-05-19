<?php
namespace sbac_core\components\feedback\form_utility;

class GateKeeper extends Base {
  protected $_prefix = 'resource_gate_keeper_';
  protected $_bundle_friendly = 'gate-keeper';

  protected $_set_field = 'field_quality_set';
  protected $_radio_field = 'field_meets_criterion';

  protected $_edit_permission = 'edit gate keeper';

  /**
   * Constructor.
   * @param [type] $form        [description]
   * @param [type] $form_state  [description]
   * @param [type] $bundle_info [description]
   */
  public function __construct(&$form, &$form_state, $bundle_info) {
    parent::__construct($form, $form_state, $bundle_info);

    if ($focus = field_entity_value($this->_resource, 'field_focus')) {
      // total number of sets
      $this->_set_total = $this->getVar('criteria_num', FEEDBACK_DEFAULT_SET_COUNT, FALSE);
    }
  }

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

  public function getBacklog() {
    $results = array();
    $query = db_select('eck_feedback', 'f')
      ->fields('f', array('id'))
      ->condition('node_id', $this->_resource->nid)
      ->condition('completed', 1)
      ->condition('type', 'gate_keeper')
      ->orderBy('id', 'DESC');

    $result = $query->execute();
    while ($id = $result->fetchField()) {
      $results[$id] = 'gk';
    }
    return $results;
  }

  /**
   * Returns FAPI element for Set's Feedback content.
   * @param $content_callback
   * @param bool $id
   * @return array [type]                   [description]
   */
  public function getReviewTeaser($content_callback, $id = FALSE) {
    $form = array();
    if ($id === FALSE) {
      $query = db_select('eck_feedback', 'f')
        ->fields('f', array('id'))
        ->condition('node_id', $this->_resource->nid)
        ->condition('created', _sbac_resource_resubmit_timestamp($this->_resource->nid), '>')
        ->condition('completed', 1)
        ->condition('type', 'gate_keeper')
        ->orderBy('id', 'ASC');
    } else {
      $query = db_select('eck_feedback', 'f')
        ->fields('f', array('id'))
        ->condition('id', $id);
    }

    $result = $query->execute();

    $i = 0;
    $counter = 1;
    while ($row = $result->fetchField()) {
      $entity = entity_load_single('feedback', $row);

      // No longer need the username of the user.
      // $author = theme('username', array(
      //   'account' => user_load($entity->uid)
      // ));

      $created = format_date($entity->created, 'full');

      list($headline, $comments) = $content_callback($entity);

      $form['feedback_' . $entity->id]['#markup'] = theme('qc_teaser', array(
        'id'          => $entity->id,
        'author'      => 'Reviewer '. $counter,//$author,
        'created'     => $created,
        'headline'    => $headline,
        'comments'    => more_less_text($comments, 140),
      ));

      $counter++;
      if (++$i == 1) { // 3 = total number of reviews
        $this->clearFapi($form['feedback_' . $entity->id]);
      }
    }

    return $form;
  }
}
