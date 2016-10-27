<?php

/**
 * New theme callback for all form elements.
 *
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function feedback_theme_form_element($variables) {
  $element = &$variables['element'];

  $attributes = array(
    'class' => array(
      'form-item-error-holder',
    ),
  );

  // if the element contains an error, add the class for CSS selection
  if (isset($element['#parents']) && form_get_error($element)) {
    $attributes['class'][] = 'error';
  }

  $output = '<div' . drupal_attributes($attributes) . '></div>' . theme('form_element_original', $variables);

  return $output;
}

/**
 * Output for Display Suite field "Resource Slideshow"
 * @param  [type] $variables [description]
 * @return [type]            [description]
 */
function theme_resource_slideshow($variables) {
  $output = '';

  if (isset($variables['entity'])) {
    $node = $variables['entity'];

    $items = array();
    $items[] = resource_slider_taxonomy($node, 'field_attributes');
    $items[] = resource_slider_text($node, 'field_student_agency');
    $items[] = resource_slider_taxonomy($node, 'field_focus');
    $items[] = resource_slider_text($node, 'field_alt_body');
    $items[] = resource_slider_text($node, 'field_learning_goals');
    $items[] = resource_slider_text($node, 'field_success_criteria');
    $items[] = resource_slider_text($node, 'field_supporting_evidence');
    $items[] = resource_slider_text($node, 'field_contexts');
    $items[] = resource_slider_text($node, 'field_connection_to_ccss');
    $items[] = resource_slider_text($node, 'field_connection_to_fap');
    $items[] = resource_slider_text($node, 'field_principles');

    // break up the fields into columns
    // we will tailor the height of each slider text to be up to the height
    // of the tallest individual item, with a minimum limit of 200 chars -
    // roughly 50 for title & 150 for body
    $max_length = 200;
    foreach ($items as $item) {
      $len = strlen($item['title'] . $item['body']);
      if ($len > $max_length) {
        $max_length = $len;
      }
    }

    $sliders = array();
    $slider = '';
    foreach ($items as $item) {
      $slider_len = strlen(strip_tags($slider));
      $item_len = strlen($item['title'] . $item['body']);

      $item_markup = resource_theme_label($item['title']);
      $item_markup .= resource_theme_body($item['body']);
      $item_markup = resource_theme_wrap_slider($node, $item['field'], $item_markup);

      // we add 60 characters for a line break in between fields
      if (($slider_len + 60 + $item_len) <= $max_length) {
        $slider .= $item_markup;
      }
      else {
        $sliders[] = $slider;
        $slider = $item_markup;
      }
    }

    // we may have a slider remaining which hasn't reached max length and thus
    // wasn't appended
    if ($slider) {
      $sliders[] = $slider;
    }

    $item_list = theme('item_list', array(
      'items' => $sliders,
      'attributes' => array(
        'class' => array(
          'slides',
        ),
      ),
    ));

    $output .= '
                <div class="flexslider item-list">
                  <div class="flex-viewport">
                    ' . $item_list . '
                  </div>
                </div>
              ';
  }
/* 
  global $user;
  if (in_array('advanced end user', $user->roles) || $user->uid==1)
  {
	$form=drupal_get_form('sbac_anonymous_url_form');
	$form['nid']['#value']=$node->nid;
	return $output.drupal_render($form);
  }
  else return $output;
*/
  return $output;
}

/**
 * Prepares output for taxonomy field.
 * @param  [type] $node       [description]
 * @param  [type] $field_name [description]
 * @return [type]             [description]
 */
function resource_slider_taxonomy($node, $field_name) {
  $body = '';

  $label = '';
  if ($terms = field_entity_value($node, $field_name)) {
    $label = resource_field_label($field_name);

    if (!is_array($terms) && is_object($terms)) {
      $terms = array($terms);
    }

    $data = array();
    foreach ($terms as $term) {
      if (is_object($term)) {
        $data[] = $term->name;
      }
      elseif ($term = taxonomy_term_load($term)) {
        $data[] = $term->name;
      }
    }

    $body = implode(', ', $data);
  }

  return array(
    'title' => $label,
    'body' => $body,
    'field' => $field_name,
  );

  return resource_theme_wrap_slider_field($node, $field_name, $output);
}

/**
 * Prepares output for text field.
 * @param  [type] $node       [description]
 * @param  [type] $field_name [description]
 * @return [type]             [description]
 */
function resource_slider_text($node, $field_name) {
  $label = resource_field_label($field_name);
  $body = field_entity_value($node, $field_name);

  return array(
    'title' => $label,
    'body' => $body,
    'field' => $field_name,
  );

  return resource_theme_wrap_slider_field($node, $field_name, $output);
}

/**
 * Wraps the slider label.
 * @param  [type] $label [description]
 * @return [type]        [description]
 */
function resource_theme_label($label) {
  return '<label class="slider-label">' . t($label) . '</label>';
}

/**
 * Wraps the slider body.
 * @param  [type] $label [description]
 * @return [type]        [description]
 */
function resource_theme_body($body) {
  return '<div class="slider-body">' . $body . '</div>';
}

/**
 * Wraps output field.
 * @param  [type] $node       [description]
 * @param  [type] $field_name [description]
 * @param  [type] $output     [description]
 * @return [type]             [description]
 */
function resource_theme_wrap_slider($node, $field_name, $output) {
  return '<div class="' . $node->type . '-field content-field ' . $node->type . '-' . $field_name . '">' . $output . '</div>';
}
