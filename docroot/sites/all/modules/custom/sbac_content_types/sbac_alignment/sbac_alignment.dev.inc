<?php
/**
 *
 */
function sbac_alignment_devtest() {
  dsm($_SERVER);
  //dsm('http://' . $_SERVER['HTTP_HOST'] . '/' .  drupal_get_path('module', 'sbac_alignment') . '/data/ela.json');
  if(isset($_GET['vocab'])) {
    $edu_alignment_vocab_name = $_GET['vocab'];
  }
  else {
    $edu_alignment_vocab_name = "education_alignment2";
  }

  $edu_alignment_vocab = taxonomy_vocabulary_machine_name_load($edu_alignment_vocab_name);
  $grade_terms = array();

  $read = FALSE;
  $create_base = TRUE;
  $create = TRUE;
  $print = FALSE;

  if($read) {
    $data = drupal_http_request( 'http://' . $_SERVER['HTTP_HOST'] . '/' .  drupal_get_path('module', 'sbac_alignment') . '/data/ela.sample.json');
    dsm($data->data);
    $contents = $data->data;
   // return '';
  ////get data
  //  $filename = $_SERVER['DOCUMENT_ROOT'] . '/' . drupal_get_path('module', 'sbac_alignment') . '/data/ela.sample.json';
  //  $handle = fopen($filename, "r");
  //  $contents = fread($handle, filesize($filename));
  //  fclose($handle);

    $json = drupal_json_decode($contents);
    dsm($json);
  }

  // create base terms
  if ($create_base) {
    // Add education alignment
    $terms = array(
      'English Language Arts' => array(
        'desc' => 'lorem ipsum',
        'children' => array(
          'KG - Kindergarten' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '1 - First Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '2 - Second Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '3 - Third Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '4 - Fourth Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '5 - Fifth Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '6 - Sixth Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '7 - Seventh Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '8 - Eight Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '9 - Ninth Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '10 - Tenth Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '11 - Eleventh Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
          '12 - Twelveth Grade' =>  array(
            'desc' => 'lorem ipsum',
          ),
        ),
      ),
    );
    sbac_alignment_add_terms($edu_alignment_vocab->vid, $terms);
  }

  //create terms
  if ($create) {
    // get grades tids
    $terms = taxonomy_get_tree($edu_alignment_vocab->vid, 0, 2, TRUE);
    foreach ($terms as $term) {
      if($term->depth == 1) {
        $name = explode('-', $term->name);
        $grade_terms[''+truncate($name[0])] = $term;
      }
    }

    //get data
    $data = drupal_http_request( 'http://' . $_SERVER['HTTP_HOST'] . '/' .  drupal_get_path('module', 'sbac_alignment') . '/data/ela.json');

    $contents = $data->data;

    $json = drupal_json_decode($contents);
    //dsm($json);

    // build tree
    $parent_tid = 0;
    $parents = array();
    foreach ($json as $term) {
      //dsm($term);
      $grade = truncate($term['fkGradeLevel']);

      // Root term. first set after the grade
      if ($term['treeLevel'] < 2) {
        $parent_tid = $grade_terms[$grade]->tid;
        sbac_alignment_add_term($edu_alignment_vocab->vid, $term, $parent_tid);
      }
      elseif($term['treeLevel'] >=2) {
        $parent_key = $grade . '|' . $term['fkParent'];
        $parent_tid = sbac_alignment_get_parent($parent_key);
        //$parent_tid = $parents[$parent_key]->tid;
        //dsm(array($parent_key, $parent_tid));
        if (empty($parent_tid)) {
          //cannot find parent save to grade
          $parent_tid = $grade_terms[$grade]->tid;
        }
        $key = $grade . '|' . $term['key'];
        $parents[$key] = sbac_alignment_add_term($edu_alignment_vocab->vid, $term, $parent_tid);
      }
      else{
        //dsm('BAD TERM');dsm($term);
        //@TODO KS - need to output in case of error
      }
    }
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
}
