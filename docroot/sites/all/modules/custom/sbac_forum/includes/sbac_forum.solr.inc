<?php



/**
 * Implements hook_apachesolr_index_document_build().
 */
function sbac_forum_apachesolr_index_document_build(ApacheSolrDocument $document, $entity, $entity_type, $env_id) {
  $valid_document = FALSE;
  $forum_data = NULL;
  switch($entity_type) {
    case 'taxonomy_term':
      if ($entity->vocabulary_machine_name == 'forum') {
        $forum_data = entity_metadata_wrapper('taxonomy_term', $entity);
        $valid_document = TRUE;
      }
      break;
    case 'node':
      if ($entity->type == 'topic') {
        $topic_data = entity_metadata_wrapper($entity_type, $entity);
        $forum_parent = $topic_data->field_topic_forum_parent->value();

        $forum_data = entity_metadata_wrapper('taxonomy_term', $forum_parent);
        $valid_document = TRUE;
      }
      break;
    case 'comment':
      if ($entity->node_type == 'comment_node_topic') {
        $comment_data = entity_metadata_wrapper($entity_type, $entity);
        $forum_parent = $comment_data->node->field_topic_forum_parent->value();

        $forum_data = entity_metadata_wrapper('taxonomy_term', $forum_parent);
        $valid_document = TRUE;
      }
      break;
  }


  if ($valid_document && !empty($forum_data)) {
    // Check to see if forum is role restricted.
    $validate_user_role = FALSE; // default to all roles have access
    if (isset($forum_data->field_forum_access_user_roles)) {
      $doc_field_key = SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_ROLE;
      $role_access = $forum_data->field_forum_access_user_roles->value();
      if (!$role_access) { // Means forum is restricted to certain roles
        $validate_user_role = TRUE;
        if (isset($forum_data->field_forum_access_role_list)) {
          $allowed_roles = $forum_data->field_forum_access_role_list->value();
          if (!empty($allowed_roles)) {
            foreach ($allowed_roles as $index => $position_term_id) {
              $document->addField($doc_field_key, $position_term_id);
            }
          }
        }
      } else { // Forum is not role restricted.
        $doc_field_key = SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_ROLE_OPEN;
        $document->addField($doc_field_key, 0);
      }
    }

    // Check to see if forum is state restricted.
    $validate_user_state = FALSE; // Default to not care about state.
    if (isset($forum_data->field_forum_access_states)) {
      $doc_field_key = SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_STATE;
      $state_access = $forum_data->field_forum_access_states->value();
      if (!$state_access) { // Means forum is restricted to certain states
        $validate_user_state = TRUE;
        if (isset($forum_data->field_state)) {
          $states = $forum_data->field_state->value();
          if (!empty($states)) {
            foreach ($states as $state) {
              $document->addField($doc_field_key, $state->tid);
            }
          }
        }
      } else { // Forum is not state restricted.
        $doc_field_key = SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_STATE_OPEN;
        $document->addField($doc_field_key, 0);
      }
    }
  }
}


/**
 * Creates a Solr query for a given user
 *
 * @param $account
 *   an account to get grants for and build a solr query
 *
 * @throws Exception
 *
 * @return SolrFilterSubQuery
 *   Instance of SolrFilterSubQuery
 */
function sbac_forum_build_role_subquery($account) {
  if (!user_access('access content', $account)) {
    throw new Exception('No access');
  }
  $access_query = apachesolr_drupal_subquery();
  $user_profile = user_load($account->uid); // Load up profile.
  $user_profile_wrapper = entity_metadata_wrapper('user', $user_profile);
  $has_role = array();
  if (isset($user_profile_wrapper->field_position)) {
    $title_terms = $user_profile_wrapper->field_position->value();
    if (!empty($title_terms)) {
      $users_title = $title_terms->tid;
      $access_query->addFilter(SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_ROLE, $users_title);
    }
  }

  $access_query->addFilter(SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_ROLE_OPEN, 0);
  return $access_query;
}

/**
 * Creates a Solr query for a given user
 *
 * @param $account
 *   an account to get grants for and build a solr query
 *
 * @throws Exception
 *
 * @return SolrFilterSubQuery
 *   Instance of SolrFilterSubQuery
 */
function sbac_forum_build_state_subquery($account) {
  if (!user_access('access content', $account)) {
    throw new Exception('No access');
  }
  $access_query = apachesolr_drupal_subquery();
  $user_profile = user_load($account->uid); // Load up profile.
  $user_profile_wrapper = entity_metadata_wrapper('user', $user_profile);
  $has_state = array();
  if (isset($user_profile_wrapper->field_state)) {
    $state_terms = $user_profile_wrapper->field_state->value();
    if (!empty($state_terms)) {
      foreach ($state_terms as $state) {
        $access_query->addFilter(SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_STATE, $state->tid);
      }
    }
  }

  $access_query->addFilter(SBAC_FORUM_CUSTOM_SOLR_FILTER_FIELD_STATE_OPEN, 0);
  return $access_query;
}

/**
 * Implements hook_apachesolr_query_alter().
 *
 * Alter the query to include the access subquery
 *
 * @param DrupalSolrQueryInterface $query
 *
 */
function sbac_forum_apachesolr_query_alter(DrupalSolrQueryInterface $query) {
  global $user;
  try {
    $role_subquery = sbac_forum_build_role_subquery($user);
    $query->addFilterSubQuery($role_subquery);
    $state_subquery = sbac_forum_build_state_subquery($user);
    $query->addFilterSubQuery($state_subquery);
  }
  catch (Exception $e) {
    watchdog("apachesolr_access", 'User %name (UID:!uid) cannot search: @message', array('%name' => $user->name, '!uid' => $user->uid, '@message' => $e->getMessage()));
    $query->abort_search = TRUE;
  }
}
