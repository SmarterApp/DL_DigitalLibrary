<?php
namespace taskit;

/**
 * Base class.
 */
class Base {
  /**
   * Common getter/setter
   * @param  [type] $key   [description]
   * @param  [type] $value [description]
   * @return [type]        [description]
   */
  public function data($key, $value = NULL) {
    $field = '_' . $key;

    if (!is_null($value)) {
      $this->{$field} = $value;
    }
    elseif (!isset($this->{$field})) {
      $this->{$field} = NULL;
    }

    return $this->{$field};
  }
}