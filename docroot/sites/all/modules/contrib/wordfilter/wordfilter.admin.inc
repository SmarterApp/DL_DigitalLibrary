<?php
/**
 * @file
 * Administrative functions for word filtering.
 *
 * This provides the UI to list, create, edit and delete words to be filtered.
 */

/**
 * Implements hook_settings().
 *
 * @return
 *   array of form elements
 */
function wordfilter_settings_form() {
  $form = array();

  $form['general_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('General options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['general_options']['wordfilter_node_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable word filtering on node titles'),
    '#description' => t('If checked, node titles will be filtered on node load but the original node title will not be changed.'),
    '#default_value' => variable_get('wordfilter_node_title', TRUE),
    '#return_value' => TRUE,
  );
  $form['general_options']['wordfilter_comment_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable word filtering on comment titles'),
    '#description' => t('If checked, comment titles will be filtered on comment load but the original comment title will not be changed.'),
    '#default_value' => variable_get('wordfilter_comment_title', TRUE),
    '#return_value' => TRUE,
  );
  $form['general_options']['wordfilter_use_utf8_flag'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Perl UTF8 Regular Expression Modifier'),
    '#description' => t('Enabling this option adds the PCRE_UTF8 flag to the PHP Perl-Compatible Regular Expression used for filtering. <strong>WARNING</strong>: The PHP manual says: &ldquo;<em><u>Matching characters by Unicode property is not fast, because PCRE has to search a structure that contains data for over fifteen thousand characters.</u></em>&rdquo; If you suffer poor performance consider disabling this option.'),
    '#default_value' => variable_get('wordfilter_use_utf8_flag', FALSE),
    '#return_value' => TRUE,
  );
  $form['general_options']['wordfilter_default_replacement'] = array(
    '#type' => 'textfield',
    '#title' => t('Default word replacement'),
    '#description' => t('Enter the default replacement text here. If you do not enter replacement text for an individual filtered word, the replacement text entered here will be used as the replacement text.'),
    '#default_value' => variable_get('wordfilter_default_replacement', '[filtered word]'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Delete a word from the word filter list delete
 * confirmation callback
 */
function wordfilter_admin_form_delete_confirm($form, &$form_state, $word_id) {
  $form = array();
  $form['word_id'] = array(
    '#type' => 'value',
    '#value' => $word_id,
  );
  return confirm_form($form, t('Are you sure you want to delete this word or phrase from the word filtering list?'), 'admin/config/content/wordfilter');
}

/**
 * Delete a word from the word filter list
 */
function wordfilter_admin_form_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_delete('wordfilter')
      ->condition('id', $form_state['values']['word_id'])
      ->execute();

    drupal_set_message(t('The word was removed from the word filter list'));
    $form_state['redirect'] = 'admin/config/content/wordfilter';
    cache_clear_all('*', 'cache_filter', TRUE);
  }
}


/**
 * Wordfilter admin settings page callback.
 */
function wordfilter_admin_list() {
  $build = array();
  $header = array(
    array('data' => t('Word to filter'), 'field' => 'words', 'sort' => 'asc'),
    array('data' => t('Replacement text'), 'field' => 'replacement'),
    array('data' => t('Standalone'), 'field' => 'standalone'),
    array('data' => t('Operations'), 'colspan' => 2)
  );
  $rows = array();
  
  $list = db_select('wordfilter', 'w')
    ->fields('w')
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->orderByHeader($header)
    ->limit(10)
    ->execute();
  
  foreach ($list as $word) {
    $rows[] = array(
      check_plain($word->words),
      ($word->replacement) ? check_plain($word->replacement) : check_plain(variable_get('wordfilter_default_replacement', '[filtered word]')),
      ($word->standalone) ? t('Yes') : t('No'),
      l(t('Edit word'), 'admin/config/content/wordfilter/edit/' . $word->id),
      l(t('Delete word'), 'admin/config/content/wordfilter/delete/' . $word->id),
    );
  }
  $build['wordfilter_settings_form'] = drupal_get_form('wordfilter_settings_form');
  $build['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
  );
  $build['pager'] = array(
    '#markup' => theme('pager')
  );

  return $build;
}

/**
 * Edit word filter form.
 */
