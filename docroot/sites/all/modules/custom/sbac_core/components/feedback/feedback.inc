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