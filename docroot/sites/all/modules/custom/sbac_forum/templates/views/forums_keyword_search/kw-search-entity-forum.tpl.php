<div class="kw-search-entity-forum-wrapper">
  <div class="row-left">
    <div class="view-field-title"><?php print $fields['title'];?></div>
    <div class="view-field-info">
      <div class="view-field-membership"><?php print $fields['membership'];?></div>
      <div class="view-field-last-activity"><?php print 'Last Activity: ' . '<span>'.$fields['last_activity'].'</span>';?></div>
    </div>
  </div>

  <div class="row-right">
    <div class="topic-count"><?php print $fields['topic_count'];?> <span class="label">Topics</span></div>
    <div class="reply-count"><?php print $fields['reply_count'];?> <span class="label">Replies</span></div>
    <div class="member-count"><?php print $fields['member_count'];?> <span class="label">Members</span></div>
  </div>
</div>
