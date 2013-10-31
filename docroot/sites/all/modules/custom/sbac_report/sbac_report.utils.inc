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
  // this doesn't force the output to download: module_invoke_all('exit');
  exit;
}

function format_value_field(&$row, $field, $separator, $encloseer, $subseparator, $quote_arrays, $subquote, $is_date=false)
{
  //reset($array); $first =  key($array);
  $count = count($field['und']); $ix = 0;
  $row.=$encloseer;
  if ($count > 1 and $quote_arrays)  {
    $row .= $subquote;
  }
  foreach ($field['und'] as $array_value) {
    if ($is_date) {
      $value = format_date($array_value['value'], 'custom', 'Y-m-d');
    }
    else {
      $value = $array_value['value'];
    }
    $row .= str_replace("$encloseer","$encloseer$encloseer",$value) . $subseparator; //subseparator removed later if at end of array.
    $ix++;
    if ($ix == $count) {
      $row = substr($row, 0, -1);
    } // reduce length by one removing the last sub-separator
  }
  if ($count > 1 and $quote_arrays)  { $row .= $subquote; }
  $row.=$encloseer;
  $row.=$separator;
}

function format_value_property(&$resource_node, $fieldkey, $missing_string) {
  if (!property_exists($resource_node,$fieldkey)) {
    $resource_node->{$fieldkey} = array();
  }
  if (is_null($resource_node->{$fieldkey}['und'])) {
    $resource_node->{$fieldkey}['und'] = array();
    $resource_node->{$fieldkey}['und'][0] = array();
    $resource_node->{$fieldkey}['und'][0]['value'] = $missing_string;
  }
  $ix = 0;
  foreach ($resource_node->{$fieldkey}['und'] as $field) {
    if (is_null($resource_node->{$fieldkey}['und'][0]['value'])) {
      $resource_node->{$fieldkey}['und'][$ix]['value'] = $missing_string;
    }
    $ix++;
  }
}
function format_tid_property(&$resource_node, $fieldkey, $missing_string, &$used_tids) {
  // todo: look up the actual value in the foreign table, replace the tid with the actual value in the value field.
  if (!property_exists($resource_node,$fieldkey)) {
    $resource_node->{$fieldkey} = array();
  }
  if (is_null($resource_node->{$fieldkey}['und'])) {
    $resource_node->{$fieldkey}['und'] = array();
    $resource_node->{$fieldkey}['und'][0] = array();
    $resource_node->{$fieldkey}['und'][0]['tid'] = $missing_string;
    $resource_node->{$fieldkey}['und'][0]['value'] = $missing_string;
  }
  $ix = 0;
  foreach ($resource_node->{$fieldkey}['und'] as &$field) {
    if (is_null($field['tid'])) {
      $field['tid'] = $missing_string;
    }
    if (is_null($field['value'])) {
      $field['value'] = $missing_string;
    }
    // look up the value in the foreign table.
    if ($field['tid'] != $missing_string) {
      $used_tids[$field['tid']] = $field['tid'];
    }
    $ix++;
  }
}
function set_tid_property(&$resource_node, $fieldkey, &$tid_terms) {
  $ix = 0;
  foreach ($resource_node->{$fieldkey}['und'] as &$field) {
    // look up the value in the foreign table.
    if ($field['tid'] != 0) {
      $field['value'] = $tid_terms[$field['tid']]->name;
    }
    $ix++;
  }
}