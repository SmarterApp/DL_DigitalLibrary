<?php

/**
 * Materials widget / form element.
 *
 * @param $form
 * @param $form_state
 */
function _sbac_media_materials_widget(&$form, &$form_state) {
  $form['#attached']['js'][] = drupal_get_path('module', 'sbac_media') . '/js/sbac_media.form.js';

  $form['field_file_container']['#tree'] = TRUE;
  $form['field_file_container'] = array(
    '#prefix'=>'<div id="sbac-content-module-container">',
    '#suffix'=>'</div>',
  );

  // Resource Summary.
  $form['field_file_container']['field_file_summary'] = array(
    '#type' => 'item',
    '#title' => t('Add Materials') . ' ' . theme('form_required_marker'),
    '#markup' => '<p>'.t('You can add a combination of videos, images and documents to this resource. This resource must contain at least one (1) material.').'</p>',
    '#weight' => -101,
    '#prefix' => '<div class="media-table">',
  );

  $form['field_file_container']['materials'] = array(
    '#markup' => '<div id="sbac-media-list"></div>',
    '#weight' => -100,
  );

  $media_items = array();
  if (isset($form['#node']->nid) && $form['#node']->nid) {
    $media_items = sbac_media_load_items($form['#node']->nid);
    if ($media_items) {
      $output = _sbac_media_create_list($media_items);
      $form['field_file_container']['materials'] = array(
        '#markup' => $output,
        '#weight' => -100,
        '#suffix' => '</div>',
      );
    }
    else {
      $form['field_file_container']['materials'] = array(
        '#markup' => '',
        '#weight' => -100,
        '#suffix' => '</div>',
      );
    }
  }
  else {
    $form['field_file_container']['materials'] = array(
      '#markup' => '',
      '#weight' => -100,
      '#suffix' => '</div>',
    );
  }

  $weight = array();
  if ($media_items) {
    foreach ($media_items as $key => $media_item) {
      if ($media_item->weight) {
        $weight[$media_item->id] = $media_item->weight;
      }
      else {
        $weight[$media_item->id] = $key;
      }
    }
  }

  $form['field_file_container']['weights'] = array(
    '#type' => 'hidden',
    '#attributes' => array('id' => 'sbac-media-weights'),
    '#value' => drupal_json_encode($weight),
  );

  $form['field_file_container']['field_embed_video'] = array(
    '#type' => 'textfield',
    '#title' => t('Embed Video URL'),
    '#default_value' => '',
    '#description' => t('e.g. http://www.someserver.com/videos/somevideo.mp4'),
  );

  $form['field_file_container']['field_embed_video_button'] = array(
    '#type' => 'submit',
    '#value' => 'Add Embedded Video',
    '#sbac_embed_video' => TRUE,
    '#validate' => array('sbac_media_widget_form_element_validate'),
    '#attributes' => array('class' => array('video-embed-button')),
    '#ajax'=> array(
      'callback'=>'sbac_media_widget_form_element_upload',
      'wrapper'=> 'sbac-field-file-container',
      'method'=> 'replace',
      'effect'=> 'fade',
    ),
  );

  if (isset($form['#node']->nid) && $form['#node']->nid) {
    $form['field_file_container']['field_embed_video_modal'] = array(
      '#markup' => l(t('Modal'), 'sbac-media/nojs/internet-confirm', array(
        'attributes' => array(
          'class' => 'ctools-use-modal button use-ajax ctools-modal-sbac-media-internet-confirm',
          'id' => 'sbac-media-internet-confirm'
        ),
        'query' => array(
          'nid' => $form['#node']->nid,
          'embed' => 'SBAC-MEDIA-EMBEDDED',
        )
      )),
    );

    // JS to properly size the modal.
    $js_settings = array(
      'sbac-media-internet-confirm' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 600,
          'height' => 160,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting');
  }

  $form['field_file_container']['field_file_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload2'),
    '#size' => 22,
    '#theme_wrappers' => array(),
  );

  $form['field_file_container']['field_file_upload_button'] = array(
    '#type' => 'submit',
    '#value' => 'Upload (100MB Max)',
    // '#submit' => array('sbac_media_widget_form_element_upload'),
    '#sbac_embed_video' => FALSE,
    '#ajax'=> array(
      'callback'=>'sbac_media_widget_form_element_upload',
      'wrapper'=> 'sbac-field-file-container',
      'method'=> 'replace',
      'effect'=> 'fade',
    ),
  );

  // Duplicates modal button.
  if (isset($form['#node']->nid) && $form['#node']->nid) {
    $form['actions']['duplicates_button'] = array(
      '#markup' => l(t('Duplicates'), 'sbac-media/nojs/duplicates', array(
        'attributes' => array(
          'class' => 'ctools-use-modal button use-ajax ctools-modal-sbac-media-modal-duplicates',
          'id' => 'sbac-media-modal-duplicates'
        ),
        'query' => array(
          'nid' => $form['#node']->nid
        )
      )),
      '#weight' => 3,
    );

    // JS to properly size the modal when submit resource is clicked.
    $js_settings = array(
      'sbac-media-modal-duplicates' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 700,
          'height' => 550,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting');
  }

  $form['#after_build'][] = 'sbac_media_after_build_form';
  $form['#group_children']['field_file_container'] = 'group_materials';
}

/**
 * After build function to add the submit handler in.
 *
 * Used to add weights to the eck_media table.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_media_after_build_form($form, $form_state) {
  $form['#submit'][] = 'sbac_media_widget_form_element_submit_handler';
  return $form;
}

/**
 * Submit handler to set the weights;
 *
 * @param $form
 * @param $form_state
 */
function sbac_media_widget_form_element_submit_handler($form, $form_state) {
  if (isset($form_state['input']['weights']) && $form_state['input']['weights']) {
    $weights = drupal_json_decode($form_state['input']['weights']);
    if ($weights) {
      foreach ($weights as $media_id => $weight) {
        db_query("UPDATE {eck_media} SET weight = :weight WHERE id = :id", array(':weight' => $weight, ':id' => $media_id));
      }
    }
  }
}

/**
 * @param $media_items
 * @return string
 */
function _sbac_media_create_list($media_items) {
  $output = '<table id="sbac-media-list" class="sortable">';
  $output .= '<thead><tr><th colspan="3">Material Name</th><th colspan="3">Operations</th></tr><tr><td colspan = 5>Primary Material. This is the main material with which you want users to interact.</td></tr></thead>';
  if (count($media_items) > 1) {
    $output .= '<div class="secondary-items-info">Secondary Material(s). These will be shown adjacent to the primary material.</div>';
  }

  $count = 0;
  foreach ($media_items as $key => $media_item) {

    // Open.
    $output .= '<tr id="' . $media_item->id . '">';

    // Image.
    $type = _sbac_resource_determine_type($media_item, TRUE);
    $output .= '<td class="' . $type . ' ui-icon"></td>';

    // Filename.
    $output .= '<td>' . $media_item->filename;
    if (!$media_item->fid && $media_item->filesize) {
      if (strpos($media_item->embed_url, 'slideshare') !== FALSE) {
        $output .= ' (' . $media_item->filesize . ' total slides)';
      }
      else {
        $output .= ' (' . gmdate("i:s", $media_item->filesize) . ')';
      }
    }
    $output .= '</td>';

    // Filesize.
    $bytes = 'Embedded Video';
    if ($media_item->fid && $media_item->filesize) {
      $bytes = number_format($media_item->filesize / 1024, 2) . ' KB';
    }
    $output .= '<td>' . $bytes . '</td>';

    // Delete link.
    $delete_link = l(t('Delete'), 'sbac-media/nojs/delete-media', array(
      'attributes' => array(
        'class' => 'ctools-use-modal use-ajax ctools-modal-sbac-media-modal-delete-media',
        'id' => 'sbac-media-modal-delete-media'
      ),
      'query' => array(
        'fid' => $media_item->fid,
        'nid' => $media_item->nid,
        'id' => $media_item->id,
      )
    ));
    $output .= '<td class="delete-media"><i class="general foundicon-trash""></i>' . $delete_link . '</td>';

    // Close.
    $output .= '</tr>';
    $count++;
  }
  $output .= '</table>';

  // JS to properly size the modal.
  $js_settings = array(
    'sbac-media-modal-delete-media' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 600,
        'height' => 160,
      ),
    ),
  );
  drupal_add_js($js_settings, 'setting');

  return $output;
}

