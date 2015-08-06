<?php
/*
 * Environment specific Site Settings.
 */
$conf['file_private_path'] = '/mnt/files/sbac/files-private';

/**
 * Google OSCaddie Environment Sepecific Settings.
 */
$conf['google_cdn_folder'] = 'stage';
$conf['oscaddie_gcs_folder'] = 'stage';

/**
 * SBAC SSO Settings.
 */
  define('SBAC_SSO_URL', 'https://sso-uat.smarterbalanced.org/auth/SSORedirect/metaAlias/sbac/idp');
  define('SBAC_SSO_PROGRAM_REQUEST_AUTH', 'https://sso.smarterbalanced.org/auth/oauth2/access_token?realm=/sbac');
  define('SBAC_SSO_PROGRAM_OAUTH_API_LIST', 'https://pm.smarterbalanced.org/rest/tenants');
  define('SBAC_SSO_PROGRAM_OAUTH_API', 'https://pm.smarterbalanced.org/rest/tenantchain');
  define('SBAC_SSO_DESTROY_SESSION_URL', 'https://sso-uat.smarterbalanced.org/auth/UI/Logout');
  define('SBAC_SSO_LOGOUT_REDIRECT_URL', 'https://sso-uat.smarterbalanced.org/auth/IDPSloRedirect/metaAlias/sbac/idp');


/**
 * SBAC Search Settings.
 * 
 */ 
$conf['sbac_search_env_env_id'] = 'acquia_search_server_1';
$conf['sbac_search_env_name'] = 'Acquia Search';
$conf['sbac_search_env_url'] = 'http://useast1-c1.acquia-search.com/solr/BVWZ-37038_sbacstg';
$conf['sbac_search_env_service_class'] = 'AcquiaSearchService';
$conf['sbac_search_env_conf'] = array(
  'acquia_override_auto_switch' => 1,
  'acquia_override_selector' => 'BVWZ-37038_sbacdev',
  'acquia_override_subscription_corename' => 'BVWZ-37038_sbacdev',
  'acquia_override_subscription_id' => 'BVWZ-37038',
  'acquia_override_subscription_key' => '9becc29baa4f91fac0900c6625c59534',
  'acquia_search_key' => 'fd919846b89046b75e2403a5a492b5e40f37124c',
  'apachesolr_access_always_add_grants' => 0,
  'apachesolr_direct_commit' => 0,
  'apachesolr_read_only' => '1',
  'apachesolr_soft_commit' => 0,
);
