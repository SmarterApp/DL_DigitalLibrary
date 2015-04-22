<?php

/**
 * Set server 
 */
ini_set('max_execution_time', 999);
ini_set('memory_limit', '1024M');

/**
 * Global Variables
 */
define('SBAC_ALIGNMENT_DATA_PATH', 'http://' . $_SERVER['HTTP_HOST'] . '/' .  drupal_get_path('module', 'sbac_alignment') . '/data/');

/**
 * Batch Callback
 * Imports the ccss tags using BATCH API.
 */
function sbac_alignment_batch_importer_page() {
  if (!(isset($_GET['op']) && $_GET['op'] == 'import')) {
    return 'You must provide a op parameter.';
  }
  
  if(isset($_GET['reset'])) {
    variable_set('sbac_alignment_import_counter', 0);
    variable_set('sbac_alignment_import_data', array());
    variable_set('sbac_alignment_import_bad_terms', '');
  }

  $edu_alignment_vocab_name = "education_alignment";
  $edu_alignment_vocab = taxonomy_vocabulary_machine_name_load($edu_alignment_vocab_name);
  $grade_terms = array();
  $create_base = FALSE;
  if ($_GET['create_base']) {
    $create_base = TRUE;
  }

  // create base terms
  if ($create_base) {
    // Add education alignment
    $terms = array(
      'English / Language Arts' => array(
        'children' => array(
          'KG : Kindergarten' => array('weight' => 0),
          '1 : Grade 1' => array('weight' => 1),
          '2 : Grade 2' => array('weight' => 2),
          '3 : Grade 3' => array('weight' => 3),
          '4 : Grade 4' => array('weight' => 4),
          '5 : Grade 5' => array('weight' => 5),
          '6 : Grade 6' => array('weight' => 6),
          '7 : Grade 7' => array('weight' => 7),
          '8 : Grade 8' => array('weight' => 8),
          '9-10 : Grade 9 - 10' => array('weight' => 9),
          '11-12 : Grade 11 - 12' => array('weight' => 10),
        ),
      ),
      'Mathematics' => array(
        'children' => array(
          'KG : Kindergarten' => array('weight' => 0),
          '1 : Grade 1' => array('weight' => 1),
          '2 : Grade 2' => array('weight' => 2),
          '3 : Grade 3' => array('weight' => 3),
          '4 : Grade 4' => array('weight' => 4),
          '5 : Grade 5' => array('weight' => 5),
          '6 : Grade 6' => array('weight' => 6),
          '7 : Grade 7' => array('weight' => 7),
          '8 : Grade 8' => array('weight' => 8),
          'HS : High School' => array('weight' => 9),
        ),
      ),
    );
    sbac_alignment_add_terms($edu_alignment_vocab->vid, $terms);
  }

  // Only available types are "Mathematics" and "English / Language Arts"
  if(isset($_GET['type'])) {
    $type = $_GET['type'];
    $subject = array_pop(taxonomy_get_term_by_name($type));
  }
  else {
    return 'You must enter a type. Only available types are "Mathematics" and "English / Language Arts';
  }

  $create = TRUE;

  //create terms
  if ($create && $subject) {
    // get grades tids
    $terms = taxonomy_get_tree($edu_alignment_vocab->vid, $subject->tid, 1, TRUE);
    foreach ($terms as $term) {
      if($term->depth == 0) {
        $name = explode(':', $term->name);
        $grade_terms[trim($name[0])] = $term;
      }
    }
    
    //get data
    module_load_include('inc', 'sbac_air', 'lib/sbac_air.airapiclient');
    $airclient = new AIRAPIClient();
    if ($subject->name == 'English / Language Arts') {
      $api_type = 'CC-ELA-v1';
    }
    else {
      $api_type = 'CC-MA-v1';
    }
    $json = $airclient->getStandards($api_type);
    uasort($json, 'sbac_alignment_sort_tree');
  
    $batch = array(
      'title' => t('Exporting'),
      'operations' => array(
        array('sbac_alignment_batch', array($edu_alignment_vocab->vid, $json, $grade_terms, $api_type)),
      ),
      'finished' => 'sbac_alignment_batch_test_finished',
      'file' => drupal_get_path('module', 'sbac_alignment') . '/sbac_alignment.dev.inc',
    );
    batch_set($batch);
    // Only needed if not inside a form _submit handler.
    // Setting redirect in batch_process.
    batch_process('ccss-import');
  }
}
/**
 * Batch Callback
 * BATCH API. Imports the ccss tags.
 */