/**
 * Validate embedded videos.
 *
 * @param $form
 * @param $form_state
 */
function sbac_media_widget_form_element_validate($form, $form_state) {
  if ($form_state['triggering_element']['#value'] == 'Add Embedded Video') {
    if ($form_state['values']['field_embed_video']) {
      $embed_video = strtolower($form_state['values']['field_embed_video']);
      if (strpos($embed_video, 'youtube') === FALSE && strpos($embed_video, 'teachertube') === FALSE && strpos($embed_video, 'schooltube') === FALSE && strpos($embed_video, 'vimeo') === FALSE && strpos($embed_video, 'slideshare') === FALSE) {
        form_set_error('field_embed_video', t('The following URL: ' . $form_state['values']['field_embed_video'] . ' cannot be embedded. Only videos from the following accepted hosts are allowed: YouTube, Vimeo, SchoolTube, TeacherTube and SlideShare.'));
      }
    }
    else {
      form_set_error('field_embed_video', t('You must enter a valid URL: e.g. http://www.someserver.com/videos/somevideo.mp4'));
    }
  }
}

/**
 * The form element submit handler.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_media_widget_form_element_upload($form, $form_state) {
  if (form_get_errors()) {
    $media_items = sbac_media_load_items($form['#node']->nid);
    $output = _sbac_media_create_list($media_items);
    $form['field_file_container']['materials']['#markup'] = $output;
    $form['field_file_container']['materials']['#weight'] = -100;
    return $form['field_file_container'];
  }

  if ($form_state['clicked_button']['#sbac_embed_video']) {
    $embedded_video_source = $form_state['values']['field_embed_video'];
    if (strpos($embedded_video_source, 'youtube') !== FALSE || strpos($embedded_video_source, 'vimeo') !== FALSE) {
      $_SESSION['field_embed_video'] = $embedded_video_source;
      $form['field_file_container']['run_js'] = array(
        '#markup' => '<script>jQuery("#sbac-media-internet-confirm").click();</script>',
      );
    }
    else {
      if (isset($form_state['node'])) {
        $node = $form_state['node'];
        sbac_media_save_embedded_source($embedded_video_source, $node->nid);
      }
    }
  }
  else {
    $allowed_file_types = array('txt doc docx pdf xls xlsx pptx ppt odt odp mp4 mov mp3 aac png jpg jpeg mpg avi ods');
    $directory = "private://resources/" . floor($form['#node']->nid/32000) . "/" . $form['#node']->nid;
    $writable = file_prepare_directory($directory, FILE_CREATE_DIRECTORY);
    if ($writable) {
      $file = file_save_upload('field_file_upload', array('file_validate_extensions' => $allowed_file_types), $directory, $replace = FILE_EXISTS_REPLACE);

      // Yuriy: I've removed the and'ed !$form_state['executed'] condition because it
      // was preventing file uploads, and I don't see a reason for it to be here.
      if ($file) {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);

        if (isset($form_state['node'])) {
          $node = $form_state['node'];
          $file_url = drupal_realpath($file->uri);
          $file_hash = md5_file($file_url);

          // Create the media item, duplicates get checked later.
          $media = new stdClass;
          $media->type = 'media';
          $media->fid = $file->fid;
          $media->nid = $node->nid;
          $media->filename = $file->filename;
          $media->file_size = $file->filesize;
          $media->file_hash = $file_hash;
          $media->weight = 100;
          entity_save('media', $media);
        }
      }
    }
  }

  // Update the view
  $media_items = sbac_media_load_items($form['#node']->nid);
  $output = _sbac_media_create_list($media_items);
  $form['field_file_container']['field_embed_video']['#value'] = '';
  $form['field_file_container']['materials']['#markup'] = $output;
  $form['field_file_container']['materials']['#weight'] = -100;
  // re-populate node so node_presave is up to date.
  $form_state['node']->document = $media_items;

  return $form['field_file_container'];
}
