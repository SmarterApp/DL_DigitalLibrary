<?php
/**
 * @file
 * Code for the SBAC Landing Page filters
 * 
 */

/**
 * Returns the category filters for the Landing Page.
 *
 * @return null
 */
function sbac_search_landing_page_categories() {
  $categories = array();
  drupal_add_css(drupal_get_path('module', 'sbac_search') . '/css/sbac_search.css');
  drupal_add_js(drupal_get_path('module', 'sbac_search') . '/js/sbac_search.landing-page.categories.js');
  libraries_load('jstree');

  _sbac_search_create_taxonomy_filter($categories, 'attributes', 'Formative Assessment Attributes', 'im_field_attributes');
  _sbac_search_create_taxonomy_filter($categories, 'subject', 'Subjects', 'im_field_subject');
  _sbac_search_create_taxonomy_filter($categories, 'grades', 'Grades', 'im_field_grades');
  
  $attrs = array(
    'attributes' => array(
      'class' => 'ctools-use-modal ctools-modal-ctools-ccss-style',
      'id' => 'sbac-resource-modal-alignment2',
      'title' => 'Filter Alignment',
    ),
  );
  $link = l('Common Core State Standards', 'sbac_resource/nojs/filter-by-alignment', $attrs);
  $categories['education_alignment']['display_name'] = 'Common Core State Standards';
  $vocab = taxonomy_vocabulary_machine_name_load('education_alignment');
  $categories['education_alignment']['vocabulary'] = $vocab;
  $categories['education_alignment']['terms'] = array();
  $categories['education_alignment']['link'] = $link;
  
  // Add facet ids
  $categories['attributes']['facet'] = 'field_alignment_term';
  $categories['subject']['facet'] = 'field_subject';
  $categories['grades']['facet'] = 'field_grades';
  $categories['education_alignment']['facet'] = 'field_alignment_term';
  
  $output = NULL;
  if ($categories) {
    $output = theme('sbac_landing_page_categories', array('categories' => $categories));
  }

  return $output;
}

/**
 * Form for submitting the category filters on the Landing Page.
 *
 * @return array
 */
function sbac_search_landing_page_resources_form() {
  $form = array();
  $hide_categories_text = t('Filters');
  $hide_categories_class = 'active';

  $form['current_filters'] = array(
    '#type' => 'hidden',
    '#value' => $current_filters,
    '#attributes' => array('id' => 'sbac-search-current-filters'),
  );

  $form['search_categories'] = array(
    '#markup' => sbac_search_landing_page_categories(),
  );

  $form['more']= array (
    '#type' => 'fieldset', 
    '#prefix' => '<div class="more-buttons">',
    '#suffix' => '</div>',
  );
  $form['more']['more-filters'] = array(
    '#type' => 'link',
    '#title' => t('More Filters'),
    '#href' => '/digital-library-resources',
    '#id' => 'more-filters-link',
    '#prefix' => '<div class="more-filters">',
    '#suffix' => '</div>',

  );

  $form['more']['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Find Resources'),
    '#attributes' => array(
      'id' => 'sbac-search-filter-button',
    ),
    '#prefix' => '<div class="category-buttons">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'wrapper' => '',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  return $form;
}

/**
 * Submit handler for categories.
 *
 * @param $form
 * @param $form_state
 */
function sbac_search_landing_page_resources_form_submit(&$form, &$form_state) {
  $query = array();
  $facets = explode('::', $form_state['input']['current_filters']);
  foreach($facets as $key => $value){
    $query["f[$key]"] = $value;
  }
  $form_state['redirect'] =  array(
    'digital-library-resources',
    array(
      'query' => $query
    ),
  );
}
