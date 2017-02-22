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
  public $gatekeeper_finished = 0; // If the Gate Keeper review is finished.
  public $gatekeeper_approved = 0; // If the Gate Keeper review was passed.
  public $gatekeeper_uid = null; // The uid of the user doing the gatekeeping review.
  public $qc_num_started = 0; // The number of started QCs.
  public $qc_num_finished = 0; // The number of finished QCs.
  public $qc_status = array(); // An array of the QCs and their status ('started' and 'finished').
  public $post_started = 0; // Whether the Post review has started.
  public $post_finished = 0; // Whether the Post review has finished.
  public $post_approved = 0; // Whether the Post review was approved.
  public $post_uid = null; // The uid of the user doing the gatekeeping review.
  public $post_resubmission = 0; // Whether this resource was resubmitted to the Post reviewer.

  public function __construct(&$node, $type = false)
  {
    if (is_int($node) || (is_string($node) && preg_match("/^\d+$/", $node))) {
      $nid = $node;
      $node = node_load($nid);
    } else {
      $nid = $node->nid;
      $type = $node->field_focus[LANGUAGE_NONE][0]['tid'];
    }
    // Set required quality reviews to 2 for playlists.
    $playlist_term = array_keys(taxonomy_get_term_by_name('Playlist', 'focus'));
    $playlist_tid = (string) $playlist_term[0];
    if ($type == $playlist_tid) {
      $this->qc_count = 2;
    }

    // Add the default values for the qc_status items.
    for ($x = 0; $x < $this->qc_count; $x++) {
      $this->qc_status[$x]['started'] = 0;
      $this->qc_status[$x]['finished'] = 0;
      $this->qc_status[$x]['approved'] = 0;
      $this->qc_status[$x]['uid'] = null;
    }

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'feedback')
      ->entityCondition('type', 'gate_keeper')
      ->propertyCondition('completed', 1)
      ->propertyCondition('node_id', $nid)
      ->propertyOrderBy('id', 'DESC')
      ->range(0, 1);
    $results = $query->execute();
    if (isset($results['feedback']) && count($results['feedback']) == 1) {
      $entity_ids = array_keys($results['feedback']);
      $entity = entity_load_single('feedback', $entity_ids[0]);
      $submitted = true;
    } else {
      $submitted = false;
    }

    if ($submitted && !empty($node->field_recent_publishers[LANGUAGE_NONE])) {
      // If the node was returned by the poster, this is a post resubmission
      $this->post_resubmission = 1;

      // This went through a gatekeeping, so just mark it as done.
      $this->gatekeeper_started = 1;
      $this->gatekeeper_finished = 1;
      $this->gatekeeper_approved = 1;
      $this->gatekeeper_uid = $entity->uid;

      // Get the last qc_count archived QC reviews.
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'feedback')
        ->propertyCondition('node_id', $nid)
        ->propertyCondition('current', 0)
        ->propertyCondition('status', 0)
        ->propertyCondition('completed', 1)
        ->propertyOrderBy('id', 'DESC')
        ->range(0, $this->qc_count);
      $results = $query->execute();
      // We're starting from the last, so set the 0-based last index.
      $x = $this->qc_count - 1;
      if (isset($results['feedback']) && count($results['feedback']) == $this->qc_count) {
        // We know we have the full amount, so just set them.
        $this->qc_num_started = $this->qc_count;
        $this->qc_num_finished = $this->qc_count;
        $entity_ids = array_keys($results['feedback']);
        $entities = entity_load('feedback', $entity_ids);
        foreach ($entities as $entity) {
          // We know these were started and finished, so just set them.
          $this->qc_status[$x]['started'] = 1;
          $this->qc_status[$x]['finished'] = 1;
          $this->qc_status[$x]['uid'] = $entity->uid;
          // Only set to approved if Recommend (2) or Recommend with Distinction (3) is set.
          if ((int)$entity->field_rec_options[LANGUAGE_NONE][0]['value'] >= 2) {
            $this->qc_status[$x]['approved'] = 1;
          } else {
            $this->qc_status[$x]['approved'] = 0;
          }
          // Count down...
          $x--;
        }
      }
    } else {
      // Get all of the feedback for this node that is current and active.
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'feedback')
        ->propertyCondition('node_id', $nid)
        ->propertyCondition('current', 1)
        ->propertyCondition('status', 1)
        ->propertyOrderBy('id');
      $results = $query->execute();

      if (isset($results['feedback']) && count($results['feedback']) > 0) {
        $entity_ids = array_keys($results['feedback']);
        $entities = entity_load('feedback', $entity_ids);
        $current = 0;
        foreach ($entities as $entity) {
          switch ($entity->type) {
            case 'gate_keeper':
              if (!$this->gatekeeper_finished == 1) {
                // It's active, so it's started.
                $this->gatekeeper_started = 1;
                // Copy the finished state.
                $this->gatekeeper_finished = $entity->completed;
                // Copy the approval state.
                $this->gatekeeper_approved = $entity->met_criteria;
                // Copy the uid.
                $this->gatekeeper_uid = $entity->uid;
              }
              break;
            case 'qc':
              // It's active, so it's started.
              $this->qc_num_started++;
              $this->qc_status[$current]['started'] = 1;
              // Copy the finished state.
              $this->qc_status[$current]['finished'] = $entity->completed;
              // Copy the uid.
              $this->qc_status[$current]['uid'] = $entity->uid;
              if ($entity->completed == 1) {
                // It's completed, so add it to the count of completed reviews.
                $this->qc_num_finished++;
              }
              // Only set to approved if Recommend (2) or Recommend with Distinction (3) is set.
              if ((int)$entity->field_rec_options[LANGUAGE_NONE][0]['value'] >= 2) {
                $this->qc_status[$current]['approved'] = 1;
              } else {
                $this->qc_status[$current]['approved'] = 0;
              }
              $current++;
              break;
            case 'post':
              // It's active, so it's started.
              $this->post_started = 1;
              // Copy the finished state.
              $this->post_finished = $entity->completed;
              // Copy the uid.
              $this->post_uid = $entity->uid;
              // Only set to approved if Post (1) or Post with Distinction (2) is set.
              if ((int)$entity->field_post_options[LANGUAGE_NONE][0]['value'] > 0) {
                $this->post_approved = 1;
              } else {
                $this->post_approved = 0;
              }
              break;
          }
        }
      }
    }
  }
}
