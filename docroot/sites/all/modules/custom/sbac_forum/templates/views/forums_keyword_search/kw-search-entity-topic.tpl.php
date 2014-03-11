<div class="kw-search-entity-topic-wrapper">
  <div class="row-left">
    <div>
      <?php print $fields['title'];?>
      <?php print 'in forum: ' . $fields['forum_parent'];?>
    </div>
    <div>
      <?php print 'Started by: ' . $fields['started'];?>
      <?php print 'Last Reply: ' . $fields['last_activity'];?>
    </div>
  </div>

  <div class="row-right">
    <?php print $fields['reply_count'];?> Replies
  </div>
</div>