function sbac_alignment_batch($vid, $json, $grade_terms, $api_type, &$context) {
  ini_set('max_execution_time', 9999);
  ini_set('memory_limit', '1024M');
  
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($json);
    $context['sandbox']['counter'] = 0;
    $context['sandbox']['parents'] = array();
    $context['sandbox']['noparents'] = array();
  }
  
  $counter = variable_get('sbac_alignment_import_counter', 0);
  $parents = variable_get('sbac_alignment_import_data', array());
  $bad_terms = variable_get('sbac_alignment_import_bad_terms', array());

  $json_count = count($json);
  $msg = "
    count " . $counter . "
    parents " . drupal_json_encode($parents) . "
";
  watchdog('sbac_alignment', $msg);
  
  for ($i = $counter; $i < $json_count; $i++) {
    $term = $json[$i];
    $grade = trim($term['fkGradeLevel']);
    $key = $grade . '|' . $term['key'];
    
    if($i % 100 == 0) {
      variable_set('sbac_alignment_import_counter', $i);
      variable_set('sbac_alignment_import_data', $parents);
    }

    // For Batch API. Since it does it in batches, we may have already added this term.
    if (isset($parents[$key])) {
      continue;
    }

    // Root term. first set after the grade
    if ($term['treeLevel'] < 2) {
      if ($term['fkParent'] == NULL) {
        $weight = sbac_alignment_set_weight($term, $api_type);
        $term['weight'] = $weight;
      }
      $parent_tid = $grade_terms[$grade]->tid;
      $new_term = sbac_alignment_add_term($vid, $term, $parent_tid);
      $parents[$key] = $new_term->tid;
    }
    else { // treeLevel >= 2
      $parent_key = $grade . '|' . $term['fkParent'];
      if(isset($parents[$parent_key])) {
        $parent_tid = $parents[$parent_key];
        
        $new_term = sbac_alignment_add_term($vid, $term, $parent_tid);
        $parents[$key] = $new_term->tid;
      }
      else {
        $bad_terms[] = $term['key'];
      }
    }
    
    $context['sandbox']['progress']++;
    $context['message'] = $term['key'];
    $context['results'][] = $term['key'];
    
    if($i % 100 == 0) {
      variable_set('sbac_alignment_import_counter', $i);
      variable_set('sbac_alignment_import_data', $parents);
      variable_set('sbac_alignment_import_bad_terms', $bad_terms);
    }
  }
  
  //finish
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}
/**
 * BATCH FINISHED CALLBACK
 * BATCH API. Called when batch finishes.
 */
