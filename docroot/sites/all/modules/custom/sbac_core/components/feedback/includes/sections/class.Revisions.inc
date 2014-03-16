<?php
namespace sbac_core\components\feedback\sections;

class Revisions extends Base {
  const name = 'revisions';
  const title = 'Revisions';
  const permission = 'access quality criteria revisions';

  /**
   * Builds and returns the content for current section.
   * @return string [type] [description]
   */
  public function getContent() {
    $html = '';

    // Find out at what stage was the resource returned.
    // Get the last feedback
    $results = $this->getFeedbacks(1);
    if (!empty($results)) {
      $feedback = current($results);
      switch ($feedback->type) {
        case 'qc':
          // The resource was returned at the 3RR level
          $html = $this->getReviewerContent();
          break;
        case 'gate_keeper':
          $html = $this->getGateKeeperContent($feedback);
          break;
        case 'post':
          $html = $this->getReviewerContent($this->getPostContent($feedback));
          break;
      }
    }

    return $html;
  }

  private function getPostContent($feedback) {
    $publisher_feedback = entity_load_single('feedback', $feedback->id);
    return '
          <div class="feedback-item">
            <div class="criteria-set-title">
              ' . t('Posting Comments') . '
            </div>
            <div class="comments">' . field_entity_value($publisher_feedback, 'field_to_contributor') . '</div>
          </div>
        ';
  }

  private function getReviewerContent($publisher_html = '') {
    $questions_and_comments_html = '';
    $question_html = '';
    // get the last 3 reviews
    $reviews = $this->getFeedbacks(3, 'qc');
    if (!empty($reviews)) {
      $recommendations_html = '';
      $i = 1;
      $focus = field_get_value($this->_node, 'field_focus', 'tid');
      foreach ($reviews as $review) {
        $entity = entity_load_single('feedback', $review->id);
        $created = format_date($entity->created, 'full');
        $options = field_allowed_values('field_rec_options');
        $headline = $options[field_entity_value($entity, 'field_rec_options')];
        $publisher_comment = field_entity_value($entity, 'field_rec_rationale');
        $recommendations_html .= theme('qc_teaser', array(
          'id' => $entity->id,
          'author' => t('Reviewer !count', array('!count' => $i)),
          'created' => $created,
          'headline' => $headline,
          'comments' => more_less_text($publisher_comment, 140),
        ));

        // questions
        $question_title = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_title');
        $question_title = filter_text($question_title);

        $question_desc = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_description');
        $question_desc = filter_text($question_desc);
        $question_desc = more_less_text($question_desc, 300);

        $question_html .= '
              <div class="criteria-set-title">
                ' . ($i + 1) . '. ' . strip_tags($question_title) . '
              </div>
              <div class="criteria-set-commentes-text">
                ' . $question_desc . '
              </div>
              <div class="comments-title">
                ' . t("Reviewer's Comments") . '
              </div>
           ';
        $question_html .= '<div class="feedback-item-triplet">';
        $contributor_comment = '';
        $contributor_comment_date = '';
        $questions = field_entity_value($entity, 'field_review_set');
        for ($j = 1; $j <= 3; $j++) {
          $level = field_entity_value($questions[$i], 'field_level');
          $reviewer_comments = field_entity_value($questions[$i], 'field_comments');
          // the contributor's comment is the same for all 3 reviewers, so we only need to get one
          if ($contributor_comment == '') {
            $contributor_comment = field_entity_value($questions[$i], 'field_contributor_comment');
            $contributor_comment_date = format_date(field_entity_value($questions[$i], 'field_contributor_comment_date'), 'full');
          }
          $reviewer_comments = more_less_text($reviewer_comments, 140);
          $question_html .= '
                <div class="feedback-review">
                  <div class="author">' . t('Reviewer !j', array('!j' => $j)) . '</div>
                  <div class="created">' . format_date($entity->created, 'full') . '</div>
                  <div class="headline">' . t('Quality Criteria Level: !level', array('!level' => $level)) . '</div>
                  <div class="comments">' . $reviewer_comments . '</div>
                </div>
              ';
        }

        // contributor's comment
        $question_html .= '</div>';
        $question_html .= '
                <div class="comments-title">
                    ' . t("Contributor's Comment") . '
                </div>
                <div class="">
                  ' . $contributor_comment_date . '
                </div>
                <div class="feedback-item">
                  ' . $contributor_comment . '
                </div>
              ';
        $questions_and_comments_html .= '<div class="feedback-item">' . $question_html . '<div class="clear"></div></div>';
        $i++;
      }
      $recommendations_html .= '<div class="clear"></div>';
    }
    // finalize output
    return '
          <div class="feedback-wrap" id="feedback-wrap-qc-comments">
            <h2>' . t('Quality Criteria') . '</h2>
            ' . $publisher_html . '
            <div class="criteria-set-title">
              ' . t('Reviewers Resource Recommendation') . '
            </div>
            <div class="feedback-items">
              <div class="feedback-item">
                ' . $recommendations_html . '
              </div>
              ' . $questions_and_comments_html . '
            </div>
          </div>
        ';
  }

  private function getGateKeeperContent($feedback) {
    $output_gk = '';

    // get the last GK feedback
    $entity = entity_load_single('feedback', $feedback->id);
    $i = 1;
    foreach (field_entity_value($entity, 'field_quality_set') as $question) {
      $item_title = variable_get('resource_gate_keeper_criteria_' . $i . '_title');
      $item_title = filter_text($item_title);

      $item_desc = variable_get('resource_gate_keeper_criteria_' . $i . '_description');
      $item_desc = filter_text($item_desc);
      $item_desc = more_less_text($item_desc, 300);

      $level = field_entity_value($question, 'field_meets_criterion');
      $level = $level ? t('Yes') : t('No');

      $output_gk .= '
          <div class="feedback-item">
            <div class="criteria-set-title">
              ' . $i . '. ' . strip_tags($item_title) . '
            </div>
            <div class="desc">
              ' . $item_desc . '
            </div>

            <div class="criteria-set-title">' . t('Reviewer 1') . '</div>
            <div class="date">' . format_date($entity->changed, 'full') . '</div>
            <div class="headline">' . t('Quality Criteria Level: !level', array('!level' => $level)) . '</div>
            <div class="comments">' . field_entity_value($question, 'field_comments') . '</div>

            <div class="criteria-set-title">' . t("Contributor's comment") . '</div>
            <div class="date">' . format_date(field_entity_value($question, 'field_contributor_comment_date'), 'full') . '</div>
            <div class="comments">' . field_entity_value($question, 'field_contributor_comment') . '</div>
          </div>
        ';

      $i++;
    }
    return '
        <div class="feedback-wrap" id="feedback-wrap-gk-comments">
          <h2 class="main-title">' . t('Gate Keeping Criteria') . '</h2>
          <div class="feedback-items">
            ' . $output_gk . '
          </div>
        </div>
      ';
  }

  private function getFeedbacks($num = 1, $bundle = '') {
    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'feedback');
    if ($bundle != '') {
      $query->entityCondition('bundle', $bundle);
    }
    $results = $query->propertyCondition('completed', 1)
      ->propertyCondition('met_criteria', 0)
      ->propertyCondition('current', 0)
      ->propertyCondition('archived', 1)
      ->propertyCondition('node_id', $this->_node->nid)
      ->propertyOrderBy('id', 'DESC')
      ->range(0, $num)
      ->execute();
    return $results['feedback'];
  }
}

