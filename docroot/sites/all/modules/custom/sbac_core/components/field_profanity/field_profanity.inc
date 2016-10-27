<?php

/**
 * Runs the text against Phoenetic's white- & black-lists and returns an array
 * of the blacklisted words. Mostly a clone of _phonetic_apply_filter();
 */
function profanity_validate_text($text) {
  // blacklist
  $blacklist = variable_get('phonetic_blacklist', '');
  if (!is_array($blacklist)) {
    $blacklist = explode("\n", $blacklist);
  }

  // whitelist
  $whitelist = variable_get('phonetic_whitelist', '');
  if (!is_array($whitelist)) {
    $whitelist = explode("\n", $whitelist);
  }

  $char = variable_get('phonetic_replacement_char', '*');;
  $words = str_word_count(strip_tags($text), 2);
  $bad_words = array();

  foreach ($words as $word) {
    $metaphone = metaphone($word);
    foreach ($blacklist as $original => $phonetic) {
      // phonetic filtering
      if ($phonetic == $metaphone) {
        // make sure word isn't in the whitelist
        if (!in_array($word, $whitelist)) {
          // do a similarity comparison
          $compare = similar_text(strtolower($word), $original);
          if (strlen($original) == $compare) {
            $bad_words[] = $word;

            // we found the word in the blacklist, so we break to go on to the next words
            break;
          }
        }
      }
    }
  }

  return $bad_words;
}

/**
 * Returns the error message shown when profanity is detected.
 * @return [type] [description]
 */
function profanity_error_message_text() {
  return t('Please remove inappropriate language.');
}

