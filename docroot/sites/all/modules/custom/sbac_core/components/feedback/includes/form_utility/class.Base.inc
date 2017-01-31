<?php
namespace sbac_core\components\feedback\form_utility;

class Base {
  protected $_form = array();
  protected $_form_state = array();
  protected $_bundle_info = array();
  protected $_weight = 1;

  protected $_resource = NULL;
  protected $_entity = NULL;
  protected $_lang = NULL;

  protected $_prefix = '';
  protected $_comments_field = 'field_comments';
  protected $_set_total = 0;

  protected $_required_marker = '';

  protected $_action_options = array();

  protected $_js_settings = array(
    'feedback' => array(
      'form_error' => -1,
    ),
  );

  protected $_radios = array();

  /**
   * Constructor.
   * @param [type] $form        [description]
   * @param [type] $form_state  [description]
   * @param [type] $bundle_info [description]
   */
  public function __construct(&$form, &$form_state, $bundle_info) {
    $this->_form =& $form;
    $this->_form_state =& $form_state;
    $this->_bundle_info =& $bundle_info;

    // wrap form, but only if there's no wrapping data already in place
      if (!isset($this->_form['#prefix'])) {
        $this->_form['#prefix'] = '<div id="eck-' . $this->_bundle_friendly . '-form">';
        $this->_form['#suffix'] = '</div>';
      }

    // add custom validation handler
      $this->_form['#validate'][] = 'feedback_eck_feedback_form_validate';

    // load the node this feedback entity is attached to
      if (isset($this->_form['entity']['#value']->node_id)) {
        $this->_resource = node_load($this->_form['entity']['#value']->node_id);
      }
      else {
        $this->_resource = current_node();
      }

    // set the base url parts
      $this->_base_url = array(
        'node',
        $this->_resource->nid,
        'feedback',
        $this->_bundle_friendly,
      );

    // set feedback entity's title
      if (!isset($this->_form['title']['#value']) || empty($this->_form['title']['#value'])) {
        $this->_form['title']['#value'] = t('!resource - !label', array(
          '!resource' => $this->_resource->title,
          '!label' => $this->_bundle_info['label'],
        ));
      }

    // set feedback entity's node_id property
      if (!isset($this->_form['node_id']['#value']) || empty($this->_form['node_id']['#value'])) {
        $this->_form['node_id']['#value'] = $this->_resource->nid;
      }

    // set the feedback entity & id
      $this->_entity = $this->_form['entity']['#value'];

      $this->_form['entity_id'] = array(
        '#type' => 'hidden',
        '#value' => isset($this->_entity->id) ? $this->_entity->id : 0,
      );

    // set language string
      $this->_lang = isset($this->_entity->language) ? $this->_entity->language : LANGUAGE_NONE;

    // run default operations
      $this->hideFormProperties();
      $this->setEntityProperties();

    // submit buttons
      $form['actions']['#weight'] = 10000;
      unset($form['submit']);

    // misc requirements
      drupal_add_library('dialog', 'dialog');

    // total number of sets
      $this->_set_total = $this->getVar('criteria_num', FEEDBACK_DEFAULT_SET_COUNT, FALSE);

    // set the common (across feedback types) & default action
      $this->_action_options += array(
        'save_close' => t('Save and close'),
        'validate' => t('Validate'),
      );

    // get the required form item asterisk
      $this->_required_marker = ' ' . theme('form_required_marker');
  }

  /**
   * Hides default properties
   * @return [type] [description]
   */
  protected function hideFormProperties() {
    $properties = array(
      'status',
      'completed',
      'met_criteria',
      'node_id',
      'current',
      'title',
      'reminder',
      'archived',
    );

    foreach ($properties as $property) {
      if (isset($this->_form[$property])) {
        $this->_form[$property]['#type'] = 'hidden';
      }
    }
  }

  /**
   * Sets default properties on the Entity object
   * @return [type] [description]
   */
  protected function setEntityProperties() {
    $properties = array(
      'completed' => 0,
      'node_id' => 0,
      'met_criteria' => 0,
      'id' => 0,
      'created' => REQUEST_TIME,
    );

    foreach ($properties as $property => $value) {
      if (!isset($this->_entity->{$property})) {
        $this->_entity->{$property} = $value;
      }
    }
  }

