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
      if ($form_state['triggering_element']['#value'] == 'Close') {
        $_SESSION['show_critical_message'] = TRUE;
        global $user;
        $disable_help = isset($user->data['disable_help']) ? $user->data['disable_help'] : 0;
        if ((!$disable_help && !isset($_SESSION['user_setup'])) || isset($_SESSION['welcome-update'])) {
          $output[] = ajax_command_invoke('#sbac-central-click-welcome-tutorial', 'remove');
          $output[] = ajax_command_invoke('#sbac-help-welcome-tutorial', 'click');
        }
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
