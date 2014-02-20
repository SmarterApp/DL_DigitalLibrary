<?php

/**
 * Ajax callback for sbac_forum_join_button_form in includes/sbac_forum.forms.inc
 */
function sbac_forum__ajax__join_button_form_execute($form, $form_state) {
  // ctools_include('ajax');
  $commands = array();
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

  // Need to update fields on forum entity
  $forum_term_data = entity_metadata_wrapper('taxonomy_term', $forum_term);

  // Update member counter field.
  if (isset($forum_term_data->field_forum_member_count)) {
    $current_member_count = $forum_term_data->field_forum_member_count->value();
    $current_member_count++;
    $forum_term_data->field_forum_member_count->set($current_member_count);
    $member_tab_selector = 'li.sbac-forum-vp-member-tab-item';
    $commands[] = ajax_command_invoke($member_tab_selector, 'addClass', array('sbac-qt-show'));
    $commands[] = ajax_command_invoke($member_tab_selector, 'removeClass', array('sbac-qt-hide'));
    $new_member_count_text = 'Members (' . $current_member_count . ')';
    $commands[] = ajax_command_invoke($member_tab_selector.' a', 'html', array($new_member_count_text));
  }

  $user_obj = user_load($target_user_id); // If user is facilitator, add them to the list of facis
  if (in_array('facilitator', $user_obj->roles)) {
    if (isset($forum_term_data->field_forum_facilitators)) {
      $forum_term_data->field_forum_facilitators[] = $target_user_id;

      // Update facilitator field list.
      $faci_data = entity_metadata_wrapper('user', $user_obj);
      $fn = $faci_data->field_first_name->value();
      $ln = $faci_data->field_last_name->value();
      $full_name = $fn . ' ' . $ln;
      $faci_list_selector = '.vp-faci-field ul.vp-auth-pane';
      $link = 'forum-auth-pane/'. $user_obj->uid;
      $link_ops = array('attributes' => array('class' => 'vp-auth-pane-item'));
      $faci_link = l($full_name, $link, $link_ops);
      $new_faci = '<li>' .$faci_link. '</li>';
      $commands[] = ajax_command_append($faci_list_selector, $new_faci);

      $removed_member_tab_selector = 'li.sbac-forum-vp-rem-members-tab-item';
      $commands[] = ajax_command_invoke($removed_member_tab_selector, 'addClass', array('sbac-qt-show'));
      $commands[] = ajax_command_invoke($removed_member_tab_selector, 'removeClass', array('sbac-qt-hide'));

    }
  }
  $forum_term_data->save(TRUE);
  taxonomy_term_save($forum_term);

  // invlidate memberlist cache when a new user joins.
  $cid = SBAC_FORUM_MEMBER_LIST_CACHE_ENTRY_NAME. $forum_id;
  if (cache_get($cid)) {
    cache_clear_all($cid, 'cache');
  }
  sbac_forum__api__check_user_is_forum_member($forum_id, $target_user_id);

  // Ajax/js fancy behaviour.
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
