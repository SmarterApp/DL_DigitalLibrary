<?php
namespace sbac_core\components\feedback\sections;

class Revisions extends Base {
  const name = 'revisions';
  const title = 'Revisions';
  const permission = 'access quality criteria revisions';

  private $post_count = 0;
  private $qc_count = 0;
  private $gk_count = 0;

  private $reviews = array();

  private $output = '';

  /**
   * Builds and returns the content for current section.
   * @return string [type] [description]
   */
  public function getContent() {
    // Find out at what stage was the resource returned.
    // Get the last feedback
    $results = $this->getFeedbacks('all');
    if (!empty($results)) {
      // count and collect quality criteria reviews for display
      foreach ($results as $result) {
        switch ($result->type) {
          case 'post':
            $this->post_count++;
            $this->reviews['post-' . $this->post_count] = $result;
            break;
          case 'qc':
            isset($this->reviews['qc-' . $this->qc_count]) ? $this->reviews['qc-' . $this->qc_count][] = $result : $this->reviews['qc-' . $this->qc_count] = array($result);
            break;
          case 'gate_keeper':
            $this->gk_count++;
            $this->reviews['gk-' . $this->gk_count] = $result;
            if (isset($this->reviews['qc-' . $this->qc_count])) {
              krsort($this->reviews['qc-' . $this->qc_count]);
              $this->qc_count++;
            }
            break;
        }
      }
      foreach ($this->reviews as $key => $feedback) {
        switch (preg_replace("/^(.+?)-.+$/", "$1", $key)) {
          case 'post':
            $this->getPostContent($key);
            break;
          case 'qc':
            $this->getReviewerContent($key);
            break;
          case 'gk':
            $this->getGateKeeperContent($key);
            break;
        }
      }
    }

    return $this->output;
  }

  private function getPostContent($key) {
    $publisher_feedback = entity_load_single('feedback', $this->reviews[$key]->id);
    $contributor_comment = field_entity_value($publisher_feedback, 'field_contributor_comment');
    $comment = '';
    if ($contributor_comment != '') {
      $comment= '<div class="contributor-comment">
              <div class="contributor-comment-title">Contributor\'s Comment</div>
              <div class="contributor-comment-date">'.format_date(field_entity_value($publisher_feedback, 'field_contributor_comment_date'), 'full').'</div>
              <div class="contributor-comment-comment">'.field_entity_value($publisher_feedback, 'field_contributor_comment').'</div>
            </div>';
    }

    $comments = array();
    if ($to_contributor = field_entity_value($publisher_feedback, 'field_to_contributor')) {
      $comments[0] = more_less_text($to_contributor, 140);
    }
    if ($to_reviewer = field_entity_value($publisher_feedback, 'field_to_reviewer_1')) {
      $comments[1] = more_less_text($to_reviewer, 140);
    }
    if ($to_reviewer = field_entity_value($publisher_feedback, 'field_to_reviewer_2')) {
      $comments[2] = more_less_text($to_reviewer, 140);
    }
    if ($to_reviewer = field_entity_value($publisher_feedback, 'field_to_reviewer_3')) {
      $comments[3] = more_less_text($to_reviewer, 140);
    }

    $question_html = '<div class="feedback-item-triplet">';

    foreach ($comments as $key => $value) {
      if ($key == 0) {
        $author = t('To Contributor');
      } else {
        $author = t('To Reviewer @num', array('@num' => $key));
      }

      $question_html .= '
          <div class="feedback-comment">
            <div class="headline">' . $author . '</div>
            <div class="comments-content">' . $value . '</div>
          </div>
        ';
    }
    $question_html .= '</div>';

    $this->output .= '
          <div class="feedback-wrap" id="feedback-wrap-post-comments">
            <h2><a href="#" class="feedback-section-title more">' . t('Posting Comments @count', array('@count' => $this->post_count)) . '</a></h2>
            <div class="feedback-items feedback-section-drop">
              <div class="feedback-item">
                ' . $question_html . '<div class="clear"></div>
                '.$comment.'
              </div>
            </div>
          </div>
        ';
    $this->post_count--;
  }

