<?php
/**
 * @file
 * Template for SBAC Individual Report page.
 */
?>
<h2 class="report-title"><?php print t('User Activity (CSV Report)'); ?></h2>
<p>Includes site activity statistics for all users, including:</p>
<ul>
  <li>Basic user information</li>
  <li>Activity in the Digital Library</li>
  <li>User contributions and reviews</li>
  <li>Moderation activity</li>
</ul>
<div class="report-form-container"><?php print drupal_render($form); ?></div>
