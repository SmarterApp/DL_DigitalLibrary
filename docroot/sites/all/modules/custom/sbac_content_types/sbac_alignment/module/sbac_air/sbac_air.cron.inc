<?php
/**
 * @file
 * Contains API for Drupal CCSS cron update.
 */

function sbac_air_sync_ccss($ccss_vid, $ccss_vocab_name, $publisher = 'CC') {
  module_load_include('inc', 'sbac_air', 'lib/sbac_air.airapiclient');
  $api_client = new AIRAPIClient();

  $publication = sbac_air_get_publication($api_client, $publisher, $ccss_vocab_name);
  $api_tags = $api_client->getStandards($publication);
  usort($api_tags, 'sbac_air_sort_tree');

  foreach ($api_tags as $api_standard) {
    if ($api_standard['fkParent']) {
      $target_tid = sbac_air_identify_tid($api_standard);
      if ($target_tid) {
        sbac_air_update_ccss($target_tid, $api_standard);
      }
      else {
        sbac_air_add_ccss($ccss_vid, $api_standard);
      }
    }
  }
}

/**
 * Returns latest publication from AIR API Client.
 * @param  airapi $api_client
 * @param  string $publisher
 * @param  string $type       Only options are 'Mathematics' and 'English / Language Arts'
 * @return string             Latest publication from publisher for education type.
 */
function sbac_air_get_publication(&$api_client, $publisher, $type) {
  $short_type = ($type == 'English / Language Arts' ? 'ELA' : 'MA');
  $publications = $api_client->getPublications($publisher, $short_type);
  $publication = array_pop($publications);
  return $publication['key'];
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

/**
 * Identifies the matching TID based on CCSS keys.
 * @param  array  $api_standard Represents a CCSS Term.
 * @return int                  Target TID if found, otherwise FALSE.
 */
function sbac_air_identify_tid($api_standard) {
  $matching_terms = taxonomy_get_term_by_name($api_standard['name']);
  foreach ($matching_terms as $term) {
    $parent_key = $term->field_alignment_key['und'][0]['value'];
    $parent_values = explode('|', $parent_key);
    if (array_search($api_standard['fkParent'], $parent_values)) {
      return $term->tid;
    }
  }
  return FALSE;
}

/**
 * Updates an existing taxonomy term with new description and shortname.
 * @param  int    $target_tid   Taxonomy TID.
 * @param  array  $api_standard Represents an imported CCSS tag.
 */
function sbac_air_update_ccss($target_tid, $api_standard) {
  $taxonomy_term = taxonomy_term_load($target_tid);

  $taxonomy_term->description = $api_standard['description'];
  $taxonomy_term->field_alignment_shortname['und'][0]['value'] = $api_standard['shortName'];
  $taxonomy_term->field_alignment_shortname['und'][0]['safe_value'] = $api_standard['shortName'];

  taxonomy_term_save($taxonomy_term);
}

/**
 * If a taxonomy term does not exist, it is created here.
 * @param  int    $ccss_vid     Vocab ID for 'education_alignment'.
 * @param  array  $api_standard Represents an imported CCSS tag.
 */
function sbac_air_add_ccss($ccss_vid, $api_standard) {
  // sbac_alignment_add_term($ccss_vid, $api_standard, /*GRADE TERM? */);
}
