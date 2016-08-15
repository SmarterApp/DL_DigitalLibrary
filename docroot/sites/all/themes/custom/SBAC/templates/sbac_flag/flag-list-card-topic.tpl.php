<div class="resource-card">
  <span id="resource-<?php print $node->nid; ?>"></span>
  <div class="row">
    <?php if (isset($flag_content['eck_post'])): ?>
      <div class="user-photo">
        <?php echo $flag_content['eck_post']['topic_author_picture']; ?>
      </div>
      <div class="post-details">
        <div class="resource-type">
          <span class="resource-type-text">Post</span>
        </div>
        <div class="post-author">
          <?php print $flag_content['eck_post']['topic_author']; ?>
        </div>
        <div class="post-body">
          <span class="post-body-text">
            <?php echo $flag_content['eck_post']['post_body']; ?>
          </span>
        </div>
      </div>
    <?php endif; ?>
    <div class="row-right">
      <?php $class = ''; ?>
      <?php if (isset($flag_content['eck_flag']['display_status_css']) && $flag_content['eck_flag']['display_status_css'] == 'urgent'): ?>
        <?php $class = 'urgent'; ?>
      <?php endif; ?>
      <div class="flag-status <?php echo $class; ?>">
        <?php echo $flag_content['eck_flag']['display_status']; ?>
      </div>
      <?php echo $flag_content['eck_flag']['button']; ?>
    </div>
  </div>
</div>
