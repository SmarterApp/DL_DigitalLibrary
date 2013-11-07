<?php
/**
 * Implements export of a csv file().
 */
function _cex_download($output, $filename)
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

function format_value_field(&$row, $field, $separator, $encloseer, $subseparator, $quote_arrays, $subquote, $is_date = false)
{
  //reset($array); $first =  key($array);
  $count = count($field['und']);
  $ix = 0;
  $row .= $encloseer;
  if ($count > 1 and $quote_arrays) {
    $row .= $subquote;
  }
  foreach ($field['und'] as $array_value) {
    if (is_null($array_value['value'])) {
      $value = '';
    } else if ($is_date) {
      $value = format_date($array_value['value'], 'custom', 'Y-m-d');
    } else {
      $value = $array_value['value'];
    }
    $row .= str_replace("$encloseer", "$encloseer$encloseer", $value) . $subseparator; //subseparator removed later if at end of array.
    $ix++;
    if ($ix == $count) {
      $row = substr($row, 0, -1);
    } // reduce length by one removing the last sub-separator
  }
  if ($count > 1 and $quote_arrays) {
    $row .= $subquote;
  }
  $row .= $encloseer;
  $row .= $separator;
}

function format_value_property(&$resource_node, $fieldkey, $missing_string)
{
  if (!property_exists($resource_node, $fieldkey)) {
    $resource_node->{$fieldkey} = array();
  }
  if (!array_key_exists('und', $resource_node->{$fieldkey}) or
    is_null($resource_node->{$fieldkey}['und'])
  ) {
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

function format_tid_property(&$resource_node, $fieldkey, $missing_string, &$used_tids)
{
  // todo: look up the actual value in the foreign table, replace the tid with the actual value in the value field.
  if (!property_exists($resource_node, $fieldkey)) {
    $resource_node->{$fieldkey} = array();
  }
  if (!array_key_exists('und', $resource_node->{$fieldkey}) or
    is_null($resource_node->{$fieldkey}['und'])
  ) {
    $resource_node->{$fieldkey}['und'] = array();
    $resource_node->{$fieldkey}['und'][0] = array();
    $resource_node->{$fieldkey}['und'][0]['tid'] = $missing_string;
    $resource_node->{$fieldkey}['und'][0]['value'] = $missing_string;
  }
  $ix = 0;
  foreach ($resource_node->{$fieldkey}['und'] as &$field) {
    if (!array_key_exists('tid', $field) or is_null($field['tid'])) {
      $field['tid'] = $missing_string;
    }
    if (!array_key_exists('value', $field) or is_null($field['value'])) {
      $field['value'] = $missing_string;
    }
    // look up the value in the foreign table.
    if ($field['tid'] != $missing_string) {
      $used_tids[$field['tid']] = $field['tid'];
    }
    $ix++;
  }
}

function set_tid_property(&$resource_node, $fieldkey, &$tid_terms)
{
  $ix = 0;
  foreach ($resource_node->{$fieldkey}['und'] as &$field) {
    // look up the value in the foreign table.
    if ($field['tid'] != 0) {
      $field['value'] = $tid_terms[$field['tid']]->name;
    }
    $ix++;
  }
}
function get_from_array_or_object($accessor,$value)
{
  if (is_array($value)) {
    return $value[$accessor];
  }
  else if (is_object($value)) {
    return $value->{$accessor};
  }
}

function value_or_field($value, $field_in_object=null) {
  if (is_array($field_in_object)) {
    $return_value = '';
    foreach ($field_in_object as $key => $field) {
      if ($key === 'separator') {
        $return_value .= $field;
      }
      else {
        if (is_array($field)) {

          foreach($field as $key => $accessor) {
            if ($key === 0) {
              $object = get_from_array_or_object($accessor,$value);
            }
            else {
              $object = get_from_array_or_object($accessor,$object);
            }
          }
          $return_value .= $object;
        }
        else {
          $return_value .= $value->{$field};
        }
      }
      $return_value .= ' ';
    }
    return $return_value;
  }
  if ($field_in_object) {
    return $value->{$field_in_object};
  }
  if (is_object($value) and (property_exists($value, 'name') or
    method_exists($value, 'name'))) {
    return $value->name;
  }
  return $value;
}
function grab_field_value($value, $field_in_object=null)
{
  if (is_array($value)) {
    if (count($value) == 0) {
      $actual_value = '';
    }
    else if (count($value) == 1) {
      list($actual_value) = $value; // get first value.
      $actual_value = value_or_field($actual_value, $field_in_object);
    }
    else {
      $actual_value = array();
      foreach ($value as $v) {
        array_push($actual_value, value_or_field($v, $field_in_object));
      }
    }
    $return_value = $actual_value;
  } else if (is_object($value)) {
    $return_value = value_or_field($value, $field_in_object);
  }
  else {
    $return_value = $value;
  }
  return $return_value;
}

function get_field_value_using_schema($schemakey, $data, $resource, $primary_key, &$is_date)
{
  if (array_key_exists('foreignkey', $schemakey)) {
    $value = '';
    $foreign_object = get_field_value_using_schema($schemakey['foreignkey'], $data, $resource, $primary_key, $is_date);
    if ($foreign_object != '') {
      if (array_key_exists('wrapper', $schemakey['foreignkey'])) {
        $wrapper = entity_metadata_wrapper($schemakey['foreignkey']['wrapper'], $foreign_object);

        // gets the name from the wrapper... now need the state name.
        if (array_key_exists('foreigndata', $schemakey)) {
          $value = get_field_value_using_key($schemakey['foreigndata'], $data, $wrapper, $schemakey['foreignkey'][0], $is_date);
        }
        else {
          $value = get_field_value_using_key($schemakey, $data, $wrapper, $schemakey['foreignkey'][0], $is_date);
        }
      }
      else { // used.
        $value = $foreign_object; //->{$schemakey['foreignkey']['field']};
      }
    }
    return $value;
  } else {
    return get_field_value_using_key($schemakey, $data, $resource, $primary_key, $is_date);
  }
}

function set_debug_value($message)
{
  if (false) { // set this to true to see debug output.
    return $message;
  }
  return '';
}
function get_field_value_using_key($fieldkey, $data, $resource, $primary_key, &$is_date)
{
  $value = '';
  $is_date = false;
  if (array_key_exists('fieldtype', $fieldkey)) {
    $is_date = $fieldkey['fieldtype'] == 'date';
  }

  if (array_key_exists('function', $fieldkey)) {
    $value = $fieldkey['function']($fieldkey, $resource);
  }
  else if (array_key_exists('path', $fieldkey) and is_array($fieldkey['path'])) {
    $value = $data[$fieldkey['datasource']][$resource->{$primary_key}->value()];
    foreach ($fieldkey['path'] as $accessor => $type) {
      try {
        if ($type = 'class') {
          $value = $value->{$accessor};
        } else {
          $value = $value[$accessor];
        }
      } catch (EntityMetadataWrapperException $e) {
        $value = set_debug_value("Unknown type/accessor: $type/$accessor");
        $is_date = false;
        break;
      }
    }
  }
  else if (array_key_exists('datasource', $fieldkey)) {
    if (array_key_exists('index', $fieldkey)) {
      $primary_key_value = $resource->{$primary_key}->value();
      if (array_key_exists($fieldkey['datasource'], $data) and
        array_key_exists($primary_key_value, $data[$fieldkey['datasource']])
      ) {
        $values = $data[$fieldkey['datasource']][$primary_key_value];
        if ($values and array_key_exists($fieldkey['index'], $values)) {
            try {
              $value = get_value_from_wrapper($fieldkey, $values[$fieldkey['index']]->{$fieldkey[0]});
            } catch (EntityMetadataWrapperException $e) {
              $value = set_debug_value("Unknown Index Field: $fieldkey[0]");
              $is_date = false;
            }
        }
      }

    } else {
      try {
        if (array_key_exists(0, $fieldkey)) {
          $primary_key_value = $resource->{$primary_key}->value();
          if (array_key_exists($primary_key_value, $data[$fieldkey['datasource']])) {
            if (array_key_exists('not_wrapper', $fieldkey)) {
              $value = $data[$fieldkey['datasource']][$primary_key_value]->{$fieldkey[0]};
            }
            else {
              $value = get_value_from_wrapper($fieldkey, $data[$fieldkey['datasource']][$primary_key_value]->{$fieldkey[0]});
            }
          }
        }
      } catch (EntityMetadataWrapperException $e) {
        $value = set_debug_value("Unknown Field");
        $is_date = false;
      }
    }
  } else {
    try {
      if (array_key_exists(0, $fieldkey)) {
        $value = get_value_from_wrapper($fieldkey, $resource->{$fieldkey[0]});
      }
    } catch (EntityMetadataWrapperException $e) {
      $value = set_debug_value("Unknown Field");
      $is_date = false;
    }
  }
//  if (array_key_exists('field',$fieldkey) and !is_array($value) and is_object($value)) {
//    $value = $value->{$fieldkey['field']};
//  }

  return $value;
}

function get_value_from_wrapper($fieldkey, $source)
{
  if (array_key_exists('accessor',$fieldkey)) {
    return $source->{$fieldkey['accessor']}();
  }
  else {
    return $source->value();
  }
}

function format_metadata_value_field(&$row, $field, $csv_configuration, $is_date = false, $field_in_object = null)
{
  $separator = $csv_configuration['separator'];
  $encloseer = $csv_configuration['encloseer'];
  $subseparator = $csv_configuration['subseparator'];
  $quote_arrays = $csv_configuration['quote_arrays'];
  $subquote = $csv_configuration['subquote'];

  $field = grab_field_value($field, $field_in_object);
  $ix = 0;
  $row .= $encloseer;
  if ($field == null) {
    $row .= '';
  } else if (is_array($field)) {
    $count = count($field);
    if ($count > 1 and $quote_arrays) {
      $row .= $subquote;
    }
    foreach ($field as $array_value) {
      if ($is_date) {
        $value = date('Y-m-d', $array_value);
      } else {
        $value = $array_value;
      }
      $row .= str_replace("$encloseer", "$encloseer$encloseer", $value) . $subseparator; //subseparator removed later if at end of array.
      $ix++;
      if ($ix == $count) {
        $row = substr($row, 0, -1);
      } // reduce length by one removing the last sub-separator
    }
    if ($count > 1 and $quote_arrays) {
      $row .= $subquote;
    }
  } else {
    if ($is_date) {
      $value = date('Y-m-d', intval($field));
    } else {
      $value = $field;
    }
    $row .= str_replace("$encloseer", "$encloseer$encloseer", $value);
  }
  $row .= $encloseer;
  $row .= $separator;
}