<?php
require_once realpath(__DIR__ . '/../../../vendor/autoload.php');

require_once realpath(__DIR__.'/../../../vendor/autoload.php');

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);


$update_free_access = FALSE;
$drupal_hash_salt = '';

ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 1);
ini_set('session.gc_maxlifetime', 86400);
ini_set('session.cookie_lifetime', 86400);

$conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

include_once('./sites/all/modules/contrib/fast_404/fast_404.inc');

$conf['fast_404_exts'] = '/[^robots]\.(txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['fast_404_allow_anon_imagecache'] = TRUE;

//$conf['fast_404_exts'] = '/\.(txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp|php|html?|xml)$/i';

$conf['fast_404_html'] = '<html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';
$conf['fast_404_path_check'] = FALSE;
$conf['fast_404_url_whitelisting'] = FALSE;
$conf['fast_404_whitelist'] = array('index.php', 'rss.xml', 'install.php', 'cron.php', 'update.php', 'xmlrpc.php');
$conf['fast_404_string_whitelisting'] = array('cdn/farfuture', '/advagg_', 'html5_module', 'resources', 'resource_stats_csv', 'resource_thumbnails', 'html5_thumbnails');
$conf['fast_404_HTML_error_all_paths'] = FALSE;

// Load settings when in Acquia environment
if (isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $settings_file = '/mnt/files/' . $_ENV['AH_SITE_GROUP'] . '.' . $_ENV['AH_SITE_ENVIRONMENT'] . '/files-private/sbac_acquia_settings.inc';
} else {
    // Local Environment settings.
    $settings_file = __DIR__ . '/local_settings.inc';
}

if (isset($settings_file) && file_exists($settings_file)) {
    include_once $settings_file;
}

