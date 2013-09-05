<?php
/**
 * @file
 * Drush integration for the acquia_spi module.
 */

/**
 * Implements hook_drush_command().
 */
function acquia_spi_drush_command() {
  $items = array();
  $items['spi-get'] = array(
    'description' => dt('Output raw Acquia SPI data.'),
    'options' => array(
      'outfile' => dt('Optional. A file to write data to in the current directory. If omitted Drush will output to stdout.'),
      'format' => dt('Optional. Format may be json, print_r, or var_dump. Defaults to print_r.'),
    ),
    'examples' => array(
      'spi-get --format=json --outfile=spi.json' => 'Write JSON encoded SPI data to spi.json in current directory.',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function acquia_spi_drush_help($section) {
  switch ($section) {
    case 'drush:spi-get':
      return dt("Output raw Acquia SPI data.
 NOTE: If the Acquia SPI module is not enabled or installed, execute with:
   drush -i !spidir
 ", array('!spidir' => dirname(__FILE__)));
  }
}

/**
 * SPI get callback.
 */
function drush_acquia_spi_spi_get() {
  $raw_spi = _acquia_spi_drush_get();
  switch (drush_get_option('format','print_r')) {
    case 'json':
      $spi = drush_json_encode($raw_spi);
      break;
    case 'var_dump':
    case 'var_export':
      $spi = var_export($raw_spi, 1);
      break;
    case 'print_r':
    default:
      $spi = print_r($raw_spi, 1);
      break;
  }
  if ($file = drush_get_option('outfile')) {
    // reset our working directory so that relative paths work as expected
    $wd = getcwd();
    chdir($_SERVER['PWD']);
    if (file_put_contents($file, $spi)) {
      drush_log(dt('SPI Data written to !outfile.', array('!outfile' => realpath($file))), 'success');
    }
    chdir($wd);
  }
  else {
    echo $spi;
  }
}

/**
 * If the Acquia SPI module is not enabled, include acquia_spi.module.
 *
 * HINT: invoke drush with the --include option pointing module folder,
 * otherwise drush will not execute spi-get.
 */
function _acquia_spi_drush_get() {
  global $conf;
  $conf['acquia_spi_ssl_override'] = TRUE;
  if (!function_exists('acquia_spi_get')) {
    drush_include(dirname(__FILE__), 'acquia_spi', drush_drupal_major_version(), 'module');
  }
  if (!function_exists('acquia_agent_load_versions')) {
    drush_include(dirname(dirname(__FILE__)) . '/acquia_agent', 'acquia_agent', drush_drupal_major_version(), 'module');
  }
  return acquia_spi_get();
}
