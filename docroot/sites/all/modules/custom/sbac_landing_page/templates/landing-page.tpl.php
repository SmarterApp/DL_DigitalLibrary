<?php
/* 
 * Template for SBAC landing page
 */
?>
<?php if($help_topics): ?>
<div id="lp-help-topics-wrapper">
  <div id="lp-help-topics" class="row">
    <?php print $help_topics; ?>
  </div>
</div>
<?php endif; ?>

<?php if($featured_content): ?>
<div id="lp-featured-content-wrapper">
  <div id="lp-featured-content">
    <?php print $featured_content; ?>
  </div>
</div>
<?php endif; ?>
<?php if($find_resource): ?>
<div id="lp-find-resource-wrapper">
  <div id="lp-find-resource">
    <?php print $find_resource; ?>
  </div>
</div>
<?php endif; ?>

<?php
