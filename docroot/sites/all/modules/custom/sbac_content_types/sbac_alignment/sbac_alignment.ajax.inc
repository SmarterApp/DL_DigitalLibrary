<?php

/**
 * Page Callback
 * Outputs the alignment tagger UI.
 */
function sbac_alignment_ajax_alignment_page($ref_node = NULL) {
  drupal_add_js(libraries_get_path('jquery.more') . '/jquery.more.js');
  drupal_add_css(libraries_get_path('jquery.more') . '/jquery.more.css');
  drupal_add_js(drupal_get_path('theme', 'sbac') . '/js/custom.js');
  drupal_add_css(drupal_get_path('module', 'sbac_alignment') . '/css/alignment.css');

  $alignment = sbac_alignment_type();
  $vocab = taxonomy_vocabulary_machine_name_load($alignment['type']);
  $terms = taxonomy_get_tree($vocab->vid, 0, 1, TRUE);
  $button = sbac_alignment_type_button_name();

  drupal_add_js(array(
      'sbac_alignment_everything' => array('type' => $alignment['type'], 'container' => $alignment['container'])
    ),
    array('type' => 'setting')
  );

  $output = '<div id="alignment-page"><input id="ref_node" style="display:none" value="' . $ref_node . '"> ';
  $output .= '<div class="alignment-breadcrumb"></div>';
  $output .= '<div id="alignment-msg"></div>';
  $output .= '<div class="alignment-filter">';
  $output .= theme('alignment_tags', array('terms' => $terms, 'level_title' => 'Choose Your Subject Area'));
  $output .= '</div><div class="alignment-form"></div>';
  $output .= '<div class="alignment-buttons"><a href="#" title="Add Standards" id="edit-submit" class="button disabled">' . $button . '</a><a href="#" title="Cancel" id="ccss-cancel" class="button ctools-close-modal close">Cancel</a></div>';
  $output .= '</div></div>';

  return $output;
}

/**
 * Page Callback
 * Outputs the alignment tagger UI.
 * TODO: Delete this when the filter widget is no longer needed.
 */
function sbac_alignment_ajax_filter_alignment_page($ref_node = NULL) {
  drupal_add_js(libraries_get_path('jquery.more') . '/jquery.more.js');
  drupal_add_css(libraries_get_path('jquery.more') . '/jquery.more.css');
  drupal_add_js(drupal_get_path('theme', 'sbac') . '/js/custom.js');
  drupal_add_css(drupal_get_path('module', 'sbac_alignment') . '/css/alignment.css');

  $vocab = taxonomy_vocabulary_machine_name_load(SBAC_ALIGNMENT_VOCAB_NAME);
  $terms = taxonomy_get_tree($vocab->vid, 0, SBAC_ALIGNMENT_MAX_DEPTH);

  $output = '<div id="alignment-page"><input id="ref_node" style="display:none" value="' . $ref_node . '"> ';
  $output .= '<div class="alignment-breadcrumb"></div>';
  $output .= '<div id="alignment-msg"></div>';
  $output .= '<div class="alignment-filter">';
  $output .= theme('alignment_tags', array('terms' => $terms, 'level_title' => 'Choose Your Subject Area'));
  $output .= '</div><div class="alignment-form"></div>';
  $output .= '<div class="alignment-buttons"><a href="#" title="Add Selections" id="edit-submit" class="button disabled">Add Selections</a>';
  $output .= '<a href="#" title="Cancel" id="ccss-cancel" class="button ctools-close-modal close">Cancel</a></div>';
  $output .= '</div></div>';

  return $output;
}


/**
 * AJAX Callback
 */
function sbac_alignment_ajax_terms_callback() {
  $subject_array = $output_array = array();
  $ela_cc_titles = array(
    'Choose Your Subject Area',
    'Choose Your Grade',
    'Choose Your Strand/Domain',
    'Choose Your Common Core Standard(s), ELA Anchor Standard(s), and/or Mathematical Practice(s)',
  );
  $ma_cc_titles = array(
    'Choose Your Subject Area',
    'Choose Your Grade',
    'Choose Your Domain',
    'Choose Your Common Core Standard(s), ELA Anchor Standard(s), and/or Mathematical Practice(s)',
  );
  $ela_ta_titles = array(
    'Choose Your Subject Area',
    'Choose Your Grade',
    'Choose Your Domain',
    'Choose Your Target Alignment ELA Standard(s)',
  );
  $ma_ta_titles = array(
    'Choose Your Subject Area',
    'Choose Your Grade',
    'Choose Your Domain',
    'Choose Your Target Alignment Math Standard(s)',
  );
  $defaults = array(
    'Choose Your Subject Area',
    'Choose Your Grade',
    'Choose Your Domain',
    'Choose Your Standard(s)',
  );

  $alignment = sbac_alignment_type();
  $vocab = taxonomy_vocabulary_machine_name_load($alignment['type']);
  $parent = taxonomy_term_load($_POST['parent']);
  $treetop = $parent->tid;
  if (isset($_POST['remove'])) {
    $parents = taxonomy_get_parents($parent->tid);
    $temp = array_shift($parents);
    if (!count($parents)) {
      $treetop = 0;
    }
    else {
      $parent = $temp;
      $treetop = $parent->tid;
    }
  }

  $output_array['parent'] = $parent;
  $terms = taxonomy_get_tree($vocab->vid, $treetop, 1, TRUE);
  $publication = $parent->field_alignment_publication[LANGUAGE_NONE][0]['value'];
  $output_array['publication'] = (empty($publication)) ? 0 : $publication;
  $output_array['depth'] = $depth = $treetop == 0 ? 0 : sbac_alignment_taxonomy_term_depth($treetop);
  switch ($publication) {
    case 'CC-MA-v1':
      $level_title = $ma_cc_titles[$depth];
      break;
    case 'CC-ELA-v1':
      $level_title = $ela_cc_titles[$depth];
      break;
    case 'TA-MA-v1':
      $level_title = $ma_ta_titles[$depth];
      break;
    case 'TA-ELA-v1':
      $level_title = $ela_ta_titles[$depth];
      break;
    default:
      $level_title = $defaults[$depth];
  }

  $output_array['tids'] = array();
  foreach ($terms as $term) {
    $pos = strpos($term->name, ':');
    if ($pos !== FALSE) {
      $new_name = substr($term->name, $pos + 1);
      $term->name = trim($new_name);
    }

    $output_array['tids'][] = $term;
    $children = taxonomy_get_children($term->tid);
    $output_array['children'][] = $children;
  }

  $output_array['tids_count'] = count($output_array['tids']);
  $output = theme('alignment_tags', array('terms' => $terms, 'level_title' => $level_title));
  $output_array['html'] = $output;

  drupal_json_output($output_array);
}

