<?php
namespace sbac_core\components\feedback\sections;

class Qc_Comments extends Base {
  const name = 'qc_comments';
  const title = 'Quality Criteria Comments';
  const permission = 'access qc review comments';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    // build POST output
    $output_post = '';

    $post_entities = entity_load('feedback', FALSE, array(
      'node_id' => $this->_node->nid,
      'type' => 'post',
      'status' => 1,
      'current' => 1,
      'completed' => 1,
    ));

    if ($post_entities) {
      $entity = current($post_entities);

      $output_post = '
          <div class="feedback-item">
            <div class="criteria-set-title">
              ' . t('Posting Comments') . '
            </div>
            <div class="comments">' . field_entity_value($entity, 'field_to_contributor') . '</div>
          </div>
        ';
    }


    // build QC recommendations
    $output_rec = '';

    // get the last qc feedback from the last cycle
    $qcs = db_select('eck_feedback','f')
      ->condition('f.type', 'qc')
      ->condition('f.completed',1)
      ->condition('f.node_id', $this->_node->nid)
      ->where('f.created > (SELECT h.stamp FROM workbench_moderation_node_history h WHERE h.nid = :nid AND h.state = \'needs_review\' ORDER BY h.hid DESC LIMIT 0, 1)', array(':nid' => $this->_node->nid))
      ->fields('f', array('id'))
      ->orderBy('f.created', 'ASC')
      ->execute()
      ->fetchCol();

    if (empty($qcs)){
      // if there are no qc's, go back one more cycle.  This is because if the resource is returned from arbitration
      // upon resubmission, it will skip all the gk and qc and will go straight to arbitration again. In this case,
      // there will be no gk or qc for this cycle.
      $qcs = db_select('eck_feedback','f')
        ->condition('f.type', 'qc')
        ->condition('f.completed',1)
        ->condition('f.node_id', $this->_node->nid)
        ->where('f.created > (SELECT h.stamp FROM workbench_moderation_node_history h WHERE h.nid = :nid AND h.state = \'needs_review\' ORDER BY h.hid DESC LIMIT 1, 1)', array(':nid' => $this->_node->nid))
        ->fields('f', array('id'))
        ->orderBy('f.created', 'ASC')
        ->execute()
        ->fetchCol();
    }


    $qc_entities = entity_load('feedback', $qcs);

    $i = 1;
    foreach ($qc_entities as $entity) {

      $created = format_date($entity->created, 'full');

      $options = field_allowed_values('field_rec_options');

      $headline = $options[field_entity_value($entity, 'field_rec_options')];
      $comments = field_entity_value($entity, 'field_rec_rationale');

      $output_rec .= theme('qc_teaser', array(
        'id' => $entity->id,
        'author' => t('Reviewer !count', array('!count' => $i)),
        'created' => $created,
        'headline' => $headline,
        'comments' => more_less_text($comments, 140),
      ));

      $i++;
      if ($i == 4) {
        $output_rec .= '<div class="clear"></div>';
      }
    }

    // build QC questions
    $output_qc = '';
    $focus = field_get_value($this->_node, 'field_focus', 'tid');
    $questions_count = sizeof(field_entity_value(reset($qc_entities), 'field_review_set'));
    for ($i = 0; $i < $questions_count; $i++) {
      $item_title = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_title');
      $item_title = filter_text($item_title);

      $item_desc = variable_get('qc_' . $focus . '_criteria_' . ($i + 1) . '_description');
      $item_desc = filter_text($item_desc);
      $item_desc = more_less_text($item_desc, 300);

      $output_item = '
                          <div class="criteria-set-title">
                            ' . ($i + 1) . '. ' . strip_tags($item_title) . '
                          </div>
                          <div class="criteria-set-commentes-text">
                            ' . $item_desc . '
                          </div>
                          <div class="comments-title">
                            ' . t("Reviewer's Comments") . '
                          </div>
                       ';

      $j = 1;
      $output_item .= '<div class="feedback-item-triplet">';
      foreach ($qc_entities as $entity) {
        $questions = field_entity_value($entity, 'field_review_set');

        $level = field_entity_value($questions[$i], 'field_level');
        $comments = field_entity_value($questions[$i], 'field_comments');
        $comments = more_less_text($comments, 140);

        $output_item .= '
                            <div class="feedback-review">
                              <div class="author">' . t('Reviewer !j', array('!j' => $j)) . '</div>
                              <div class="created">' . format_date($entity->created, 'full') . '</div>
                              <div class="headline">' . t('Quality Criteria Level: !level', array('!level' => $level)) . '</div>
                              <div class="comments">' . $comments . '</div>
                            </div>
                          ';

        $j++;
      }
      $output_item .= '</div>';

      $output_qc .= '<div class="feedback-item">' . $output_item . '<div class="clear"></div></div>';
    }

    // finalize output
    $output = '
                    <div class="feedback-wrap" id="feedback-wrap-qc-comments">
                      <h2>' . t('Quality Criteria') . '</h2>

                      ' . $output_post . '
                    
                      <div class="criteria-set-title">
                        ' . t('Reviewers Resource Recommendation') . '
                      </div>

                      <div class="feedback-items">
                        <div class="feedback-item">
                          ' . $output_rec . '
                        </div>

                        ' . $output_qc . '
                      </div>
                    </div>
                 ';

    return $output;
  }
}

