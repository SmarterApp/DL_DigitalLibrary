<div class="resource-card">
  <div class="row">
    <?php if (isset($flag_content['eck_review']['title'])): ?>
      <div class="review-title"><a href="<?php echo $node->path['alias']; ?>"><?php echo $flag_content['eck_review']['title']; ?></a></div>
      <div class="resource-title">
        <?php echo htmlspecialchars_decode($node->title); ?>
      </div>
    <?php endif; ?>
    <?php if (!isset($flag_content['eck_review'])): ?>
      <div class="resource-title">
        <a href="<?php echo $node->path['alias']; ?>" ><?php echo htmlspecialchars_decode($node->title); ?></a>
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
