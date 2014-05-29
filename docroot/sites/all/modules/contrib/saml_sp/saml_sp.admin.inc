<?php
/**
 * @file
 * Admin pages for the SAML Service Provider module.
 */


/**
 * Overview page.
 * Display a list of IDPs in a table.
 */
function saml_sp__admin_overview() {
  return array(
    'idps' => saml_sp__load_all_idps(),
    '#theme' => 'saml_sp__idp_list',
  );
}



/**
 * Configure or add a SAML IDP.
 *
 * @ingroup forms
 */
function saml_sp__configure_idp_form($form, &$form_state, $saml_idp = NULL) {
  if (is_null($saml_idp)) {
    // Populate a default IDP object, with empty fields.
    $saml_idp = _saml_sp__default_idp();
  }
  $form['#destination'] = 'admin/config/people/saml_sp/IDP';

 $form['export_type'] = array(
  '#type' => 'value',
  '#value' => isset($saml_idp->export_type) ? $saml_idp->export_type : NULL,
 );
 
 // If this is an update to an existing IDP, track the original machine name,
 // in case it is changed.
 if (!empty($saml_idp->machine_name)) {
   $form['orig_machine_name'] = array(
     '#type' => 'value',
     '#value' => $saml_idp->machine_name, 
   );
 }

  $form['name'] = array(
    '#type' => 'textfield', 
    '#title' => t('Name'), 
    '#default_value' => $saml_idp->name, 
    '#description' => t('The human-readable name of this IDP. This text will be displayed to administrators who can configure SAML.'), 
    '#required' => TRUE, 
    '#size' => 30,
    '#maxlength' => 30,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name', 
    '#default_value' => $saml_idp->machine_name, 
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'saml_sp_idp_load',
      // 'source' => array('machine_name'),
    ), 
    '#description' => t('A unique machine-readable name for this IDP. It must only contain lowercase letters, numbers, and underscores.'),
  );


  $form['app_name'] = array(
    '#type' => 'textfield',
    '#title' => t('App name'),
    '#description' => t('The app name is provided to the Identiy Provider, to identify the origin of the request.'),
    '#default_value' => $saml_idp->app_name,
    '#maxlength' => 30,
  );

  // The SAML Login URL and x.509 certificate must match the details provided
  // by the IDP.
  $form['idp'] = array(
    '#type' => 'fieldset',
    '#title' => t('IDP configuration'),
    '#description' => t('Enter the details provided by the IDP.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['idp']['idp_login_url'] = array(
    '#type' => 'textfield',
    '#title' => t('IDP URL'),
    '#description' => t('Login URL of the Identity Provider server.'),
    '#default_value' => $saml_idp->login_url,
    '#required' => TRUE,
    '#max_length' => 255,
  );
  $form['idp']['idp_x509_cert'] = array(
    '#type' => 'textarea',
    '#title' => t('x.509 Certificate'),
    '#description' => t('Enter the application certificate provided by the IDP.'),
    '#default_value' => $saml_idp->x509_cert,
    '#required' => TRUE,
    '#max_length' => 1024,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  return $form;
}



/**
 * Submit handler for the SAML IDP configuration form.
 */
function saml_sp__configure_idp_form_submit($form, &$form_state) {
  // Redirect to the admin overview page.
  if (!empty($form['#destination'])) {
    $form_state['redirect'] = $form['#destination'];
  }

  $idp = (object) array(
    'name'         => $form_state['values']['name'],
    'machine_name' => $form_state['values']['machine_name'],
    'app_name'     => $form_state['values']['app_name'],
    'login_url'    => $form_state['values']['idp_login_url'],
    'x509_cert'    => $form_state['values']['idp_x509_cert'],
    'export_type'  => $form_state['values']['export_type'],
  );

  // Machine names can be changed.
  if (isset($form_state['values']['orig_machine_name']) && $form_state['values']['orig_machine_name'] != $form_state['values']['machine_name']) {
    $idp->orig_machine_name = $form_state['values']['orig_machine_name'];
  }

  $result = saml_sp_idp_save($idp);
  switch ($result) {
    case SAVED_NEW:
      drupal_set_message(t('IDP %idp_name has been created.', array('%idp_name' => $form_state['values']['name'])));
      break;

    case SAVED_UPDATED:
      drupal_set_message(t('IDP %idp_name has been updated.', array('%idp_name' => $form_state['values']['name'])));
      break;

    default:
      drupal_set_message(t('An error occurred, IDP %idp_name has not been saved.', array('%idp_name' => $form_state['values']['name'])), 'error');
      break;
  }
}

/**
 * Confirmation form to delete an IDP.
 */
function saml_sp__delete_idp_form($form, &$form_state, $saml_idp) {
  $form['#destination'] = 'admin/config/people/saml_sp/IDP';

  // Pass the name to the submit handler, to use in the message.
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $saml_idp->name,
  );

  // Pass the machine name to the handler, to use as the key for invoking
  // the delete API.
  $form['machine_name'] = array(
    '#type' => 'value',
    '#value' => $saml_idp->machine_name,
  );

  // Usage: confirm_form($form, $question, $path, $description = NULL, $yes = NULL, $no = NULL, $name = 'confirm')
  $question = ($saml_idp->export_type & EXPORT_IN_CODE)
    ? t('Are you sure you wish revert the IDP %idp_name?', array('%idp_name' => $saml_idp->name))
    : t('Are you sure you wish delete the IDP %idp_name?', array('%idp_name' => $saml_idp->name));

  return confirm_form(
    $form,
    $question,
    'admin/config/people/saml_sp/IDP',
    t('This action cannot be undone.'),
    ($saml_idp->export_type & EXPORT_IN_CODE) ? t('Revert') : t('Delete'));
}

/**
 * Submit handler.
 */
function saml_sp__delete_idp_form_submit($form, &$form_state) {
  // Redirect to the admin overview page.
  if (!empty($form['#destination'])) {
    $form_state['redirect'] = $form['#destination'];
  }

  $result = saml_sp_idp_delete($form_state['values']['machine_name']);
  drupal_set_message(t('IDP %idp_name has been deleted.', array('%idp_name' => $form_state['values']['name'])));
}


/**
 * Export handler.
 */
function saml_sp__export_idp($saml_idp) {
  $output = array();

  $code = ctools_export_crud_export('saml_sp_idps', $saml_idp);
  $code .= "\n";
  $code .= '$saml_sp_idps[$saml_idp->machine_name] = $saml_idp;';
  $code .= "\n";
  $file = 'modulename.saml_sp_idps.inc';
  $export_form = drupal_get_form('ctools_export_form', $code, t('Add this to hook_saml_sp_default_idps().'));
  $output['saml_sp_idps__inc'] = array(
    '#markup' => drupal_render($export_form),
  );

  return $output;
}

