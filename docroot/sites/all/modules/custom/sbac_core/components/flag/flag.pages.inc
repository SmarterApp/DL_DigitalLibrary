<?php

/**
 * Callback for /flag/review/%
 * @return [type] [description]
 */
function flag_review_ajax_page($entity_id, $state, $trigger_id) {
  $review = entity_load_single('review', $entity_id);
  $commands = dialog_show_form('flag_review_modal_form', $review, $state, $trigger_id);

  ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
}
