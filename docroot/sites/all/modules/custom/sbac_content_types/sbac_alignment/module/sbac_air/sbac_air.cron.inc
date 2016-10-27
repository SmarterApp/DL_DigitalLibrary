<?php
/**
 * @file
 * Contains API for Drupal CCSS cron update.
 */

/**
 * Updates or adds the CCSS Standard to Drupal's Taxonomy tree.
 * @param  int    $ccss_vid     Vocab ID for 'educational_alignment'
 * @param  string $publisher    Publisher shortname.
 * @param  array  $api_standard Represents CCSS API standard.
 */
function sbac_air_sync_standard($ccss_vid, $publisher = 'CC', $api_standard) {
  if ($ccss_tid = sbac_air_identify_tid($api_standard)) {
    try {
      sbac_air_update_ccss($ccss_tid, $api_standard);
    }
    catch (\Exception $e) {
      watchdog('sbac_air', 'Failed to update CCSS', array(), WATCHDOG_NOTICE, 'link');
      drupal_set_message($e->getMessage(), 'error');
    }
  }
  else {
    try {
      sbac_air_add_ccss($ccss_vid, $api_standard);
    }
    catch (\Exception $e) {
      watchdog('sbac_air', 'Failed to create CCSS', array(), WATCHDOG_NOTICE, 'link');
      drupal_set_message($e->getMessage(), 'error');
    }
  }
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
  if ($taxonomy_term = taxonomy_term_load($target_tid)) {
    $taxonomy_term->description = $api_standard['description'];
    $taxonomy_term->field_alignment_shortname['und'][0]['value']      = $api_standard['shortName'];
    $taxonomy_term->field_alignment_shortname['und'][0]['safe_value'] = $api_standard['shortName'];

    return taxonomy_term_save($taxonomy_term);
  }
  throw new Exception('TID: ' . $target_tid . ' does not exist');
}

/**
 * If a taxonomy term does not exist, it is created here.
 * @param  int    $ccss_vid     Vocab ID for 'education_alignment'.
 * @param  array  $api_standard Represents an imported CCSS tag.
 */
function sbac_air_add_ccss($ccss_vid, $api_standard) {
  if ($parent_tid = sbac_air_find_parent_tid($api_standard) != -1) {
    return sbac_alignment_add_term($ccss_vid, $api_standard, $parent_tid);
  }
  throw new Exception('Parent tid not found');
}

/**
 * Determines the Drupal Parent ID for a new Taxonomy Term
 * @param  array  $api_standard Represents an imported CCSS tag.
 * @return int                  Taxonomy ID for parent term .
 */
function sbac_air_find_parent_tid($api_standard) {
  $parent_name = explode(':', $api_standard['fkParent']);
  $term_name   = array_pop($parent_name);
  $term_list   = taxonomy_get_term_by_name($term_name);

  foreach ($term_list as $tid => $contents) {
    if ($contents->field_alignment_key['und'][0]['value'] == $api_standard['fkParent']) {
      return $tid;
    }
  }
  return -1;
}
