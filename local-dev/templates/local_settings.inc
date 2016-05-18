<?php

/**
 * Set database variables
 */
if (FALSE !== getenv('MYSQL_DATABASE')) {
    $databases['default']['default'] = array(
      'driver' => 'mysql',
      'database' => $_ENV['MYSQL_DATABASE'],
      'username' => $_ENV['MYSQL_USER'],
      'password' => $_ENV['MYSQL_PASSWORD'],
      'host' => $_ENV['MYSQL_HOST'],
      'prefix' => '',
    );
}

/**
 * Assume we are behind a trusted proxy, so set the remote address
 */
if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
    $_SERVER['REMOTE_ADDR'] = $_SERVER['HTTP_X_FORWARDED_FOR'];
} else if (!empty($_SERVER['HTTP_X_REAL_IP'])) {
    $_SERVER['REMOTE_ADDR'] = $_SERVER['HTTP_X_REAL_IP'];
}

/**
 * Check if we should act like https since we are behind a reverse proxy
 */
if (!empty($_SERVER['HTTP_X_FORWARDED_PROTO'])) {
    $_SERVER['REQUEST_SCHEME'] = $_SERVER['HTTP_X_FORWARDED_PROTO'];
    if ($_SERVER['REQUEST_SCHEME'] === 'https') {
        $_SERVER['HTTPS'] = 'on';
    }
}

$conf['image_allow_insecure_derivatives'] = TRUE;

$conf['file_private_path'] = '/var/www/html/docroot/sites/default/files-private';
$conf['file_temporary_path'] = '/tmp';
