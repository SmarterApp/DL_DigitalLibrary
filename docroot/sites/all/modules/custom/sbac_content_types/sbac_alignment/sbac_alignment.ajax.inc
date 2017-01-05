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
  $terms = taxonomy_get_tree($vocab->vid, 0, SBAC_ALIGNMENT_MAX_DEPTH);

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
  $output .= '<div class="alignment-buttons"><a href="#" title="Add Standards" id="edit-submit" class="button disabled">Add Standard(s) to Resource</a><a href="#" title="Cancel" id="ccss-cancel" class="button ctools-close-modal close">Cancel</a></div>';
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
  if (isset($_POST['remove'])) {
    $temp = array_shift(taxonomy_get_parents($parent->tid));
    if (empty($temp)) {
      $parent->tid = 0;
    }
    else {
      $parent = $temp;
    }
  }

  $output_array['parent'] = $parent;
  $terms = taxonomy_get_tree($vocab->vid, $parent->tid, SBAC_ALIGNMENT_MAX_DEPTH);
  $publication = $parent->field_alignment_publication['und'][0]['value'];
  $output_array['publication'] = (empty($publication)) ? 0 : $publication;
  $output_array['depth'] = $depth = sbac_alignment_taxonomy_term_depth($parent->tid);
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

    $options = array(
      'attributes' => array(
        'id' => 'term-' . $term->tid,
        'class' => 'sbac-custom-term button',
        'tid' => $term->tid,
        'title' => $term->name,
      ),
      'html' => TRUE,
    );
    $subject_array[] = l($term->name, '#', $options);
  }

  $output_array['tids_count'] = count($output_array['tids']);
  $output = theme('alignment_tags', array('terms' => $terms, 'level_title' => $level_title));
  $output_array['html'] = $output;

  print drupal_json_encode($output_array);
  exit;
}

/**
 * TODO: Delete this when the filter widget is no longer needed.
 */
function sbac_alignment_ajax_filter_alignment_confirm_remove_callback() {
  $output = theme('alignment_modal_confirm', array('terms' => array()));
  $output_array['html'] = $output;
  print drupal_json_encode($output_array);
  exit;
}

function _sbac_alignment_get_alignment_unique($tid) {
  $term = taxonomy_term_load($tid);
  return $term['field_alignment_crosswalk'][LANGUAGE_NONE][0]['value'];
}

function _sbac_alignment_child_lookup($alignment_type, $id) {
  $vocab = taxonomy_vocabulary_machine_name_load($alignment_type);

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $vocab->vid, '=')
    ->fieldCondition('field_alignment_crosswalk', 'value', $id, '=');
  $result = $query->execute();

  $entities = array();
  if (isset($result['taxonomy_term']) && count($result['taxonomy_term']) > 0) {
    $entities = array_keys($result['taxonomy_term']);
  }

  return $entities;
}

function _sbac_alignment_build_table_row($tid, $selected, $indent = FALSE) {
  // load the term and get the subject, grade, and clam from its parents
  $term = taxonomy_term_load($tid);
  $parents = taxonomy_get_parents_all($tid);
  $subject = array_pop($parents);
  $grade = array_pop($parents);
  $pos = strpos($grade->name, ':');
  if ($pos !== FALSE) {
    $grade = substr($grade->name, $pos + 1);
  }
  $claim = array_pop($parents);
  // Get the publication from the term, and set the label for CC-ELA-v1
  $publication = $term->field_alignment_publication['und'][0]['value'];
  if ($publication == 'CC-ELA-v1') {
    $level_title = "Strand/Domain";
  } else {
    $level_title = "Domain";
  }
  // Get the standard name from the term
  $name = $term->name;
  // Build the id/name based on the parent/child state and the tid
  $id = "-$tid";
  if ($indent) {
    $name = "&nbsp;&nbsp" . $name;
    $id = 'standard-child' . $id;
  } else {
    $id = 'standard-parent' . $id;
  }
  // Mark the items as checked if it is selected
  $checked = '';
  if ($selected) {
    $checked = ' checked="checked"';
  }

  // Return the row array
  return array(
    $name,
    "<div class=\"read-more\">
        <a href=\"#\" title=\"Read More\" class=\"\"><i class=\"accessibility foundicon-eyeball\"></i><span>Read More</span></a>
        <div class=\"more description-hover\">
          <div class=\"description-content\">
            <h2>" . $subject->name . "</h2>
            <div class=\"standard-description\">
              <h3>Standard Description</h3>
              " . $term->description . "
            </div>
            <div class=\"standard-grade\">
              <h3>Grade</h3>
              " . $grade . "
            </div>
            <div class=\"standard-claim\">
              <h3>" . $level_title . "</h3>
              " . $claim->field_alignment_shortname['und'][0]['value'] . "
            </div>
          </div>
        </div>
      </div>",
    '<input type="checkbox" name="' . $id . '" id="' . $id . '" value="' . $tid . '"' . $checked . '/>',
  );
}

