<?php
/**
 * @file
 * Date range dropdown template.
 */
?>
<div>
<label><?php print t('Choose a time period'); ?></label>
<a href="#" id="date-selected" class="report-dropdown-toggle"><?php print $default_display; ?></a>
<ul id="date-range-dropdown" class="report-dropdown hide">
  <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $ago_30; ?>"><?php print t('Last 30 days'); ?></a></li>
  <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $ago_60; ?>"><?php print t('Last 60 days'); ?></a></li>
  <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $ago_90; ?>"><?php print t('Last 90 days'); ?></a></li>
  <li class="date-range-custom"><?php print drupal_render($from_date_popup); ?></li>
  <li class="date-range-custom"><?php print drupal_render($to_date_popup); ?></li>
</ul>
</div>
