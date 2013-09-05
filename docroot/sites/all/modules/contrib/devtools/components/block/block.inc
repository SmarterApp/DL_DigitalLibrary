<?php

/**
 * Returns block content.
 * @param  [type] $module [description]
 * @param  [type] $delta  [description]
 * @return [type]         [description]
 */
function block_render($module, $delta) {
  list($handler, $handler_data) = devtools_func_handler(__FUNCTION__, func_get_args());

  if ($handler) {
    return $handler_data;
  }
  else {
    $block = module_invoke($module, 'block_view', $delta);

    if (isset($block['content'])) {
      return $block['content'];
    }
  }

  return FALSE;
}