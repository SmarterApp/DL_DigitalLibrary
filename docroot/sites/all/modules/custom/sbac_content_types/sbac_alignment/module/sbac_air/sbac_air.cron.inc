<?php

/**
 * Updates tags for course type.
 * @param  int    $ccss_vid        Vocab ID for 'education_alignment'.
 * @param  string $ccss_vocab_name Only options are 'Mathematics' and 'English / Language Arts'
 */
function sbac_air_sync_ccss($ccss_vid, $ccss_vocab_name) {
  //  Drupal

  $d_subject = taxonomy_get_term_by_name($ccss_vocab_name);
  $d_subject = array_pop($d_subject);
  $grade_terms = array();

  //  AIR Client
  module_load_include('inc', 'sbac_air', 'lib/sbac_air.airapiclient');
  $a_client = new AIRAPIClient();

  //  String 'CC-ELA-v1' or 'CC-MA-v1'
  $api_type = sbac_air_set_api($ccss_vocab_name);

  //  AIR term tree
  $a_json = $a_client->getStandards($api_type);
  uasort($a_json, 'sbac_air_sort_tree');

  $terms = taxonomy_get_tree($ccss_vid, $d_subject->tid, 1, TRUE);

  // foreach ($terms as $term) {
  //   if ($term->depth == 0) {
  //     $name = explode(':', $term->name);

  //     $grade_terms[trim($name[0])] = $term;
  //   }
  // }



  dpm($terms, $ccss_vocab_name);

  //  sbac_air_load_local_ccss();

  //  Update existing
  //  sbac_air_update_ccss($ccss_vid, $d_subject->tid, 0, TRUE);

  //  Add new
  //  sbac_air_add_ccss($ccss_vid, $d_subject->tid, 0, TRUE);

}

/**
 * Sets API type from a given type.
 * @param  string $type Only options are 'Mathematics' and 'English / Language Arts'
 * @return string
 */
function sbac_air_set_api($type) {
  if ($type == 'English / Language Arts') {
    return 'CC-ELA-v1';
  }
  else {
    return 'CC-MA-v1';
  }
}

function sbac_air_load_local_ccss($ccss_vid, $ccss_vocab_name, $a_json) {
  return;
}

function sbac_air_update_ccss($vid, $tid, $depth = 0, $get_entities = FALSE) {
  return;
}

function sbac_air_add_ccss($vid, $tid, $depth = 0, $get_entities = FALSE) {
  return;
}

/**
 * Sorts the tree.
 */
function sbac_air_sort_tree($a, $b) {
  if ($a['treeLevel'] == $b['treeLevel']) {
    return 0;
  }
  return ($a['treeLevel'] < $b['treeLevel']) ? -1 : 1;
}
