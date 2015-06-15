<?php

/**
 * Returns current memory usage.
 */
function mem() {
  return formatmem(memory_get_usage(TRUE));
}

/**
 * Returns peak memory usage.
 */
function peak() {
  return formatmem(memory_get_peak_usage(TRUE));
}

/**
 * Formats memory usage.
 */
function formatmem($size) {
  $unit = array('b','kb','mb','gb','tb','pb');

  return @round($size / pow(1024, ($i = floor(log($size, 1024)))) , 2) . ' ' . $unit[$i];
}