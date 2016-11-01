<?php

/**
 * Returns the number of hours left between the entity's creation date
 * and the max limit.
 * @param  [type] $entity    [description]
 * @param  [type] $max_hours [description]
 * @return [type]            [description]
 */
function feedback_hours_left($entity, $max_hours = FEEDBACK_REVIEW_TIMEOUT) {
  if (!isset($entity->created)) {
    return FEEDBACK_REVIEW_TIMEOUT;
  }

  $now = new \DateTime(date(DATE_ATOM));
  $created = new \DateTime(date(DATE_ATOM, $entity->created));

  $diff = $created->diff($now);

  return FEEDBACK_REVIEW_TIMEOUT - ($diff->h + $diff->days * 24);
}

/**
 * Returns the states for recommendation options.
 * @return [type] [description]
 */
function feedback_recommendation_states() {
  $states = array(
    0 => 'not_recommend',
    1 => 'recommend_reservation',
    2 => 'recommend',
    3 => 'recommend_distinction',
  );

  return $states;
}

/**
 * Returns the states for post options.
 * @return [type] [description]
 */
function feedback_post_states() {
  $states = array(
    0 => 'reject',
    1 => 'post',
    2 => 'post_distinction',
  );

  return $states;
}

/**
 * Returns label text for specfied field.
 * @param  [type] $field_name [description]
 * @return [type]             [description]
 */
function resource_field_label($field_name) {
  // $info = field_info_instance('node', $field_name, 'resource');

  $map = array(
    'field_attributes' => 'Attributes of Formative Assessment Process',
    'field_student_agency' => 'Student Engagement in the Formative Assessment Process',
    'field_focus' => 'Resource Type',
    'field_alt_body' => 'Resource Summary',
    'field_learning_goals' => 'Learning Goals',
    'field_success_criteria' => 'Success Criteria',
    'field_supporting_evidence' => 'Supporting Evidence',
    'field_contexts' => 'Context(s) Within Which the Resource Could Be Used',
    'field_connection_to_ccss' => 'Specific Connection to the Common Core State Standards',
    'field_connection_to_fap' => 'Specific Connection to the Formative Assessment Process',
    'field_principles' => 'Principles, Literature, or Research',
  );

  if (isset($map[$field_name])) {
    return $map[$field_name];
  }

  return '';
}

/**
 * Sets taskit notifications for resource author and reviewers.
 * @param  [type] $task    [description]
 * @param  [type] $node    [description]
 * @param  [type] $reviews [description]
 * @return [type]          [description]
 */
function send_review_notifications($task, $node, $reviews) {
  if ($task) {
    global $user;

    $task->addVisibility($task::VISIBILITY_USER);
    $task->addEntity('node', $node->nid);

    // resource contributor
    $task->addOwningUser($node->uid);
    // resource reviewers
    foreach ($reviews as $entity) {
      $task->addOwningUser($entity->uid);
      $task->addEntity('feedback', $entity->id);
    }

    $task->addTriggeringUser(1);
    $task->save();
  }
}

/**
 * Class feedbackStatus
 * Creates an object which includes the current QC status of the node.
 */
class feedbackStatus
{
  public $qc_count = 3; // The number of QCs that are needed for this node.
  public $gatekeeper_started = 0; // If the Gate Keeper review has started.
  public $gatekeeper_finished = 0; // If the Gate Keeper review is finished (only if criteria are met).
  public $qc_num_finished = 0; // The number of finished QCs.
  public $qc_status = array(); // An array of the QCs and their status ('started' and 'finished').
  public $post_started = 0; // Whether the Post review has started.
  public $post_finished = 0; // Whether the Post review has finished.

  public function __construct(&$node, $type = false)
  {
    if (is_int($node) || (is_string($node) && preg_match("/^\d+$/", $node))) {
      $nid = $node;
    } else {
      $nid = $node->nid;
      $type = $node->field_focus[LANGUAGE_NONE][0]['tid'];
    }
    // Set required quality reviews to 2 for playlists.
    if ($type == '78306') {
      $this->qc_count = 2;
    }

    // Get all of the feedback for this node that is current and active.
    $query = db_select('eck_feedback', 'f');
    $query->fields('f', array('id', 'type', 'uid', 'completed', 'met_criteria'));
    $query->condition('node_id', $nid);
    $query->condition('current', 1);
    $query->condition('status', 1);
    $results = $query->execute();

    while ($result = $results->fetchAssoc()) {
      switch ($result['type']) {
        case 'gate_keeper':
          // It's active, so it's started.
          $this->gatekeeper_started = 1;
          if ($result['completed'] == 1 && $result['met_criteria'] == 1) {
            // It's completed and the criteria were met, so it's finished.
            $this->gatekeeper_finished = 1;
          }
          break;
        case 'qc':
          $current = count($this->qc_status);
          // It's active, so it's started.
          $this->qc_status[$current]['started'] = 1;
          $this->qc_status[$current]['finished'] = 0;
          if ($result['completed'] == 1) {
            // It's completed, so it's finished.
            $this->qc_status[$current]['finished'] = 1;
            $this->qc_num_finished++;
          }
          break;
        case 'post':
          // It's active, so it's started.
          $this->post_started = 1;
          if ($result['completed'] == 1) {
            // It's completed, so it's finished.
            $this->post_finished = 1;
          }
          break;
      }
    }
    // Add the rest of the QC review statuses.
    for ($x = count($this->qc_status); $x < $this->qc_count; $x++) {
      $this->qc_status[$x]['started'] = 0;
      $this->qc_status[$x]['finished'] = 0;
    }
  }
}