  private function getReviewerContent($key) {
    $recommendations_html = '';
    $questions_and_comments_html = '';

    $feedbacks = array();
    foreach ($this->reviews[$key] as $review) {
      $feedbacks[] = entity_load_single('feedback', $review->id);
    }

    // recommendations
    $i = 1;
    foreach ($feedbacks as $entity) {
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
      $i++;
    }
    $recommendations_html .= '<div class="clear"></div>';

    // QC questions
    $focus = field_get_value($this->_node, 'field_focus', 'tid');
    $questions_count = sizeof(field_entity_value(reset($feedbacks), 'field_review_set'));
    for ($i = 0; $i < $questions_count; $i++) {
      $question_title = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_title');
      $question_title = filter_text($question_title);

      $question_desc = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_description');
      $question_desc = filter_text($question_desc);
      $question_desc = more_less_text($question_desc, 300);

      $question_html = '
        <div class="criteria-set-title-question">
          ' . ($i + 1) . '. ' . strip_tags($question_title) . '
        </div>
        <div class="criteria-set-commentes-text">
          ' . $question_desc . '
        </div>
        <div class="comments-title-comments">
          ' . t("Reviewer's Comments") . '
        </div>
     ';
      $j = 1;
      $question_html .= '<div class="feedback-item-triplet">';

      $contributor_comment = '';
      $contributor_comment_date = '';

      foreach ($feedbacks as $entity) {
        $questions = field_entity_value($entity, 'field_review_set');

        $level = field_entity_value($questions[$i], 'field_level');
        $comments = field_entity_value($questions[$i], 'field_comments');
        $comments = more_less_text($comments, 140);

        // the contributor's comment is the same for all 3 reviewers, so we only need to get one
        if ($contributor_comment == '') {
          $contributor_comment = field_entity_value($questions[$i], 'field_contributor_comment');
          $contributor_comment_date = format_date(field_entity_value($questions[$i], 'field_contributor_comment_date'), 'full');
        }

        $question_html .= '
          <div class="feedback-review">
            <div class="author">' . t('Reviewer !j', array('!j' => $j)) . '</div>
            <div class="created">' . format_date($entity->created, 'full') . '</div>
            <div class="headline">' . t('Quality Criteria Level: !level', array('!level' => $level)) . '</div>
            <div class="comments-content">' . $comments . '</div>
          </div>
        ';
        $j++;
      }
      $question_html .= '</div>';

      // contributor's comment
      if ($contributor_comment != '') {
        $question_html .= '
          <div class="comments-title-contributor">
              ' . t("Contributor's Comment") . '
          </div>
          <div class="created">
            ' . $contributor_comment_date . '
          </div>
          <div class="feedback-content">
            ' . $contributor_comment . '
          </div>
        ';
      }

      $questions_and_comments_html .= '<div class="feedback-item">' . $question_html . '<div class="clear"></div></div>';
    }

    // finalize output
    $this->output .= '
          <div class="feedback-wrap" id="feedback-wrap-qc-comments">
            <h2><a href="#" class="feedback-section-title more">' . t('Quality Criteria @count', array('@count' => $this->qc_count)) . '</a></h2>
            <div class="feedback-section-drop">
              <div class="criteria-set-title-recommendation">
                ' . t('Reviewers Resource Recommendation') . '
              </div>
              <div class="feedback-items">
                <div class="feedback-item">
                  ' . $recommendations_html . '
                </div>
                ' . $questions_and_comments_html . '
              </div>
            </div>
          </div>
        ';
    $this->qc_count--;
  }

  private function getGateKeeperContent($key) {
    $output_gk = '';

    // get the last GK feedback
    $entity = entity_load_single('feedback', $this->reviews[$key]->id);
    $i = 1;
    foreach (field_entity_value($entity, 'field_quality_set') as $question) {
      $item_title = variable_get('resource_gate_keeper_criteria_' . $i . '_title');
      $item_title = filter_text($item_title);

      $item_desc = variable_get('resource_gate_keeper_criteria_' . $i . '_description');
      $item_desc = filter_text($item_desc);
      $item_desc = more_less_text($item_desc, 300);

      $level = field_entity_value($question, 'field_meets_criterion');
      $level = $level ? t('Yes') : t('No');

      $contributor_comment = field_entity_value($question, 'field_contributor_comment');

      $output_gk .= '
          <div class="feedback-item">
            <div class="criteria-set-title-gate-keeper">
              ' . $i . '. ' . strip_tags($item_title) . '
            </div>
            <div class="desc">
              ' . $item_desc . '
            </div>

            <div class="criteria-set-title-reviewer">' . t('Reviewer 1') . '</div>
            <div class="date">' . format_date($entity->changed, 'full') . '</div>
            <div class="headline">' . t('Meets Criteria: !level', array('!level' => $level)) . '</div>
            <div class="comments-content">' . field_entity_value($question, 'field_comments') . '</div>
            ';
      if ($contributor_comment != '') {
        $output_gk .= '
            <div class="criteria-set-title-contributor">' . t("Contributor's comment") . '</div>
            <div class="date">' . format_date(field_entity_value($question, 'field_contributor_comment_date'), 'full') . '</div>
            <div class="comments-content">' . $contributor_comment . '</div>
            ';
      }
      $output_gk .= '
          </div>
        ';

      $i++;
    }
    if ($output_gk) {

      $this->output .= '
          <div class="feedback-wrap" id="feedback-wrap-gk-comments">
            <h2 class="main-title"><a href="#" class="feedback-section-title more">' . t('Gatekeeping Criteria @count', array('@count' => $this->gk_count)) . '</a></h2>
            <div class="feedback-items feedback-section-drop">
              ' . $output_gk . '
            </div>
          </div>
      ';
      $this->gk_count--;
    }
  }

  private function getFeedbacks($num = 1, $bundle = FALSE) {
    $query = new \EntityFieldQuery();
    $query->entityCondition('entity_type', 'feedback');
    if ($bundle) {
      $query->entityCondition('bundle', $bundle);
    }
    if ($num == 'all') {
      $results = $query->propertyCondition('completed', 1)
        ->propertyCondition('node_id', $this->_node->nid)
        ->propertyOrderBy('created', 'DESC')
        ->execute();
    }
    elseif (is_array($num)) {
      $results = $query->propertyCondition('completed', 1)
        ->propertyCondition('node_id', $this->_node->nid)
        ->propertyOrderBy('created', 'DESC')
        ->range($num[0], $num[1])
        ->execute();
    }
    else {
      $results = $query->propertyCondition('completed', 1)
        ->propertyCondition('node_id', $this->_node->nid)
        ->propertyOrderBy('created', 'DESC')
        ->range(0, $num)
        ->execute();
    }
    return $results['feedback'];
  }
}
