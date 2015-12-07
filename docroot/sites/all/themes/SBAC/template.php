<?php

/**
 * Implements theme_links() targeting the main menu specifically
 * Outputs Foundation Nav bar http://foundation.zurb.com/docs/navigation.php
 *
 */
//function SBAC_links__system_main_menu($vars) {
//  // Get all the main menu links
//  $menu_links = menu_tree_output(menu_tree_all_data('main-menu'));
//
//  // Initialize some variables to prevent errors
//  $output = '';
//  $sub_menu = '';
//
//  foreach ($menu_links as $key => $link) {
//    // Add special class needed for Foundation dropdown menu to work
//    !empty($link['#below']) ? $link['#attributes']['class'][] = 'has-flyout' : '';
//
//    // Render top level and make sure we have an actual link
//    if (!empty($link['#href'])) {
//      $output .= '<li' . drupal_attributes($link['#attributes']) . '>' . l($link['#title'], $link['#href']);
//      // Get sub navigation links if they exist
//      foreach ($link['#below'] as $key => $sub_link) {
//        if (!empty($sub_link['#href'])) {
//          $sub_menu .= '<li>' . l($sub_link['#title'], $sub_link['#href']) . '</li>';
//        }
//
//      }
//      $output .= !empty($link['#below']) ? '<a href="#" class="flyout-toggle"><span> </span></a><ul class="flyout">' . $sub_menu . '</ul>' : '';
//
//      // Reset dropdown to prevent duplicates
//      unset($sub_menu);
//      $sub_menu = '';
//
//      $output .=  '</li>';
//    }
//  }
//  return '<ul class="nav-bar">' . $output . '</ul>';
//}

/**
 * Implements template_preprocess_html().
 *
 */
//function SBAC_preprocess_html(&$vars) {
//  // Add conditional CSS for IE. To use uncomment below and add IE css file
//  drupal_add_css(path_to_theme() . '/css/ie.css', array('weight' => CSS_THEME, 'browsers' => array('!IE' => FALSE), 'preprocess' => FALSE));
//
//  // Need legacy support for IE downgrade to Foundation 2 or use JS file below
//  // drupal_add_js('http://ie7-js.googlecode.com/svn/version/2.1(beta4)/IE7.js', 'external');
//}

/**
 * Implements template_preprocess_page
 *
 */
//function SBAC_preprocess_page(&$vars) {
//}

/**
 * Implements template_preprocess_node
 *
 */
//function SBAC_preprocess_node(&$vars) {
//}

/**
 * Implements hook_preprocess_block()
 */
//function SBAC_preprocess_block(&$vars) {
//  // Add wrapping div with global class to all block content sections.
//  $vars['content_attributes_array']['class'][] = 'block-content';
//
//  // Convenience variable for classes based on block ID
//  $block_id = $vars['block']->module . '-' . $vars['block']->delta;
//
//  // Add classes based on a specific block
//  switch ($block_id) {
//    // System Navigation block
//    case 'system-navigation':
//      // Custom class for entire block
//      $vars['classes_array'][] = 'system-nav';
//      // Custom class for block title
//      $vars['title_attributes_array']['class'][] = 'system-nav-title';
//      // Wrapping div with custom class for block content
//      $vars['content_attributes_array']['class'] = 'system-nav-content';
//      break;
//
//    // User Login block
//    case 'user-login':
//      // Hide title
//      $vars['title_attributes_array']['class'][] = 'element-invisible';
//      break;
//
//    // Example of adding Foundation classes
//    case 'block-foo': // Target the block ID
//      // Set grid column or mobile classes or anything else you want.
//      $vars['classes_array'][] = 'six columns';
//      break;
//  }
//
//  // Add template suggestions for blocks from specific modules.
//  switch($vars['elements']['#block']->module) {
//    case 'menu':
//      $vars['theme_hook_suggestions'][] = 'block__nav';
//    break;
//  }
//}

//function SBAC_preprocess_views_view(&$vars) {
//}

/**
 * Implements template_preprocess_panels_pane().
 *
 */
//function SBAC_preprocess_panels_pane(&$vars) {
//}

/**
 * Implements template_preprocess_views_views_fields().
 *
 */
//function SBAC_preprocess_views_view_fields(&$vars) {
//}

