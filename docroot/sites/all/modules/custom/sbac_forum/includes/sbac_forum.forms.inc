<?php


/**
 * Form for submitting the forum category filters.
 *
 * @return array
 */
function sbac_forum_category_forum_form() {
  $form = array();

  $hide_categories_text = t('Hide Categories');
  $hide_categories_class = 'active';
  $should_hide_categories = '';
  if (isset($_COOKIE[SBAC_FORUM_FILTERS_CLOSED]) && $_COOKIE[SBAC_FORUM_FILTERS_CLOSED]) {
    $should_hide_categories = ' style="display:none;"';
  }

  $current_filters = NULL;
  if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
    $current_filters = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
  }

  if ($should_hide_categories) {
    $hide_categories_text = t('Show Categories');
    $hide_categories_class = '';
  }

  $form['current_filters'] = array(
    '#prefix' => '<a class="category-hide js-hide '. $hide_categories_class .'" href="#">' . $hide_categories_text . '</a>',
    '#type' => 'hidden',
    '#value' => $current_filters,
    '#attributes' => array('id' => 'sbac-forum-current-filters'),
  );

  $form['search_categories'] = array(
    '#markup' => _sbac_forum_filter_categories(),
  );

  $form['filter'] = array(
    '#type' => 'submit',
    '#value' => ($current_filters != NULL) ? t('Edit Filters') : t('Apply Filters'),
    '#attributes' => array(
      'id' => 'sbac-forum-filter-button',
      'class' => array(
        ($current_filters != NULL) ? 'is-edit': 'is-apply',
        ($current_filters == NULL) ? 'js-hide': ''
      ),
    ),
    '#prefix' => '<div class="category-buttons slideable" '. $should_hide_categories .'>',
    '#ajax' => array(
      'wrapper' => '',
      'method' => 'replace',
      'effect' => 'fade'
    ),
    '#attached' => array(
      'js' => array(
        array(
          'data' => array('sbac_forum' => array('isEdit' => ($current_filters != NULL ? 1 : 0))),
          'type' => 'setting',
        ),
      ),
    ),
  );

  $form['reset_filters'] = array(
    '#type' => 'submit',
    '#value' => t('Reset Filters'),
    '#attributes' => array(
      'class' => array('js-hide'),
    ),
    '#suffix' => '</div>',
  );

  return $form;
}


function _sbac_forum_filter_categories() {
  $categories = array();
  drupal_add_js(drupal_get_path('module', 'sbac_forum') . '/js/sbac_forum.filter_categories.js');

  $subject = taxonomy_vocabulary_machine_name_load('subject');
  $categories['subject']['display_name'] = 'Subjects';
  $categories['subject']['vocabulary'] = $subject;
  $categories['subject']['terms'] = taxonomy_get_tree($subject->vid);

  $grades = taxonomy_vocabulary_machine_name_load('grades');
  $categories['grades']['display_name'] = 'Grades';
  $categories['grades']['vocabulary'] = $grades;
  $categories['grades']['terms'] = taxonomy_get_tree($grades->vid);

  $intended_student_populations = taxonomy_vocabulary_machine_name_load('intended_student_populations');
  $categories['intended_student_populations']['display_name'] = 'Intended Student Populations';
  $categories['intended_student_populations']['vocabulary'] = $intended_student_populations;
  $categories['intended_student_populations']['terms'] = taxonomy_get_tree($intended_student_populations->vid);

  $intended_end_user = taxonomy_vocabulary_machine_name_load('intended_end_user');
  $categories['intended_end_user']['display_name'] = 'Intended End Users';
  $categories['intended_end_user']['vocabulary'] = $intended_end_user;
  $categories['intended_end_user']['terms'] = taxonomy_get_tree($intended_end_user->vid);

  $cf_value = NULL;
  $cf_html = array();
  if (isset($_SESSION[SBAC_FORUM_CATEGORY_FILTERS])) {
    $cf_value = $_SESSION[SBAC_FORUM_CATEGORY_FILTERS];
    if ($cf_value) {
      $filters = explode('::', $cf_value);
      if ($filters) {
        foreach ($filters as $filter) {
          $filter_info = explode(':', $filter);
          if ($filter_info && sizeof($filter_info) == 2) {
            $vid = $filter_info[0];
            $tid = $filter_info[1];
            if ($vid && $tid) {
              $term = taxonomy_term_load($tid);
              if ($term) {
                $cf_html[] = '<div class="current-filter"><span vid="' . $vid . '" tid="' . $tid . '" class="filter-name">' . $term->name . '</span></div>';
              }
            }
          }
        }
      }
    }
  }

  $output = NULL;
  if ($categories) {
    $output = theme('sbac_forum_filter_categories', array('categories' => $categories, 'cf_value' => $cf_value, 'cf_html' => $cf_html));
  }
  return $output;
}
