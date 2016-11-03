<div class="kw-search-entity-topic-wrapper">
  <div class="row-left">
    <div class="view-field-info-upper">
      <div class="view-field-title"><?php print $fields['title'];?></div>
      <div class="view-field-in-forum"><?php print 'in forum: ' .' <span>' . $fields['forum_parent']. '</span>';?></div>
    </div>
    <div class="view-field-info-lower">
      <div class="view-field-start"><?php print 'Started by: ' . $fields['started'];?></div>
      <div class="view-field-last-reply"><?php print 'Last Reply: ' . '<span>'. $fields['last_activity'].'</span>';?></div>
    </div>
  </div>

  <div class="row-right">
    <div class="reply-count"><?php print $fields['reply_count'];?> <span class="label">Replies</span></div>
  </div>
</div>
