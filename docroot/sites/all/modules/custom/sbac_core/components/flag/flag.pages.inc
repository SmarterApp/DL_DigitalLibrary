<?php

/**
 * Callback for /flag/review/%
 * @return [type] [description]
 */
function flag_review_ajax_page($entity_id, $state, $trigger_id) {
  $args = func_get_args();

  print_rr($args);

  exit();


  $flag = entity_load_single('flag', $entity_id);
  $commands = dialog_show_form('flag_review_confirmation_form', $flag, $state, $trigger_id);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));


  echo 'here';exit();
}




// function resource_feedback_ajax_page($bundle, $node, $state, $trigger_id, $entity_id = NULL) {
//   $commands = dialog_show_form('feedback_' . $bundle . '_form', $node, $state, $trigger_id, $entity_id);

//   ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
// }