<?php
namespace sbac_core\components\feedback\form_utility;

class Post extends Base {
  protected $_prefix = 'resource_post_';
  protected $_bundle_friendly = 'post';
  protected $_edit_permission = 'edit post';

  /**
   * Constructor.
   * @param [type] $form        [description]
   * @param [type] $form_state  [description]
   * @param [type] $bundle_info [description]
   */
  public function __construct(&$form, &$form_state, $bundle_info) {
    parent::__construct($form, $form_state, $bundle_info);
  }

  /**
   * Loops through sets and creates data structure.
   * @return [type] [description]
   */
  public function process() {
    $in_poster_workflow = _sbac_resource_is_in_poster_workflow($this->_form['node_id']['#value']);

    // add 'required field' asterisks
    if ($in_poster_workflow) {
      $this->_form['field_to_reviewer_1']['#access'] = FALSE;
      $this->_form['field_to_reviewer_2']['#access'] = FALSE;
      $this->_form['field_to_reviewer_3']['#access'] = FALSE;
      $required_fields = array(
        'field_to_contributor',
      );
    }
    else {
      $required_fields = array(
        'field_to_contributor',
        'field_to_reviewer_1',
        'field_to_reviewer_2',
        'field_to_reviewer_3',
      );
    }

    foreach ($required_fields as $field_name) {
      $this->_form[$field_name][$this->_lang]['#title'] .= $this->_required_marker;

      $children = element_num_children($this->_form[$field_name][$this->_lang]);
      foreach ($children as &$child) {
        $child['#title'] .= $this->_required_marker;
        $child['value']['#title'] .= $this->_required_marker;
      }
    }

    // remove the N/A option & add asterisk to post options
    unset($this->_form['field_post_options'][$this->_lang]['#options']['_none']);
    $this->_form['field_post_options'][$this->_lang]['#title'] .= $this->_required_marker;

    // prep review sets
    module_load_include('inc', 'sbac_core', 'components/feedback/includes/form_utility/class.Qc');

    $reviewUtil = new Qc($this->_form, $this->_form_state, $this->_bundle_info);
    if ($focus = field_entity_value($this->_resource, 'field_focus')) {
      $reviewUtil->setPrefix('qc_' . $focus->tid . '_');
      $total = $reviewUtil->getSetTotal();

      $items = array();
      for ($i = 1; $i <= $total; $i++) {
        $item = array();
        $item += $reviewUtil->getSetTitle($i);
        $item += $reviewUtil->getSetDescription($i);
        if (!$in_poster_workflow) {
          $item += $this->getReviewersCommentsTitle();

          $item += $reviewUtil->getReviewTeaser(function ($entity) use ($i) {
            $reviews = field_entity_value($entity, 'field_review_set');
            $review = $reviews[$i - 1];

            $headline = t('Quality Criterion Level: !level', array(
              '!level' => field_entity_value($review, 'field_level'),
            ));

            $comments = field_entity_value($review, 'field_comments');

            return array($headline, $comments);
          });
        }

        $this->wrapFapi($item, 'feedback-item feedback-item-' . $i);
        $this->setWeight($item);

        $items['set_' . $i] = $item;
      }

      if (!$in_poster_workflow) {

        // add reviewers' recommendation options
        $item = array(
          '#prefix' => '<div class="criteria-set-title"><p>' . t('Reviewers Resource Recommendation') . '</p></div>',
        );
        $item += $reviewUtil->getReviewTeaser(function ($entity) {
          $options = field_allowed_values('field_rec_options');

          $headline = $options[field_entity_value($entity, 'field_rec_options')];
          $comments = field_entity_value($entity, 'field_rec_rationale');

          return array($headline, $comments);
        });

        $this->setWeight($item);
        $this->wrapFapi($item, 'feedback-item feedback-item-rec');
        $items['rec_details'] = $item;
      }

      $this->wrapFapi($items, 'feedback-items');
      $this->setWeight($items);
      $this->_form['feedback_items'] = $items;
    }

    $comments_title = array(
      '#markup' => '
                      <div class="field-title">
                        ' . t("Poster Comments") . '
                        <span class="required"></span>
                      </div>
                      <div class="field-description">
                        ' . t("") . '
                      </div>
                   ',
    );

    $this->setWeight($comments_title);
    $this->_form['comments_title'] = $comments_title;

    $this->setWeight($this->_form['field_to_contributor']);
    $this->setWeight($this->_form['field_to_reviewer_1']);
    $this->setWeight($this->_form['field_to_reviewer_2']);
    $this->setWeight($this->_form['field_to_reviewer_3']);
    $this->clearFapi($this->_form['field_to_reviewer_3']);

    $this->setWeight($this->_form['field_post_options']);

    // add descriptions to post options
    $this->_form['field_post_options']['#prefix'] = '<div class="radios-with-desc">';
    $this->_form['field_post_options']['#suffix'] = '</div>';
    foreach ($this->_form['field_post_options'][$this->_lang]['#options'] as $option_key => &$option) {
      // commented out descriptions for now
      // if ($option_desc = variable_get('post_options_' . $option_key, input_default_full_html())) {
      //   $option .= '<span>' . t(' - ') . filter_text($option_desc) . '</span>';
      // }
    }

    // figure out current state
    $states = feedback_post_states();
    $this->_js_settings['feedback']['post']['decision_radio_states'] = $states;
    $this->_js_settings['feedback']['post']['is_disabled'] = FALSE;

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
      $this->_form['field_to_contributor']['#disabled'] = TRUE;
      $this->_form['field_to_reviewer_1']['#disabled'] = TRUE;
      $this->_form['field_to_reviewer_2']['#disabled'] = TRUE;
      $this->_form['field_to_reviewer_3']['#disabled'] = TRUE;
      $this->_form['field_post_options']['#disabled'] = TRUE;

      $this->_js_settings['feedback']['post']['is_disabled'] = TRUE;

      $this->_form['actions'] = array();
    }
  }

  /**
   * Additional functionality outside of the criteria sets.
   * @return [type] [description]
   */
  public function postProcess() {
    // set hidden select action options
    $this->_action_options += array(
      'reject' => t('Return'),
      'post' => t('Post'),
      'post_distinction' => t('Post with Distinction'),
    );

    // add custom submit handler
    $this->_form['#submit'][] = 'feedback_eck_post_form_submit';

    $this->_form['field_contributor_comment']['#access'] = FALSE;
    $this->_form['field_contributor_comment_date']['#access'] = FALSE;

    $this->_form['field_contributor_comment']['#access'] = false;
    $this->_form['field_contributor_comment_date']['#access'] = false;

    parent::postProcess();
  }

  /**
   * Returns FAPI for Reviewers Comments title.
   * @return [type] [description]
   */
  public function getReviewersCommentsTitle() {
    $form = array();

    $form['reviewers_comments'] = array(
      '#prefix' => '<div class="comments-title">',
      '#suffix' => '</div>',
      '#markup' => t("Reviewers' Comments"),
    );

    return $form;
  }
}