/**
 * Status messages in reveal modal
 *
 */
//function SBAC_status_messages($vars) {
//  $display = $vars['display'];
//  $output = '';
//
//  $status_heading = array(
//    'status' => t('Status message'),
//    'error' => t('Error message'),
//    'warning' => t('Warning message'),
//  );
//  foreach (drupal_get_messages($display) as $type => $messages) {
//    $output .= "<div class=\"messages $type\">\n";
//    if (!empty($status_heading[$type])) {
//      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
//    }
//    if (count($messages) > 1) {
//      $output .= " <ul>\n";
//      foreach ($messages as $message) {
//        $output .= '  <li>' . $message . "</li>\n";
//      }
//      $output .= " </ul>\n";
//    }
//    else {
//      $output .= $messages[0];
//    }
//    $output .= "</div>\n";
//  }
//  if ($output != '') {
//    drupal_add_js("jQuery(document).ready(function() { jQuery('#status-messages').reveal();
//            });", array('type' => 'inline', 'scope' => 'footer'));
//    $output = '<div id="status-messages" class="reveal-modal expand" >'. $output;
//    $output .= '<a class="close-reveal-modal">&#215;</a>';
//    $output .= "</div>\n";
//  }
//  return $output;
//}

/**
 * Implements theme_form_element_label()
 * Use foundation tooltips
 */
//function SBAC_form_element_label($vars) {
//  if (!empty($vars['element']['#title'])) {
//    $vars['element']['#title'] = '<span class="secondary label">' . $vars['element']['#title'] . '</span>';
//  }
//  if (!empty($vars['element']['#description'])) {
//    $vars['element']['#description'] = ' <span class="has-tip tip-top radius" data-width="250" title="' . $vars['element']['#description'] . '">' . t('More information?') . '</span>';
//  }
//  return theme_form_element_label($vars);
//}

/**
 * Implements hook_preprocess_button().
 */
//function SBAC_preprocess_button(&$vars) {
//  $vars['element']['#attributes']['class'][] = 'button';
//  if (isset($vars['element']['#parents'][0]) && $vars['element']['#parents'][0] == 'submit') {
//    $vars['element']['#attributes']['class'][] = 'secondary';
//  }
//}

/**
 * Implements hook_form_alter()
 * Example of using foundation sexy buttons
 */
//function SBAC_form_alter(&$form, &$form_state, $form_id) {
//  // Sexy submit buttons
//  if (!empty($form['actions']) && $form['actions']['submit']) {
//    $form['actions']['submit']['#attributes'] = array('class' => array('primary', 'button', 'radius'));
//  }
//}

// Sexy preview buttons
//function SBAC_form_comment_form_alter(&$form, &$form_state) {
//  $form['actions']['preview']['#attributes']['class'][] = array('class' => array('secondary', 'button', 'radius'));
//}

drupal_add_js(libraries_get_path('flexslider') . '/jquery.flexslider-min.js');
drupal_add_css(libraries_get_path('flexslider') . '/flexslider.css');

/**
 * Implements hook_css_alter()
 */
function sbac_css_alter(&$css) {
  // Remove Base theme css, so we can add the latest version and use all mixins without overhead.
  $path = drupal_get_path('theme','zurb_foundation');

  $foundation = $path.'/css/foundation.min.css';
  $normalize = $path.'/css/normalize.css';
  $base = $path.'/css/base.css';
  $app = $path.'/css/app.css';

  unset($css[$foundation]);
  unset($css[$normalize]);
  unset($css[$base]);
  unset($css[$app]);
}

function sbac_js_alter(&$js) {
  // JS that comes with the theme is outdated so w're removing the original js files anadding newer versions
  $path = drupal_get_path('theme','zurb_foundation');

  $jquery = $path.'/js/vendor/jquery.js';
  $foundation = $path.'/js/foundation.min.js';
  $dropdown = $path.'/js/foundation/foundation.dropdown.js';

  unset($js[$jquery]);
  unset($js[$foundation]);
  unset($js[$dropdown]);
}

/**
 * Implements hook_preprocess().
 */