  /**
   * Identifies & returns criteria sets.
   * @return [type] [description]
   */
  protected function getCriteriaSets() {
    $set_count = 0;

    $this->setWeight($this->_form[$this->_set_field]);

    $sets = array();
    foreach ($this->_form[$this->_set_field][$this->_lang] as $key => &$item) {
      // skip over all FAPI proprties
      if ($key{0} == '#' || !is_numeric($key)) {
        continue;
      }

      // track data & check for empty items in set
      $set_count++;

      if ($set_count > $this->_set_total) {
        $item = array();
        unset($this->_form[$this->_set_field][$this->_lang][$key]);
        continue;
      }

      $sets[] =& $item;
    }

    return $sets;
  }

  /**
   * Attaches helpful info.
   * @return [type] [description]
   */
  public function attachHelpfulInfo() {
    // attach helpful info
    if ($helpful_info = $this->getVar('help')) {
      $output = theme('feedback_helpful_info', array(
        'helpful_info' => more_less_text($helpful_info),
      ));

      $this->_form['helpful_info'] = array(
        '#markup' => $output,
      );

      $this->setWeight($this->_form['helpful_info']);
    }
  }

  /**
   * Wraps FAPI element in DIV with specified class or id.
   * @param  [type]  $element [description]
   * @param  [type]  $class   [description]
   * @param  boolean $id      [description]
   * @return [type]           [description]
   */
  public function wrapFapi(&$element, $class, $id = FALSE) {
    $attribute = 'class';
    if ($id) {
      $attribute = 'id';
    }

    $prefix = '';
    if (isset($element['#prefix'])) {
      $prefix = $element['#prefix'];
    }

    $element['#prefix'] = '<div ' . $attribute . '="' . $class . '">' . $prefix;

    $suffix = '';
    if (isset($element['#suffix'])) {
      $suffix = $element['#suffix'];
    }

    $element['#suffix'] = $suffix . '</div>';
  }

  /**
   * Sets up the fields with required asterisks.
   * @param  [type] $item [description]
   * @return [type]       [description]
   */
  public function markRequiredFields(&$item) {
    // add required asterisk to textarea
    $children = element_num_children($item[$this->_comments_field][$this->_lang]);
    foreach ($children as &$child) {
      $child['value']['#title'] .= $this->_required_marker;
    }

    // add required asterisk to radio
    $item[$this->_radio_field][$this->_lang]['#title'] .= $this->_required_marker;

    // remove the default N/A value
    unset($item[$this->_radio_field][$this->_lang]['#options']['_none']);

    // add back in a N/A value for the Integrates media and technology effectively entry
    if ($this->_radio_field == 'field_level' && !preg_match("/Integrates media and technology effectively/", $item['set_title']['#value'])) {
      unset($item[$this->_radio_field][$this->_lang]['#options'][0]);
    }
  }

  /**
   * Adds CSS clearing DIV to FAPI element's #suffix.
   * @param  [type] $element [description]
   * @return [type]          [description]
   */
  public function clearFapi(&$element) {
    $suffix = '';
    if (isset($element['#suffix'])) {
      $suffix = $element['#suffix'];
    }

    $element['#suffix'] = $suffix . '<div class="clear"></div>';
  }

  /**
   * Sets the correct #weight on FAPI element.
   * @param [type] $element [description]
   */
  public function setWeight(&$element) {
    $element['#weight'] = $this->_weight++;
  }

  /**
   * Returns FAPI element for Set Title.
   * @return [type] [description]
   */
  public function getSetTitle($set_count) {
    $form = array();

    if ($title = $this->getVar('criteria_' . $set_count . '_title', '')) {
      $form['set_title'] = array(
        '#prefix' => '<div class="criteria-set-title">' . $title . '</div>',
        '#type' => 'hidden',
        '#value' => $title,
      );
    }

    return $form;
  }

  /**
   * Returns FAPI element for Set Description.
   * @param  [type] $set_count [description]
   * @return [type]            [description]
   */
  public function getSetDescription($set_count) {
    $form = array();

    if ($desc = $this->getVar('criteria_' . $set_count . '_description', '')) {
      // do we want to display the description text as collapsed or expanded?
      $desc_state_expanded = FALSE;
      if ($this->getVar('criteria_' . $set_count . '_desc_state', 'collapsed', FALSE) == 'expanded') {
        $desc_state_expanded = TRUE;
      }

      $form['set_desc'] = array(
        '#prefix' => '<div class="criteria-set-comments-text">',
        '#suffix' => '</div>',
        '#markup' => more_less_text($desc, 300, $desc_state_expanded),
      );
    }

    return $form;
  }