function _sbac_alignment_build_table_rows($alignment_array) {
  $rows = array();
  // Go through the selected items and their children and add the rows for these
  foreach ($alignment_array as $tid => $info) {
    $rows[] = _sbac_alignment_build_table_row($tid, $info['selected']);
    foreach ($info['children'] as $cid => $child) {
      $rows[] = _sbac_alignment_build_table_row($cid, $child['selected'], TRUE);
    }
  }
  return $rows;
}

function _sbac_alignment_table_builder($new, $current, $main_alignment) {
  $all_terms = array_merge($new, $current);
  if (count($all_terms)) {
    // Make sure we know what the other taxonomy type is
    $other_alignment = SBAC_ALIGNMENT_VOCAB_NAME;
    if ($main_alignment == $other_alignment) {
      $other_alignment = SBAC_ALIGNMENT_TARGET_VOCAB_NAME;
    }
    // Load taxonomy terms
    $terms = taxonomy_term_load_multiple($all_terms);
    // Load the vocabs
    $main_alignment_vocab = taxonomy_vocabulary_machine_name_load($main_alignment);
    $other_alignment_vocab = taxonomy_vocabulary_machine_name_load($other_alignment);
    // Initialize the array of selected items
    $alignment_selection = array(SBAC_ALIGNMENT_VOCAB_NAME => array(), SBAC_ALIGNMENT_TARGET_VOCAB_NAME => array());

    // Build the tables with the current items (if any)
    foreach ($terms as $tid => $term) {
      $current_alignment = $term->vid == $main_alignment_vocab->vid ? $main_alignment : $other_alignment;
      // Add the term and it's children
      // Get the unique value for this standard
      $alignment_unique = _sbac_alignment_get_alignment_unique($tid);
      // Get the tids of the associated tags from the other standard
      $children = _sbac_alignment_child_lookup($other_alignment, $alignment_unique);
      // Go through each tid and add it with the proper selection state
      foreach ($children as $child) {
        // Mark it as selected if this child was selected as a parent item, or if the current parent is new (we select by default)
        if (in_array($child, $current) || in_array($tid, $new)) {
          $alignment_selection[$current_alignment][$tid]['children'][$child]['selected'] = 1;
        } else {
          $alignment_selection[$current_alignment][$tid]['children'][$child]['selected'] = 0;
        }
      }
      // Mark this item as selected
      $alignment_selection[$current_alignment][$tid]['selected'] = 1;
    }

    // The render array for the CC standards
    $ccss_table = array(
      '#theme' => 'table',
      '#header' => array(t('Standard'), array('data' => t('Operations'), 'colspan' => 2)),
      '#rows' => _sbac_alignment_build_table_rows($alignment_selection[SBAC_ALIGNMENT_VOCAB_NAME]),
    );
    // The render array for the target standards
    $target_table = array(
      '#theme' => 'table',
      '#header' => array(t('Target'), array('data' => t('Operations'), 'colspan' => 2)),
      '#rows' => _sbac_alignment_build_table_rows($alignment_selection[SBAC_ALIGNMENT_TARGET_VOCAB_NAME]),
    );

    // The array of rendered tables
    $tables = array(
      'ccss_html' => render($ccss_table),
      'target_html' => render($target_table),
    );
  } else {
    $tables = array(
      'ccss_html' => '',
      'target_html' => '',
    );
  }
  return $tables;
}

/**
 * AJAX Callback
 * CRUD for Alignment nodes.
 */
