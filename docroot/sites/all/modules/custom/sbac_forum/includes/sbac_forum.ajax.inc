<?php

/**
 * Ajax callback for sbac_forum_join_button_form in includes/sbac_forum.forms.inc
 */
function sbac_forum__ajax__join_button_form_execute($form, $form_state) {
  // ctools_include('ajax');
  $values = $form_state['values'];

  $forum_id = $values['forum_id'];
  $target_user_id = $values['target_user_id'];

  $forum_term = taxonomy_term_load($forum_id);
  $forum_name = $forum_term->name;

  // Create new field collection instance for member being added.
  $params = array(
    'field_name' => 'field_fc_forum_members'
  );
  $new_member_item = entity_create('field_collection_item', $params);
  $new_member_item->setHostEntity('taxonomy_term', $forum_term);
  $new_member_data = entity_metadata_wrapper('field_collection_item', $new_member_item);
  $new_member_data->field_fc_forum_member->set($target_user_id);
  $date = strtotime('today');
  $new_member_data->field_fc_forum_member_joined->set($date);
  $new_member_data->save(TRUE);
  taxonomy_term_save($forum_term);

  // invlidate memberlist cache when a new user joins.
  $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME. $forum_id;
  if (cache_get($cid)) {
    cache_clear_all($cid, 'cache');
  }
  sbac_forum__api__check_user_is_forum_member($forum_id, $target_user_id);

  $message_selector = '.sbac-forum-confirm-message-region';
  $message = 'Welcome to ' . $forum_name;
  $commands[] = ajax_command_html($message_selector, $message);

  $button_selector = '#join-forum-form-wrapper';
  $link_text = sbac_forum__api__create_start_new_topic_link();
  $commands[] = ajax_command_replace($button_selector, $link_text);

  $page = array('#type' => 'ajax', '#commands' => $commands);
  ajax_deliver($page);
  exit;
}