  /**
   * Updates FAPI element to set correct description text.
   * @param  [type] $element   [description]
   * @param  [type] $set_count [description]
   * @return [type]            [description]
   */
  public function updateRadioDesc(&$element, $set_count) {
    if ($radio_help = $this->getVar('criteria_' . $set_count . '_radiobuttonshelptext', '&nbsp;')) {
      $element['value']['#theme_options']['description at top'] = $radio_help;
      $element['#theme_options']['description at top'] = $radio_help;
    }
  }

  /**
   * Returns the form FAPI.
   * @return [type] [description]
   */
  public function getForm() {
    return $this->_form;
  }

  /**
   * Loops through sets and creates data structure.
   * @return [type] [description]
   */
  public function process() {
    $set_count = 1;
    $sets = $this->getCriteriaSets();

    foreach ($sets as &$item) {
      // if the entity is completed, the user cannot edit any data, so disable all fields
      if (!resource_access($this->_edit_permission, $this->_resource)) {
        $item[$this->_comments_field]['#disabled'] = TRUE;
        $item[$this->_radio_field]['#disabled'] = TRUE;
      }

      // title
      $item += $this->getSetTitle($set_count);

      // description
      $item += $this->getSetDescription($set_count);

      // comments
      $this->wrapFapi($item[$this->_comments_field], 'criteria-set-comments');

      $this->markRequiredFields($item);

      // radio
      $this->updateRadioDesc($item[$this->_radio_field][$this->_lang], $set_count);
      $this->wrapFapi($item[$this->_radio_field], 'criteria-set-radios');

      // log radio to JS
      $this->_radios[] = 'input[name="' . $item[$this->_radio_field][$this->_lang]['#field_parents'][0] .
                          '[' . $item[$this->_radio_field][$this->_lang]['#field_parents'][1] . ']' .
                          '[' . $item[$this->_radio_field][$this->_lang]['#field_parents'][2] . ']' .
                          '[' . $item[$this->_radio_field][$this->_lang]['#field_name'] . ']' .
                          '[' . $this->_lang . ']"]';

      $set_count++;
    }
  }

  /**
   * Additional functionality outside of the criteria sets.
   * @return [type] [description]
   */
  function postProcess() {
    // hidden select to determine which action the user has performed. this is necessary because all form submissions
    // actually happen through the same 'Save and Close' (submit) button:
    // 1. a link is clicked to trigger a modal
    // 2. a button is clicked in the modal (which submits the modal form) and the modal's callback
    //    triggers Drupal.behaviors.feedback.submit_modal_callback(), which sets the appropriate value in this
    //    select element, and then triggers the click() event on the 'Save and Close' button
    $this->_form['action'] = array(
      '#type' => 'select',
      '#title' => 'Actions',
      '#title_display' => 'invisible',
      '#options' => $this->_action_options,
      '#default_value' => 'save_close',
      '#attributes' => array(
        'class' => array(
          'hidden',
        ),
      ),
    );

    // attach the JS
    $this->_form['#attached']['js'][] = array(
      'data' => $this->_js_settings,
      'type' => 'setting',
    );

    // if the entity is completed, we need to remove the submit buttons
    if ($this->_entity->completed) {
      $this->_form['actions'] = array();
    }

    // add asterisk explanation
    $this->_form['asterisk'] = array(
      '#prefix' => '<div class="criteria-set-required-info">',
      '#suffix' => '</div>',
      '#markup' => theme('form_required_marker') . ' ' . t('Required information'),
    );

    $this->setWeight($this->_form['asterisk']);
  }

  /**
   * Returns the radios.
   * @return [type] [description]
   */
  public function getRadios() {
    return $this->_radios;
  }

  /**
   * Returns the total number of sets.
   * @return [type] [description]
   */
  public function getSetTotal() {
    return $this->_set_total;
  }

  /**
   * Retrieves variables with the proper contextual prefix. Optionally filters
   * text values.
   *
   * @param  [type]  $setting     [description]
   * @param  string  $default     [description]
   * @param  boolean $filter_text [description]
   * @return [type]               [description]
   */
  public function getVar($setting, $default = '', $filter_text = TRUE) {
    $variable_name = $this->_prefix . $setting;
    $variable = variable_get($variable_name, $default);

    if ($filter_text) {
      $variable = filter_text($variable);
    }

    return $variable;
  }

