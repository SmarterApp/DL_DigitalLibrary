<?php

/**
 * Implementation of hook_theme()
 *
 */
function sbac_resource_theme($existing, $type, $theme, $path) {
  $items['node__resource'] = array(
    'render element' => 'elements',
    'path' => $path . '/templates',
    'template' => 'node--resource',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_node',
    ),
  );

  $items['resource_node_form'] = array(
    'file' => 'sbac_resource.forms.inc',
    'render element' => 'form',
  );

  $items['resource_alignment_item'] = array(
    'variables' => array('title' => NULL, 'tags' => array()),
    'template' => 'alignment-item',
  );

  $items['digital_library'] = array(
    'path' => drupal_get_path('module', 'sbac_resource') . '/templates',
    'template' => 'digital-library',
    'variables' => array(
      'resource_grid_view' => NULL,
      'no_results' => NULL,
      'search_string' => NULL,
    )
  );

  // Resources - Grid View
  $items['views_view_fields__resources__grid_view'] = array(
    'template' => 'templates/resources/grid_view/views-view-fields--resources--grid-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  // Resources - Grid View
  $items['views_view__resources__grid_view'] = array(
    'template' => 'templates/resources/grid_view/views-view--resources--grid-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );


  $items['views_view_fields__resources__list_view'] = array(
    'template' => 'templates/resources/list_view/views-view-fields--resources--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resources__list_view__preprocess'
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );


  $items['views_view_unformatted__resources__list_view'] = array(
    'template' => 'templates/resources/list_view/views-view-unformatted--resources--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'rows' => NULL, 'title' => NULL),
    'original hook' => 'views_view_unformatted',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_unformatted',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  $items['views_view__resources__list_view'] = array(
    'template' => 'templates/resources/list_view/views-view--resources--list-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resources__list_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  /*************** ALL RESOURCES *************************************/

  $items['views_view_fields__all_resources__grid_view'] = array(
    'template' => 'templates/all_resources/grid_view/views-view-fields--all-resources--grid-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  $items['views_view__all_resources__grid_view'] = array(
    'template' => 'templates/all_resources/grid_view/views-view--all-resources--grid-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resources__grid_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );


  $items['views_view_fields__all_resources__list_view'] = array(
    'template' => 'templates/all_resources/list_view/views-view-fields--all-resources--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'row' => NULL),
    'original hook' => 'views_view_fields',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_fields',
      'sbac_resource_views_view_fields__resources__list_view__preprocess'
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );


  $items['views_view_unformatted__all_resources__list_view'] = array(
    'template' => 'templates/all_resources/list_view/views-view-unformatted--all-resources--list-view',
    'arguments' => array('view' => NULL, 'options' => NULL, 'rows' => NULL, 'title' => NULL),
    'original hook' => 'views_view_unformatted',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view_unformatted',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  $items['views_view__all_resources__list_view'] = array(
    'template' => 'templates/all_resources/list_view/views-view--all-resources--list-view',
    'arguments' => array('view' => NULL),
    'original hook' => 'views_view',
    'preprocess functions' => array(
      'template_preprocess',
      'template_preprocess_views_view',
      'sbac_resource_views_view__resources__list_view__preprocess',
    ),
    'path' => drupal_get_path('module', 'sbac_resource')
  );

  return $items;
}

/**
 * Extract the title from the alignment
 *
 * @param array $alignment
 *  The alignment array element.
 * @return string
 *   The themed output.
 */
function sbac_resource__alignment_extract($alignment) {
  $title = check_plain($alignment['#title']);
  $tags = array();
  foreach ($alignment['#items'] as $item) {
    $tags[] = $item['taxonomy_term']->name;
  }
  return theme('resource_alignment_item', array('title' => $title, 'tags' => $tags));
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view__resources__grid_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view__resources__list_view__preprocess(&$vars) {
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
}

/**
 * Preprocessor for the grid view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__resources__grid_view__preprocess(&$vars) {
  global $user;
  $vars['fields']['state_button'] = NULL;
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
  $image_assets = _sbac_resource_grid_image($vars['fields']);
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  if (in_array('resource contributor', $user->roles) || in_array('DLRB Member', $user->roles)) {
    $variables = _sbac_resource_contributor_links($vars['fields']);
  }
  if (in_array('resource reviewer', $user->roles)) {
    $variables = _sbac_resource_reviewer_links($vars['fields']);
  }
  if (in_array('resource publisher', $user->roles)) {
    $variables = _sbac_resource_publisher_links($vars['fields']);
  }

  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grades'])) {
    $vars['fields']['grades'] = $variables['grades'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
}

/**
 * Preprocessor for the list view.
 *
 * @param $vars
 */
function sbac_resource_views_view_fields__resources__list_view__preprocess(&$vars) {
  global $user;
  ctools_include('modal');
  ctools_include('ajax');
  ctools_add_js('ajax-responder');
  ctools_modal_add_js();
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_css(drupal_get_path('module','sbac_resource').'/css/sbac_resource.css');
  $image_assets = _sbac_resource_grid_image($vars['fields'], 'list');
  if ($image_assets) {
    $vars['fields']['image'] = $image_assets['image'];
    $vars['fields']['mime-type'] = $image_assets['mime-type'];
    $vars['fields']['file-type-icon'] = $image_assets['file-type-icon'];
  }
  if (in_array('resource contributor', $user->roles) || in_array('DLRB Member', $user->roles)) {
    $variables = _sbac_resource_contributor_links($vars['fields']);
  }
  if (in_array('resource reviewer', $user->roles)) {
    $variables = _sbac_resource_reviewer_links($vars['fields']);
  }
  if (in_array('resource publisher', $user->roles)) {
    $variables = _sbac_resource_publisher_links($vars['fields']);
  }

  if (isset($variables['buttons'])) {
    $vars['fields']['buttons'] = $variables['buttons'];
  }
  if (isset($variables['links'])) {
    $vars['fields']['links'] = $variables['links'];
  }
  if (isset($variables['text'])) {
    $vars['fields']['text'] = $variables['text'];
  }
  if (isset($variables['views'])) {
    $vars['fields']['views'] = $variables['views'];
  }
  if (isset($variables['collaborators'])) {
    $vars['fields']['collaborators'] = $variables['collaborators'];
  }
  if (isset($variables['downloads'])) {
    $vars['fields']['downloads'] = $variables['downloads'];
  }
  if (isset($variables['subject'])) {
    $vars['fields']['subject'] = $variables['subject'];
  }
  if (isset($variables['grade'])) {
    $vars['fields']['grade'] = $variables['grade'];
  }
  if (isset($variables['media_types'])) {
    $vars['fields']['media_types'] = $variables['media_types'];
  }
}

/**
 * Creates the links and buttons for the resource contributor
 *
 * @param $fields
 * @param $links
 * @param $buttons
 * @param $text
 */
function _sbac_resource_contributor_links($fields) {
  $variables = array();
  if (isset($fields['state']->raw)) {
    $nid = $fields['nid']->raw;
    $state = $fields['state']->raw;
    switch ($state) {
      case 'draft':
        $url = url('node/' . $nid . '/edit', array('absolute' => TRUE));
        $variables['buttons'][] = l('Edit', $url, array('attributes' => array('class' => array('medium', 'button'))));
        $variables['buttons'][] = l(t('Delete'), 'sbac_resource/nojs/delete-resource', array(
          'html' => TRUE,
          'attributes' => array(
            'class' => 'use-ajax medium button ctools-modal-sbac-resource-modal-delete-resource',
             'id' => 'sbac-resource-modal-delete-resource'
          ),
          'query' => array('nid' => $nid),
        ));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
        $variables['links'][] = l('Edit', 'node/' . $nid . '/edit', array('absolute' => TRUE));
        $variables['links'][] = l(t('Delete'), 'sbac_resource/nojs/delete-resource', array(
          'html' => TRUE,
          'query' => array(
            'nid' => $nid
          ),
          'attributes' => array(
            'class' => 'use-ajax ctools-modal-sbac-resource-modal-delete-resource',
            'id' => 'sbac-resource-modal-delete-resource'
          )
        ));
        $variables['text'] = t('Saved as Draft');
        break;
      case 'needs_review':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
        $variables['text'] = t('Submitted');
        break;
      case 'being_reviewed':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
        $variables['text'] = t('In Review');
        break;
      case 'rejected':
        $variables['buttons'][] = l('View Notification', 'user', array('absolute' => TRUE, 'fragment' => 'profile-notifications', 'attributes' => array('class' => array('medium', 'button'))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
        $variables['links'][] = l('View Notification', 'user', array('absolute' => TRUE, 'fragment' => 'profile-notifications'));
        $url = url('node/' . $nid . '/edit', array('absolute' => TRUE));
        $variables['links'][] = l('Edit & Resubmit', $url, array('absolute' => TRUE));
        $variables['text'] = t('Returned');
        break;
      case 'approved':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = l('View', $url, array('attributes' => array('class' => array('medium', 'button'))));
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
        $variables['text'] = t('Approved');
        break;
      case 'published':
        $variables['sticky'] = FALSE;
        if ($fields['sticky']->raw) {
          $variables['sticky'] = TRUE;
        }
        $variables['views'] = '0 Views';
        if (isset($fields['field_unique_views'])) {
          $variables['views'] = $fields['field_unique_views']->content;
        }
        $variables['downloads'] = '0 Downloads';
        if (isset($fields['field_asset_downloads'])) {
          $variables['downloads'] = $fields['field_asset_downloads']->content;
        }
        $variables['collaborators'] = 'N Collaborations';
        $variables['subject'] = $fields['field_subject']->content;
        $variables['grades'] = $fields['field_grades']->content;
        $variables['media_types'] = $fields['field_digital_media_type']->content;
        break;
    }

    // JS to properly size the modal when submit resource is clicked.
    $js_settings = array(
      'sbac-resource-modal-delete-resource' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 600,
          'height' => 160,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting');
  }
  return $variables;
}

/**
 * Returns the image icon.
 *
 * @param $fields
 */
function _sbac_resource_grid_image($fields, $view_display = 'grid') {
  $variables = array();
  if (isset($fields['nid']->raw)) {
    $nid = $fields['nid']->raw;
    $node = node_load($nid);
    $image = field_get_items('node', $node, 'field_file');
    $default_file = 'public://file.png';

    $class = 'grid-image';
    if ($view_display == 'list') {
      $class = 'list-image';
    }

    if ($image) {
      $material = field_view_value('node', $node, 'field_file', $image[0]);
      if ($material['#file']) {
        $url = $material['#file']->uri;
        $ext = pathinfo($url, PATHINFO_EXTENSION);
        $media = _sbac_resource_determine_extension($ext);
        if ($media != 'image') {
          $url = $default_file;
        }
        $variables['image'] = theme('image_style', array('style_name' => 'resource_image_grid', 'path' => $url, 'attributes' => array('class' => $class)));
        $variables['mime-type'] = file_get_mimetype($material['#file']->uri);
        $variables['file-type-icon'] = _sbac_resource_determine_file_type_icon($ext);
      }
    }
    else {
      $url = $default_file;
      $variables['image'] = theme('image_style', array('style_name' => 'resource_image_grid', 'path' => $url, 'attributes' => array('class' => $class)));
      $variables['mime-type'] = 'image';
      $variables['file-type-icon'] = _sbac_resource_determine_file_type_icon('jpg');
    }
  }
  return $variables;
}

/**
 * Creates the links and buttons for the resource reviewer
 *
 * @param $fields
 * @param $links
 * @param $buttons
 * @param $text
 */
function _sbac_resource_reviewer_links($fields) {
  $variables = array();
  if (isset($fields['state']->raw)) {
    $nid = $fields['nid']->raw;
    $node = node_load($nid);
    $state = $fields['state']->raw;
    switch ($state) {
      case 'needs_review':
        $url = url('node/' . $nid, array('absolute' => TRUE));
        $variables['buttons'][] = _sbac_resource_start_review_link($node, 'gate_keeper');
        $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
        $variables['links'][] = _sbac_resource_start_review_link($node, 'gate_keeper', 'link');
        $variables['text'] = t('Needs Review');
        break;
      case 'being_reviewed':
        global $user;
        $under_review = FALSE;
        // if the current user is performing the gate keeper process
        $gate_keeper = _sbac_resource_determine_feedback($nid, 'gate_keeper', $user->uid, 1, 0, 1);
        if ($gate_keeper) {
          if (!$gate_keeper['completed'] || !$gate_keeper['status']) {
            $url = url('node/' . $nid, array('absolute' => TRUE));
            $variables['buttons'][] = l('Continue Review', $url, array('attributes' => array('class' => array('medium', 'button'))));
            $variables['links'][] = l('Continue Review', 'node/' . $nid, array('absolute' => TRUE));
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
            $variables['text'] = t('Being Reviewed');
            $under_review = TRUE;
          }
        }

        if (!$under_review) {
          $feedback = _sbac_resource_determine_feedback($nid, 'review', $user->uid, 1, 0, 1, 'set');
          if ($feedback) {
            // if the user is reviewing it, its "being reviewed"
            $url = url('node/' . $nid, array('absolute' => TRUE));
            $variables['buttons'][] = l('Continue Review', $url, array('attributes' => array('class' => array('medium', 'button'))));
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
            $variables['links'][] = l('Continue Review', 'node/' . $nid, array('absolute' => TRUE));
            $variables['text'] = t('Being Reviewed');
          }
          else {
            $url = url('node/' . $nid, array('absolute' => TRUE));
            $variables['buttons'][] = l('Start Review', $url, array('attributes' => array('class' => array('medium', 'button'))));
            $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
            $variables['links'][] = l('Start Review', 'node/' . $nid, array('absolute' => TRUE));
            $variables['text'] = t('Needs Review');
          }
        }

        break;
      case 'published':
        $variables['sticky'] = FALSE;
        if ($fields['sticky']->raw) {
          $variables['sticky'] = TRUE;
        }
        $variables['views'] = '0 Views';
        if (isset($fields['field_unique_views'])) {
          $variables['views'] = $fields['field_unique_views']->content;
        }
        $variables['downloads'] = '0 Downloads';
        if (isset($fields['field_asset_downloads'])) {
          $variables['downloads'] = $fields['field_asset_downloads']->content;
        }
        $variables['collaborators'] = 'N Collaborations';
        $variables['subject'] = $fields['field_subject']->content;
        $variables['grades'] = $fields['field_grades']->content;
        $variables['media_types'] = $fields['field_digital_media_type']->content;
        break;
    }
  }
  return $variables;
}

/**
 * Creates the links and buttons for the resource reviewer
 *
 * @param $fields
 * @param $links
 * @param $buttons
 * @param $text
 */
function _sbac_resource_publisher_links($fields) {
  $variables = array();
  if (isset($fields['state']->raw)) {
    $nid = $fields['nid']->raw;
    $node = node_load($nid);
    $state = $fields['state']->raw;
    switch ($state) {
      case 'approved':
        global $user;
        $feedback = _sbac_resource_determine_feedback($nid, 'post', $user->uid, 1, 0, 1, 'single');
        if ($feedback) {
          $url = url('node/' . $nid, array('absolute' => TRUE));
          $variables['buttons'][] = _sbac_resource_start_review_link($node, 'post');
          $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
          $variables['links'][] = _sbac_resource_start_review_link($node, 'post', 'link');
          $variables['text'] = t('Being Reviewed');
        }
        else {
          $url = url('node/' . $nid, array('absolute' => TRUE));
          $variables['buttons'][] = _sbac_resource_start_review_link($node, 'post');
          $variables['links'][] = l('View Details', 'node/' . $nid, array('absolute' => TRUE));
          $variables['links'][] = _sbac_resource_start_review_link($node, 'post', 'link');
          $variables['text'] = t('Needs Posting');
        }
        break;
      case 'published':
        $variables['sticky'] = FALSE;
        if ($fields['sticky']->raw) {
          $variables['sticky'] = TRUE;
        }
        $variables['views'] = '0 Views';
        if (isset($fields['field_unique_views'])) {
          $variables['views'] = $fields['field_unique_views']->content;
        }
        $variables['downloads'] = '0 Downloads';
        if (isset($fields['field_asset_downloads'])) {
          $variables['downloads'] = $fields['field_asset_downloads']->content;
        }
        $variables['collaborators'] = 'N Collaborations';
        $variables['subject'] = $fields['field_subject']->content;
        $variables['grades'] = $fields['field_grades']->content;
        $variables['media_types'] = $fields['field_digital_media_type']->content;
        break;
    }
  }
  return $variables;
}

/**
 * Selects the number of feedback review items from the table for
 * the given nid / uid.
 *
 * @param $uid
 * @param $nid
 */
function _sbac_resource_determine_feedback($nid, $type = 'review', $uid = FALSE, $status = FALSE, $completed = FALSE, $current = FALSE, $return_type = 'set', $uid_not = FALSE) {
  $feedback = array();
  if ($nid) {
    $query = db_select('eck_feedback', 'f');
    $query->fields('f', array('id', 'uid', 'node_id', 'created', 'changed', 'title', 'status', 'completed', 'met_criteria', 'current'));
    $query->condition('f.node_id', $nid);
    $query->condition('f.type', $type);
    if ($uid !== FALSE) {
      if ($uid_not) {
        $query->condition('f.uid', array($uid), 'NOT IN');
      }
      else{
        $query->condition('f.uid', $uid);
      }
    }
    if ($status !== FALSE) {
      $query->condition('f.status', $status);
    }
    if ($completed !== FALSE) {
      $query->condition('f.completed', $completed);
    }
    if ($current !== FALSE) {
      $query->condition('f.current', $current);
    }
    if ($return_type == 'single') { // get the latest result.
      $query->orderBy('f.id', 'DESC');
      $query->range(0, 1);
      return $query->execute()->fetchAssoc();
    }
    else {
      $result = $query->execute();
      foreach ($result as $record) {
        $feedback[] = $record;
      }
    }
  }
  return $feedback;
}

/**
 * Selects the number of feedback review items from the table for
 * the given nid / uid.
 *
 * @param $uid
 * @param $nid
 */
function _sbac_resource_determine_gate_keeper($nid, $uid = FALSE) {
  if ($nid) {
    $query = db_select('eck_feedback', 'f');
    $query->fields('f', array('id', 'uid', 'node_id', 'created', 'changed', 'title', 'status', 'completed', 'met_criteria', 'current'));
    $query->condition('f.node_id', $nid);
    $query->condition('f.type', 'gate_keeper');
    if ($uid) {
      $query->condition('f.uid', $uid);
    }
    $query->orderBy('f.id', 'DESC');
    $query->range(0, 1);
    return $query->execute()->fetchAssoc();
  }
  return FALSE;
}

/**
 * Pulled from sbac_core/components/feedback/feedback.page.inc
 * _feedback_start_review_link
 * Updated to take more control over the link attributes.
 *
 * @param $node
 * @param $type
 * @return string
 */
function _sbac_resource_start_review_link($node, $type, $style = 'button') {
  if ($type == 'gate_keeper') {
    $stub = 'gate-keeper';
    if (!resource_access('start gate keeper', $node)) {
      return '';
    }
  }
  elseif ($type == 'post') {
    $stub = 'post';
    if (!resource_access('start post', $node)) {
      return '';
    }
  }
  else {
    return '';
  }

  static $count;
  if (is_null($count)) {
    $count = 1;
  }
  else {
    $count++;
  }
  $trigger_id = $stub . '-trigger-' . $count;

  drupal_add_library('dialog', 'dialog');
  $link_text = t('Start Review', array('!hours' => FEEDBACK_REVIEW_TIMEOUT));
  if ($style == 'button') {
    $content = l($link_text, 'node/' . $node->nid . '/review/' . $stub . '/start/' . $trigger_id, array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
          'medium',
          'button',
        ),
        'id' => $trigger_id,
      ),
    ));
  }
  else {
    $content = l($link_text, 'node/' . $node->nid . '/review/' . $stub . '/start/' . $trigger_id, array(
      'attributes' => array(
        'class' => array(
          'use-ajax',
          'use-dialog',
        ),
        'id' => $trigger_id,
      ),
    ));
  }
  return $content;
}
