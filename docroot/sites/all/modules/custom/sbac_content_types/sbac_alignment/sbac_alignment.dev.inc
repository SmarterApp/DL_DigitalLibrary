<?php
/**
 * Set server 
 */
ini_set('max_execution_time', '999');
ini_set('memory_limit', '1024M');
/**
 * Global Variables
 */
define('SBAC_ALIGNMENT_DATA_PATH', 'http://' . $_SERVER['HTTP_HOST'] . '/' .  drupal_get_path('module', 'sbac_alignment') . '/data/');

function sbac_alignment_devfix() {
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

  uasort($json, 'cmp');
  
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
 *
 */
function sbac_alignment_devfix3(){
  $shortnames = get_shortnames();
  
  $filename = 'ma.json';
  
  //get data
  $data = drupal_http_request(SBAC_ALIGNMENT_DATA_PATH . $filename);
  $contents = $data->data;

  $json = drupal_json_decode($contents);
  //dsm($json);

  usort($json, 'cmp');
  $count = 0;
  foreach($json as &$term) {
    dsm($term);
    $temp = explode(':', $term['key']);
    $key = $temp[1];
    
    if(empty($term['shortname'])) {
      $term['shortName'] = $shortnames[$key];  
    }
    
    if($count++ >10){
      //break;
    }
  }
  print drupal_json_encode($json);
  
  exit;
}
/**
 *
 */
function sbac_alignment_devfix2(){
  $shortnames = get_shortnames();
  //dsm($shortnames);
  
  $publication = 'SBAC-ELA-v1';
  
  foreach ($shortnames as $key => $shortname) {
    //dsm(array($key, $shortname));
    //select fdfak.field_alignment_key_value, fdfas.field_alignment_shortname_value from field_data_field_alignment_key fdfak left join field_data_field_alignment_shortname fdfas on fdfak.entity_id = fdfas.entity_id order by fdfak.field_alignment_key_value;

    $sql = "
      UPDATE {field_data_field_alignment_shortname} fdfas
      LEFT JOIN {field_data_field_alignment_key} fdfak
      ON fdfak.entity_id = fdfas.entity_id
      SET fdfas.field_alignment_shortname_value= '$shortname'
      WHERE fdfak.field_alignment_key_value LIKE '%|$publication:$key'";
      db_query($sql);
  }
  
  return '';
}

function cmp2($a, $b) {
    if ($a->depth == $b->depth) {
        return 0;
    }
    return ($a->depth > $b->depth) ? -1 : 1;
}


function cmp($a, $b) {
    if ($a['treeLevel'] == $b['treeLevel']) {
        return 0;
    }
    return ($a['treeLevel'] < $b['treeLevel']) ? -1 : 1;
}

/**
 * Helper Function
 * Gets the file name via http.
 */
function get_file($filename) {
   //@TODO KS - add error handler
   $data = drupal_http_request(SBAC_ALIGNMENT_DATA_PATH . $filename);
   return $data->data;
}
/**
 * Helper Function
 * Gets the shortnames from file.
 */
function get_shortnames() {
  $shortnames = array();
  $data = explode("\n", get_file('ma.shortname.csv'));
  array_shift($data);
  
  foreach ($data as $row) {
    $temp = explode(',', $row);
    //$shortnames[trim($temp[0])] = array(
    //  'key' => $temp[0],
    //  'shortname' => $temp[1],
    //);
    $shortnames[trim($temp[0])] = $temp[1];
  }
  
  return $shortnames;
}

function sbac_alignment_devtest() {
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
  $print = FALSE;

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
          '8 - Eight Grade' =>  array(),
          '9 - Ninth Grade' =>  array(),
          '10 - Tenth Grade' =>  array(),
          '11 - Eleventh Grade' =>  array(),
          '12 - Twelveth Grade' =>  array(),
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
        '8 - Eight Grade' =>  array(),
        '9 - Ninth Grade' =>  array(),
        '10 - Tenth Grade' =>  array(),
        '11 - Eleventh Grade' =>  array(),
        '12 - Twelveth Grade' =>  array(),
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
  
  
  dsm($subject);
  
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
    //dsm($grade_terms);
    
    //return '';
    //get data
    $data = drupal_http_request(SBAC_ALIGNMENT_DATA_PATH . $filename);
    $contents = $data->data;

    $json = drupal_json_decode($contents);
    //dsm($json);

    uasort($json, 'cmp');
    //dsm($json);



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
        //dsm('BAD TERM');dsm($term);
        //@TODO KS - need to output in case of error
      }
    }
    
    dsm($broken_terms);
  }

  if($print) {
    $terms = taxonomy_get_tree($edu_alignment_vocab->vid, 0, NULL, TRUE);
    dsm($terms);
  }

  return '';
}
/**
 *
 */
function sbac_alignment_get_parent($key) {
  $result = db_query('SELECT frfak.entity_id
    FROM {field_revision_field_alignment_key} frfak WHERE frfak.field_alignment_key_value = :field_alignment_key_value',
    array(':field_alignment_key_value' => $key));

  return $result->fetchObject()->entity_id;
}
/**
 *
 */
function sbac_alignment_devdelete() {
  if (isset($_GET['tid'])) {
  
  }
   
   
   
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

  return '';

  
  if (!isset($_GET['tid'])) {
      return '';
   }
   
   $tid = $_GET['tid'];
   
   $terms = taxonomy_get_tree('2', $tid);
   dsm($terms);
   
   uasort($terms, 'cmp2');
   
   dsm($terms);
   foreach($terms as $term) {
      taxonomy_term_delete($term->tid);
   }
   
   
   return '';
}