  /**
   * Adds the Cancel button.
   * @return [type] [description]
   */
  public function cancelButton() {
    $trigger_id = $this->_bundle_friendly . '-cancel';

    $text = t('Cancel review (!hours hrs)', array(
              '!hours' => feedback_hours_left($this->_entity),
            ));

    $url = implode('/', array_merge($this->_base_url, array(
      'cancel',
      $trigger_id,
      $this->_entity->id,
    )));

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'button',
          'radius',
        ),
        'id' => $trigger_id,
      ),
    );

    $this->_form['actions']['cancel'] = array(
      '#markup' => l($text, $url, $options),
    );

    $this->setWeight($this->_form['actions']['cancel']);
  }

  /**
   * Adds Save & Close button.
   * @return [type] [description]
   */
  public function saveButton() {
    $this->_form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save and Close'),
      '#ajax' => array(
        'callback' => 'feedback_eck_feedback_form_submit',
        'wrapper' => 'eck-' . $this->_bundle_friendly . '-form',
      ),
      '#attributes' => array(
        'class' => array(
          'action-save',
        ),
      ),
    );

    $this->setWeight($this->_form['actions']['submit']);
  }

  /**
   * Adds the Does Not Meet All Criteria button.
   * @return [type] [description]
   */
  public function notMeetButton() {
    /*
      dialog modals can only be added on anchor links (not form buttons), but we have a requirement to
      selectively disable the buttons (and thus prevent dialog from opening). since we can't actually
      disable anchor links, we have to create 'fake' buttons which propagate the click events to the hidden
      links when they're clicked. since these buttons are proper form elements, their disabled state is
      respected by Drupal (or is it the browser?) and nothing happens when a disabled button is clicked.
    */
    $this->_form['actions']['not_meet_button'] = array(
      '#type' => 'submit',
      '#value' => t('Does Not Meet All Criteria'),
      '#attributes' => array(
        'class' => array(
          'action-not-meet',
        ),
      ),
    );

    $this->setWeight($this->_form['actions']['not_meet_button']);

    // hidden link to trigger modal
    $trigger_id = $this->_bundle_friendly . '-not-meet';

    $text = t('Does Not Meet All Criteria');

    $url = implode('/', array_merge($this->_base_url, array(
      'not_meet',
      $trigger_id,
      $this->_entity->id,
    )));

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'hidden',
        ),
        'id' => $trigger_id,
      ),
    );

    $this->_form['actions']['not_meet'] = array(
      '#markup' => l($text, $url, $options),
    );

    $this->setWeight($this->_form['actions']['not_meet']);
  }

  /**
   * Adds the Meets All Criteria button.
   * @return [type] [description]
   */
  public function meetButton() {
    $text = t('Meets All Criteria');

    $this->_form['actions']['meet_button'] = array(
      '#type' => 'submit',
      '#value' => $text,
      '#attributes' => array(
        'class' => array(
          'action-meet',
        ),
      ),
    );

    $this->setWeight($this->_form['actions']['meet_button']);

    // hidden link to trigger modal
    $trigger_id = $this->_bundle_friendly . '-meet';

    $url = implode('/', array_merge($this->_base_url, array(
      'meet',
      $trigger_id,
      $this->_entity->id,
    )));

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'hidden',
        ),
        'id' => $trigger_id,
      ),
    );

    $this->_form['actions']['meet'] = array(
      '#markup' => l($text, $url, $options),
    );

    $this->setWeight($this->_form['actions']['meet']);
  }

  /**
   * Adds the Complete button.
   * @return [type] [description]
   */
  public function completeButton($state = 'cancel') {
    $text = t('Complete Review');

    $this->_form['actions']['complete_button'] = array(
      '#type' => 'submit',
      '#value' => $text,
      '#attributes' => array(
        'class' => array(
          'action-complete',
        ),
      ),
    );

    $this->setWeight($this->_form['actions']['complete_button']);

    // hidden link to trigger modal
    $trigger_id = $this->_bundle_friendly . '-complete';

    $url = implode('/', array_merge($this->_base_url, array(
      $state,
      $trigger_id,
      $this->_entity->id,
    )));

    $options = array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'hidden',
          'link-complete',
        ),
        'id' => $trigger_id,
      ),
    );

    $this->_form['actions']['complete'] = array(
      '#markup' => l($text, $url, $options),
    );

    $this->setWeight($this->_form['actions']['complete']);
  }

  /**
   * Sets the prefix.
   * @param [type] $prefix [description]
   */
  public function setPrefix($prefix) {
    $this->_prefix = $prefix;
  }
}