function sbac_preprocess(&$variables, $hook) {
  // TPL needs SSO variable even when SSO is not enabled.
  if (!module_exists('sbac_sso')) {
    $variables['conflicting_profile'] = FALSE;
  }
  // some theme() invocations (specifically within Resources view) are missing keys which Drupal
  // expects to be present, resulting in PHP notices; this workaround adds those defaults when
  // they're missing
  $defaults = array(
    'classes_array',
    'title_attributes_array',
    'content_attributes_array',
    'attributes_array',
  );

  foreach ($defaults as $key) {
    if (!isset($variables[$key])) {
      $variables[$key] = array();
    }
  }
}

/**
 * @param $variables
 * @return string
 */
function sbac_textarea($variables) {
  $element = $variables['element'];
  $element['#attributes']['name'] = $element['#name'];
  $element['#attributes']['id'] = $element['#id'];
  $element['#attributes']['cols'] = $element['#cols'];
  $element['#attributes']['rows'] = $element['#rows'];
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    $wrapper_attributes['class'][] = 'resizable';
  }

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}


/**
 * Implements theme_links() targeting the main menu specifically
 * Outputs Foundation Top Bar http://foundation.zurb.com/docs/navigation.php
 */
function sbac_links__system_main_menu($vars) {
  // Get all the main menu links
  $menu_links = menu_tree_output(menu_tree_all_data('main-menu'));

  // Initialize some variables to prevent errors
  $output = '';
  $sub_menu = '';
  $small_link = '';

  foreach ($menu_links as $key => $link) {
    // Add special class needed for Foundation dropdown menu to work
    $small_link = $link; //duplicate version that won't get the dropdown class, save for later
    !empty($link['#below']) ? $link['#attributes']['class'][] = 'has-dropdown' : '';

    // Render top level and make sure we have an actual link
    if (!empty($link['#href'])) {

      $output .= '<li' . drupal_attributes($link['#attributes']) . '>' . l($link['#title'], $link['#href']);
// Uncomment if we don't want to repeat the links under the dropdown for large-screen
//      $small_link['#attributes']['class'][] = 'show-for-small';
      $sub_menu = '<li' . drupal_attributes($small_link['#attributes']) . '>' . l($link['#title'], $link['#href']);
      // Get sub navigation links if they exist
      foreach ($link['#below'] as $key => $sub_link) {
        if (!empty($sub_link['#href'])) {
        $sub_menu .= '<li>' . l($sub_link['#title'], $sub_link['#href']) . '</li>';
        }
      }
      $output .= !empty($link['#below']) ? '<ul class="dropdown">' . $sub_menu . '</ul>' : '';

      // Reset dropdown to prevent duplicates
      unset($sub_menu);
      unset($small_link);
      $small_link = '';
      $sub_menu = '';

      $output .=  '</li>';
    }
  }
  return '<ul class="left">' . $output . '</ul>';
}
// end Top Bar */
/**
 * Returns HTML for a form element label and required marker.
 *
 * Form element labels include the #title and a #required marker. The label is
 * associated with the element itself by the element #id. Labels may appear
 * before or after elements, depending on theme_form_element() and
 * #title_display.
 *
 * This function will not be called for elements with no labels, depending on
 * #title_display. For elements that have an empty #title and are not required,
 * this function will output no label (''). For required elements that have an
 * empty #title, this will output the required marker alone within the label.
 * The label will use the #id to associate the marker with the field that is
 * required. That is especially important for screenreader users to know
 * which field is required.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #required, #title, #id, #value, #description.
 *
 * @ingroup themeable
 */