function sbac_alignment_ajax_alignment_crud_callback() {
  // Grab the JSON from the POST
  $json_input = json_decode(file_get_contents('php://input'));

  // Output the tables as JSON
  drupal_json_output(_sbac_alignment_table_builder(
    $json_input['new_standards'],
    $json_input['current_standards'],
    $json_input['alignment_type']
  ));

//  global $user;
//  $op = 'none';
//  $nid = 0;
//  if (isset($_POST['op'])) {
//    $op = $_POST['op'];
//  }
//
//  switch ($op) {
//    case 'delete':
//      if (isset($_POST['nid'])) {
//        $nid = $_POST['nid'];
//      }
//      // prep JSON response
//      $data = array(
//        'deleted_nid' => $nid,
//      );
//
//      $node = node_load($nid);
//      if (node_access('delete', $node)) {
//        // node_delete($nid);
//        $current_nid = $_POST['current_nid'];
//        // set the entity reference field_data_field_resource_reference deleted flag to 2
//        db_query('UPDATE field_data_field_resource_reference SET deleted = :deleted WHERE field_resource_reference_target_id = :target_id AND entity_id = :entity_id', array(':deleted' => 2, ':target_id' => $current_nid, ':entity_id' => $nid));
//      }
//
//      print drupal_json_encode($data);
//
//      break;
//
//    case 'create':
//      if (isset($_POST['alignment_standards'])) {
//        $standards = explode('|', $_POST['alignment_standards']);
//        array_shift($standards);
//      }
//      if (isset($_POST['alignment_type'])) {
//        $alignment_type = $_POST['alignment_type'];
//      }
//      if (isset($_POST['alignment_ref'])) {
//        $alignment_ref = $_POST['alignment_ref'];
//      }
//      else {
//        $alignment_ref = 537;
//      }
//
//      $types = array();
//      $vocab = taxonomy_vocabulary_machine_name_load(SBAC_ALIGNMENT_TYPE_VOCAB_NAME);
//      $terms = taxonomy_get_tree($vocab->vid, 0, SBAC_ALIGNMENT_MAX_DEPTH);
//
//      foreach ($terms as $term) {
//        $types[$term->name] = $term->tid;
//      }
//
//      $standards_terms = array();
//      foreach ($standards as $tid) {
//        //create alignment
//        $node = new stdClass();
//        $node->title = "resource-$alignment_ref-alignment-$tid";
//        $node->type = 'alignment';
//        $node->uid = $user->uid;
//        node_object_prepare($node);
//
//        $node->field_education_alignment['und'][]['tid'] = $tid;
//        $node->field_alignment_type['und'][]['tid'] = $types[$alignment_type];
//        $node->field_resource_reference['und'][]['target_id'] = $alignment_ref;
//        node_save($node);
//
//        // Set the deleted flag to 1 to create a temp new alignment.
//        db_query('UPDATE field_data_field_resource_reference SET deleted = :deleted WHERE field_resource_reference_target_id = :target_id AND entity_id = :entity_id', array(':deleted' => 1, ':target_id' => $alignment_ref, ':entity_id' => $node->nid));
//
//        $term = taxonomy_term_load($tid);
//        $standards_terms[] = $term->name;
//      }
//
//      $data = array(
//        'html' => views_embed_view('alignment', 'resource_admin_view', $alignment_ref),
//        'terms' => $standards_terms,
//      );
//
//      print drupal_json_encode($data);
//
//      exit;
//      break;
//  }
//  exit;
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

  print drupal_json_encode($data);
  exit;
}

/**
 * AJAX Callback
 * Lazy-loading the form.
 */
function sbac_alignment_ajax_alignment_form_callback() {
  $tid = $_POST['tid'];
  $output['html'] = drupal_render(drupal_get_form('sbac_alignment_alignment_form', $tid));
  print drupal_json_encode($output);
  exit;
}
/**
 * AJAX Callback - filter dialog for ccss
 * Lazy-loading the form.
 * TODO: Delete this when the filter widget is no longer needed.
 */
function sbac_alignment_ajax_filter_alignment_form_callback() {
  $tid = $_POST['tid'];
  $output['html'] = drupal_render(drupal_get_form('sbac_alignment_filter_alignment_form', $tid));
  print drupal_json_encode($output);
  exit;
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
  print drupal_json_encode($output);
  exit;
}
