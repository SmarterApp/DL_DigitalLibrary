<?php


// Acquia DB String
if (file_exists('/var/www/site-php')) {
  require('/var/www/site-php/sbac/sbac-settings.inc');
}

if (isset($_ENV['AH_SITE_ENVIRONMENT'])) {
// Memcache
  $conf['cache_backends'][] = './sites/all/modules/contrib/memcache/memcache.inc';
  $conf['cache_default_class'] = 'MemCacheDrupal';
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
  $conf['memcache_key_prefix'] = 'sbac';
  
  switch ($_ENV['AH_SITE_ENVIRONMENT']) {
    case 'dev':
      $conf['file_private_path'] = '/mnt/files/sbac/files-private';

/**
 * Google OSCaddie Environment Sepecific Settings.
 */
      $conf['google_cdn_folder'] = 'dev';
      $conf['oscaddie_gcs_folder'] = 'dev';

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
      
      break;

    case 'test':
      $conf['file_private_path'] = '/mnt/files/sbac.test/files-private';

/**
 * Google OSCaddie Environment Sepecific Settings.
 */
      $conf['google_cdn_folder'] = 'stage';
      $conf['oscaddie_gcs_folder'] = 'stage';

/**
 * SBAC SSO Settings.
 */
      define('SBAC_SSO_URL', 'https://sso-amptest.smarterbalanced.org/auth/SSORedirect/metaAlias/sbac/idp');
      define('SBAC_SSO_PROGRAM_REQUEST_AUTH', 'https://sso.smarterbalanced.org/auth/oauth2/access_token?realm=/sbac');
      define('SBAC_SSO_PROGRAM_OAUTH_API_LIST', 'https://pm.smarterbalanced.org/rest/tenants');
      define('SBAC_SSO_PROGRAM_OAUTH_API', 'https://pm.smarterbalanced.org/rest/tenantchain');
      define('SBAC_SSO_DESTROY_SESSION_URL', 'https://sso-amptest.smarterbalanced.org/auth/UI/Logout');
      define('SBAC_SSO_LOGOUT_REDIRECT_URL', 'https://sso-amptest.smarterbalanced.org/auth/IDPSloRedirect/metaAlias/sbac/idp');


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

      break;

    case 'prod':
      $conf['file_private_path'] = '/mnt/files/sbac/files-private';

/**
 * Google OSCaddie Environment Sepecific Settings.
 */
      $conf['google_cdn_folder'] = 'production';
      $conf['oscaddie_gcs_folder'] = 'production';

/**
 * SBAC SSO Settings.
 */
      define('SBAC_SSO_URL', 'https://sso.smarterbalanced.org/auth/SSORedirect/metaAlias/sbac/idp');
      define('SBAC_SSO_PROGRAM_REQUEST_AUTH', 'https://sso.smarterbalanced.org/auth/oauth2/access_token?realm=/sbac');
      define('SBAC_SSO_PROGRAM_OAUTH_API_LIST', 'https://pm.smarterbalanced.org/rest/tenants');
      define('SBAC_SSO_PROGRAM_OAUTH_API', 'https://pm.smarterbalanced.org/rest/tenantchain');
      define('SBAC_SSO_DESTROY_SESSION_URL', 'https://sso.smarterbalanced.org/auth/UI/Logout');
      define('SBAC_SSO_LOGOUT_REDIRECT_URL', 'https://sso.smarterbalanced.org/auth/IDPSloRedirect/metaAlias/sbac/idp');


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

      break;
  }
}
else {
// Local Environment settings.
  $file = __DIR__ . '/local_settings.inc';
  if (file_exists($file)) {
    include_once $file;
  }
}

