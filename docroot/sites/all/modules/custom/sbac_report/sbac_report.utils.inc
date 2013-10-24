<?php
/**
 * Implements export of a csv file().
 */
function _cex_download( $output, $filename)
{
  header("Pragma: public");
  header("Expires: 0");
  header("Cache-Control: private");
  header("Content-type: application/octet-stream");
  header("Content-Disposition: attachment; filename=$filename");
  header("Accept-Ranges: bytes");
  echo $output;
  exit;
}