/**
 * TODO: Delete this when the filter widget is no longer needed.
 */
function sbac_alignment_ajax_filter_alignment_confirm_remove_callback() {
  $output = theme('alignment_modal_confirm', array('terms' => array()));
  $output_array['html'] = $output;
  drupal_json_output($output_array);
}

/**
 * AJAX Callback
 * CRUD for Alignment nodes.
 */
function sbac_alignment_ajax_alignment_crud_callback() {
  // Grab the JSON from the POST
  $json_input = json_decode(file_get_contents('php://input'));

  // Output the tables as JSON
  if (property_exists($json_input, 'first_select')) {
    $output = _sbac_alignment_table_builder($json_input->new_standards, $json_input->current_standards, $json_input->alignment_type, $json_input->first_select);
  } else {
    $output = _sbac_alignment_table_builder($json_input->new_standards, $json_input->current_standards, $json_input->alignment_type);
  }

  drupal_json_output($output);
}

/**
 * AJAX Callback
 * CRUD for Alignment nodes.
 * TODO: Delete this when the filter widget is no longer needed.
 */
function sbac_alignment_ajax_filter_alignment_finish_set_callback() {
  global $user;
  $op = 'none';
  if (isset($_POST['op'])) {
    $op = $_POST['op'];
  }

  if (isset($_POST['alignment_standards'])) {
    $standards = explode('|', $_POST['alignment_standards']);
    array_shift($standards);
  }

  $types = array();
  $vocab = taxonomy_vocabulary_machine_name_load(SBAC_ALIGNMENT_VOCAB_NAME);

  $standards_terms = array();
  $filter_markup = array();
  $filter_hidden = array();

  $term_information = taxonomy_term_load_multiple($standards);
  foreach ($standards as $tid) {
    $label = '';
    $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term_information[$tid]);
    if (isset($term_wrapper->field_alignment_shortname)) {
      $label = $term_wrapper->field_alignment_shortname->value();
    } else {
      $label = $term_wrapper->name->value();
    }
    
    $filter_text = '<div class="current-filter" class="filter-name" tid="'.$tid.'" vid="im_field_alignment_term">';
    $filter_text .= $label;
    $filter_text .= '</div>';
    $filter_markup[] = $filter_text;

    $filter_hidden[] = $vocab->vid . ':' . $tid;
  }

  $html = implode('',$filter_markup);
  $filters = implode('::',$filter_hidden);
  $data = array(
    'html' => $html,
    'filters' => $filters,
  );

  drupal_json_output($data);
}

/**
 * AJAX Callback
 * Lazy-loading the form.
 */
function sbac_alignment_ajax_alignment_form_callback() {
  $tid = $_POST['tid'];
  $output['html'] = drupal_render(drupal_get_form('sbac_alignment_alignment_form', $tid));
  drupal_json_output($output);
}
/**
 * AJAX Callback - filter dialog for ccss
 * Lazy-loading the form.
 * TODO: Delete this when the filter widget is no longer needed.
 */
function sbac_alignment_ajax_filter_alignment_form_callback() {
  $tid = $_POST['tid'];
  $output['html'] = drupal_render(drupal_get_form('sbac_alignment_filter_alignment_form', $tid));
  print drupal_json_output($output);
}


/**
 * AJAX Callback
 * Outputs the breadcumbs.
 */
function sbac_alignment_ajax_alignment_breadcrumbs_callback() {
  $output = $terms = array();
  $parents = taxonomy_get_parents_all($_POST['tid']);

  foreach ($parents AS $key => $term) {
    $pos = strpos($term->name, ':');
    // Remove the ":" from the string.
    if ($pos !== FALSE) {
      $new_name = substr($term->name, $pos + 1);
      $term->name = trim($new_name);
      $parents[$key] = $term;
    }

    // Trim the name if its greater then 41 characters.
    if (strlen($term->name) > 41) {
      $term->name = substr($term->name, 0, 41) . '...';
      $parents[$key] = $term;
    }
  }

  $output['html'] = theme('alignment_breadcrumbs', array('terms' => array_reverse($parents)));
  drupal_json_output($output);
}
