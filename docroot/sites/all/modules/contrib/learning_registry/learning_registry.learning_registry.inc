<?php
/**
 * @file
 * Handles all learning registry specific functionality
 */

/**
 * Publish node metadata to specified Learning Registry node.
 *
 * @param object &$node
 *   A reference to the node object. We have to be very careful to not set
 *   anything, only read from the node object reference since the node
 *   reference allows us to edit the node content.
 * @param bool $headless
 *   A flag to determine if this is called from cron (non-user session).
 *
 * @return bool
 *   Returns TRUE if operation was successful, FALSE if not.
 */
function _learning_registry_publish(&$node, $headless = FALSE) {
  $content_info = _learning_registry_get_content_info($node);
  $resource_data = _learning_registry_def_resource_data($content_info);
  $empty_submission = _learning_registry_build_envelope();
  drupal_alter('learning_registry_prepared_submission', $resource_data, $node);
  $prepared_submission = _learning_registry_add_resource_data_to_submission($empty_submission, $resource_data);
  $resource_post_payload = drupal_json_encode($prepared_submission);
  $result = _learning_registry_send_to_registry($node->nid, $resource_post_payload, LEARNING_REGISTRY_MODE_PUBLISH, $headless);
  return $result;
}

/**
 * Return info we submit about nodes to the LR.
 *
 * @param object &$node
 *   A reference to the node object. We have to be very careful to not set
 *   anything, only read from the node object reference since the node
 *   reference allows us to edit the node content.
 */
function _learning_registry_get_content_info(&$node) {
  $author_user = user_load($node->uid);
  $content_info = array();
  $content_info['resource_locator'] = _learning_registry_get_node_url($node);
  $content_info['resource_data_type'] = 'metadata';
  $content_info['submitter'] = $author_user->name;
  $content_info['owner'] = variable_get('learning_registry_submitter', NULL);
  $content_info['tos'] = variable_get('learning_registry_tos', NULL);

  // Currently set curator and submitter the same, once we get a better sense
  // of what each field means, this will change.
  $content_info['curator'] = $content_info['submitter'];
  $content_info['active'] = TRUE;

  // Determine the current schema to be used.
  $schema = variable_get('learning_registry_schema_type', '');
  if (isset($schema['name'])) {
    $content_info['payload_schema'] = $schema['payload_schema'];
    if (function_exists($schema['resource_data_callback'])) {
      $resource_data = call_user_func($schema['resource_data_callback'], $node);
    }
  }

  $content_info['resource_data'] = $resource_data;
  $keys = learning_registry_extract_keys($node);
  $content_info['keys'] = $keys;

  // Add key location and signature.
  $content_info['key_location'] = explode(',', variable_get('learning_registry_key_location', ''));
  $content_info['signing_method'] = variable_get('learning_registry_signing_method', 'LR-PGP.1.0');
  $content_info['signature'] = strip_tags(file_get_contents($content_info['key_location'][0]));

  return $content_info;
}

/**
 * Return the absolute URL to a node.  If alias available,  return alias.
 *
 * @param object $node
 *   The node.
 *
 * @return string
 *   The absolute URL to the node.  If alias available, return alias.
 */
function _learning_registry_get_node_url(&$node) {

  // URL Type is an admin setting.  Return either alias or node ID.
  if (variable_get('learning_registry_url_type', LEARNING_REGISTRY_URL_NODE_ID) == LEARNING_REGISTRY_URL_ALIAS) {
    return url('node/' . $node->nid, array('absolute' => TRUE, 'alias' => FALSE));
  }
  else {
    return url('node/' . $node->nid, array('absolute' => TRUE, 'alias' => TRUE));
  }
}

/**
 * Make the drupal_http_request calls to send to the LR node.
 *
 * All the specified nodeapi operations ($ops) call this to send the data.
 *
 * @param string $nid
 *   A string containing the node ID for submission into the registry.
 * @param string $json
 *   A string containing the json object to be sent to the registry node.
 * @param int $service_num
 *   An int that specifies the service that will be called.
 *   0 - publish (default value)
 *   1 - update (future impl)
 *   2 - delete  (future impl)
 * @param bool $headless
 *   A flag to determine if this is called from cron (non-user session).
 *
 * @return bool
 *   True if operation was successful, false if error.
 */
