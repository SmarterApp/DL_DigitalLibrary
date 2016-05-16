<?php
/**
 * @file
 * Template for SBAC Forum Stats page.
 */
?>
<h2 class="report-title"><?php print t('Forum Statistics Report'); ?></h2>
<p>Includes statistics for forum activity in the Digital Library, including:</p>
<ul>
  <li>Collaboration on resources</li>
  <li>Collaboration in topic forums</li>
</ul>
<div class="report-form-container"><?php print drupal_render($form); ?></div>
<hr />
