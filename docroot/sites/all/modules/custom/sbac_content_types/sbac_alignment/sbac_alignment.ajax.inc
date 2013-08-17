<?php
function sbac_alignment_ajax_get_child_callback($form, $form_state) {
  //@TODO KS - add get child implmentation here.

  print drupal_json_encode(array('123'));
  exit;
}
/**
 * AJAX Callback
 */
function sbac_alignment_ajax_alignment_breadcrumbs_callback() {
  $output = $terms = array();
  $parents = taxonomy_get_parents_all($_POST['tid']);
  $output['html'] = theme('alignment_breadcrumbs', array('terms' => array_reverse($parents)));
  print drupal_json_encode($output);
  exit;
}
/**
 * AJAX Callback
 */
function sbac_alignment_ajax_terms_callback() {
  $subject_array = $output_array = array();
  $vocab = taxonomy_vocabulary_machine_name_load(SBAC_ALIGNMENT_VOCAB_NAME);
  $parent = taxonomy_term_load($_POST['parent']);
  if(isset($_POST['remove'])) {
    $temp = array_shift(taxonomy_get_parents($parent->tid));
    if(empty($temp)) {
      $parent->tid = 0;
    }
    else {
      $parent = $temp;
    }
  }

  $output_array['parent'] = $parent;
  $terms = taxonomy_get_tree($vocab->vid, $parent->tid, SBAC_ALIGNMENT_MAX_DEPTH);

  $output_array['depth'] = sbac_alignment_term_depth($parent->tid);
  $output_array['tids'] = array();
  foreach ($terms as $term) {
    $output_array['tids'][] = $term;
    $children = taxonomy_get_children($term->tid);
    $output_array['children'][] = $children;

    $options = array(
      'attributes' => array(
        'id' => 'term-' . $term->tid,
        'class' => 'sbac-custom-term button',
        'tid' => $term->tid,
      ),
      'html' => TRUE,
    );
    $subject_array[] = l($term->name, '#', $options);
  }

  $output_array['tids_count'] = count($output_array['tids']);

  $output .= theme('alignment_tags', array('terms' => $terms));
  $output_array['html'] = $output;

  print drupal_json_encode($output_array);
  exit;
}
