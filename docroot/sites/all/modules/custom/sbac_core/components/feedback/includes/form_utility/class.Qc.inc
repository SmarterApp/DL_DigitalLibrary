<?php
namespace sbac_core\components\feedback\form_utility;

class Qc extends Base {
  protected $_prefix = '';
  protected $_bundle_friendly = 'qc';

  protected $_set_field = 'field_review_set';
  protected $_radio_field = 'field_level';
  protected $_edit_permission = 'edit quality criteria';

  /**
   * Constructor.
   * @param [type] $form        [description]
   * @param [type] $form_state  [description]
   * @param [type] $bundle_info [description]
   */
  public function __construct(&$form, &$form_state, $bundle_info) {
    parent::__construct($form, $form_state, $bundle_info);

    if ($focus = field_entity_value($this->_resource, 'field_focus')) {
      $this->_prefix = 'qc_' . $focus->tid . '_';

      // total number of sets
      $this->_set_total = $this->getVar('criteria_num', FEEDBACK_DEFAULT_SET_COUNT, FALSE);
    }
  }

  /**
   * Updates FAPI element to set correct description text.
   * @param  [type] $element   [description]
   * @param  [type] $set_count [description]
   * @return [type]            [description]
   */
  public function updateRadioDesc(&$element, $set_count) {
    parent::updateRadioDesc($element, $set_count);

    $desc = '';
    $level_class = 'hidden';
    $level_val = $element['#default_value'];

    if ($level_val) {
      $desc = variable_get('qc_level_' . $level_val, '');
      $desc = filter_text($desc);

      $level_class = '';
    }

    $suffix = '';
    if (isset($element['#suffix'])) {
      $suffix = $element['#suffix'];
    }

    $element['#suffix'] = '<div class="desc ' . $level_class . '">' . $desc . '</div>' . $suffix;
  }

  /**
   * Loops through sets and creates data structure.
   * @return [type] [description]
   */
  public function process() {
    parent::process();

    // remove the N/A option
    unset($this->_form['field_rec_options'][$this->_lang]['#options']['_none']);

    // add 'required field' asterisks
    $this->_form['field_rec_options'][$this->_lang]['#title'] .= $this->_required_marker;
    $this->_form['field_rec_rationale'][$this->_lang]['#title'] .= $this->_required_marker;

    $children = element_num_children($this->_form['field_rec_rationale'][$this->_lang]);
    foreach ($children as &$child) {
      $child['#title'] .= $this->_required_marker;
      $child['value']['#title'] .= $this->_required_marker;
    }

    // log radio button descriptions
    $this->_js_settings['feedback']['level_desc'] = array();
    foreach (field_allowed_values('field_level') as $value => $label) {
      $desc = variable_get('qc_level_' . $value, '');
      $this->_js_settings['feedback']['level_desc'][$value] = json_encode(filter_text($desc));
    }

    // log radio selectors
    $this->_js_settings['feedback']['level_radios'] = $this->_radios;

    // add descriptions to recommendaton radio buttons
    $this->_form['field_rec_options']['#prefix'] = '<div class="radios-with-desc">';
    $this->_form['field_rec_options']['#suffix'] = '</div>';
    foreach ($this->_form['field_rec_options'][$this->_lang]['#options'] as $option_key => &$option) {
      if ($option_desc = variable_get('qc_rec_' . $option_key, input_default_full_html())) {
        $option .= '<span>' . t(' - ') . filter_text($option_desc) . '</span>';
      }
    }

    // wrap the rationale
    $this->_form['field_rec_rationale']['#prefix'] = '<div class="form-textarea-wrapper">';
    $this->_form['field_rec_rationale']['#suffix'] = '</div>';

    // figure out current state
    $states = feedback_recommendation_states();
    $this->_js_settings['feedback']['qc']['decision_radio_states'] = $states;
    $this->_js_settings['feedback']['qc']['is_disabled'] = FALSE;

    $state_key = 0;
    if (isset($this->_form['field_rec_options'][$this->_lang]['#default_value'])) {
      $state_key = $this->_form['field_rec_options'][$this->_lang]['#default_value'];
    }

    // add action buttons
    $this->cancelButton();
    $this->saveButton();
    $this->completeButton($states[$state_key]);

    // if the entity is completed, the user cannot edit any data, so disable all fields
    if ($this->_entity->completed || !resource_access($this->_edit_permission, $this->_resource)) {
      $this->_form['field_rec_options']['#disabled'] = TRUE;
      $this->_form['field_rec_rationale']['#disabled'] = TRUE;

      $this->_js_settings['feedback']['qc']['is_disabled'] = TRUE;

      $this->_form['actions'] = array();
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
      'complete' => t('Complete Review'),
    );

    // add custom submit handler
    $this->_form['#submit'][] = 'feedback_eck_qc_form_submit';

    // only show field_contributor_comment to the resource author
    global $user;
    if ($this->_resource->uid != $user->uid) {
      if (!empty($this->_form['field_review_set'][LANGUAGE_NONE])) {
        for ($i = 0; $i < $this->_form['field_review_set'][LANGUAGE_NONE]['#cardinality']; $i++) {
          if(!empty($this->_form['field_review_set']['und'][$i]['field_contributor_comment'])){
            $this->_form['field_review_set']['und'][$i]['field_contributor_comment']['#access'] = FALSE;
          }
          if(!empty($this->_form['field_review_set']['und'][$i]['field_contributor_comment_date'])){
            $this->_form['field_review_set']['und'][$i]['field_contributor_comment_date']['#access'] = FALSE;
          }
        }
      }
    }
    parent::postProcess();
  }

  /**
   * Returns FAPI element for Set's Feedback content.
   * @param  [type] $content_callback [description]
   * @return [type]                   [description]
   */
  public function getReviewTeaser($content_callback) {
    $form = array();

    $query = "
SELECT
	f.id
FROM {eck_feedback} f
WHERE f.node_id = :node_id
      AND f.created > :time_stamp
      AND f.completed = 1
      AND f.type = 'qc'
    ORDER BY f.created ASC";

    $result = db_query($query, array(':node_id' => $this->_resource->nid, ':time_stamp' => _sbac_resource_resubmit_timestamp($this->_resource->nid)));

    $i = 0;
    $counter = 1;
    foreach ($result as $row) {
      $entity = entity_load_single('feedback', $row->id);

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
      if (++$i == 3) { // 3 = total number of reviews
        $this->clearFapi($form['feedback_' . $entity->id]);
      }
    }

    return $form;
  }
}