function _learning_registry_send_to_registry($nid, $json, $service_num = LEARNING_REGISTRY_MODE_PUBLISH, $headless = FALSE) {
  $url = variable_get('learning_registry_node_url', NULL);
  if ($url == NULL) {
    drupal_set_message(t('This node has not been published because the Learning Registry URL has not been set.
      Please visit Site configuration -> Learning Registry settings to set the URL of the Learning Registry.'), 'warning');

    return FALSE;
  }
  else {
    $url .= '/publish';
    $oauth_consumer = learning_registry_oauth_verify();
    $oauth_consumer->fetch($url, $json, OAUTH_HTTP_METHOD_POST, array('Content-Type' => 'application/json'));
    $result = $oauth_consumer->getLastResponse();
    $response_info = $oauth_consumer->getLastResponseInfo();
    $submission_result = _learning_registry_parse_result($result, $response_info['http_code']);
    if (isset($submission_result['success'], $submission_result['doc_id']) && $submission_result['success'] === TRUE) {
      $result = _learning_registry_update_submission_status($nid, $result);
      if (!$headless) {
        $submission_url = variable_get('learning_registry_node_url', NULL) . '/harvest/getrecord?by_doc_ID=TRUE&request_ID=' . $result;
        drupal_set_message(t('Node ID @nid published to the registry. <a href="@url" target="_new">(View node on registry.)</a>', array('@nid' => $nid, '@url' => $submission_url)));
      }

      return TRUE;
    }
    else {
      if (!$headless) {
        drupal_set_message(t('Error publishing node to registry.'), 'warning');
      }

      return FALSE;
    }
  }
}

/**
 * Define the Learning Registry resource data.
 *
 * @param array $content_info
 *   Metadata information from the node.
 *
 * @return array
 *   Formatted array of resource data.
 */
function _learning_registry_def_resource_data($content_info) {
  // Values specified as immutable in the LR spec.
  $identity = new stdClass();
  $resource_data = new stdClass();
  $tos = new stdClass();

  $opt_id_fields = array(
    'curator',
    'owner',
    'signer',
  );

  $opt_res_fields = array(
    'submitter_timestamp',
    'submitter_TTL',
    'keys',
    'resource_TTL',
    'payload_schema_locator',
    'payload_schema_format',
  );

  $opt_sig_fields = array(
    'signature',
    'key_server',
    'key_location',
    'key_owner',
    'signing_method',
  );

  $opt_tos_fields = array(
    'tos_submission_attribution',
  );
  $identity->submitter_type = LEARNING_REGISTRY_SUBMITTER_TYPE;
  $identity->submitter = $content_info['submitter'];

  $tos->submission_TOS = $content_info['tos'];

  // Optional identity values.
  foreach ($opt_id_fields as $field) {
    if (array_key_exists($field, $content_info)) {
      $identity->$field = $content_info[$field];
    }
  }

  // Optional resource_data values.
  foreach ($opt_res_fields as $field) {
    if (array_key_exists($field, $content_info)) {
      $resource_data->$field = $content_info[$field];
    }
  }

  // Create an empty stdClass since the digital_signature is completely
  // optional.
  $digital_signature = new stdClass();
  // Optional digital signature values.
  foreach ($opt_sig_fields as $field) {
    if (array_key_exists($field, $content_info)) {
      $digital_signature->$field = $content_info[$field];
    }
  }

  // Optional TOS values.
  foreach ($opt_tos_fields as $field) {
    if (array_key_exists($field, $content_info)) {
      $tos->$field = $content_info[$field];
    }
  }

  $resource_data->doc_type = LEARNING_REGISTRY_DOC_TYPE;
  $resource_data->doc_version = LEARNING_REGISTRY_DOC_VERSION;
  $resource_data->resource_data_type = $content_info['resource_data_type'];
  $resource_data->active = $content_info['active'];
  $resource_data->identity = $identity;
  $resource_data->TOS = $tos;

  // Only add the signature key if signature data are defined.
  if (!empty($digital_signature)) {
    $resource_data->digital_signature = $digital_signature;
  }

  $resource_data->resource_locator = $content_info['resource_locator'];
  $resource_data->payload_placement = LEARNING_REGISTRY_PAYLOAD_PLACEMENT;
  $resource_data->payload_schema = $content_info['payload_schema'];
  $resource_data->resource_data = $content_info['resource_data'];

  return $resource_data;
}

/**
 * Return a basic LR submission envelope.
 *
 * @return object
 *   An empty LR submission envelop.
 */
function _learning_registry_build_envelope() {
  $submission = new stdClass();
  $submission->documents = array();
  return $submission;
}

/**
 * Adds resource data to a LR submission envelope.
 *
 * @param object $submission
 *   An LR submission object.
 * @param object $resource_data
 *   An LR resource data object.
 *
 * @return object
 *   The submission object with $resource data pushed to the documents array.
 */
function _learning_registry_add_resource_data_to_submission($submission, $resource_data) {
  $submission->documents[] = $resource_data;
  return $submission;
}

/**
 * Adds a status record in the learning_registry table to record submission.
 *
 * @param int $nid
 *   Drupal node ID of item to submit.
 * @param string $result
 *   JSON response from Learning Registry.
 */
function _learning_registry_update_submission_status($nid, $result) {
  if ($result) {

    $result_array = drupal_json_decode($result);

    if ($result_array['document_results'][0]['OK']) {
      // Check to see if submission already in database.
      $submission_check_result = db_query('SELECT * FROM {learning_registry} WHERE nid = :nid', array(':nid' => $nid));
      $submission_record = $submission_check_result->fetch();

      // Check if this has been published before.
      // If no, set the published timestamp.
      // Else, the updated timestamp.
      if ($submission_record) {
        if ($submission_record->published == 0) {
          db_update('learning_registry')
          ->fields(array(
                  'published' => REQUEST_TIME,
                  'docid' => $result_array['document_results'][0]['doc_ID'],
                  'queued' => 0,
                ))
          ->condition('nid', $nid)
          ->execute();
        }
        else {
          db_update('learning_registry')
          ->fields(array(
                  'updated' => REQUEST_TIME,
                  'docid' => $result_array['document_results'][0]['doc_ID'],
                  'queued' => 0,
                ))
          ->condition('nid', $nid)
          ->execute();
        }
      }
      else {
        // Insert new record.
        //
        // Fill parameter array.
        $data = array(
          'nid' => $nid,
          'published' => REQUEST_TIME,
          'docid' => $result_array['document_results'][0]['doc_ID'],
        );
        // Write it to the database.
        drupal_write_record('learning_registry', $data);
      }
      return $result_array['document_results'][0]['doc_ID'];
    }
    else {
      watchdog('learning_registry', 'Error publishing node ID %nid to the registry.  Full response: %msg', array('%nid' => $nid, '%msg' => $result), WATCHDOG_ERROR);
      return FALSE;
    }
  }
}

/**
 * Parse out result from Learning Registry submission.
 *
 * @param object $result
 *   JSON array result from Learning Registry submission
 * @param string $code
 *   Error string from curl (if error occured)
 *
 * @return object
 *   Array with status information from submission
 */
function _learning_registry_parse_result($result, $code) {
  $submission_result = array();

  if ($code == 200) {
    // We have something back from the Learning Registry service.
    $result_array = drupal_json_decode($result);

    if ($result_array['OK']) {
      // Submission okay.
      $submission_result['success'] = TRUE;
      $submission_result['doc_id'] = $result_array['document_results'][0]['doc_ID'];
    }
    else {
      $submission_result['success'] = FALSE;
      if (!is_null($result_array['document_results'][0]['error'])) {
        $submission_result['error_message'] = $result_array['document_results'][0]['error'];
      }
      else {
        // If the error message comes back in form of a HTML page, let's just
        // pop off the title tag as Couch will tell us what's wrong there.
        // Current impl of LR spits two title tags, so we're grabbing the
        // last one as it displays better error message.  If not two
        // present, we'd just grab the first.
        if (strpos($result, '<html') > 0) {
          $start = strripos($result, '<title>');
          $end = strripos($result, '</title');
          // Error msg is between the title tags (+7 skips first title tag).
          $submission_result['error_message'] = drupal_substr($result, $start + 7, $end - $start - 7);
        }
      }
    }
  }
  else {
    // We didn't contact the Learning Registry, must be a network error.
    $submission_result['SUCCESS'] = FALSE;
    $submission_result['error_message'] = $result;
  }

  return $submission_result;
}

/**
 * Queues a node for submission to the LR via the learning_registry table.
 *
 * @param int $nid
 *   Drupal node ID of item to submit.
 */
function _learning_registry_queue_node($nid) {

  // Check if this record exists in submission table.
  $submission_check_result = db_query('SELECT * FROM {learning_registry} WHERE nid = :nid', array(':nid' => $nid));
  $submission_record = $submission_check_result->fetch();

  // If exists, update, else insert new record.
  if ($submission_record) {
    db_update('learning_registry')
    ->fields(array(
            'queued' => 1,
          ))
    ->condition('nid', $nid)
    ->execute();
  }
  else {
    $id = db_insert('learning_registry')
    ->fields(array(
      'nid' => $nid,
      'queued' => 1,
    ))
    ->execute();
  }
}

/**
 * Creates Dublin Core 1.1 XML document with information from node.
 *
 * @param object $node
 *   Drupal node
 *
 * @return string
 *   XML document
 */
function _learning_registry_create_dublincore_payload(&$node) {
  $author_user = user_load($node->uid);
  // Set the initial RDF XML DC envelope body.
  $source = '<?xml version="1.0"?>
    <!DOCTYPE rdf:RDF PUBLIC "-//DUBLIN CORE//DCMES DTD 2002/07/31//EN"
      "http://dublincore.org/documents/2002/07/31/dcmes-xml/dcmes-xml-dtd.dtd">
    <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
      xmlns:dc ="http://purl.org/dc/elements/1.1/">
      <rdf:Description rdf:about="http://dublincore.org/">
      </rdf:Description>
    </rdf:RDF>';

  $xml_document = new DOMDocument();
  $xml_document->loadXML($source);

  // Retrieve just the DC node.
  $node_list = $xml_document->getElementsByTagNameNS('http://www.w3.org/1999/02/22-rdf-syntax-ns#', 'Description');
  $dc_node = $node_list->item(0);

  // Set the DC title to the node title.
  $element = $xml_document->createElementNS('http://purl.org/dc/elements/1.1/', 'title', $node->title);
  $dc_node->appendChild($element);

  // Set the DC description to the node body.
  $element = $xml_document->createElementNS('http://purl.org/dc/elements/1.1/', 'description', $node->body['und'][0]['value']);
  $dc_node->appendChild($element);

  // Set the DC date to the node create date.
  $date_created = format_date($node->created, 'custom', 'Y-m-d');
  $element = $xml_document->createElementNS('http://purl.org/dc/elements/1.1/', 'date', $date_created);
  $dc_node->appendChild($element);

  // Set the DC identifier to the absolute URL of the node.
  $element = $xml_document->createElementNS('http://purl.org/dc/elements/1.1/', 'identifier', _learning_registry_get_node_url($node));
  $dc_node->appendChild($element);

  // Set the DC creator to the Drupal username.
  $element = $xml_document->createElementNS('http://purl.org/dc/elements/1.1/', 'creator', $author_user->name);
  $dc_node->appendChild($element);

  // Pretty format the XML before sending it to the LR.
  // Must be reloaded, won't work if just set on $xmlDoc.
  $return_xml = new DOMDocument();
  $return_xml->preserveWhiteSpace = FALSE;
  $return_xml->formatOutput = TRUE;
  $return_xml->loadXML($xml_document->saveXML());

  return $return_xml->saveXML();
}
