<div class="kw-search-entity-forum-wrapper">
  <div class="row-left">
    <div><?php print $fields['title'];?></div>
    <div>
      <?php print $fields['membership'];?>
      <?php print 'Last Activity: ' . $fields['last_activity'];?>
    </div>
  </div>

  <div class="row-right">
    <?php print $fields['topic_count'];?> Topics
    <?php print $fields['reply_count'];?> Replies
    <?php print $fields['member_count'];?> Members
  </div>
</div>
