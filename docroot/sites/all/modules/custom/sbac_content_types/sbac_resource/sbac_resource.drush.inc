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

  $items['sbac-resource-update-thumbnails'] = array(
    'description' => 'Update the resource thumbnails.',
    'examples' => array(
      'drush sbac-resource-update-thumbnails',
    ),
    'options' => array(
      'chunk-size' => array(
        'description' => 'Number of entities to process at once.',
      ),
    ),
    'callback' => 'drush_sbac_resource_update_thumbnails',
  );

  $items['sbac-resource-update-failed-thumbnails'] = array(
    'description' => 'Update the resource failed thumbnails.',
    'examples' => array(
      'drush sbac-resource-update-failed-thumbnails',
    ),
    'options' => array(
      'chunk-size' => array(
        'description' => 'Number of entities to process at once.',
      ),
    ),
    'callback' => 'drush_sbac_resource_update_failed_thumbnails',
  );

  $items['sbac-resource-move-private-to-public'] = array(
    'description' => 'Moves private thumbnails to public.',
    'examples' => array(
      'drush sbac-resource-move-private-to-public',
    ),
    'callback' => 'drush_sbac_resource_move_private_to_public',
  );

  $items['sbac-resource-move-html5-thumbnails'] = array(
    'description' => 'Move html5 thumbnails',
    'examples' => array(
      'drush sbac-resource-move-html5-thumbnails',
    ),
    'callback' => 'drush_sbac_resource_move_html5_thumbnails',
  );

  $items['sbac-resource-find-resources-with-missing-reviewers'] = array(
    'description' => 'Find resources that have no original reviewers/publishers'
  );

  $items['sbac-resource-find-extra-reviews'] = array(
    'description' => 'Find resources that are affected by the workflow bug. See 81058166',
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

/**
 * Update thumbnails URI for resource cards.
 * @return [type] [description]
 */
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

function drush_sbac_resource_update_thumbnails() {
  $current_limit = drush_memory_limit();
  ini_set('memory_limit', '1048M');

  $row = 0;
  $start_time = time();
  // drush_print('Start time', $start_time);

  $max_nid = db_query("SELECT MAX(n.nid)
                       FROM   {node} n
                       WHERE  n.type = 'resource'
                      ")->fetchField();

  $current_nid = 0;
  $chunk_size = drush_get_option('chunk-size', 25);
  // drush_print(dt('Updating thumbnails for Resource nodes.'));

  while ($current_nid <= $max_nid) {
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'))
      ->condition('n.nid', $current_nid, '>')
      ->condition('n.type', 'resource', '=')
      ->orderBy('n.nid')
      ->range(0, $chunk_size);
    $nids = $query->execute()->fetchCol();

    foreach ($nids as $nid) {
      $node = node_load($nid);
      if ($node) {
        $current_nid = $nid;
        sbac_resource_determine_thumbnail_uri($node);
        entity_save_field(array('field_thumbnail_uri'), $node, 'node', $node->nid);
        drush_print($node->nid . ' updated.');
      }
      unset($node);
    }
  }


  ini_set('memory_limit', $current_limit);
}

function drush_sbac_resource_update_failed_thumbnails() {
  $current_limit = drush_memory_limit();
  ini_set('memory_limit', '1048M');

  $row = 0;
  $start_time = time();
  // drush_print('Start time', $start_time);

  $max_nid = db_query("SELECT MAX(n.nid)
                       FROM   {node} n
                       WHERE  n.type = 'resource'
                      ")->fetchField();

  $current_nid = 0;
  $chunk_size = drush_get_option('chunk-size', 25);
  // drush_print(dt('Updating thumbnails for Resource nodes.'));

  while ($current_nid <= $max_nid) {

    $db_or = db_or()->condition('ft.field_thumbnail_uri_value', array(
        '::',
        'public://file.png::public://file.png',
        'no_img::no_img'
      ), 'IN')
      ->condition('ft.field_thumbnail_uri_value', '%x-empty%', 'LIKE');

    $query = db_select('field_data_field_thumbnail_uri', 'ft');
    $query->fields('ft', array('entity_id'))
      ->condition('ft.entity_id', $current_nid, '>')
      ->condition($db_or)
      ->orderBy('ft.entity_id')
      ->range(0, $chunk_size);
    $nids = $query->execute()->fetchCol();

    foreach ($nids as $nid) {
      $node = node_load($nid);
      if ($node) {
        $current_nid = $nid;
        sbac_resource_determine_thumbnail_uri($node);
        entity_save_field(array('field_thumbnail_uri'), $node, 'node', $node->nid);
        drush_print($node->nid . ' updated.');
      }
      unset($node);
    }
  }
  ini_set('memory_limit', $current_limit);
}

/**
 * Moves the already generated thumbnail from private
 * to a public directory, else tries to re-create the thumbnail
 * and place in public directory.
 */
function drush_sbac_resource_move_private_to_public() {
  ini_set('memory_limit', '1048M');

  $max_nid = db_query("SELECT MAX(n.nid)
                       FROM   {node} n
                       WHERE  n.type = 'resource'
                      ")->fetchField();

  $current_nid = 0;
  $chunk_size = drush_get_option('chunk-size', 300);
  while ($current_nid <= $max_nid) {
    $query = db_select('node', 'n');
    $query->fields('n', array('nid'))
      ->condition('n.nid', $current_nid, '>')
      ->condition('n.type', 'resource', '=')
      ->orderBy('n.nid')
      ->range(0, $chunk_size);
    $nids = $query->execute()->fetchCol();

    foreach ($nids as $nid) {
      $node = node_load($nid);
      if ($node) {
        $current_nid = $nid;
        if (isset($node->field_thumbnail_uri['und'][0]['value']) && $node->field_thumbnail_uri['und'][0]['value'] != NULL) {
          $location = $node->field_thumbnail_uri['und'][0]['value'];
          if (strpos($location, 'x-empty') !== FALSE) {
            sbac_resource_determine_thumbnail_uri($node);
            entity_save_field(array('field_thumbnail_uri'), $node, 'node', $node->nid);
          }
          else if (strpos($location, 'private://resource_thumbnails') !== FALSE) {
            // Get the private location.
            sbac_resource_move_private_to_public($node);
          }
          else if (strpos($location, 'public://resource_thumbnails') === FALSE && strpos($location, 'no_img::no_img') === FALSE) {
            sbac_resource_determine_thumbnail_uri($node);
            entity_save_field(array('field_thumbnail_uri'), $node, 'node', $node->nid);
          }
          drush_print($node->nid . ' updated.');
        }
      }
      unset($node);
    }
  }
}

/**
 * Move the HTML5 thumbnails.
 */
function drush_sbac_resource_move_html5_thumbnails() {
  $result = db_query("SELECT n.nid FROM {node} n JOIN {field_data_field_html5} f ON n.nid = f.entity_id WHERE  n.type = 'resource' AND f.field_html5_value = 1");
  foreach ($result as $row) {
    $node = node_load($row->nid);
    if ($node) {
      sbac_resource_move_html5_thumbnail($node);
    }
    drush_print($node->nid . ' updated.');
  }
}

/**
 * Find resources with missing original reviewers/publishers
 */
function drush_sbac_resource_find_resources_with_missing_reviewers() {
  // Get all resources that haven't been published yet
  $resources = db_select('workbench_moderation_node_history', 'h')
    ->condition('h.current', 1)
    ->condition('h.state', 'published', '<>')
    ->fields('h', array('nid', 'state'))
    ->orderBy('h.state')
    ->orderBy('h.nid')
    ->execute()
    ->fetchAll();
  foreach ($resources as $resource) {
    $row = array();
    $rejected = db_select('workbench_moderation_node_history', 'h')
      ->condition('h.state', 'rejected')
      ->condition('h.nid', $resource->nid)
      ->fields('h')
      ->countQuery()
      ->execute()
      ->fetchField();
    if ($rejected) {
      $reviewers = db_select('field_data_field_recent_reviewers', 'r')
        ->condition('r.entity_id', $resource->nid)
        ->condition('r.field_recent_reviewers_target_id', 0, '>')
        ->fields('r', array())
        ->countQuery()
        ->execute()
        ->fetchField();
      if (!$reviewers) {
        $row[] = $resource->nid;
        $row[] = 'no reviewers';
      }
    }
    $approve = db_select('workbench_moderation_node_history', 'h')
      ->condition('h.state', 'approve')
      ->condition('h.nid', $resource->nid)
      ->condition('h.current', 0)
      ->fields('h')
      ->countQuery()
      ->execute()
      ->fetchField();
    if($approve){
      $publishers = db_select('field_data_field_recent_publishers', 'r')
        ->condition('r.entity_id', $resource->nid)
        ->condition('r.field_recent_publishers_target_id', 0, '>')
        ->fields('r', array())
        ->countQuery()
        ->execute()
        ->fetchField();
      if (!$publishers) {
        $row[] = $resource->nid;
        $row[] = 'no publishers';
      }
    }
    if (!empty($row)) {
      $query = db_select('node', 'n');
      $query->leftJoin('users', 'u', 'u.uid = n.uid');
      $query->leftJoin('workbench_moderation_node_history', 'h',
        'h.nid = n.nid');
      $query->leftJoin('field_data_field_state', 's', 's.entity_id = n.nid');
      $query->leftJoin('taxonomy_term_data', 't', 't.tid = s.field_state_tid');
      $query->condition('n.nid', $resource->nid);
      $query->fields('h', array('state'))
        ->fields('n', array('title'))
        ->fields('u', array('name', 'mail'))
        ->fields('t', array('name'));
      $info = $query->execute()->fetchAll();
      foreach ($info as $r) {
        $row = array_merge($row, (array) $r);
      }
      drush_print(implode(' | ', $row));
    }
  }
}