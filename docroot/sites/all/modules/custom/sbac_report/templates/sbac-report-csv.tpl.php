<?php
/**
 * @file
 * Template for SBAC Individual Report page.
 */
?>
<h2><?php print t('CSV Report'); ?></h2>
<div class="report-form-container"><?php print drupal_render($form); ?></div>
<hr>
<?php if (!empty($csv_activity_report)) : ?>
  <h2><?php print t('Activity Report'); ?></h2>
  <?php print $csv_activity_report; ?>
<?php endif ?>
