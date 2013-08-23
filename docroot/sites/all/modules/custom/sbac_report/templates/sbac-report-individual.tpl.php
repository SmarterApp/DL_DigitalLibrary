<?php
/**
 * @file
 * Template for SBAC Individual Report page.
 */
?>
<h2><?php print t('Individual SNE Report'); ?></h2>
<div class="report-form-container"><?php print drupal_render($form); ?></div>
<hr>
<?php if (!empty($sne_details) && !empty($contributed_summary)) : ?>
<?php print $sne_details; ?>
<h2><?php print t('Contributed Resources'); ?></h2>
<?php print $contributed_summary; ?>
<?php print $contributed_details; ?>
<div style="clear:both;"></div>
<?php endif ?>