function sbac_form_element_label($variables) {
  $element = $variables['element'];

  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  //Alignment Tags Custom
  if (arg(2) != 'edit' && isset($element['#parents'][0]) && $element['#parents'][0] == 'field_education_alignment'){
    return '';
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}
/**
 * Returns HTML for a checkbox form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #return_value, #description, #required,
 *     #attributes, #checked.
 *
 * @ingroup themeable
 */
function sbac_checkbox($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'checkbox';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  // Unchecked checkbox has #value of integer 0.
  if (!empty($element['#checked'])) {
    $element['#attributes']['checked'] = 'checked';
  }
  _form_set_class($element, array('form-checkbox'));

  //Alignment Tags Custom
  if ($element['#type'] == 'checkbox' && strpos($element['#parents'][0], 'term-') !== FALSE){
    $temp = explode('term-', $element['#parents'][0]);
    $tid = $temp[1];
    $term = taxonomy_term_load($tid);
    if ($term) {
      $element['term'] = $term;
      return theme('alignment_checkbox', array('element' => $element));
    }
  }

  return ' <input' . drupal_attributes($element['#attributes']) . ' />';
}
/**
 * Returns HTML for a set of checkbox form elements.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #children, #attributes.
 *
 * @ingroup themeable
 */
function sbac_checkboxes($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'][] = 'form-checkboxes';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }

  if ($element['#type'] == 'checkboxes' && $element['#parents'][0] == 'field_education_alignment'){
    $attributes['class'][] = 'standards-browser select';
  }

  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

function sbac_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }

  if ($element['#type'] == 'checkbox' && strpos($element['#parents'][0], 'term-') !== FALSE){
    $attributes['class'][] = 'large-12 columns';
  }

  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Preprocess function for the yesno template.
 */
function sbac_preprocess_rate_template_yesno(&$variables) {
  extract($variables);

  $buttons = array();
  foreach ($links as $link) {
    $button = theme('rate_button', array('text' => $link['text'], 'href' => $link['href'], 'class' => 'rate-yesno-btn'));
    $buttons[] = $button;
  }
  $variables['buttons'] = $buttons;

  $info = array();
  if ($mode == RATE_CLOSED) {
    $info[] = t('Voting is closed.');
  }
  if ($mode != RATE_COMPACT && $mode != RATE_COMPACT_DISABLED) {
    if (isset($results['user_vote'])) {
      if ($results['user_vote'] == 'yes') {
        $info[] = t('You found this review helpful. Thank you for your feedback.');
      }
      else {
        $info[] = t('You <strong>did not</strong> find this review helpful. Thank you for your feedback.');
      }
    }
  }
  $variables['info'] = implode(' ', $info);
}

/**
 * Preprocess function for page template.
 */
function sbac_preprocess_page(&$variables) {
  if (arg(0) == 'digital-library-resources') {
    $variables['page']['search'] = '';
    $variables['page']['filter'] = '';
    $variables['page']['sub-header'] = '';
    
    // Facet blocks DLR search page
    $block_subjects = module_invoke('facetapi', 'block_view', 'nrsgXavatPXoRE97gHS2r1ESNWswbnCM') ?  module_invoke('facetapi', 'block_view', 'nrsgXavatPXoRE97gHS2r1ESNWswbnCM') : NULL ;
    if($block_subjects) {
      $variables['blocks']['subjects'] = render($block_subjects['content']);
    }

    $block_resource_type = module_invoke('facetapi', 'block_view', 'fRhMp2aUokH7KlAdfnq3f7c0FVV4fr4Q') ?  module_invoke('facetapi', 'block_view', 'fRhMp2aUokH7KlAdfnq3f7c0FVV4fr4Q') : NULL ;
    if($block_resource_type) {
      $variables['blocks']['resource_type'] = render($block_resource_type['content']);
    }
    
    $block_module_type = module_invoke('facetapi', 'block_view', 'SV01DFPPCFVbU0JqswlVxgJCJhXbmcOy') ?  module_invoke('facetapi', 'block_view', 'SV01DFPPCFVbU0JqswlVxgJCJhXbmcOy') : NULL ;
    if($block_module_type) {
      $variables['blocks']['module_type'] = render($block_module_type['content']);
    }
    
    $block_grades = module_invoke('facetapi', 'block_view', 'k204ecdKtRrzpYIMM7Zu0XeKxWWemUh5') ?  module_invoke('facetapi', 'block_view', 'k204ecdKtRrzpYIMM7Zu0XeKxWWemUh5') : NULL ;
    if($block_grades) {
      $variables['blocks']['grades'] = render($block_grades['content']);
    }

    $block_intended_end_users = module_invoke('facetapi', 'block_view', 'L6gAFTHWR0vscswQ685yyJJu1FITNoqS') ?  module_invoke('facetapi', 'block_view', 'L6gAFTHWR0vscswQ685yyJJu1FITNoqS') : NULL ;
    if($block_intended_end_users) {
      $variables['blocks']['intended_end_users'] = render($block_intended_end_users['content']);
    }

    $block_geographic_settings = module_invoke('facetapi', 'block_view', '1R3OMmLo12PjYpsfCD5PMODCA12DF2WR') ?  module_invoke('facetapi', 'block_view', '1R3OMmLo12PjYpsfCD5PMODCA12DF2WR') : NULL ;
    if($block_geographic_settings) {
      $variables['blocks']['geographic_settings'] = render($block_geographic_settings['content']);
    }

    $block_formative_assessment_attributes = module_invoke('facetapi', 'block_view', 'cXOKcVqn9MFTuVzWnt9rC7RLWCWDPQ4N') ?  module_invoke('facetapi', 'block_view', 'cXOKcVqn9MFTuVzWnt9rC7RLWCWDPQ4N') : NULL ;
    if($block_formative_assessment_attributes) {
      $variables['blocks']['formative_assessment_attributes'] = render($block_formative_assessment_attributes['content']);
    }

    $block_intended_student_populations = module_invoke('facetapi', 'block_view', '00LKPOl8iXFf0Xou1niewt0aXS4fppRM') ?  module_invoke('facetapi', 'block_view', '00LKPOl8iXFf0Xou1niewt0aXS4fppRM') : NULL ;
    if($block_intended_student_populations) {
      $variables['blocks']['intended_student_populations'] = render($block_intended_student_populations['content']);
    }

    $block_common_core_state_standards = module_invoke('facetapi', 'block_view', 'UPdv5417AehtcIuC8o5n3oR4NI4SXwXG') ?  module_invoke('facetapi', 'block_view', 'UPdv5417AehtcIuC8o5n3oR4NI4SXwXG') : NULL ;
    if($block_common_core_state_standards) {
      $variables['blocks']['common_core_state_standards'] = render($block_common_core_state_standards['content']);
    }

    $block_media_types = module_invoke('facetapi', 'block_view', 'UrOlQvUwcdlf2A0eLTIoIux0Jkne1XA1') ?  module_invoke('facetapi', 'block_view', 'UrOlQvUwcdlf2A0eLTIoIux0Jkne1XA1') : NULL ;
    if($block_media_types) {
      $variables['blocks']['media_types'] = render($block_media_types['content']);
    }

    $block_educational_use = module_invoke('facetapi', 'block_view', 'OIPuW0AWUGbaUEzkfMhRrqgVcNchlQfM') ?  module_invoke('facetapi', 'block_view', 'OIPuW0AWUGbaUEzkfMhRrqgVcNchlQfM') : NULL ;
    if($block_educational_use) {
      $variables['blocks']['educational_use'] = render($block_educational_use['content']);
    }
  }
}

/**
 * Preprocess function for views fields.
 */
function sbac_preprocess_views_view_fields(&$variables) {
  if ($variables['view']->name == 'digital_library_resources') {
    $node = node_load($variables['fields']['entity_id']->raw);
    $output = '';
    $output .= '<div class="resource-top">';
    if (!empty($node->title)) {
      $output .= '<h3>';
      $output .= l($node->title, 'node/' . $node->nid);
      $output .= '</h3>';
    }

    if (!empty($node->field_thumbnail_uri[LANGUAGE_NONE][0]['safe_value'])) {
      $image = explode("::", $node->field_thumbnail_uri[LANGUAGE_NONE][0]['safe_value']);
      $output .= l('<img src="' . file_create_url($image[0]) . '" />', 'node/' . $node->nid, array('html' => TRUE));
    }

    if (!empty($node->field_alt_body[LANGUAGE_NONE][0]['safe_value'])) {
      $output .= truncate_utf8($node->field_alt_body[LANGUAGE_NONE][0]['safe_value'], 250, TRUE, TRUE, $min_wordsafe_length = 1);
    }

    $output .= '</div>';

    $output .= '<div class="resource-bottom">';

    $output .= '<div class="search-item-break">';
    $output .= t('<span class="bold">Subjects:</span>');
    if (!empty($node->field_subject[LANGUAGE_NONE])) {
      $subject = $node->field_subject[LANGUAGE_NONE];
      $subject_count = count($subject);
      $subject_i = 1;
      foreach ($subject as $subject_term) {
        $subject_comma = '';
        if ($subject_i < $subject_count) {
          $subject_comma = ', ';
        }
        $subject_term_full = taxonomy_term_load($subject_term['tid']);
        $output .= $subject_term_full->name . $subject_comma;
        $subject_i++;
      }
    }
    else {
      $output .= 'Not Subject Specific';
    }
    $output .= '</div>';

    $output .= '<div class="search-item-break">';
    $output .= t('<span class="bold">Grades:</span>');
    if (!empty($node->field_grades[LANGUAGE_NONE])) {
      $grade = $node->field_grades[LANGUAGE_NONE];
      $grade_count = count($grade);
      $grade_i = 1;

      foreach ($grade as $grade_term) {
        $grade_comma = '';
        if ($grade_i < $grade_count) {
          $grade_comma = ', ';
        }
        $grade_term_full = taxonomy_term_load($grade_term['tid']);
        $output .= $grade_term_full->name . $grade_comma;
        $grade_i++;
      }
    }
    else {
      $output .= 'Not Grade Specific';
    }
    $output .= '</div>';

    $output .= '<div class="search-item-break">';
    $output .= t('<span class="bold">Media Types:</span>');
    if (!empty($node->field_digital_media_type[LANGUAGE_NONE])) {
      $media = $node->field_digital_media_type[LANGUAGE_NONE];
      $media_count = count($media);
      $media_i = 1;

      foreach ($media as $media_term) {
        $media_comma = '';
        if ($media_i < $media_count) {
          $media_comma = ', ';
        }
        $media_term_full = taxonomy_term_load($media_term['tid']);
        $output .= $media_term_full->name . $media_comma;
        $media_i++;
      }
    }
    else {
      $output .= 'Not Media Specific';
    }
    $output .= '</div>';
    // Edit Link
    if (user_access('edit any resource content')){
      $output .= '<div class="resource-button search-item-break">';
      $path = 'node/' . $node->nid . '/edit';
      $output .= l('Edit', $path, array('attributes' => array('class' => 'medium button'), 'query' => array('destination' => 'digital-library-resources')));
      $output .= '</div>';
    }
    $output .= '<div class="paradata-numbers">';

    $output .= '<div class="stat-views">';
    $output .= '<a href="#" data-tooltipp="Views">';
    $output .= '<img src="' . drupal_get_path('module', 'sbac_resource') . '/images/icons/icon-statviews.png" alt="Views">';
    $output .= '</a>';
    $output .= '<span>';
    if (!empty($node->field_total_views[LANGUAGE_NONE][0]['value'])) {
      $output .= $node->field_total_views[LANGUAGE_NONE][0]['value'];
    }
    else {
      $output .= '0';
    }
    $output .= '</span>';
    $output .= '</div>';

    $output .= '<div class="stat-downloads">';
    $output .= '<a href="#" data-tooltipp="Downloads">';
    $output .= '<img src="' . drupal_get_path('module', 'sbac_resource') . '/images/icons/icon-statdownloads.png" alt="Views">';
    $output .= '</a>';
    $output .= '<span>';
    if (!empty($node->field_asset_downloads[LANGUAGE_NONE][0]['value'])) {
      $output .= $node->field_asset_downloads[LANGUAGE_NONE][0]['value'];
    }
    else {
      $output .= '0';
    }
    $output .= '</span>';
    $output .= '</div>';

    $rate_count = db_query('SELECT COUNT(*) FROM eck_review WHERE node_id = :nid', array(':nid' => $node->nid))->fetchColumn();
    $output .= '<div class="rating-count">';

    $output .= '<span class="rating-item star-image">';
    $output .= '<a href="#" data-tooltipp="Rating">';
    $output .= sbac_resource_display_fivestar_rating($node->field_node_avg_rating[LANGUAGE_NONE][0]['value']);
    $output .= '</a>';
    $output .= '</span>';
    $output .= '<span class="rating-item">';
    $output .= '(' . $rate_count . ')';
    $output .= '</span>';
    $output .= '</div>';

    $output .= '</div>';
    $output .= '</div>';

    $variables['fields']['entity_id']->wrapper_prefix = '<div class="resource-card">';
    $variables['fields']['entity_id']->wrapper_suffix = '</div>';
    $variables['fields']['entity_id']->content = $output;
  }
}
