<?php
namespace sbac_core\components\feedback\sections;

class Gk_Comments extends Base {
  const name = 'gk_comments';
  const title = 'Gate Keeper Comments';
  const permission = 'access gk review comments';

  /**
   * Builds and returns the content for current section.
   * @return [type] [description]
   */
  public function getContent() {
    // build GK output
    $output_gk = '';

    $last_gk = db_select('eck_feedback', 'f')
      ->condition('f.node_id', $this->_node->nid)
      ->condition('f.type', 'gate_keeper')
      ->condition('f.completed', 1)
      ->fields('f', array('id'))
      ->orderBy('f.changed', 'DESC')
      ->range(0, 1)
      ->execute()
      ->fetchField();

    $gk_entities = entity_load('feedback', array($last_gk));

    $entity = current($gk_entities);
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
              ' . $i . '.' . strip_tags($item_title) . '
            </div>
            <div class="desc">
              ' . $item_desc . '
            </div>

            <div class="criteria-set-title">' . t('Reviewer 1') . '</div>
            <div class="date">' . format_date($entity->created, 'full') . '</div>
            <div class="headline">' . t('Quality Criteria Level: !level', array('!level' => $level)) . '</div>
            <div class="comments">' . field_entity_value($question, 'field_comments') . '</div>
          </div>
        ';

      $i++;
    }

    // finalize output
    $output = '
        <div class="feedback-wrap" id="feedback-wrap-gk-comments">
          <h2 class="main-title">' . t('Gate Keeping Criteria') . '</h2>

          <div class="feedback-items">
            ' . $output_gk . '
          </div>
        </div>
      ';

    return $output;
  }
}

