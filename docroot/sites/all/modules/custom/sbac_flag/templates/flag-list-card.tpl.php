<div class="resource-card">
  <div class="row">
    <?php if (isset($node->eck_review)): ?>
      <div class="review-title"><a href="<?php echo $node->path['alias']; ?>"><?php echo $node->eck_review_title; ?></a></div>
      <div class="resource-title">
        <?php echo htmlspecialchars_decode($node->title); ?>
      </div>
    <?php endif; ?>
    <?php if (!isset($node->eck_review)): ?>
      <div class="resource-title">
        <a href="<?php echo $node->path['alias']; ?>" ><?php echo htmlspecialchars_decode($node->title); ?></a>
      </div>
    <?php endif; ?>
		<div class="row-right">
    		<div class="flag-status">
		      <?php echo $node->eck_flag->display_status; ?>
		    </div>
		    <?php echo $node->eck_flag->button; ?>
		</div>
  </div>
</div>
