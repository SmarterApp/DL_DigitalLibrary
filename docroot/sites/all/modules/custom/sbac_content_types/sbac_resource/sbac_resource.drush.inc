<?php

/**
 * @file
 * Drush-related callbacks for SBAC Resources module.
 */

/**
 * Implementation of hook_drush_command()
 *
 */
function sbac_resource_drush_command() {
  $items = array();

  $items['sbac-resource-recalc-review-avg'] = array(
    'description' => "Calculate and update the average total review score for every Review entity.",
    'examples' => array(
      'drush sbac-resource-recalc-review-avg',
    ),
    'options' => array(
      'chunk-size' => array(
        'description' => 'Number of entities to process at once.',
      )
    ),
    'callback' => 'drush_sbac_resource_update_review_averages',
  );

  $items['sbac-resource-recalc-node-avg-rating'] = array(
    'description' => "Calculate and update the average total review score for every Resource node.",
    'examples' => array(
      'drush sbac-resource-recalc-node-avg-rating',
    ),
    'options' => array(
      'chunk-size' => array(
        'description' => 'Number of entities to process at once.',
      )
    ),
    'callback' => 'drush_sbac_resource_update_node_review_averages',
  );

  return $items;
}


/**
 * =============================================================================
 *    Drush callbacks
 * =============================================================================
 */

function drush_sbac_resource_update_review_averages() {
  $start = time();
  $row = 0;

  // Get the last review entity's node id.
  $max_eid = 0;
  $entity_type = 'review';
  $entity_bundle = 'end_use';
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type)
    ->entityCondition('bundle', $entity_bundle)
    ->entityOrderBy('entity_id', 'DESC')
    ->range(0, 1);
  $result = $query->execute();
  if (!empty($result[$entity_type])) {
    $max_entity = array_shift($result[$entity_type]);
    $max_eid = $max_entity->id;
  }

  $current_eid = 0;
  $chunk_size = drush_get_option('chunk-size', 100);

  drush_print(dt('Updating average scores for Review entities.'));

  // Field names for the fivestar fields.
  $rating_fields = array(
    'field_student_learning',
    'field_pro_dev',
    'field_ease_use',
  );
  $avg_score_field = 'field_avg_rating';

  // Loop through all entities.
  while ($current_eid <= $max_eid) {
    // Get subset of entities. Process them in smaller batches.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type)
      ->entityCondition('bundle', $entity_bundle)
      ->entityCondition('entity_id', $current_eid, '>')
      ->entityOrderBy('entity_id', 'ASC')
      ->range(0, $chunk_size);
    $result = $query->execute();
    if ($result[$entity_type]) {
      $review_ids = array_keys($result[$entity_type]);
      $reviews = entity_load($entity_type, $review_ids);
    }

    foreach ($reviews as $eid => $review) {
      if (!empty($review)) {
        // Get the average scores for this review.
        $rating_total = 0;
        $rating_avg = 0;
        $review_wrapper = entity_metadata_wrapper($entity_type, $review);
        foreach ($rating_fields as $rating_field) {
          $score = $review_wrapper->{$rating_field}->value();
          $rating_total += $score;
        }
        $rating_avg = $rating_total / count($rating_fields);

        // Save the entity.
        $review_wrapper->{$avg_score_field}->set($rating_avg);
        $review_wrapper->save();
      }
      $current_eid = $eid;

      // Log progress
      $row++;
      if ($row %1000 == 0) {
        drush_print('.', 0, NULL, FALSE);
      }
    }

    if ($current_eid == $max_eid) {
      break;
    }
  }

  // Cleanup.
  $end = time();
  $throughput = round($row / ($end - $start));

  // Clear line.
  drush_print();
  // Output metrics.
  drush_print("Total review entities processed: $row");
  drush_print("Throughput: $throughput entities /sec");
}



function drush_sbac_resource_update_node_review_averages() {
  $start = time();
  $row = 0;

  // Get last node of type resource thats published (according to workbench).
  //   This is used as the marker for the last node to process.
  $max_nid = db_query("SELECT MAX(n.nid)
  FROM {node} n
  LEFT JOIN {workbench_moderation_node_history} wb
    ON n.nid = wb.nid
  WHERE n.type = 'resource'
    AND wb.state = 'published'
    AND wb.published = 1
    AND wb.current = 1 ")->fetchField();
  $current_nid = 0;
  $chunk_size = drush_get_option('chunk-size', 25);

  drush_print(dt('Updating total average rating score for Resource nodes.'));

  // Query the database for nodes until max_nid is reached.
  //   Restrict the query based on server capacity, default is 25 nodes per query.
  while ($current_nid <= $max_nid) {
    $query = db_select('node', 'n');
    $query->join('workbench_moderation_node_history', 'wb', 'n.nid = wb.nid');
    $query->fields('n', array('nid'))
      ->condition('n.nid', $current_nid, '>')
      ->condition('n.type', 'resource', '=')
      ->condition('wb.current', 1, '=') // Use workbench published status.
      ->condition('wb.published', 1, '=') // Use workbench published status.
      ->condition('wb.state', 'published', '=') // Use workbench published status.
      ->orderBy('n.nid')
      ->range(0, $chunk_size);
    $nids = $query->execute()->fetchCol();

    // Dont node load here, function will already node load.
    foreach ($nids as $nid) {
      if (!empty($nid)) {
        sbac_resource_update_average_rating_score($nid);
      }
      $current_nid = $nid;

      // Log progress
      $row++;
      if ($row %100 == 0) {
        drush_print('.', 0, NULL, FALSE);
      }
    }

    if ($current_nid == $max_nid) {
      break;
    }
  }

  // Cleanup.
  $end = time();
  $throughput = round($row / ($end - $start));

  // Clear line.
  drush_print();
  // Output metrics.
  drush_print("Total Resource nodes processed: $row");
  drush_print("Throughput: $throughput entities /sec");
}