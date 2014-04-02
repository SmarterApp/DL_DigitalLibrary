<?php
/**
 * @file
 * Date range dropdown template.
 */
?>
<fieldset class="form-wrapper" id="edit-date-range<?php print $which?>">
    <legend><?php print t('Choose a time period'); ?> <span class="form-required" title="This field is required.">*</span></legend>
        <input type="radio" name="date-select" value="<?php print $ago_30; ?>" <?php print $date_display == t('Last 30 Days') ? 'checked' : ''; ?>><?php print t('Last 30 Days'); ?><br />
        <input type="radio" name="date-select" value="<?php print $ago_60; ?>" <?php print $date_display == t('Last 60 Days') ? 'checked' : ''; ?>><?php print t('Last 60 Days'); ?><br />
        <input type="radio" name="date-select" value="<?php print $ago_90; ?>" <?php print $date_display == t('Last 90 Days') ? 'checked' : ''; ?>><?php print t('Last 90 Days'); ?><br />
        <input type="radio" name="date-select" value="custom" <?php print $date_display == t('Custom Date') ? 'checked' : ''; ?>><?php print t('Custom Date'); ?><br />
            <fieldset class="form-wrapper">
              <legend>Choose a Date:</legend>
<?php // The closing tags are attached to the date popup form element. ?>