function wordfilter_admin_edit_form($form, &$form_state, $word_id = NULL) {
  if (!isset($word_id) || !is_numeric($word_id)) {
    drupal_set_message(t('The wordfilter ID of the word or phrase you are trying to edit is missing or is not a number.'), 'error');
    drupal_goto('admin/config/content/wordfilter');
  }
  
  $word = db_select('wordfilter', 'w')
    ->fields('w')
    ->condition('w.id', $word_id)
    ->execute()
    ->fetch();


  $form = array();
  $form['id'] = array(
    '#type' => 'hidden',
    '#value' => $word->id,
  );

  $form['words'] = array(
    '#type' => 'textfield',
    '#title' => t('Word or phrase to filter'),
    '#default_value' => $word->words,
    '#description' => t('Enter the word or phrase you want to filter.'),
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['replacement'] = array(
    '#type' => 'textfield',
    '#title' => t('Replacement text'),
    '#description' => t('Enter the filtered version of the word or phrase to replace the original word or phrase.'),
    '#default_value' => ($word->replacement) ? $word->replacement : variable_get('wordfilter_default_replacement', '[filtered word]'),
    '#size' => 50,
    '#maxlength' => 255,
  );
  $form['standalone'] = array(
    '#type' => 'checkbox',
    '#title' => t('Stand-alone'),
    '#default_value' => $word->standalone,
    '#description' => t('When checked, the word or phrase will only be filtered when found as a separate word or phrase (i.e. prefixed and suffixed by spaces or "whitespace"). A period one character after a word or phrase will exclude the words or phrases from replacement in stand-alone mode. This is useful for preventing accidental word or phrase filtering with short or common words or phrases.'),
  );

  $form['Save word filter'] = array(
    '#type' => 'submit',
    '#value' => t('Save word filter'),
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );

  return $form;
}

/**
 * Edit word filter form submit handler.
 */
function wordfilter_admin_edit_form_submit($form, &$form_state) {
  drupal_write_record('wordfilter', $form_state['values'], 'id');
  watchdog('wordfilter', 'Updated filter for: %word', array('%word' => $form_state['values']['words']));
  drupal_set_message(t('Updated filter for: %word', array('%word' => $form_state['values']['words'])));
  $form_state['redirect'] = 'admin/config/content/wordfilter';
  cache_clear_all('*', 'cache_filter', TRUE);
  cache_clear_all('wordfilter', 'cache');
}

/**
 * Add word filter form.
 */
function wordfilter_admin_add_form() {
  $form = array();

  $form['help'] = array(
    '#type' => 'markup',
    '#value' => t("<p>Enter a word or phrase you want to filter followed by '|' and the replacement word or phrase. You can enter multiple word and replacement word pairs by hitting return and adding more word pairs. Any word or phrases that do not have a replacement word or phrase will use the default replacement word below.</p>"),
  );

  $form['words'] = array(
    '#type' => 'textarea',
    '#title' => t('Words'),
    '#description' => t("Enter a word or phrase you want to filter followed by '|' and the replacement word or phrase if any."),
    '#required' => true
  );
  $form['replacement'] = array(
    '#type' => 'textfield',
    '#title' => t('Replacement'),
    '#default_value' => variable_get('wordfilter_default_replacement', '[filtered word]'),
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('Enter the filtered version of the word to replace the original words with. If no replacement word or phrase is specified for a word or phrase in the list above, the word or phrase entered here will be used as the replacement for that word or phrase.')
  );
  $form['standalone'] = array(
    '#type' => 'checkbox',
    '#title' => t('Stand-alone'),
    '#description' => t('When checked, the word or phrase will only be filtered when found as a separate word or phrase (i.e. prefixed and suffixed by spaces or "whitespace"). A period one character after a word or phrase will exclude the words from replacement in stand-alone mode. This is useful for preventing accidental word or phrase filtering with short or common words and phrases.')
  );
  $form['language'] = array(
    '#type' => 'value',
    '#value' => '',
  );

  $form['Save word filter'] = array(
    '#type' => 'submit',
    '#value' => t('Save word filter')
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel')
  );

  return $form;
}

/**
 * Add word filter form submit handler.
 */
function wordfilter_admin_add_form_submit($form, &$form_state) {
  $pairs = explode("\n", $form_state['values']['words']);
  $pairs = array_map('trim', $pairs);
  $pairs = array_filter($pairs, 'strlen');
  foreach ($pairs as $pair) {
    $row = new stdClass;
    $row->standalone = $form_state['values']['standalone'];
    list($row->words, $row->replacement, $row->language) = array_pad(explode('|', $pair), 3, '');
    if (!$row->replacement) {
      $row->replacement = $form_state['values']['replacement'];
    }
    if (!$row->language) {
      $row->language = $form_state['values']['language'];
    }
    drupal_write_record('wordfilter', $row);
    watchdog('wordfilter', 'Added filter for: %word', array('%word' => $row->words));
    drupal_set_message(t('Added filter for: %word', array('%word' => $row->words)));
  }
  $form_state['redirect'] = 'admin/config/content/wordfilter';
  cache_clear_all('*', 'cache_filter', TRUE);
  cache_clear_all('wordfilter', 'cache');
}

/**
 * Test word filter form.
 */
function wordfilter_admin_test_filter_form($form, &$form_state) {
  $form = array();
  $form['#redirect'] = FALSE;

  $form['test_word'] = array(
    '#type' => 'textfield',
    '#title' => t('Word to test'),
    '#description' => t('Enter a word or phrase that you want to test your wordfilters on'),
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  if (isset($form_state['values']['test_word'])) {
    $form['text_result'] = array(
      '#type' => 'item',
      '#markup' => _wordfilter_test_filter($form_state['values']['test_word']),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Test word filters'),
  );

  return $form;
}

/**
 * Test word filter form submit handler.
 */
function wordfilter_admin_test_filter_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Test word filter page callback.
 */
function _wordfilter_test_filter($word) {
  $filtered_word = wordfilter_filter_process($word);
  if ($word == $filtered_word) {
    return t("Your test phrase '%word' did not match any filters", array('%word' => $word));
  }
  else {
    $no_html = t("<p>Your test phrase: <br />
&nbsp;&nbsp;'@word' <br />
was filtered to: <br />
&nbsp;&nbsp;'@filtered_word'</p>", array('@word' => $word, '@filtered_word' => $filtered_word));
    $html = t("<p>(As HTML): <br />
&nbsp;&nbsp;'!word' <br />
was filtered to: <br />
&nbsp;&nbsp;'!filtered_word'</p>", array('!word' => filter_xss_admin($word), '!filtered_word' => filter_xss_admin($filtered_word)));
    return $no_html . $html;
  }
}