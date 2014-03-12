<div class="kw-search-entity-comment-wrapper">
  <div class="row-left">
    <div class="author-thubmnail"><?php print $fields['auth_image'];?></div>
  </div>

  <div class="row-right">
    <div class="view-comment-info">
      <span><?php print $fields['auth_name'];?></span>
      <span><?php print $fields['created'];?></span>
      <span><?php print 'in topic: ' . $fields['topic_link'];?></span>
      <span><?php print 'in forum: ' . $fields['forum_link'];?></span>
    </div>
    <div class="view-field-comment">
			<?php print $fields['content'];?>
		</div>
  </div>
</div>