function sbac_alignment_batch_test_finished($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = format_plural(count($results), 'One post processed.', '@count posts processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
  // Providing data for the redirected page is done through $_SESSION.
  foreach ($results as $result) {
    $items[] = t('Loaded node %title.', array('%title' => $result));
  }
  $_SESSION['my_batch_results'] = $items;
}
/**
 * Function Callback.
 * Used to import sample data set for testing.
 */
function sbac_alignment_test_import() {
  if (!(isset($_GET['op']) && $_GET['op'] == 'test')) {
    return '';
  }
  
  $edu_alignment_vocab_name = "education_alignment";
  $filename = 'ela.sample.json';

  $edu_alignment_vocab = taxonomy_vocabulary_machine_name_load($edu_alignment_vocab_name);
  $parents = $grade_terms = array();
  $parent_tid = 0;
  
  //DELETE old terms
  $terms = taxonomy_get_tree($edu_alignment_vocab->vid);
  foreach ($terms as $term) {
    taxonomy_term_delete($term->tid);
  }

  // Add education alignment
  $terms = array(
    'English / Language Arts' => array(
      'children' => array(
        'KG - Kindergarten' =>  array(),
        '1 - First Grade' =>  array(),
        '2 - Second Grade' =>  array(),
        '3 - Third Grade' =>  array(),
        '4 - Fourth Grade' =>  array(),
        '5 - Fifth Grade' =>  array(),
        '6 - Sixth Grade' =>  array(),
        '7 - Seventh Grade' =>  array(),
        '8 - Eight Grade' =>  array(),
        '9 - Ninth Grade' =>  array(),
        '10 - Tenth Grade' =>  array(),
        '11 - Eleventh Grade' =>  array(),
        '12 - Twelveth Grade' =>  array(),
      ),
    ),
  );
  
  sbac_alignment_add_terms($edu_alignment_vocab->vid, $terms);

  $subject = array_pop(taxonomy_get_term_by_name('English / Language Arts'));
  
  /** create terms*/
  // get grades tids
  $terms = taxonomy_get_tree($edu_alignment_vocab->vid, $subject->tid, 1, TRUE);
  foreach ($terms as $term) {
    if($term->depth == 0) {
      $name = explode('-', $term->name);
      $grade_terms[trim($name[0])] = $term;
    }
  }
  //get data
  $data = drupal_http_request(SBAC_ALIGNMENT_DATA_PATH . $filename);
  $contents = $data->data;
  $json = drupal_json_decode($contents);

  uasort($json, 'sbac_alignment_sort_tree');
  
  foreach ($json as $term) {
    $grade = trim($term['fkGradeLevel']);

    // Root term. first set after the grade
    if ($term['treeLevel'] < 2) {
      $parent_tid = $grade_terms[$grade]->tid;
      $key = $grade . '|' . $term['key'];
      $parents[$key] = sbac_alignment_add_term($edu_alignment_vocab->vid, $term, $parent_tid);
    }
    elseif(($tree_level = $term['treeLevel']) >=2) {
      $parent_key = $grade . '|' . $term['fkParent'];
      //$parent_tid = sbac_alignment_get_parent($parent_key);
      $parent_tid = $parents[$parent_key]->tid;
      //dsm(array($parent_key, $parent_tid));
      if (empty($parent_tid)) {
        //cannot find parent save to grade
        $parent_tid = $grade_terms[$grade]->tid;
        $broken_terms[] = $term;
      }
      else {
      $key = $grade . '|' . $term['key'];
      $parents[$key] = sbac_alignment_add_term($edu_alignment_vocab->vid, $term, $parent_tid);
      }
    }
    else{
      //@TODO KS - need to output in case of error
    }
  }
}
/**
 * Helper Function
 * Sorts the tree.
 */
function sbac_alignment_sort_tree($a, $b) {
  if ($a['treeLevel'] == $b['treeLevel']) {
    return 0;
  }
  return ($a['treeLevel'] < $b['treeLevel']) ? -1 : 1;
}
/**
 * Helper Function
 * Gets the file name via http.
 */
function sbac_alignment_get_file($filename) {
   //@TODO KS - add error handler
   $data = drupal_http_request(SBAC_ALIGNMENT_DATA_PATH . $filename);
   return $data->data;
}
/**
 * Page Callback
 * Imports ccss tagger based on GET params
 */
function sbac_alignment_import_ccss() {
  ini_set('max_execution_time', '9999');
  ini_set('memory_limit', '2048M');
  
  if(isset($_GET['vocab'])) {
    $edu_alignment_vocab_name = $_GET['vocab'];
  }
  else {
    $edu_alignment_vocab_name = "education_alignment2";
  }

  if(isset($_GET['file'])) {
    $filename = $_GET['file'];
  }
  else {
    $filename = "ela.json";
  }

  $edu_alignment_vocab = taxonomy_vocabulary_machine_name_load($edu_alignment_vocab_name);
  $grade_terms = array();

  $create_base = TRUE;
  $create = TRUE;

  // create base terms
  if ($create_base) {
    // Add education alignment
    $terms = array(
      'English / Language Arts' => array(
        'children' => array(
          'KG - Kindergarten' =>  array(),
          '1 - First Grade' =>  array(),
          '2 - Second Grade' =>  array(),
          '3 - Third Grade' =>  array(),
          '4 - Fourth Grade' =>  array(),
          '5 - Fifth Grade' =>  array(),
          '6 - Sixth Grade' =>  array(),
          '7 - Seventh Grade' =>  array(),
          '8 - Eightf Grade' =>  array(),
          '9 - Ninth Grade' =>  array(),
          '10 - Tenth Grade' =>  array(),
          '11 - Eleventh Grade' =>  array(),
          '12 - Twelfth Grade' =>  array(),
        ),
      ),
      'Math' => array(
        'children' => array(
          'KG - Kindergarten' =>  array(),
        '1 - First Grade' =>  array(),
        '2 - Second Grade' =>  array(),
        '3 - Third Grade' =>  array(),
        '4 - Fourth Grade' =>  array(),
        '5 - Fifth Grade' =>  array(),
        '6 - Sixth Grade' =>  array(),
        '7 - Seventh Grade' =>  array(),
        '8 - Eighth Grade' =>  array(),
        '9 - Ninth Grade' =>  array(),
        '10 - Tenth Grade' =>  array(),
        '11 - Eleventh Grade' =>  array(),
        '12 - Twelfth Grade' =>  array(),
        ),
      ),
    );
    
    sbac_alignment_add_terms($edu_alignment_vocab->vid, $terms);
  }

  if(isset($_GET['type'])) {
    $subject = array_pop(taxonomy_get_term_by_name($_GET['type']));
  }
  else {
    $subject = array_pop(taxonomy_get_term_by_name('English / Language Arts'));
  }
  
  //create terms
  if ($create) {
    // get grades tids
    $terms = taxonomy_get_tree($edu_alignment_vocab->vid, $subject->tid, 1, TRUE);
    //dsm($terms);
    foreach ($terms as $term) {
      if($term->depth == 0) {
        $name = explode('-', $term->name);
        //dsm(array($term->name, truncate($name[0])));
        $grade_terms[trim($name[0])] = $term;

      }
    }
    //get data
    $data = drupal_http_request(SBAC_ALIGNMENT_DATA_PATH . $filename);
    $contents = $data->data;

    $json = drupal_json_decode($contents);
  
    // build tree
    $parent_tid = 0;
    $clean_parent = TRUE;
    $parents = array();
    
    $broken_terms = array();
    
    foreach ($json as $term) {
      //dsm($term);
      $grade = trim($term['fkGradeLevel']);

      // Root term. first set after the grade
      if ($term['treeLevel'] < 2) {
        $parent_tid = $grade_terms[$grade]->tid;
        $key = $grade . '|' . $term['key'];
        $parents[$key] = sbac_alignment_add_term($edu_alignment_vocab->vid, $term, $parent_tid);
      }
      elseif(($tree_level = $term['treeLevel']) >=2) {
        $parent_key = $grade . '|' . $term['fkParent'];
        $parent_tid = $parents[$parent_key]->tid;
        if (empty($parent_tid)) {
          //cannot find parent save to grade
          $parent_tid = $grade_terms[$grade]->tid;
          $broken_terms[] = $term;
        }
        else {
        $key = $grade . '|' . $term['key'];
        $parents[$key] = sbac_alignment_add_term($edu_alignment_vocab->vid, $term, $parent_tid);
        }
      }
      else{
        //dsm('BAD TERM');dsm($term);
      }
    }
    
    print drupal_json_encode($parents);
    exit;
  }

  return '';
}
/**
 * Helper Function
 * Get parent based on a key.
 */
function sbac_alignment_get_parent($key) {
  $result = db_query('SELECT frfak.entity_id
    FROM {field_revision_field_alignment_key} frfak WHERE frfak.field_alignment_key_value = :field_alignment_key_value',
    array(':field_alignment_key_value' => $key));

  return $result->fetchObject()->entity_id;
}
/**
 * Callback function
 * Deletes vocabulary.
 */
function sbac_alignment_delete_vocab() {
  if (isset($_GET['op'])) {
    if(isset($_GET['vocab'])) {
      $edu_alignment_vocab_name = $_GET['vocab'];
    }
    else {
      $edu_alignment_vocab_name = "education_alignment2";
    }
    $edu_alignment_vocab = taxonomy_vocabulary_machine_name_load($edu_alignment_vocab_name);
    $grade_terms = array();
  
    $delete = TRUE;
    $print = FALSE;
  
    //delete terms
    if ($delete) {
      $terms = taxonomy_get_tree($edu_alignment_vocab->vid);
      foreach ($terms as $term) {
        //if($term->depth > 1){
          taxonomy_term_delete($term->tid);
        //}
      }
    }
  
    if($print) {
      $terms = taxonomy_get_tree($edu_alignment_vocab->vid, 0, NULL, TRUE);
      dsm($terms);
    }
  }

  return '';
}

/**
 * Sets the weight determined by awesome logic.
 *
 * @param $term
 * @param $api_type
 * @return int
 */
function sbac_alignment_set_weight($term, $api_type) {
  $weight = 0;
  if ($api_type == 'CC-ELA-v1') {
    switch($term['name']) {
      case 'RL':
        $weight = 0;
        break;
      case 'RI':
        $weight = 1;
        break;
      case 'RF':
        $weight = 2;
        break;
      case 'W':
        $weight = 3;
        break;
      case 'SL':
        $weight = 4;
        break;
      case 'L':
        $weight = 5;
        break;
      case 'RH':
        $weight = 6;
        break;
      case 'RST':
        $weight = 7;
        break;
      case 'WHST':
        $weight = 8;
        break;
    }
  }
  else {
    switch($term['name']) {
      case 'CC':
        $weight = 0;
        break;
      case 'OA':
        $weight = 1;
        break;
      case 'NBT':
        $weight = 2;
        break;
      case 'MD':
        $weight = 3;
        break;
      case 'G':
        $weight = 4;
        break;
      case 'NF':
        $weight = 5;
        break;
      case 'RP':
        $weight = 6;
        break;
      case 'NS':
        $weight = 7;
        break;
      case 'EE':
        $weight = 8;
        break;
      case 'SP':
        $weight = 9;
        break;
      case 'F':
        $weight = 10;
        break;
      case 'HSN-RN':
        $weight = 11;
        break;
      case 'HSN-Q':
        $weight = 12;
        break;
      case 'HSN-CN':
        $weight = 13;
        break;
      case 'HSN-VM':
        $weight = 14;
        break;
      case 'HSA-SSE':
        $weight = 15;
        break;
      case 'HSA-APR':
        $weight = 16;
        break;
      case 'HSA_CED':
        $weight = 17;
        break;
      case 'HSA-REI':
        $weight = 18;
        break;
      case 'HSF-IF':
        $weight = 19;
        break;
      case 'HSF-BF':
        $weight = 20;
        break;
      case 'HSF-LE':
        $weight = 21;
        break;
      case 'HSF-TF':
        $weight = 22;
        break;
      case 'HSG-CO':
        $weight = 23;
        break;
      case 'HSG-SRT':
        $weight = 24;
        break;
      case 'HSG-C':
        $weight = 25;
        break;
      case 'HSG-GPE':
        $weight = 26;
        break;
      case 'HSG-GMD':
        $weight = 27;
        break;
      case 'HSG-MG':
        $weight = 28;
        break;
      case 'HSS-ID':
        $weight = 29;
        break;
      case 'HSS-IC':
        $weight = 30;
        break;
      case 'HSS-CP':
        $weight = 31;
        break;
      case 'HSS-MD':
        $weight = 32;
        break;
    }
  }

  return $weight;
}
