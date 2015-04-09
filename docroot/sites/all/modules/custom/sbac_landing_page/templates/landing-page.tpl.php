<?php
/* 
 * 
 * 
 * 
 */
print $test;
?>
<?php if($help_topics): ?>
<div id="landing-page-help-topics">
  <?php print $help_topics; ?>
</div>
<?php endif; ?>

<?php if($featured_content): ?>
<div id="landing-page-featured-content">
  <?php print $featured_content; ?>
</div>
<?php endif; ?>
<?php if($find_resource): ?>
<div id="landing-page-find-resource">
  <?php print $find_resource; ?>
</div>
<?php endif; ?>