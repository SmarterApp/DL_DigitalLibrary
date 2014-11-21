<?php

/**
 * The sbac flag modal
 *
 * @param bool $js
 */
function sbac_central_critical_message_modal($js = FALSE) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    ctools_add_js('ajax-responder');
    ctools_modal_add_js();
    $form_state = array(
      'title' => t('Important Notice'),
      'ajax' => TRUE,
    );

    module_load_include('inc', 'sbac_central', 'sbac_central.modal');
    $output = ctools_modal_form_wrapper('sbac_central_critical_message_form', $form_state);
    // This means the form has been executed
    if (!empty($form_state['executed'])) {
      $output = array();
      $output[] = ctools_modal_command_dismiss();
      if ($form_state['triggering_element']['#value'] != 'Cancel') {

      }
    }
    print ajax_render($output);
    exit();
  }
  else {
    return;
  }
}

/**
 * Critical Message form.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function sbac_central_critical_message_form($form, &$form_state) {
  $critical_message_text = variable_get('critical_message_textbox', '');

  $form['message'] = array(
    '#markup' => $critical_message_text,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Close',
    '#attributes' => array('class' => array('close'))
  );

  return $form;
}
