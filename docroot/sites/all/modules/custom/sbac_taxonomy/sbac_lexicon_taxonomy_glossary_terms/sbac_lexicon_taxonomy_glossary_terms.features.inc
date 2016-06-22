<?php
/**
 * @file
 * sbac_lexicon_taxonomy_glossary_terms.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_lexicon_taxonomy_glossary_terms_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
