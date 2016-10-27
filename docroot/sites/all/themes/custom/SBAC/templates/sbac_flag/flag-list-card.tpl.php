<div class="resource-card">
  <span id="resource-<?php print $node->nid; ?>"></span>
  <div class="row">
    <?php if (isset($flag_content['eck_review']['title'])): ?>
      <div class="resource-title">
        <span class="resource-type">Review</span>
      </div>
      <div class="review-title"><a href="<?php echo $flag_content['eck_flag']['title_href']; ?>"><?php echo $flag_content['eck_review']['title']; ?></a></div>
      <div class="resource-description">
        <!-- <?php echo htmlspecialchars_decode($node->title); ?> -->
      </div>
    <?php endif; ?>
    <?php if (!isset($flag_content['eck_review'])): ?>
      <div class="resource-title">
        <span class="resource-type">Resource</span>
        <a href="<?php echo $flag_content['eck_flag']['title_href'] ?>" ><?php echo htmlspecialchars_decode($node->title); ?></a>
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
