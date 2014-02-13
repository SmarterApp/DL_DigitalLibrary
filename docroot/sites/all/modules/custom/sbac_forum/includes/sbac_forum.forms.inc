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
    '#attributes' => array('id' => 'sbac-search-current-filters'),
  );

  // $form['search_categories'] = array(
  //   '#markup' => sbac_search_my_resources_categories(),
  // );

  $form['filter'] = array(
    '#type' => 'submit',
    '#value' => ($current_filters != NULL) ? t('Edit Filters') : t('Apply Filters'),
    '#attributes' => array(
      'id' => 'sbac-search-filter-button',
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
          'data' => array('sbac_search' => array('isEdit' => ($current_filters != NULL ? 1 : 0))),
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
