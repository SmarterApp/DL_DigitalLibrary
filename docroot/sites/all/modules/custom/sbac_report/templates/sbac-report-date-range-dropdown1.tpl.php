<?php
/**
 * @file
 * Date range dropdown template.
 */
?>
<div id="edit-date-range-dropdown<?php print $which ?>" class="date-range-container">
  <label for="date-selected">
  <?php print t('Choose a time period'); ?>
  <span class="form-required" title="This field is required.">*</span>
  </label>
  <a href="#" id="date-selected<?php print $which ?>" class="report-dropdown-toggle"><?php print $date_display; ?></a>
  <div id="date-range-dropdown<?php print $which ?>" class="report-dropdown hide">
    <ul>
      <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $cumulative; ?>">
              <?php print t('Cumulative to date'); ?>
      </a></li>
      <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $ago_30; ?>">
              <?php print t('Last 30 Days'); ?>
      </a></li>
      <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $ago_60; ?>">
              <?php print t('Last 60 Days'); ?>
      </a></li>
      <li><a class="date-range-item report-dropdown-toggle" data-value="<?php print $ago_90; ?>">
              <?php print t('Last 90 Days'); ?>
      </a></li>
    </ul>
    <div><?php print t('Custom Date'); ?></div>
<?php // The closing tags are attached to the date popup form element. ?>
