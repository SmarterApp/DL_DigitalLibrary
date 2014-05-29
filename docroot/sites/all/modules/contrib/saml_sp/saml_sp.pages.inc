<?php
/**
 * @file
 * User pages for the SAML Service Provider module.
 */

/**
 * Page callback to complete the SAML authentication process.
 * This is the consumer endpoint for all SAML authentication requests.
 */
function saml_sp__endpoint() {
  // Check that the request is a valid SAML response.
  if (!saml_sp__is_valid_authentication_response()) {
    // Not a valid incoming auth-message from an IDP, so abort.
    drupal_goto();
  }

  // The OneLogin_Saml_Response object uses the settings to verify the validity
  // of a request, in OneLogin_Saml_Response::isValid(), via XMLSecurityDSig.
  // Extract the incoming ID (the `inresponseto` parameter of the
  // `<samlp:response` XML node).
  if ($inbound_id = _saml_sp__extract_inbound_id($_POST['SAMLResponse'])) {
    if ($request = saml_sp__get_tracked_request($inbound_id)) {
      $idp = saml_sp_idp_load($request['idp']);
      $settings = saml_sp__get_settings($idp);
      $samlResponse = new OneLogin_Saml_Response($settings, $_POST['SAMLResponse']);

      // Remove the now-expired tracked request.
      cache_clear_all($inbound_id, 'saml_sp_request_tracking_cache');

      // Try to check the validity of the samlResponse.
      try {
        // $samlResponse->isValid() will throw various exceptions to communicate
        // any errors. Sadly, these are all of type Exception - no subclassing.
        $is_valid = $samlResponse->isValid();
      }
      catch (Exception $e) {
        // @TODO: inspect the Exceptions, and log a meaningful error condition.
        $is_valid = FALSE;
      }

      // Invoke the callback function.
      $callback = $request['callback'];
      $result = $callback($is_valid, $samlResponse);
    
      // The callback *should* redirect the user to a valid page.
      // Provide a fail-safe just in case it doesn't.
      if (empty($result)) {
        drupal_goto();
      }
      else {
        return $result;
      }
    }
  }
  // Failover: redirect to the homepage.
  drupal_goto();
}

/**
 * Check that a request is a valid SAML authentication response.
 *
 * @return Boolean
 */
function saml_sp__is_valid_authentication_response() {
  return ($_SERVER['REQUEST_METHOD'] == 'POST' && !empty($_POST['SAMLResponse']));
}
