<?php

/**
 * @file
 * Administration callbacks for the learning_registry module
 */

/**
 * LEARNING_REGISTRY_PAYLOAD_SCHEMA_DC11 - Content in Dublin Core 1.1 wrapper.
 *
 * LEARNING_REGISTRY_PAYLOAD_SCHEMA_LOM - Content in LOM wrapper.
 *
 * LEARNING_REGISTRY_PAYLOAD_SCHEMA_UNKNOWN - Content is unknown.
 */

define('LEARNING_REGISTRY_PAYLOAD_SCHEMA_DC11', 0);
define('LEARNING_REGISTRY_PAYLOAD_SCHEMA_LOM', 1);
define('LEARNING_REGISTRY_PAYLOAD_SCHEMA_UNKNOWN', -1);

/**
 * Form constructor to for basic search form for Learning Registry.
 */
function learning_registry_content_form($form, &$form_state) {

  if (variable_get('learning_registry_node_url', NULL) == NULL) {
    drupal_set_message(t('A Learning Registry URL has not yet been configured in the administration settings.
        Please visit Site Configuration -> Learning Registry settings to configure a URL before continuing.'), 'error');
  }
  else {
    $form_state['#redirect'] = FALSE;

    $form['learning_registry'] = array(
      '#type' => 'fieldset',
      '#title' => t('Search'),
    );

    $form['learning_registry']['search_identity'] = array(
      '#type' => 'textfield',
      '#title' => t('Identity'),
      '#size' => 72,
      '#maxlength' => 1024,
      '#description' => t('The name of a person or organization that is the submitter, author, owner, or curator.'),
      '#default_value' => isset($form_state['values']['search_identity']) ? urldecode($form_state['values']['search_identity']) : '',
    );

    $form['learning_registry']['search_tags'] = array(
      '#type' => 'textfield',
      '#title' => t('Tags'),
      '#size' => 72,
      '#maxlength' => 1024,
      '#description' => t('List of tags, matched against keys, payload_schema, or resource_data_type.'),
      '#default_value' => isset($form_state['values']['search_tags']) ? urldecode($form_state['values']['search_tags']) : '',
    );

    $form['learning_registry']['search_from'] = array(
      '#type' => 'textfield',
      '#title' => t('From date'),
      '#size' => 24,
      '#maxlength' => 128,
      '#description' => t('Date of publication to learning registry. Format:  YYYY-MM-DD.'),
      '#default_value' => isset($form_state['values']['search_from']) ? urldecode($form_state['values']['search_from']) : '',
    );

    $form['learning_registry']['search_until'] = array(
      '#type' => 'textfield',
      '#title' => t('Until date'),
      '#size' => 24,
      '#maxlength' => 128,
      '#description' => t('Date of publication to learning registry. Format:  YYYY-MM-DD.'),
      '#default_value' => isset($form_state['values']['search_until']) ? urldecode($form_state['values']['search_until']) : '',
    );

    $form['learning_registry']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Search'),
    );

    if (isset($form_state['storage']['results'])) {
      $form['learning_registry']['results'] = array(
        '#markup' => $form_state['storage']['results'],
      );
    }
  }

  return $form;
}

/**
 * Form validation handler for learning_registry_content_form().
 */
function learning_registry_content_form_validate($form, &$form_state) {
  if ($form_state['values']['search_identity'] == '' && $form_state['values']['search_tags'] == '' &&
          $form_state['values']['search_from'] == '' && $form_state['values']['search_until'] == '') {

    form_set_error('', t('Please enter terms to search the Learning Registry.'));
  }
}

/**
 * Form submission handler for learning_registry_content_form().
 */
function learning_registry_content_form_submit($form, &$form_state) {
  $identity = $form_state['values']['search_identity'];
  $tags = $form_state['values']['search_tags'];
  $from = $form_state['values']['search_from'];
  $until = $form_state['values']['search_until'];
  $output = '';

  $search = '';

  if (drupal_strlen($identity) > 0) {
    $search .= '&identity=' . urlencode($identity);
  }
  if (drupal_strlen($tags) > 0) {
    $search .= '&any_tags=' . urlencode($tags);
  }
  if (drupal_strlen($from) > 0) {
    $search .= '&from=' . urlencode($from);
  }
  if (drupal_strlen($until) > 0) {
    $search .= '&until=' . urlencode($until);
  }

  if ($search != '') {
    $search = variable_get('learning_registry_node_url', NULL) . '/slice?' . $search;
    $result = drupal_http_request($search);
    $result_array = drupal_json_decode($result->data);

    $schema = variable_get('learning_registry_schema_type', '');

    if (function_exists($schema['slice_callback'])) {
      $output = call_user_func($schema['slice_callback'], $result_array);
    }

    $form_state['storage']['results'] = $output;

    $form_state["rebuild"] = TRUE;
    return;
  }
}

/**
 * Return metadata type from Learning Registry envelope.
 */
function _learning_registry_get_metadata_type($payload_schema_array) {
  $type = LEARNING_REGISTRY_PAYLOAD_SCHEMA_UNKNOWN;

  foreach ($payload_schema_array as $payload_schema) {
    switch ($payload_schema) {
      case "LOM":
        return LEARNING_REGISTRY_PAYLOAD_SCHEMA_LOM;

      break;

      case "DC 1.1":
        return LEARNING_REGISTRY_PAYLOAD_SCHEMA_DC11;

      break;
    }
  }
  return $type;
}

/**
 * Slice callback to display results.
 *
 * @param array $result_array
 *   Raw array of results from slice method.
 *
 * @return string
 *   HTML reprsentation of data.
 */
function _learning_registry_dublincore_slice($result_array) {
  $header = array();
  $header[] = 'Resource';
  $header[] = 'Submitter';
  $header[] = 'Description';
  $header[] = 'Create date';

  $rows = array();
  $docs = $result_array['documents'];

  foreach ($docs as $row) {
    $doc_type = $row['resource_data_description']['doc_type'];

    if ($doc_type == 'resource_data') {
      $payload_schema = $row['resource_data_description']['payload_schema'];
      $url = $row['resource_data_description']['resource_locator'];
      $payload = $row['resource_data_description']['resource_data'];
      $submitter = $row['resource_data_description']['identity']['submitter'];
      $create_date = $row['resource_data_description']['create_timestamp'];
      $create_date = drupal_substr($create_date, 0, 10);

      $title = '[unknown]';
      $desc = '[unknown]';

      if (gettype($payload) == 'string') {
        // Load XML, surpress errors.
        $xml = simplexml_load_string($payload, 'SimpleXMLElement', LIBXML_NOERROR);
        if (gettype($xml) == 'object') {
          switch (_learning_registry_get_metadata_type($payload_schema)) {
            case LEARNING_REGISTRY_PAYLOAD_SCHEMA_DC11:
              if (array_key_exists('dc', $xml->getNameSpaces(TRUE))) {
                $result = $xml->xpath('//dc:title');
                if (count($result) > 0) {
                  $title = $result[0][0];
                }
                $result = $xml->xpath('//dc:description');
                if (count($result) > 0) {
                  $desc = $result[0][0];
                }
              }
              break;

            case LEARNING_REGISTRY_PAYLOAD_SCHEMA_LOM:
              $lom = $xml;
              $title = (string) $lom->description->metadata->lom->general->title->string[0];
              $desc = (string) $lom->description->metadata->lom->general->description->string[0];
              break;

            default:
              break;

          }
          if (drupal_strlen($title) == 0) {
            $title = "[not provided]";
          }
          $title = check_plain($title);
          $link = l($title, $url, array('attributes' => array('target' => '_blank')));
          $submitter = check_plain($submitter);
          $desc = check_plain($desc);
          $create_date = check_plain($create_date);
          $rows[] = array($link, $submitter, $desc, $create_date);
        }
      }
    }
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}
