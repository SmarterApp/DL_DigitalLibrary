<div class="kw-search-entity-comment-wrapper">
  <div class="row-left">
    <div><?php print $fields['auth_image'];?></div>
  </div>

  <div class="row-right">
    <div>
      <?php print $fields['auth_name'];?>
      <?php print $fields['created'];?>
      <?php print 'in topic: ' . $fields['topic_link'];?>
      <?php print 'in forum: ' . $fields['forum_link'];?>
    </div>
    <?php print $fields['content'];?>
  </div>
</div>
